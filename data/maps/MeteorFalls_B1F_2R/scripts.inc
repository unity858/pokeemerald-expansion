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
	setupstaticenc STATIC_ENC_COBALION, FLAG_TEMP_HIDE_STATIC_MON
	return

MeteorFalls_B1F_2R_EventScript_Cobalion::
	staticencounter STATIC_ENC_COBALION, SPECIES_COBALION
