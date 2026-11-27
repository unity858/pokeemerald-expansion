#include "global.h"
#include "item.h"
#include "test/battle.h"

// R.O.W.E.: a wild Pokemon knocked out while holding its own item drops it.
// The item goes to the Bag when the battle is won (or ends with a catch), with
// "{mon} dropped its {item}!". Never in Trainer battles.

ASSUMPTIONS
{
    ASSUME(B_WILD_HELD_ITEM_DROPS == TRUE);
}

WILD_BATTLE_TEST("Wild item drop: a knocked-out wild Pokemon drops its held item into the Bag")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { HP(1); Item(ITEM_HYPER_POTION); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        MESSAGE("The wild Wobbuffet fainted!");
        MESSAGE("The wild Wobbuffet dropped its Hyper Potion!");
    } THEN {
        EXPECT_EQ(TRUE, CheckBagHasItem(ITEM_HYPER_POTION, 1));
    }
}

WILD_BATTLE_TEST("Wild item drop: a wild Pokemon that faints itself still drops its item")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_MEMENTO) == EFFECT_MEMENTO);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Item(ITEM_HYPER_POTION); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_MEMENTO); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_MEMENTO, opponent);
        MESSAGE("The wild Wobbuffet dropped its Hyper Potion!");
    } THEN {
        EXPECT_EQ(TRUE, CheckBagHasItem(ITEM_HYPER_POTION, 1));
    }
}

WILD_BATTLE_TEST("Wild item drop: nothing is dropped by a wild Pokemon with no held item")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { HP(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        MESSAGE("The wild Wobbuffet fainted!");
        NOT MESSAGE("The wild Wobbuffet dropped its Hyper Potion!");
    }
}

SINGLE_BATTLE_TEST("Wild item drop: a Trainer's Pokemon never drops its held item")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { HP(1); Item(ITEM_HYPER_POTION); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        MESSAGE("The opposing Wobbuffet fainted!");
        NOT MESSAGE("The opposing Wobbuffet dropped its Hyper Potion!");
    } THEN {
        EXPECT_EQ(FALSE, CheckBagHasItem(ITEM_HYPER_POTION, 1));
    }
}

// These knock the wild Pokemon out with two Dragon Rages (40 HP each) after the
// item is lost, from a level 1 user so the first move can't knock it out.
WILD_BATTLE_TEST("Wild item drop: a Knocked Off item is not dropped")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_KNOCK_OFF) == EFFECT_KNOCK_OFF);
        ASSUME(GetMoveEffect(MOVE_DRAGON_RAGE) == EFFECT_FIXED_HP_DAMAGE);
        PLAYER(SPECIES_WOBBUFFET) { Level(1); }
        OPPONENT(SPECIES_WOBBUFFET) { MaxHP(100); HP(60); Item(ITEM_HYPER_POTION); }
    } WHEN {
        TURN { MOVE(player, MOVE_KNOCK_OFF); }
        TURN { MOVE(player, MOVE_DRAGON_RAGE); }
        TURN { MOVE(player, MOVE_DRAGON_RAGE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_KNOCK_OFF, player);
        MESSAGE("Wobbuffet knocked off the wild Wobbuffet's Hyper Potion!");
        MESSAGE("The wild Wobbuffet fainted!");
        NOT MESSAGE("The wild Wobbuffet dropped its Hyper Potion!");
    } THEN {
        EXPECT_EQ(FALSE, CheckBagHasItem(ITEM_HYPER_POTION, 1));
    }
}

WILD_BATTLE_TEST("Wild item drop: an item stolen by Thief (held by the thief) is not dropped again")
{
    GIVEN {
        WITH_CONFIG(B_STEAL_WILD_ITEMS, GEN_8);
        PLAYER(SPECIES_WOBBUFFET) { Level(1); }
        OPPONENT(SPECIES_WOBBUFFET) { MaxHP(100); HP(60); Item(ITEM_HYPER_POTION); }
    } WHEN {
        TURN { MOVE(player, MOVE_THIEF); }
        TURN { MOVE(player, MOVE_DRAGON_RAGE); }
        TURN { MOVE(player, MOVE_DRAGON_RAGE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_ITEM_STEAL, opponent);
        MESSAGE("The wild Wobbuffet fainted!");
        NOT MESSAGE("The wild Wobbuffet dropped its Hyper Potion!");
    } THEN {
        EXPECT_EQ(FALSE, CheckBagHasItem(ITEM_HYPER_POTION, 1));
    }
}

WILD_BATTLE_TEST("Wild item drop: an item stolen by Thief into the Bag is only given once")
{
    GIVEN {
        WITH_CONFIG(B_STEAL_WILD_ITEMS, GEN_9);
        PLAYER(SPECIES_WOBBUFFET) { Level(1); }
        OPPONENT(SPECIES_WOBBUFFET) { MaxHP(100); HP(60); Item(ITEM_HYPER_POTION); }
    } WHEN {
        TURN { MOVE(player, MOVE_THIEF); }
        TURN { MOVE(player, MOVE_DRAGON_RAGE); }
        TURN { MOVE(player, MOVE_DRAGON_RAGE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_ITEM_STEAL, opponent);
        MESSAGE("The wild Wobbuffet fainted!");
        NOT MESSAGE("The wild Wobbuffet dropped its Hyper Potion!");
    } THEN {
        EXPECT_EQ(TRUE, CheckBagHasItem(ITEM_HYPER_POTION, 1));
        EXPECT_EQ(FALSE, CheckBagHasItem(ITEM_HYPER_POTION, 2));
    }
}

WILD_BATTLE_TEST("Wild item drop: an eaten Berry is not dropped")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_DRAGON_RAGE) == EFFECT_FIXED_HP_DAMAGE);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { MaxHP(100); HP(60); Item(ITEM_SITRUS_BERRY); }
    } WHEN {
        TURN { MOVE(player, MOVE_DRAGON_RAGE); } // 60 -> 20, Sitrus Berry -> 45
        TURN { MOVE(player, MOVE_DRAGON_RAGE); } // 45 -> 5
        TURN { MOVE(player, MOVE_DRAGON_RAGE); } // fainted
    } SCENE {
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_BERRY, opponent);
        MESSAGE("The wild Wobbuffet fainted!");
        NOT MESSAGE("The wild Wobbuffet dropped its Sitrus Berry!");
    } THEN {
        EXPECT_EQ(FALSE, CheckBagHasItem(ITEM_SITRUS_BERRY, 1));
    }
}

