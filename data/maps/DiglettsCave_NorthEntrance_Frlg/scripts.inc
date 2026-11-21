@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

DiglettsCave_NorthEntrance_Frlg_MapScripts::
	.byte 0

DiglettsCave_NorthEntrance_EventScript_Hiker::
	msgbox DiglettsCave_NorthEntrance_RockTunnelPitchBlack, MSGBOX_NPC
	end

DiglettsCave_NorthEntrance_RockTunnelPitchBlack::
	.string "I went inside ROCK TUNNEL, but it's\n"
	.string "pitch-black and scary in there.\p"
	.string "If I could get a POKéMON to use\n"
	.string "FLASH and light it up…$"
