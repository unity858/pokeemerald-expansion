@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

PalletTown_ProfessorOaksLab_Frlg_MapScripts::
	.byte 0

PalletTown_ProfessorOaksLab_EventScript_Aide1::
	lock
	faceplayer
	goto PalletTown_ProfessorOaksLab_EventScript_Aide1GameClear

PalletTown_ProfessorOaksLab_EventScript_Aide1GameClear::
	msgbox PalletTown_ProfessorOaksLab_Text_OakIsGoingToHaveRadioShow
	release
	end

PalletTown_ProfessorOaksLab_EventScript_Aide2::
	lock
	faceplayer
	goto PalletTown_ProfessorOaksLab_EventScript_Aide2GameClear

PalletTown_ProfessorOaksLab_EventScript_Aide2GameClear::
	msgbox PalletTown_ProfessorOaksLab_Text_DaisyWillGroomMons
	release
	end

PalletTown_ProfessorOaksLab_EventScript_Aide3::
	lock
	faceplayer
	msgbox PalletTown_ProfessorOaksLab_Text_OakIsAuthorityOnMons
	release
	end

PalletTown_ProfessorOaksLab_EventScript_Computer::
	msgbox PalletTown_ProfessorOaksLab_Text_EmailMessage, MSGBOX_SIGN
	end

PalletTown_ProfessorOaksLab_EventScript_LeftSign::
	msgbox PalletTown_ProfessorOaksLab_Text_PressStartToOpenMenu, MSGBOX_SIGN
	end

PalletTown_ProfessorOaksLab_EventScript_RightSign::
	lockall
	goto PalletTown_ProfessorOaksLab_EventScript_RightSignAlt

PalletTown_ProfessorOaksLab_EventScript_RightSignAlt::
	msgbox PalletTown_ProfessorOaksLab_Text_AllMonTypesHaveStrongAndWeakPoints
	releaseall
	end

PalletTown_ProfessorOaksLab_Text_PressStartToOpenMenu::
	.string "Press START to open the MENU!$"


PalletTown_ProfessorOaksLab_Text_AllMonTypesHaveStrongAndWeakPoints::
	.string "All POKéMON types have strong and\n"
	.string "weak points against others.$"


PalletTown_ProfessorOaksLab_Text_EmailMessage::
	.string "There's an e-mail message here.\p"
	.string "…\p"
	.string "Finally!\n"
	.string "The ultimate TRAINERS of the\l"
	.string "POKéMON LEAGUE are ready to\l"
	.string "take on all comers!\p"
	.string "Bring your best POKéMON and see\n"
	.string "how you rate as a TRAINER!\p"
	.string "POKéMON LEAGUE HQ\n"
	.string "INDIGO PLATEAU\p"
	.string "PROF. OAK, please visit us!\n"
	.string "…$"


PalletTown_ProfessorOaksLab_Text_DaisyWillGroomMons::
	.string "Hi, {PLAYER}. I bet you've become\n"
	.string "good friends with your POKéMON.\p"
	.string "By the way, did you know about\n"
	.string "DAISY?\p"
	.string "If you show DAISY your POKéMON,\n"
	.string "she can tell how much it likes you.\p"
	.string "Occasionally, she will even groom\n"
	.string "a POKéMON for you.\p"
	.string "This is a secret, so please don't\n"
	.string "tell anyone.$"


PalletTown_ProfessorOaksLab_Text_OakIsGoingToHaveRadioShow::
	.string "PROF. OAK is going to have his own\n"
	.string "radio show soon.\p"
	.string "The program will be called PROF.\n"
	.string "OAK's POKéMON SEMINAR.$"


PalletTown_ProfessorOaksLab_Text_OakIsAuthorityOnMons::
	.string "PROF. OAK may not look like much,\n"
	.string "but he's the authority on POKéMON.\p"
	.string "Many POKéMON TRAINERS hold him in\n"
	.string "high regard.$"
