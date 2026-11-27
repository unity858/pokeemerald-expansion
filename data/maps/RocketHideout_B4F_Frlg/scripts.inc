@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

.equ NUM_DOOR_GRUNTS_DEFEATED, VAR_TEMP_1

RocketHideout_B4F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, RocketHideout_B4F_OnLoad
	map_script MAP_SCRIPT_ON_RESUME, RocketHideout_B4F_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, RocketHideout_B4F_OnTransition
	.byte 0

RocketHideout_B4F_OnResume::
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, HackStatic_EventScript_TryRemoveCaughtMon
	end

RocketHideout_B4F_OnTransition::
	call RocketHideout_B4F_EventScript_SetupXerneas
	call RocketHideout_B4F_EventScript_SetupYveltal
	call RocketHideout_B4F_EventScript_SetupLiftKey
	end

@ Xerneas and Yveltal: behind the long couch in Giovanni's office, after the League
@ (FLAG_SYS_GAME_CLEAR). The couch back is solid, so each is talked to from the couch
@ seat in front of it (the seat tiles are walkable but block moving north).
RocketHideout_B4F_EventScript_SetupXerneas::
	setupstaticenc STATIC_ENC_XERNEAS, FLAG_TEMP_HIDE_STATIC_MON, FLAG_SYS_GAME_CLEAR
	return

RocketHideout_B4F_EventScript_SetupYveltal::
	setupstaticenc STATIC_ENC_YVELTAL, FLAG_TEMP_HIDE_STATIC_MON_2, FLAG_SYS_GAME_CLEAR
	return

RocketHideout_B4F_EventScript_Xerneas::
	staticencounter STATIC_ENC_XERNEAS, SPECIES_XERNEAS, HackStatic_EventScript_LegendaryBattle

RocketHideout_B4F_EventScript_Yveltal::
	staticencounter STATIC_ENC_YVELTAL, SPECIES_YVELTAL, HackStatic_EventScript_LegendaryBattle

@ ---- Team Rocket (FRLG) ----
@ Giovanni sits on the middle couch seat (19,4) and never leaves; Xerneas (18,3) and Yveltal (20,3)
@ are still talked to from the seats at (18,4) and (20,4), reached from row 5. Beating him sets
@ FLAG_HIDE_ROCKET_HIDEOUT_ROCKETS, which hides every Rocket trainer on B1F-B4F; talking to him
@ again only gives a line. The grunt by the stairs drops the Lift Key (FLAG_GOT_ROCKET_HIDEOUT_LIFT_KEY
@ once picked up), which the hideout elevator needs. The ball is hidden with FLAG_TEMP_1 until then.

RocketHideout_B4F_OnLoad::
	goto_if_set FLAG_HIDE_ROCKET_HIDEOUT_ROCKETS, RocketHideout_B4F_EventScript_OnLoadEnd
	setvar NUM_DOOR_GRUNTS_DEFEATED, 0
	call_if_defeated TRAINER_KANTO_TEAM_ROCKET_GRUNT_16, RocketHideout_B4F_EventScript_CountGruntDefeated
	call_if_defeated TRAINER_KANTO_TEAM_ROCKET_GRUNT_17, RocketHideout_B4F_EventScript_CountGruntDefeated
	call_if_ne NUM_DOOR_GRUNTS_DEFEATED, 2, RocketHideout_B4F_EventScript_SetBarrier
RocketHideout_B4F_EventScript_OnLoadEnd::
	end

RocketHideout_B4F_EventScript_SetupLiftKey::
	call_if_set FLAG_GOT_ROCKET_HIDEOUT_LIFT_KEY, RocketHideout_B4F_EventScript_HideLiftKey
	call_if_not_defeated TRAINER_KANTO_TEAM_ROCKET_GRUNT_18, RocketHideout_B4F_EventScript_HideLiftKey
	return

RocketHideout_B4F_EventScript_HideLiftKey::
	setflag FLAG_TEMP_1
	return

RocketHideout_B4F_EventScript_CountGruntDefeated::
	addvar NUM_DOOR_GRUNTS_DEFEATED, 1
	return

