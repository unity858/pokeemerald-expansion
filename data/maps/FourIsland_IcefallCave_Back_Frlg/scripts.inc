@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

FourIsland_IcefallCave_Back_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, FourIsland_IcefallCave_Back_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, FourIsland_IcefallCave_Back_OnTransition
	.byte 0

FourIsland_IcefallCave_Back_OnTransition:
	call FourIsland_IcefallCave_Back_EventScript_SetupArticuno
	end

FourIsland_IcefallCave_Back_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, HackStatic_EventScript_TryRemoveCaughtMon
	end

@ Articuno floats on the pool in the middle of the chamber (elevation 1, the
@ water level), so it can only be reached and spoken to while surfing.
FourIsland_IcefallCave_Back_EventScript_SetupArticuno::
	setupstaticenc STATIC_ENC_ARTICUNO, FLAG_TEMP_HIDE_STATIC_MON
	return

FourIsland_IcefallCave_Back_EventScript_Articuno::
	staticencounter STATIC_ENC_ARTICUNO, SPECIES_ARTICUNO, HackStatic_EventScript_GyaooBattle
