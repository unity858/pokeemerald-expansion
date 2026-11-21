@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

SafariZone_Center_Frlg_MapScripts::
	.byte 0

SafariZone_Center_EventScript_RestHouseSign::
	msgbox SafariZone_Center_Text_RestHouse, MSGBOX_SIGN
	end

SafariZone_Center_EventScript_TrainerTips::
	msgbox SafariZone_Center_Text_PressStartToCheckTime, MSGBOX_SIGN
	end

SafariZone_Center_EventScript_AreaSign::
	msgbox SafariZone_Center_Text_CenterArea, MSGBOX_SIGN
	end

SafariZone_Center_Text_RestHouse::
	.string "REST HOUSE$"


SafariZone_Center_Text_PressStartToCheckTime::
	.string "TRAINER TIPS\p"
	.string "Press START to check\n"
	.string "remaining time.$"


SafariZone_Center_Text_CenterArea::
	.string "CENTER AREA$"
