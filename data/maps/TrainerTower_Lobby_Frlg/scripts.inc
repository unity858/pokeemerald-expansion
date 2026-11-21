@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

TrainerTower_Lobby_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, TrainerTower_Lobby_OnResume
	map_script MAP_SCRIPT_ON_LOAD, TrainerTower_Lobby_OnLoad
	.byte 0

TrainerTower_Lobby_OnResume::
	setvar VAR_TEMP_2, 0
	goto_if_eq VAR_RESULT, FALSE, TrainerTower_Lobby_OnResumeEnd
	@ Never reached, above always FALSE
	setvar VAR_TEMP_0, 0
	applymovement LOCALID_PLAYER, TrainerTower_Lobby_Movement_FaceReceptionist

TrainerTower_Lobby_OnResumeEnd::
	end

TrainerTower_Lobby_OnLoad::
	call_if_eq VAR_TEMP_D, 17, TrainerTower_Lobby_OpenCounterBarrier
	end

TrainerTower_Lobby_OpenCounterBarrier::
	setmetatile 17, 10, METATILE_TrainerTower_Floor_ShadeBottomLeft, 0
	return

TrainerTower_Lobby_Mart_Items::
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_FULL_RESTORE
	.2byte ITEM_MAX_POTION
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_REVIVE
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_NONE
	release
	end


TrainerTower_Lobby_Movement_FaceReceptionist::
	face_right
	step_end


TrainerTower_Lobby_EventScript_CooltrainerF::
	msgbox TrainerTower_Lobby_Text_WonderWhatKindsOfTrainers, MSGBOX_NPC
	end

TrainerTower_Lobby_EventScript_BaldingMan::
	msgbox TrainerTower_Lobby_Text_StairsTougherThanAnyBattle, MSGBOX_NPC
	end

TrainerTower_Lobby_Text_WonderWhatKindsOfTrainers::
	.string "I'm here to see how good I am.\p"
	.string "I wonder what kinds of TRAINERS\n"
	.string "are waiting for me?\p"
	.string "It's nerve-racking!$"


TrainerTower_Lobby_Text_StairsTougherThanAnyBattle::
	.string "Gasp, gasp…\n"
	.string "Gasp…\p"
	.string "Never mind battling! These stairs…\n"
	.string "They're tougher than any battle…$"



TrainerTower_Lobby_EventScript_NurseEm::
	setvar VAR_0x800B, LOCALID_TOWER_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

TrainerTower_Lobby_EventScript_ClerkEm1::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart TrainerTower_Lobby_Mart_Items
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end
