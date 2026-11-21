@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

PokemonMansion_2F_Frlg_MapScripts::
	.byte 0

PokemonMansion_2F_EventScript_DiaryJuly5th::
	msgbox PokemonMansion_1F_Text_NewMonDiscoveredInGuyanaJungle, MSGBOX_SIGN
	end

PokemonMansion_2F_EventScript_DiaryJuly10th::
	msgbox PokemonMansion_1F_Text_ChristenedDiscoveredMonMew, MSGBOX_SIGN
	end

PokemonMansion_1F_Text_NewMonDiscoveredInGuyanaJungle::
	.string "Diary: July 5\n"
	.string "Guyana, South America\p"
	.string "A new POKéMON was discovered deep\n"
	.string "in the jungle.$"


PokemonMansion_1F_Text_ChristenedDiscoveredMonMew::
	.string "Diary: July 10\n"
	.string "We christened the newly discovered\l"
	.string "POKéMON, MEW.$"
