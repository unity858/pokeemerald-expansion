@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

FourIsland_House1_Frlg_MapScripts::
	.byte 0

FourIsland_House1_EventScript_FatMan::
	msgbox FourIsland_House1_Text_YoureAwfullyHeavy, MSGBOX_NPC
	end

FourIsland_House1_Text_YoureAwfullyHeavy::
	.string "There! Boing!\n"
	.string "You're awfully heavy!$"
