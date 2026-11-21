@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

SixIsland_House_Frlg_MapScripts::
	.byte 0

SixIsland_House_EventScript_OldMan::
	msgbox SixIsland_House_Text_GoodPlaceForNatureAndHistory, MSGBOX_NPC
	end

SixIsland_House_Text_GoodPlaceForNatureAndHistory::
	.string "There's nothing that young people'd\n"
	.string "find exciting here on this island.\p"
	.string "But, this is a good place in terms\n"
	.string "of nature and history.\p"
	.string "Relax and enjoy your stay.$"
