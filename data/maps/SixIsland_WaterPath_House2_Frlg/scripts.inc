@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

SixIsland_WaterPath_House2_Frlg_MapScripts::
	.byte 0

SixIsland_WaterPath_House2_EventScript_Man::
	msgbox SixIsland_WaterPath_House2_Text_MyNeighborMeasuredMe, MSGBOX_NPC
	end

SixIsland_WaterPath_House2_Text_MyNeighborMeasuredMe::
	.string "My height is 67.0 inches on the\n"
	.string "button.\p"
	.string "I know it is this precisely because\n"
	.string "my neighbor measured me.$"
