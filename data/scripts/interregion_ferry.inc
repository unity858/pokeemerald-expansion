@ Inter-region ferry: the SEAGALLOP HI-SPEED line between Hoenn (Slateport and
@ Lilycove harbors), Vermilion City and the Sevii Islands.
@
@ Unlocks (flags only, no ticket items):
@   Sevii Islands  FLAG_BADGE08_GET (or FLAG_SYS_GAME_CLEAR)
@   Southern Island FLAG_BADGE08_GET (Hoenn harbors; boat, not the Seagallop)
@   Vermilion City FLAG_SYS_GAME_CLEAR
@
@ Ports call these with VAR_0x8004 = SEAGALLOP_* id of the port the player is at.
@ Destination list items use SEAGALLOP_* ids; the trip itself is FRLG's Seagallop
@ cutscene (DoSeagallopFerryScene, src/seagallop.c), which warps to the
@ destination dock.

@ Kanto/Sevii harbor attendants
InterRegionFerry_EventScript_SeagallopSailor::
	lock
	faceplayer
	message InterRegionFerry_Text_WhereDoYouWantToSail
	waitmessage
	call InterRegionFerry_EventScript_PushSeagallopDests
	call InterRegionFerry_EventScript_ShowDestList
	goto_if_eq VAR_RESULT, FERRY_DEST_CANCEL, InterRegionFerry_EventScript_SailAnotherTime
	goto InterRegionFerry_EventScript_Sail
	end

@ Pushes the Seagallop destinations available from port VAR_0x8004
InterRegionFerry_EventScript_PushSeagallopDests::
	goto_if_ge VAR_0x8004, SEAGALLOP_SLATEPORT, InterRegionFerry_EventScript_PushDestsFromHoenn
	dynmultipush InterRegionFerry_Text_SlateportCity, SEAGALLOP_SLATEPORT
	dynmultipush InterRegionFerry_Text_LilycoveCity, SEAGALLOP_LILYCOVE
	call_if_set FLAG_SYS_GAME_CLEAR, InterRegionFerry_EventScript_TryPushVermilion
	call_if_ne VAR_0x8004, SEAGALLOP_ONE_ISLAND, InterRegionFerry_EventScript_PushOneIsland
	call_if_ne VAR_0x8004, SEAGALLOP_TWO_ISLAND, InterRegionFerry_EventScript_PushTwoIsland
	call_if_ne VAR_0x8004, SEAGALLOP_THREE_ISLAND, InterRegionFerry_EventScript_PushThreeIsland
	call_if_ne VAR_0x8004, SEAGALLOP_FOUR_ISLAND, InterRegionFerry_EventScript_PushFourIsland
	call_if_ne VAR_0x8004, SEAGALLOP_FIVE_ISLAND, InterRegionFerry_EventScript_PushFiveIsland
	call_if_ne VAR_0x8004, SEAGALLOP_SIX_ISLAND, InterRegionFerry_EventScript_PushSixIsland
	call_if_ne VAR_0x8004, SEAGALLOP_SEVEN_ISLAND, InterRegionFerry_EventScript_PushSevenIsland
	return

@ From Hoenn the Sevii Islands are a single stop (One Island)
InterRegionFerry_EventScript_PushDestsFromHoenn::
	call_if_set FLAG_BADGE08_GET, InterRegionFerry_EventScript_PushSeviiIslands
	call_if_unset FLAG_BADGE08_GET, InterRegionFerry_EventScript_TryPushSeviiAfterGameClear
	call_if_set FLAG_SYS_GAME_CLEAR, InterRegionFerry_EventScript_PushVermilion
	return

InterRegionFerry_EventScript_TryPushSeviiAfterGameClear::
	goto_if_unset FLAG_SYS_GAME_CLEAR, Common_EventScript_NopReturn
InterRegionFerry_EventScript_PushSeviiIslands::
	dynmultipush InterRegionFerry_Text_SeviiIslands, SEAGALLOP_ONE_ISLAND
	return

InterRegionFerry_EventScript_TryPushVermilion::
	goto_if_eq VAR_0x8004, SEAGALLOP_VERMILION_CITY, Common_EventScript_NopReturn
InterRegionFerry_EventScript_PushVermilion::
	dynmultipush InterRegionFerry_Text_VermilionCity, SEAGALLOP_VERMILION_CITY
	return

InterRegionFerry_EventScript_PushOneIsland::
	dynmultipush InterRegionFerry_Text_OneIsland, SEAGALLOP_ONE_ISLAND
	return

InterRegionFerry_EventScript_PushTwoIsland::
	dynmultipush InterRegionFerry_Text_TwoIsland, SEAGALLOP_TWO_ISLAND
	return

InterRegionFerry_EventScript_PushThreeIsland::
	dynmultipush InterRegionFerry_Text_ThreeIsland, SEAGALLOP_THREE_ISLAND
	return

InterRegionFerry_EventScript_PushFourIsland::
	dynmultipush InterRegionFerry_Text_FourIsland, SEAGALLOP_FOUR_ISLAND
	return

InterRegionFerry_EventScript_PushFiveIsland::
	dynmultipush InterRegionFerry_Text_FiveIsland, SEAGALLOP_FIVE_ISLAND
	return

InterRegionFerry_EventScript_PushSixIsland::
	dynmultipush InterRegionFerry_Text_SixIsland, SEAGALLOP_SIX_ISLAND
	return

