@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

FourIsland_IcefallCave_1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, FourIsland_IcefallCave_1F_OnResume
	.byte 0

FourIsland_IcefallCave_1F_OnResume::
	setstepcallback STEP_CB_ICEFALL_CAVE
	end
