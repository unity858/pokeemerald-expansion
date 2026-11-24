#include "global.h"
#include "event_data.h"
#include "field_move.h"
#include "fldeff.h"
#include "fldeff_misc.h"
#include "party_menu.h"
#include "pokemon.h"
#include "strings.h"
#include "constants/field_move.h"
#include "constants/moves.h"
#include "constants/party_menu.h"

static bool32 IsAlwaysFalse(enum FieldMove fieldMove)
{
    return FALSE;
}

static bool32 IsAlwaysTrue(enum FieldMove fieldMove)
{
    return TRUE;
}

static bool32 HasBadgeForFieldMove(enum FieldMove fieldMove)
{
    return FlagGet(gFieldMoveInfo[fieldMove].arg + FLAG_BADGE01_GET);
}

const struct FieldMoveUnlock gFieldMoveUnlocks[FIELD_MOVE_UNLOCK_COUNT] =
{
    [CANT_UNLOCK] =
    {
        .isUnlockedFunc = IsAlwaysFalse,
        .lockedMessage = gText_EmptyString2,
    },
    [ALWAYS_UNLOCKED] =
    {
        .isUnlockedFunc = IsAlwaysTrue,
        .lockedMessage = gText_EmptyString2,
    },
    [BADGE_UNLOCK] =
    {
        .isUnlockedFunc = HasBadgeForFieldMove,
        .lockedMessage = gText_CantUseUntilNewBadge,
    },
};

#define FLAG_TO_BADGE(flag) flag - FLAG_BADGE01_GET

