@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

Route2_House_Frlg_MapScripts::
	.byte 0

Route2_House_EventScript_Scientist::
	msgbox Route2_House_Text_FaintedMonsCanUseFieldMoves, MSGBOX_NPC
	end

Route2_House_Text_FaintedMonsCanUseFieldMoves::
	.string "A fainted POKéMON just has no\n"
	.string "energy left to battle.\p"
	.string "It can still use moves like CUT\n"
	.string "outside of battle.$"
