@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

.equ RETURN_AFTER_SS_TICKET, FLAG_TEMP_3

Route25_SeaCottage_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route25_SeaCottage_OnTransition
	.byte 0

Route25_SeaCottage_OnTransition::
	call Route25_SeaCottage_EventScript_SetReturnedAfterSSTicket
	end

Route25_SeaCottage_EventScript_SetReturnedAfterSSTicket::
	setflag RETURN_AFTER_SS_TICKET
	return

Route25_SeaCottage_EventScript_Bill::
	lock
	faceplayer
	goto_if_set RETURN_AFTER_SS_TICKET, Route25_SeaCottage_EventScript_BillGoLookAtPC
	goto Route25_SeaCottage_EventScript_BillGoToSSAnne

Route25_SeaCottage_EventScript_BillGoToSSAnne::
	msgbox Route25_SeaCottage_Text_SSAnnePartyYouGoInstead
	release
	end

Route25_SeaCottage_EventScript_BillGoLookAtPC::
	msgbox Route25_SeaCottage_Text_CheckOutRareMonsOnPC
	release
	end

Route25_SeaCottage_Text_SSAnnePartyYouGoInstead::
	.string "That cruise ship S.S. ANNE is in\n"
	.string "VERMILION CITY.\p"
	.string "I hear there are lots of TRAINERS\n"
	.string "on board, too.\p"
	.string "They invited me to their party, but\n"
	.string "I can't stand fancy do's.\p"
	.string "Why don't you go instead of me?\n"
	.string "Go on and have a good time.$"


Route25_SeaCottage_Text_CheckOutRareMonsOnPC::
	.string "BILL: Feel like checking out some\n"
	.string "of my rare POKéMON on my PC?\p"
	.string "Go on, check out my PC.$"
