@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

CinnabarIsland_Gym_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, CinnabarIsland_Gym_OnLoad
	.byte 0

CinnabarIsland_Gym_OnLoad::
	goto CinnabarIsland_Gym_OnLoadOpenAllDoors

CinnabarIsland_Gym_OnLoadOpenAllDoors::
	call CinnabarIsland_Gym_EventScript_OpenDoor1
	call CinnabarIsland_Gym_EventScript_OpenDoor2
	call CinnabarIsland_Gym_EventScript_OpenDoor3
	call CinnabarIsland_Gym_EventScript_OpenDoor4
	call CinnabarIsland_Gym_EventScript_OpenDoor5
	call CinnabarIsland_Gym_EventScript_OpenDoor6
	end

CinnabarIsland_Gym_EventScript_GymGuy::
	lock
	faceplayer
	goto CinnabarIsland_Gym_EventScript_GymGuyPostVictory

CinnabarIsland_Gym_EventScript_GymGuyPostVictory::
	msgbox CinnabarIsland_Gym_Text_GymGuyPostVictory
	release
	end

CinnabarIsland_Gym_EventScript_GymStatue::
	lockall
	goto CinnabarIsland_Gym_EventScript_GymStatuePostVictory

CinnabarIsland_Gym_EventScript_GymStatuePostVictory::
	msgbox CinnabarIsland_Gym_Text_GymStatuePlayerWon
	releaseall
	end

CinnabarIsland_Gym_EventScript_Quz1Left::
	lockall
	setvar VAR_TEMP_1, 0
	goto CinnabarIsland_Gym_EventScript_Quiz1

CinnabarIsland_Gym_EventScript_Quz1Right::
	lockall
	setvar VAR_TEMP_1, 1
	goto CinnabarIsland_Gym_EventScript_Quiz1

CinnabarIsland_Gym_EventScript_Quiz1::
	msgbox CinnabarIsland_Gym_Text_PokemonQuizRules
	msgbox CinnabarIsland_Gym_Text_QuizQuestion1, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, CinnabarIsland_Gym_EventScript_Quiz1Correct
	goto_if_eq VAR_RESULT, NO, CinnabarIsland_Gym_EventScript_Quiz1Incorrect
	end

CinnabarIsland_Gym_EventScript_CorrectAnswer::
	playfanfare MUS_LEVEL_UP
	waitfanfare
	msgbox CinnabarIsland_Gym_Text_CorrectGoOnThrough
	return

CinnabarIsland_Gym_EventScript_IncorrectAnswer::
	waitse
	playse SE_BOO
	waitse
	msgbox CinnabarIsland_Gym_Text_SorryBadCall
	closemessage
	return

CinnabarIsland_Gym_EventScript_Quiz1Correct::
	call CinnabarIsland_Gym_EventScript_CorrectAnswer
	goto CinnabarIsland_Gym_EventScript_DoorAlreadyOpen

CinnabarIsland_Gym_EventScript_DoorAlreadyOpen::
	releaseall
	end

CinnabarIsland_Gym_EventScript_Quiz1Incorrect::
	call CinnabarIsland_Gym_EventScript_IncorrectAnswer
	releaseall
	end

CinnabarIsland_Gym_EventScript_Quiz2Left::
	lockall
	setvar VAR_TEMP_1, 0
	goto CinnabarIsland_Gym_EventScript_Quiz2

CinnabarIsland_Gym_EventScript_Quiz2Right::
	lockall
	setvar VAR_TEMP_1, 1
	goto CinnabarIsland_Gym_EventScript_Quiz2

CinnabarIsland_Gym_EventScript_Quiz2::
	msgbox CinnabarIsland_Gym_Text_PokemonQuizRules
	msgbox CinnabarIsland_Gym_Text_QuizQuestion2, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, CinnabarIsland_Gym_EventScript_Quiz2Incorrect
	goto_if_eq VAR_RESULT, NO, CinnabarIsland_Gym_EventScript_Quiz2Correct
	end

CinnabarIsland_Gym_EventScript_Quiz2Correct::
	call CinnabarIsland_Gym_EventScript_CorrectAnswer
	goto CinnabarIsland_Gym_EventScript_DoorAlreadyOpen

CinnabarIsland_Gym_EventScript_Quiz2Incorrect::
	call CinnabarIsland_Gym_EventScript_IncorrectAnswer
	releaseall
	end

CinnabarIsland_Gym_EventScript_Quiz3Left::
	lockall
	setvar VAR_TEMP_1, 0
	goto CinnabarIsland_Gym_EventScript_Quiz3

