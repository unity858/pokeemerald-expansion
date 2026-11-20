// Move stat overrides for Custom data mode (ported from R.O.W.E.).
//
// Applied by GetMovePower/GetMoveType/GetMoveAccuracy/GetMovePP in include/move.h
// only when IsCustomDataMode() is TRUE. Vanilla mode always uses gMovesInfo.
//
// One entry per move; leave a field out (or 0) to keep the vanilla value.
// Use CUSTOM_ACCURACY_NEVER_MISSES for a move that can't miss (accuracy 0 in gMovesInfo).
// Comments show vanilla (current gMovesInfo) -> custom; "--" means never misses.
//
// Power, type, accuracy, PP, target and category are overridden here
// (target -> GetMoveTarget, category -> GetMoveCategory). Effects and
// additional effects are overridden in custom_move_effects.h, move flags in
// custom_move_flags.h. Priority is unchanged from vanilla.
// Target/category: write the TARGET_* / DAMAGE_CATEGORY_* constant directly;
// 0 (TARGET_NONE / DAMAGE_CATEGORY_NONE) means "no override".
//
// Present: R.O.W.E. gave it power 90 together with a different effect
// (EFFECT_HIT_ENEMY_HEAL_ALLY, "damage foes, heal allies" like Pollen Puff).
// That effect is now applied in Custom mode (custom_move_effects.h), so the
// power 90 below is used.
//
// "Kept vanilla per user": moves the user chose to leave fully vanilla
// (stats, effects and flags) in Custom mode.

