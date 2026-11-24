@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

Route12_NorthEntrance_2F_Frlg_MapScripts::
	.byte 0

Route12_NorthEntrance_2F_EventScript_LeftBinoculars::
	msgbox Route12_NorthEntrance_2F_Text_TheresManFishing, MSGBOX_SIGN
	end

Route12_NorthEntrance_2F_EventScript_RightBinoculars::
	msgbox Route12_NorthEntrance_2F_Text_ItsPokemonTower, MSGBOX_SIGN
	end

Route12_NorthEntrance_2F_EventScript_Lass::
	lock
	faceplayer
	goto Route12_NorthEntrance_2F_EventScript_ExplainTM27

Route12_NorthEntrance_2F_EventScript_ExplainTM27::
	msgbox Route12_NorthEntrance_2F_Text_ExplainTM27
	release
	end

Route12_NorthEntrance_2F_Text_ExplainTM27::
	.string "TM27 is a move called RETURN…\p"
	.string "If you treat your POKéMON good,\n"
	.string "it will return your love by working\l"
	.string "its hardest in battle.$"


Route12_NorthEntrance_2F_Text_TheresManFishing::
	.string "Let's see what the binoculars have\n"
	.string "to show…\p"
	.string "There's a man fishing!$"


Route12_NorthEntrance_2F_Text_ItsPokemonTower::
	.string "Let's see what the binoculars have\n"
	.string "to show…\p"
	.string "It's POKéMON TOWER!$"
