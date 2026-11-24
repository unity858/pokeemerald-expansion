@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

CeladonCity_House1_Frlg_MapScripts::
	.byte 0

CeladonCity_House1_EventScript_RocketChief::
	msgbox CeladonCity_House1_Text_SlotsReelInTheDough, MSGBOX_NPC
	end

CeladonCity_House1_Text_SlotsReelInTheDough::
	.string "Hehehe!\p"
	.string "The slots just reel in the dough,\n"
	.string "big-time!$"
