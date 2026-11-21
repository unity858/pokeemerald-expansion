@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

Route7_Frlg_MapScripts::
	.byte 0

Route7_EventScript_UndergroundPathSign::
	msgbox Route7_Text_UndergroundPathSign, MSGBOX_SIGN
	end

Route7_Text_UndergroundPathSign::
	.string "UNDERGROUND PATH\n"
	.string "CELADON CITY - LAVENDER TOWN$"
