@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

SafariZone_SecretHouse_Frlg_MapScripts::
	.byte 0

SafariZone_SecretHouse_EventScript_Attendant::
	lock
	faceplayer
	goto SafariZone_SecretHouse_EventScript_ExplainSurf

SafariZone_SecretHouse_EventScript_ExplainSurf::
	msgbox SafariZone_SecretHouse_Text_ExplainSurf
	release
	end

SafariZone_SecretHouse_Text_ExplainSurf::
	.string "HM03 is SURF.\p"
	.string "POKéMON will be able to ferry you\n"
	.string "across water using it.\p"
	.string "And, this HM isn't disposable, so\n"
	.string "you can use it over and over.\p"
	.string "You're super lucky for winning this\n"
	.string "fabulous prize!$"
