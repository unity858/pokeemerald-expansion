@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

PewterCity_Gym_Frlg_MapScripts::
	.byte 0

PewterCity_Gym_EventScript_GymGuy::
	lock
	faceplayer
	goto PewterCity_Gym_EventScript_GymGuyPostVictory

PewterCity_Gym_EventScript_GymGuyPostVictory::
	msgbox PewterCity_Gym_Text_YoureChampMaterial
	release
	end

PewterCity_Gym_EventScript_GymStatue::
	lockall
	goto PewterCity_Gym_EventScript_GymStatuePostVictory

PewterCity_Gym_EventScript_GymStatuePostVictory::
	msgbox PewterCity_Gym_Text_GymStatuePlayerWon
	releaseall
	end

PewterCity_Gym_Text_YoureChampMaterial::
	.string "Just as I thought!\n"
	.string "You're POKéMON champ material!$"


PewterCity_Gym_Text_GymStatuePlayerWon::
	.string "PEWTER POKéMON GYM\n"
	.string "LEADER: BROCK\p"
	.string "WINNING TRAINERS:\n"
	.string "{RIVAL}, {PLAYER}$"
