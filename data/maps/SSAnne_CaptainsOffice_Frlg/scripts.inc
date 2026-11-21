@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

SSAnne_CaptainsOffice_Frlg_MapScripts::
	.byte 0

SSAnne_CaptainsOffice_EventScript_Captain::
	lock
	goto SSAnne_CaptainsOffice_EventScript_AlreadyGotCut

SSAnne_CaptainsOffice_EventScript_AlreadyGotCut::
	applymovement LOCALID_SS_ANNE_CAPTAIN, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SSAnne_CaptainsOffice_Text_SSAnneWillSetSailSoon
	release
	end

SSAnne_CaptainsOffice_EventScript_TrashCan::
	msgbox SSAnne_CaptainsOffice_Text_YuckShouldntHaveLooked, MSGBOX_SIGN
	end

SSAnne_CaptainsOffice_EventScript_Book::
	msgbox SSAnne_CaptainsOffice_Text_HowToConquerSeasickness, MSGBOX_SIGN
	end

SSAnne_CaptainsOffice_Text_SSAnneWillSetSailSoon::
	.string "CAPTAIN: …Whew!\p"
	.string "Now that I'm not sick anymore,\n"
	.string "I guess it's time.\p"
	.string "The S.S. ANNE will set sail soon!\p"
	.string "Farewell, until our return to\n"
	.string "VERMILION CITY!$"


SSAnne_CaptainsOffice_Text_YuckShouldntHaveLooked::
	.string "Yuck!\n"
	.string "Shouldn't have looked!$"


SSAnne_CaptainsOffice_Text_HowToConquerSeasickness::
	.string "How to Conquer Seasickness…\n"
	.string "The CAPTAIN's reading this!$"
