#ifndef GUARD_CONSTANTS_TMS_HMS_H
#define GUARD_CONSTANTS_TMS_HMS_H

// A TM's number is its position in FOREACH_TM, except that TM121-TM128 are
// intentionally unused: TMs in FOREACH_TM_AFTER_GAP are numbered from TM129.
// The gap has no items or list entries, so it costs no bag slots.
#define TM_GAP_FIRST 121 // First unused TM number
#define TM_GAP_SIZE    8 // TM121-TM128

// TM01-TM120
#define FOREACH_TM_BEFORE_GAP(F) \
    F(FOCUS_PUNCH) \
    F(DRAGON_CLAW) \
    F(WATER_PULSE) \
    F(CALM_MIND) \
    F(ROAR) \
    F(TOXIC) \
    F(HAIL) \
    F(BULK_UP) \
    F(BULLET_SEED) \
    F(HIDDEN_POWER) \
    F(SUNNY_DAY) \
    F(TAUNT) \
    F(ICE_BEAM) \
    F(BLIZZARD) \
    F(HYPER_BEAM) \
    F(LIGHT_SCREEN) \
    F(PROTECT) \
    F(RAIN_DANCE) \
    F(GIGA_DRAIN) \
    F(SAFEGUARD) \
    F(FRUSTRATION) \
    F(SOLAR_BEAM) \
    F(IRON_TAIL) \
    F(THUNDERBOLT) \
    F(THUNDER) \
    F(EARTHQUAKE) \
    F(RETURN) \
    F(DIG) \
    F(PSYCHIC) \
    F(SHADOW_BALL) \
    F(BRICK_BREAK) \
    F(DOUBLE_TEAM) \
    F(REFLECT) \
    F(SHOCK_WAVE) \
    F(FLAMETHROWER) \
    F(SLUDGE_BOMB) \
    F(SANDSTORM) \
    F(FIRE_BLAST) \
    F(ROCK_TOMB) \
    F(AERIAL_ACE) \
    F(TORMENT) \
    F(FACADE) \
    F(SECRET_POWER) \
    F(REST) \
    F(ATTRACT) \
    F(THIEF) \
    F(STEEL_WING) \
    F(SKILL_SWAP) \
    F(SNATCH) \
    F(OVERHEAT) \
    F(LOW_SWEEP) \
    F(FOCUS_BLAST) \
    F(ENERGY_BALL) \
    F(FALSE_SWIPE) \
    F(SCALD) \
    F(DARKEST_LARIAT) \
    F(CHARGE_BEAM) \
    F(ROOST) \
    F(BRUTAL_SWING) \
    F(QUASH) \
    F(WILL_O_WISP) \
    F(ACROBATICS) \
    F(EMBARGO) \
    F(EXPLOSION) \
    F(SHADOW_CLAW) \
    F(PAYBACK) \
    F(SMART_STRIKE) \
    F(GIGA_IMPACT) \
    F(ROCK_POLISH) \
    F(AURORA_VEIL) \
    F(STONE_EDGE) \
    F(VOLT_SWITCH) \
    F(THUNDER_WAVE) \
    F(GYRO_BALL) \
    F(SWORDS_DANCE) \
    F(FLY) \
    F(PSYCH_UP) \
    F(BULLDOZE) \
    F(FROST_BREATH) \
    F(ROCK_SLIDE) \
    F(X_SCISSOR) \
    F(DRAGON_TAIL) \
    F(INFESTATION) \
    F(POISON_JAB) \
    F(DREAM_EATER) \
    F(GRASS_KNOT) \
    F(SWAGGER) \
    F(SLEEP_TALK) \
    F(U_TURN) \
    F(SUBSTITUTE) \
    F(FLASH_CANNON) \
    F(TRICK_ROOM) \
    F(WILD_CHARGE) \
    F(SURF) \
    F(SNARL) \
    F(NATURE_POWER) \
    F(DARK_PULSE) \
    F(WATERFALL) \
    F(DAZZLING_GLEAM) \
    F(CONFIDE) \
    F(SLUDGE_WAVE) \
    F(LIQUIDATION) \
    F(LEECH_LIFE) \
    F(PLAY_ROUGH) \
    F(PSYSHOCK) \
    F(AURA_SPHERE) \
    F(POWER_GEM) \
    F(EARTH_POWER) \
    F(GUNK_SHOT) \
    F(STEALTH_ROCK) \
    F(HEAT_CRASH) \
    F(POLLEN_PUFF) \
    F(NASTY_PLOT) \
    F(BRAVE_BIRD) \
    F(BUG_BUZZ) \
    F(DRAGON_DANCE) \
    F(BLAZE_KICK) \
    F(TRI_ATTACK) \
    F(DRAIN_PUNCH) \
    F(MYSTICAL_FIRE)

// TM129 onward
#define FOREACH_TM_AFTER_GAP(F) \
    F(TERA_BLAST)

#define FOREACH_TM(F) \
    FOREACH_TM_BEFORE_GAP(F) \
    FOREACH_TM_AFTER_GAP(F)

// HMs are removed; field moves are usable based on learnsets (see field_move.c).
#define FOREACH_HM(F)

#define FOREACH_TMHM(F) \
    FOREACH_TM(F) \
    FOREACH_HM(F)

#endif
