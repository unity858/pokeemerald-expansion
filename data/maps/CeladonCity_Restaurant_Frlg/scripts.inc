@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

CeladonCity_Restaurant_Frlg_MapScripts::
	.byte 0

CeladonCity_Restaurant_EventScript_Chef::
	msgbox CeladonCity_Restaurant_Text_TakingBreakRightNow, MSGBOX_NPC
	end

CeladonCity_Restaurant_EventScript_Woman::
	msgbox CeladonCity_Restaurant_Text_OftenGoToDrugstore, MSGBOX_NPC
	end

CeladonCity_Restaurant_EventScript_CoinCaseMan::
	lock
	faceplayer
	goto CeladonCity_Restaurant_EventScript_AlreadyGotCoinCase

CeladonCity_Restaurant_EventScript_AlreadyGotCoinCase::
	msgbox CeladonCity_Restaurant_Text_ThoughtIdWinItBack
	release
	end

CeladonCity_Restaurant_EventScript_WorkerM::
	msgbox CeladonCity_Restaurant_Text_PsstBasementUnderGameCorner, MSGBOX_NPC
	end

CeladonCity_Restaurant_EventScript_FatMan::
	msgbox CeladonCity_Restaurant_Text_ManLostItAllAtSlots, MSGBOX_NPC
	end

CeladonCity_Restaurant_Text_TakingBreakRightNow::
	.string "Hi!\p"
	.string "Sorry, but we're taking a break\n"
	.string "right now.$"


CeladonCity_Restaurant_Text_OftenGoToDrugstore::
	.string "My POKéMON are weak, so I often\n"
	.string "have to go to the DRUGSTORE.$"


CeladonCity_Restaurant_Text_PsstBasementUnderGameCorner::
	.string "Psst! There's a basement under the\n"
	.string "GAME CORNER, I hear.$"


CeladonCity_Restaurant_Text_ManLostItAllAtSlots::
	.string "Munch…\p"
	.string "The man at that table lost it all\n"
	.string "at the slots.$"


CeladonCity_Restaurant_Text_ThoughtIdWinItBack::
	.string "I always thought I was going to\n"
	.string "win it back…$"
