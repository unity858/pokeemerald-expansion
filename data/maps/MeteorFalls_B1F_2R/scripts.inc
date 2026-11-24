MeteorFalls_B1F_2R_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MeteorFalls_B1F_2R_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, MeteorFalls_B1F_2R_OnResume
	.byte 0

MeteorFalls_B1F_2R_OnTransition:
	call MeteorFalls_B1F_2R_EventScript_SetupCobalion
	end

MeteorFalls_B1F_2R_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, HackStatic_EventScript_TryRemoveCaughtMon
	end

@ Cobalion: in the middle of the enlarged chamber beyond the pond. After the 8th badge.
MeteorFalls_B1F_2R_EventScript_SetupCobalion::
	setflag FLAG_TEMP_HIDE_STATIC_MON
	goto_if_unset FLAG_BADGE08_GET, Common_EventScript_NopReturn
	goto_if_set FLAG_CAUGHT_COBALION, Common_EventScript_NopReturn
	goto_if_set FLAG_DEFEATED_COBALION, Common_EventScript_NopReturn
	clearflag FLAG_TEMP_HIDE_STATIC_MON
	return

MeteorFalls_B1F_2R_EventScript_Cobalion::
	lock
	faceplayer
	setvar VAR_0x8004, SPECIES_COBALION
	setvar VAR_0x8006, ITEM_NONE
	call HackStatic_EventScript_LegendaryBattle
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, MeteorFalls_B1F_2R_EventScript_CaughtCobalion
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, MeteorFalls_B1F_2R_EventScript_DefeatedCobalion
	setvar VAR_0x8004, SPECIES_COBALION
	goto Common_EventScript_LegendaryFlewAway
	end

MeteorFalls_B1F_2R_EventScript_DefeatedCobalion::
	setflag FLAG_DEFEATED_COBALION
	setvar VAR_0x8004, SPECIES_COBALION
	goto Common_EventScript_LegendaryFlewAway
	end

MeteorFalls_B1F_2R_EventScript_CaughtCobalion::
	setflag FLAG_CAUGHT_COBALION
	release
	end
