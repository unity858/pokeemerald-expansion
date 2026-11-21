@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

OneIsland_TreasureBeach_Frlg_MapScripts::
	.byte 0

OneIsland_TreasureBeach_EventScript_Boy::
	msgbox OneIsland_TreasureBeach_Text_GoodThingsWashUpOnBeach, MSGBOX_NPC
	end

OneIsland_TreasureBeach_Text_GoodThingsWashUpOnBeach::
	.string "Good things get washed up by the\n"
	.string "ocean current onto this beach.\p"
	.string "That's why I often come here for\n"
	.string "some beachcombing.$"
