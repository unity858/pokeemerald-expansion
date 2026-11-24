#include "global.h"
#include "test/battle.h"

// "The substitute took damage for X!" must only appear for a Pokémon whose
// substitute actually took the hit, and must name that Pokémon.

SINGLE_BATTLE_TEST("Substitute message: attacker's own substitute does not print a message for the target")
{
    GIVEN {
        PLAYER(SPECIES_HAWLUCHA) { Speed(10); }
        OPPONENT(SPECIES_MARSHTOMP) { Speed(1); HP(30); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_SUBSTITUTE); MOVE(opponent, MOVE_METAL_SOUND); }
        TURN { MOVE(player, MOVE_ACROBATICS); SEND_OUT(opponent, 1); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SUBSTITUTE, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_METAL_SOUND, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ACROBATICS, player);
        NONE_OF {
            MESSAGE("The substitute took damage for the opposing Marshtomp!");
            MESSAGE("The substitute took damage for Hawlucha!");
        }
        MESSAGE("The opposing Marshtomp took 30 damage from Hawlucha!");
        NONE_OF {
            MESSAGE("The substitute took damage for the opposing Marshtomp!");
            MESSAGE("The substitute took damage for Hawlucha!");
        }
    }
}

DOUBLE_BATTLE_TEST("Substitute message: attacker or its ally having a substitute prints nothing when hitting a foe")
{
    struct BattlePokemon *subUser = NULL;
    PARAMETRIZE { subUser = playerLeft; }
    PARAMETRIZE { subUser = playerRight; }
    GIVEN {
        PLAYER(SPECIES_HAWLUCHA) { Speed(10); }
        PLAYER(SPECIES_WOBBUFFET) { Speed(9); }
        OPPONENT(SPECIES_MARSHTOMP) { Speed(2); }
        OPPONENT(SPECIES_WYNAUT) { Speed(1); }
    } WHEN {
        TURN { MOVE(subUser, MOVE_SUBSTITUTE); }
        TURN { MOVE(playerLeft, MOVE_DRAGON_RAGE, target: opponentLeft); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SUBSTITUTE, subUser);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_DRAGON_RAGE, playerLeft);
        NONE_OF {
            MESSAGE("The substitute took damage for the opposing Marshtomp!");
            MESSAGE("The substitute took damage for Hawlucha!");
            MESSAGE("The substitute took damage for Wobbuffet!");
        }
        MESSAGE("The opposing Marshtomp took 40 damage from Hawlucha!");
        NONE_OF {
            MESSAGE("The substitute took damage for the opposing Marshtomp!");
            MESSAGE("The substitute took damage for Hawlucha!");
            MESSAGE("The substitute took damage for Wobbuffet!");
        }
    }
}

DOUBLE_BATTLE_TEST("Substitute message: foe with a substitute attacking a foe without one prints nothing")
{
    GIVEN {
        PLAYER(SPECIES_HAWLUCHA) { Speed(1); }
        PLAYER(SPECIES_WOBBUFFET) { Speed(2); }
        OPPONENT(SPECIES_MARSHTOMP) { Speed(10); }
        OPPONENT(SPECIES_WYNAUT) { Speed(9); }
    } WHEN {
        TURN { MOVE(opponentLeft, MOVE_SUBSTITUTE); }
        TURN { MOVE(opponentLeft, MOVE_DRAGON_RAGE, target: playerLeft); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SUBSTITUTE, opponentLeft);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_DRAGON_RAGE, opponentLeft);
        NONE_OF {
            MESSAGE("The substitute took damage for Hawlucha!");
            MESSAGE("The substitute took damage for the opposing Marshtomp!");
        }
        MESSAGE("Hawlucha took 40 damage from the opposing Marshtomp!");
        NONE_OF {
            MESSAGE("The substitute took damage for Hawlucha!");
            MESSAGE("The substitute took damage for the opposing Marshtomp!");
        }
    }
}

DOUBLE_BATTLE_TEST("Substitute message: spread move names the Pokémon whose substitute was hit")
{
    GIVEN {
        PLAYER(SPECIES_HAWLUCHA) { Speed(1); }
        PLAYER(SPECIES_WOBBUFFET) { Speed(2); }
        OPPONENT(SPECIES_MARSHTOMP) { Speed(10); HP(1); }
        OPPONENT(SPECIES_WYNAUT) { Speed(9); }
    } WHEN {
        TURN { MOVE(opponentRight, MOVE_SUBSTITUTE); }
        TURN { MOVE(playerLeft, MOVE_ROCK_SLIDE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SUBSTITUTE, opponentRight);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ROCK_SLIDE, playerLeft);
        MESSAGE("The substitute took damage for the opposing Wynaut!");
        NOT MESSAGE("The substitute took damage for the opposing Marshtomp!");
        MESSAGE("The opposing Marshtomp took 1 damage from Hawlucha!");
    }
}
