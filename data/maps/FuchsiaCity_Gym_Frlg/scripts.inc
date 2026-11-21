@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

FuchsiaCity_Gym_Frlg_MapScripts::
	.byte 0

FuchsiaCity_Gym_EventScript_GymGuy::
	lock
	faceplayer
	goto FuchsiaCity_Gym_EventScript_GymGuyPostVictory

FuchsiaCity_Gym_EventScript_GymGuyPostVictory::
	msgbox FuchsiaCity_Gym_Text_GymGuyPostVictory
	release
	end

FuchsiaCity_Gym_EventScript_GymStatue::
	lockall
	goto FuchsiaCity_Gym_EventScript_GymStatuePostVictory

FuchsiaCity_Gym_EventScript_GymStatuePostVictory::
	msgbox FuchsiaCity_Gym_Text_GymStatuePlayerWon
	releaseall
	end

FuchsiaCity_Gym_Text_GymGuyPostVictory::
	.string "It's amazing how ninja can terrify,\n"
	.string "even now!$"


FuchsiaCity_Gym_Text_GymStatuePlayerWon::
	.string "FUCHSIA POKéMON GYM\n"
	.string "LEADER: KOGA\p"
	.string "WINNING TRAINERS:\n"
	.string "{RIVAL}, {PLAYER}$"
