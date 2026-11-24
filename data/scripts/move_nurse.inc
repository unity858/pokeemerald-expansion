@ Move Nurse: the second nurse, left of the healing machine in every Pokemon
@ Center 1F (Hoenn, Kanto and Sevii). Uses the built-in move relearner UI.
@   Recall a move - level-up moves up to the mon's level, free
@   Egg moves     - Egg moves of the earliest pre-evolution, MOVE_NURSE_EGG_MOVE_PRICE
@                   (include/constants/move_relearner.h) per move actually learned
@   Tutor moves   - Tutor moves unlocked by Hoenn badge count, free
@                   (table: src/data/tutor_move_badges.h)
@ The relearner runs in script mode (chooseboxmon), so each visit to the move
@ list teaches at most one move and SELECT can't switch to another move type.

Common_EventScript_MoveNurse::
	lock
	faceplayer
	message MoveNurse_Text_Welcome
	waitmessage
	goto MoveNurse_EventScript_ChooseService
	end

MoveNurse_EventScript_ChooseService::
	dynmultipush MoveNurse_Text_RecallAMove, 0
	dynmultipush MoveNurse_Text_EggMoves, 1
	dynmultipush MoveNurse_Text_TutorMoves, 2
	dynmultipush MoveNurse_Text_NoThanks, 3
	dynmultistack 0, 0, FALSE, 4, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	closemessage
	switch VAR_RESULT
	case 0, MoveNurse_EventScript_Recall
	case 1, MoveNurse_EventScript_EggMoves
	case 2, MoveNurse_EventScript_TutorMoves
	goto MoveNurse_EventScript_Goodbye
	end

MoveNurse_EventScript_AnythingElse::
	message MoveNurse_Text_AnythingElse
	waitmessage
	goto MoveNurse_EventScript_ChooseService
	end

MoveNurse_EventScript_Goodbye::
	msgbox MoveNurse_Text_Goodbye, MSGBOX_DEFAULT
	release
	end

@ ---------------------------------------------------------------------------
@ Recall a move (level-up moves, free)
@ ---------------------------------------------------------------------------
MoveNurse_EventScript_Recall::
	setmoverelearnerstate MOVE_RELEARNER_LEVEL_UP_MOVES
	msgbox MoveNurse_Text_WhichMonRecall, MSGBOX_DEFAULT
	call MoveNurse_EventScript_ChooseMon
	goto_if_ne VAR_RESULT, TRUE, MoveNurse_EventScript_AnythingElse
	msgbox MoveNurse_Text_WhichMoveRecall, MSGBOX_DEFAULT
	special TeachMoveRelearnerMove
	goto MoveNurse_EventScript_AnythingElse
	end

@ ---------------------------------------------------------------------------
@ Egg moves (MOVE_NURSE_EGG_MOVE_PRICE per move learned)
@ ---------------------------------------------------------------------------
MoveNurse_EventScript_EggMoves::
	special MoveNurse_BufferEggMovePrice
	showmoneybox 0, 0
	msgbox MoveNurse_Text_EggMovePrice, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MoveNurse_EventScript_EggMovesDeclined
	checkmoney MOVE_NURSE_EGG_MOVE_PRICE
	goto_if_eq VAR_RESULT, FALSE, MoveNurse_EventScript_EggMovesCantAfford
	hidemoneybox
	setmoverelearnerstate MOVE_RELEARNER_EGG_MOVES
	msgbox MoveNurse_Text_WhichMonEgg, MSGBOX_DEFAULT
	call MoveNurse_EventScript_ChooseMon
	goto_if_ne VAR_RESULT, TRUE, MoveNurse_EventScript_AnythingElse
	msgbox MoveNurse_Text_WhichMoveEgg, MSGBOX_DEFAULT
	special TeachMoveRelearnerMove
	goto_if_ne VAR_RESULT, TRUE, MoveNurse_EventScript_AnythingElse
	removemoney MOVE_NURSE_EGG_MOVE_PRICE
	special MoveNurse_BufferEggMovePrice
	showmoneybox 0, 0
	playse SE_SHOP
	msgbox MoveNurse_Text_PaidForEggMove, MSGBOX_DEFAULT
	hidemoneybox
	goto MoveNurse_EventScript_AnythingElse
	end

MoveNurse_EventScript_EggMovesDeclined::
	hidemoneybox
	goto MoveNurse_EventScript_AnythingElse
	end

MoveNurse_EventScript_EggMovesCantAfford::
	msgbox MoveNurse_Text_CantAffordEggMove, MSGBOX_DEFAULT
	hidemoneybox
	goto MoveNurse_EventScript_AnythingElse
	end

@ ---------------------------------------------------------------------------
@ Tutor moves (free, unlocked by Hoenn badge count)
@ ---------------------------------------------------------------------------
MoveNurse_EventScript_TutorMoves::
	special MoveNurse_GetTutorAvailability
	goto_if_eq VAR_RESULT, MOVE_NURSE_TUTOR_NO_BADGES, MoveNurse_EventScript_TutorNoBadges
	goto_if_eq VAR_RESULT, MOVE_NURSE_TUTOR_NEED_MORE, MoveNurse_EventScript_TutorNeedMoreBadges
	setmoverelearnerstate MOVE_RELEARNER_BADGE_TUTOR_MOVES
	msgbox MoveNurse_Text_WhichMonTutor, MSGBOX_DEFAULT
	call MoveNurse_EventScript_ChooseMon
	goto_if_ne VAR_RESULT, TRUE, MoveNurse_EventScript_AnythingElse
	msgbox MoveNurse_Text_WhichMoveTutor, MSGBOX_DEFAULT
	special TeachMoveRelearnerMove
	goto MoveNurse_EventScript_AnythingElse
	end

MoveNurse_EventScript_TutorNoBadges::
	msgbox MoveNurse_Text_TutorNoBadges, MSGBOX_DEFAULT
	goto MoveNurse_EventScript_AnythingElse
	end

MoveNurse_EventScript_TutorNeedMoreBadges::
	msgbox MoveNurse_Text_TutorNeedMoreBadges, MSGBOX_DEFAULT
	goto MoveNurse_EventScript_AnythingElse
	end

@ ---------------------------------------------------------------------------
@ Pick a Pokemon for the current relearner state.
@ Returns VAR_RESULT TRUE when the chosen mon has a move to learn.
@ ---------------------------------------------------------------------------
MoveNurse_EventScript_ChooseMon::
	chooseboxmon SELECT_PC_MON_MOVE_RELEARNER
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, MoveNurse_EventScript_ChoseNothing
	special IsSelectedMonEgg
	goto_if_eq VAR_RESULT, TRUE, MoveNurse_EventScript_ChoseEgg
	special Special_HasMoveToRelearn
	goto_if_eq VAR_RESULT, FALSE, MoveNurse_EventScript_NoMoveForMon
	setvar VAR_RESULT, TRUE
	return

MoveNurse_EventScript_ChoseNothing::
	setvar VAR_RESULT, FALSE
	return

MoveNurse_EventScript_ChoseEgg::
	msgbox MoveNurse_Text_CantTeachEgg, MSGBOX_DEFAULT
	setvar VAR_RESULT, FALSE
	return

MoveNurse_EventScript_NoMoveForMon::
	msgbox MoveNurse_Text_NoMoveForMon, MSGBOX_DEFAULT
	setvar VAR_RESULT, FALSE
	return
