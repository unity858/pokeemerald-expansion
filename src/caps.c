#include "global.h"
#include "battle.h"
#include "event_data.h"
#include "caps.h"
#include "difficulty.h"
#include "level_scaling.h"
#include "pokemon.h"

// R.O.W.E. level caps by badge count: 16 with no badges, 77 with all 8, MAX_LEVEL once the game is cleared.
// After Rayquaza (LEVEL_SCALING_STAGE_RAYQUAZA) there is no cap.
static const u8 sBadgeLevelCaps[LEVEL_SCALING_STAGE_GAME_CLEAR + 1] = {16, 23, 29, 36, 43, 51, 57, 69, 77, MAX_LEVEL};

// The badge-count cap, before the difficulty decides how it applies.
u32 GetBadgeLevelCap(void)
{
    u32 stage = GetLevelScalingBadgeCount();

    if (stage >= ARRAY_COUNT(sBadgeLevelCaps) || sBadgeLevelCaps[stage] > MAX_LEVEL)
        return MAX_LEVEL;
    return sBadgeLevelCaps[stage];
}

// The cap used for EXP gain, level-ups and the Day Care (B_EXP_CAP_TYPE).
// With LEVEL_CAP_BADGE_COUNT, only Hard has one.
u32 GetCurrentLevelCap(void)
{
    if (B_LEVEL_CAP_TYPE == LEVEL_CAP_BADGE_COUNT)
    {
        if (GetLevelScalingDifficulty() == DIFFICULTY_HARD)
            return GetBadgeLevelCap();
        return MAX_LEVEL;
    }

    static const u32 sLevelCapFlagMap[][2] =
    {
        // R.O.W.E. caps: the cap is the value paired with the first flag that is NOT set.
        // 16 before badge 1, 23/29/36/43/51/57/69/77 after badges 1-8, MAX_LEVEL (100) once Champion.
        {FLAG_BADGE01_GET, 16},
        {FLAG_BADGE02_GET, 23},
        {FLAG_BADGE03_GET, 29},
        {FLAG_BADGE04_GET, 36},
        {FLAG_BADGE05_GET, 43},
        {FLAG_BADGE06_GET, 51},
        {FLAG_BADGE07_GET, 57},
        {FLAG_BADGE08_GET, 69},
        {FLAG_IS_CHAMPION, 77},
    };

    u32 i;

    if (B_LEVEL_CAP_TYPE == LEVEL_CAP_FLAG_LIST)
    {
        for (i = 0; i < ARRAY_COUNT(sLevelCapFlagMap); i++)
        {
            if (!FlagGet(sLevelCapFlagMap[i][0]))
                return sLevelCapFlagMap[i][1];
        }
    }
    else if (B_LEVEL_CAP_TYPE == LEVEL_CAP_VARIABLE)
    {
        return VarGet(B_LEVEL_CAP_VARIABLE);
    }

    return MAX_LEVEL;
}

// Normal difficulty: the player's Pokémon keep gaining EXP and levels past the cap,
// but their stats are calculated as if their level were the cap.
u32 GetStatLevelCap(void)
{
    if (TESTING)
        return MAX_LEVEL;
    if (B_LEVEL_CAP_TYPE == LEVEL_CAP_BADGE_COUNT && GetLevelScalingDifficulty() == DIFFICULTY_NORMAL)
        return GetBadgeLevelCap();
    return MAX_LEVEL;
}

// Rare Candies and EXP Candies (B_RARE_CANDY_CAP) are refused at or above this level,
// and EXP Candies can't raise a Pokémon past it. Easy has no cap.
u32 GetRareCandyLevelCap(void)
{
    if (B_LEVEL_CAP_TYPE == LEVEL_CAP_BADGE_COUNT)
    {
        if (GetLevelScalingDifficulty() == DIFFICULTY_EASY)
            return MAX_LEVEL;
        return GetBadgeLevelCap();
    }
    return GetCurrentLevelCap();
}

STATIC_ASSERT(B_TRAINER_PLAYER == 0, PlayerPartyIsFirstInGParties);

