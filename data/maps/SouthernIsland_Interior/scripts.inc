@ Latios and Latias are two separate statics here (no TV roamer any more).
@ Both keep the vanilla Southern Island encounter: Lv50, holding a Soul Dew.
@ Southern Island is reachable at 8 badges (Hoenn harbor ferry, or surfing
@ Route 135); the 8-badge check follows the hack's convention for statics.
SouthernIsland_Interior_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, SouthernIsland_Interior_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, SouthernIsland_Interior_OnTransition
	.byte 0

SouthernIsland_Interior_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, HackStatic_EventScript_TryRemoveCaughtMon
	end

SouthernIsland_Interior_OnTransition:
	call SouthernIsland_Interior_EventScript_SetupLatios
	call SouthernIsland_Interior_EventScript_SetupLatias
	call SouthernIsland_Interior_EventScript_SetUpPlayerGfx
	end

SouthernIsland_Interior_EventScript_SetupLatios::
	setflag FLAG_TEMP_HIDE_STATIC_MON
	goto_if_unset FLAG_BADGE08_GET, Common_EventScript_NopReturn
	goto_if_set FLAG_CAUGHT_LATIOS, Common_EventScript_NopReturn
	goto_if_set FLAG_DEFEATED_LATIOS, Common_EventScript_NopReturn
	clearflag FLAG_TEMP_HIDE_STATIC_MON
	return

SouthernIsland_Interior_EventScript_SetupLatias::
	setflag FLAG_TEMP_HIDE_STATIC_MON_2
	goto_if_unset FLAG_BADGE08_GET, Common_EventScript_NopReturn
	goto_if_set FLAG_CAUGHT_LATIAS, Common_EventScript_NopReturn
	goto_if_set FLAG_DEFEATED_LATIAS, Common_EventScript_NopReturn
	clearflag FLAG_TEMP_HIDE_STATIC_MON_2
	return

SouthernIsland_Interior_EventScript_SetUpPlayerGfx::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, SouthernIsland_Interior_EventScript_SetBrendanGfx
	goto_if_eq VAR_RESULT, FEMALE, SouthernIsland_Interior_EventScript_SetMayGfx
	end

SouthernIsland_Interior_EventScript_SetBrendanGfx::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_RIVAL_BRENDAN_NORMAL
	return

SouthernIsland_Interior_EventScript_SetMayGfx::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_RIVAL_MAY_NORMAL
	return

SouthernIsland_Interior_EventScript_Latios::
	lock
	faceplayer
	setvar VAR_0x8004, SPECIES_LATIOS
	call SouthernIsland_Interior_EventScript_LatiBattle
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, SouthernIsland_Interior_EventScript_CaughtLatios
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, SouthernIsland_Interior_EventScript_DefeatedLatios
	setvar VAR_0x8004, SPECIES_LATIOS
	goto Common_EventScript_LegendaryFlewAway
	end

SouthernIsland_Interior_EventScript_DefeatedLatios::
	setflag FLAG_DEFEATED_LATIOS
	setvar VAR_0x8004, SPECIES_LATIOS
	goto Common_EventScript_LegendaryFlewAway
	end

SouthernIsland_Interior_EventScript_CaughtLatios::
	setflag FLAG_CAUGHT_LATIOS
	release
	end

SouthernIsland_Interior_EventScript_Latias::
	lock
	faceplayer
	setvar VAR_0x8004, SPECIES_LATIAS
	call SouthernIsland_Interior_EventScript_LatiBattle
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, SouthernIsland_Interior_EventScript_CaughtLatias
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, SouthernIsland_Interior_EventScript_DefeatedLatias
	setvar VAR_0x8004, SPECIES_LATIAS
	goto Common_EventScript_LegendaryFlewAway
	end

SouthernIsland_Interior_EventScript_DefeatedLatias::
	setflag FLAG_DEFEATED_LATIAS
	setvar VAR_0x8004, SPECIES_LATIAS
	goto Common_EventScript_LegendaryFlewAway
	end

SouthernIsland_Interior_EventScript_CaughtLatias::
	setflag FLAG_CAUGHT_LATIAS
	release
	end

@ VAR_0x8004 = species. Vanilla level and held item. Returns the outcome in VAR_RESULT.
SouthernIsland_Interior_EventScript_LatiBattle::
	waitse
	playmoncry VAR_0x8004, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8005, 50
	setvar VAR_0x8006, ITEM_SOUL_DEW
	special CreateEnemyEventMon
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLatiBattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	return

SouthernIsland_Interior_EventScript_Sign::
	msgbox SouthernIsland_Interior_Text_Sign, MSGBOX_SIGN
	end
