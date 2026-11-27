SpearPillar_MapScripts::
	.byte 0

@ Portal ported from R.O.W.E. (NewMauville_EventScript_WarptoPowerPlant): talk to it,
@ Hoopa cries, then a normal warp (SE_EXIT + fade) to the paired portal.
SpearPillar_EventScript_PortalToIndigoPlateau::
	lock
	waitse
	playmoncry SPECIES_HOOPA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	warp MAP_INDIGO_PLATEAU_EXTERIOR, 13, 8
	waitstate
	release
	end
