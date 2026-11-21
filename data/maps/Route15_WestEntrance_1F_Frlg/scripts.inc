@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

Route15_WestEntrance_1F_Frlg_MapScripts::
	.byte 0

Route15_WestEntrance_1F_EventScript_Guard::
	msgbox Route15_WestEntrance_1F_Text_OaksAideCameByHere, MSGBOX_NPC
	end

Route15_WestEntrance_1F_Text_OaksAideCameByHere::
	.string "Are you the kid who's working on\n"
	.string "a POKéDEX?\p"
	.string "PROF. OAK's AIDE came by here.$"
