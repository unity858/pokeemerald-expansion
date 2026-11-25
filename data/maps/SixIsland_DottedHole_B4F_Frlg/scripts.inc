@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

SixIsland_DottedHole_B4F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SixIsland_DottedHole_B4F_Frlg_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SixIsland_DottedHole_B4F_Frlg_OnResume
	.byte 0

SixIsland_DottedHole_B4F_Frlg_OnTransition:
	call SixIsland_DottedHole_B4F_Frlg_EventScript_SetupGougingFire
	end

SixIsland_DottedHole_B4F_Frlg_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, HackStatic_EventScript_TryRemoveCaughtMon
	end

@ Postgame only.
SixIsland_DottedHole_B4F_Frlg_EventScript_SetupGougingFire::
	setupstaticenc STATIC_ENC_GOUGING_FIRE, FLAG_TEMP_HIDE_STATIC_MON, FLAG_SYS_GAME_CLEAR
	return

SixIsland_DottedHole_B4F_Frlg_EventScript_GougingFire::
	staticencounter STATIC_ENC_GOUGING_FIRE, SPECIES_GOUGING_FIRE
