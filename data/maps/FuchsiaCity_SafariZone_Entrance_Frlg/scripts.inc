@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

FuchsiaCity_SafariZone_Entrance_Frlg_MapScripts::
	.byte 0

FuchsiaCity_SafariZone_Entrance_EventScript_InfoAttendant::
	lock
	faceplayer
	msgbox FuchsiaCity_SafariZone_Entrance_Text_FirstTimeAtSafariZone, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, FuchsiaCity_SafariZone_Entrance_EventScript_ExplainSafariZone
	msgbox FuchsiaCity_SafariZone_Entrance_Text_SorryYoureARegularHere
	release
	end

FuchsiaCity_SafariZone_Entrance_EventScript_ExplainSafariZone::
	msgbox FuchsiaCity_SafariZone_Entrance_Text_ExplainSafariZone
	release
	end

FuchsiaCity_SafariZone_Entrance_Text_FirstTimeAtSafariZone::
	.string "Hi! Is it your first time here at\n"
	.string "the SAFARI ZONE?$"


FuchsiaCity_SafariZone_Entrance_Text_ExplainSafariZone::
	.string "The SAFARI ZONE actually has\n"
	.string "four zones in it.\p"
	.string "Each zone has different kinds of\n"
	.string "POKéMON, even some rare ones.\p"
	.string "Use the supplied SAFARI BALLS to\n"
	.string "catch them.\p"
	.string "You can also throw BAIT or ROCKS\n"
	.string "besides the SAFARI BALLS.\p"
	.string "If you throw BAIT, the POKéMON\n"
	.string "becomes less likely to flee, but\l"
	.string "harder to catch.\p"
	.string "If you throw ROCKS, the POKéMON\n"
	.string "becomes more likely to flee, but\l"
	.string "easier to catch.\p"
	.string "When you run out of time or SAFARI\n"
	.string "BALLS, it's game over for you!$"


FuchsiaCity_SafariZone_Entrance_Text_SorryYoureARegularHere::
	.string "Sorry, you're a regular here!$"
