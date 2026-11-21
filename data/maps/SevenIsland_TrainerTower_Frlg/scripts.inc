@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

SevenIsland_TrainerTower_Frlg_MapScripts::
	.byte 0

SevenIsland_TrainerTower_EventScript_TrainerTowerSign::
	msgbox SevenIsland_TrainerTower_Text_TrainerTowerSign, MSGBOX_SIGN
	end

SevenIsland_TrainerTower_EventScript_TrainerTowerAheadSign::
	msgbox SevenIsland_TrainerTower_Text_TrainerTowerAhead, MSGBOX_SIGN
	end

SevenIsland_TrainerTower_Text_TrainerTowerSign::
	.string "TRAINER TOWER ENTRANCE\n"
	.string "Rise to the Challenge, TRAINERS!$"


SevenIsland_TrainerTower_Text_TrainerTowerAhead::
	.string "TRAINER TOWER AHEAD$"
