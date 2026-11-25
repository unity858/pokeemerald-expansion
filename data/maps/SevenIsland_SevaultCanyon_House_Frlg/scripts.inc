@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

SevenIsland_SevaultCanyon_House_Frlg_MapScripts::
	.byte 0

SevenIsland_SevaultCanyon_House_EventScript_Chansey::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_CHANSEY, CRY_MODE_NORMAL
	msgbox SevenIsland_SevaultCanyon_House_Text_Chansey
	waitmoncry
	release
	end

SevenIsland_SevaultCanyon_House_Text_Chansey::
	.string "CHANSEY: Chansi! Chansi!$"

@ Poipole gift (postgame, once). Party full -> PC.
SevenIsland_SevaultCanyon_House_EventScript_PoipoleResearcher::
	lock
	faceplayer
	goto_if_staticenc GIFT_POIPOLE, RECEIVED, SevenIsland_SevaultCanyon_House_EventScript_PoipoleGiven
	goto_if_unset FLAG_SYS_GAME_CLEAR, SevenIsland_SevaultCanyon_House_EventScript_PoipoleNotYet
	msgbox SevenIsland_SevaultCanyon_House_Text_OfferPoipole, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SevenIsland_SevaultCanyon_House_EventScript_DeclinePoipole
	givegiftmon GIFT_POIPOLE, SPECIES_POIPOLE
	goto_if_eq VAR_RESULT, FALSE, SevenIsland_SevaultCanyon_House_EventScript_PoipoleEnd
	msgbox SevenIsland_SevaultCanyon_House_Text_PoipoleReceived, MSGBOX_DEFAULT
SevenIsland_SevaultCanyon_House_EventScript_PoipoleEnd::
	release
	end

SevenIsland_SevaultCanyon_House_EventScript_PoipoleNotYet::
	msgbox SevenIsland_SevaultCanyon_House_Text_PoipoleNotYet, MSGBOX_DEFAULT
	release
	end

SevenIsland_SevaultCanyon_House_EventScript_DeclinePoipole::
	msgbox SevenIsland_SevaultCanyon_House_Text_DeclinedPoipole, MSGBOX_DEFAULT
	release
	end

SevenIsland_SevaultCanyon_House_EventScript_PoipoleGiven::
	msgbox SevenIsland_SevaultCanyon_House_Text_PoipoleGiven, MSGBOX_DEFAULT
	release
	end

SevenIsland_SevaultCanyon_House_Text_PoipoleNotYet:
	.string "A strange light opened in the sky\n"
	.string "over the canyon one night…\p"
	.string "And this odd little POKéMON fell\n"
	.string "out of it.\p"
	.string "I'm looking for a TRAINER worthy\n"
	.string "of it. Someone who has stood at\l"
	.string "the top of a POKéMON LEAGUE…$"

SevenIsland_SevaultCanyon_House_Text_OfferPoipole:
	.string "A strange light opened in the sky\n"
	.string "over the canyon one night, and a\l"
	.string "little POKéMON fell out of it.\p"
	.string "You're a CHAMPION, aren't you?\n"
	.string "It seems to like you.\p"
	.string "Will you take care of it?$"

SevenIsland_SevaultCanyon_House_Text_DeclinedPoipole:
	.string "Oh… It looks disappointed.\n"
	.string "Come back if you change your mind.$"

SevenIsland_SevaultCanyon_House_Text_PoipoleReceived:
	.string "That's POIPOLE. No one here has\n"
	.string "ever seen one before.\p"
	.string "I wonder what world it came from…$"

SevenIsland_SevaultCanyon_House_Text_PoipoleGiven:
	.string "How's POIPOLE doing?\n"
	.string "I still watch the sky at night,\l"
	.string "in case that light comes back.$"

