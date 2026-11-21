@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

Route4_Frlg_MapScripts::
	.byte 0

Route4_EventScript_Woman::
	msgbox Route4_Text_TrippedOverGeodude, MSGBOX_NPC
	end

Route4_EventScript_MtMoonSign::
	msgbox Route4_Text_MtMoonEntrance, MSGBOX_SIGN
	end

Route4_EventScript_RouteSign::
	msgbox Route4_Text_RouteSign, MSGBOX_SIGN
	end

Route4_Text_TrippedOverGeodude::
	.string "Ouch! I tripped over a rocky\n"
	.string "POKéMON, GEODUDE!$"


Route4_Text_MtMoonEntrance::
	.string "MT. MOON\n"
	.string "Tunnel Entrance$"


Route4_Text_RouteSign::
	.string "ROUTE 4\n"
	.string "MT. MOON - CERULEAN CITY$"
