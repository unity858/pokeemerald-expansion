@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

SaffronCity_Gym_Frlg_MapScripts::
	.byte 0

SaffronCity_Gym_EventScript_GymGuy::
	lock
	faceplayer
	goto SaffronCity_Gym_EventScript_GymGuyPostVictory

SaffronCity_Gym_EventScript_GymGuyPostVictory::
	msgbox SaffronCity_Gym_Text_GymGuyPostVictory
	release
	end

SaffronCity_Gym_EventScript_GymStatue::
	lockall
	goto SaffronCity_Gym_EventScript_GymStatuePostVictory

SaffronCity_Gym_EventScript_GymStatuePostVictory::
	msgbox SaffronCity_Gym_Text_GymStatuePlayerWon
	releaseall
	end

SaffronCity_Gym_Text_GymGuyPostVictory::
	.string "Psychic power, huh?\p"
	.string "If I had that, I'd make a bundle\n"
	.string "at the slots!$"


SaffronCity_Gym_Text_GymStatuePlayerWon::
	.string "SAFFRON POKéMON GYM\n"
	.string "LEADER: SABRINA\p"
	.string "WINNING TRAINERS:\n"
	.string "{RIVAL}, {PLAYER}$"
