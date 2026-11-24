ShoalCave_LowTideEntranceRoom_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ShoalCave_LowTideEntranceRoom_OnTransition
	.byte 0

ShoalCave_LowTideEntranceRoom_OnTransition:
	special UpdateShoalTideFlag
	goto_if_set FLAG_SYS_SHOAL_TIDE, ShoalCave_LowTideEntranceRoom_EventScript_SetHighTide
	goto ShoalCave_LowTideEntranceRoom_EventScript_SetLowTide

ShoalCave_LowTideEntranceRoom_EventScript_SetHighTide::
	setmaplayoutindex LAYOUT_SHOAL_CAVE_HIGH_TIDE_ENTRANCE_ROOM
	end

ShoalCave_LowTideEntranceRoom_EventScript_SetLowTide::
	setmaplayoutindex LAYOUT_SHOAL_CAVE_LOW_TIDE_ENTRANCE_ROOM
	end

ShoalCave_LowTideEntranceRoom_EventScript_ShellBellExpert::
	lock
	faceplayer
	dotimebasedevents
	call_if_set FLAG_SYS_SHOAL_ITEM, ShoalCave_LowTideEntranceRoom_EventScript_ResetShoalItems
	goto_if_unset FLAG_BADGE08_GET, ShoalCave_LowTideEntranceRoom_EventScript_ShellBellCheck
	goto_if_unset FLAG_RECEIVED_KUBFU, ShoalCave_LowTideEntranceRoom_EventScript_GiveKubfu
ShoalCave_LowTideEntranceRoom_EventScript_ShellBellCheck::
	checkitem ITEM_SHOAL_SALT, 4
	goto_if_eq VAR_RESULT, FALSE, ShoalCave_LowTideEntranceRoom_EventScript_NotEnoughShoalSaltOrShells
	checkitem ITEM_SHOAL_SHELL, 4
	goto_if_eq VAR_RESULT, FALSE, ShoalCave_LowTideEntranceRoom_EventScript_NotEnoughShoalSaltOrShells
	msgbox ShoalCave_LowTideEntranceRoom_Text_WouldYouLikeShellBell, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, ShoalCave_LowTideEntranceRoom_EventScript_DeclineShellBell
	checkitemspace ITEM_SHELL_BELL
	call_if_eq VAR_RESULT, FALSE, ShoalCave_LowTideEntranceRoom_EventScript_CheckSpaceWillBeFreed
	goto_if_eq VAR_RESULT, 2, ShoalCave_LowTideEntranceRoom_EventScript_NoRoomForShellBell
	msgbox ShoalCave_LowTideEntranceRoom_Text_MakeShellBellRightAway, MSGBOX_DEFAULT
	removeitem ITEM_SHOAL_SALT, 4
	removeitem ITEM_SHOAL_SHELL, 4
	giveitem ITEM_SHELL_BELL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull  @ Never FALSE, we already made sure there will be room in the bag.
	msgbox ShoalCave_LowTideEntranceRoom_Text_ExplainShellBell, MSGBOX_DEFAULT
	setflag FLAG_TEMP_2  @ Not read. Perhaps meant to stop him from re-explaining the Shell Bell if multiple are received in one sitting.
	release
	end

@ If the bag is full, check if a slot will be freed when 4 Shoal Salt or Shells are given
ShoalCave_LowTideEntranceRoom_EventScript_CheckSpaceWillBeFreed::
	checkitem ITEM_SHOAL_SALT, 5
	goto_if_eq VAR_RESULT, TRUE, ShoalCave_LowTideEntranceRoom_EventScript_CheckSpaceWillBeFreedShells
	return

ShoalCave_LowTideEntranceRoom_EventScript_CheckSpaceWillBeFreedShells::
	checkitem ITEM_SHOAL_SHELL, 5
	goto_if_eq VAR_RESULT, TRUE, ShoalCave_LowTideEntranceRoom_EventScript_NoSpaceWillBeFreed
	return

