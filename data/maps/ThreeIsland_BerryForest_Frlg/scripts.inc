@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

ThreeIsland_BerryForest_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ThreeIsland_BerryForest_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, ThreeIsland_BerryForest_OnResume
	.byte 0

ThreeIsland_BerryForest_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, HackStatic_EventScript_TryRemoveCaughtMon
	end

ThreeIsland_BerryForest_OnTransition::
	call ThreeIsland_BerryForest_EventScript_SetupTapuBulu
	setescapewarp MAP_THREE_ISLAND_BOND_BRIDGE, 12, 6
	end

ThreeIsland_BerryForest_EventScript_WelcomeSign::
	msgbox ThreeIsland_BerryForest_Text_WelcomeToBerryForest, MSGBOX_SIGN
	end

ThreeIsland_BerryForest_EventScript_BewareSign::
	msgbox ThreeIsland_BerryForest_Text_BewareWildBerryLovingMons, MSGBOX_SIGN
	end

ThreeIsland_BerryForest_Text_WelcomeToBerryForest::
	.string "Welcome to the BERRY FOREST\p"
	.string "Be friendly and share BERRIES with\n"
	.string "others and POKéMON.$"


ThreeIsland_BerryForest_Text_BewareWildBerryLovingMons::
	.string "Beware of wild, BERRY-loving\n"
	.string "POKéMON!$"

ThreeIsland_BerryForest_EventScript_SetupTapuBulu::
	setflag FLAG_TEMP_HIDE_STATIC_MON
	goto_if_unset FLAG_BADGE08_GET, Common_EventScript_NopReturn
	goto_if_set FLAG_CAUGHT_TAPU_BULU, Common_EventScript_NopReturn
	goto_if_set FLAG_DEFEATED_TAPU_BULU, Common_EventScript_NopReturn
	clearflag FLAG_TEMP_HIDE_STATIC_MON
	return

ThreeIsland_BerryForest_EventScript_TapuBulu::
	lock
	faceplayer
	setvar VAR_0x8004, SPECIES_TAPU_BULU
	setvar VAR_0x8006, ITEM_NONE
	call HackStatic_EventScript_LegendaryBattle
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, ThreeIsland_BerryForest_EventScript_CaughtTapuBulu
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, ThreeIsland_BerryForest_EventScript_DefeatedTapuBulu
	setvar VAR_0x8004, SPECIES_TAPU_BULU
	goto Common_EventScript_LegendaryFlewAway
	end

ThreeIsland_BerryForest_EventScript_DefeatedTapuBulu::
	setflag FLAG_DEFEATED_TAPU_BULU
	setvar VAR_0x8004, SPECIES_TAPU_BULU
	goto Common_EventScript_LegendaryFlewAway
	end

ThreeIsland_BerryForest_EventScript_CaughtTapuBulu::
	setflag FLAG_CAUGHT_TAPU_BULU
	release
	end
