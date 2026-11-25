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
	goto_if_not_staticenc GIFT_KUBFU, RECEIVED, ShoalCave_LowTideEntranceRoom_EventScript_GiveKubfu
	call ShoalCave_LowTideEntranceRoom_EventScript_CheckScrolls
	goto_if_eq VAR_RESULT, FALSE, ShoalCave_LowTideEntranceRoom_EventScript_GiveScrollsLater
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
	givegiftmon GIFT_KUBFU, SPECIES_KUBFU
	goto_if_eq VAR_RESULT, FALSE, ShoalCave_LowTideEntranceRoom_EventScript_KubfuEnd
	msgbox ShoalCave_LowTideEntranceRoom_Text_OfferScrolls, MSGBOX_DEFAULT
	call ShoalCave_LowTideEntranceRoom_EventScript_GiveMissingScrolls
	msgbox ShoalCave_LowTideEntranceRoom_Text_KubfuReceived, MSGBOX_DEFAULT
ShoalCave_LowTideEntranceRoom_EventScript_KubfuEnd::
	release
	end

@ Kubfu's two scrolls come with it. Players who got Kubfu before the scrolls were
@ added (or whose Bag was full) get any missing scroll on their next talk.
@ Returns VAR_RESULT = TRUE if the player has both scrolls.
ShoalCave_LowTideEntranceRoom_EventScript_CheckScrolls::
	checkitem ITEM_SCROLL_OF_DARKNESS
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_NopReturn
	checkitem ITEM_SCROLL_OF_WATERS
	return

ShoalCave_LowTideEntranceRoom_EventScript_GiveScrollsLater::
	msgbox ShoalCave_LowTideEntranceRoom_Text_ForgotScrolls, MSGBOX_DEFAULT
	call ShoalCave_LowTideEntranceRoom_EventScript_GiveMissingScrolls
	msgbox ShoalCave_LowTideEntranceRoom_Text_ExplainScrolls, MSGBOX_DEFAULT
	release
	end

ShoalCave_LowTideEntranceRoom_EventScript_GiveMissingScrolls::
	checkitem ITEM_SCROLL_OF_DARKNESS
	call_if_eq VAR_RESULT, FALSE, ShoalCave_LowTideEntranceRoom_EventScript_GiveScrollOfDarkness
	checkitem ITEM_SCROLL_OF_WATERS
	call_if_eq VAR_RESULT, FALSE, ShoalCave_LowTideEntranceRoom_EventScript_GiveScrollOfWaters
	return

ShoalCave_LowTideEntranceRoom_EventScript_GiveScrollOfDarkness::
	giveitem ITEM_SCROLL_OF_DARKNESS
	call_if_eq VAR_RESULT, FALSE, ShoalCave_LowTideEntranceRoom_EventScript_ScrollBagFull
	return

ShoalCave_LowTideEntranceRoom_EventScript_GiveScrollOfWaters::
	giveitem ITEM_SCROLL_OF_WATERS
	call_if_eq VAR_RESULT, FALSE, ShoalCave_LowTideEntranceRoom_EventScript_ScrollBagFull
	return

ShoalCave_LowTideEntranceRoom_EventScript_ScrollBagFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	return

ShoalCave_LowTideEntranceRoom_Text_OfferScrolls:
	.string "And these scrolls go with it.\n"
	.string "They're as old as this cave.$"

ShoalCave_LowTideEntranceRoom_Text_ForgotScrolls:
	.string "Ah, it's you! I forgot to give you\n"
	.string "these when you took that little\l"
	.string "one with you.$"

ShoalCave_LowTideEntranceRoom_Text_ExplainScrolls:
	.string "The SCROLL OF DARKNESS teaches\n"
	.string "the strikes of the dark.\p"
	.string "The SCROLL OF WATERS teaches\n"
	.string "the flow of the tides.\p"
	.string "Only one path can be chosen, so\n"
	.string "choose well.$"

ShoalCave_LowTideEntranceRoom_Text_OfferKubfu:
	.string "Hmm… You've become quite a strong\n"
	.string "TRAINER, haven't you?\p"
	.string "This little one wandered into the\n"
	.string "cave and has trained against the\l"
	.string "tides ever since.\p"
	.string "It wants a strong partner.\n"
	.string "Please, take it with you.$"

ShoalCave_LowTideEntranceRoom_Text_KubfuReceived:
	.string "Train it well, and show it one of\n"
	.string "those scrolls when it's ready.\l"
	.string "It'll master the style it reads.\p"
	.string "And bring me SHOAL SALT and\n"
	.string "SHOAL SHELLS, and I'll still make\l"
	.string "you a SHELL BELL!$"
