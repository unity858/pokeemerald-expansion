@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

SixIsland_Harbor_Frlg_MapScripts::
	.byte 0

@ Seagallop ferry (data/scripts/interregion_ferry.inc)
SixIsland_Harbor_EventScript_Sailor::
	setvar VAR_0x8004, SEAGALLOP_SIX_ISLAND
	goto InterRegionFerry_EventScript_SeagallopSailor
	end
