@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.
@ Zekrom (barrel room, northeast) and Miraidon (in front of the south generator) are
@ hack statics, after the League (FLAG_SYS_GAME_CLEAR).

PowerPlant_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, PowerPlant_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, PowerPlant_OnTransition
	.byte 0

PowerPlant_OnResume::
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, HackStatic_EventScript_TryRemoveCaughtMon
	end

PowerPlant_OnTransition::
	call PowerPlant_EventScript_SetupZekrom
	call PowerPlant_EventScript_SetupMiraidon
	end

@ Postgame only.
PowerPlant_EventScript_SetupZekrom::
	setupstaticenc STATIC_ENC_ZEKROM, FLAG_TEMP_HIDE_STATIC_MON, FLAG_SYS_GAME_CLEAR
	return

PowerPlant_EventScript_SetupMiraidon::
	setupstaticenc STATIC_ENC_MIRAIDON, FLAG_TEMP_HIDE_STATIC_MON_2, FLAG_SYS_GAME_CLEAR
	return

PowerPlant_EventScript_Zekrom::
	staticencounter STATIC_ENC_ZEKROM, SPECIES_ZEKROM, HackStatic_EventScript_LegendaryBattle

PowerPlant_EventScript_Miraidon::
	staticencounter STATIC_ENC_MIRAIDON, SPECIES_MIRAIDON, HackStatic_EventScript_LegendaryBattle
