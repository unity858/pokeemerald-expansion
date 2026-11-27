#include "global.h"
#include "event_data.h"
#include "item.h"
#include "new_game_plus.h"
#include "player_pc.h"
#include "pokedex.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "save.h"
#include "script_pokemon_util.h"
#include "test/test.h"
#include "constants/flags.h"
#include "constants/items.h"

// Tests share the save blocks: leave the PC and party empty for the tests that follow.
static void ClearTestStorage(void)
{
    ResetPokemonStorageSystem();
    ZeroPlayerPartyMons();
}

static void ExpectLevelledDown(struct BoxPokemon *boxMon, enum Species species, u32 hpEv, u32 atkIv)
{
    struct Pokemon fresh;
    u32 i;

    // A freshly created level 1 mon of the species with its initial moveset has the level 1 moves.
    CreateMon(&fresh, species, 1, 0, OTID_STRUCT_PLAYER_ID);
    GiveMonInitialMoveset(&fresh);

    EXPECT_EQ(GetBoxMonData(boxMon, MON_DATA_SPECIES), species);
    EXPECT_EQ(GetLevelFromBoxMonExp(boxMon), 1);
    EXPECT_EQ(GetBoxMonData(boxMon, MON_DATA_HP_EV), hpEv);
    EXPECT_EQ(GetBoxMonData(boxMon, MON_DATA_ATK_IV), atkIv);
    EXPECT_EQ(GetBoxMonData(boxMon, MON_DATA_HP_LOST), 0);
    for (i = 0; i < MAX_MON_MOVES; i++)
        EXPECT_EQ(GetBoxMonData(boxMon, MON_DATA_MOVE1 + i), GetMonData(&fresh, MON_DATA_MOVE1 + i));
    EXPECT_NE(GetBoxMonData(boxMon, MON_DATA_MOVE1), MOVE_NONE);
}

static void CreateTrainedMon(struct Pokemon *mon, enum Species species, u32 level, u32 hpEv, u32 atkIv)
{
    CreateMon(mon, species, level, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(mon, MON_DATA_HP_EV, &hpEv);
    SetMonData(mon, MON_DATA_ATK_IV, &atkIv);
    CalculateMonStats(mon);
}

TEST("New Game Plus moves the party to the PC and levels every stored Pokemon down to 1")
{
    struct Pokemon mon;
    struct Pokemon leftovers[PARTY_SIZE];
    u32 hpLost = 40, isEgg = TRUE, eggExp;

    ResetPokemonStorageSystem();
    ZeroPlayerPartyMons();
    ResetPokedex();

    // Box 1: a trained Wobbuffet that lost HP, then an egg.
    CreateTrainedMon(&mon, SPECIES_WOBBUFFET, 50, 252, 31);
    SetMonData(&mon, MON_DATA_HP_LOST, &hpLost);
    *GetBoxedMonPtr(0, 0) = mon.box;
    CreateMon(&mon, SPECIES_TOGEPI, 5, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&mon, MON_DATA_IS_EGG, &isEgg);
    eggExp = GetMonData(&mon, MON_DATA_EXP);
    *GetBoxedMonPtr(0, 1) = mon.box;

    // Party: Pikachu and Snorlax.
    CreateTrainedMon(&gParties[B_TRAINER_PLAYER][0], SPECIES_PIKACHU, 40, 100, 20);
    CreateTrainedMon(&gParties[B_TRAINER_PLAYER][1], SPECIES_SNORLAX, 60, 4, 7);
    gPartiesCount[B_TRAINER_PLAYER] = 2;
    EXPECT(!IsPlayerPartyAndPokemonStorageFull());

    EXPECT_EQ(NewGamePlus_MovePartyToPC(leftovers), 0);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_SPECIES), SPECIES_NONE);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][1], MON_DATA_SPECIES), SPECIES_NONE);

    NewGamePlus_LevelDownStorage();
    ExpectLevelledDown(GetBoxedMonPtr(0, 0), SPECIES_WOBBUFFET, 252, 31);
    ExpectLevelledDown(GetBoxedMonPtr(0, 2), SPECIES_PIKACHU, 100, 20);
    ExpectLevelledDown(GetBoxedMonPtr(0, 3), SPECIES_SNORLAX, 4, 7);

    // The egg is untouched.
    EXPECT(GetBoxMonData(GetBoxedMonPtr(0, 1), MON_DATA_IS_EGG));
    EXPECT_EQ(GetBoxMonData(GetBoxedMonPtr(0, 1), MON_DATA_EXP), eggExp);

    NewGamePlus_RegisterOwnedMonsInPokedex();
    EXPECT(GetSetPokedexFlag(SpeciesToNationalPokedexNum(SPECIES_WOBBUFFET), FLAG_GET_CAUGHT));
    EXPECT(GetSetPokedexFlag(SpeciesToNationalPokedexNum(SPECIES_PIKACHU), FLAG_GET_CAUGHT));
    EXPECT(GetSetPokedexFlag(SpeciesToNationalPokedexNum(SPECIES_SNORLAX), FLAG_GET_SEEN));
    EXPECT(GetSetPokedexFlag(SpeciesToNationalPokedexNum(SPECIES_SNORLAX), FLAG_GET_CAUGHT));
    EXPECT(!GetSetPokedexFlag(SpeciesToNationalPokedexNum(SPECIES_TOGEPI), FLAG_GET_SEEN));
    EXPECT(!GetSetPokedexFlag(SpeciesToNationalPokedexNum(SPECIES_TOGEPI), FLAG_GET_CAUGHT));
    ClearTestStorage();
}

