@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

.equ NUM_BOULDERS_PRESENT, VAR_TEMP_2

SeafoamIslands_B4F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SeafoamIslands_B4F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SeafoamIslands_B4F_OnResume
	map_script MAP_SCRIPT_ON_LOAD, SeafoamIslands_B4F_OnLoad
	.byte 0

SeafoamIslands_B4F_OnResume::
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, HackStatic_EventScript_TryRemoveCaughtMon
	end

SeafoamIslands_B4F_OnTransition::
	call SeafoamIslands_B4F_EventScript_SetupArticuno
	call SeafoamIslands_B4F_EventScript_SetNoCurrentLayout
	end

SeafoamIslands_B4F_EventScript_SetNoCurrentLayout::
	setmaplayoutindex LAYOUT_SEAFOAM_ISLANDS_B4F_CURRENT_STOPPED
	return

SeafoamIslands_B4F_OnLoad::
	setvar NUM_BOULDERS_PRESENT, 0
	goto_if_eq NUM_BOULDERS_PRESENT, 2, SeafoamIslands_B4F_EventScript_SetCalmWaterNearStairs
	end

SeafoamIslands_B4F_EventScript_SetCalmWaterNearStairs::
	setmetatile 12, 14, METATILE_GeneralFrlg_CalmWater, 0
	setmetatile 13, 14, METATILE_GeneralFrlg_CalmWater, 0
	end

SeafoamIslands_B4F_EventScript_BoulderHintSign::
	msgbox SeafoamIslands_B4F_Text_BouldersMightChangeWaterFlow, MSGBOX_SIGN
	end

SeafoamIslands_B4F_EventScript_FastCurrentSign::
	msgbox SeafoamIslands_B4F_Text_DangerFastCurrent, MSGBOX_SIGN
	end

SeafoamIslands_B4F_Text_BouldersMightChangeWaterFlow::
	.string "Hint: Boulders might change the\n"
	.string "flow of water.$"


SeafoamIslands_B4F_Text_DangerFastCurrent::
	.string "DANGER\n"
	.string "Fast current!$"

SeafoamIslands_B4F_EventScript_SetupArticuno::
	setflag FLAG_TEMP_HIDE_STATIC_MON
	goto_if_unset FLAG_BADGE08_GET, Common_EventScript_NopReturn
	goto_if_set FLAG_CAUGHT_ARTICUNO, Common_EventScript_NopReturn
	goto_if_set FLAG_DEFEATED_ARTICUNO, Common_EventScript_NopReturn
	clearflag FLAG_TEMP_HIDE_STATIC_MON
	return

SeafoamIslands_B4F_EventScript_Articuno::
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
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, SeafoamIslands_B4F_EventScript_CaughtArticuno
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, SeafoamIslands_B4F_EventScript_DefeatedArticuno
	setvar VAR_0x8004, SPECIES_ARTICUNO
	goto Common_EventScript_LegendaryFlewAway
	end

SeafoamIslands_B4F_EventScript_DefeatedArticuno::
	setflag FLAG_DEFEATED_ARTICUNO
	setvar VAR_0x8004, SPECIES_ARTICUNO
	goto Common_EventScript_LegendaryFlewAway
	end

SeafoamIslands_B4F_EventScript_CaughtArticuno::
	setflag FLAG_CAUGHT_ARTICUNO
	release
	end
