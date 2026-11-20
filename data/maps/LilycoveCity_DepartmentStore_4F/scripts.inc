LilycoveCity_DepartmentStore_4F_MapScripts::
	.byte 0

LilycoveCity_DepartmentStore_4F_EventScript_Gentleman::
	msgbox LilycoveCity_DepartmentStore_4F_Text_AttackOrDefenseTM, MSGBOX_NPC
	end

LilycoveCity_DepartmentStore_4F_EventScript_Woman::
	msgbox LilycoveCity_DepartmentStore_4F_Text_FiftyDifferentTMs, MSGBOX_NPC
	end

LilycoveCity_DepartmentStore_4F_EventScript_Youngster::
	msgbox LilycoveCity_DepartmentStore_4F_Text_PokemonOnlyHaveFourMoves, MSGBOX_NPC
	end

LilycoveCity_DepartmentStore_4F_EventScript_ClerkLeft::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart LilycoveCity_DepartmentStore_4F_Pokemart_AttackTMs
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
LilycoveCity_DepartmentStore_4F_Pokemart_AttackTMs:
	.2byte ITEM_TM_FIRE_BLAST
	.2byte ITEM_TM_THUNDER
	.2byte ITEM_TM_BLIZZARD
	.2byte ITEM_TM_HYPER_BEAM
	.2byte ITEM_TM_ENERGY_BALL
	.2byte ITEM_TM_BRUTAL_SWING
	.2byte ITEM_TM_EMBARGO
	.2byte ITEM_TM_PAYBACK
	.2byte ITEM_TM_GYRO_BALL
	.2byte ITEM_TM_SWORDS_DANCE
	.2byte ITEM_TM_BULLDOZE
	.2byte ITEM_TM_FROST_BREATH
	.2byte ITEM_TM_X_SCISSOR
	.2byte ITEM_TM_DRAGON_TAIL
	.2byte ITEM_TM_POISON_JAB
	.2byte ITEM_TM_SLEEP_TALK
	.2byte ITEM_TM_FLASH_CANNON
	.2byte ITEM_TM_NATURE_POWER
	.2byte ITEM_TM_DARK_PULSE
	.2byte ITEM_TM_SLUDGE_WAVE
	.2byte ITEM_TM_LEECH_LIFE
	.2byte ITEM_TM_PLAY_ROUGH
	.2byte ITEM_TM_EARTH_POWER
	.2byte ITEM_TM_GUNK_SHOT
	.2byte ITEM_TM_POLLEN_PUFF
	.2byte ITEM_TM_NASTY_PLOT
	.2byte ITEM_TM_BUG_BUZZ
	.2byte ITEM_TM_DRAGON_DANCE
	.2byte ITEM_TM_TRI_ATTACK
	pokemartlistend

LilycoveCity_DepartmentStore_4F_EventScript_ClerkRight::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart LilycoveCity_DepartmentStore_4F_Pokemart_DefenseTMs
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
LilycoveCity_DepartmentStore_4F_Pokemart_DefenseTMs:
	.2byte ITEM_TM_PROTECT
	.2byte ITEM_TM_SAFEGUARD
	.2byte ITEM_TM_REFLECT
	.2byte ITEM_TM_LIGHT_SCREEN
	.2byte ITEM_TM_DARKEST_LARIAT
	.2byte ITEM_TM_QUASH
	.2byte ITEM_TM_EMBARGO
	.2byte ITEM_TM_SMART_STRIKE
	.2byte ITEM_TM_AURORA_VEIL
	.2byte ITEM_TM_PSYCH_UP
	.2byte ITEM_TM_INFESTATION
	.2byte ITEM_TM_U_TURN
	.2byte ITEM_TM_SUBSTITUTE
	.2byte ITEM_TM_TRICK_ROOM
	.2byte ITEM_TM_SNARL
	.2byte ITEM_TM_CONFIDE
	pokemartlistend

LilycoveCity_DepartmentStore_4F_Text_AttackOrDefenseTM:
	.string "Hmm…\p"
	.string "An attacking move…\n"
	.string "Or a defensive move…\p"
	.string "It's no easy matter to decide which TM\n"
	.string "moves should be taught to POKéMON…$"

LilycoveCity_DepartmentStore_4F_Text_FiftyDifferentTMs:
	.string "There are so many different kinds of\n"
	.string "TM moves.\p"
	.string "A catalog I read said there are fifty\n"
	.string "different kinds.$"

LilycoveCity_DepartmentStore_4F_Text_PokemonOnlyHaveFourMoves:
	.string "I'd like to get all the different TMs,\n"
	.string "but a POKéMON learns only four moves.$"