// Fills the PC with `pcMons` Pokémon (the last one an egg) and the party with `partyMons`.
static void FillStorage(u32 pcMons, u32 partyMons)
{
    struct Pokemon mon;
    u32 i, isEgg = TRUE;

    ResetPokemonStorageSystem();
    ZeroPlayerPartyMons();
    CreateMon(&mon, SPECIES_WOBBUFFET, 10, 0, OTID_STRUCT_PLAYER_ID);
    for (i = 0; i < pcMons; i++)
        *GetBoxedMonPtr(i / IN_BOX_COUNT, i % IN_BOX_COUNT) = mon.box;
    if (pcMons != 0)
        SetBoxMonData(GetBoxedMonPtr((pcMons - 1) / IN_BOX_COUNT, (pcMons - 1) % IN_BOX_COUNT), MON_DATA_IS_EGG, &isEgg);
    for (i = 0; i < partyMons; i++)
        CreateMon(&gParties[B_TRAINER_PLAYER][i], SPECIES_PIKACHU, 10, 0, OTID_STRUCT_PLAYER_ID);
    gPartiesCount[B_TRAINER_PLAYER] = partyMons;
}

TEST("Storage is full at party + PC >= PC capacity, eggs included")
{
    u32 capacity = TOTAL_BOXES_COUNT * IN_BOX_COUNT;
    u32 party, isEgg = TRUE;

    for (party = 0; party <= PARTY_SIZE; party++)
    {
        FillStorage(capacity - 1 - party, party); // 419
        EXPECT(!IsPlayerPartyAndPokemonStorageFull());
        FillStorage(capacity - party, party); // 420
        EXPECT(IsPlayerPartyAndPokemonStorageFull());
    }

    // A party egg counts too: 414 in the PC + 5 + an egg = 420.
    FillStorage(capacity - PARTY_SIZE, PARTY_SIZE - 1);
    EXPECT(!IsPlayerPartyAndPokemonStorageFull());
    CreateMon(&gParties[B_TRAINER_PLAYER][PARTY_SIZE - 1], SPECIES_TOGEPI, 5, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&gParties[B_TRAINER_PLAYER][PARTY_SIZE - 1], MON_DATA_IS_EGG, &isEgg);
    EXPECT(IsPlayerPartyAndPokemonStorageFull());

    // The box-only check keeps its meaning.
    FillStorage(capacity - 1, 1);
    EXPECT(IsPlayerPartyAndPokemonStorageFull());
    EXPECT(!IsPokemonStorageFull());
    ClearTestStorage();
}

TEST("Giving a Pokemon or an egg is refused once storage is full")
{
    u32 capacity = TOTAL_BOXES_COUNT * IN_BOX_COUNT;

    FillStorage(capacity - 2, 1); // 419: one more fits
    EXPECT_EQ(ScriptGiveMon(SPECIES_PIKACHU, 5, ITEM_NONE), MON_GIVEN_TO_PARTY);
    EXPECT(IsPlayerPartyAndPokemonStorageFull());
    EXPECT_EQ(ScriptGiveMon(SPECIES_PIKACHU, 5, ITEM_NONE), MON_CANT_GIVE);
    EXPECT_EQ(ScriptGiveEgg(SPECIES_PICHU), MON_CANT_GIVE);
    EXPECT_EQ(CalculatePlayerPartyCount(), 2);

    // Party full, PC has room but the total is at the limit: nothing goes to the PC either.
    FillStorage(capacity - PARTY_SIZE, PARTY_SIZE);
    EXPECT(!IsPokemonStorageFull());
    EXPECT_EQ(ScriptGiveMon(SPECIES_PIKACHU, 5, ITEM_NONE), MON_CANT_GIVE);
    ClearTestStorage();
}

