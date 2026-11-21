@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

OneIsland_KindleRoad_Frlg_MapScripts::
	.byte 0

OneIsland_KindleRoad_EventScript_RouteSign::
	msgbox OneIsland_KindleRoad_Text_RouteSign, MSGBOX_SIGN
	end

OneIsland_KindleRoad_EventScript_EmberSpaSign::
	msgbox OneIsland_KindleRoad_Text_EmberSpaSign, MSGBOX_SIGN
	end

OneIsland_KindleRoad_Text_RouteSign::
	.string "This is KINDLE ROAD.\p"
	.string "Go straight for MT. EMBER.$"


OneIsland_KindleRoad_Text_EmberSpaSign::
	.string "Light the Fire in Your Heart!\n"
	.string "EMBER SPA$"
