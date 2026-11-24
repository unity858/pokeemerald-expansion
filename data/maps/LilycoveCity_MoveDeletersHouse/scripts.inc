LilycoveCity_MoveDeletersHouse_MapScripts::
	.byte 0

@ Trades a WATER starter of the player's choice for 1 Blue Shard (see data/scripts/starter_shard_trade.inc)
LilycoveCity_MoveDeletersHouse_EventScript_WaterStarters::
	lock
	faceplayer
	checkitem ITEM_BLUE_SHARD
	goto_if_eq VAR_RESULT, FALSE, LilycoveCity_MoveDeletersHouse_EventScript_StarterNoShard
	playse SE_PIN
	applymovement VAR_LAST_TALKED, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement VAR_LAST_TALKED, Common_Movement_Delay48
	waitmovement 0
	msgbox LilycoveCity_MoveDeletersHouse_Text_StarterOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, StarterShardTrade_EventScript_Declined
	message StarterShardTrade_Text_WhichOne
	waitmessage
	dynmultichoice 30, 1, FALSE, 6, 0, DYN_MULTICHOICE_CB_NONE, StarterShardTrade_Text_Squirtle, StarterShardTrade_Text_Totodile, StarterShardTrade_Text_Mudkip, StarterShardTrade_Text_Piplup, StarterShardTrade_Text_Oshawott, StarterShardTrade_Text_Froakie, StarterShardTrade_Text_Popplio, StarterShardTrade_Text_Sobble, StarterShardTrade_Text_Quaxly
	setvar VAR_0x800A, ITEM_BLUE_SHARD
	setvar VAR_0x8009, ITEM_NONE
	switch VAR_RESULT
	case 0, LilycoveCity_MoveDeletersHouse_EventScript_Squirtle
	case 1, LilycoveCity_MoveDeletersHouse_EventScript_Totodile
	case 2, LilycoveCity_MoveDeletersHouse_EventScript_Mudkip
	case 3, LilycoveCity_MoveDeletersHouse_EventScript_Piplup
	case 4, LilycoveCity_MoveDeletersHouse_EventScript_Oshawott
	case 5, LilycoveCity_MoveDeletersHouse_EventScript_Froakie
	case 6, LilycoveCity_MoveDeletersHouse_EventScript_Popplio
	case 7, LilycoveCity_MoveDeletersHouse_EventScript_Sobble
	case 8, LilycoveCity_MoveDeletersHouse_EventScript_Quaxly
	goto StarterShardTrade_EventScript_Declined
	end

LilycoveCity_MoveDeletersHouse_EventScript_Squirtle::
	setvar VAR_0x8008, SPECIES_SQUIRTLE
	setvar VAR_0x8009, ITEM_BLASTOISINITE
	goto StarterShardTrade_EventScript_Give
LilycoveCity_MoveDeletersHouse_EventScript_Totodile::
	setvar VAR_0x8008, SPECIES_TOTODILE
	setvar VAR_0x8009, ITEM_FERALIGITE
	goto StarterShardTrade_EventScript_Give
LilycoveCity_MoveDeletersHouse_EventScript_Mudkip::
	setvar VAR_0x8008, SPECIES_MUDKIP
	setvar VAR_0x8009, ITEM_SWAMPERTITE
	goto StarterShardTrade_EventScript_Give
LilycoveCity_MoveDeletersHouse_EventScript_Piplup::
	setvar VAR_0x8008, SPECIES_PIPLUP
	goto StarterShardTrade_EventScript_Give
LilycoveCity_MoveDeletersHouse_EventScript_Oshawott::
	setvar VAR_0x8008, SPECIES_OSHAWOTT
	goto StarterShardTrade_EventScript_Give
LilycoveCity_MoveDeletersHouse_EventScript_Froakie::
	setvar VAR_0x8008, SPECIES_FROAKIE
	setvar VAR_0x8009, ITEM_GRENINJITE
	goto StarterShardTrade_EventScript_Give
LilycoveCity_MoveDeletersHouse_EventScript_Popplio::
	setvar VAR_0x8008, SPECIES_POPPLIO
	goto StarterShardTrade_EventScript_Give
LilycoveCity_MoveDeletersHouse_EventScript_Sobble::
	setvar VAR_0x8008, SPECIES_SOBBLE
	goto StarterShardTrade_EventScript_Give
LilycoveCity_MoveDeletersHouse_EventScript_Quaxly::
	setvar VAR_0x8008, SPECIES_QUAXLY
	goto StarterShardTrade_EventScript_Give

LilycoveCity_MoveDeletersHouse_EventScript_StarterNoShard::
	msgbox LilycoveCity_MoveDeletersHouse_Text_StarterNoShard, MSGBOX_DEFAULT
	release
	end

LilycoveCity_MoveDeletersHouse_Text_StarterNoShard:
	.string "Uh…\n"
	.string "Oh, I don't delete moves anymore.\p"
	.string "These days I raise WATER-type\n"
	.string "POKéMON instead.\p"
	.string "If you bring me a BLUE SHARD, I'll\n"
	.string "trade you one of them for it.$"

LilycoveCity_MoveDeletersHouse_Text_StarterOffer:
	.string "Hm! Is that a BLUE SHARD?\p"
	.string "Do you want to trade it for one\n"
	.string "of my WATER-type POKéMON?$"
