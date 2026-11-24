@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

CeruleanCity_House3_Frlg_MapScripts::
	.byte 0

CeruleanCity_House3_EventScript_OldWoman::
	msgbox CeruleanCity_House3_Text_PleaseTradeWithMyHusband, MSGBOX_NPC
	end

CeruleanCity_House3_Text_PleaseTradeWithMyHusband::
	.string "My husband likes trading POKéMON.\p"
	.string "You're collecting POKéMON for your\n"
	.string "POKéDEX, aren't you?\p"
	.string "Would you please trade with him?$"
