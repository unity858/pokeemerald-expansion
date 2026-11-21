@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

PokemonLeague_BrunosRoom_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, PokemonLeague_BrunosRoom_OnResume
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, PokemonLeague_BrunosRoom_OnWarp
	.byte 0

PokemonLeague_BrunosRoom_OnWarp::
	map_script_2 VAR_TEMP_1, 0, PokemonLeague_BrunosRoom_EventScript_TurnPlayerNorth
	.2byte 0

PokemonLeague_BrunosRoom_OnResume::
	setvar VAR_0x8004, 1
	end

PokemonLeague_BrunosRoom_EventScript_TurnPlayerNorth::
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

PokemonLeague_BrunosRoom_EventScript_Bruno::
	lock
	faceplayer
	goto PokemonLeague_BrunosRoom_EventScript_PostBattle

PokemonLeague_BrunosRoom_EventScript_PostBattle::
	msgbox PokemonLeague_BrunosRoom_Text_PostBattle
	closemessage
	call_if_eq VAR_FACING, DIR_NORTH, PokemonLeague_BrunosRoom_EventScript_BrunoLookAwayRight
	call_if_eq VAR_FACING, DIR_SOUTH, PokemonLeague_BrunosRoom_EventScript_BrunoLookAwayLeft
	call_if_eq VAR_FACING, DIR_WEST, PokemonLeague_BrunosRoom_EventScript_BrunoLookAwayDown
	call_if_eq VAR_FACING, DIR_EAST, PokemonLeague_BrunosRoom_EventScript_BrunoLookAwayDown
	release
	end

PokemonLeague_BrunosRoom_EventScript_BrunoLookAwayLeft::
	applymovement LOCALID_BRUNO, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

PokemonLeague_BrunosRoom_EventScript_BrunoLookAwayRight::
	applymovement LOCALID_BRUNO, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

PokemonLeague_BrunosRoom_EventScript_BrunoLookAwayDown::
	applymovement LOCALID_BRUNO, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

PokemonLeague_BrunosRoom_Text_PostBattle::
	.string "My job is done.\n"
	.string "Go face your next challenge.$"
