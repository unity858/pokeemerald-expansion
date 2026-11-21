@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

FuchsiaCity_WardensHouse_Frlg_MapScripts::
	.byte 0

FuchsiaCity_WardensHouse_EventScript_Warden::
	lock
	faceplayer
	goto FuchsiaCity_WardensHouse_EventScript_ExplainStrength

FuchsiaCity_WardensHouse_EventScript_ExplainStrength::
	msgbox FuchsiaCity_WardensHouse_Text_ExplainStrength
	release
	end

FuchsiaCity_WardensHouse_EventScript_DisplaySign1::
	msgbox FuchsiaCity_WardensHouse_Text_MonPhotosFossilsOnDisplay, MSGBOX_SIGN
	end

FuchsiaCity_WardensHouse_EventScript_DisplaySign2::
	msgbox FuchsiaCity_WardensHouse_Text_OldMonMerchandiseOnDisplay, MSGBOX_SIGN
	end

FuchsiaCity_WardensHouse_Text_ExplainStrength::
	.string "WARDEN: Inside HM04 you'll find\n"
	.string "STRENGTH.\p"
	.string "It lets POKéMON move boulders when\n"
	.string "you're outside of battle.\p"
	.string "Oh yes, did you find the SECRET\n"
	.string "HOUSE in the SAFARI ZONE?$"

@ Unused

FuchsiaCity_WardensHouse_Text_MonPhotosFossilsOnDisplay::
	.string "POKéMON photos and fossils are on\n"
	.string "display.$"


FuchsiaCity_WardensHouse_Text_OldMonMerchandiseOnDisplay::
	.string "Old POKéMON merchandise is on\n"
	.string "display.$"
