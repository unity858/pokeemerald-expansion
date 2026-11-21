@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

Route14_Frlg_MapScripts::
	.byte 0

Route14_EventScript_RouteSign::
	msgbox Route14_Text_RouteSign, MSGBOX_SIGN
	end

Route14_Text_RouteSign::
	.string "ROUTE 14\n"
	.string "West to FUCHSIA CITY$"
