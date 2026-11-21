@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

CeruleanCity_Gym_Frlg_MapScripts::
	.byte 0

CeruleanCity_Gym_EventScript_GymGuy::
	lock
	faceplayer
	goto CeruleanCity_Gym_EventScript_GymGuyPostVictory

CeruleanCity_Gym_EventScript_GymGuyPostVictory::
	msgbox CeruleanCity_Gym_Text_WeMakePrettyGoodTeam
	release
	end

CeruleanCity_Gym_EventScript_GymStatue::
	lockall
	goto CeruleanCity_Gym_EventScript_GymStatuePostVictory

CeruleanCity_Gym_EventScript_GymStatuePostVictory::
	msgbox CeruleanCity_Gym_Text_GymStatuePlayerWon
	releaseall
	end

CeruleanCity_Gym_Text_WeMakePrettyGoodTeam::
	.string "You beat MISTY!\n"
	.string "See, what'd I tell ya?\p"
	.string "You and me, kid, we make a pretty\n"
	.string "darn-good team!$"


CeruleanCity_Gym_Text_GymStatuePlayerWon::
	.string "CERULEAN POKéMON GYM\n"
	.string "LEADER: MISTY\p"
	.string "WINNING TRAINERS:\n"
	.string "{RIVAL}, {PLAYER}$"
