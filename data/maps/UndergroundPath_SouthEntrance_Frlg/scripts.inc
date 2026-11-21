@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

UndergroundPath_SouthEntrance_Frlg_MapScripts::
	.byte 0

UndergroundPath_SouthEntrance_EventScript_Woman::
	msgbox UndergroundPath_SouthEntrance_Text_PeopleLoseThingsInTheDarkness, MSGBOX_NPC
	end

UndergroundPath_SouthEntrance_Text_PeopleLoseThingsInTheDarkness::
	.string "People often lose things in the\n"
	.string "darkness of the UNDERGROUND PATH.$"
