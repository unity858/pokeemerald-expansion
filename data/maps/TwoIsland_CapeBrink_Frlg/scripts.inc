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
	setflag FLAG_TEMP_HIDE_STATIC_MON
	goto_if_unset FLAG_BADGE08_GET, Common_EventScript_NopReturn
	goto_if_set FLAG_CAUGHT_TAPU_KOKO, Common_EventScript_NopReturn
	goto_if_set FLAG_DEFEATED_TAPU_KOKO, Common_EventScript_NopReturn
	clearflag FLAG_TEMP_HIDE_STATIC_MON
	return

TwoIsland_CapeBrink_EventScript_TapuKoko::
	lock
	faceplayer
	setvar VAR_0x8004, SPECIES_TAPU_KOKO
	setvar VAR_0x8006, ITEM_NONE
	call HackStatic_EventScript_LegendaryBattle
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, TwoIsland_CapeBrink_EventScript_CaughtTapuKoko
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, TwoIsland_CapeBrink_EventScript_DefeatedTapuKoko
	setvar VAR_0x8004, SPECIES_TAPU_KOKO
	goto Common_EventScript_LegendaryFlewAway
	end

TwoIsland_CapeBrink_EventScript_DefeatedTapuKoko::
	setflag FLAG_DEFEATED_TAPU_KOKO
	setvar VAR_0x8004, SPECIES_TAPU_KOKO
	goto Common_EventScript_LegendaryFlewAway
	end

TwoIsland_CapeBrink_EventScript_CaughtTapuKoko::
	setflag FLAG_CAUGHT_TAPU_KOKO
	release
	end
