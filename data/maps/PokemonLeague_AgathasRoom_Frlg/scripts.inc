@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

PokemonLeague_AgathasRoom_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, PokemonLeague_AgathasRoom_OnResume
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, PokemonLeague_AgathasRoom_OnWarp
	.byte 0

PokemonLeague_AgathasRoom_OnWarp::
	map_script_2 VAR_TEMP_1, 0, PokemonLeague_AgathasRoom_EventScript_TurnPlayerNorth
	.2byte 0

PokemonLeague_AgathasRoom_OnResume::
	setvar VAR_0x8004, 2
	end

PokemonLeague_AgathasRoom_EventScript_TurnPlayerNorth::
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

PokemonLeague_AgathasRoom_EventScript_Agatha::
	lock
	faceplayer
	goto PokemonLeague_AgathasRoom_EventScript_PostBattle

PokemonLeague_AgathasRoom_EventScript_PostBattle::
	msgbox PokemonLeague_AgathasRoom_Text_PostBattle
	release
	end

PokemonLeague_AgathasRoom_Text_PostBattle::
	.string "You win!\p"
	.string "I see what the old duff sees in\n"
	.string "you now.\p"
	.string "I have nothing else to say.\n"
	.string "Run along now, child!$"
