LilycoveCity_Harbor_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LilycoveCity_Harbor_OnTransition
	.byte 0

LilycoveCity_Harbor_OnTransition:
	setescapewarp MAP_LILYCOVE_CITY, 12, 33
	@ The boat to Southern Island runs from 8 badges
	call_if_set FLAG_BADGE08_GET, LilycoveCity_Harbor_EventScript_ShowSSTidal
	end

LilycoveCity_Harbor_EventScript_ShowSSTidal::
	clearflag FLAG_HIDE_LILYCOVE_HARBOR_SSTIDAL
	return

@ The ferry is gated by flags only, no ticket items:
@   8 badges        Seagallop to the Sevii Islands and the boat to Southern Island
@                   (InterRegionFerry_EventScript_HoennOfferSevii)
@   Hoenn League    every route, incl. the other special islands and Vermilion City
LilycoveCity_Harbor_EventScript_FerryAttendant::
	lock
	faceplayer
	setvar VAR_0x8004, SEAGALLOP_LILYCOVE
	goto_if_set FLAG_SYS_GAME_CLEAR, LilycoveCity_Harbor_EventScript_AskWhereTo
	goto_if_set FLAG_BADGE08_GET, InterRegionFerry_EventScript_HoennOfferSevii
	goto LilycoveCity_Harbor_EventScript_FerryUnavailable
	end

LilycoveCity_Harbor_EventScript_AskWhereTo::
	message InterRegionFerry_Text_ChampionSailsFree
	waitmessage
	goto LilycoveCity_Harbor_EventScript_FerryRegularLocationSelect
	end

LilycoveCity_Harbor_EventScript_FerryRegularLocationSelect::
	setvar VAR_0x8004, SEAGALLOP_LILYCOVE
	dynmultipush InterRegionFerry_Text_SlateportCity, SEAGALLOP_SLATEPORT
	call_if_set FLAG_MET_SCOTT_ON_SS_TIDAL, LilycoveCity_Harbor_EventScript_PushBattleFrontier
	dynmultipush InterRegionFerry_Text_SouthernIsland, FERRY_DEST_SOUTHERN_ISLAND
	dynmultipush InterRegionFerry_Text_NavelRock, FERRY_DEST_NAVEL_ROCK
	dynmultipush InterRegionFerry_Text_BirthIsland, FERRY_DEST_BIRTH_ISLAND
	dynmultipush InterRegionFerry_Text_FarawayIsland, FERRY_DEST_FARAWAY_ISLAND
	call InterRegionFerry_EventScript_PushSeagallopDests
	call InterRegionFerry_EventScript_ShowDestList
	switch VAR_RESULT
	case SEAGALLOP_SLATEPORT, LilycoveCity_Harbor_EventScript_GoToSlateport
	case FERRY_DEST_BATTLE_FRONTIER, LilycoveCity_Harbor_EventScript_GoToBattleFrontier
	case FERRY_DEST_SOUTHERN_ISLAND, LilycoveCity_Harbor_EventScript_GoToSouthernIsland
	case FERRY_DEST_NAVEL_ROCK, LilycoveCity_Harbor_EventScript_GoToNavelRock
	case FERRY_DEST_BIRTH_ISLAND, LilycoveCity_Harbor_EventScript_GoToBirthIsland
	case FERRY_DEST_FARAWAY_ISLAND, LilycoveCity_Harbor_EventScript_GoToFarawayIsland
	case FERRY_DEST_CANCEL, LilycoveCity_Harbor_EventScript_ExitSailSelect
	goto InterRegionFerry_EventScript_Sail
	end

LilycoveCity_Harbor_EventScript_PushBattleFrontier::
	dynmultipush InterRegionFerry_Text_BattleFrontier, FERRY_DEST_BATTLE_FRONTIER
	return

LilycoveCity_Harbor_EventScript_GoToSouthernIsland::
	clearflag FLAG_SPECIAL_ISLAND_FERRY_FROM_SLATEPORT
	call LilycoveCity_Harbor_EventScript_BoardFerry
	warp MAP_SOUTHERN_ISLAND_EXTERIOR, 13, 22
	waitstate
	release
	end

LilycoveCity_Harbor_EventScript_GoToNavelRock::
	clearflag FLAG_SPECIAL_ISLAND_FERRY_FROM_SLATEPORT
	call LilycoveCity_Harbor_EventScript_BoardFerry
	warp MAP_NAVEL_ROCK_HARBOR, 8, 4
	waitstate
	release
	end

LilycoveCity_Harbor_EventScript_GoToBirthIsland::
	clearflag FLAG_SPECIAL_ISLAND_FERRY_FROM_SLATEPORT
	call LilycoveCity_Harbor_EventScript_BoardFerry
	warp MAP_BIRTH_ISLAND_HARBOR, 8, 4
	waitstate
	release
	end

LilycoveCity_Harbor_EventScript_GoToFarawayIsland::
	clearflag FLAG_SPECIAL_ISLAND_FERRY_FROM_SLATEPORT
	call LilycoveCity_Harbor_EventScript_BoardFerry
	warp MAP_FARAWAY_ISLAND_ENTRANCE, 13, 38
	waitstate
	release
	end

LilycoveCity_Harbor_EventScript_GoToSlateport::
	msgbox LilycoveCity_Harbor_Text_SlateportItIs, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LilycoveCity_Harbor_EventScript_FerryDestinationChangeMind
	setvar VAR_SS_TIDAL_STATE, SS_TIDAL_BOARD_LILYCOVE
	call LilycoveCity_Harbor_EventScript_BoardFerry
	warp MAP_SS_TIDAL_CORRIDOR, 1, 10
	waitstate
	release
	end

