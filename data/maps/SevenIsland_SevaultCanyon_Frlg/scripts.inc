@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

SevenIsland_SevaultCanyon_Frlg_MapScripts::
	.byte 0

SevenIsland_SevaultCanyon_EventScript_RouteSign::
	msgbox SevenIsland_SevaultCanyon_Text_RouteSign, MSGBOX_SIGN
	end

SevenIsland_SevaultCanyon_Text_RouteSign::
	.string "SEVAULT CANYON\n"
	.string "TANOBY RUINS AHEAD$"