RocketHideout_B4F_EventScript_Giovanni::
	trainerbattle_single TRAINER_KANTO_BOSS_GIOVANNI, RocketHideout_B4F_Text_GiovanniIntro, RocketHideout_B4F_Text_GiovanniDefeat, RocketHideout_B4F_EventScript_DefeatedGiovanni
	msgbox RocketHideout_B4F_Text_GiovanniAfterBattle, MSGBOX_AUTOCLOSE
	end

RocketHideout_B4F_EventScript_DefeatedGiovanni::
	msgbox RocketHideout_B4F_Text_GiovanniPostBattle
	closemessage
	fadescreen FADE_TO_BLACK
	setflag FLAG_HIDE_ROCKET_HIDEOUT_ROCKETS
	removeobject LOCALID_ROCKET_HIDEOUT_B4F_GRUNT_LIFT_KEY
	removeobject LOCALID_ROCKET_HIDEOUT_B4F_GRUNT_DOOR_LEFT
	removeobject LOCALID_ROCKET_HIDEOUT_B4F_GRUNT_DOOR_RIGHT
	fadescreen FADE_FROM_BLACK
	release
	end

RocketHideout_B4F_EventScript_Grunt1::
	trainerbattle_single TRAINER_KANTO_TEAM_ROCKET_GRUNT_18, RocketHideout_B4F_Text_Grunt1Intro, RocketHideout_B4F_Text_Grunt1Defeat, RocketHideout_B4F_EventScript_DefeatedGrunt1
	msgbox RocketHideout_B4F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

RocketHideout_B4F_EventScript_DefeatedGrunt1::
	msgbox RocketHideout_B4F_Text_Grunt1PostBattle
	goto_if_set FLAG_GOT_ROCKET_HIDEOUT_LIFT_KEY, RocketHideout_B4F_EventScript_DefeatedGrunt1End
	clearflag FLAG_TEMP_1
	addobject LOCALID_ROCKET_HIDEOUT_B4F_LIFT_KEY
RocketHideout_B4F_EventScript_DefeatedGrunt1End::
	release
	end

RocketHideout_B4F_EventScript_LiftKey::
	lock
	faceplayer
	checkitemspace ITEM_LIFT_KEY
	goto_if_eq VAR_RESULT, FALSE, EventScript_BagIsFull
	removeobject LOCALID_ROCKET_HIDEOUT_B4F_LIFT_KEY
	giveitem ITEM_LIFT_KEY
	setflag FLAG_GOT_ROCKET_HIDEOUT_LIFT_KEY
	release
	end

RocketHideout_B4F_EventScript_Grunt2::
	trainerbattle_single TRAINER_KANTO_TEAM_ROCKET_GRUNT_16, RocketHideout_B4F_Text_Grunt2Intro, RocketHideout_B4F_Text_Grunt2Defeat, RocketHideout_B4F_EventScript_DefeatedDoorGrunt
	msgbox RocketHideout_B4F_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

RocketHideout_B4F_EventScript_Grunt3::
	trainerbattle_single TRAINER_KANTO_TEAM_ROCKET_GRUNT_17, RocketHideout_B4F_Text_Grunt3Intro, RocketHideout_B4F_Text_Grunt3Defeat, RocketHideout_B4F_EventScript_DefeatedDoorGrunt
	msgbox RocketHideout_B4F_Text_Grunt3PostBattle, MSGBOX_AUTOCLOSE
	end

RocketHideout_B4F_EventScript_DefeatedDoorGrunt::
	setvar NUM_DOOR_GRUNTS_DEFEATED, 0
	call_if_defeated TRAINER_KANTO_TEAM_ROCKET_GRUNT_16, RocketHideout_B4F_EventScript_CountGruntDefeated
	call_if_defeated TRAINER_KANTO_TEAM_ROCKET_GRUNT_17, RocketHideout_B4F_EventScript_CountGruntDefeated
	call_if_eq NUM_DOOR_GRUNTS_DEFEATED, 2, RocketHideout_B4F_EventScript_RemoveBarrier
	call_if_eq NUM_DOOR_GRUNTS_DEFEATED, 2, RocketHideout_B4F_EventScript_DrawMapForBarrierRemoval
	release
	end

