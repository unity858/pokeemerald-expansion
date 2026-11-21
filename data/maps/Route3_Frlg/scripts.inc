@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

Route3_Frlg_MapScripts::
	.byte 0

Route3_EventScript_Youngster::
	msgbox Route3_Text_TunnelFromCeruleanTiring, MSGBOX_NPC
	end

Route3_EventScript_RouteSign::
	msgbox Route3_Text_RouteSign, MSGBOX_SIGN
	end

Route3_Text_TunnelFromCeruleanTiring::
	.string "Whew… I better take a rest…\n"
	.string "Groan…\p"
	.string "That tunnel from CERULEAN takes a\n"
	.string "lot out of you!$"


Route3_Text_RouteSign::
	.string "ROUTE 3\n"
	.string "MT. MOON AHEAD$"