TEST("New Game Plus is hidden when storage is full (party + PC >= PC capacity), eggs included")
{
    u32 capacity = TOTAL_BOXES_COUNT * IN_BOX_COUNT;
    u8 savedStatus = gSaveFileStatus;

    // A valid save that has beaten the game; the storage check decides.
    gSaveFileStatus = SAVE_STATUS_OK;
    FlagSet(FLAG_SYS_GAME_CLEAR);

    FillStorage(capacity - 1 - PARTY_SIZE, PARTY_SIZE); // 419
    EXPECT(!IsPlayerPartyAndPokemonStorageFull());
    EXPECT(IsNewGamePlusAvailable());

    FillStorage(capacity - PARTY_SIZE, PARTY_SIZE); // 420
    EXPECT(IsPlayerPartyAndPokemonStorageFull());
    EXPECT(!IsNewGamePlusAvailable());

    FillStorage(capacity - 1, 0); // 419, empty party
    EXPECT(IsNewGamePlusAvailable());

    FillStorage(capacity, 0); // 420, empty party
    EXPECT(!IsNewGamePlusAvailable());

    FillStorage(capacity - 2, 1); // 419
    EXPECT(IsNewGamePlusAvailable());
    FillStorage(capacity - 1, 1); // 420
    EXPECT(!IsNewGamePlusAvailable());

    // Only saves CONTINUE would load.
    FillStorage(0, 1);
    EXPECT(IsNewGamePlusAvailable());
    gSaveFileStatus = SAVE_STATUS_ERROR;
    EXPECT(IsNewGamePlusAvailable());
    gSaveFileStatus = SAVE_STATUS_EMPTY;
    EXPECT(!IsNewGamePlusAvailable());
    gSaveFileStatus = SAVE_STATUS_CORRUPT;
    EXPECT(!IsNewGamePlusAvailable());

    // Only saves that have beaten the game.
    gSaveFileStatus = SAVE_STATUS_OK;
    FlagClear(FLAG_SYS_GAME_CLEAR);
    EXPECT(!CanStartNewGamePlus());
    EXPECT(!IsNewGamePlusAvailable());
    gSaveFileStatus = SAVE_STATUS_ERROR;
    EXPECT(!IsNewGamePlusAvailable());
    ClearTestStorage();
    gSaveFileStatus = savedStatus;
}

TEST("New Game Plus keeps party Pokemon that do not fit in a full PC, levelled down")
{
    struct Pokemon mon;
    struct Pokemon leftovers[PARTY_SIZE];
    u32 boxId, boxPos, count;

    ResetPokemonStorageSystem();
    ZeroPlayerPartyMons();
    CreateMon(&mon, SPECIES_WOBBUFFET, 10, 0, OTID_STRUCT_PLAYER_ID);
    for (boxId = 0; boxId < TOTAL_BOXES_COUNT; boxId++)
        for (boxPos = 0; boxPos < IN_BOX_COUNT; boxPos++)
            *GetBoxedMonPtr(boxId, boxPos) = mon.box;
    ZeroBoxMonAt(TOTAL_BOXES_COUNT - 1, IN_BOX_COUNT - 1); // one free slot

    CreateTrainedMon(&gParties[B_TRAINER_PLAYER][0], SPECIES_PIKACHU, 40, 100, 20);
    CreateTrainedMon(&gParties[B_TRAINER_PLAYER][1], SPECIES_SNORLAX, 60, 4, 7);
    gPartiesCount[B_TRAINER_PLAYER] = 2;
    EXPECT(IsPlayerPartyAndPokemonStorageFull());
    EXPECT(!IsNewGamePlusAvailable());

    count = NewGamePlus_MovePartyToPC(leftovers);
    EXPECT_EQ(count, 1);
    EXPECT_EQ(GetBoxMonData(GetBoxedMonPtr(TOTAL_BOXES_COUNT - 1, IN_BOX_COUNT - 1), MON_DATA_SPECIES), SPECIES_PIKACHU);

    ZeroPlayerPartyMons();
    NewGamePlus_RestoreLeftoverParty(leftovers, count);
    EXPECT_EQ(gPartiesCount[B_TRAINER_PLAYER], 1);
    ExpectLevelledDown(&gParties[B_TRAINER_PLAYER][0].box, SPECIES_SNORLAX, 4, 7);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_LEVEL), 1);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_HP), GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_MAX_HP));
    ClearTestStorage();
}

TEST("New Game Plus carries over every bag pocket but Key Items, and the PC items")
{
    void *saved;
    u32 key = 0x5A5A;

    ClearBag();
    memset(gSaveBlock1Ptr->pcItems, 0, sizeof(gSaveBlock1Ptr->pcItems));
    AddBagItem(ITEM_POTION, 5);
    AddBagItem(ITEM_POKE_BALL, 10);
    AddBagItem(ITEM_ORAN_BERRY, 3);
    AddBagItem(ITEM_TM01, 1);
    AddBagItem(ITEM_MACH_BIKE, 1);
    AddPCItem(ITEM_SUPER_POTION, 7);
    // The old save's quantities are encrypted with its key.
    ApplyNewEncryptionKeyToBagItems(key);
    gSaveBlock2Ptr->encryptionKey = key;

    saved = NewGamePlus_SaveItems();
    EXPECT(saved != NULL);

    // What NewGameInitData does in between.
    gSaveBlock2Ptr->encryptionKey = 0;
    ClearBag();
    NewGameInitPCItems();
    NewGamePlus_RestoreItems(saved);

    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_POTION), 5);
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_POKE_BALL), 10);
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_ORAN_BERRY), 3);
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_TM01), 1);
    EXPECT(!CheckBagHasItem(ITEM_MACH_BIKE, 1));
    EXPECT(CheckPCHasItem(ITEM_SUPER_POTION, 7));
    EXPECT(!CheckPCHasItem(ITEM_POTION, 1)); // the new game's starting PC Potion is replaced
}
