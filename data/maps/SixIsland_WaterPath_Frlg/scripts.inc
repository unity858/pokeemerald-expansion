@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

SixIsland_WaterPath_Frlg_MapScripts::
	.byte 0

SixIsland_WaterPath_EventScript_HornWantedSign::
	msgbox SixIsland_WaterPath_Text_WantedUltimateHorn, MSGBOX_SIGN
	end

SixIsland_WaterPath_EventScript_RouteSign::
	msgbox SixIsland_WaterPath_Text_RouteSign, MSGBOX_SIGN
	end

SixIsland_WaterPath_Text_WantedUltimateHorn::
	.string "Wanted!\n"
	.string "The Ultimate Horn!$"


SixIsland_WaterPath_Text_RouteSign::
	.string "WATER PATH\n"
	.string "Leads to RUIN VALLEY$"