CinnabarIsland_Gym_EventScript_Quiz3Right::
	lockall
	setvar VAR_TEMP_1, 1
	goto CinnabarIsland_Gym_EventScript_Quiz3

CinnabarIsland_Gym_EventScript_Quiz3::
	msgbox CinnabarIsland_Gym_Text_PokemonQuizRules
	msgbox CinnabarIsland_Gym_Text_QuizQuestion3, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, CinnabarIsland_Gym_EventScript_Quiz3Incorrect
	goto_if_eq VAR_RESULT, NO, CinnabarIsland_Gym_EventScript_Quiz3Correct
	end

CinnabarIsland_Gym_EventScript_Quiz3Correct::
	call CinnabarIsland_Gym_EventScript_CorrectAnswer
	goto CinnabarIsland_Gym_EventScript_DoorAlreadyOpen

CinnabarIsland_Gym_EventScript_Quiz3Incorrect::
	call CinnabarIsland_Gym_EventScript_IncorrectAnswer
	releaseall
	end

CinnabarIsland_Gym_EventScript_Quiz4Left::
	lockall
	setvar VAR_TEMP_1, 0
	goto CinnabarIsland_Gym_EventScript_Quiz4

CinnabarIsland_Gym_EventScript_Quiz4Right::
	lockall
	setvar VAR_TEMP_1, 1
	goto CinnabarIsland_Gym_EventScript_Quiz4

CinnabarIsland_Gym_EventScript_Quiz4::
	msgbox CinnabarIsland_Gym_Text_PokemonQuizRules
	msgbox CinnabarIsland_Gym_Text_QuizQuestion4, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, CinnabarIsland_Gym_EventScript_Quiz4Incorrect
	goto_if_eq VAR_RESULT, NO, CinnabarIsland_Gym_EventScript_Quiz4Correct
	end

CinnabarIsland_Gym_EventScript_Quiz4Correct::
	call CinnabarIsland_Gym_EventScript_CorrectAnswer
	goto CinnabarIsland_Gym_EventScript_DoorAlreadyOpen

CinnabarIsland_Gym_EventScript_Quiz4Incorrect::
	call CinnabarIsland_Gym_EventScript_IncorrectAnswer
	releaseall
	end

CinnabarIsland_Gym_EventScript_Quiz5Left::
	lockall
	setvar VAR_TEMP_1, 0
	goto CinnabarIsland_Gym_EventScript_Quiz5

CinnabarIsland_Gym_EventScript_Quiz5Right::
	lockall
	setvar VAR_TEMP_1, 1
	goto CinnabarIsland_Gym_EventScript_Quiz5

CinnabarIsland_Gym_EventScript_Quiz5::
	msgbox CinnabarIsland_Gym_Text_PokemonQuizRules
	msgbox CinnabarIsland_Gym_Text_QuizQuestion5, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, CinnabarIsland_Gym_EventScript_Quiz5Correct
	goto_if_eq VAR_RESULT, NO, CinnabarIsland_Gym_EventScript_Quiz5Incorrect
	end

CinnabarIsland_Gym_EventScript_Quiz5Correct::
	call CinnabarIsland_Gym_EventScript_CorrectAnswer
	goto CinnabarIsland_Gym_EventScript_DoorAlreadyOpen

CinnabarIsland_Gym_EventScript_Quiz5Incorrect::
	call CinnabarIsland_Gym_EventScript_IncorrectAnswer
	releaseall
	end

CinnabarIsland_Gym_EventScript_Quiz6Left::
	lockall
	setvar VAR_TEMP_1, 0
	goto CinnabarIsland_Gym_EventScript_Quiz6

CinnabarIsland_Gym_EventScript_Quiz6Right::
	lockall
	setvar VAR_TEMP_1, 1
	goto CinnabarIsland_Gym_EventScript_Quiz6

CinnabarIsland_Gym_EventScript_Quiz6::
	msgbox CinnabarIsland_Gym_Text_PokemonQuizRules
	msgbox CinnabarIsland_Gym_Text_QuizQuestion6, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, CinnabarIsland_Gym_EventScript_Quiz6Incorrect
	goto_if_eq VAR_RESULT, NO, CinnabarIsland_Gym_EventScript_Quiz6Correct
	end

CinnabarIsland_Gym_EventScript_Quiz6Correct::
	call CinnabarIsland_Gym_EventScript_CorrectAnswer
	goto CinnabarIsland_Gym_EventScript_DoorAlreadyOpen

CinnabarIsland_Gym_EventScript_Quiz6Incorrect::
	call CinnabarIsland_Gym_EventScript_IncorrectAnswer
	releaseall
	end

