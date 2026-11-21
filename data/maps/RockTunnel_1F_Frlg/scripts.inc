@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

RockTunnel_1F_Frlg_MapScripts::
	.byte 0

RockTunnel_1F_EventScript_RouteSign::
	msgbox RockTunnel_1F_Text_RouteSign, MSGBOX_SIGN
	end

RockTunnel_1F_Text_RouteSign::
	.string "ROCK TUNNEL\n"
	.string "CERULEAN CITY - LAVENDER TOWN$"
