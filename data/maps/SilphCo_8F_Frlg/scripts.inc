@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

SilphCo_8F_Frlg_MapScripts::
	.byte 0

SilphCo_8F_EventScript_WorkerM::
	lock
	faceplayer
	goto SilphCo_8F_EventScript_WorkerMRocketsGone

SilphCo_8F_EventScript_WorkerMRocketsGone::
	msgbox SilphCo_8F_Text_ThanksForSavingUs
	release
	end

SilphCo_8F_EventScript_FloorSign::
	msgbox SilphCo_8F_Text_FloorSign, MSGBOX_SIGN
	end

SilphCo_8F_Text_ThanksForSavingUs::
	.string "Thanks for saving us!$"


SilphCo_8F_Text_FloorSign::
	.string "SILPH CO. HEAD OFFICE\n"
	.string "8F$"