CinnabarIsland_Gym_EventScript_OpenDoor1::
	setmetatile 26,  8, METATILE_CinnabarGym_Floor_WallLeftCorner, 0
	setmetatile 27,  8, METATILE_CinnabarGym_Floor_WallRightCorner, 0
	setmetatile 26,  9, METATILE_CinnabarGym_Floor_WallLeftEdge, 0
	setmetatile 27,  9, METATILE_CinnabarGym_Floor_WallRightEdge, 0
	setmetatile 26, 10, METATILE_CinnabarGym_Floor_ShadeFull, 0
	setmetatile 27, 10, METATILE_CinnabarGym_Floor, 0
	setmetatile 28, 10, METATILE_CinnabarGym_Floor_ShadeDiagonal, 0
	return

CinnabarIsland_Gym_EventScript_OpenDoor2::
	setmetatile 17,  8, METATILE_CinnabarGym_Floor_WallLeftCorner, 0
	setmetatile 18,  8, METATILE_CinnabarGym_Floor_WallRightCorner, 0
	setmetatile 17,  9, METATILE_CinnabarGym_Floor_WallLeftEdge, 0
	setmetatile 18,  9, METATILE_CinnabarGym_Floor_WallRightEdge, 0
	setmetatile 17, 10, METATILE_CinnabarGym_Floor_ShadeFull, 0
	setmetatile 18, 10, METATILE_CinnabarGym_Floor, 0
	setmetatile 19, 10, METATILE_CinnabarGym_Floor_ShadeDiagonal, 0
	return

CinnabarIsland_Gym_EventScript_OpenDoor3::
	setmetatile 17, 15, METATILE_CinnabarGym_Floor_WallLeftCorner, 0
	setmetatile 18, 15, METATILE_CinnabarGym_Floor_WallRightCorner, 0
	setmetatile 17, 16, METATILE_CinnabarGym_Floor_WallLeftEdge, 0
	setmetatile 18, 16, METATILE_CinnabarGym_Floor_WallRightEdge, 0
	setmetatile 17, 17, METATILE_CinnabarGym_Floor_ShadeFull, 0
	setmetatile 18, 17, METATILE_CinnabarGym_Floor, 0
	setmetatile 19, 17, METATILE_CinnabarGym_Floor_ShadeDiagonal, 0
	return

CinnabarIsland_Gym_EventScript_OpenDoor4::
	setmetatile 11, 21, METATILE_CinnabarGym_Wall_RetractedBarrier, 1
	setmetatile 11, 22, METATILE_CinnabarGym_Floor_ShadeFull, 0
	setmetatile 11, 23, METATILE_CinnabarGym_Floor, 0
	return

CinnabarIsland_Gym_EventScript_OpenDoor5::
	setmetatile  5, 16, METATILE_CinnabarGym_Floor_WallLeftCorner, 0
	setmetatile  6, 16, METATILE_CinnabarGym_Floor_WallRightCorner, 0
	setmetatile  5, 17, METATILE_CinnabarGym_Floor_WallLeftEdge, 0
	setmetatile  6, 17, METATILE_CinnabarGym_Floor_WallRightEdge, 0
	setmetatile  5, 18, METATILE_CinnabarGym_Floor_ShadeFull, 0
	setmetatile  6, 18, METATILE_CinnabarGym_Floor, 0
	setmetatile  7, 18, METATILE_CinnabarGym_Floor_ShadeDiagonal, 0
	return

CinnabarIsland_Gym_EventScript_OpenDoor6::
	setmetatile  5,  8, METATILE_CinnabarGym_Floor_WallLeftCorner, 0
	setmetatile  6,  8, METATILE_CinnabarGym_Floor_WallRightCorner, 0
	setmetatile  5,  9, METATILE_CinnabarGym_Floor_WallLeftEdge, 0
	setmetatile  6,  9, METATILE_CinnabarGym_Floor_WallRightEdge, 0
	setmetatile  5, 10, METATILE_CinnabarGym_Floor_ShadeFull, 0
	setmetatile  6, 10, METATILE_CinnabarGym_Floor, 0
	setmetatile  7, 10, METATILE_CinnabarGym_Floor_ShadeDiagonal, 0
	return

CinnabarIsland_Gym_Text_GymGuyPostVictory::
	.string "{PLAYER}!\n"
	.string "You beat that firebrand!$"


