#include "global.h"
#include "battle.h"
#include "data.h"
#include "battle_pike.h"
#include "battle_pyramid.h"
#include "difficulty.h"
#include "event_data.h"
#include "level_scaling.h"
#include "random.h"
#include "constants/battle_pyramid.h"
#include "constants/flags.h"
#include "constants/opponents.h"
#include "constants/trainers.h"

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

// Wild mons in the Battle Pike and Battle Pyramid keep the Frontier's own levels.
bool32 ShouldScaleWildMonLevels(void)
{
    if (TESTING)
        return FALSE;
    if (InBattlePike() || CurrentBattlePyramidLocation() != PYRAMID_LOCATION_NONE)
        return FALSE;
    return TRUE;
}

// Rolled per encounter, ignoring the encounter table's min/max levels.
u32 GetScaledWildMonLevel(void)
{
    return ClampScaledLevel(GetLevelScalingWildMinLevel() + RollLevelScalingBoost());
}

// R.O.W.E. DexNav: the scaled wild level plus chain / 5, with a 2% chance of +10,
// never above the current boss minimum level.
u32 GetScaledDexNavMonLevel(u32 chain)
{
    u32 level = GetScaledWildMonLevel() + chain / 5;
    u32 maxLevel = GetLevelScalingBossMinLevel();

    if (Random() % 100 < 2)
        level += 10;
    if (level > maxLevel)
        level = maxLevel;
    return ClampScaledLevel(level);
}

// Trainer battles that keep the levels from their party data.
#define LEVEL_SCALING_EXCLUDED_BATTLE_TYPES (BATTLE_TYPE_LINK                 \
                                           | BATTLE_TYPE_RECORDED           \
                                           | BATTLE_TYPE_RECORDED_LINK      \
                                           | BATTLE_TYPE_TOWER_LINK_MULTI   \
                                           | BATTLE_TYPE_FRONTIER           \
                                           | BATTLE_TYPE_TRAINER_HILL       \
                                           | BATTLE_TYPE_SECRET_BASE        \
                                           | BATTLE_TYPE_EREADER_TRAINER    \
                                           | BATTLE_TYPE_CATCH_TUTORIAL)

// Bosses: Gym Leaders, Elite Four, Champion and Wally.
bool32 IsLevelScalingBoss(u16 trainerId, const struct Trainer *trainer)
{
    switch (trainer->trainerClass)
    {
    case TRAINER_CLASS_LEADER:
    case TRAINER_CLASS_ELITE_FOUR:
    case TRAINER_CLASS_CHAMPION:
        return TRUE;
    default:
        break;
    }

    // Wally shares TRAINER_CLASS_RIVAL with May, Brendan and Steven, so match his trainer IDs.
    switch (trainerId)
    {
    case TRAINER_WALLY_MAUVILLE:
    case TRAINER_WALLY_VR_1:
    case TRAINER_WALLY_VR_2:
    case TRAINER_WALLY_VR_3:
    case TRAINER_WALLY_VR_4:
    case TRAINER_WALLY_VR_5:
        return TRUE;
    default:
        return FALSE;
    }
}

// Returns the scaled level of party slot 0, or 0 if this party keeps its data levels.
// Call once per trainer per battle: the regular trainers' random boost is rolled here.
u32 GetScaledTrainerPartyBaseLevel(u16 trainerId, const struct Trainer *trainer, bool32 isPartner)
{
    if (TESTING)
        return 0;
    if (gBattleTypeFlags & LEVEL_SCALING_EXCLUDED_BATTLE_TYPES)
        return 0;

    if (!isPartner)
    {
        // TRAINER_SECRET_BASE, TRAINER_LINK_OPPONENT, TRAINER_UNION_ROOM, ...
        if (trainerId == TRAINER_NONE || trainerId >= TRAINER_SECRET_BASE)
            return 0;
        // Bosses get no random boost, so their ace (last slot) is always the highest.
        if (IsLevelScalingBoss(trainerId, trainer))
            return GetLevelScalingBossMinLevel();
    }

    // Regular trainers and in-game partners (e.g. Steven in the Mossdeep tag battle).
    return ClampScaledLevel(GetLevelScalingTrainerMinLevel() + RollLevelScalingBoost());
}

u32 GetScaledTrainerMonLevel(u32 baseLevel, u32 partySlot)
{
    return ClampScaledLevel(baseLevel + partySlot);
}
