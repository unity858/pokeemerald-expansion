@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

SaffronCity_PokemonCenter_1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SaffronCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

SaffronCity_PokemonCenter_1F_OnTransition::
	setrespawn HEAL_LOCATION_SAFFRON_CITY
	end

SaffronCity_PokemonCenter_1F_EventScript_Gentleman::
	msgbox SaffronCity_PokemonCenter_1F_Text_SilphCoVictimOfFame, MSGBOX_NPC
	end

SaffronCity_PokemonCenter_1F_EventScript_Woman::
	msgbox SaffronCity_PokemonCenter_1F_Text_GrowthRatesDifferBySpecies, MSGBOX_NPC
	end

SaffronCity_PokemonCenter_1F_EventScript_Youngster::
	lock
	faceplayer
	goto SaffronCity_PokemonCenter_1F_EventScript_YoungsterRocketsGone

SaffronCity_PokemonCenter_1F_EventScript_YoungsterRocketsGone::
	msgbox SaffronCity_PokemonCenter_1F_Text_TeamRocketTookOff
	release
	end

SaffronCity_PokemonCenter_1F_Text_GrowthRatesDifferBySpecies::
	.string "POKéMON growth rates differ from\n"
	.string "species to species.$"


SaffronCity_PokemonCenter_1F_Text_SilphCoVictimOfFame::
	.string "SILPH CO. is widely known to all.\p"
	.string "It's a victim of its own fame - it\n"
	.string "attracted TEAM ROCKET.$"


SaffronCity_PokemonCenter_1F_Text_TeamRocketTookOff::
	.string "TEAM ROCKET took off!\n"
	.string "We can go out safely again!\l"
	.string "That's great!$"



SaffronCity_PokemonCenter_1F_EventScript_NurseEm::
	setvar VAR_0x800B, LOCALID_SAFFRON_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end
