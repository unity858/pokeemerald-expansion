#include "global.h"
#include "event_data.h"
#include "item.h"
#include "malloc.h"
#include "new_game_plus.h"
#include "pokedex.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "save.h"
#include "constants/flags.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/species.h"

// See include/new_game_plus.h.

// A save that CONTINUE would load (the main menu shows CONTINUE for SAVE_STATUS_OK and for
// SAVE_STATUS_ERROR, where the newest save was damaged and the previous one was loaded)
// and that has beaten the game.
bool32 CanStartNewGamePlus(void)
{
    return (gSaveFileStatus == SAVE_STATUS_OK || gSaveFileStatus == SAVE_STATUS_ERROR)
        && FlagGet(FLAG_SYS_GAME_CLEAR);
}

u32 NewGamePlus_CountFreePcSlots(void)
{
    u32 boxId, boxPos, count = 0;

    for (boxId = 0; boxId < TOTAL_BOXES_COUNT; boxId++)
    {
        for (boxPos = 0; boxPos < IN_BOX_COUNT; boxPos++)
        {
            if (GetBoxMonData(GetBoxedMonPtr(boxId, boxPos), MON_DATA_SPECIES) == SPECIES_NONE)
                count++;
        }
    }
    return count;
}

u32 NewGamePlus_CountPartyMons(void)
{
    u32 i, count = 0;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_SPECIES) != SPECIES_NONE)
            count++;
    }
    return count;
}

// Storage is full when the party and the PC together hold at least a PC's worth of
// Pokémon (eggs included). Reaching exactly the PC capacity counts as full on purpose,
// so NEW GAME+ always leaves at least one free PC slot after moving the party in.
bool32 NewGamePlus_IsStorageFull(void)
{
    u32 pcMons = TOTAL_BOXES_COUNT * IN_BOX_COUNT - NewGamePlus_CountFreePcSlots();

    return NewGamePlus_CountPartyMons() + pcMons >= TOTAL_BOXES_COUNT * IN_BOX_COUNT;
}

bool32 IsNewGamePlusAvailable(void)
{
    return CanStartNewGamePlus() && !NewGamePlus_IsStorageFull();
}

static struct BoxPokemon *FindFreePcSlot(void)
{
    u32 boxId, boxPos;

    for (boxId = 0; boxId < TOTAL_BOXES_COUNT; boxId++)
    {
        for (boxPos = 0; boxPos < IN_BOX_COUNT; boxPos++)
        {
            struct BoxPokemon *boxMon = GetBoxedMonPtr(boxId, boxPos);
            if (GetBoxMonData(boxMon, MON_DATA_SPECIES) == SPECIES_NONE)
                return boxMon;
        }
    }
    return NULL;
}

u32 NewGamePlus_MovePartyToPC(struct Pokemon *leftovers)
{
    u32 i, leftoverCount = 0;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        struct Pokemon *mon = &gParties[B_TRAINER_PLAYER][i];
        struct BoxPokemon *slot;

        if (GetMonData(mon, MON_DATA_SPECIES) == SPECIES_NONE)
            continue;

        slot = FindFreePcSlot();
        if (slot != NULL)
        {
            MonRestorePP(mon);
            *slot = mon->box;
        }
        else
        {
            leftovers[leftoverCount++] = *mon;
        }
        ZeroMonData(mon);
    }
    return leftoverCount;
}

void NewGamePlus_LevelDownBoxMon(struct BoxPokemon *boxMon)
{
    enum Species species = GetBoxMonData(boxMon, MON_DATA_SPECIES);
    enum Move firstMove;
    u32 exp;

    if (species == SPECIES_NONE || GetBoxMonData(boxMon, MON_DATA_IS_EGG))
        return;

    firstMove = GetBoxMonData(boxMon, MON_DATA_MOVE1);
    exp = gExperienceTables[gSpeciesInfo[SanitizeSpeciesId(species)].growthRate][1];
    SetBoxMonData(boxMon, MON_DATA_EXP, &exp);
    GiveBoxMonInitialMoveset(boxMon);
    // A species with no level 1 move keeps its old first move rather than knowing none.
    if (GetBoxMonData(boxMon, MON_DATA_MOVE1) == MOVE_NONE && firstMove != MOVE_NONE)
        SetBoxMonMoveSlot(boxMon, firstMove, 0);
    // Box mons store HP lost; clear it so the lower max HP never underflows. Also clears
    // status and restores PP (with PP Ups) for the new moves.
    HealBoxPokemon(boxMon);
}

void NewGamePlus_LevelDownStorage(void)
{
    u32 boxId, boxPos;

    for (boxId = 0; boxId < TOTAL_BOXES_COUNT; boxId++)
    {
        for (boxPos = 0; boxPos < IN_BOX_COUNT; boxPos++)
            NewGamePlus_LevelDownBoxMon(GetBoxedMonPtr(boxId, boxPos));
    }
}