CinnabarIsland_Gym_Text_GymStatuePlayerWon::
	.string "CINNABAR POKéMON GYM\n"
	.string "LEADER: BLAINE\p"
	.string "WINNING TRAINERS:\n"
	.string "{RIVAL}, {PLAYER}$"


CinnabarIsland_Gym_Text_PokemonQuizRules::
	.string "POKéMON Quiz!\p"
	.string "Get it right, and the door opens to\n"
	.string "the next room.\p"
	.string "Get it wrong, and face a TRAINER!\p"
	.string "If you want to conserve your\n"
	.string "POKéMON for the GYM LEADER…\p"
	.string "Then get it right!\n"
	.string "Here we go!$"


CinnabarIsland_Gym_Text_QuizQuestion1::
	.string "CATERPIE evolves into METAPOD?$"


CinnabarIsland_Gym_Text_QuizQuestion2::
	.string "There are nine certified POKéMON\n"
	.string "LEAGUE BADGES?$"


CinnabarIsland_Gym_Text_QuizQuestion3::
	.string "POLIWAG evolves three times?$"


CinnabarIsland_Gym_Text_QuizQuestion4::
	.string "Are electric moves effective\n"
	.string "against GROUND-type POKéMON?$"


CinnabarIsland_Gym_Text_QuizQuestion5::
	.string "POKéMON of the same kind and level\n"
	.string "are not identical?$"


CinnabarIsland_Gym_Text_QuizQuestion6::
	.string "TM28 contains TOMBSTONY?$"


CinnabarIsland_Gym_Text_CorrectGoOnThrough::
	.string "You're absolutely correct!\p"
	.string "Go on through!$"


CinnabarIsland_Gym_Text_SorryBadCall::
	.string "Sorry!\n"
	.string "Bad call!$"

@ ---- Kanto trainers: generated by dev_scripts/kanto/add_kanto_trainers.py ----

CinnabarIsland_Gym_EventScript_KT_Quinn::
	trainerbattle_single TRAINER_KANTO_BURGLAR_QUINN, CinnabarIsland_Gym_Text_QuinnIntro, CinnabarIsland_Gym_Text_QuinnDefeat
	msgbox CinnabarIsland_Gym_Text_QuinnPostBattle, MSGBOX_AUTOCLOSE
	end

CinnabarIsland_Gym_Text_QuinnIntro::
	.string "I was a thief, but I went straight\n"
	.string "as a TRAINER.$"

CinnabarIsland_Gym_Text_QuinnDefeat::
	.string "I surrender!$"

CinnabarIsland_Gym_Text_QuinnPostBattle::
	.string "I get this uncontrollable urge to\n"
	.string "steal other people's POKéMON.$"

CinnabarIsland_Gym_EventScript_KT_Erik::
	trainerbattle_single TRAINER_KANTO_SUPER_NERD_ERIK, CinnabarIsland_Gym_Text_ErikIntro, CinnabarIsland_Gym_Text_ErikDefeat
	msgbox CinnabarIsland_Gym_Text_ErikPostBattle, MSGBOX_AUTOCLOSE
	end

CinnabarIsland_Gym_Text_ErikIntro::
	.string "Do you know how hot POKéMON fire\n"
	.string "breath can get?$"

CinnabarIsland_Gym_Text_ErikDefeat::
	.string "Yow!\n"
	.string "Hot, hot, hot!$"

CinnabarIsland_Gym_Text_ErikPostBattle::
	.string "Fire, or to be more precise,\n"
	.string "combustion…\p"
	.string "…Oxygen in the air…\n"
	.string "Blah, blah, blah, blah…$"

CinnabarIsland_Gym_EventScript_KT_Avery::
	trainerbattle_single TRAINER_KANTO_SUPER_NERD_AVERY, CinnabarIsland_Gym_Text_AveryIntro, CinnabarIsland_Gym_Text_AveryDefeat
	msgbox CinnabarIsland_Gym_Text_AveryPostBattle, MSGBOX_AUTOCLOSE
	end

CinnabarIsland_Gym_Text_AveryIntro::
	.string "I've studied POKéMON thoroughly.\n"
	.string "You can't win!$"

CinnabarIsland_Gym_Text_AveryDefeat::
	.string "Waah!\n"
	.string "My studies were insufficient!$"

CinnabarIsland_Gym_Text_AveryPostBattle::
	.string "My theories are too complicated\n"
	.string "for you to understand.$"

CinnabarIsland_Gym_EventScript_KT_Ramon::
	trainerbattle_single TRAINER_KANTO_BURGLAR_RAMON, CinnabarIsland_Gym_Text_RamonIntro, CinnabarIsland_Gym_Text_RamonDefeat
	msgbox CinnabarIsland_Gym_Text_RamonPostBattle, MSGBOX_AUTOCLOSE
	end

