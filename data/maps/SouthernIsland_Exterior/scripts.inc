SouthernIsland_Exterior_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SouthernIsland_Exterior_OnTransition
	.byte 0

SouthernIsland_Exterior_OnTransition:
	setflag FLAG_LANDMARK_SOUTHERN_ISLAND
	end

@ Route 135 lets the player surf here before the boat runs (8 badges); the
@ sailor only sails back once it does, so he can't skip ahead to Lilycove.
SouthernIsland_Exterior_EventScript_Sailor::
	lock
	faceplayer
	goto_if_unset FLAG_BADGE08_GET, SouthernIsland_Exterior_EventScript_BoatNotRunning
	call Common_EventScript_BufferFerryHomePort
	msgbox EventTicket_Text_SouthernIslandSailBack, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SouthernIsland_Exterior_EventScript_AsYouLike
	msgbox EventTicket_Text_SailHome, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 30
	hideobjectat LOCALID_SOUTHERN_ISLAND_SAILOR, MAP_SOUTHERN_ISLAND_EXTERIOR
	setvar VAR_0x8004, LOCALID_SOUTHERN_ISLAND_SS_TIDAL
	call Common_EventScript_FerryDepartIsland
	goto_if_set FLAG_SPECIAL_ISLAND_FERRY_FROM_SLATEPORT, Common_EventScript_FerryReturnToSlateport
	warp MAP_LILYCOVE_CITY_HARBOR, 8, 11
	waitstate
	release
	end

SouthernIsland_Exterior_EventScript_BoatNotRunning::
	msgbox SouthernIsland_Exterior_Text_BoatNotRunning, MSGBOX_DEFAULT
	release
	end

SouthernIsland_Exterior_EventScript_AsYouLike::
	msgbox EventTicket_Text_AsYouLike, MSGBOX_DEFAULT
	release
	end

Ferry_EventScript_DepartIslandSouth::
	applymovement LOCALID_PLAYER, Ferry_Movement_DepartIslandBoardSouth
	waitmovement 0
	return

Ferry_EventScript_DepartIslandWest::
	applymovement LOCALID_PLAYER, Ferry_Movement_DepartIslandBoardWest
	waitmovement 0
	return

Ferry_Movement_DepartIslandBoardSouth:
	walk_down
	step_end

Ferry_Movement_DepartIslandBoardWest:
	walk_left
	walk_in_place_faster_down
	step_end

SouthernIsland_Exterior_EventScript_Sign::
	msgbox SouthernIsland_Exterior_Text_Sign, MSGBOX_SIGN
	end

SouthernIsland_Exterior_Text_BoatNotRunning:
	.string "Aye, mate, you surfed all the way out\n"
	.string "here? Impressive!\p"
	.string "This boat only sails for TRAINERS with\n"
	.string "all eight HOENN GYM BADGES, though.\p"
	.string "You'll have to surf back the way you\n"
	.string "came, I'm afraid.$"
