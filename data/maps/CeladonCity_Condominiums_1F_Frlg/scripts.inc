@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

CeladonCity_Condominiums_1F_Frlg_MapScripts::
	.byte 0

CeladonCity_Condominiums_1F_EventScript_TeaWoman::
	lock
	faceplayer
	goto CeladonCity_Condominiums_1F_EventScript_TeaWomanAfterTea

CeladonCity_Condominiums_1F_EventScript_TeaWomanAfterTea::
	msgbox CeladonCity_Condominiums_1F_Text_MyDearMonsKeepMeCompany
	release
	end

CeladonCity_Condominiums_1F_EventScript_Meowth::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MEOWTH, CRY_MODE_NORMAL
	msgbox CeladonCity_Condominiums_1F_Text_Meowth
	waitmoncry
	release
	end

CeladonCity_Condominiums_1F_EventScript_Clefairy::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_CLEFAIRY, CRY_MODE_NORMAL
	msgbox CeladonCity_Condominiums_1F_Text_Clefairy
	waitmoncry
	release
	end

CeladonCity_Condominiums_1F_EventScript_Nidoran::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_NIDORAN_F, CRY_MODE_NORMAL
	msgbox CeladonCity_Condominiums_1F_Text_Nidoran
	waitmoncry
	release
	end

CeladonCity_Condominiums_1F_EventScript_SuiteSign::
	msgbox CeladonCity_Condominiums_1F_Text_ManagersSuite, MSGBOX_SIGN
	end

CeladonCity_Condominiums_1F_Text_Meowth::
	.string "MEOWTH: Meow!$"


CeladonCity_Condominiums_1F_Text_MyDearMonsKeepMeCompany::
	.string "My dear POKéMON keep me company.\n"
	.string "MEOWTH even brings money home!$"


CeladonCity_Condominiums_1F_Text_Clefairy::
	.string "CLEFAIRY: Pi pippippi!$"


CeladonCity_Condominiums_1F_Text_Nidoran::
	.string "NIDORAN♀: Kya kyaoo!$"


CeladonCity_Condominiums_1F_Text_ManagersSuite::
	.string "CELADON MANSION\n"
	.string "Manager's Suite$"
