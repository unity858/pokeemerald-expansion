@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

Route9_Frlg_MapScripts::
	.byte 0

Route9_EventScript_RouteSign::
	msgbox Route9_Text_RouteSign, MSGBOX_SIGN
	end

Route9_Text_RouteSign::
	.string "ROUTE 9\n"
	.string "CERULEAN CITY - ROCK TUNNEL$"
