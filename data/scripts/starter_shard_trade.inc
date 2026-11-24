@ Starter-for-shard trades (Lavaridge: fire / Red Shard, Lilycove: water / Blue Shard,
@ Fortree: grass / Green Shard). Each NPC script shows its own species list, then sets:
@   VAR_0x8008 = species (given at level 10, default level-up moves)
@   VAR_0x8009 = held item (Mega Stone of the line, or ITEM_NONE)
@   VAR_0x800A = shard item taken in exchange
@ and does `goto StarterShardTrade_EventScript_Give`. The shard is only removed once the
@ Pokémon has actually been placed in the party or PC. Repeatable: one starter per shard.

StarterShardTrade_EventScript_Give::
	copyvar VAR_TEMP_TRANSFERRED_SPECIES, VAR_0x8008
	givemon VAR_0x8008, 10, VAR_0x8009
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, StarterShardTrade_EventScript_GiveParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, StarterShardTrade_EventScript_GivePC
	goto Common_EventScript_NoMoreRoomForPokemon
	end

StarterShardTrade_EventScript_GiveParty::
	call StarterShardTrade_EventScript_ReceivedFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, StarterShardTrade_EventScript_ComeAgain
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto StarterShardTrade_EventScript_ComeAgain
	end

StarterShardTrade_EventScript_GivePC::
	call StarterShardTrade_EventScript_ReceivedFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, StarterShardTrade_EventScript_SendToPC
	call Common_EventScript_NameReceivedBoxMon
StarterShardTrade_EventScript_SendToPC::
	call Common_EventScript_TransferredToPC
	goto StarterShardTrade_EventScript_ComeAgain
	end

StarterShardTrade_EventScript_ReceivedFanfare::
	removeitem VAR_0x800A
	bufferitemname STR_VAR_2, VAR_0x800A
	msgbox StarterShardTrade_Text_HandedOverShard, MSGBOX_DEFAULT
	bufferspeciesname STR_VAR_1, VAR_0x8008
	playfanfare MUS_OBTAIN_ITEM
	message StarterShardTrade_Text_PlayerReceivedMon
	waitmessage
	waitfanfare
	goto_if_eq VAR_0x8009, ITEM_NONE, StarterShardTrade_EventScript_ReceivedFanfareEnd
	bufferitemname STR_VAR_2, VAR_0x8009
	msgbox StarterShardTrade_Text_MonHoldsStone, MSGBOX_DEFAULT
StarterShardTrade_EventScript_ReceivedFanfareEnd::
	bufferspeciesname STR_VAR_1, VAR_0x8008
	return

StarterShardTrade_EventScript_ComeAgain::
	msgbox StarterShardTrade_Text_ComeAgain, MSGBOX_DEFAULT
	release
	end

StarterShardTrade_EventScript_Declined::
	msgbox StarterShardTrade_Text_Declined, MSGBOX_DEFAULT
	release
	end

StarterShardTrade_Text_WhichOne::
	.string "Which POKéMON would you like?$"

StarterShardTrade_Text_HandedOverShard:
	.string "{PLAYER} handed over the\n"
	.string "{STR_VAR_2}.$"

StarterShardTrade_Text_PlayerReceivedMon:
	.string "{PLAYER} received {STR_VAR_1}!$"

StarterShardTrade_Text_MonHoldsStone:
	.string "Oh, and it's holding a {STR_VAR_2}.\n"
	.string "Take good care of it!$"

StarterShardTrade_Text_ComeAgain:
	.string "Come again if you want another\n"
	.string "one.$"

StarterShardTrade_Text_Declined:
	.string "Oh well, come again if you change\n"
	.string "your mind.$"

@ Choice list entries
StarterShardTrade_Text_Charmander::
	.string "Charmander$"
StarterShardTrade_Text_Cyndaquil::
	.string "Cyndaquil$"
StarterShardTrade_Text_Torchic::
	.string "Torchic$"
StarterShardTrade_Text_Chimchar::
	.string "Chimchar$"
StarterShardTrade_Text_Tepig::
	.string "Tepig$"
StarterShardTrade_Text_Fennekin::
	.string "Fennekin$"
StarterShardTrade_Text_Litten::
	.string "Litten$"
StarterShardTrade_Text_Scorbunny::
	.string "Scorbunny$"
StarterShardTrade_Text_Fuecoco::
	.string "Fuecoco$"

StarterShardTrade_Text_Squirtle::
	.string "Squirtle$"
StarterShardTrade_Text_Totodile::
	.string "Totodile$"
StarterShardTrade_Text_Mudkip::
	.string "Mudkip$"
StarterShardTrade_Text_Piplup::
	.string "Piplup$"
StarterShardTrade_Text_Oshawott::
	.string "Oshawott$"
StarterShardTrade_Text_Froakie::
	.string "Froakie$"
StarterShardTrade_Text_Popplio::
	.string "Popplio$"
StarterShardTrade_Text_Sobble::
	.string "Sobble$"
StarterShardTrade_Text_Quaxly::
	.string "Quaxly$"

StarterShardTrade_Text_Bulbasaur::
	.string "Bulbasaur$"
StarterShardTrade_Text_Chikorita::
	.string "Chikorita$"
StarterShardTrade_Text_Treecko::
	.string "Treecko$"
StarterShardTrade_Text_Turtwig::
	.string "Turtwig$"
StarterShardTrade_Text_Snivy::
	.string "Snivy$"
StarterShardTrade_Text_Chespin::
	.string "Chespin$"
StarterShardTrade_Text_Rowlet::
	.string "Rowlet$"
StarterShardTrade_Text_Grookey::
	.string "Grookey$"
StarterShardTrade_Text_Sprigatito::
	.string "Sprigatito$"
