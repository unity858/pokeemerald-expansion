@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

PokemonMansion_3F_Frlg_MapScripts::
	.byte 0

PokemonMansion_3F_EventScript_DiaryFeb6th::
	msgbox PokemonMansion_1F_Text_MewGaveBirthToMewtwo, MSGBOX_SIGN
	end

PokemonMansion_1F_Text_MewGaveBirthToMewtwo::
	.string "Diary: Feb. 6\n"
	.string "MEW gave birth.\p"
	.string "We named the newborn MEWTWO.$"
