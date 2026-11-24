RustboroCity_House1_MapScripts::
	.byte 0

@ R.O.W.E. Tradeback Guy: trades the player's own Pokemon back to them, so
@ Pokemon that evolve by trading can evolve. Free, unlimited, no flags.
RustboroCity_House1_EventScript_Trader::
	lock
	faceplayer
	msgbox RustboroCity_House1_Text_TradebackGuyIntro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_House1_EventScript_TradebackDecline
	special ChoosePartyMon
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, RustboroCity_House1_EventScript_TradebackDecline
	special IsSelectedMonEgg
	goto_if_eq VAR_RESULT, TRUE, RustboroCity_House1_EventScript_TradebackEgg
	special IsSelectedMonHoldingMail
	goto_if_eq VAR_RESULT, TRUE, RustboroCity_House1_EventScript_TradebackMail
	setvar VAR_0x8005, INGAME_TRADE_TRADEBACK
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	msgbox RustboroCity_House1_Text_TradebackComeBack, MSGBOX_DEFAULT
	release
	end

RustboroCity_House1_EventScript_TradebackDecline::
	msgbox RustboroCity_House1_Text_TradebackDecline, MSGBOX_DEFAULT
	release
	end

RustboroCity_House1_EventScript_TradebackEgg::
	msgbox RustboroCity_House1_Text_TradebackEgg, MSGBOX_DEFAULT
	release
	end

RustboroCity_House1_EventScript_TradebackMail::
	msgbox RustboroCity_House1_Text_TradebackMail, MSGBOX_DEFAULT
	release
	end

RustboroCity_House1_EventScript_Hiker::
	msgbox RustboroCity_House1_Text_AllSortsOfPlaces, MSGBOX_NPC
	end

RustboroCity_House1_Text_TradebackGuyIntro:
	.string "Hi! I'm the Tradeback Guy!\p"
	.string "If you have a Pokémon that only\n"
	.string "evolves through trading, then I\l"
	.string "can help you out!\p"
	.string "Do you have any Pokémon that you'd\n"
	.string "like to evolve?$"

RustboroCity_House1_Text_TradebackComeBack:
	.string "Come back anytime!$"

RustboroCity_House1_Text_TradebackDecline:
	.string "Alright. Well, if you change\n"
	.string "your mind, I'll be here.$"

RustboroCity_House1_Text_TradebackEgg:
	.string "Whoa, that's an Egg!\p"
	.string "Eggs can't evolve, so there's no\n"
	.string "point in trading one. Come back\l"
	.string "once it's hatched!$"

RustboroCity_House1_Text_TradebackMail:
	.string "Oh, that Pokémon is holding Mail.\p"
	.string "I wouldn't want the Mail to get\n"
	.string "lost in the trade. Please take it\l"
	.string "off first, then come see me.$"

RustboroCity_House1_Text_AllSortsOfPlaces:
	.string "In all sorts of places, there are all\n"
	.string "sorts of POKéMON and people.\p"
	.string "I find that fascinating, so I go to all\n"
	.string "sorts of places.$"

