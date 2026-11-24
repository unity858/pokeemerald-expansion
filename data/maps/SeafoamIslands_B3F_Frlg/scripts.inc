@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

SeafoamIslands_B3F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SeafoamIslands_B3F_OnTransition
	.byte 0

SeafoamIslands_B3F_OnTransition::
	call SeafoamIslands_B3F_EventScript_SetNoCurrentLayout
	end

SeafoamIslands_B3F_EventScript_SetNoCurrentLayout::
	setmaplayoutindex LAYOUT_SEAFOAM_ISLANDS_B3F_CURRENT_STOPPED
	return
