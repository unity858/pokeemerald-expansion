#include "global.h"
#include "difficulty.h"
#include "test/battle.h"

// Hack: on Easy and Normal a damaging move's hit prints
// "{target} took {N} damage from {attacker}!" after the HP bar drops and
// before the critical hit / effectiveness messages. Hard prints nothing.

SINGLE_BATTLE_TEST("Damage-dealt message: fixed damage, shown on Easy and Normal but not Hard")
{
    u32 difficulty;
    PARAMETRIZE { difficulty = DIFFICULTY_EASY; }
    PARAMETRIZE { difficulty = DIFFICULTY_NORMAL; }
    PARAMETRIZE { difficulty = DIFFICULTY_HARD; }
    GIVEN {
        SetCurrentDifficultyLevel(difficulty);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_MARSHTOMP);
    } WHEN {
        TURN { MOVE(player, MOVE_DRAGON_RAGE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_DRAGON_RAGE, player);
        HP_BAR(opponent, damage: 40);
        if (difficulty == DIFFICULTY_HARD)
            NOT MESSAGE("The opposing Marshtomp took 40 damage from Wobbuffet!");
        else
            MESSAGE("The opposing Marshtomp took 40 damage from Wobbuffet!");
    } FINALLY {
        SetCurrentDifficultyLevel(DIFFICULTY_NORMAL);
    }
}

SINGLE_BATTLE_TEST("Damage-dealt message: KO shows the HP that was left, before crit and effectiveness messages")
{
    GIVEN {
        PLAYER(SPECIES_HAWLUCHA);
        OPPONENT(SPECIES_MARSHTOMP) { HP(7); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_FROST_BREATH); SEND_OUT(opponent, 1); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_FROST_BREATH, player);
        HP_BAR(opponent, damage: 7);
        MESSAGE("The opposing Marshtomp took 7 damage from Hawlucha!");
        MESSAGE("A critical hit!");
        MESSAGE("The opposing Marshtomp fainted!");
    }
}

SINGLE_BATTLE_TEST("Damage-dealt message: shown before the super effective message")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_CHARMANDER) { HP(5); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_WATER_GUN); SEND_OUT(opponent, 1); }
    } SCENE {
        HP_BAR(opponent, damage: 5);
        MESSAGE("The opposing Charmander took 5 damage from Wobbuffet!");
        MESSAGE("It's super effective!");
    }
}

SINGLE_BATTLE_TEST("Damage-dealt message: shown for each hit of a multi-hit move")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_BLISSEY);
    } WHEN {
        TURN { MOVE(player, MOVE_DOUBLE_KICK); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_DOUBLE_KICK, player);
        HP_BAR(opponent, damage: 124);
        MESSAGE("The opposing Blissey took 124 damage from Wobbuffet!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_DOUBLE_KICK, player);
        HP_BAR(opponent, damage: 124);
        MESSAGE("The opposing Blissey took 124 damage from Wobbuffet!");
        MESSAGE("The Pokémon was hit 2 times!");
    }
}

SINGLE_BATTLE_TEST("Damage-dealt message: not shown when a substitute takes the hit")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Speed(1); }
        OPPONENT(SPECIES_MARSHTOMP) { Speed(2); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_SUBSTITUTE); MOVE(player, MOVE_DRAGON_RAGE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SUBSTITUTE, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_DRAGON_RAGE, player);
        NONE_OF {
            HP_BAR(opponent);
            MESSAGE("The opposing Marshtomp took 40 damage from Wobbuffet!");
        }
        MESSAGE("The substitute took damage for the opposing Marshtomp!");
    }
}

SINGLE_BATTLE_TEST("Damage-dealt message: not shown for recoil or Life Orb damage")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Item(ITEM_LIFE_ORB); }
        OPPONENT(SPECIES_MARSHTOMP) { HP(3); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_DOUBLE_EDGE); SEND_OUT(opponent, 1); }
    } SCENE {
        HP_BAR(opponent, damage: 3);
        MESSAGE("The opposing Marshtomp took 3 damage from Wobbuffet!");
        HP_BAR(player);
        NOT MESSAGE("Wobbuffet took 1 damage from Wobbuffet!");
    }
}

DOUBLE_BATTLE_TEST("Damage-dealt message: spread moves show one message per Pokémon hit")
{
    GIVEN {
        PLAYER(SPECIES_HAWLUCHA);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_MARSHTOMP) { HP(2); }
        OPPONENT(SPECIES_WYNAUT) { HP(3); }
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_HYPER_VOICE); SEND_OUT(opponentLeft, 2); SEND_OUT(opponentRight, 3); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_HYPER_VOICE, playerLeft);
        HP_BAR(opponentLeft, damage: 2);
        HP_BAR(opponentRight, damage: 3);
        MESSAGE("The opposing Marshtomp took 2 damage from Hawlucha!");
        MESSAGE("The opposing Wynaut took 3 damage from Hawlucha!");
    }
}

DOUBLE_BATTLE_TEST("Damage-dealt message: single-target move in doubles names the right battlers")
{
    GIVEN {
        PLAYER(SPECIES_HAWLUCHA);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_MARSHTOMP);
        OPPONENT(SPECIES_WYNAUT);
    } WHEN {
        TURN { MOVE(opponentRight, MOVE_SEISMIC_TOSS, target: playerRight); }
    } SCENE {
        HP_BAR(playerRight, damage: 100);
        MESSAGE("Wobbuffet took 100 damage from the opposing Wynaut!");
    }
}
