#include "global.h"
#include "difficulty.h"
#include "event_data.h"
#include "level_scaling.h"
#include "random.h"
#include "constants/flags.h"

// R.O.W.E. level scaling tables, indexed by [difficulty][badge count 0-10].
// Ported from R.O.W.E. src/level_scaling.c.
static const u8 sWildMinLevel[DIFFICULTY_HARD + 1][LEVEL_SCALING_STAGE_COUNT] =
{
    [DIFFICULTY_EASY]   = {4, 10, 15, 20, 25, 30, 35, 40, 45, 55, 60},
    [DIFFICULTY_NORMAL] = {5, 10, 15, 20, 25, 31, 37, 43, 50, 60, 65},
    [DIFFICULTY_HARD]   = {5, 11, 16, 21, 26, 32, 38, 45, 52, 62, 68},
};

static const u8 sTrainerMinLevel[DIFFICULTY_HARD + 1][LEVEL_SCALING_STAGE_COUNT] =
{
    [DIFFICULTY_EASY]   = {6, 10, 15, 20, 25, 30, 35, 40, 45, 55, 60},
    [DIFFICULTY_NORMAL] = {7, 12, 18, 24, 30, 36, 42, 48, 55, 65, 70},
    [DIFFICULTY_HARD]   = {7, 13, 19, 25, 32, 38, 44, 50, 57, 67, 73},
};

static const u8 sBossMinLevel[DIFFICULTY_HARD + 1][LEVEL_SCALING_STAGE_COUNT] =
{
    [DIFFICULTY_EASY]   = {12, 17, 22, 27, 32, 37, 42, 50, 55, 65, 70},
    [DIFFICULTY_NORMAL] = {13, 19, 25, 31, 37, 43, 49, 60, 68, 76, 82},
    [DIFFICULTY_HARD]   = {13, 19, 25, 31, 38, 45, 51, 62, 70, 77, 85},
};

u32 GetLevelScalingBadgeCount(void)
{
    u32 badges = 0;

    if (FlagGet(FLAG_SYS_GAME_CLEAR))
    {
        // Sky Pillar sets FLAG_DEFEATED_RAYQUAZA when Rayquaza is caught or knocked out.
        if (FlagGet(FLAG_DEFEATED_RAYQUAZA))
            return LEVEL_SCALING_STAGE_RAYQUAZA;
        return LEVEL_SCALING_STAGE_GAME_CLEAR;
    }

    // Count the badges owned rather than taking the highest one, so the gyms can be reordered.
    for (u32 flag = FLAG_BADGE01_GET; flag <= FLAG_BADGE08_GET; flag++)
    {
        if (FlagGet(flag))
            badges++;
    }
    return badges;
}

enum DifficultyLevel GetLevelScalingDifficulty(void)
{
    enum DifficultyLevel difficulty = GetCurrentDifficultyLevel();

    // Anything out of range (e.g. DIFFICULTY_TEST or a corrupt var) scales like Normal.
    if (difficulty > DIFFICULTY_HARD)
        return DIFFICULTY_NORMAL;
    return difficulty;
}

// R.O.W.E.'s getLevelBoost, without its division by zero at 0 badges.
// Easy, or Normal before game clear: U(0..b+1)
// Hard, or Normal after game clear:  U(0..b+1) + U(0..b-1)
u32 RollLevelScalingBoost(void)
{
    u32 badges = GetLevelScalingBadgeCount();
    enum DifficultyLevel difficulty = GetLevelScalingDifficulty();
    u32 boost = Random() % (badges + 2);

    if (difficulty == DIFFICULTY_HARD || (difficulty == DIFFICULTY_NORMAL && FlagGet(FLAG_SYS_GAME_CLEAR)))
    {
        if (badges != 0)
            boost += Random() % badges;
    }
    return boost;
}

u32 GetLevelScalingWildMinLevel(void)
{
    return sWildMinLevel[GetLevelScalingDifficulty()][GetLevelScalingBadgeCount()];
}

u32 GetLevelScalingTrainerMinLevel(void)
{
    return sTrainerMinLevel[GetLevelScalingDifficulty()][GetLevelScalingBadgeCount()];
}

u32 GetLevelScalingBossMinLevel(void)
{
    return sBossMinLevel[GetLevelScalingDifficulty()][GetLevelScalingBadgeCount()];
}

u32 ClampScaledLevel(s32 level)
{
    if (level < 1)
        return 1;
    if (level > MAX_LEVEL)
        return MAX_LEVEL;
    return level;
}
