@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

.equ SIGN_LADY_READY, VAR_TEMP_2

PalletTown_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PalletTown_OnTransition
	.byte 0

PalletTown_OnTransition::
	call PalletTown_EventScript_TryReadySignLady
	end

PalletTown_EventScript_TryReadySignLady::
	goto Common_EventScript_NopReturn

PalletTown_EventScript_SignLady::
	lock
	goto PalletTown_EventScript_SignLadyDone

PalletTown_EventScript_SignLadyDone::
	applymovement LOCALID_PALLET_SIGN_LADY, Common_Movement_FacePlayer
	waitmovement 0
	msgbox PalletTown_Text_RaisingMonsToo
	release
	end

PalletTown_EventScript_FatMan::
	msgbox PalletTown_Text_CanStoreItemsAndMonsInPC, MSGBOX_NPC
	end

PalletTown_EventScript_OaksLabSign::
	lockall
	msgbox PalletTown_Text_OakPokemonResearchLab
	releaseall
	end

PalletTown_EventScript_PlayersHouseSign::
	msgbox PalletTown_Text_PlayersHouse, MSGBOX_SIGN
	end

PalletTown_EventScript_RivalsHouseSign::
	msgbox PalletTown_Text_RivalsHouse, MSGBOX_SIGN
	end

PalletTown_EventScript_TownSign::
	msgbox PalletTown_Text_TownSign, MSGBOX_SIGN
	end

PalletTown_EventScript_TrainerTips::
	lockall
	msgbox PalletTown_Text_PressStartToOpenMenu
	releaseall
	end

PalletTown_Text_RaisingMonsToo::
	.string "I'm raising POKéMON, too.\p"
	.string "When they get strong, they can\n"
	.string "protect me.$"


PalletTown_Text_CanStoreItemsAndMonsInPC::
	.string "Technology is incredible!\p"
	.string "You can now store and recall items\n"
	.string "and POKéMON as data via PC.$"


PalletTown_Text_OakPokemonResearchLab::
	.string "OAK POKéMON RESEARCH LAB$"


PalletTown_Text_PlayersHouse::
	.string "{PLAYER}'s house$"


PalletTown_Text_RivalsHouse::
	.string "{RIVAL}'s house$"


PalletTown_Text_TownSign::
	.string "PALLET TOWN\n"
	.string "Shades of your journey await!$"


PalletTown_Text_PressStartToOpenMenu::
	.string "TRAINER TIPS\p"
	.string "Press START to open the MENU!$"
