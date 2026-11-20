// Move effect overrides for Custom data mode (ported from R.O.W.E.).
//
// Applied by GetMoveEffect, GetMoveAdditionalEffectCount,
// GetMoveAdditionalEffectById and GetMoveDescription in include/move.h only
// when IsCustomDataMode() is TRUE. Vanilla mode always uses gMovesInfo.
//
// Fields (leave out to keep vanilla):
//   .effect       - replacement battle effect (EFFECT_*).
//   CUSTOM_ADDITIONAL_EFFECTS({...}, ...)
//                 - replaces the move's whole additionalEffects list (same
//                   syntax as ADDITIONAL_EFFECTS in moves_info.h). Sheer Force,
//                   the AI and the summary screen all read this through the
//                   accessors.
//   .description  - replacement move description (summary screen / battle).
//
// Power/type/accuracy/PP changes live in custom_move_stats.h, flag changes in
// custom_move_flags.h.

const struct MoveEffectOverride gCustomMoveEffects[MOVES_COUNT] =
{
    // Breaks screens like Brick Break; keeps its vanilla high critical-hit ratio.
    [MOVE_KARATE_CHOP] =
    {
        CUSTOM_ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BREAK_SCREEN,
            .preAttackEffect = TRUE,
        }),
        .description = COMPOUND_STRING(
            "Breaks barriers. Has a\n"
            "high critical-hit ratio."),
    },

    // 20% chance to raise the user's Attack by 1.
    [MOVE_STRENGTH] =
    {
        CUSTOM_ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_STAT_PLUS,
            .attack = 1,
            .self = TRUE,
            .chance = 20,
        }),
        .description = COMPOUND_STRING(
            "A mighty slam that may\n"
            "raise the user's Attack."),
    },

    // Attack raise chance 10% -> 30% (description still accurate).
    [MOVE_METAL_CLAW] =
    {
        CUSTOM_ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_STAT_PLUS,
            .attack = 1,
            .self = TRUE,
            .chance = 30,
        }),
    },

    // Defense drop chance 50% -> 100%.
    [MOVE_ROCK_SMASH] =
    {
        CUSTOM_ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_STAT_MINUS,
            .defense = 1,
            .chance = 100,
        }),
        .description = COMPOUND_STRING(
            "A rock-crushing attack\n"
            "that lowers Defense."),
    },

    // Badly poison chance 50% -> 20% (R.O.W.E. raised its power 50 -> 75,
    // see custom_move_stats.h). Description still accurate.
    [MOVE_POISON_FANG] =
    {
        CUSTOM_ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_TOXIC,
            .chance = 20,
        }),
    },

    // Sp. Atk raise chance 70% -> 100%.
    [MOVE_CHARGE_BEAM] =
    {
        CUSTOM_ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_STAT_PLUS,
            .spAtk = 1,
            .self = TRUE,
            .chance = 100,
        }),
        .description = COMPOUND_STRING(
            "Fires an electric beam.\n"
            "Raises the user's Sp. Atk."),
    },

    // 10% paralysis, no recoil.
    [MOVE_WILD_CHARGE] =
    {
        .effect = EFFECT_HIT,
        CUSTOM_ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 10,
        }),
        .description = COMPOUND_STRING(
            "An electrical tackle that\n"
            "may cause paralysis."),
    },

    // 10% paralysis (vanilla), no recoil.
    [MOVE_VOLT_TACKLE] =
    {
        .effect = EFFECT_HIT,
        CUSTOM_ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 10,
        }),
        .description = COMPOUND_STRING(
            "A charged-up tackle that\n"
            "may cause paralysis."),
    },

    // 10% chance to lower the target's Sp. Atk; no party status heal.
    // Power 110 / accuracy 85 are in custom_move_stats.h.
    [MOVE_SPARKLY_SWIRL] =
    {
        CUSTOM_ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_STAT_MINUS,
            .spAtk = 1,
            .chance = 10,
        }),
        .description = COMPOUND_STRING(
            "A swirl of sparkles that\n"
            "may lower Sp. Atk."),
    },

    // Damages foes, heals allies (Pollen Puff's effect) instead of a random
    // power or heal. Power 90 is in custom_move_stats.h.
    [MOVE_PRESENT] =
    {
        .effect = EFFECT_HIT_ENEMY_HEAL_ALLY,
        .description = COMPOUND_STRING(
            "A gift that hurts foes but\n"
            "restores an ally's HP."),
    },

    // One-turn attack, no semi-invulnerable charge turn. Power 95 is in
    // custom_move_stats.h. The overworld Dive field move does not use this.
    [MOVE_DIVE] =
    {
        .effect = EFFECT_HIT,
        .description = COMPOUND_STRING(
            "Dives at the foe and\n"
            "strikes in a single turn."),
    },

    // Jungle Healing's effect: heals HP and status of the user and allies.
    [MOVE_LIFE_DEW] =
    {
        .effect = EFFECT_JUNGLE_HEALING,
        .description = COMPOUND_STRING(
            "Heals HP and status of\n"
            "itself and allies in battle."),
    },
};
