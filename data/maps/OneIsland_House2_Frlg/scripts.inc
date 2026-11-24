@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

OneIsland_House2_Frlg_MapScripts::
	.byte 0

OneIsland_House2_EventScript_Lass::
	msgbox OneIsland_House2_Text_IWantToStayHereForever, MSGBOX_NPC
	end

OneIsland_House2_Text_IWantToStayHereForever::
	.string "Young people all want to go off to\n"
	.string "big cities.\p"
	.string "But I want to stay here forever!$"
