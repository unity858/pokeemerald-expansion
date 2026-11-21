@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

PowerPlant_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, PowerPlant_OnResume
	.byte 0

PowerPlant_OnResume::
	call PowerPlant_EventScript_TryRemoveStaticMon
	end

PowerPlant_EventScript_TryRemoveStaticMon::
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	return
