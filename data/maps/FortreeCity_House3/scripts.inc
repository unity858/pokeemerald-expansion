FortreeCity_House3_MapScripts::
	.byte 0

@ Trades a GRASS starter of the player's choice for 1 Green Shard (see data/scripts/starter_shard_trade.inc)
FortreeCity_House3_EventScript_Maniac::
	lock
	faceplayer
	checkitem ITEM_GREEN_SHARD
	goto_if_eq VAR_RESULT, FALSE, FortreeCity_House3_EventScript_StarterNoShard
	playse SE_PIN
	applymovement VAR_LAST_TALKED, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement VAR_LAST_TALKED, Common_Movement_Delay48
	waitmovement 0
	msgbox FortreeCity_House3_Text_StarterOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, StarterShardTrade_EventScript_Declined
	message StarterShardTrade_Text_WhichOne
	waitmessage
	dynmultichoice 30, 1, FALSE, 6, 0, DYN_MULTICHOICE_CB_NONE, StarterShardTrade_Text_Bulbasaur, StarterShardTrade_Text_Chikorita, StarterShardTrade_Text_Treecko, StarterShardTrade_Text_Turtwig, StarterShardTrade_Text_Snivy, StarterShardTrade_Text_Chespin, StarterShardTrade_Text_Rowlet, StarterShardTrade_Text_Grookey, StarterShardTrade_Text_Sprigatito
	setvar VAR_0x800A, ITEM_GREEN_SHARD
	setvar VAR_0x8009, ITEM_NONE
	switch VAR_RESULT
	case 0, FortreeCity_House3_EventScript_Bulbasaur
	case 1, FortreeCity_House3_EventScript_Chikorita
	case 2, FortreeCity_House3_EventScript_Treecko
	case 3, FortreeCity_House3_EventScript_Turtwig
	case 4, FortreeCity_House3_EventScript_Snivy
	case 5, FortreeCity_House3_EventScript_Chespin
	case 6, FortreeCity_House3_EventScript_Rowlet
	case 7, FortreeCity_House3_EventScript_Grookey
	case 8, FortreeCity_House3_EventScript_Sprigatito
	goto StarterShardTrade_EventScript_Declined
	end

FortreeCity_House3_EventScript_Bulbasaur::
	setvar VAR_0x8008, SPECIES_BULBASAUR
	setvar VAR_0x8009, ITEM_VENUSAURITE
	goto StarterShardTrade_EventScript_Give
FortreeCity_House3_EventScript_Chikorita::
	setvar VAR_0x8008, SPECIES_CHIKORITA
	setvar VAR_0x8009, ITEM_MEGANIUMITE
	goto StarterShardTrade_EventScript_Give
FortreeCity_House3_EventScript_Treecko::
	setvar VAR_0x8008, SPECIES_TREECKO
	setvar VAR_0x8009, ITEM_SCEPTILITE
	goto StarterShardTrade_EventScript_Give
FortreeCity_House3_EventScript_Turtwig::
	setvar VAR_0x8008, SPECIES_TURTWIG
	goto StarterShardTrade_EventScript_Give
FortreeCity_House3_EventScript_Snivy::
	setvar VAR_0x8008, SPECIES_SNIVY
	goto StarterShardTrade_EventScript_Give
FortreeCity_House3_EventScript_Chespin::
	setvar VAR_0x8008, SPECIES_CHESPIN
	setvar VAR_0x8009, ITEM_CHESNAUGHTITE
	goto StarterShardTrade_EventScript_Give
FortreeCity_House3_EventScript_Rowlet::
	setvar VAR_0x8008, SPECIES_ROWLET
	goto StarterShardTrade_EventScript_Give
FortreeCity_House3_EventScript_Grookey::
	setvar VAR_0x8008, SPECIES_GROOKEY
	goto StarterShardTrade_EventScript_Give
FortreeCity_House3_EventScript_Sprigatito::
	setvar VAR_0x8008, SPECIES_SPRIGATITO
	goto StarterShardTrade_EventScript_Give

FortreeCity_House3_EventScript_StarterNoShard::
	msgbox FortreeCity_House3_Text_StarterNoShard, MSGBOX_DEFAULT
	release
	end

FortreeCity_House3_EventScript_SchoolKidM::
	msgbox FortreeCity_House3_Text_OhYouHavePokedex, MSGBOX_NPC
	end

FortreeCity_House3_Text_StarterNoShard:
	.string "I collect rare stones, and GREEN\n"
	.string "SHARDS are my favorite.\p"
	.string "If you bring me one, I'll trade you\n"
	.string "a GRASS-type POKéMON for it.$"

FortreeCity_House3_Text_StarterOffer:
	.string "Is that a GREEN SHARD?\p"
	.string "Do you want to trade it for one\n"
	.string "of my GRASS-type POKéMON?$"

FortreeCity_House3_Text_OhYouHavePokedex:
	.string "What's that thing you have there?\p"
	.string "… … … … … …\p"
	.string "Oh, it's called a POKéDEX?\n"
	.string "It's really awesome!$"