InterRegionFerry_EventScript_PushSevenIsland::
	dynmultipush InterRegionFerry_Text_SevenIsland, SEAGALLOP_SEVEN_ISLAND
	return

@ Adds CANCEL and shows the pushed list (scrolls past 6 rows). B returns FERRY_DEST_CANCEL.
InterRegionFerry_EventScript_ShowDestList::
	dynmultipush InterRegionFerry_Text_Cancel, FERRY_DEST_CANCEL
	dynmultistack 30, 1, FALSE, 6, FALSE, 0xFF, DYN_MULTICHOICE_CB_NONE  @ 0xFF: no item id, start on the first row
	return

@ Hoenn harbor attendant before the Hoenn League is beaten, with 8 badges:
@ the S.S. TIDAL isn't running yet, but the Seagallop to the Sevii Islands is,
@ and so is the boat to Southern Island. VAR_0x8004 = SEAGALLOP_SLATEPORT/LILYCOVE.
InterRegionFerry_EventScript_HoennOfferSevii::
	message InterRegionFerry_Text_SeagallopToSeviiIsCalling
	waitmessage
	call InterRegionFerry_EventScript_PushSeviiIslands
	dynmultipush InterRegionFerry_Text_SouthernIsland, FERRY_DEST_SOUTHERN_ISLAND
	call InterRegionFerry_EventScript_ShowDestList
	goto_if_eq VAR_RESULT, FERRY_DEST_CANCEL, InterRegionFerry_EventScript_SailAnotherTime
	goto_if_eq VAR_RESULT, FERRY_DEST_SOUTHERN_ISLAND, InterRegionFerry_EventScript_HoennToSouthernIsland
	goto InterRegionFerry_EventScript_Sail
	end

@ Reuses the harbors' own Southern Island trips, so the island's sailor knows
@ which harbor to bring the player back to.
InterRegionFerry_EventScript_HoennToSouthernIsland::
	goto_if_eq VAR_0x8004, SEAGALLOP_SLATEPORT, SlateportCity_Harbor_EventScript_SouthernIsland
	goto LilycoveCity_Harbor_EventScript_GoToSouthernIsland
	end

@ VAR_0x8004 = origin port, VAR_RESULT = destination port
InterRegionFerry_EventScript_Sail::
	copyvar VAR_0x8006, VAR_RESULT
	specialvar VAR_RESULT, GetSeagallopNumber
	buffernumberstring STR_VAR_1, VAR_RESULT
	msgbox InterRegionFerry_Text_AllAboardSeagallopNum
	closemessage
	delay 20
	fadescreen FADE_TO_BLACK
	special DoSeagallopFerryScene
	waitstate
	end

InterRegionFerry_EventScript_SailAnotherTime::
	msgbox InterRegionFerry_Text_SailAnotherTime, MSGBOX_DEFAULT
	release
	end

InterRegionFerry_Text_WhereDoYouWantToSail:
	.string "Where would you like to sail?$"

InterRegionFerry_Text_SeagallopToSeviiIsCalling:
	.string "Hello! The S.S. TIDAL isn't in service\n"
	.string "yet, I'm afraid.\p"
	.string "But the SEAGALLOP HI-SPEED calls here\n"
	.string "for TRAINERS with all eight HOENN\l"
	.string "GYM BADGES.\p"
	.string "We can also take you to SOUTHERN\n"
	.string "ISLAND. Where would you like to sail?$"

InterRegionFerry_Text_AllAboardSeagallopNum:
	.string "All right!\n"
	.string "All aboard SEAGALLOP HI-SPEED {STR_VAR_1}!$"

InterRegionFerry_Text_SailAnotherTime:
	.string "Please sail with us another time!$"

InterRegionFerry_Text_SlateportCity:
	.string "SLATEPORT CITY$"

InterRegionFerry_Text_LilycoveCity:
	.string "LILYCOVE CITY$"

InterRegionFerry_Text_VermilionCity:
	.string "VERMILION CITY$"

InterRegionFerry_Text_SeviiIslands:
	.string "SEVII ISLANDS$"

InterRegionFerry_Text_OneIsland:
	.string "ONE ISLAND$"

InterRegionFerry_Text_TwoIsland:
	.string "TWO ISLAND$"

InterRegionFerry_Text_ThreeIsland:
	.string "THREE ISLAND$"

InterRegionFerry_Text_FourIsland:
	.string "FOUR ISLAND$"

InterRegionFerry_Text_FiveIsland:
	.string "FIVE ISLAND$"

InterRegionFerry_Text_SixIsland:
	.string "SIX ISLAND$"

InterRegionFerry_Text_SevenIsland:
	.string "SEVEN ISLAND$"

InterRegionFerry_Text_BattleFrontier::
	.string "BATTLE FRONTIER$"

InterRegionFerry_Text_SouthernIsland::
	.string "SOUTHERN ISLAND$"

InterRegionFerry_Text_NavelRock::
	.string "NAVEL ROCK$"

InterRegionFerry_Text_BirthIsland::
	.string "BIRTH ISLAND$"

InterRegionFerry_Text_FarawayIsland::
	.string "FARAWAY ISLAND$"

InterRegionFerry_Text_Cancel:
	.string "CANCEL$"

InterRegionFerry_Text_ChampionSailsFree::
	.string "Hello, are you here for the ferry?\p"
	.string "Our CHAMPION sails free of charge!\n"
	.string "Where would you like to go?$"
