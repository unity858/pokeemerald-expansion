@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

NavelRock_Base_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, NavelRock_Base_Frlg_OnResume
	.byte 0

NavelRock_Base_Frlg_OnResume::
	call NavelRock_Base_Frlg_EventScript_TryRemoveLugia
	end

NavelRock_Base_Frlg_EventScript_TryRemoveLugia::
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	return
