@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

Route18_Frlg_MapScripts::
	.byte 0

Route18_EventScript_RouteSign::
	msgbox Route18_Text_RouteSign, MSGBOX_SIGN
	end

Route18_EventScript_CyclingRoadSign::
	msgbox Route18_Text_CyclingRoadSign, MSGBOX_SIGN
	end

Route18_Text_RouteSign::
	.string "ROUTE 18\n"
	.string "CELADON CITY - FUCHSIA CITY$"


Route18_Text_CyclingRoadSign::
	.string "CYCLING ROAD\n"
	.string "No pedestrians permitted!$"
