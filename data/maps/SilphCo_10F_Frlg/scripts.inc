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

@ ---- Team Rocket trainers (FRLG); hidden by FLAG_HIDE_SILPH_CO_ROCKETS once Giovanni is beaten ----

SilphCo_10F_EventScript_Travis::
	trainerbattle_single TRAINER_KANTO_SCIENTIST_TRAVIS, SilphCo_10F_Text_TravisIntro, SilphCo_10F_Text_TravisDefeat
	msgbox SilphCo_10F_Text_TravisPostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_10F_Text_TravisIntro::
	.string "Enough of your silly games!$"

SilphCo_10F_Text_TravisDefeat::
	.string "No continues left!$"

SilphCo_10F_Text_TravisPostBattle::
	.string "Are you satisfied with beating me?\n"
	.string "Then go on home!$"

SilphCo_10F_EventScript_Grunt::
	trainerbattle_single TRAINER_KANTO_TEAM_ROCKET_GRUNT_39, SilphCo_10F_Text_GruntIntro, SilphCo_10F_Text_GruntDefeat
	msgbox SilphCo_10F_Text_GruntPostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_10F_Text_GruntIntro::
	.string "Welcome to 10F!\n"
	.string "So good of you to join me!$"

SilphCo_10F_Text_GruntDefeat::
	.string "I'm stunned!$"

SilphCo_10F_Text_GruntPostBattle::
	.string "Nice try, but the boardroom is up\n"
	.string "one more floor.$"
