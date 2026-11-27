@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

RocketHideout_B1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, RocketHideout_B1F_OnLoad
	.byte 0

@ The barrier in front of the elevator corridor stays shut until the grunt next to it is beaten
@ (FRLG). Once the hideout is cleared (the grunts are gone) it is always open.
RocketHideout_B1F_OnLoad::
	goto_if_set FLAG_HIDE_ROCKET_HIDEOUT_ROCKETS, RocketHideout_B1F_EventScript_OnLoadEnd
	call_if_not_defeated TRAINER_KANTO_TEAM_ROCKET_GRUNT_12, RocketHideout_B1F_EventScript_SetBarrier
RocketHideout_B1F_EventScript_OnLoadEnd::
	end

@ ---- Team Rocket trainers (FRLG); hidden by FLAG_HIDE_ROCKET_HIDEOUT_ROCKETS once Giovanni is beaten ----

RocketHideout_B1F_EventScript_Grunt2::
	trainerbattle_single TRAINER_KANTO_TEAM_ROCKET_GRUNT_9, RocketHideout_B1F_Text_Grunt2Intro, RocketHideout_B1F_Text_Grunt2Defeat
	msgbox RocketHideout_B1F_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

RocketHideout_B1F_Text_Grunt2Intro::
	.string "You broke into TEAM ROCKET's\n"
	.string "operation? What nerve!$"

RocketHideout_B1F_Text_Grunt2Defeat::
	.string "Boom!$"

RocketHideout_B1F_Text_Grunt2PostBattle::
	.string "You're not going to get away with\n"
	.string "this, brat!$"

RocketHideout_B1F_EventScript_Grunt1::
	trainerbattle_single TRAINER_KANTO_TEAM_ROCKET_GRUNT_8, RocketHideout_B1F_Text_Grunt1Intro, RocketHideout_B1F_Text_Grunt1Defeat
	msgbox RocketHideout_B1F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

RocketHideout_B1F_Text_Grunt1Intro::
	.string "Who are you?\n"
	.string "How did you get here?$"

RocketHideout_B1F_Text_Grunt1Defeat::
	.string "Oww!\n"
	.string "Beaten!$"

RocketHideout_B1F_Text_Grunt1PostBattle::
	.string "Blast it… You're dissing TEAM\n"
	.string "ROCKET, aren't you?$"

RocketHideout_B1F_EventScript_Grunt4::
	trainerbattle_single TRAINER_KANTO_TEAM_ROCKET_GRUNT_11, RocketHideout_B1F_Text_Grunt4Intro, RocketHideout_B1F_Text_Grunt4Defeat
	msgbox RocketHideout_B1F_Text_Grunt4PostBattle, MSGBOX_AUTOCLOSE
	end

RocketHideout_B1F_Text_Grunt4Intro::
	.string "Why did you come here?$"

RocketHideout_B1F_Text_Grunt4Defeat::
	.string "This won't do!$"

RocketHideout_B1F_Text_Grunt4PostBattle::
	.string "Okay, I'll talk…\n"
	.string "Take the elevator to see my BOSS.$"

RocketHideout_B1F_EventScript_Grunt3::
	trainerbattle_single TRAINER_KANTO_TEAM_ROCKET_GRUNT_10, RocketHideout_B1F_Text_Grunt3Intro, RocketHideout_B1F_Text_Grunt3Defeat
	msgbox RocketHideout_B1F_Text_Grunt3PostBattle, MSGBOX_AUTOCLOSE
	end

RocketHideout_B1F_Text_Grunt3Intro::
	.string "Intruder alert!$"

RocketHideout_B1F_Text_Grunt3Defeat::
	.string "I can't do it!$"

RocketHideout_B1F_Text_Grunt3PostBattle::
	.string "SILPH SCOPE? Humph!\n"
	.string "I don't know where it is.$"

RocketHideout_B1F_EventScript_Grunt5::
	trainerbattle_single TRAINER_KANTO_TEAM_ROCKET_GRUNT_12, RocketHideout_B1F_Text_Grunt5Intro, RocketHideout_B1F_Text_Grunt5Defeat, RocketHideout_B1F_EventScript_DefeatedGrunt5
	msgbox RocketHideout_B1F_Text_Grunt5PostBattle, MSGBOX_AUTOCLOSE
	end

RocketHideout_B1F_EventScript_DefeatedGrunt5::
	call RocketHideout_B1F_EventScript_RemoveBarrier
	playse SE_UNLOCK
	special DrawWholeMapView
	waitse
	release
	end

RocketHideout_B1F_EventScript_SetBarrier::
	setmetatile 20, 19, METATILE_SilphCo_HideoutBarrier_TopLeft_Floor, TRUE
	setmetatile 21, 19, METATILE_SilphCo_HideoutBarrier_TopRight_Floor, TRUE
	setmetatile 20, 20, METATILE_SilphCo_HideoutBarrier_BottomLeft, TRUE
	setmetatile 21, 20, METATILE_SilphCo_HideoutBarrier_BottomRight, TRUE
	setmetatile 20, 21, METATILE_SilphCo_HideoutFloor_ShadeFull, FALSE
	setmetatile 21, 21, METATILE_SilphCo_HideoutFloor_ShadeFull, FALSE
	return

RocketHideout_B1F_EventScript_RemoveBarrier::
	setmetatile 20, 19, METATILE_SilphCo_HideoutFloor_ShadeFull, FALSE
	setmetatile 21, 19, METATILE_SilphCo_HideoutFloor, FALSE
	setmetatile 20, 20, METATILE_SilphCo_HideoutFloor_ShadeFull, FALSE
	setmetatile 21, 20, METATILE_SilphCo_HideoutFloor, FALSE
	setmetatile 20, 21, METATILE_SilphCo_HideoutFloor_ShadeFull, FALSE
	setmetatile 21, 21, METATILE_SilphCo_HideoutFloor, FALSE
	return

RocketHideout_B1F_Text_Grunt5Intro::
	.string "Are you lost, you little mouse?$"

RocketHideout_B1F_Text_Grunt5Defeat::
	.string "Why…?$"

RocketHideout_B1F_Text_Grunt5PostBattle::
	.string "Uh-oh, that ruckus somehow opened\n"
	.string "the door!$"