// The stat clamp only applies to the player's Pokémon. Wild, trainer and partner Pokémon are
// always created in the non-player gParties slots; every other Pokémon (the player's party,
// PC withdrawals, gifts, Day Care, box summaries) belongs to the player.
bool32 IsMonAffectedByStatLevelCap(const struct Pokemon *mon)
{
    uintptr_t addr = (uintptr_t)mon;
    uintptr_t otherPartiesStart = (uintptr_t)&gParties[B_TRAINER_PLAYER + 1][0];
    uintptr_t otherPartiesEnd = (uintptr_t)gParties + sizeof(gParties);

    return !(addr >= otherPartiesStart && addr < otherPartiesEnd);
}

void RecalculatePlayerPartyStats(void)
{
    for (u32 i = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_SPECIES) != SPECIES_NONE)
            CalculateMonStats(&gParties[B_TRAINER_PLAYER][i]);
    }
}

// Called by FlagSet: the badge-count cap rises with each badge, at game clear and after
// Rayquaza, so refresh the party's stats (clamped on Normal) when one of those flags is set.
void TryRecalculateStatsForLevelCapFlag(u16 flagId)
{
    if (B_LEVEL_CAP_TYPE != LEVEL_CAP_BADGE_COUNT)
        return;
    if ((flagId >= FLAG_BADGE01_GET && flagId <= FLAG_BADGE08_GET)
     || flagId == FLAG_SYS_GAME_CLEAR
     || flagId == FLAG_DEFEATED_RAYQUAZA)
        RecalculatePlayerPartyStats();
}

u32 GetSoftLevelCapExpValue(u32 level, u32 expValue)
{
    static const u32 sExpScalingDown[5] = { 4, 8, 16, 32, 64 };
    static const u32 sExpScalingUp[5]   = { 16, 8, 4, 2, 1 };

    u32 levelDifference;
    u32 currentLevelCap = GetCurrentLevelCap();

    if (B_EXP_CAP_TYPE == EXP_CAP_NONE)
        return expValue;

    if (level < currentLevelCap)
    {
        if (B_LEVEL_CAP_EXP_UP)
        {
            levelDifference = currentLevelCap - level;
            if (levelDifference > ARRAY_COUNT(sExpScalingUp) - 1)
                return expValue + (expValue / sExpScalingUp[ARRAY_COUNT(sExpScalingUp) - 1]);
            else
                return expValue + (expValue / sExpScalingUp[levelDifference]);
        }
        else
        {
            return expValue;
        }
    }
    else if (B_EXP_CAP_TYPE == EXP_CAP_HARD)
    {
        return 0;
    }
    else if (B_EXP_CAP_TYPE == EXP_CAP_SOFT)
    {
        levelDifference = level - currentLevelCap;
        if (levelDifference > ARRAY_COUNT(sExpScalingDown) - 1)
            return expValue / sExpScalingDown[ARRAY_COUNT(sExpScalingDown) - 1];
        else
            return expValue / sExpScalingDown[levelDifference];
    }
    else
    {
       return expValue;
    }
}

u32 GetCurrentEVCap(void)
{
    static const u16 sEvCapFlagMap[][2] = {
        // Define EV caps for each milestone
        {FLAG_BADGE01_GET, MAX_TOTAL_EVS *  1 / 17},
        {FLAG_BADGE02_GET, MAX_TOTAL_EVS *  3 / 17},
        {FLAG_BADGE03_GET, MAX_TOTAL_EVS *  5 / 17},
        {FLAG_BADGE04_GET, MAX_TOTAL_EVS *  7 / 17},
        {FLAG_BADGE05_GET, MAX_TOTAL_EVS *  9 / 17},
        {FLAG_BADGE06_GET, MAX_TOTAL_EVS * 11 / 17},
        {FLAG_BADGE07_GET, MAX_TOTAL_EVS * 13 / 17},
        {FLAG_BADGE08_GET, MAX_TOTAL_EVS * 15 / 17},
        {FLAG_IS_CHAMPION, MAX_TOTAL_EVS},
    };

    if (B_EV_CAP_TYPE == EV_CAP_FLAG_LIST)
    {
        for (u32 evCap = 0; evCap < ARRAY_COUNT(sEvCapFlagMap); evCap++)
        {
            if (!FlagGet(sEvCapFlagMap[evCap][0]))
                return sEvCapFlagMap[evCap][1];
        }
    }
    else if (B_EV_CAP_TYPE == EV_CAP_VARIABLE)
    {
        return VarGet(B_EV_CAP_VARIABLE);
    }
    else if (B_EV_CAP_TYPE == EV_CAP_NO_GAIN)
    {
        return 0;
    }

    return MAX_TOTAL_EVS;
}
