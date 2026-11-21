@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

Route4_PokemonCenter_1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route4_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

Route4_PokemonCenter_1F_OnTransition::
	setrespawn HEAL_LOCATION_ROUTE4
	end

Route4_PokemonCenter_1F_EventScript_Boy::
	msgbox Route4_PokemonCenter_1F_Text_CanHaveSixMonsWithYou, MSGBOX_NPC
	end

Route4_PokemonCenter_1F_EventScript_Gentleman::
	lock
	msgbox Route4_PokemonCenter_1F_Text_TeamRocketAttacksCerulean
	release
	end

Route4_PokemonCenter_1F_EventScript_MagikarpSalesman::
	lock
	faceplayer
	goto Route4_PokemonCenter_1F_EventScript_AlreadyBoughtMagikarp

Route4_PokemonCenter_1F_EventScript_AlreadyBoughtMagikarp::
	msgbox Route4_PokemonCenter_1F_Text_IDontGiveRefunds
	release
	end

Route4_PokemonCenter_1F_EventScript_Youngster::
	msgbox Route4_PokemonCenter_1F_Text_ShouldStoreMonsUsingPC, MSGBOX_NPC
	end

Route4_PokemonCenter_1F_EventScript_Newspaper::
	lock
	msgbox Route4_PokemonCenter_1F_Text_ItsANewspaper
	release
	end

Route4_PokemonCenter_1F_Text_CanHaveSixMonsWithYou::
	.string "Okay, set six POKé BALLS in my\n"
	.string "belt…\p"
	.string "Yeah, that'll do it. At most, you\n"
	.string "can have six POKéMON with you.$"


Route4_PokemonCenter_1F_Text_TeamRocketAttacksCerulean::
	.string "TEAM ROCKET attacks CERULEAN\n"
	.string "citizens…\p"
	.string "Not a day goes by without TEAM\n"
	.string "ROCKET being in the news.$"


Route4_PokemonCenter_1F_Text_IDontGiveRefunds::
	.string "MAN: Well, I don't give refunds.\n"
	.string "You knew what you were getting!$"


Route4_PokemonCenter_1F_Text_ShouldStoreMonsUsingPC::
	.string "Sometimes, you'll have too many\n"
	.string "POKéMON with you to add any more.\p"
	.string "In that case, you should just\n"
	.string "store some using any PC.$"


Route4_PokemonCenter_1F_Text_ItsANewspaper::
	.string "It's a newspaper.$"



Route4_PokemonCenter_1F_EventScript_NurseEm::
	setvar VAR_0x800B, LOCALID_ROUTE4_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end
