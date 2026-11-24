@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

SafariZone_West_RestHouse_Frlg_MapScripts::
	.byte 0

SafariZone_West_RestHouse_EventScript_Man::
	msgbox SafariZone_West_Text_BaitMakesMonStickAround, MSGBOX_NPC
	end

SafariZone_West_RestHouse_EventScript_Scientist::
	msgbox SafariZone_West_Text_RocksMakeMonRunButEasierCatch, MSGBOX_NPC
	end

SafariZone_West_RestHouse_EventScript_CooltrainerF::
	msgbox SafariZone_West_Text_HikedLotsDidntSeeMonIWanted, MSGBOX_NPC
	end

SafariZone_West_Text_RocksMakeMonRunButEasierCatch::
	.string "Tossing ROCKS at POKéMON might\n"
	.string "make them run, but they'll be\l"
	.string "easier to catch.$"


SafariZone_West_Text_BaitMakesMonStickAround::
	.string "Using BAIT will make POKéMON more\n"
	.string "likely to stick around if they get\l"
	.string "busy eating.$"


SafariZone_West_Text_HikedLotsDidntSeeMonIWanted::
	.string "I hiked a lot, but I didn't see any\n"
	.string "POKéMON I wanted.$"