void NewGamePlus_RestoreLeftoverParty(const struct Pokemon *leftovers, u32 count)
{
    u32 i;

    if (count > PARTY_SIZE)
        count = PARTY_SIZE;
    for (i = 0; i < count; i++)
    {
        struct Pokemon *mon = &gParties[B_TRAINER_PLAYER][i];

        u32 mail = MAIL_NONE;

        *mon = leftovers[i];
        // The mail data was wiped with the rest of the save.
        SetMonData(mon, MON_DATA_MAIL, &mail);
        NewGamePlus_LevelDownBoxMon(&mon->box);
        if (!GetMonData(mon, MON_DATA_IS_EGG))
        {
            CalculateMonStats(mon);
            HealPokemon(mon);
        }
    }
    gPartiesCount[B_TRAINER_PLAYER] = CalculatePartyCount(B_TRAINER_PLAYER);
}

static void RegisterBoxMonInPokedex(struct BoxPokemon *boxMon)
{
    enum Species species = GetBoxMonData(boxMon, MON_DATA_SPECIES);
    enum NationalDexOrder nationalNum;
    u32 personality;

    if (species == SPECIES_NONE || GetBoxMonData(boxMon, MON_DATA_IS_EGG))
        return;

    nationalNum = SpeciesToNationalPokedexNum(species);
    if (nationalNum == NATIONAL_DEX_NONE)
        return;

    // As the catch path does: seen first (records the Unown/Spinda personality
    // the first time that species is seen), then caught.
    personality = GetBoxMonData(boxMon, MON_DATA_PERSONALITY);
    HandleSetPokedexFlag(nationalNum, FLAG_SET_SEEN, personality);
    HandleSetPokedexFlag(nationalNum, FLAG_SET_CAUGHT, personality);
}

void NewGamePlus_RegisterOwnedMonsInPokedex(void)
{
    u32 i, boxId, boxPos;

    for (boxId = 0; boxId < TOTAL_BOXES_COUNT; boxId++)
    {
        for (boxPos = 0; boxPos < IN_BOX_COUNT; boxPos++)
            RegisterBoxMonInPokedex(GetBoxedMonPtr(boxId, boxPos));
    }
    for (i = 0; i < PARTY_SIZE; i++)
        RegisterBoxMonInPokedex(&gParties[B_TRAINER_PLAYER][i].box);
}

// Items: every bag pocket except Key Items, and the PC item storage, carry over.

static u32 GetCarriedItemSlotCount(void)
{
    u32 pocketId, count = PC_ITEMS_COUNT;

    for (pocketId = 0; pocketId < POCKETS_COUNT; pocketId++)
    {
        if (pocketId != POCKET_KEY_ITEMS)
            count += gBagPockets[pocketId].capacity;
    }
    return count;
}

void *NewGamePlus_SaveItems(void)
{
    struct ItemSlot *saved = Alloc(GetCarriedItemSlotCount() * sizeof(struct ItemSlot));
    u32 pocketId, i, n = 0;

    if (saved == NULL)
        return NULL;

    for (pocketId = 0; pocketId < POCKETS_COUNT; pocketId++)
    {
        if (pocketId == POCKET_KEY_ITEMS)
            continue;
        // Decrypted with the old save's key, which NewGameInitData resets afterwards.
        for (i = 0; i < gBagPockets[pocketId].capacity; i++)
            saved[n++] = BagPocket_GetSlotData(&gBagPockets[pocketId], i);
    }
    for (i = 0; i < PC_ITEMS_COUNT; i++)
        saved[n++] = gSaveBlock1Ptr->pcItems[i];
    return saved;
}

void NewGamePlus_RestoreItems(void *savedItems)
{
    const struct ItemSlot *saved = savedItems;
    u32 pocketId, i, n = 0, pcCount = 0;

    if (saved == NULL)
        return;

    for (pocketId = 0; pocketId < POCKETS_COUNT; pocketId++)
    {
        if (pocketId == POCKET_KEY_ITEMS)
            continue;
        for (i = 0; i < gBagPockets[pocketId].capacity; i++)
        {
            struct ItemSlot slot = saved[n++];
            if (slot.itemId == ITEM_NONE || slot.quantity == 0)
                slot = (struct ItemSlot) {ITEM_NONE, 0};
            BagPocket_SetSlotData(&gBagPockets[pocketId], i, slot);
        }
    }

    // Replaces the new game's starting PC items. Key items never stay in the PC.
    memset(gSaveBlock1Ptr->pcItems, 0, sizeof(gSaveBlock1Ptr->pcItems));
    for (i = 0; i < PC_ITEMS_COUNT; i++)
    {
        struct ItemSlot slot = saved[n++];
        if (slot.itemId == ITEM_NONE || slot.quantity == 0 || GetItemPocket(slot.itemId) == POCKET_KEY_ITEMS)
            continue;
        gSaveBlock1Ptr->pcItems[pcCount++] = slot;
    }

    Free(savedItems);
}
