// Move flag overrides for Custom data mode (ported from R.O.W.E.).
//
// Applied only when IsCustomDataMode() is TRUE, by these accessors in
// include/move.h:
//   .criticalHitStage -> GetMoveCriticalHitStage   (CUSTOM_CRIT_STAGE(n))
//   .punchingMove     -> IsPunchingMove            (R.O.W.E. FLAG_IRON_FIST_BOOST)
//   .pulseMove        -> IsPulseMove               (R.O.W.E. FLAG_MEGA_LAUNCHER_BOOST)
//   .soundMove        -> IsSoundMove               (R.O.W.E. FLAG_SOUND)
//   .powderMove       -> IsPowderMove              (R.O.W.E. FLAG_POWDER)
//   .windMove         -> IsWindMove                (R.O.W.E. FLAG_WIND_BASED)
//   .damagesAirborne  -> MoveDamagesAirborne       (R.O.W.E. FLAG_HIT_IN_AIR)
//   .slicingMove      -> IsSlicingMove             (R.O.W.E. FLAG_BLADEMASTER_BOOST)
//   .strikerBoost     -> IsStrikerBoostedMove      (R.O.W.E. FLAG_STRIKER_BOOST)
//   .sleepTalkBanned  -> IsMoveSleepTalkBanned
//   .instructBanned   -> IsMoveInstructBanned
//   .assistBanned     -> IsMoveAssistBanned
// Boolean properties: CUSTOM_FLAG_SET forces TRUE, CUSTOM_FLAG_CLEAR forces
// FALSE, leaving the field out keeps vanilla.
//
// Only R.O.W.E.'s own changes (R.O.W.E. vs its upstream base, expansion
// b7b1b26) are listed, and only where they differ from current vanilla data.
// R.O.W.E. changes that already match vanilla, so need no entry:
//   high crit:  Sky Attack, Snipe Shot
//   wind:       Gust, Whirlwind, Blizzard, Icy Wind, Sandstorm, Twister,
//               Heat Wave, Air Cutter, Silver Wind, Tailwind, Ominous Wind,
//               Hurricane, Petal Blizzard, Fairy Wind
//   sound:      Round
//   protection: Obstruct (vanilla EFFECT_PROTECT already)
// Not ported:
//   FLAG_SHEER_FORCE_BOOST changes (Volt Tackle, Razor Shell, Floaty Fall,
//   Secret Power): expansion derives Sheer Force from additional effects.
//   Moves kept fully vanilla per user (Secret Power's and Beak Blast's flag
//   changes).
//
// Slicing: R.O.W.E. called Sharpness "Blademaster" and gave it its own move
// list. In Custom mode Sharpness boosts the union of the vanilla slicing moves
// and that list, so only the R.O.W.E. moves that aren't vanilla slicing moves
// are set here (Cut, Slash, Fury Cutter, Leaf Blade, Night Slash, X-Scissor,
// Psycho Cut, Cross Poison, Sacred Sword, Razor Shell, Secret Sword and Solar
// Blade already are).
// Striker: R.O.W.E.-only property, read by ABILITY_STRIKER (1.3x power) in
// src/battle_util.c.

