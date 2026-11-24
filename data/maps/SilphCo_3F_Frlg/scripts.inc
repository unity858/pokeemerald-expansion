@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

SilphCo_3F_Frlg_MapScripts::
	.byte 0

SilphCo_3F_EventScript_WorkerM::
	lock
	faceplayer
	goto SilphCo_3F_EventScript_WorkerMRocketsGone

SilphCo_3F_EventScript_WorkerMRocketsGone::
	msgbox SilphCo_3F_Text_YouAndYourMonsSavedUs
	release
	end

SilphCo_3F_EventScript_FloorSign::
	msgbox SilphCo_3F_Text_FloorSign, MSGBOX_SIGN
	end

SilphCo_3F_Text_YouAndYourMonsSavedUs::
	.string "{PLAYER}!\n"
	.string "You and your POKéMON saved us!$"


SilphCo_3F_Text_FloorSign::
	.string "SILPH CO. HEAD OFFICE\n"
	.string "3F$"