const struct FieldMoveInfo gFieldMoveInfo[FIELD_MOVES_COUNT] =
{
    [FIELD_MOVE_CUT] =
    {
        .fieldMoveFunc = SetUpFieldMove_Cut,
        .unlockType = BADGE_UNLOCK,
        .moveID = MOVE_CUT,
        .partyMsgID = PARTY_MSG_NOTHING_TO_CUT,
        .arg = IS_FRLG ? FLAG_TO_BADGE(FLAG_BADGE02_GET) : FLAG_TO_BADGE(FLAG_BADGE01_GET),
    },

    [FIELD_MOVE_FLASH] =
    {
        .fieldMoveFunc = SetUpFieldMove_Flash,
        .unlockType = BADGE_UNLOCK,
        .moveID = MOVE_FLASH,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
        .arg = IS_FRLG ? FLAG_TO_BADGE(FLAG_BADGE01_GET) : FLAG_TO_BADGE(FLAG_BADGE02_GET),
    },

    [FIELD_MOVE_ROCK_SMASH] =
    {
        .fieldMoveFunc = SetUpFieldMove_RockSmash,
        .unlockType = BADGE_UNLOCK,
        .moveID = MOVE_ROCK_SMASH,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
        .arg = IS_FRLG ? FLAG_TO_BADGE(FLAG_BADGE06_GET) : FLAG_TO_BADGE(FLAG_BADGE03_GET),
    },

    [FIELD_MOVE_STRENGTH] =
    {
        .fieldMoveFunc = SetUpFieldMove_Strength,
        .unlockType = BADGE_UNLOCK,
        .moveID = MOVE_STRENGTH,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
        .arg = FLAG_TO_BADGE(FLAG_BADGE04_GET),
    },

    [FIELD_MOVE_SURF] =
    {
        .fieldMoveFunc = SetUpFieldMove_Surf,
        .unlockType = BADGE_UNLOCK,
        .moveID = MOVE_SURF,
        .partyMsgID = PARTY_MSG_CANT_SURF_HERE,
        .arg = FLAG_TO_BADGE(FLAG_BADGE05_GET),
    },

    [FIELD_MOVE_FLY] =
    {
        .fieldMoveFunc = SetUpFieldMove_Fly,
        .unlockType = BADGE_UNLOCK,
        .moveID = MOVE_FLY,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
        .arg = IS_FRLG ? FLAG_TO_BADGE(FLAG_BADGE03_GET) : FLAG_TO_BADGE(FLAG_BADGE06_GET),
    },

    [FIELD_MOVE_DIVE] =
    {
        .fieldMoveFunc = SetUpFieldMove_Dive,
        .unlockType = BADGE_UNLOCK,
        .moveID = MOVE_DIVE,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
        .arg = FLAG_TO_BADGE(FLAG_BADGE07_GET),
    },

    [FIELD_MOVE_WATERFALL] =
    {
        .fieldMoveFunc = SetUpFieldMove_Waterfall,
        .unlockType = BADGE_UNLOCK,
        .moveID = MOVE_WATERFALL,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
        .arg = IS_FRLG ? FLAG_TO_BADGE(FLAG_BADGE07_GET) : FLAG_TO_BADGE(FLAG_BADGE08_GET),
    },

    [FIELD_MOVE_TELEPORT] =
    {
        .fieldMoveFunc = SetUpFieldMove_Teleport,
        .unlockType = ALWAYS_UNLOCKED,
        .moveID = MOVE_TELEPORT,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
    },

    [FIELD_MOVE_DIG] =
    {
        .fieldMoveFunc = SetUpFieldMove_Dig,
        .unlockType = ALWAYS_UNLOCKED,
        .moveID = MOVE_DIG,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
    },

    [FIELD_MOVE_SECRET_POWER] =
    {
        .fieldMoveFunc = SetUpFieldMove_SecretPower,
        .unlockType = ALWAYS_UNLOCKED,
        .moveID = MOVE_SECRET_POWER,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
    },

    [FIELD_MOVE_MILK_DRINK] =
    {
        .fieldMoveFunc = SetUpFieldMove_SoftBoiled,
        .unlockType = ALWAYS_UNLOCKED,
        .moveID = MOVE_MILK_DRINK,
        .partyMsgID = PARTY_MSG_NOT_ENOUGH_HP,
    },

    [FIELD_MOVE_SOFT_BOILED] =
    {
        .fieldMoveFunc = SetUpFieldMove_SoftBoiled,
        .unlockType = ALWAYS_UNLOCKED,
        .moveID = MOVE_SOFT_BOILED,
        .partyMsgID = PARTY_MSG_NOT_ENOUGH_HP,
    },

    [FIELD_MOVE_SWEET_SCENT] =
    {
        .fieldMoveFunc = SetUpFieldMove_SweetScent,
        .unlockType = ALWAYS_UNLOCKED,
        .moveID = MOVE_SWEET_SCENT,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
    },
    [FIELD_MOVE_ROCK_CLIMB] =
    {
        .fieldMoveFunc = SetUpFieldMove_RockClimb,
#if OW_ROCK_CLIMB_FIELD_MOVE
        .unlockType = ALWAYS_UNLOCKED,
#else
        .unlockType = CANT_UNLOCK,
#endif
        .moveID = MOVE_ROCK_CLIMB,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
        .hideIfLocked = TRUE,
    },
    [FIELD_MOVE_DEFOG] =
    {
        .fieldMoveFunc = SetUpFieldMove_Defog,
#if OW_DEFOG_FIELD_MOVE
        .unlockType = ALWAYS_UNLOCKED,
#else
        .unlockType = CANT_UNLOCK,
#endif
        .moveID = MOVE_DEFOG,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
        .hideIfLocked = TRUE,
    },
};

// HM items are removed. The 8 former HM field moves are usable by a party
// Pokémon iff the badge requirement is met (IsFieldMoveUnlocked) and it either
// knows the move (e.g. Smeargle via Sketch) or the move is in the learnable
// lists (level-up, egg, teachable) of its species or any of its
// pre-evolutions. Other field moves still have to be known.
bool32 IsHMFieldMove(enum FieldMove fieldMove)
{
    switch (fieldMove)
    {
    case FIELD_MOVE_CUT:
    case FIELD_MOVE_FLASH:
    case FIELD_MOVE_ROCK_SMASH:
    case FIELD_MOVE_STRENGTH:
    case FIELD_MOVE_SURF:
    case FIELD_MOVE_FLY:
    case FIELD_MOVE_DIVE:
    case FIELD_MOVE_WATERFALL:
        return TRUE;
    default:
        return FALSE;
    }
}

