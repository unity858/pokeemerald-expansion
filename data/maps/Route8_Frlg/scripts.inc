@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

Route8_Frlg_MapScripts::
	.byte 0

Route8_EventScript_UndergroundPathSign::
	msgbox Route8_Text_UndergroundPathSign, MSGBOX_SIGN
	end

Route8_Text_UndergroundPathSign::
	.string "UNDERGROUND PATH\n"
	.string "CELADON CITY - LAVENDER TOWN$"
