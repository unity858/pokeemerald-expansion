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

// New Game Plus choice made on the main menu (NEW GAME+ vs NEW GAME). NewGameInitData
// reads it before resetting the save; NewGameOptions_ApplyToSave clears it.
void NewGameOptions_SetNewGamePlusPending(bool32 pending);
bool32 NewGameOptions_IsNewGamePlusPending(void);

// Accessors for the rest of the game.
// Difficulty: use GetCurrentDifficultyLevel() from difficulty.h.
bool32 IsCustomDataMode(void);
enum NewGameDataMode GetDataMode(void);
// R.O.W.E. Perfect IV Mode: every Pokemon's IVs read as 31 (see GetBoxMonData3).
bool32 IsPerfectIvMode(void);

#endif // GUARD_NEW_GAME_OPTIONS_H
