@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

SilphCo_11F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SilphCo_11F_OnTransition
	.byte 0

@ VAR_TEMP_2 is 1 once Giovanni is beaten, which turns off the triggers in front of the boardroom door.
SilphCo_11F_OnTransition::
	call_if_defeated TRAINER_KANTO_BOSS_GIOVANNI_2, SilphCo_11F_EventScript_SetGiovanniBeaten
	end

SilphCo_11F_EventScript_SetGiovanniBeaten::
	setvar VAR_TEMP_2, 1
	return

SilphCo_11F_EventScript_President::
	lock
	faceplayer
	goto SilphCo_11F_EventScript_AlreadyGotMasterBall

SilphCo_11F_EventScript_AlreadyGotMasterBall::
	msgbox SilphCo_11F_Text_ThatsOurSecretPrototype
	release
	end

SilphCo_11F_EventScript_Secretary::
	msgbox SilphCo_11F_Text_ThanksForRescuingUs, MSGBOX_NPC
	end

SilphCo_11F_EventScript_FloorSign::
	msgbox SilphCo_11F_Text_FloorSign, MSGBOX_SIGN
	end

SilphCo_11F_Text_ThatsOurSecretPrototype::
	.string "PRESIDENT: You can't buy that\n"
	.string "anywhere.\p"
	.string "It's our secret prototype MASTER\n"
	.string "BALL.\p"
	.string "It will catch any POKéMON without\n"
	.string "fail!\p"
	.string "You should be quiet about using it,\n"
	.string "though.$"


SilphCo_11F_Text_ThanksForRescuingUs::
	.string "SECRETARY: Thank you for rescuing\n"
	.string "all of us.\p"
	.string "We, from the PRESIDENT down,\n"
	.string "are indebted to you.$"


SilphCo_11F_Text_FloorSign::
	.string "SILPH CO. HEAD OFFICE\n"
	.string "11F$"

@ ---- Team Rocket trainers (FRLG); hidden by FLAG_HIDE_SILPH_CO_ROCKETS once Giovanni is beaten ----

SilphCo_11F_EventScript_Grunt1::
	trainerbattle_single TRAINER_KANTO_TEAM_ROCKET_GRUNT_40, SilphCo_11F_Text_Grunt1Intro, SilphCo_11F_Text_Grunt1Defeat
	msgbox SilphCo_11F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_11F_Text_Grunt1Intro::
	.string "Halt! Do you have an appointment\n"
	.string "with my BOSS?$"

SilphCo_11F_Text_Grunt1Defeat::
	.string "Gaah!\n"
	.string "Demolished!$"

SilphCo_11F_Text_Grunt1PostBattle::
	.string "Watch your step…\n"
	.string "My BOSS likes his POKéMON tough!$"

SilphCo_11F_EventScript_Grunt2::
	trainerbattle_single TRAINER_KANTO_TEAM_ROCKET_GRUNT_41, SilphCo_11F_Text_Grunt2Intro, SilphCo_11F_Text_Grunt2Defeat
	msgbox SilphCo_11F_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_11F_Text_Grunt2Intro::
	.string "Stop right there!\n"
	.string "Don't you move!$"

SilphCo_11F_Text_Grunt2Defeat::
	.string "Don't…\n"
	.string "Please!$"

SilphCo_11F_Text_Grunt2PostBattle::
	.string "So, you want to see my BOSS?$"

@ ---- Giovanni (FRLG) ----
@ The triggers in front of the boardroom door start the battle as in FRLG. Here Giovanni stays in the
@ boardroom afterwards (back at his spot, (6,11)) and only gives a line when talked to; beating him sets
@ FLAG_HIDE_SILPH_CO_ROCKETS, which hides every Rocket trainer on 2F-11F.
@ To make him leave as in FRLG instead: give his object the flag FLAG_HIDE_SILPH_CO_ROCKETS and
@ removeobject LOCALID_SILPH_CO_GIOVANNI in place of the setobjectxy/turnobject below.
SilphCo_11F_EventScript_Giovanni::
	trainerbattle_single TRAINER_KANTO_BOSS_GIOVANNI_2, SilphCo_11F_Text_GiovanniIntro, SilphCo_11F_Text_GiovanniDefeat, SilphCo_11F_EventScript_DefeatedGiovanni
	msgbox SilphCo_11F_Text_GiovanniAfterBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_11F_EventScript_GiovanniTriggerLeft::
	lockall
	setvar VAR_TEMP_1, 0
	goto SilphCo_11F_EventScript_BattleGiovanni
	end

