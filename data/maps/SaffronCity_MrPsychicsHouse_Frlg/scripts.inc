@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

SaffronCity_MrPsychicsHouse_Frlg_MapScripts::
	.byte 0

SaffronCity_MrPsychicsHouse_EventScript_MrPsychic::
	lock
	faceplayer
	goto SaffronCity_MrPsychicsHouse_EventScript_AlreadyGotTM29

SaffronCity_MrPsychicsHouse_EventScript_AlreadyGotTM29::
	msgbox SaffronCity_MrPsychicsHouse_Text_ExplainTM29
	release
	end

SaffronCity_MrPsychicsHouse_Text_ExplainTM29::
	.string "You already know, don't you?\n"
	.string "TM29 is PSYCHIC.\p"
	.string "It's an attack that may also lower\n"
	.string "the target's special stats.$"
