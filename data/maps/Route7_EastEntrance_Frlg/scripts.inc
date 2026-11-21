@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

Route7_EastEntrance_Frlg_MapScripts::
	.byte 0

Route7_EastEntrance_EventScript_Guard::
	msgbox Route7_EastEntrance_Text_HiHowsItGoing, MSGBOX_NPC
	end

Route7_EastEntrance_Text_HiHowsItGoing::
	.string "Hi, how's it going?$"
