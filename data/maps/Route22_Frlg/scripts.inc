@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

Route22_Frlg_MapScripts::
	.byte 0

Route22_EventScript_LeagueGateSign::
	msgbox Route22_Text_LeagueGateSign, MSGBOX_SIGN
	end

Route22_Text_LeagueGateSign::
	.string "POKéMON LEAGUE\n"
	.string "Front Gate$"
