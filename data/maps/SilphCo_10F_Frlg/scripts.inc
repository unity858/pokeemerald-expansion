@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

SilphCo_10F_Frlg_MapScripts::
	.byte 0

SilphCo_10F_EventScript_WorkerF::
	lock
	faceplayer
	goto SilphCo_10F_EventScript_WorkerFRocketsGone

SilphCo_10F_EventScript_WorkerFRocketsGone::
	msgbox SilphCo_10F_Text_KeepMeCryingASecret
	release
	end

SilphCo_10F_EventScript_FloorSign::
	msgbox SilphCo_10F_Text_FloorSign, MSGBOX_SIGN
	end

SilphCo_10F_Text_KeepMeCryingASecret::
	.string "About me crying…\n"
	.string "Please keep it a secret.$"


SilphCo_10F_Text_FloorSign::
	.string "SILPH CO. HEAD OFFICE\n"
	.string "10F$"
