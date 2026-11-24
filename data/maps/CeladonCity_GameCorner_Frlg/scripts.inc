@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

CeladonCity_GameCorner_Frlg_MapScripts::
	.byte 0

CeladonCity_GameCorner_EventScript_InfoClerk::
	msgbox CeladonCity_GameCorner_Text_CanExchangeCoinsNextDoor, MSGBOX_NPC
	end

CeladonCity_GameCorner_EventScript_BaldingMan::
	lock
	faceplayer
	msgbox CeladonCity_GameCorner_Text_RumoredTeamRocketRunsThisPlace
	goto CeladonCity_GameCorner_EventScript_FaceSlotMachine

CeladonCity_GameCorner_EventScript_FaceSlotMachine::
	closemessage
	waitmovement 0
	release
	end

CeladonCity_GameCorner_EventScript_Woman1::
	lock
	faceplayer
	msgbox CeladonCity_GameCorner_Text_ThinkMachinesHaveDifferentOdds
	goto CeladonCity_GameCorner_EventScript_FaceSlotMachine

CeladonCity_GameCorner_EventScript_Fisher::
	lock
	faceplayer
	goto CeladonCity_GameCorner_EventScript_FisherAlreadyGotCoins

CeladonCity_GameCorner_EventScript_FisherAlreadyGotCoins::
	msgbox CeladonCity_GameCorner_Text_WinsComeAndGo
	goto CeladonCity_GameCorner_EventScript_FaceSlotMachine

CeladonCity_GameCorner_EventScript_GymGuy::
	lock
	faceplayer
	goto CeladonCity_GameCorner_EventScript_GymGuyPostVictory

CeladonCity_GameCorner_EventScript_GymGuyPostVictory::
	msgbox CeladonCity_GameCorner_Text_RareMonsForCoins
	goto CeladonCity_GameCorner_EventScript_FaceSlotMachine

CeladonCity_GameCorner_EventScript_Woman2::
	lock
	faceplayer
	msgbox CeladonCity_GameCorner_Text_WinOrLoseItsOnlyLuck
	goto CeladonCity_GameCorner_EventScript_FaceSlotMachine

CeladonCity_GameCorner_EventScript_OldMan::
	lock
	faceplayer
	msgbox CeladonCity_GameCorner_Text_SoEasyToGetHooked
	goto CeladonCity_GameCorner_EventScript_FaceSlotMachine

CeladonCity_GameCorner_EventScript_Scientist::
	lock
	faceplayer
	goto CeladonCity_GameCorner_EventScript_ScientistAlreadyGotCoins

CeladonCity_GameCorner_EventScript_ScientistAlreadyGotCoins::
	msgbox CeladonCity_GameCorner_Text_NeedMoreCoinsForMonIWant
	goto CeladonCity_GameCorner_EventScript_FaceSlotMachine

CeladonCity_GameCorner_EventScript_Gentleman::
	lock
	faceplayer
	goto CeladonCity_GameCorner_EventScript_GentlemanAlreadyGotCoins

CeladonCity_GameCorner_EventScript_GentlemanAlreadyGotCoins::
	msgbox CeladonCity_GameCorner_Text_WatchReelsClosely
	goto CeladonCity_GameCorner_EventScript_FaceSlotMachine

CeladonCity_GameCorner_EventScript_Poster::
	lockall
	msgbox CeladonCity_GameCorner_Text_SwitchBehindPosterPushIt
	releaseall
	end

CeladonCity_GameCorner_EventScript_UnusableSlotMachine1::
	msgbox CeladonCity_GameCorner_Text_OutOfOrder, MSGBOX_SIGN
	end

CeladonCity_GameCorner_EventScript_UnusableSlotMachine2::
	msgbox CeladonCity_GameCorner_Text_OutToLunch, MSGBOX_SIGN
	end

CeladonCity_GameCorner_EventScript_UnusableSlotMachine3::
	msgbox CeladonCity_GameCorner_Text_SomeonesKeys, MSGBOX_SIGN
	end

CeladonCity_GameCorner_Text_CanExchangeCoinsNextDoor::
	.string "Welcome!\p"
	.string "You can exchange your COINS for\n"
	.string "fabulous prizes next door.$"


CeladonCity_GameCorner_Text_RumoredTeamRocketRunsThisPlace::
	.string "Keep this quiet.\p"
	.string "It's rumored that this place is run\n"
	.string "by TEAM ROCKET.$"


CeladonCity_GameCorner_Text_ThinkMachinesHaveDifferentOdds::
	.string "I think these machines have\n"
	.string "different odds.$"


CeladonCity_GameCorner_Text_WinsComeAndGo::
	.string "Wins seem to come and go.\n"
	.string "Nothing's a sure thing.$"


CeladonCity_GameCorner_Text_WinOrLoseItsOnlyLuck::
	.string "These slot games…\n"
	.string "Win or lose, it's only by luck.$"


CeladonCity_GameCorner_Text_RareMonsForCoins::
	.string "They offer rare POKéMON that can\n"
	.string "be exchanged for your COINS.\p"
	.string "But, I just can't seem to win!$"


CeladonCity_GameCorner_Text_SoEasyToGetHooked::
	.string "Games are scary!\n"
	.string "It's so easy to get hooked!$"


CeladonCity_GameCorner_Text_NeedMoreCoinsForMonIWant::
	.string "Darn! I need more COINS for the\n"
	.string "POKéMON I want!$"


CeladonCity_GameCorner_Text_WatchReelsClosely::
	.string "The trick is to watch the reels\n"
	.string "closely.$"


CeladonCity_GameCorner_Text_SwitchBehindPosterPushIt::
	.string "Hey!\p"
	.string "A switch behind the poster!?\n"
	.string "Let's push it!$"


CeladonCity_GameCorner_Text_OutOfOrder::
	.string "OUT OF ORDER\n"
	.string "This is broken.$"


CeladonCity_GameCorner_Text_OutToLunch::
	.string "OUT TO LUNCH\n"
	.string "This is reserved.$"


CeladonCity_GameCorner_Text_SomeonesKeys::
	.string "Someone's keys!\n"
	.string "They'll be back.$"
