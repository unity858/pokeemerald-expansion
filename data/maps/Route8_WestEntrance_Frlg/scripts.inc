@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

Route8_WestEntrance_Frlg_MapScripts::
	.byte 0

Route8_WestEntrance_EventScript_Guard::
	msgbox Route8_WestEntrance_Text_HiHowsItGoing, MSGBOX_NPC
	end

Route8_WestEntrance_Text_HiHowsItGoing::
	.string "Hi, how's it going?$"