const struct MoveStatOverride gCustomMoveStats[MOVES_COUNT] =
{
    [MOVE_COMET_PUNCH] = { .power = 25, .type = TYPE_FIGHTING, .accuracy = 100 }, // Power 18->25, Normal->Fighting, Acc 85->100
    [MOVE_MEGA_PUNCH] = { .accuracy = 100 }, // Acc 85->100
    [MOVE_PAY_DAY] = { .power = 60 }, // Power 40->60
    [MOVE_FIRE_PUNCH] = { .power = 80 }, // Power 75->80
    [MOVE_ICE_PUNCH] = { .power = 80 }, // Power 75->80
    [MOVE_THUNDER_PUNCH] = { .power = 80 }, // Power 75->80
    // [MOVE_VISE_GRIP] = { .power = 60, .type = TYPE_WATER }, // Power 55->60, Normal->Water. Kept vanilla per user
    [MOVE_RAZOR_WIND] = { .power = 110, .type = TYPE_FLYING }, // Power 80->110, Normal->Flying
    [MOVE_CUT] = { .power = 70, .type = TYPE_STEEL, .accuracy = 100, .pp = 20 }, // Power 50->70, Normal->Steel, Acc 95->100, PP 30->20
    [MOVE_WING_ATTACK] = { .power = 80, .pp = 20 }, // Power 60->80, PP 35->20
    [MOVE_FLY] = { .power = 100, .accuracy = 100 }, // Power 90->100, Acc 95->100
    [MOVE_SLAM] = { .accuracy = 90 }, // Acc 75->90
    [MOVE_MEGA_KICK] = { .accuracy = 85 }, // Acc 75->85
    [MOVE_TWINEEDLE] = { .power = 45 }, // Power 25->45
    [MOVE_FLAMETHROWER] = { .power = 95 }, // Power 90->95
    [MOVE_HYDRO_PUMP] = { .power = 120, .accuracy = 85 }, // Power 110->120, Acc 80->85
    [MOVE_SURF] = { .power = 95 }, // Power 90->95
    [MOVE_ICE_BEAM] = { .power = 95 }, // Power 90->95
    [MOVE_BLIZZARD] = { .power = 120, .accuracy = 75 }, // Power 110->120, Acc 70->75
    [MOVE_AURORA_BEAM] = { .power = 75 }, // Power 65->75
    [MOVE_STRENGTH] = { .type = TYPE_FIGHTING }, // Normal->Fighting
    [MOVE_ABSORB] = { .power = 40 }, // Power 20->40
    [MOVE_MEGA_DRAIN] = { .power = 60 }, // Power 40->60
    [MOVE_SLEEP_POWDER] = { .accuracy = 80 }, // Acc 75->80
    [MOVE_FIRE_SPIN] = { .power = 40, .accuracy = 90 }, // Power 35->40, Acc 85->90
    [MOVE_THUNDERBOLT] = { .power = 95 }, // Power 90->95
    [MOVE_THUNDER] = { .power = 120, .accuracy = 75 }, // Power 110->120, Acc 70->75
    [MOVE_LICK] = { .power = 40 }, // Power 30->40
    [MOVE_SMOG] = { .power = 35, .accuracy = 90 }, // Power 30->35, Acc 70->90
    [MOVE_WATERFALL] = { .power = 85 }, // Power 80->85
    [MOVE_LOVELY_KISS] = { .accuracy = 85 }, // Acc 75->85
    // [MOVE_TRIPLE_KICK] = { .power = 25 }, // Power 10->25. Kept vanilla: expansion scales multi-hit power by hit number
    [MOVE_PRESENT] = { .power = 90 }, // Power 1->90 (used by its Custom-mode EFFECT_HIT_ENEMY_HEAL_ALLY, see note at top)
    [MOVE_METAL_CLAW] = { .power = 60 }, // Power 50->60
    // [MOVE_EXTREME_SPEED] = { .pp = 10 }, // PP 5->10. Kept vanilla per user
    [MOVE_ROCK_SMASH] = { .power = 50 }, // Power 40->50
    [MOVE_WHIRLPOOL] = { .power = 50, .accuracy = 100 }, // Power 35->50, Acc 85->100
    // [MOVE_SECRET_POWER] = { .power = 60, .pp = 15 }, // Power 70->60, PP 20->15. Kept vanilla per user
    [MOVE_DIVE] = { .power = 95 }, // Power 80->95 (one-turn attack in Custom mode, see custom_move_effects.h)
    [MOVE_ARM_THRUST] = { .power = 25 }, // Power 15->25
    [MOVE_LUSTER_PURGE] = { .pp = 10 }, // PP 5->10
    [MOVE_MIST_BALL] = { .pp = 10 }, // PP 5->10
    [MOVE_NEEDLE_ARM] = { .power = 95 }, // Power 60->95
    [MOVE_POISON_FANG] = { .power = 75 }, // Power 50->75
    [MOVE_GRASS_WHISTLE] = { .accuracy = 60 }, // Acc 55->60
    [MOVE_SHADOW_PUNCH] = { .power = 80 }, // Power 60->80
    [MOVE_SAND_TOMB] = { .power = 50, .accuracy = 100 }, // Power 35->50, Acc 85->100
    [MOVE_MUDDY_WATER] = { .power = 95, .accuracy = 90 }, // Power 90->95, Acc 85->90
    [MOVE_DRAGON_CLAW] = { .power = 85 }, // Power 80->85
    [MOVE_COVET] = { .type = TYPE_FAIRY }, // Normal->Fairy
    [MOVE_WATER_PULSE] = { .power = 70 }, // Power 60->70
    [MOVE_PSYCHO_BOOST] = { .accuracy = 100 }, // Acc 90->100
    [MOVE_AURA_SPHERE] = { .power = 90 }, // Power 80->90
    [MOVE_DARK_PULSE] = { .power = 85 }, // Power 80->85
    [MOVE_NIGHT_SLASH] = { .power = 80 }, // Power 70->80
    [MOVE_AQUA_TAIL] = { .power = 100, .accuracy = 85 }, // Power 90->100, Acc 90->85
    [MOVE_X_SCISSOR] = { .power = 85 }, // Power 80->85
    [MOVE_DRAGON_PULSE] = { .power = 90, .accuracy = CUSTOM_ACCURACY_NEVER_MISSES }, // Power 85->90, Acc 100->--
    [MOVE_DRAGON_RUSH] = { .accuracy = 80 }, // Acc 75->80
    [MOVE_POWER_GEM] = { .power = 90 }, // Power 80->90
    [MOVE_FOCUS_BLAST] = { .accuracy = 75 }, // Acc 70->75
    [MOVE_SHADOW_CLAW] = { .power = 90 }, // Power 70->90
    [MOVE_PSYCHO_CUT] = { .power = 80 }, // Power 70->80
    [MOVE_ROCK_CLIMB] = { .type = TYPE_ROCK, .accuracy = 90 }, // Normal->Rock, Acc 85->90
    [MOVE_DRACO_METEOR] = { .accuracy = 100 }, // Acc 90->100
    [MOVE_LEAF_STORM] = { .accuracy = 100 }, // Acc 90->100
    // [MOVE_CROSS_POISON] = { .power = 90 }, // Power 70->90. Kept vanilla per user
    [MOVE_STONE_EDGE] = { .accuracy = 85 }, // Acc 80->85
    // [MOVE_CHATTER] = { .power = 90 }, // Power 65->90. Kept vanilla per user
    [MOVE_JUDGMENT] = { .power = 125 }, // Power 100->125
    [MOVE_CHARGE_BEAM] = { .accuracy = 100 }, // Acc 90->100
    [MOVE_HEAD_SMASH] = { .accuracy = 85 }, // Acc 80->85
    [MOVE_DARK_VOID] = { .accuracy = 70 }, // Acc 50->70
    [MOVE_SHADOW_FORCE] = { .power = 130 }, // Power 120->130
    [MOVE_INFERNO] = { .power = 120 }, // Power 100->120
    [MOVE_WILD_CHARGE] = { .power = 100 }, // Power 90->100
    [MOVE_SACRED_SWORD] = { .pp = 20 }, // PP 15->20
    // [MOVE_RAZOR_SHELL] = { .power = 80, .accuracy = 100 }, // Power 75->80, Acc 95->100. Kept vanilla per user (only gets high crit, see custom_move_flags.h)
    // [MOVE_LEAF_TORNADO] = { .power = 60, .accuracy = 100 }, // Power 65->60, Acc 90->100. Kept vanilla per user
    [MOVE_TAIL_SLAP] = { .accuracy = 100 }, // Acc 85->100
    [MOVE_HURRICANE] = { .power = 120, .accuracy = 75 }, // Power 110->120, Acc 70->75
    [MOVE_GEAR_GRIND] = { .power = 55, .accuracy = 100 }, // Power 50->55, Acc 85->100
    [MOVE_TECHNO_BLAST] = { .power = 140 }, // Power 120->140
    [MOVE_GLACIATE] = { .power = 80 }, // Power 65->80
    [MOVE_ICICLE_CRASH] = { .accuracy = 95 }, // Acc 90->95
    [MOVE_PHANTOM_FORCE] = { .power = 110 }, // Power 90->110
    [MOVE_PETAL_BLIZZARD] = { .power = 80, .category = DAMAGE_CATEGORY_SPECIAL, .target = TARGET_BOTH }, // Power 90->80, Physical->Special, foes and ally->both foes
    [MOVE_FREEZE_DRY] = { .power = 80 }, // Power 70->80
    [MOVE_FAIRY_WIND] = { .power = 60 }, // Power 40->60
    [MOVE_HYPERSPACE_HOLE] = { .power = 90, .pp = 10 }, // Power 80->90, PP 5->10
    [MOVE_MYSTICAL_FIRE] = { .power = 85 }, // Power 75->85
    [MOVE_INFESTATION] = { .power = 50 }, // Power 20->50
    [MOVE_ORIGIN_PULSE] = { .power = 120, .accuracy = 90 }, // Power 110->120, Acc 85->90
    [MOVE_DRAGON_ASCENT] = { .power = 130 }, // Power 120->130
    [MOVE_TOXIC_THREAD] = { .pp = 15 }, // PP 20->15
    // [MOVE_BEAK_BLAST] = { .pp = 10 }, // PP 15->10. Kept vanilla per user
    [MOVE_DRAGON_HAMMER] = { .power = 100 }, // Power 90->100
    [MOVE_FLEUR_CANNON] = { .power = 140, .accuracy = 100 }, // Power 130->140, Acc 90->100
    [MOVE_SPARKLY_SWIRL] = { .power = 110, .accuracy = 85 }, // Power 120->110, Acc 85 (unchanged, set explicitly per user)
    [MOVE_JAW_LOCK] = { .power = 90 }, // Power 80->90
    [MOVE_SNAP_TRAP] = { .power = 50 }, // Power 35->50
    [MOVE_PYRO_BALL] = { .power = 100 }, // Power 120->100
    [MOVE_OBSTRUCT] = { .accuracy = CUSTOM_ACCURACY_NEVER_MISSES }, // Acc 100->--
    [MOVE_EXPANDING_FORCE] = { .target = TARGET_BOTH }, // Selected (both foes only in Psychic Terrain)->always both foes
    [MOVE_MISTY_EXPLOSION] = { .power = 160 }, // Power 100->160
    [MOVE_GRASSY_GLIDE] = { .power = 60 }, // Power 55->60
    [MOVE_LASH_OUT] = { .power = 90 }, // Power 75->90
    // [MOVE_TRIPLE_AXEL] = { .power = 35 }, // Power 20->35. Kept vanilla: expansion scales multi-hit power by hit number
    [MOVE_SCORCHING_SANDS] = { .power = 75 }, // Power 70->75
    [MOVE_THUNDEROUS_KICK] = { .type = TYPE_ELECTRIC }, // Fighting->Electric
};
