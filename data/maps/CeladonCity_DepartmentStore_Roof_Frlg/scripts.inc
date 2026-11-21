@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

CeladonCity_DepartmentStore_Roof_Frlg_MapScripts::
	.byte 0

CeladonCity_DepartmentStore_Roof_EventScript_CooltrainerM::
	msgbox CeladonCity_DepartmentStore_Roof_Text_MySisterIsImmature, MSGBOX_NPC
	end

CeladonCity_DepartmentStore_Roof_EventScript_FloorSign::
	msgbox CeladonCity_DepartmentStore_Roof_Text_FloorSign, MSGBOX_SIGN
	end

CeladonCity_DepartmentStore_Roof_Text_MySisterIsImmature::
	.string "My sister is a TRAINER, believe it\n"
	.string "or not.\p"
	.string "But, she's so immature, she drives\n"
	.string "me nuts!$"


CeladonCity_DepartmentStore_Roof_Text_FloorSign::
	.string "ROOFTOP SQUARE:\n"
	.string "VENDING MACHINES$"
