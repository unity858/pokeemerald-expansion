@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

Route10_Frlg_MapScripts::
	.byte 0

Route10_EventScript_NorthRockTunnelSign::
	msgbox Route10_Text_RockTunnelDetourToLavender, MSGBOX_SIGN
	end

Route10_EventScript_SouthRockTunnelSign::
	msgbox Route10_Text_RockTunnel, MSGBOX_SIGN
	end

Route10_EventScript_PowerPlantSign::
	msgbox Route10_Text_PowerPlant, MSGBOX_SIGN
	end

Route10_Text_RockTunnelDetourToLavender::
	.string "ROCK TUNNEL\n"
	.string "Detour to LAVENDER TOWN$"


Route10_Text_RockTunnel::
	.string "ROCK TUNNEL$"


Route10_Text_PowerPlant::
	.string "POWER PLANT$"
