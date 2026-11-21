#ifndef GUARD_LEVEL_SCALING_H
#define GUARD_LEVEL_SCALING_H

#include "constants/difficulty.h"

// R.O.W.E. badge-based level scaling.
//
// The scaling stage ("badge count") goes from 0 to LEVEL_SCALING_STAGE_MAX:
//   0-8 : number of gym badges owned (counted, so gyms may be reordered)
//   9   : game cleared (FLAG_SYS_GAME_CLEAR)
//   10  : post-game, Rayquaza caught or defeated at Sky Pillar (FLAG_DEFEATED_RAYQUAZA)
#define LEVEL_SCALING_STAGE_GAME_CLEAR  9
#define LEVEL_SCALING_STAGE_RAYQUAZA    10
#define LEVEL_SCALING_STAGE_MAX         LEVEL_SCALING_STAGE_RAYQUAZA
#define LEVEL_SCALING_STAGE_COUNT       (LEVEL_SCALING_STAGE_MAX + 1)

u32 GetLevelScalingBadgeCount(void);
enum DifficultyLevel GetLevelScalingDifficulty(void);
u32 RollLevelScalingBoost(void);

u32 GetLevelScalingWildMinLevel(void);
u32 GetLevelScalingTrainerMinLevel(void);
u32 GetLevelScalingBossMinLevel(void);
u32 ClampScaledLevel(s32 level);

bool32 ShouldScaleWildMonLevels(void);
u32 GetScaledWildMonLevel(void);
u32 GetScaledDexNavMonLevel(u32 chain);

#endif // GUARD_LEVEL_SCALING_H
