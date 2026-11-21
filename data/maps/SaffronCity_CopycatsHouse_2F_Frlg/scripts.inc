@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

SaffronCity_CopycatsHouse_2F_Frlg_MapScripts::
	.byte 0

SaffronCity_CopycatsHouse_2F_EventScript_Doduo::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_DODUO, CRY_MODE_NORMAL
	msgbox SaffronCity_CopycatsHouse_2F_Text_Doduo
	waitmoncry
	release
	end

SaffronCity_CopycatsHouse_2F_EventScript_Doll::
	lock
	msgbox SaffronCity_CopycatsHouse_2F_Text_RareMonOnlyDoll
	release
	end

SaffronCity_CopycatsHouse_2F_EventScript_Computer::
	msgbox SaffronCity_CopycatsHouse_2F_Text_MySecrets, MSGBOX_SIGN
	end

SaffronCity_CopycatsHouse_2F_EventScript_Game::
	msgbox SaffronCity_CopycatsHouse_2F_Text_MarioWearingABucket, MSGBOX_SIGN
	end

SaffronCity_CopycatsHouse_2F_Text_Doduo::
	.string "DODUO: Giiih!\p"
	.string "PRETTY MIRROR LOOK AT ME,\n"
	.string "SEE HOW PRETTY I CAN BE?$"


SaffronCity_CopycatsHouse_2F_Text_RareMonOnlyDoll::
	.string "This is a rare POKéMON!\n"
	.string "Huh? It's only a doll!$"


SaffronCity_CopycatsHouse_2F_Text_MarioWearingABucket::
	.string "A game with MARIO wearing a bucket\n"
	.string "on his head!$"


SaffronCity_CopycatsHouse_2F_Text_MySecrets::
	.string "…\p"
	.string "My Secrets!\p"
	.string "Skill: Mimicry!\n"
	.string "Hobby: Collecting dolls!\l"
	.string "Favorite POKéMON: CLEFAIRY!$"
