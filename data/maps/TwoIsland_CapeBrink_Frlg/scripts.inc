@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

TwoIsland_CapeBrink_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, TwoIsland_CapeBrink_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, TwoIsland_CapeBrink_OnResume
	.byte 0

TwoIsland_CapeBrink_OnTransition:
	call TwoIsland_CapeBrink_EventScript_SetupTapuKoko
	end

TwoIsland_CapeBrink_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, HackStatic_EventScript_TryRemoveCaughtMon
	end

TwoIsland_CapeBrink_EventScript_SetupTapuKoko::
	setupstaticenc STATIC_ENC_TAPU_KOKO, FLAG_TEMP_HIDE_STATIC_MON
	return

TwoIsland_CapeBrink_EventScript_TapuKoko::
	staticencounter STATIC_ENC_TAPU_KOKO, SPECIES_TAPU_KOKO
