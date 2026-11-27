@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

RocketHideout_B2F_Frlg_MapScripts::
	.byte 0

@ ---- Team Rocket trainers (FRLG); hidden by FLAG_HIDE_ROCKET_HIDEOUT_ROCKETS once Giovanni is beaten ----

RocketHideout_B2F_EventScript_Grunt::
	trainerbattle_single TRAINER_KANTO_TEAM_ROCKET_GRUNT_13, RocketHideout_B2F_Text_GruntIntro, RocketHideout_B2F_Text_GruntDefeat
	msgbox RocketHideout_B2F_Text_GruntPostBattle, MSGBOX_AUTOCLOSE
	end

RocketHideout_B2F_Text_GruntIntro::
	.string "BOSS said you can see ghosts with\n"
	.string "the SILPH SCOPE.$"

RocketHideout_B2F_Text_GruntDefeat::
	.string "I surrender!$"

RocketHideout_B2F_Text_GruntPostBattle::
	.string "The TEAM ROCKET HQ has four\n"
	.string "underground floors.\p"
	.string "Think you can reach the BOSS?$"
