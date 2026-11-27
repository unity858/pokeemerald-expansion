@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

RocketHideout_Elevator_Frlg_MapScripts::
	.byte 0

@ ---- Floor select (FRLG) ----
@ Panel at (0,2). Needs the Lift Key (FLAG_GOT_ROCKET_HIDEOUT_LIFT_KEY, from the B4F grunt by the stairs).
@ GetElevatorFloor reads the floor the player came from out of the dynamic warp (set by the game when
@ entering the elevator, whose exit warps are MAP_DYNAMIC); the choice sets a new dynamic warp.
@ VAR_KANTO_ELEVATOR_FLOOR is Emerald's VAR_DEPT_STORE_FLOOR (recomputed on entry, so it can be shared).

RocketHideout_Elevator_EventScript_FloorSelect::
	lockall
	goto_if_unset FLAG_GOT_ROCKET_HIDEOUT_LIFT_KEY, RocketHideout_Elevator_EventScript_NeedKey
	setvar VAR_0x8004, 2
	call_if_unset FLAG_TEMP_2, EventScript_GetElevatorFloor
	copyvar VAR_0x8005, VAR_KANTO_ELEVATOR_FLOOR
	special DrawElevatorCurrentFloorWindow
	message gText_WantWhichFloor
	waitmessage
	setvar VAR_0x8004, 2
	specialvar VAR_RESULT, InitElevatorFloorSelectMenuPos
	switch VAR_RESULT
	case 0, RocketHideout_Elevator_EventScript_FloorSelectFromB1F
	case 1, RocketHideout_Elevator_EventScript_FloorSelectFromB2F
	case 2, RocketHideout_Elevator_EventScript_FloorSelectFromB4F
	end

RocketHideout_Elevator_EventScript_FloorSelectFromB1F::
	multichoicedefault 0, 0, MULTI_ROCKET_HIDEOUT_ELEVATOR, 0, FALSE
	goto RocketHideout_Elevator_EventScript_ChooseFloor
	end

RocketHideout_Elevator_EventScript_FloorSelectFromB2F::
	multichoicedefault 0, 0, MULTI_ROCKET_HIDEOUT_ELEVATOR, 1, FALSE
	goto RocketHideout_Elevator_EventScript_ChooseFloor
	end

RocketHideout_Elevator_EventScript_FloorSelectFromB4F::
	multichoicedefault 0, 0, MULTI_ROCKET_HIDEOUT_ELEVATOR, 2, FALSE
	goto RocketHideout_Elevator_EventScript_ChooseFloor
	end

RocketHideout_Elevator_EventScript_ChooseFloor::
	switch VAR_RESULT
	case 0, RocketHideout_Elevator_EventScript_ToB1F
	case 1, RocketHideout_Elevator_EventScript_ToB2F
	case 2, RocketHideout_Elevator_EventScript_ToB4F
	case 3, RocketHideout_Elevator_EventScript_ExitFloorSelect
	case 127, RocketHideout_Elevator_EventScript_ExitFloorSelect
	end

RocketHideout_Elevator_EventScript_ToB1F::
	setvar VAR_0x8006, 3
	setdynamicwarp MAP_ROCKET_HIDEOUT_B1F, 255, 24, 25
	goto_if_eq VAR_KANTO_ELEVATOR_FLOOR, 3, RocketHideout_Elevator_EventScript_ExitFloorSelect
	call RocketHideout_Elevator_EventScript_MoveElevator
	setvar VAR_KANTO_ELEVATOR_FLOOR, 3
	goto RocketHideout_Elevator_EventScript_ExitFloorSelect
	end

RocketHideout_Elevator_EventScript_ToB2F::
	setvar VAR_0x8006, 2
	setdynamicwarp MAP_ROCKET_HIDEOUT_B2F, 255, 28, 16
	goto_if_eq VAR_KANTO_ELEVATOR_FLOOR, 2, RocketHideout_Elevator_EventScript_ExitFloorSelect
	call RocketHideout_Elevator_EventScript_MoveElevator
	setvar VAR_KANTO_ELEVATOR_FLOOR, 2
	goto RocketHideout_Elevator_EventScript_ExitFloorSelect
	end

RocketHideout_Elevator_EventScript_ToB4F::
	setvar VAR_0x8006, 0
	setdynamicwarp MAP_ROCKET_HIDEOUT_B4F, 255, 20, 23
	goto_if_eq VAR_KANTO_ELEVATOR_FLOOR, 0, RocketHideout_Elevator_EventScript_ExitFloorSelect
	call RocketHideout_Elevator_EventScript_MoveElevator
	setvar VAR_KANTO_ELEVATOR_FLOOR, 0
	goto RocketHideout_Elevator_EventScript_ExitFloorSelect
	end

RocketHideout_Elevator_EventScript_ExitFloorSelect::
	special CloseElevatorCurrentFloorWindow
	releaseall
	end

RocketHideout_Elevator_EventScript_MoveElevator::
	special CloseElevatorCurrentFloorWindow
	closemessage
	waitse
	special AnimateElevator
	waitstate
	setflag FLAG_TEMP_2
	return

RocketHideout_Elevator_EventScript_NeedKey::
	msgbox RocketHideout_Elevator_Text_AppearsToNeedAKey
	releaseall
	end

RocketHideout_Elevator_Text_AppearsToNeedAKey::
	.string "It appears to need a key.$"

