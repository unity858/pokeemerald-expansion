#ifndef GUARD_CONSTANTS_TMS_HMS_H
#define GUARD_CONSTANTS_TMS_HMS_H

// TMs that teach a move an HM also teaches use an alias token, since each
// FOREACH_TM/FOREACH_HM token must be unique (it names ITEM_TM_*/ITEM_HM_* and
// the TM/HM index). MOVE_<token> must resolve to the real move.
#define MOVE_FLY_TM         MOVE_FLY
#define MOVE_SURF_TM        MOVE_SURF
#define MOVE_WATERFALL_TM   MOVE_WATERFALL

#define FOREACH_TM(F) \
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
    F(FLY_TM) \
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
    F(SURF_TM) \
    F(SNARL) \
    F(NATURE_POWER) \
    F(DARK_PULSE) \
    F(WATERFALL_TM) \
    F(DAZZLING_GLEAM) \
    F(CONFIDE)

#define FOREACH_HM(F) \
    F(CUT) \
    F(FLY) \
    F(SURF) \
    F(STRENGTH) \
    F(FLASH) \
    F(ROCK_SMASH) \
    F(WATERFALL) \
    F(DIVE)

#define FOREACH_TMHM(F) \
    FOREACH_TM(F) \
    FOREACH_HM(F)

#endif
