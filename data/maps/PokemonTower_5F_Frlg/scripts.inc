@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

PokemonTower_5F_Frlg_MapScripts::
	.byte 0

PokemonTower_5F_EventScript_Channeler::
	msgbox PokemonTower_5F_Text_RestHereInPurifiedSpace, MSGBOX_NPC
	end

PokemonTower_5F_Text_RestHereInPurifiedSpace::
	.string "Come, child!\n"
	.string "I have purified this space.\l"
	.string "You can rest here.$"
