@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

CinnabarIsland_PokemonLab_Lounge_Frlg_MapScripts::
	.byte 0

CinnabarIsland_PokemonLab_Lounge_EventScript_Scientist::
	msgbox CinnabarIsland_PokemonLab_Lounge_Text_FoundFossilInMtMoon, MSGBOX_NPC
	end

CinnabarIsland_PokemonLab_Lounge_Text_FoundFossilInMtMoon::
	.string "I found this most remarkable fossil\n"
	.string "inside MT. MOON.\p"
	.string "I think it's of a rare, prehistoric\n"
	.string "POKéMON.$"