SilphCo_11F_EventScript_GiovanniTriggerRight::
	lockall
	setvar VAR_TEMP_1, 1
	goto SilphCo_11F_EventScript_BattleGiovanni
	end

SilphCo_11F_EventScript_BattleGiovanni::
	textcolor NPC_TEXT_COLOR_MALE
	applymovement LOCALID_SILPH_CO_GIOVANNI, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 25
	msgbox SilphCo_11F_Text_GiovanniIntro
	closemessage
	call_if_eq VAR_TEMP_1, 0, SilphCo_11F_EventScript_GiovanniApproachLeft
	call_if_eq VAR_TEMP_1, 1, SilphCo_11F_EventScript_GiovanniApproachRight
	setvar VAR_LAST_TALKED, LOCALID_SILPH_CO_GIOVANNI
	trainerbattle_no_intro TRAINER_KANTO_BOSS_GIOVANNI_2, SilphCo_11F_Text_GiovanniDefeat
	goto SilphCo_11F_EventScript_DefeatedGiovanni
	end

SilphCo_11F_EventScript_DefeatedGiovanni::
	msgbox SilphCo_11F_Text_GiovanniPostBattle
	closemessage
	fadescreen FADE_TO_BLACK
	setflag FLAG_HIDE_SILPH_CO_ROCKETS
	removeobject LOCALID_SILPH_CO_11F_GRUNT_1
	removeobject LOCALID_SILPH_CO_11F_GRUNT_2
	setobjectxy LOCALID_SILPH_CO_GIOVANNI, 6, 11
	turnobject LOCALID_SILPH_CO_GIOVANNI, DIR_EAST
	fadescreen FADE_FROM_BLACK
	setvar VAR_TEMP_2, 1
	releaseall
	end

SilphCo_11F_EventScript_GiovanniApproachLeft::
	applymovement LOCALID_SILPH_CO_GIOVANNI, SilphCo_11F_Movement_GiovanniApproachLeft
	applymovement LOCALID_PLAYER, SilphCo_11F_Movement_PlayerFaceGiovanni
	waitmovement 0
	return

SilphCo_11F_EventScript_GiovanniApproachRight::
	applymovement LOCALID_SILPH_CO_GIOVANNI, SilphCo_11F_Movement_GiovanniApproachRight
	waitmovement 0
	return

SilphCo_11F_Movement_GiovanniApproachLeft:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_in_place_faster_left
	step_end

SilphCo_11F_Movement_GiovanniApproachRight:
	walk_down
	walk_down
	walk_down
	step_end

SilphCo_11F_Movement_PlayerFaceGiovanni:
	delay_16
	delay_16
	delay_16
	delay_8
	delay_4
	walk_in_place_faster_right
	step_end

SilphCo_11F_Text_GiovanniIntro::
	.string "Ah, {PLAYER}!\n"
	.string "So we meet again!\p"
	.string "The PRESIDENT and I are discussing\n"
	.string "a vital business proposition.\p"
	.string "Keep your nose out of grown-up\n"
	.string "matters…\p"
	.string "Or, experience a world of pain!$"

SilphCo_11F_Text_GiovanniDefeat::
	.string "Arrgh!!\n"
	.string "I lost again!?$"

SilphCo_11F_Text_GiovanniPostBattle::
	.string "Blast it all!\n"
	.string "You ruined our plans for SILPH!\p"
	.string "But, TEAM ROCKET will never fall!\p"
	.string "{PLAYER}! Never forget that all\n"
	.string "POKéMON exist for TEAM ROCKET!\p"
	.string "…Men! Clear out of this building!$"

SilphCo_11F_Text_GiovanniAfterBattle::
	.string "GIOVANNI: My men have left SILPH.\n"
	.string "Are you satisfied?\p"
	.string "Don't think this is the last you'll\n"
	.string "see of TEAM ROCKET.$"
