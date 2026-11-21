@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

Route5_Frlg_MapScripts::
	.byte 0

Route5_EventScript_UndergroundPathSign::
	msgbox Route5_Text_UndergroundPathSign, MSGBOX_SIGN
	end

Route5_Text_UndergroundPathSign::
	.string "UNDERGROUND PATH\n"
	.string "CERULEAN CITY - VERMILION CITY$"