ShoalCave_LowTideEntranceRoom_EventScript_NoSpaceWillBeFreed::
	setvar VAR_RESULT, 2
	return

ShoalCave_LowTideEntranceRoom_EventScript_NoRoomForShellBell::
	msgbox ShoalCave_LowTideEntranceRoom_Text_NoSpaceInYourBag, MSGBOX_DEFAULT
	release
	end

ShoalCave_LowTideEntranceRoom_EventScript_NotEnoughShoalSaltOrShells::
	checkitem ITEM_SHOAL_SALT
	goto_if_eq VAR_RESULT, TRUE, ShoalCave_LowTideEntranceRoom_EventScript_HasSomeShoalSaltOrShell
	checkitem ITEM_SHOAL_SHELL
	goto_if_eq VAR_RESULT, TRUE, ShoalCave_LowTideEntranceRoom_EventScript_HasSomeShoalSaltOrShell
	msgbox ShoalCave_LowTideEntranceRoom_Text_AreYouPlanningOnGoingInThere, MSGBOX_DEFAULT
	release
	end

ShoalCave_LowTideEntranceRoom_EventScript_HasSomeShoalSaltOrShell::
	msgbox ShoalCave_LowTideEntranceRoom_Text_BringMe4ShoalSaltAndShells, MSGBOX_DEFAULT
	release
	end

ShoalCave_LowTideEntranceRoom_EventScript_DeclineShellBell::
	msgbox ShoalCave_LowTideEntranceRoom_Text_WantedToMakeShellBell, MSGBOX_DEFAULT
	release
	end

ShoalCave_LowTideEntranceRoom_EventScript_ResetShoalItems::
	clearflag FLAG_RECEIVED_SHOAL_SALT_1
	clearflag FLAG_RECEIVED_SHOAL_SALT_2
	clearflag FLAG_RECEIVED_SHOAL_SALT_3
	clearflag FLAG_RECEIVED_SHOAL_SALT_4
	clearflag FLAG_RECEIVED_SHOAL_SHELL_1
	clearflag FLAG_RECEIVED_SHOAL_SHELL_2
	clearflag FLAG_RECEIVED_SHOAL_SHELL_3
	clearflag FLAG_RECEIVED_SHOAL_SHELL_4
	clearflag FLAG_SYS_SHOAL_ITEM
	return

@ Kubfu gift: the first time he's spoken to after the 8th Gym Badge, the Shell Bell
@ man gives Kubfu (scaled wild level). Afterwards he's back to his Shell Bell routine.
ShoalCave_LowTideEntranceRoom_EventScript_GiveKubfu::
	msgbox ShoalCave_LowTideEntranceRoom_Text_OfferKubfu, MSGBOX_DEFAULT
	setvar VAR_0x8008, SPECIES_KUBFU
	call HackGift_EventScript_GiveMon
	goto_if_eq VAR_RESULT, FALSE, ShoalCave_LowTideEntranceRoom_EventScript_KubfuEnd
	setflag FLAG_RECEIVED_KUBFU
	msgbox ShoalCave_LowTideEntranceRoom_Text_KubfuReceived, MSGBOX_DEFAULT
ShoalCave_LowTideEntranceRoom_EventScript_KubfuEnd::
	release
	end

ShoalCave_LowTideEntranceRoom_Text_OfferKubfu:
	.string "Hmm… You've become quite a strong\n"
	.string "TRAINER, haven't you?\p"
	.string "This little one wandered into the\n"
	.string "cave and has trained against the\l"
	.string "tides ever since.\p"
	.string "It wants a strong partner.\n"
	.string "Please, take it with you.$"

ShoalCave_LowTideEntranceRoom_Text_KubfuReceived:
	.string "Train it well, and one day it'll\n"
	.string "master a fighting style of its\l"
	.string "own.\p"
	.string "And bring me SHOAL SALT and\n"
	.string "SHOAL SHELLS, and I'll still make\l"
	.string "you a SHELL BELL!$"
