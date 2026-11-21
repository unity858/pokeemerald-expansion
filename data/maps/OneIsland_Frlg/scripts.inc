@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

OneIsland_Frlg_MapScripts::
	.byte 0

OneIsland_EventScript_OldMan::
	lock
	faceplayer
	goto OneIsland_EventScript_OldManLinkHoenn

OneIsland_EventScript_OldManLinkHoenn::
	msgbox OneIsland_Text_HavePCLinkageWithHoenn
	release
	end

OneIsland_EventScript_BaldingMan::
	msgbox OneIsland_Text_IsntWarmClimateHereGreat, MSGBOX_NPC
	end

OneIsland_EventScript_IslandSign::
	msgbox OneIsland_Text_IslandSign, MSGBOX_SIGN
	end

OneIsland_EventScript_PokemonNetCenterSign::
	msgbox OneIsland_Text_PokemonNetCenterSign, MSGBOX_SIGN
	end

OneIsland_Text_HavePCLinkageWithHoenn::
	.string "My granddaughter was in a tizzy\n"
	.string "over a new breakthrough.\p"
	.string "She said we finally have PC linkage\n"
	.string "with people in HOENN.\p"
	.string "I'm not sure what that means, but\n"
	.string "CELIO is quite the man.\p"
	.string "He would make a fine husband for\n"
	.string "my granddaughter!$"


OneIsland_Text_IslandSign::
	.string "ONE ISLAND\n"
	.string "Friends Gather at Knot Island$"


OneIsland_Text_PokemonNetCenterSign::
	.string "Expanding the POKéMON World!\n"
	.string "POKéMON NET CENTER$"

@ Unused

OneIsland_Text_IsntWarmClimateHereGreat::
	.string "Hi, sight-seeing, are you?\n"
	.string "Isn't the warm climate here great?$"
