@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

UndergroundPath_WestEntrance_Frlg_MapScripts::
	.byte 0

UndergroundPath_WestEntrance_EventScript_BaldingMan::
	msgbox UndergroundPath_WestEntrance_Text_SleepyMonNearCeladon, MSGBOX_NPC
	end

UndergroundPath_WestEntrance_Text_SleepyMonNearCeladon::
	.string "I heard a sleepy POKéMON appeared\n"
	.string "out near CELADON CITY, too.$"
