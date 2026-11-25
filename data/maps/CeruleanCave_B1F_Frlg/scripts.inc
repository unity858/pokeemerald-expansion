@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.
@ Mewtwo is restored as a hack static at its FRLG spot, after the League
@ (FLAG_SYS_GAME_CLEAR), holding Mewtwonite Y; Mewtwonite X is an item ball beside it.

CeruleanCave_B1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, CeruleanCave_B1F_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, CeruleanCave_B1F_OnTransition
	.byte 0

CeruleanCave_B1F_OnResume::
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, HackStatic_EventScript_TryRemoveCaughtMon
	end

CeruleanCave_B1F_OnTransition::
	call CeruleanCave_B1F_EventScript_SetupMewtwo
	end

CeruleanCave_B1F_EventScript_SetupMewtwo::
	setupstaticenc STATIC_ENC_MEWTWO, FLAG_TEMP_HIDE_STATIC_MON, FLAG_SYS_GAME_CLEAR
	return

CeruleanCave_B1F_EventScript_Mewtwo::
	staticencounter STATIC_ENC_MEWTWO, SPECIES_MEWTWO, HackStatic_EventScript_MewtwoBattle, ITEM_MEWTWONITE_Y
