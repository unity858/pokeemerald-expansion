@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

MtEmber_Summit_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, MtEmber_Summit_OnResume
	.byte 0

MtEmber_Summit_OnResume::
	call MtEmber_Summit_EventScript_TryRemoveMoltres
	end

MtEmber_Summit_EventScript_TryRemoveMoltres::
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	return
