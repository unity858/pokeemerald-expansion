@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

Route16_NorthEntrance_1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route16_NorthEntrance_1F_OnTransition
	.byte 0

Route16_NorthEntrance_1F_OnTransition::
	call Route16_NorthEntrance_1F_EventScript_DisableNeedBikeTrigger
	end

Route16_NorthEntrance_1F_EventScript_DisableNeedBikeTrigger::
	setvar VAR_TEMP_1, 1
	return

Route16_NorthEntrance_1F_EventScript_Guard::
	msgbox Route16_NorthEntrance_1F_Text_CyclingRoadIsDownhillCourse, MSGBOX_NPC
	end

Route16_NorthEntrance_1F_EventScript_OldMan::
	msgbox Route16_NorthEntrance_1F_Text_HowdYouGetInGoodEffort, MSGBOX_NPC
	end

Route16_NorthEntrance_1F_Text_CyclingRoadIsDownhillCourse::
	.string "CYCLING ROAD is a downhill course\n"
	.string "by the sea. It's a great ride.$"


Route16_NorthEntrance_1F_Text_HowdYouGetInGoodEffort::
	.string "How'd you get in?\n"
	.string "Good effort!$"
