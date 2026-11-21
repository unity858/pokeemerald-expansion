@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

.equ REQUIRED_OWNED_MONS, 20

Route10_PokemonCenter_1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route10_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

Route10_PokemonCenter_1F_OnTransition::
	setrespawn HEAL_LOCATION_ROUTE10
	end

Route10_PokemonCenter_1F_EventScript_FatMan::
	msgbox Route10_PokemonCenter_1F_Text_NuggetUselessSoldFor5000, MSGBOX_NPC
	end

Route10_PokemonCenter_1F_EventScript_Gentleman::
	msgbox Route10_PokemonCenter_1F_Text_EveryTypeStrongerThanOthers, MSGBOX_NPC
	end

Route10_PokemonCenter_1F_EventScript_Youngster::
	msgbox Route10_PokemonCenter_1F_Text_HeardGhostsHauntLavender, MSGBOX_NPC
	end

Route10_PokemonCenter_1F_EventScript_Aide::
	lock
	faceplayer
	call Route10_PokemonCenter_1F_EventScript_GetAideRequestInfo
	goto Route10_PokemonCenter_1F_EventScript_AlreadyGotEverstone

Route10_PokemonCenter_1F_EventScript_AlreadyGotEverstone::
	msgbox Route10_PokemonCenter_1F_Text_ExplainEverstone
	release
	end

Route10_PokemonCenter_1F_EventScript_GetAideRequestInfo::
	buffernumberstring STR_VAR_1, REQUIRED_OWNED_MONS
	bufferitemname STR_VAR_2, ITEM_EVERSTONE
	return

Route10_PokemonCenter_1F_Text_EveryTypeStrongerThanOthers::
	.string "The types of POKéMON match up\n"
	.string "differently with each other.\p"
	.string "Every type is stronger than some\n"
	.string "types and weaker than others.$"


Route10_PokemonCenter_1F_Text_NuggetUselessSoldFor5000::
	.string "A NUGGET is totally useless.\n"
	.string "So I sold it for ¥5000.$"


Route10_PokemonCenter_1F_Text_HeardGhostsHauntLavender::
	.string "I heard that ghosts haunt\n"
	.string "LAVENDER TOWN.$"


Route10_PokemonCenter_1F_Text_ExplainEverstone::
	.string "Making POKéMON evolve certainly\n"
	.string "can add to the POKéDEX.\p"
	.string "However, at times, you may not\n"
	.string "want a certain POKéMON to evolve.\p"
	.string "In that case, give the EVERSTONE\n"
	.string "to that POKéMON.\p"
	.string "It will prevent evolution according\n"
	.string "to the PROFESSOR.$"



Route10_PokemonCenter_1F_EventScript_NurseEm::
	setvar VAR_0x800B, LOCALID_ROUTE10_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end
