@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

FourIsland_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FourIsland_OnTransition
	.byte 0

FourIsland_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_FOUR_ISLAND
	call FourIsland_EventScript_TrySetDayCareManPos
	end

FourIsland_EventScript_TrySetDayCareManPos::

FourIsland_EventScript_EndSetDayCareManPos::
	return

FourIsland_EventScript_OldWoman::
	lock
	faceplayer
	goto FourIsland_EventScript_OldWomanLoreleiLeft

FourIsland_EventScript_OldWomanLoreleiLeft::
	msgbox FourIsland_Text_LoreleiMetLaprasAsChild
	release
	end

FourIsland_EventScript_LittleGirl::
	lock
	faceplayer
	msgbox FourIsland_Text_LoreleiHasLotsOfStuffedDolls
	release
	end

FourIsland_EventScript_FatMan::
	msgbox FourIsland_Text_MadeSlushieUsingIcefallCaveIce, MSGBOX_NPC
	end

FourIsland_EventScript_IslandSign::
	msgbox FourIsland_Text_IslandSign, MSGBOX_SIGN
	end

FourIsland_EventScript_LoreleisHouseSign::
	msgbox FourIsland_Text_LoreleisHouse, MSGBOX_SIGN
	end

FourIsland_Text_IslandSign::
	.string "FOUR ISLAND\n"
	.string "The Warm, Blue, Floe Island$"


FourIsland_Text_LoreleiMetLaprasAsChild::
	.string "LORELEI has gone back.\p"
	.string "The LAPRAS she has, I imagine it\n"
	.string "to be the one she met as a child.\p"
	.string "I believe it was in ICEFALL CAVE\n"
	.string "that she caught it.\p"
	.string "Perhaps that POKéMON has been with\n"
	.string "her ever since.$"


FourIsland_Text_LoreleiHasLotsOfStuffedDolls::
	.string "Oh, you found me!\n"
	.string "Please don't tell LORELEI.\p"
	.string "Did you know that LORELEI has lots\n"
	.string "and lots of stuffed dolls?\p"
	.string "Every time she comes back to\n"
	.string "FOUR ISLAND, her collection grows!$"


FourIsland_Text_MadeSlushieUsingIcefallCaveIce::
	.string "Ooh, chilly!\p"
	.string "I made a slushie using ice I\n"
	.string "shaved inside ICEFALL CAVE.\p"
	.string "It's chilly and tasty!$"


FourIsland_Text_LoreleisHouse::
	.string "LORELEI'S HOUSE$"
