@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

CinnabarIsland_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CinnabarIsland_OnTransition
	.byte 0

CinnabarIsland_OnTransition::
	call CinnabarIsland_EventScript_CheckUnlockGym
	end

CinnabarIsland_EventScript_CheckUnlockGym::
	goto CinnabarIsland_EventScript_UnlockGym

CinnabarIsland_EventScript_UnlockGym::
	setvar VAR_TEMP_1, 1
	return

CinnabarIsland_EventScript_Woman::
	lock
	faceplayer
	msgbox CinnabarIsland_Text_BlaineLivedHereSinceBeforeLab
	release
	end

CinnabarIsland_EventScript_OldMan::
	msgbox CinnabarIsland_Text_ScientistsExperimentInMansion, MSGBOX_NPC
	end

CinnabarIsland_EventScript_IslandSign::
	msgbox CinnabarIsland_Text_IslandSign, MSGBOX_SIGN
	end

CinnabarIsland_EventScript_PokemonLabSign::
	msgbox CinnabarIsland_Text_PokemonLab, MSGBOX_SIGN
	end

CinnabarIsland_EventScript_GymSign::
	lockall
	msgbox CinnabarIsland_Text_GymSign
	releaseall
	end

CinnabarIsland_Text_BlaineLivedHereSinceBeforeLab::
	.string "CINNABAR GYM's BLAINE is quite the\n"
	.string "odd fellow.\p"
	.string "He's lived on the island since way\n"
	.string "before the LAB was built.$"


CinnabarIsland_Text_ScientistsExperimentInMansion::
	.string "Scientists conduct experiments \n"
	.string "in the burned-out building.\p"
	.string "You know, the one they call the\n"
	.string "POKéMON MANSION.$"


CinnabarIsland_Text_IslandSign::
	.string "CINNABAR ISLAND\n"
	.string "The Fiery Town of Burning Desire$"


CinnabarIsland_Text_PokemonLab::
	.string "POKéMON LAB$"


CinnabarIsland_Text_GymSign::
	.string "CINNABAR ISLAND POKéMON GYM\n"
	.string "LEADER: BLAINE\l"
	.string "The Hotheaded Quiz Master!$"
