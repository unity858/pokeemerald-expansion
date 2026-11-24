@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

NavelRock_Summit_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, NavelRock_Summit_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, NavelRock_Summit_OnResume
	.byte 0

NavelRock_Summit_OnTransition::
	call NavelRock_Summit_EventScript_HideHoOh
	end

NavelRock_Summit_EventScript_HideHoOh::
	setvar VAR_TEMP_1, 1
	return

NavelRock_Summit_OnResume::
	call NavelRock_Summit_EventScript_TryRemoveHoOh
	end

NavelRock_Summit_EventScript_TryRemoveHoOh::
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	return
