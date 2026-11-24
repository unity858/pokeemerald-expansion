@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

ThreeIsland_Port_Frlg_MapScripts::
	.byte 0

ThreeIsland_Port_EventScript_Woman::
	lock
	faceplayer
	goto ThreeIsland_Port_EventScript_WomanLostelleFound

ThreeIsland_Port_EventScript_WomanLostelleFound::
	msgbox ThreeIsland_Port_Text_EverythingTurnedOutForBest
	release
	end

ThreeIsland_Port_Text_EverythingTurnedOutForBest::
	.string "Those BIKERS ran off, and\n"
	.string "LOSTELLE was found safe.\p"
	.string "Everything turned out for the best!$"
