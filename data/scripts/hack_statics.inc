@ Shared scripts for the hack's added static legendaries and gift Pokémon.
@ Their level comes from GetScaledStaticLevel (src/level_scaling.c): the scaled wild level
@ for the current badge stage and difficulty. Vanilla statics keep their fixed levels.
@
@ Their state is a STATIC_ENC_* / GIFT_* ID (include/constants/static_encounters.h) with
@ 2 bits in SaveBlock3 (src/static_encounters.c), not event flags:
@ DEFEATED = knocked out, cleared again by the Hall of Fame (hall_of_fame.inc);
@ CAUGHT = gone for good; RECEIVED = gift given.
@
@ A static needs three things on its map (macros in asm/macros/event.inc):
@   ON_TRANSITION:  setupstaticenc STATIC_ENC_X, FLAG_TEMP_HIDE_STATIC_MON[, gateFlag]
@                   (hides the object unless gated in and neither caught nor knocked out;
@                   gateFlag defaults to FLAG_BADGE08_GET)
@   ON_RESUME:      call_if_set FLAG_SYS_CTRL_OBJ_DELETE, HackStatic_EventScript_TryRemoveCaughtMon
@   its object:     staticencounter STATIC_ENC_X, SPECIES_X[, battle script]
@ A gift: goto_if_staticenc GIFT_X, RECEIVED, <already given> ... givegiftmon GIFT_X, SPECIES_X

@ Static legendary battles. Set VAR_0x8004 = species and VAR_0x8006 = held item first.
@ Each plays the cry, creates the Pokémon at the scaled level and starts the battle.
@ The battle outcome is returned in VAR_RESULT.
HackStatic_EventScript_LegendaryBattle::
	call HackStatic_EventScript_Cry
@ Same, for scripts that played the cry themselves (e.g. the Kanto birds' "Gyaoo!").
HackStatic_EventScript_LegendaryBattleNoCry::
	call HackStatic_EventScript_CreateMon
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	return

@ The Kanto birds: "Gyaoo!" with their cry, the FRLG legendary music, then the battle.
HackStatic_EventScript_GyaooBattle::
	waitse
	playmoncry VAR_0x8004, CRY_MODE_ENCOUNTER
	message Text_Gyaoo
	waitmessage
	waitmoncry
	delay 10
	playbgm MUS_RG_ENCOUNTER_GYM_LEADER, 0
	waitbuttonpress
	goto HackStatic_EventScript_LegendaryBattleNoCry

HackStatic_EventScript_RegiBattle::
	call HackStatic_EventScript_CryAndCreateMon
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special StartRegiBattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	return

HackStatic_EventScript_CryAndCreateMon::
	call HackStatic_EventScript_Cry
HackStatic_EventScript_CreateMon::
	specialvar VAR_0x8005, GetScaledStaticLevel
	special CreateEnemyEventMon
	return

HackStatic_EventScript_Cry::
	waitse
	playmoncry VAR_0x8004, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	return

@ End of the staticencounter macro, after the battle. VAR_RESULT = battle outcome,
@ VAR_0x8004 = species, VAR_0x8005 = encounter ID.
@ Caught: gone for good. Knocked out: back after the next Hall of Fame. Either way,
@ and on running away, the object leaves (the caught one was removed on resume).
HackStatic_EventScript_SetOutcome::
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, HackStatic_EventScript_SetCaught
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, HackStatic_EventScript_SetDefeated
	goto Common_EventScript_LegendaryFlewAway
	end

HackStatic_EventScript_SetDefeated::
	setstaticenc VAR_0x8005, DEFEATED
	goto Common_EventScript_LegendaryFlewAway
	end

HackStatic_EventScript_SetCaught::
	setstaticenc VAR_0x8005, CAUGHT
	release
	end

@ ON_RESUME: after a battle started from one of the statics above, remove the
@ object straight away if it was caught.
HackStatic_EventScript_TryRemoveCaughtMon::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

@ Gift Pokémon at the scaled level. Set VAR_0x8008 = species first.
@ Party full -> sent to the PC. Returns VAR_RESULT = TRUE if it was given,
@ FALSE if there was no room anywhere (the "no more room" message has been shown).
HackGift_EventScript_GiveMon::
	copyvar VAR_TEMP_TRANSFERRED_SPECIES, VAR_0x8008
	specialvar VAR_0x8005, GetScaledStaticLevel
	givemon VAR_0x8008, VAR_0x8005
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, HackGift_EventScript_GiveParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, HackGift_EventScript_GivePC
	msgbox gText_NoMoreRoomForPokemon, MSGBOX_DEFAULT
	setvar VAR_RESULT, FALSE
	return

HackGift_EventScript_GiveParty::
	call HackGift_EventScript_ReceivedFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, HackGift_EventScript_Given
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto HackGift_EventScript_Given

HackGift_EventScript_GivePC::
	call HackGift_EventScript_ReceivedFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, HackGift_EventScript_SendToPC
	call Common_EventScript_NameReceivedBoxMon
HackGift_EventScript_SendToPC::
	call Common_EventScript_TransferredToPC
HackGift_EventScript_Given::
	setvar VAR_RESULT, TRUE
	return

HackGift_EventScript_ReceivedFanfare::
	bufferspeciesname STR_VAR_1, VAR_0x8008
	playfanfare MUS_OBTAIN_ITEM
	message HackGift_Text_PlayerReceivedMon
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, VAR_0x8008
	return

HackGift_Text_PlayerReceivedMon:
	.string "{PLAYER} received {STR_VAR_1}!$"
