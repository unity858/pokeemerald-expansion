@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

BirthIsland_Exterior_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, BirthIsland_Exterior_Frlg_OnResume
	.byte 0

BirthIsland_Exterior_Frlg_OnResume::
	call BirthIsland_Exterior_Frlg_EventScript_TryRemoveDeoxys
	end

BirthIsland_Exterior_Frlg_EventScript_TryRemoveDeoxys::
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	return
