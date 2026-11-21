@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

Route15_Frlg_MapScripts::
	.byte 0

Route15_EventScript_RouteSign::
	msgbox Route15_Text_RouteSign, MSGBOX_SIGN
	end

Route15_Text_RouteSign::
	.string "ROUTE 15\n"
	.string "West to FUCHSIA CITY$"