static bool32 SpeciesLearnablesContainMove(enum Species species, enum Move move)
{
    u32 i;
    const struct LevelUpMove *levelUpLearnset = GetSpeciesLevelUpLearnset(species);
    const u16 *eggMoves = GetSpeciesEggMoves(species);

    for (i = 0; levelUpLearnset[i].move != LEVEL_UP_MOVE_END; i++)
    {
        if (levelUpLearnset[i].move == move)
            return TRUE;
    }
    for (i = 0; eggMoves[i] != MOVE_UNAVAILABLE; i++)
    {
        if (eggMoves[i] == move)
            return TRUE;
    }
    return CanLearnTeachableMove(species, move);
}

// Fills chain with species followed by each pre-evolution; returns the count.
// chain must hold MAX_PRE_EVO_CHAIN entries (include/field_move.h).
u32 GetPreEvolutionChain(enum Species species, enum Species *chain)
{
    u32 count = 0;

    while (species != SPECIES_NONE && count < MAX_PRE_EVO_CHAIN)
    {
        chain[count++] = species;
        species = GetSpeciesPreEvolution(species);
    }
    return count;
}

static bool32 ChainLearnablesContainMove(const enum Species *chain, u32 chainCount, enum Move move)
{
    for (u32 i = 0; i < chainCount; i++)
    {
        if (SpeciesLearnablesContainMove(chain[i], move))
            return TRUE;
    }
    return FALSE;
}

static bool32 IsUsableMon(struct Pokemon *mon)
{
    enum Species species = GetMonData(mon, MON_DATA_SPECIES);
    return species != SPECIES_NONE && species != SPECIES_EGG && !GetMonData(mon, MON_DATA_IS_EGG);
}

STATIC_ASSERT(FIELD_MOVES_COUNT <= 32, FieldMoveMaskFitsInU32);

// Bitmask of field moves (1 << FIELD_MOVE_*) the mon qualifies for, ignoring
// badges: HM field moves if known or learnable (incl. pre-evolutions), others
// if known.
u32 GetMonFieldMoveQualifiedMask(struct Pokemon *mon)
{
    enum Species chain[MAX_PRE_EVO_CHAIN];
    u32 mask = 0, chainCount;
    enum FieldMove fieldMove;

    if (!IsUsableMon(mon))
        return 0;

    chainCount = GetPreEvolutionChain(GetMonData(mon, MON_DATA_SPECIES), chain);
    for (fieldMove = 0; fieldMove < FIELD_MOVES_COUNT; fieldMove++)
    {
        enum Move move = FieldMove_GetMoveId(fieldMove);

        if (MonKnowsMove(mon, move)
         || (IsHMFieldMove(fieldMove) && ChainLearnablesContainMove(chain, chainCount, move)))
            mask |= 1u << fieldMove;
    }
    return mask;
}

// Whether the mon qualifies for one field move, by the same rule as
// GetMonFieldMoveQualifiedMask (badge requirement checked separately).
bool32 MonQualifiesForFieldMove(struct Pokemon *mon, enum FieldMove fieldMove)
{
    enum Species chain[MAX_PRE_EVO_CHAIN];
    u32 chainCount;

    if (!IsUsableMon(mon))
        return FALSE;
    if (MonKnowsMove(mon, FieldMove_GetMoveId(fieldMove)))
        return TRUE;
    if (!IsHMFieldMove(fieldMove))
        return FALSE;

    chainCount = GetPreEvolutionChain(GetMonData(mon, MON_DATA_SPECIES), chain);
    return ChainLearnablesContainMove(chain, chainCount, FieldMove_GetMoveId(fieldMove));
}
