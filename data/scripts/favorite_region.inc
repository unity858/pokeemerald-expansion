@ The rival asks the player for their favorite region when they first meet in
@ Littleroot (rival's bedroom, or downstairs if the player tries to leave first).
@ The answer is stored in VAR_FAVORITE_REGION as an enum Region and decides which
@ starters are in PROF. BIRCH's bag (see GetStarterPokemon in src/starter_choose.c).

RivalsHouse_EventScript_MayIntroduction::
	msgbox RivalsHouse_Text_MayWhoAreYou, MSGBOX_DEFAULT
	message RivalsHouse_Text_MayAskFavoriteRegion
	waitmessage
	call RivalsHouse_EventScript_ChooseFavoriteRegion
	msgbox RivalsHouse_Text_MayFavoriteRegionAndForgot, MSGBOX_DEFAULT
	return

RivalsHouse_EventScript_BrendanIntroduction::
	msgbox RivalsHouse_Text_BrendanWhoAreYou, MSGBOX_DEFAULT
	message RivalsHouse_Text_BrendanAskFavoriteRegion
	waitmessage
	call RivalsHouse_EventScript_ChooseFavoriteRegion
	msgbox RivalsHouse_Text_BrendanFavoriteRegionAndForgot, MSGBOX_DEFAULT
	return

@ Scrolling list of regions (5 rows visible). B can't cancel. The item ids are the
@ enum Region values, so VAR_RESULT is stored as is. Leaves the name in STR_VAR_1.
RivalsHouse_EventScript_ChooseFavoriteRegion::
	dynmultipush RivalsHouse_Text_RegionKanto, REGION_KANTO
	dynmultipush RivalsHouse_Text_RegionJohto, REGION_JOHTO
	dynmultipush RivalsHouse_Text_RegionHoenn, REGION_HOENN
	dynmultipush RivalsHouse_Text_RegionSinnoh, REGION_SINNOH
	dynmultipush RivalsHouse_Text_RegionUnova, REGION_UNOVA
	dynmultipush RivalsHouse_Text_RegionKalos, REGION_KALOS
	dynmultipush RivalsHouse_Text_RegionAlola, REGION_ALOLA
	dynmultipush RivalsHouse_Text_RegionGalar, REGION_GALAR
	dynmultipush RivalsHouse_Text_RegionPaldea, REGION_PALDEA
	dynmultistack 20, 1, TRUE, 5, FALSE, REGION_NONE, DYN_MULTICHOICE_CB_NONE
	copyvar VAR_FAVORITE_REGION, VAR_RESULT
	switch VAR_FAVORITE_REGION
	case REGION_KANTO, RivalsHouse_EventScript_BufferKanto
	case REGION_JOHTO, RivalsHouse_EventScript_BufferJohto
	case REGION_SINNOH, RivalsHouse_EventScript_BufferSinnoh
	case REGION_UNOVA, RivalsHouse_EventScript_BufferUnova
	case REGION_KALOS, RivalsHouse_EventScript_BufferKalos
	case REGION_ALOLA, RivalsHouse_EventScript_BufferAlola
	case REGION_GALAR, RivalsHouse_EventScript_BufferGalar
	case REGION_PALDEA, RivalsHouse_EventScript_BufferPaldea
	bufferstring STR_VAR_1, RivalsHouse_Text_RegionHoenn
	return

RivalsHouse_EventScript_BufferKanto:
	bufferstring STR_VAR_1, RivalsHouse_Text_RegionKanto
	return

RivalsHouse_EventScript_BufferJohto:
	bufferstring STR_VAR_1, RivalsHouse_Text_RegionJohto
	return

RivalsHouse_EventScript_BufferSinnoh:
	bufferstring STR_VAR_1, RivalsHouse_Text_RegionSinnoh
	return

RivalsHouse_EventScript_BufferUnova:
	bufferstring STR_VAR_1, RivalsHouse_Text_RegionUnova
	return

RivalsHouse_EventScript_BufferKalos:
	bufferstring STR_VAR_1, RivalsHouse_Text_RegionKalos
	return

RivalsHouse_EventScript_BufferAlola:
	bufferstring STR_VAR_1, RivalsHouse_Text_RegionAlola
	return

RivalsHouse_EventScript_BufferGalar:
	bufferstring STR_VAR_1, RivalsHouse_Text_RegionGalar
	return

RivalsHouse_EventScript_BufferPaldea:
	bufferstring STR_VAR_1, RivalsHouse_Text_RegionPaldea
	return

RivalsHouse_Text_RegionKanto:
	.string "KANTO$"

RivalsHouse_Text_RegionJohto:
	.string "JOHTO$"

RivalsHouse_Text_RegionHoenn:
	.string "HOENN$"

RivalsHouse_Text_RegionSinnoh:
	.string "SINNOH$"

RivalsHouse_Text_RegionUnova:
	.string "UNOVA$"

RivalsHouse_Text_RegionKalos:
	.string "KALOS$"

RivalsHouse_Text_RegionAlola:
	.string "ALOLA$"

RivalsHouse_Text_RegionGalar:
	.string "GALAR$"

RivalsHouse_Text_RegionPaldea:
	.string "PALDEA$"

RivalsHouse_Text_MayWhoAreYou:
	.string "Huh?\n"
	.string "Who… Who are you?\p"
	.string "… … … … … … … …\n"
	.string "… … … … … … … …\p"
	.string "Oh, you're {PLAYER}{KUN}.\n"
	.string "So your move was today.\p"
	.string "Um… I'm MAY.\n"
	.string "Glad to meet you!\p"
	.string "I…\n"
	.string "I have this dream of becoming friends\l"
	.string "with POKéMON all over the world.\p"
	.string "I… I heard about you, {PLAYER}{KUN}, from\n"
	.string "my dad, PROF. BIRCH.\p"
	.string "I was hoping that you would be nice,\n"
	.string "{PLAYER}{KUN}, and that we could be friends.\p"
	.string "Oh, this is silly, isn't it?\n"
	.string "I… I've just met you, {PLAYER}{KUN}.\p"
	.string "Eheheh…$"

RivalsHouse_Text_MayAskFavoriteRegion:
	.string "Um… Can I ask you something?\n"
	.string "What's your favorite region?$"

RivalsHouse_Text_MayFavoriteRegionAndForgot:
	.string "Oh, {STR_VAR_1}? Cool!\n"
	.string "I'd love to go there someday!\p"
	.string "Oh, no! I forgot!\p"
	.string "I was supposed to go help Dad catch\n"
	.string "some wild POKéMON!\p"
	.string "{PLAYER}{KUN}, I'll catch you later!$"

RivalsHouse_Text_BrendanWhoAreYou:
	.string "Hey!\n"
	.string "You…\p"
	.string "Who are you?\p"
	.string "Oh, you're {PLAYER}, aren't you?\n"
	.string "Moved in next door, right?\p"
	.string "I didn't know that you're a girl.\p"
	.string "Dad, PROF. BIRCH, said that our new\n"
	.string "next-door neighbor is a GYM LEADER's\l"
	.string "kid, so I assumed you'd be a guy.\p"
	.string "My name's BRENDAN.\n"
	.string "So, hi, neighbor!\p"
	.string "Huh? Hey, {PLAYER}, don't you have\n"
	.string "a POKéMON?\p"
	.string "Do you want me to go catch you one?$"

RivalsHouse_Text_BrendanAskFavoriteRegion:
	.string "Oh, wait. First things first.\n"
	.string "What's your favorite region?$"

RivalsHouse_Text_BrendanFavoriteRegionAndForgot:
	.string "{STR_VAR_1}, huh? Cool!\n"
	.string "Good pick.\p"
	.string "Aw, darn, I forgot…\p"
	.string "I'm supposed to go help my dad catch\n"
	.string "some wild POKéMON.\p"
	.string "Some other time, okay?$"
