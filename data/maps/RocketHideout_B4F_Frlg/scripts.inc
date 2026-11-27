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

RocketHideout_B4F_OnLoad::
	setvar NUM_DOOR_GRUNTS_DEFEATED, 0
	call RocketHideout_B4F_EventScript_CountGruntDefeated
	call RocketHideout_B4F_EventScript_CountGruntDefeated
	call_if_ne NUM_DOOR_GRUNTS_DEFEATED, 2, RocketHideout_B4F_EventScript_SetBarrier
	end

RocketHideout_B4F_EventScript_CountGruntDefeated::
	addvar NUM_DOOR_GRUNTS_DEFEATED, 1
	return

RocketHideout_B4F_EventScript_SetBarrier::
	setmetatile 17, 12, METATILE_SilphCo_HideoutBarrier_TopLeft_Floor, 1
	setmetatile 18, 12, METATILE_SilphCo_HideoutBarrier_TopRight_Floor, 1
	setmetatile 17, 13, METATILE_SilphCo_HideoutBarrier_BottomLeft, 1
	setmetatile 18, 13, METATILE_SilphCo_HideoutBarrier_BottomRight, 1
	setmetatile 17, 14, METATILE_SilphCo_HideoutFloor_ShadeFull, 0
	setmetatile 18, 14, METATILE_SilphCo_HideoutFloor_ShadeFull, 0
	return
