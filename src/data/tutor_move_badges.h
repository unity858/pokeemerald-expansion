#ifndef GUARD_DATA_TUTOR_MOVE_BADGES_H
#define GUARD_DATA_TUTOR_MOVE_BADGES_H

// ============================================================================
// Pokemon Center Move Nurse: Tutor move unlocks by Hoenn badge count
// ============================================================================
//
// The Move Nurse (left of the healing machine in every Pokemon Center,
// data/scripts/move_nurse.inc) teaches Tutor moves for free. Each Tutor move
// unlocks once the player owns at least this many Hoenn Gym Badges
// (FLAG_BADGE01_GET .. FLAG_BADGE08_GET, counted, so gym order doesn't matter).
//
// HOW TO EDIT
//   * Change the number after a move to 1-8 to move it into that badge group.
//       1 = after the first gym ... 8 = after the eighth gym.
//   * With 8 badges every Tutor move is unlocked, whatever its value here.
//   * A Tutor move missing from this table (or set to 0) uses
//     TUTOR_MOVE_DEFAULT_BADGES below.
//   * Listing a move here does NOT make it a Tutor move. The moves on offer
//     come from GetTutorMoves() in src/pokemon.c (gTutorMoves in Vanilla data
//     mode, gCustomTutorMoves in Custom data mode), and a Pokemon only sees
//     the ones in its own teachable learnset. The comment on each line says
//     which mode's list contains the move.
//   * With 0 badges, or when no Tutor move is unlocked yet, the nurse says
//     Tutor moves aren't available yet.
//
// For now every Tutor move is in group 1 (unlocked after the first gym).
// ============================================================================

#define TUTOR_MOVE_DEFAULT_BADGES 1

static const u8 sTutorMoveBadgeRequirements[MOVES_COUNT] =
{
    [MOVE_BLAST_BURN]        = 1, // Custom only
    [MOVE_BODY_PRESS]        = 1, // Custom only
    [MOVE_BODY_SLAM]         = 1, // both
    [MOVE_BREAKING_SWIPE]    = 1, // Custom only
    [MOVE_CLOSE_COMBAT]      = 1, // Custom only
    [MOVE_COUNTER]           = 1, // both
    [MOVE_CUT]               = 1, // Custom only
    [MOVE_DEFENSE_CURL]      = 1, // both
    [MOVE_DEFOG]             = 1, // Custom only
    [MOVE_DOUBLE_EDGE]       = 1, // both
    [MOVE_DRACO_METEOR]      = 1, // Custom only
    [MOVE_DRAGON_PULSE]      = 1, // Custom only
    [MOVE_DREAM_EATER]       = 1, // both
    [MOVE_DRILL_RUN]         = 1, // Custom only
    [MOVE_DUAL_WINGBEAT]     = 1, // Custom only
    [MOVE_DYNAMIC_PUNCH]     = 1, // both
    [MOVE_ENDURE]            = 1, // both
    [MOVE_EXPLOSION]         = 1, // both
    [MOVE_FIRE_FANG]         = 1, // Custom only
    [MOVE_FIRE_PUNCH]        = 1, // both
    [MOVE_FLASH]             = 1, // Custom only
    [MOVE_FLIP_TURN]         = 1, // Custom only
    [MOVE_FOUL_PLAY]         = 1, // Custom only
    [MOVE_FRENZY_PLANT]      = 1, // Custom only
    [MOVE_FURY_CUTTER]       = 1, // both
    [MOVE_GRASSY_GLIDE]      = 1, // Custom only
    [MOVE_HEAL_BELL]         = 1, // Custom only
    [MOVE_HEAT_WAVE]         = 1, // Custom only
    [MOVE_HIGH_HORSEPOWER]   = 1, // Custom only
    [MOVE_HYDRO_CANNON]      = 1, // Custom only
    [MOVE_HYPER_VOICE]       = 1, // Custom only
    [MOVE_ICE_FANG]          = 1, // Custom only
    [MOVE_ICE_PUNCH]         = 1, // both
    [MOVE_ICY_WIND]          = 1, // both
    [MOVE_KNOCK_OFF]         = 1, // Custom only
    [MOVE_MEGA_KICK]         = 1, // both
    [MOVE_MEGA_PUNCH]        = 1, // both
    [MOVE_METRONOME]         = 1, // both
    [MOVE_MIMIC]             = 1, // both
    [MOVE_MUD_SLAP]          = 1, // both
    [MOVE_OUTRAGE]           = 1, // Custom only
    [MOVE_PAIN_SPLIT]        = 1, // Custom only
    [MOVE_PSYCH_UP]          = 1, // both
    [MOVE_RECYCLE]           = 1, // Custom only
    [MOVE_ROCK_SLIDE]        = 1, // both
    [MOVE_ROCK_SMASH]        = 1, // Custom only
    [MOVE_ROLLOUT]           = 1, // both
    [MOVE_SCORCHING_SANDS]   = 1, // Custom only
    [MOVE_SEED_BOMB]         = 1, // Custom only
    [MOVE_SEISMIC_TOSS]      = 1, // both
    [MOVE_SIGNAL_BEAM]       = 1, // Custom only
    [MOVE_SLEEP_TALK]        = 1, // both
    [MOVE_SNORE]             = 1, // both
    [MOVE_SOFT_BOILED]       = 1, // both
    [MOVE_STEEL_BEAM]        = 1, // Custom only
    [MOVE_STOMPING_TANTRUM]  = 1, // Custom only
    [MOVE_STRENGTH]          = 1, // Custom only
    [MOVE_SUBSTITUTE]        = 1, // both
    [MOVE_SUPERPOWER]        = 1, // Custom only
    [MOVE_SWAGGER]           = 1, // both
    [MOVE_SWIFT]             = 1, // both
    [MOVE_SWORDS_DANCE]      = 1, // both
    [MOVE_TAILWIND]          = 1, // Custom only
    [MOVE_THUNDER_FANG]      = 1, // Custom only
    [MOVE_THUNDER_PUNCH]     = 1, // both
    [MOVE_THUNDER_WAVE]      = 1, // both
    [MOVE_TRIPLE_AXEL]       = 1, // Custom only
    [MOVE_VOLT_TACKLE]       = 1, // Custom only
    [MOVE_WHIRLPOOL]         = 1, // Custom only
};

#endif // GUARD_DATA_TUTOR_MOVE_BADGES_H
