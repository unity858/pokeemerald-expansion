@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

IndigoPlateau_Exterior_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, IndigoPlateau_Exterior_OnTransition
	.byte 0

IndigoPlateau_Exterior_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_INDIGO_PLATEAU_EXTERIOR
	end

@ Portal ported from R.O.W.E. (NewMauville_EventScript_WarptoPowerPlant): talk to it,
@ Hoopa cries, then a normal warp (SE_EXIT + fade) to the paired portal.
IndigoPlateau_Exterior_EventScript_PortalToSpearPillar::
	lock
	waitse
	playmoncry SPECIES_HOOPA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	warp MAP_SPEAR_PILLAR, 15, 13
	waitstate
	release
	end
