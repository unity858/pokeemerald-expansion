@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

CeladonCity_Condominiums_Roof_Frlg_MapScripts::
	.byte 0

CeladonCity_Condominiums_Roof_EventScript_Sign::
	msgbox CeladonCity_Condominiums_Roof_Text_IKnowEverything, MSGBOX_SIGN
	end

CeladonCity_Condominiums_Roof_Text_IKnowEverything::
	.string "I KNOW EVERYTHING!$"
