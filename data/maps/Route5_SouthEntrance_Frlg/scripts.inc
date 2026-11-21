@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

Route5_SouthEntrance_Frlg_MapScripts::
	.byte 0

Route5_SouthEntrance_EventScript_Guard::
	msgbox Route5_SouthEntrance_Text_HiHowsItGoing, MSGBOX_NPC
	end

Route5_SouthEntrance_Text_HiHowsItGoing::
	.string "Hi, how's it going?$"
