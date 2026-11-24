#ifndef GUARD_NEW_GAME_OPTIONS_H
#define GUARD_NEW_GAME_OPTIONS_H

// "Game options" screen shown between NEW GAME on the main menu and
// Professor Birch's intro speech. The choices are fixed for the playthrough.

enum NewGameDataMode
{
    DATA_MODE_VANILLA,
    DATA_MODE_CUSTOM,
    DATA_MODE_COUNT,
};

void CB2_InitNewGameOptions(void);

// Writes the pending choices into the save (B_VAR_DIFFICULTY,
// FLAG_CUSTOM_DATA_MODE and FLAG_PERFECT_IV_MODE). Must be called after NewGameInitData, which
// clears all flags and vars.
void NewGameOptions_ApplyToSave(void);

// Accessors for the rest of the game.
// Difficulty: use GetCurrentDifficultyLevel() from difficulty.h.
bool32 IsCustomDataMode(void);
enum NewGameDataMode GetDataMode(void);
// R.O.W.E. Perfect IV Mode: every Pokemon's IVs read as 31 (see GetBoxMonData3).
bool32 IsPerfectIvMode(void);

#endif // GUARD_NEW_GAME_OPTIONS_H
