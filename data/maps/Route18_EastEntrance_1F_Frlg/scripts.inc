@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

Route18_EastEntrance_1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route18_EastEntrance_1F_OnTransition
	.byte 0

Route18_EastEntrance_1F_OnTransition::
	call Route18_EastEntrance_1F_EventScript_DisableNeedBikeTrigger
	end

Route18_EastEntrance_1F_EventScript_DisableNeedBikeTrigger::
	setvar VAR_TEMP_1, 1
	return

Route18_EastEntrance_1F_EventScript_Guard::
	msgbox Route18_EastEntrance_1F_Text_CyclingRoadAllUphillFromHere, MSGBOX_NPC
	end

Route18_EastEntrance_1F_Text_CyclingRoadAllUphillFromHere::
	.string "CYCLING ROAD is all uphill from\n"
	.string "here.$"
