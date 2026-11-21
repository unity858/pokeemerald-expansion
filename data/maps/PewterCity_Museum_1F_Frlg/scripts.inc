@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

PewterCity_Museum_1F_Frlg_MapScripts::
	.byte 0

PewterCity_Museum_1F_EventScript_Scientist1::
	lock
	faceplayer
	goto_if_eq VAR_FACING, DIR_WEST, PewterCity_Museum_1F_EventScript_Scientist1BehindCounter
	goto_if_eq VAR_FACING, DIR_SOUTH, PewterCity_Museum_1F_EventScript_Scientist1BehindCounter
	goto_if_eq VAR_FACING, DIR_NORTH, PewterCity_Museum_1F_EventScript_Scientist1BehindCounter
	msgbox PewterCity_Museum_1F_Text_PleaseEnjoyYourself
	release
	end

PewterCity_Museum_1F_EventScript_Scientist1BehindCounter::
	msgbox PewterCity_Museum_1F_Text_DoYouKnowWhatAmberIs, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PewterCity_Museum_1F_EventScript_AmberHasGeneticMatter
	goto_if_eq VAR_RESULT, NO, PewterCity_Museum_1F_EventScript_ExplainAmber
	end

PewterCity_Museum_1F_EventScript_AmberHasGeneticMatter::
	msgbox PewterCity_Museum_1F_Text_AmberContainsGeneticMatter
	waitmovement 0
	release
	end

PewterCity_Museum_1F_EventScript_ExplainAmber::
	msgbox PewterCity_Museum_1F_Text_AmberIsFossilizedSap
	waitmovement 0
	release
	end

PewterCity_Museum_1F_EventScript_Scientist2::
	msgbox PewterCity_Museum_1F_Text_WeHaveTwoFossilsOnExhibit, MSGBOX_NPC
	end

PewterCity_Museum_1F_EventScript_OldMan::
	msgbox PewterCity_Museum_1F_Text_ShouldBeGratefulForLongLife, MSGBOX_NPC
	end

PewterCity_Museum_1F_EventScript_OldAmberScientist::
	lock
	faceplayer
	goto PewterCity_Museum_1F_EventScript_AlreadyGotOldAmber

PewterCity_Museum_1F_EventScript_AlreadyGotOldAmber::
	msgbox PewterCity_Museum_1F_Text_GetOldAmberChecked
	release
	end

PewterCity_Museum_1F_Text_PleaseEnjoyYourself::
	.string "Please enjoy yourself.$"


PewterCity_Museum_1F_Text_DoYouKnowWhatAmberIs::
	.string "You can't sneak in the back way!\n"
	.string "Nice try, kid, but no.\p"
	.string "Oh, whatever!\n"
	.string "Do you know what AMBER is?$"


PewterCity_Museum_1F_Text_AmberContainsGeneticMatter::
	.string "AMBER contains the genetic matter\n"
	.string "of ancient POKéMON.\p"
	.string "There's a LAB somewhere trying to\n"
	.string "resurrect POKéMON from AMBER.$"


PewterCity_Museum_1F_Text_AmberIsFossilizedSap::
	.string "AMBER is actually sap, that gooey\n"
	.string "stuff that oozes from trees.\p"
	.string "The ancient sap fossilized over\n"
	.string "time to become rock-hard AMBER.$"

@ Unused

PewterCity_Museum_1F_Text_ShouldBeGratefulForLongLife::
	.string "I should be grateful for my long\n"
	.string "life.\p"
	.string "Never did I think I would get to\n"
	.string "see the bones of a dragon!$"


PewterCity_Museum_1F_Text_GetOldAmberChecked::
	.string "Ssh!\n"
	.string "Get the OLD AMBER checked!$"


PewterCity_Museum_1F_Text_WeHaveTwoFossilsOnExhibit::
	.string "We have two fossils of rare,\n"
	.string "prehistoric POKéMON on exhibit.$"
