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
	setupstaticenc STATIC_ENC_MOLTRES, FLAG_TEMP_HIDE_STATIC_MON
	return

MtEmber_Summit_EventScript_Moltres::
	staticencounter STATIC_ENC_MOLTRES, SPECIES_MOLTRES, HackStatic_EventScript_GyaooBattle
