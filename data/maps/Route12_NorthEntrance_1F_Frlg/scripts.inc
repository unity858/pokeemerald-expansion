@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

Route12_NorthEntrance_1F_Frlg_MapScripts::
	.byte 0

Route12_NorthEntrance_1F_EventScript_Guard::
	msgbox Route12_NorthEntrance_1F_Text_LookoutSpotUpstairs, MSGBOX_NPC
	end

Route12_NorthEntrance_1F_Text_LookoutSpotUpstairs::
	.string "There's a lookout spot upstairs.\n"
	.string "The view is magnificent.$"
