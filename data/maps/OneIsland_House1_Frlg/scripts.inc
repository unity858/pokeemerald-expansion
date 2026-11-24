@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

OneIsland_House1_Frlg_MapScripts::
	.byte 0

OneIsland_House1_EventScript_OldMan::
	msgbox OneIsland_House1_Text_GazeUponVolcanoOnSunnyDays, MSGBOX_NPC
	end

OneIsland_House1_EventScript_OldWoman::
	msgbox OneIsland_House1_Text_LastTimeMtEmberErupted, MSGBOX_NPC
	end

OneIsland_House1_Text_GazeUponVolcanoOnSunnyDays::
	.string "On sunny days, I step out and gaze\n"
	.string "upon the volcano.\p"
	.string "That's my daily routine.$"


OneIsland_House1_Text_LastTimeMtEmberErupted::
	.string "Let me think… When was the last\n"
	.string "time MT. EMBER erupted?$"
