@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

MtEmber_Summit_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, MtEmber_Summit_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, MtEmber_Summit_OnTransition
	.byte 0

MtEmber_Summit_OnTransition:
	call MtEmber_Summit_EventScript_SetupMoltres
	end

MtEmber_Summit_OnResume::
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, HackStatic_EventScript_TryRemoveCaughtMon
	end

MtEmber_Summit_EventScript_SetupMoltres::
	setflag FLAG_TEMP_HIDE_STATIC_MON
	goto_if_unset FLAG_BADGE08_GET, Common_EventScript_NopReturn
	goto_if_set FLAG_CAUGHT_MOLTRES, Common_EventScript_NopReturn
	goto_if_set FLAG_DEFEATED_MOLTRES, Common_EventScript_NopReturn
	clearflag FLAG_TEMP_HIDE_STATIC_MON
	return

MtEmber_Summit_EventScript_Moltres::
	lock
	faceplayer
	setvar VAR_0x8004, SPECIES_MOLTRES
	setvar VAR_0x8006, ITEM_NONE
	waitse
	playmoncry SPECIES_MOLTRES, CRY_MODE_ENCOUNTER
	message Text_Gyaoo
	waitmessage
	waitmoncry
	delay 10
	playbgm MUS_RG_ENCOUNTER_GYM_LEADER, 0
	waitbuttonpress
	call HackStatic_EventScript_LegendaryBattleNoCry
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, MtEmber_Summit_EventScript_CaughtMoltres
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, MtEmber_Summit_EventScript_DefeatedMoltres
	setvar VAR_0x8004, SPECIES_MOLTRES
	goto Common_EventScript_LegendaryFlewAway
	end

MtEmber_Summit_EventScript_DefeatedMoltres::
	setflag FLAG_DEFEATED_MOLTRES
	setvar VAR_0x8004, SPECIES_MOLTRES
	goto Common_EventScript_LegendaryFlewAway
	end

MtEmber_Summit_EventScript_CaughtMoltres::
	setflag FLAG_CAUGHT_MOLTRES
	release
	end
