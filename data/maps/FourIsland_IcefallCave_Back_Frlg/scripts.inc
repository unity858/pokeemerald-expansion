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
	setflag FLAG_TEMP_HIDE_STATIC_MON
	goto_if_unset FLAG_BADGE08_GET, Common_EventScript_NopReturn
	goto_if_set FLAG_CAUGHT_ARTICUNO, Common_EventScript_NopReturn
	goto_if_set FLAG_DEFEATED_ARTICUNO, Common_EventScript_NopReturn
	clearflag FLAG_TEMP_HIDE_STATIC_MON
	return

FourIsland_IcefallCave_Back_EventScript_Articuno::
	lock
	faceplayer
	setvar VAR_0x8004, SPECIES_ARTICUNO
	setvar VAR_0x8006, ITEM_NONE
	waitse
	playmoncry SPECIES_ARTICUNO, CRY_MODE_ENCOUNTER
	message Text_Gyaoo
	waitmessage
	waitmoncry
	delay 10
	playbgm MUS_RG_ENCOUNTER_GYM_LEADER, 0
	waitbuttonpress
	call HackStatic_EventScript_LegendaryBattleNoCry
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, FourIsland_IcefallCave_Back_EventScript_CaughtArticuno
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, FourIsland_IcefallCave_Back_EventScript_DefeatedArticuno
	setvar VAR_0x8004, SPECIES_ARTICUNO
	goto Common_EventScript_LegendaryFlewAway
	end

FourIsland_IcefallCave_Back_EventScript_DefeatedArticuno::
	setflag FLAG_DEFEATED_ARTICUNO
	setvar VAR_0x8004, SPECIES_ARTICUNO
	goto Common_EventScript_LegendaryFlewAway
	end

FourIsland_IcefallCave_Back_EventScript_CaughtArticuno::
	setflag FLAG_CAUGHT_ARTICUNO
	release
	end
