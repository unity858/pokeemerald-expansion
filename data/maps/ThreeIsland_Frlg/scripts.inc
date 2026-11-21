@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

ThreeIsland_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ThreeIsland_OnTransition
	.byte 0

ThreeIsland_OnTransition::
	call ThreeIsland_EventScript_HideAntiBikers
	call ThreeIsland_EventScript_SetAntiBikersMovementAfterBikers
	end

ThreeIsland_EventScript_HideAntiBikers::
	return

ThreeIsland_EventScript_SetAntiBikersMovementAfterBikers::
	setobjectmovementtype LOCALID_THREE_ISLAND_ANTIBIKER1, MOVEMENT_TYPE_LOOK_AROUND
	setobjectmovementtype LOCALID_THREE_ISLAND_ANTIBIKER2, MOVEMENT_TYPE_LOOK_AROUND
	return

ThreeIsland_EventScript_AntiBiker1::
	lock
	goto ThreeIsland_EventScript_AntiBiker1GotFullRestore

ThreeIsland_EventScript_AntiBiker1GotFullRestore::
	applymovement LOCALID_THREE_ISLAND_ANTIBIKER1, Common_Movement_FacePlayer
	waitmovement 0
	msgbox ThreeIsland_Text_YouveGotImpressiveMons
	release
	end

ThreeIsland_EventScript_AntiBiker2::
	lock
	goto ThreeIsland_EventScript_AntiBiker2BikersGone

ThreeIsland_EventScript_AntiBiker2BikersGone::
	applymovement LOCALID_THREE_ISLAND_ANTIBIKER2, Common_Movement_FacePlayer
	waitmovement 0
	msgbox ThreeIsland_Text_LostelleWentOffTowardsBondBridge
	release
	end

ThreeIsland_EventScript_Woman::
	msgbox ThreeIsland_Text_WouldntWantToSeeBikersHereAgain, MSGBOX_NPC
	end

ThreeIsland_EventScript_LittleBoy::
	msgbox ThreeIsland_Text_WhenDodouEvolvesGoingToPlayGame, MSGBOX_NPC
	end

ThreeIsland_EventScript_Doduo::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_DODUO, CRY_MODE_NORMAL
	msgbox ThreeIsland_Text_Doduo
	waitmoncry
	release
	end

ThreeIsland_EventScript_IslandSign::
	msgbox ThreeIsland_Text_IslandSign, MSGBOX_SIGN
	end

ThreeIsland_Text_IslandSign::
	.string "THREE ISLAND\n"
	.string "Kin Island of Family Bonding$"


ThreeIsland_Text_YouveGotImpressiveMons::
	.string "You've got seriously impressive\n"
	.string "POKéMON with you.$"


ThreeIsland_Text_LostelleWentOffTowardsBondBridge::
	.string "It'd be fantastic if someone as\n"
	.string "strong as you lived here.\p"
	.string "I hope you'll at least stay here\n"
	.string "a while.\p"
	.string "…I beg your pardon?\n"
	.string "You're looking for LOSTELLE?\p"
	.string "LOSTELLE went off towards BOND\n"
	.string "BRIDGE a while ago.$"


ThreeIsland_Text_WouldntWantToSeeBikersHereAgain::
	.string "THREE ISLAND is actually the most\n"
	.string "populous of the islands here.\p"
	.string "Still, it could be less sleepy.\p"
	.string "But I wouldn't want to see goons\n"
	.string "like those BIKERS here again.$"


ThreeIsland_Text_WhenDodouEvolvesGoingToPlayGame::
	.string "I'm going to train my DODUO in the\n"
	.string "BERRY FOREST.\p"
	.string "When it evolves, I'm going to play\n"
	.string "a game on TWO ISLAND.$"


ThreeIsland_Text_Doduo::
	.string "DODUO: Gigiih!$"
