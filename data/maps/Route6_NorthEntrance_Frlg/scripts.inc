@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

Route6_NorthEntrance_Frlg_MapScripts::
	.byte 0

Route6_NorthEntrance_EventScript_Guard::
	msgbox Route6_NorthEntrance_Text_HiHowsItGoing, MSGBOX_NPC
	end

Route6_NorthEntrance_Text_HiHowsItGoing::
	.string "Hi, how's it going?$"
