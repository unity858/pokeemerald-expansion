@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

.equ NUM_SWITCHES_PRESSED, VAR_TEMP_8

SevenIsland_SevaultCanyon_TanobyKey_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SevenIsland_SevaultCanyon_TanobyKey_OnTransition
	.byte 0

SevenIsland_SevaultCanyon_TanobyKey_OnTransition::
	call SevenIsland_SevaultCanyon_TanobyKey_EventScript_MoveBouldersToSolvedPos
	setvar VAR_TEMP_1, 0
	setvar VAR_TEMP_2, 0
	setvar VAR_TEMP_3, 0
	setvar VAR_TEMP_4, 0
	setvar VAR_TEMP_5, 0
	setvar VAR_TEMP_6, 0
	setvar VAR_TEMP_7, 0
	setvar NUM_SWITCHES_PRESSED, 0
	end

SevenIsland_SevaultCanyon_TanobyKey_EventScript_MoveBouldersToSolvedPos::
	setobjectxyperm LOCALID_TANOBY_KEY_BOULDER1, 7, 2
	setobjectxyperm LOCALID_TANOBY_KEY_BOULDER2, 4, 4
	setobjectxyperm LOCALID_TANOBY_KEY_BOULDER3, 10, 4
	setobjectxyperm LOCALID_TANOBY_KEY_BOULDER4, 5, 6
	setobjectxyperm LOCALID_TANOBY_KEY_BOULDER5, 9, 6
	setobjectxyperm LOCALID_TANOBY_KEY_BOULDER6, 5, 8
	setobjectxyperm LOCALID_TANOBY_KEY_BOULDER7, 9, 8
	return
