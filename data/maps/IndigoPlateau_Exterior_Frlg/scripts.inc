@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

IndigoPlateau_Exterior_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, IndigoPlateau_Exterior_OnTransition
	.byte 0

IndigoPlateau_Exterior_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_INDIGO_PLATEAU_EXTERIOR
	end