WILD_BATTLE_TEST("Wild item drop: an item the player Tricked onto the wild Pokemon is not dropped")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_TRICK) == EFFECT_TRICK);
        PLAYER(SPECIES_WOBBUFFET) { Item(ITEM_HYPER_POTION); }
        OPPONENT(SPECIES_WOBBUFFET) { MaxHP(100); HP(60); }
    } WHEN {
        TURN { MOVE(player, MOVE_TRICK); }
        TURN { MOVE(player, MOVE_DRAGON_RAGE); }
        TURN { MOVE(player, MOVE_DRAGON_RAGE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TRICK, player);
        MESSAGE("The wild Wobbuffet fainted!");
        NOT MESSAGE("The wild Wobbuffet dropped its Hyper Potion!");
    } THEN {
        EXPECT_EQ(FALSE, CheckBagHasItem(ITEM_HYPER_POTION, 1));
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_HELD_ITEM), ITEM_HYPER_POTION);
    }
}

WILD_BATTLE_TEST("Wild item drop: a caught wild Pokemon keeps its held item and drops nothing")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Item(ITEM_HYPER_POTION); }
    } WHEN {
        TURN { USE_ITEM(player, ITEM_MASTER_BALL); }
    } SCENE {
        NOT MESSAGE("The wild Wobbuffet dropped its Hyper Potion!");
    } THEN {
        EXPECT_EQ(FALSE, CheckBagHasItem(ITEM_HYPER_POTION, 1));
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][1], MON_DATA_HELD_ITEM), ITEM_HYPER_POTION);
    }
}

WILD_BATTLE_TEST("Wild item drop: with no room in the Bag the item is left behind")
{
    GIVEN {
        ASSUME(GetItemPocket(ITEM_RAZZ_BERRY) == POCKET_BERRIES);
        GIVE_PLAYER_ITEM(ITEM_RAZZ_BERRY, MAX_BAG_ITEM_CAPACITY);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { HP(1); Item(ITEM_RAZZ_BERRY); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        MESSAGE("The wild Wobbuffet fainted!");
        MESSAGE("The wild Wobbuffet dropped its Razz Berry, but your Bag is full!");
    } THEN {
        EXPECT_EQ(TRUE, CheckBagHasItem(ITEM_RAZZ_BERRY, MAX_BAG_ITEM_CAPACITY));
    }
}

WILD_DOUBLE_BATTLE_TEST("Wild item drop: both wild Pokemon in a double battle drop their items")
{
    GIVEN {
        ASSUME(GetMoveTarget(MOVE_SURF) == TARGET_FOES_AND_ALLY);
        PLAYER(SPECIES_WOBBUFFET);
        PLAYER(SPECIES_WYNAUT);
        OPPONENT(SPECIES_WOBBUFFET) { HP(1); Item(ITEM_HYPER_POTION); }
        OPPONENT(SPECIES_WYNAUT) { HP(1); Item(ITEM_FULL_RESTORE); }
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_SURF); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SURF, playerLeft);
        MESSAGE("The wild Wobbuffet dropped its Hyper Potion!");
        MESSAGE("The wild Wynaut dropped its Full Restore!");
    } THEN {
        EXPECT_EQ(TRUE, CheckBagHasItem(ITEM_HYPER_POTION, 1));
        EXPECT_EQ(TRUE, CheckBagHasItem(ITEM_FULL_RESTORE, 1));
    }
}

WILD_DOUBLE_BATTLE_TEST("Wild item drop: in a double battle the fainted foe drops its item when the other is caught")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        PLAYER(SPECIES_WYNAUT);
        OPPONENT(SPECIES_WOBBUFFET) { HP(1); Item(ITEM_HYPER_POTION); }
        OPPONENT(SPECIES_WYNAUT) { Item(ITEM_FULL_RESTORE); }
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_SCRATCH, target: opponentLeft); }
        TURN { USE_ITEM(playerLeft, ITEM_MASTER_BALL); }
    } SCENE {
        MESSAGE("The wild Wobbuffet fainted!");
        MESSAGE("The wild Wobbuffet dropped its Hyper Potion!");
        NOT MESSAGE("The wild Wynaut dropped its Full Restore!");
    } THEN {
        EXPECT_EQ(TRUE, CheckBagHasItem(ITEM_HYPER_POTION, 1));
        EXPECT_EQ(FALSE, CheckBagHasItem(ITEM_FULL_RESTORE, 1));
    }
}