RocketHideout_B4F_EventScript_DrawMapForBarrierRemoval::
	playse SE_UNLOCK
	special DrawWholeMapView
	waitse
	return

RocketHideout_B4F_EventScript_SetBarrier::
	setmetatile 17, 12, METATILE_SilphCo_HideoutBarrier_TopLeft_Floor, TRUE
	setmetatile 18, 12, METATILE_SilphCo_HideoutBarrier_TopRight_Floor, TRUE
	setmetatile 17, 13, METATILE_SilphCo_HideoutBarrier_BottomLeft, TRUE
	setmetatile 18, 13, METATILE_SilphCo_HideoutBarrier_BottomRight, TRUE
	setmetatile 17, 14, METATILE_SilphCo_HideoutFloor_ShadeFull, FALSE
	setmetatile 18, 14, METATILE_SilphCo_HideoutFloor_ShadeFull, FALSE
	return

RocketHideout_B4F_EventScript_RemoveBarrier::
	setmetatile 17, 12, METATILE_SilphCo_HideoutFloor_ShadeFull, FALSE
	setmetatile 18, 12, METATILE_SilphCo_HideoutFloor, FALSE
	setmetatile 17, 13, METATILE_SilphCo_HideoutFloor_ShadeFull, FALSE
	setmetatile 18, 13, METATILE_SilphCo_HideoutFloor, FALSE
	setmetatile 17, 14, METATILE_SilphCo_HideoutFloor_ShadeFull, FALSE
	setmetatile 18, 14, METATILE_SilphCo_HideoutFloor, FALSE
	return

RocketHideout_B4F_Text_GiovanniIntro::
	.string "So! I must say, I am impressed you\n"
	.string "got here.\p"
	.string "TEAM ROCKET captures POKéMON from\n"
	.string "around the world.\p"
	.string "They're important tools for keeping\n"
	.string "our criminal enterprise going.\p"
	.string "I am the leader, GIOVANNI!\p"
	.string "For your insolence, you will feel a\n"
	.string "world of pain!$"

RocketHideout_B4F_Text_GiovanniDefeat::
	.string "WHAT!\n"
	.string "This can't be!$"

RocketHideout_B4F_Text_GiovanniPostBattle::
	.string "I see that you raise POKéMON with\n"
	.string "utmost care.\p"
	.string "A child like you would never\n"
	.string "understand what I hope to achieve.\p"
	.string "Very well. I shall send my men\n"
	.string "away… this time.$"

RocketHideout_B4F_Text_GiovanniAfterBattle::
	.string "GIOVANNI: You have beaten me, and\n"
	.string "my men are gone.\p"
	.string "Leave me be, child. I have a great\n"
	.string "deal to think about.$"

RocketHideout_B4F_Text_Grunt2Intro::
	.string "I know you!\n"
	.string "You ruined our plans at MT. MOON!$"

RocketHideout_B4F_Text_Grunt2Defeat::
	.string "Burned again!$"

RocketHideout_B4F_Text_Grunt2PostBattle::
	.string "Do you have something against TEAM\n"
	.string "ROCKET?$"

RocketHideout_B4F_Text_Grunt3Intro::
	.string "How can you not see the beauty of\n"
	.string "our evil?$"

RocketHideout_B4F_Text_Grunt3Defeat::
	.string "Ayaya!$"

RocketHideout_B4F_Text_Grunt3PostBattle::
	.string "BOSS!\n"
	.string "I'm sorry I failed you!$"

RocketHideout_B4F_Text_Grunt1Intro::
	.string "The elevator doesn't work?\n"
	.string "Who has the LIFT KEY?$"

RocketHideout_B4F_Text_Grunt1Defeat::
	.string "No!$"

RocketHideout_B4F_Text_Grunt1PostBattle::
	.string "Oh, no!\n"
	.string "I dropped the LIFT KEY!$"
