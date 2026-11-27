@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

SilphCo_2F_Frlg_MapScripts::
	.byte 0

SilphCo_2F_EventScript_FloorSign::
	msgbox SilphCo_2F_Text_FloorSign, MSGBOX_SIGN
	end

SilphCo_2F_Text_FloorSign::
	.string "SILPH CO. HEAD OFFICE\n"
	.string "2F$"

@ ---- Team Rocket trainers (FRLG); hidden by FLAG_HIDE_SILPH_CO_ROCKETS once Giovanni is beaten ----

SilphCo_2F_EventScript_Grunt2::
	trainerbattle_single TRAINER_KANTO_TEAM_ROCKET_GRUNT_24, SilphCo_2F_Text_Grunt2Intro, SilphCo_2F_Text_Grunt2Defeat
	msgbox SilphCo_2F_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_2F_Text_Grunt2Intro::
	.string "Hey, kid!\n"
	.string "What are you wandering here for?$"

SilphCo_2F_Text_Grunt2Defeat::
	.string "I goofed!$"

SilphCo_2F_Text_Grunt2PostBattle::
	.string "SILPH CO. will be associated with\n"
	.string "TEAM ROCKET!$"

SilphCo_2F_EventScript_Jerry::
	trainerbattle_single TRAINER_KANTO_SCIENTIST_JERRY, SilphCo_2F_Text_JerryIntro, SilphCo_2F_Text_JerryDefeat
	msgbox SilphCo_2F_Text_JerryPostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_2F_Text_JerryIntro::
	.string "It's off-limits here!\n"
	.string "Go home!$"

SilphCo_2F_Text_JerryDefeat::
	.string "You're good.$"

SilphCo_2F_Text_JerryPostBattle::
	.string "Can you solve the maze in here?\n"
	.string "It's not easy, I tell you!$"

SilphCo_2F_EventScript_Grunt1::
	trainerbattle_single TRAINER_KANTO_TEAM_ROCKET_GRUNT_23, SilphCo_2F_Text_Grunt1Intro, SilphCo_2F_Text_Grunt1Defeat
	msgbox SilphCo_2F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_2F_Text_Grunt1Intro::
	.string "No kids are allowed in here!$"

SilphCo_2F_Text_Grunt1Defeat::
	.string "Tough!$"

SilphCo_2F_Text_Grunt1PostBattle::
	.string "Diamond-shaped tiles are teleport\n"
	.string "blocks.\p"
	.string "They're transporters for this\n"
	.string "high-tech building.$"

SilphCo_2F_EventScript_Connor::
	trainerbattle_single TRAINER_KANTO_SCIENTIST_CONNOR, SilphCo_2F_Text_ConnorIntro, SilphCo_2F_Text_ConnorDefeat
	msgbox SilphCo_2F_Text_ConnorPostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_2F_Text_ConnorIntro::
	.string "Help!\n"
	.string "I'm a SILPH employee.$"

SilphCo_2F_Text_ConnorDefeat::
	.string "How did you know\n"
	.string "I was a ROCKET?$"

SilphCo_2F_Text_ConnorPostBattle::
	.string "I work for both SILPH and TEAM\n"
	.string "ROCKET.$"
