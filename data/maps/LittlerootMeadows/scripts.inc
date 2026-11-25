LittlerootMeadows_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LittlerootMeadows_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, LittlerootMeadows_OnResume
	.byte 0

LittlerootMeadows_OnTransition:
	call LittlerootMeadows_EventScript_SetupEnamorus
	end

LittlerootMeadows_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, HackStatic_EventScript_TryRemoveCaughtMon
	end

@ Enamorus (Incarnate), in the middle of the meadow. Shown from the 8th badge.
LittlerootMeadows_EventScript_SetupEnamorus::
	setupstaticenc STATIC_ENC_ENAMORUS, FLAG_TEMP_HIDE_STATIC_MON
	return

LittlerootMeadows_EventScript_Enamorus::
	staticencounter STATIC_ENC_ENAMORUS, SPECIES_ENAMORUS
