@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

CeruleanCity_House2_Frlg_MapScripts::
	.byte 0

CeruleanCity_House2_EventScript_Hiker::
	lock
	faceplayer
	goto CeruleanCity_House2_EventScript_HikerGotTM28

CeruleanCity_House2_EventScript_HikerGotTM28::
	msgbox CeruleanCity_House2_Text_TeachDiglettDigWithoutTM
	release
	end

CeruleanCity_House2_EventScript_Lass::
	msgbox CeruleanCity_House2_Text_TeamRocketTryingToDigIntoNoGood, MSGBOX_NPC
	end

CeruleanCity_House2_EventScript_WallHole::
	msgbox CeruleanCity_House2_Text_TeamRocketLeftWayOut, MSGBOX_SIGN
	end

CeruleanCity_House2_Text_TeachDiglettDigWithoutTM::
	.string "I figure what's lost is lost.\p"
	.string "I decided to teach DIGLETT how to\n"
	.string "DIG without a TM.$"


CeruleanCity_House2_Text_TeamRocketTryingToDigIntoNoGood::
	.string "TEAM ROCKET must be trying to DIG\n"
	.string "their way into no good!$"


CeruleanCity_House2_Text_TeamRocketLeftWayOut::
	.string "TEAM ROCKET left a way out!$"