const struct MoveFlagOverride gCustomMoveFlags[MOVES_COUNT] =
{
    [MOVE_STOMP] = { .strikerBoost = TRUE }, // Striker
    [MOVE_DOUBLE_KICK] = { .strikerBoost = TRUE }, // Striker
    [MOVE_MEGA_KICK] = { .strikerBoost = TRUE }, // Striker
    [MOVE_JUMP_KICK] = { .strikerBoost = TRUE }, // Striker
    [MOVE_ROLLING_KICK] = { .strikerBoost = TRUE }, // Striker
    [MOVE_CUT] = { .criticalHitStage = CUSTOM_CRIT_STAGE(1) }, // High crit
    [MOVE_FLAMETHROWER] = { .pulseMove = CUSTOM_FLAG_SET }, // Pulse (Mega Launcher)
    [MOVE_HYDRO_PUMP] = { .pulseMove = CUSTOM_FLAG_SET }, // Pulse (Mega Launcher)
    [MOVE_DRILL_PECK] = { .criticalHitStage = CUSTOM_CRIT_STAGE(1) }, // High crit
    [MOVE_SLEEP_POWDER] = { .powderMove = CUSTOM_FLAG_CLEAR }, // Not a powder move
    [MOVE_BONE_CLUB] = { .damagesAirborne = CUSTOM_FLAG_SET }, // Hits airborne (Fly/Bounce) targets
    [MOVE_HIGH_JUMP_KICK] = { .strikerBoost = TRUE }, // Striker
    [MOVE_BONEMERANG] = { .damagesAirborne = CUSTOM_FLAG_SET }, // Hits airborne (Fly/Bounce) targets
    [MOVE_TRIPLE_KICK] = { .strikerBoost = TRUE }, // Striker
    [MOVE_OCTAZOOKA] = { .pulseMove = CUSTOM_FLAG_SET }, // Pulse (Mega Launcher)
    [MOVE_ZAP_CANNON] = { .pulseMove = CUSTOM_FLAG_SET }, // Pulse (Mega Launcher)
    [MOVE_BONE_RUSH] = { .damagesAirborne = CUSTOM_FLAG_SET }, // Hits airborne (Fly/Bounce) targets
    [MOVE_FALSE_SWIPE] = { .slicingMove = CUSTOM_FLAG_SET }, // Slicing (Sharpness)
    [MOVE_SUPERPOWER] = { .punchingMove = CUSTOM_FLAG_SET }, // Punching (Iron Fist)
    // Dive is a one-turn hit in Custom mode (custom_move_effects.h), so drop the
    // bans it had only for being a two-turn semi-invulnerable move. Its Sky
    // Battle ban is kept: that list bans water/ground moves (e.g. Surf, Muddy Water).
    [MOVE_DIVE] = { .sleepTalkBanned = CUSTOM_FLAG_CLEAR, .instructBanned = CUSTOM_FLAG_CLEAR, .assistBanned = CUSTOM_FLAG_CLEAR }, // Callable by Sleep Talk, Instruct, Assist
    [MOVE_BLAZE_KICK] = { .strikerBoost = TRUE }, // Striker
    [MOVE_DRAGON_CLAW] = { .criticalHitStage = CUSTOM_CRIT_STAGE(1) }, // High crit
    [MOVE_CLOSE_COMBAT] = { .punchingMove = CUSTOM_FLAG_SET }, // Punching (Iron Fist)
    [MOVE_SUCKER_PUNCH] = { .punchingMove = CUSTOM_FLAG_SET }, // Punching (Iron Fist)
    [MOVE_X_SCISSOR] = { .criticalHitStage = CUSTOM_CRIT_STAGE(1) }, // High crit
    [MOVE_FOCUS_BLAST] = { .pulseMove = CUSTOM_FLAG_SET }, // Pulse (Mega Launcher)
    [MOVE_SHADOW_CLAW] = { .slicingMove = CUSTOM_FLAG_SET }, // Slicing (Sharpness)
    [MOVE_FLASH_CANNON] = { .pulseMove = CUSTOM_FLAG_SET }, // Pulse (Mega Launcher)
    [MOVE_DUAL_CHOP] = { .slicingMove = CUSTOM_FLAG_SET }, // Slicing (Sharpness)
    [MOVE_SACRED_SWORD] = { .criticalHitStage = CUSTOM_CRIT_STAGE(1) }, // High crit
    [MOVE_RAZOR_SHELL] = { .criticalHitStage = CUSTOM_CRIT_STAGE(1) }, // High crit (stats/effect stay vanilla)
    [MOVE_SECRET_SWORD] = { .criticalHitStage = CUSTOM_CRIT_STAGE(1) }, // High crit
    [MOVE_HIGH_HORSEPOWER] = { .strikerBoost = TRUE }, // Striker
    [MOVE_TROP_KICK] = { .strikerBoost = TRUE }, // Striker
    [MOVE_DYNAMAX_CANNON] = { .pulseMove = CUSTOM_FLAG_SET }, // Pulse (Mega Launcher)
    [MOVE_SNIPE_SHOT] = { .pulseMove = CUSTOM_FLAG_SET }, // Pulse (Mega Launcher); high crit already vanilla
    [MOVE_PYRO_BALL] = { .strikerBoost = TRUE }, // Striker
    [MOVE_TRIPLE_AXEL] = { .strikerBoost = TRUE }, // Striker
    [MOVE_THUNDEROUS_KICK] = { .strikerBoost = TRUE }, // Striker
};
