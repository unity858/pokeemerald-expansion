@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

.equ REQUIRED_CAUGHT_MONS, 50

Route15_WestEntrance_2F_Frlg_MapScripts::
	.byte 0

Route15_WestEntrance_2F_EventScript_LeftBinoculars::
	lockall
	msgbox Route15_WestEntrance_2F_Text_LargeShiningBird
	showmonpic SPECIES_ARTICUNO, 10, 3
	delay 20
	waitbuttonpress
	hidemonpic
	setvar VAR_0x8004, SPECIES_ARTICUNO
	special SetSeenMon
	releaseall
	end

Route15_WestEntrance_2F_EventScript_RightBinoculars::
	msgbox Route15_WestEntrance_2F_Text_SmallIslandOnHorizon, MSGBOX_SIGN
	end

Route15_WestEntrance_2F_EventScript_Aide::
	lock
	faceplayer
	call Route15_WestEntrance_2F_EventScript_GetAideRequestInfo
	goto Route15_WestEntrance_2F_EventScript_AlreadyGotExpShare

Route15_WestEntrance_2F_EventScript_AlreadyGotExpShare::
	msgbox Route15_WestEntrance_2F_Text_ExplainExpShare
	release
	end

Route15_WestEntrance_2F_EventScript_GetAideRequestInfo::
	buffernumberstring STR_VAR_1, REQUIRED_CAUGHT_MONS
	bufferitemname STR_VAR_2, ITEM_EXP_SHARE
	return

Route15_WestEntrance_2F_Text_ExplainExpShare::
	.string "EXP. SHARE is an item to be held\n"
	.string "by a POKéMON.\p"
	.string "The POKéMON will receive a share\n"
	.string "of the EXP. Points without having\l"
	.string "to battle.$"


Route15_WestEntrance_2F_Text_LargeShiningBird::
	.string "Let's see what the binoculars have\n"
	.string "to show…\p"
	.string "A large, shining bird is flying\n"
	.string "toward the sea.$"


Route15_WestEntrance_2F_Text_SmallIslandOnHorizon::
	.string "Let's see what the binoculars have\n"
	.string "to show…\p"
	.string "It looks like a small island on\n"
	.string "the horizon!$"
