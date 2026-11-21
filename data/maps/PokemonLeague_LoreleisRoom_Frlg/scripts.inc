@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

PokemonLeague_LoreleisRoom_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, PokemonLeague_LoreleisRoom_OnResume
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, PokemonLeague_LoreleisRoom_OnWarp
	.byte 0

PokemonLeague_LoreleisRoom_OnWarp::
	map_script_2 VAR_TEMP_1, 0, PokemonLeague_LoreleisRoom_EventScript_TurnPlayerNorth
	.2byte 0

PokemonLeague_LoreleisRoom_OnResume::
	setvar VAR_0x8004, 0
	end

PokemonLeague_LoreleisRoom_EventScript_TurnPlayerNorth::
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

PokemonLeague_LoreleisRoom_EventScript_Lorelei::
	lock
	faceplayer
	goto PokemonLeague_LoreleisRoom_EventScript_PostBattle

PokemonLeague_LoreleisRoom_EventScript_PostBattle::
	msgbox PokemonLeague_LoreleisRoom_Text_PostBattle
	release
	end

PokemonLeague_LoreleisRoom_Text_PostBattle::
	.string "You're better than I thought.\n"
	.string "Go on ahead.\p"
	.string "You only got a taste of the\n"
	.string "POKéMON LEAGUE's power.$"
