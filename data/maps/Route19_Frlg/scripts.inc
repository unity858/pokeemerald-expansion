@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

Route19_Frlg_MapScripts::
	.byte 0

Route19_EventScript_RouteSign::
	msgbox Route19_Text_RouteSign, MSGBOX_SIGN
	end

Route19_Text_RouteSign::
	.string "SEA ROUTE 19\n"
	.string "FUCHSIA CITY - SEAFOAM ISLANDS$"
