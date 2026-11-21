@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

PokemonLeague_LancesRoom_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, PokemonLeague_LancesRoom_OnResume
	map_script MAP_SCRIPT_ON_LOAD, PokemonLeague_LancesRoom_OnLoad
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, PokemonLeague_LancesRoom_OnWarp
	.byte 0

PokemonLeague_LancesRoom_OnWarp::
	map_script_2 VAR_TEMP_1, 0, PokemonLeague_LancesRoom_EventScript_TurnPlayerNorth
	.2byte 0

PokemonLeague_LancesRoom_OnResume::
	setvar VAR_0x8004, 3
	end

PokemonLeague_LancesRoom_OnLoad::
	call PokemonLeague_LancesRoom_EventScript_CloseEntry
	call PokemonLeague_LancesRoom_EventScript_SetDoorOpen
	end

PokemonLeague_LancesRoom_EventScript_CloseEntry::
	call PokemonLeague_LancesRoom_EventScript_SetEntryClosed
	return

PokemonLeague_LancesRoom_EventScript_SetDoorOpen::
	return

PokemonLeague_LancesRoom_EventScript_TurnPlayerNorth::
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

PokemonLeague_LancesRoom_EventScript_SetEntryClosed::
	setmetatile 5, 14, METATILE_PokemonLeague_Entry_TopLeft_Closed, 1
	setmetatile 6, 14, METATILE_PokemonLeague_Entry_TopMid_Closed, 1
	setmetatile 7, 14, METATILE_PokemonLeague_Entry_TopRight_Closed, 1
	setmetatile 5, 15, METATILE_PokemonLeague_Entry_BottomLeft_Closed, 1
	setmetatile 6, 15, METATILE_PokemonLeague_Entry_BottomMid_Closed, 1
	setmetatile 7, 15, METATILE_PokemonLeague_Entry_BottomRight_Closed, 1
	setmetatile 6, 16, METATILE_PokemonLeague_Floor_ShadeFull_Lance, 0
	setmetatile 7, 16, METATILE_PokemonLeague_Floor_ShadeFull_Lance, 0
	return

PokemonLeague_LancesRoom_EventScript_Lance::
	lock
	faceplayer
	goto PokemonLeague_LancesRoom_EventScript_PostBattle

PokemonLeague_LancesRoom_EventScript_PostBattle::
	msgbox PokemonLeague_LancesRoom_Text_PostBattle
	release
	end

PokemonLeague_LancesRoom_Text_PostBattle::
	.string "I still can't believe my dragons\n"
	.string "lost to you, {PLAYER}.\p"
	.string "You are now the POKéMON LEAGUE\n"
	.string "CHAMPION!\p"
	.string "…Or, you would have been, but\n"
	.string "you have one more challenge left.\p"
	.string "There is one more TRAINER to face!\n"
	.string "His name is…\p"
	.string "{RIVAL}!\p"
	.string "He beat the ELITE FOUR before\n"
	.string "you.\p"
	.string "He is the real POKéMON LEAGUE\n"
	.string "CHAMPION.$"
