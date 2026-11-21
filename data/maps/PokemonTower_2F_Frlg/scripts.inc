@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

PokemonTower_2F_Frlg_MapScripts::
	.byte 0

PokemonTower_2F_EventScript_Channeler::
	msgbox PokemonTower_2F_Text_SilphScopeCouldUnmaskGhosts, MSGBOX_NPC
	end

PokemonTower_2F_Text_SilphScopeCouldUnmaskGhosts::
	.string "Even we could not identify the\n"
	.string "wayward ghosts.\p"
	.string "A SILPH SCOPE might be able to\n"
	.string "unmask them.$"
