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

@ ---- Team Rocket trainers (FRLG); hidden by FLAG_HIDE_SILPH_CO_ROCKETS once Giovanni is beaten ----

SilphCo_3F_EventScript_Grunt::
	trainerbattle_single TRAINER_KANTO_TEAM_ROCKET_GRUNT_25, SilphCo_3F_Text_GruntIntro, SilphCo_3F_Text_GruntDefeat
	msgbox SilphCo_3F_Text_GruntPostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_3F_Text_GruntIntro::
	.string "Quit messing with us, kid!$"

SilphCo_3F_Text_GruntDefeat::
	.string "I give up!$"

SilphCo_3F_Text_GruntPostBattle::
	.string "A hint? You can open doors with\n"
	.string "a CARD KEY!$"

SilphCo_3F_EventScript_Jose::
	trainerbattle_single TRAINER_KANTO_SCIENTIST_JOSE, SilphCo_3F_Text_JoseIntro, SilphCo_3F_Text_JoseDefeat
	msgbox SilphCo_3F_Text_JosePostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_3F_Text_JoseIntro::
	.string "I support TEAM ROCKET more than\n"
	.string "I support SILPH CO.!$"

SilphCo_3F_Text_JoseDefeat::
	.string "You really got me!$"

SilphCo_3F_Text_JosePostBattle::
	.string "Humph…\p"
	.string "TEAM ROCKET said that if I helped\n"
	.string "them, they'd let me study POKéMON.$"