LilycoveCity_Harbor_EventScript_GoToBattleFrontier::
	msgbox LilycoveCity_Harbor_Text_BattleFrontierItIs, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LilycoveCity_Harbor_EventScript_FerryDestinationChangeMind
	call LilycoveCity_Harbor_EventScript_BoardFerry
	warp MAP_BATTLE_FRONTIER_OUTSIDE_WEST, 19, 67
	waitstate
	release
	end

LilycoveCity_Harbor_EventScript_FerryUnavailable::
	msgbox LilycoveCity_Harbor_Text_FerryUnavailable, MSGBOX_DEFAULT
	release
	end

LilycoveCity_Harbor_EventScript_FerryDestinationChangeMind::
	message LilycoveCity_Harbor_Text_WhereWouldYouLikeToGo
	waitmessage
	goto LilycoveCity_Harbor_EventScript_FerryRegularLocationSelect
	end

LilycoveCity_Harbor_EventScript_BoardFerry::
	msgbox LilycoveCity_Harbor_Text_PleaseBoard, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 30
	hideobjectat VAR_LAST_TALKED, MAP_LILYCOVE_CITY_HARBOR
	call_if_eq VAR_FACING, DIR_NORTH, LilycoveCity_Harbor_EventScript_PlayerBoardFerryNorth
	call_if_eq VAR_FACING, DIR_EAST, LilycoveCity_Harbor_EventScript_PlayerBoardFerryEast
	delay 30
	hideplayer
	setvar VAR_0x8004, LOCALID_LILYCOVE_HARBOR_SS_TIDAL
	call Common_EventScript_FerryDepart
	return

LilycoveCity_Harbor_EventScript_PlayerBoardFerryEast::
	applymovement LOCALID_PLAYER, LilycoveCity_Harbor_Movement_PlayerBoardFerryEast
	waitmovement 0
	return

LilycoveCity_Harbor_EventScript_PlayerBoardFerryNorth::
	applymovement LOCALID_PLAYER, LilycoveCity_Harbor_Movement_PlayerBoardFerryNorth
	waitmovement 0
	return

LilycoveCity_Harbor_EventScript_ExitSailSelect::
	msgbox LilycoveCity_Harbor_Text_SailAnotherTime, MSGBOX_DEFAULT
	release
	end

LilycoveCity_Harbor_Movement_PlayerBoardFerryEast:
	walk_right
	walk_in_place_faster_up
	step_end

LilycoveCity_Harbor_Movement_PlayerBoardFerryNorth:
	walk_up
	step_end

LilycoveCity_Harbor_EventScript_Sailor::
	lock
	faceplayer
	goto_if_set FLAG_SYS_GAME_CLEAR, LilycoveCity_Harbor_EventScript_SailorFerryAvailable
	goto_if_set FLAG_BADGE08_GET, LilycoveCity_Harbor_EventScript_SailorSeagallop
	msgbox LilycoveCity_Harbor_Text_SailorFerryUnavailable, MSGBOX_DEFAULT
	release
	end

LilycoveCity_Harbor_EventScript_SailorSeagallop::
	msgbox LilycoveCity_Harbor_Text_SailorSeagallop, MSGBOX_DEFAULT
	release
	end

LilycoveCity_Harbor_EventScript_SailorFerryAvailable::
	msgbox LilycoveCity_Harbor_Text_SailorFerryAvailable, MSGBOX_DEFAULT
	release
	end

LilycoveCity_Harbor_Text_FerryUnavailable:
	.string "I beg your pardon?\n"
	.string "You're looking for a ship?\p"
	.string "I'm sorry, the ferry service isn't\n"
	.string "available at present…$"

LilycoveCity_Harbor_Text_SailAnotherTime:
	.string "Please sail with us another time!$"

LilycoveCity_Harbor_Text_SlateportItIs:
	.string "SLATEPORT CITY it is, then!$"

LilycoveCity_Harbor_Text_BattleFrontierItIs:
	.string "BATTLE FRONTIER it is, then!$"

LilycoveCity_Harbor_Text_PleaseBoard:
	.string "Please board the ferry and wait for\n"
	.string "departure.$"

LilycoveCity_Harbor_Text_WhereWouldYouLikeToGo:
	.string "Then, where would you like to go?$"

LilycoveCity_Harbor_Text_SailorFerryUnavailable:
	.string "Until they finish making the ferry,\n"
	.string "we sailors have nothing to do…\p"
	.string "I wish they'd get a move on, the folks\n"
	.string "at the SHIPYARD in SLATEPORT.$"

LilycoveCity_Harbor_Text_SailorSeagallop:
	.string "The S.S. TIDAL still isn't finished…\p"
	.string "But a SEAGALLOP from the faraway\n"
	.string "SEVII ISLANDS calls here now.\p"
	.string "They only take TRAINERS with all\n"
	.string "eight HOENN GYM BADGES, though.$"

LilycoveCity_Harbor_Text_SailorFerryAvailable:
	.string "The ferry S.S. TIDAL is finally in\n"
	.string "operation.\p"
	.string "The folks at the SHIPYARD in SLATEPORT\n"
	.string "must've worked extra hard.\p"
	.string "Well, it's my turn to get busy now!$"
