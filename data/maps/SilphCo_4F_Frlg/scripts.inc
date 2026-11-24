@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

SilphCo_4F_Frlg_MapScripts::
	.byte 0

SilphCo_4F_EventScript_WorkerM::
	lock
	faceplayer
	goto SilphCo_4F_EventScript_WorkerMRocketsGone

SilphCo_4F_EventScript_WorkerMRocketsGone::
	msgbox SilphCo_4F_Text_TeamRocketIsGone
	release
	end

SilphCo_4F_EventScript_FloorSign::
	msgbox SilphCo_4F_Text_FloorSign, MSGBOX_SIGN
	end

SilphCo_4F_Text_TeamRocketIsGone::
	.string "Huh?\n"
	.string "TEAM ROCKET is gone?$"


SilphCo_4F_Text_FloorSign::
	.string "SILPH CO. HEAD OFFICE\n"
	.string "4F$"