CinnabarIsland_Gym_Text_RamonIntro::
	.string "I like using FIRE-type POKéMON.\n"
	.string "I just do.$"

CinnabarIsland_Gym_Text_RamonDefeat::
	.string "Too hot to handle!$"

CinnabarIsland_Gym_Text_RamonPostBattle::
	.string "I wish there were a thief POKéMON.\n"
	.string "I'd use that!$"

CinnabarIsland_Gym_EventScript_KT_Derek::
	trainerbattle_single TRAINER_KANTO_SUPER_NERD_DEREK, CinnabarIsland_Gym_Text_DerekIntro, CinnabarIsland_Gym_Text_DerekDefeat
	msgbox CinnabarIsland_Gym_Text_DerekPostBattle, MSGBOX_AUTOCLOSE
	end

CinnabarIsland_Gym_Text_DerekIntro::
	.string "I know why BLAINE became a\n"
	.string "TRAINER.$"

CinnabarIsland_Gym_Text_DerekDefeat::
	.string "Ow!$"

CinnabarIsland_Gym_Text_DerekPostBattle::
	.string "Our LEADER, BLAINE, became lost\n"
	.string "in the mountains but good.\p"
	.string "Night fell when a fiery bird\n"
	.string "POKéMON appeared.\p"
	.string "Its light allowed BLAINE to find\n"
	.string "his way down safely.$"

CinnabarIsland_Gym_EventScript_KT_Dusty::
	trainerbattle_single TRAINER_KANTO_BURGLAR_DUSTY, CinnabarIsland_Gym_Text_DustyIntro, CinnabarIsland_Gym_Text_DustyDefeat
	msgbox CinnabarIsland_Gym_Text_DustyPostBattle, MSGBOX_AUTOCLOSE
	end

CinnabarIsland_Gym_Text_DustyIntro::
	.string "I've been to many GYMS, but this\n"
	.string "one best suits my style.$"

CinnabarIsland_Gym_Text_DustyDefeat::
	.string "Yowza!\n"
	.string "Too hot!$"

CinnabarIsland_Gym_Text_DustyPostBattle::
	.string "PONYTA, NINETALES…\n"
	.string "Those are popular FIRE POKéMON.$"

CinnabarIsland_Gym_EventScript_KT_Zac::
	trainerbattle_single TRAINER_KANTO_SUPER_NERD_ZAC, CinnabarIsland_Gym_Text_ZacIntro, CinnabarIsland_Gym_Text_ZacDefeat
	msgbox CinnabarIsland_Gym_Text_ZacPostBattle, MSGBOX_AUTOCLOSE
	end

CinnabarIsland_Gym_Text_ZacIntro::
	.string "Fire is weak against H2O.$"

CinnabarIsland_Gym_Text_ZacDefeat::
	.string "Oh!\n"
	.string "Snuffed out!$"

CinnabarIsland_Gym_Text_ZacPostBattle::
	.string "Water beats fire, of course.\p"
	.string "But fire melts ice, so the FIRE\n"
	.string "type beats ICE-type POKéMON.$"

CinnabarIsland_Gym_EventScript_KT_Blaine::
	trainerbattle_single TRAINER_KANTO_LEADER_BLAINE, CinnabarIsland_Gym_Text_BlaineIntro, CinnabarIsland_Gym_Text_KT_BlaineDefeat, NULL, NO_MUSIC
	msgbox CinnabarIsland_Gym_Text_BlainePostBattle, MSGBOX_AUTOCLOSE
	end

CinnabarIsland_Gym_Text_BlaineIntro::
	.string "Hah!\p"
	.string "I am BLAINE, the red-hot LEADER\n"
	.string "of CINNABAR GYM!\p"
	.string "My fiery POKéMON are all rough\n"
	.string "and ready with intense heat!\p"
	.string "They incinerate all challengers!\p"
	.string "Hah!\n"
	.string "You better have BURN HEAL!{PLAY_BGM}{MUS_RG_ENCOUNTER_GYM_LEADER}$"

CinnabarIsland_Gym_Text_KT_BlaineDefeat::
	.string "I have burned down to nothing!\n"
	.string "Not even ashes remain!$"

CinnabarIsland_Gym_Text_BlainePostBattle::
	.string "TM38 contains FIRE BLAST.\n"
	.string "Teach it to FIRE-type POKéMON.\p"
	.string "VULPIX or CHARMELEON would be\n"
	.string "ideal for that move.$"
