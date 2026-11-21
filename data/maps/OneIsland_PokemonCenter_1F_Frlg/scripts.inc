@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

OneIsland_PokemonCenter_1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, OneIsland_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	map_script MAP_SCRIPT_ON_LOAD, OneIsland_PokemonCenter_1F_OnLoad
	.byte 0

OneIsland_PokemonCenter_1F_OnLoad::
	call OneIsland_PokemonCenter_1F_EventScript_SetRubyMetatile
	call OneIsland_PokemonCenter_1F_EventScript_SetNetworkMachineOn
	end

OneIsland_PokemonCenter_1F_EventScript_SetRubyMetatile::
	setmetatile 13, 4, METATILE_PokemonCenterFrlg_NetworkMachine_Ruby, 1
	return

OneIsland_PokemonCenter_1F_EventScript_SetSapphireMetatile::
	setmetatile 16, 4, METATILE_PokemonCenterFrlg_NetworkMachine_Sapphire, 1
	return

OneIsland_PokemonCenter_1F_EventScript_SetNetworkMachineOn::
	call OneIsland_PokemonCenter_1F_EventScript_SetSapphireMetatile
	setmetatile 14, 4, METATILE_PokemonCenterFrlg_NetworkMachine_ScreenLeft_On, 1
	setmetatile 15, 4, METATILE_PokemonCenterFrlg_NetworkMachine_ScreenRight_On, 1
	return

OneIsland_PokemonCenter_1F_OnTransition::
	setrespawn HEAL_LOCATION_ONE_ISLAND
	end

OneIsland_PokemonCenter_1F_EventScript_Celio::
	lock
	faceplayer
	goto OneIsland_PokemonCenter_1F_EventScript_CelioGiveBillFact

OneIsland_PokemonCenter_1F_EventScript_CelioGiveBillFact::
	msgbox OneIsland_PokemonCenter_1F_Text_CelioHearingRumorsAboutYou
	random 3
	goto_if_eq VAR_RESULT, 0, OneIsland_PokemonCenter_1F_EventScript_BillFact1
	goto_if_eq VAR_RESULT, 1, OneIsland_PokemonCenter_1F_EventScript_BillFact2
	msgbox OneIsland_PokemonCenter_1F_Text_BillCantStomachMilk
	release
	end

OneIsland_PokemonCenter_1F_EventScript_BillFact1::
	msgbox OneIsland_PokemonCenter_1F_Text_BillsFirstMonWasAbra
	release
	end

OneIsland_PokemonCenter_1F_EventScript_BillFact2::
	msgbox OneIsland_PokemonCenter_1F_Text_BillsHometownInGoldenrod
	release
	end

OneIsland_PokemonCenter_1F_EventScript_LittleBoy::
	msgbox OneIsland_PokemonCenter_1F_Text_CameFromPalletDontKnowIt, MSGBOX_NPC
	end

OneIsland_PokemonCenter_1F_EventScript_Hiker::
	msgbox OneIsland_PokemonCenter_1F_Text_EnormousVolcanoOnIsland, MSGBOX_NPC
	end

OneIsland_PokemonCenter_1F_EventScript_BattleGirl::
	lock
	faceplayer
	goto OneIsland_PokemonCenter_1F_EventScript_BattleGirlHoennLinked

OneIsland_PokemonCenter_1F_EventScript_BattleGirlHoennLinked::
	msgbox OneIsland_PokemonCenter_1F_Text_TradedWithFarAwayBoyfriend
	release
	end

OneIsland_PokemonCenter_1F_EventScript_NetworkMachine::
	lockall
	goto OneIsland_PokemonCenter_1F_EventScript_NetworkMachineLinkedWithHoenn

OneIsland_PokemonCenter_1F_EventScript_NetworkMachineLinkedWithHoenn::
	msgbox OneIsland_PokemonCenter_1F_Text_MachineLinkedWithKantoAndHoenn
	releaseall
	end

OneIsland_PokemonCenter_1F_Text_CelioHearingRumorsAboutYou::
	.string "CELIO: Hello!\p"
	.string "{PLAYER}, I've been hearing rumors\n"
	.string "about you.$"


OneIsland_PokemonCenter_1F_Text_BillsFirstMonWasAbra::
	.string "{PLAYER}, what's your favorite kind\n"
	.string "of POKéMON?\p"
	.string "BILL is a POKéMANIAC, so he loves\n"
	.string "every kind.\p"
	.string "Apparently, the first one he caught\n"
	.string "was an ABRA.$"


OneIsland_PokemonCenter_1F_Text_BillsHometownInGoldenrod::
	.string "By the way, {PLAYER}, you're from\n"
	.string "PALLET TOWN, aren't you?\p"
	.string "I've heard that it's a quiet and\n"
	.string "pleasant place.\p"
	.string "BILL's hometown is GOLDENROD CITY,\n"
	.string "where his folks still live.\p"
	.string "I've heard that it's quite the\n"
	.string "festive, bustling city.\p"
	.string "I'd like to go there one day.$"


OneIsland_PokemonCenter_1F_Text_BillCantStomachMilk::
	.string "{PLAYER}, is there anything that\n"
	.string "you can't stand?\p"
	.string "Apparently, BILL simply can't\n"
	.string "stomach milk at all.$"


OneIsland_PokemonCenter_1F_Text_CameFromPalletDontKnowIt::
	.string "Oh, you're a stranger here!\n"
	.string "Hi! Where did you come from?\p"
	.string "…PALLET TOWN?\n"
	.string "I don't know it!$"


OneIsland_PokemonCenter_1F_Text_EnormousVolcanoOnIsland::
	.string "On this island, there's an enormous\n"
	.string "volcano.\p"
	.string "It hasn't erupted lately, so why\n"
	.string "not enjoy a hike?$"


OneIsland_PokemonCenter_1F_Text_TradedWithFarAwayBoyfriend::
	.string "I traded POKéMON with my boyfriend\n"
	.string "far away!\p"
	.string "Everyone's saying that we can\n"
	.string "thank you and CELIO.\p"
	.string "So, thank you!$"


OneIsland_PokemonCenter_1F_Text_MachineLinkedWithKantoAndHoenn::
	.string "Network Machine\n"
	.string "Link Level 2\p"
	.string "Link established with the KANTO\n"
	.string "and HOENN regions.$"


OneIsland_PokemonCenter_1F_EventScript_NurseEm::
	setvar VAR_0x800B, LOCALID_ONE_ISLAND_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end
