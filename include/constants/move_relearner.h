#ifndef GUARD_CONSTANTS_MOVE_RELEARNER_H
#define GUARD_CONSTANTS_MOVE_RELEARNER_H

// Max number of moves shown by the move relearner.
// Increased from 25 to 60 so Mew can display all TMs/HMs.
// If you plan on adding more TMs, increase this number too.
#define MAX_RELEARNER_MOVES 60

// Price in money (not coins) the Pokemon Center Move Nurse charges for each
// Egg move a Pokemon actually learns. Recall and Tutor moves are free.
#define MOVE_NURSE_EGG_MOVE_PRICE 500

// Results of the MoveNurse_GetTutorAvailability special.
#define MOVE_NURSE_TUTOR_AVAILABLE      0
#define MOVE_NURSE_TUTOR_NO_BADGES      1 // no Hoenn badges yet
#define MOVE_NURSE_TUTOR_NEED_MORE      2 // has badges, but no tutor move unlocked yet

// Move Relearner menu change constants
enum MoveRelearnerStates
{
    MOVE_RELEARNER_LEVEL_UP_MOVES,
    MOVE_RELEARNER_EGG_MOVES,
    MOVE_RELEARNER_TM_MOVES,
    MOVE_RELEARNER_TUTOR_MOVES,
    // Pokemon Center Move Nurse only: tutor moves gated by Hoenn badge count
    // (src/data/tutor_move_badges.h). Never offered by the summary screen's
    // relearner cycling.
    MOVE_RELEARNER_BADGE_TUTOR_MOVES,
    MOVE_RELEARNER_COUNT,
};

enum RelearnMode
{
    RELEARN_MODE_NONE = 0,
    RELEARN_MODE_SCRIPT = 1,                     // Relearning moves through an event script
    // These two must stay 2 and 3, they are tied to the summary screen pages
    RELEARN_MODE_PSS_PAGE_BATTLE_MOVES = 2,      // Relearning moves through the summary screen's battle moves page
    RELEARN_MODE_PSS_PAGE_CONTEST_MOVES = 3,     // Relearning moves through the summary screen's contest moves page (defaults to contest page on relearner screen)
};

#endif // GUARD_CONSTANTS_MOVE_RELEARNER_H
