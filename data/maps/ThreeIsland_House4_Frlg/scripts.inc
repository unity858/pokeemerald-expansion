@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

ThreeIsland_House4_Frlg_MapScripts::
	.byte 0

ThreeIsland_House4_EventScript_BaldingMan::
	msgbox ThreeIsland_House4_Text_GhostsInBerryForest, MSGBOX_NPC
	end

ThreeIsland_House4_EventScript_LittleBoy::
	msgbox ThreeIsland_House4_Text_PapaKeepsLyingToMe, MSGBOX_NPC
	end

ThreeIsland_House4_Text_GhostsInBerryForest::
	.string "You must never, ever go out to\n"
	.string "the BERRY FOREST alone.\p"
	.string "Why?\n"
	.string "There are ghosts there.$"


ThreeIsland_House4_Text_PapaKeepsLyingToMe::
	.string "Papa keeps lying to me, and won't\n"
	.string "let me go out and play!$"
