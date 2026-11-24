@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

SevenIsland_SevaultCanyon_House_Frlg_MapScripts::
	.byte 0

SevenIsland_SevaultCanyon_House_EventScript_Chansey::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_CHANSEY, CRY_MODE_NORMAL
	msgbox SevenIsland_SevaultCanyon_House_Text_Chansey
	waitmoncry
	release
	end

SevenIsland_SevaultCanyon_House_Text_Chansey::
	.string "CHANSEY: Chansi! Chansi!$"
