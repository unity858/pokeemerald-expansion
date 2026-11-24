@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

SilphCo_9F_Frlg_MapScripts::
	.byte 0

SilphCo_9F_EventScript_HealWoman::
	lock
	faceplayer
	goto SilphCo_9F_EventScript_HealWomanRocketsGone

SilphCo_9F_EventScript_HealWomanRocketsGone::
	msgbox SilphCo_9F_Text_ThankYouSoMuch
	release
	end

SilphCo_9F_EventScript_FloorSign::
	msgbox SilphCo_9F_Text_FloorSign, MSGBOX_SIGN
	end

SilphCo_9F_Text_ThankYouSoMuch::
	.string "Thank you so much.$"


SilphCo_9F_Text_FloorSign::
	.string "SILPH CO. HEAD OFFICE\n"
	.string "9F$"
