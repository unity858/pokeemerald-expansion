@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

Route12_Frlg_MapScripts::
	.byte 0

Route12_EventScript_RouteSign::
	msgbox Route12_Text_RouteSign, MSGBOX_SIGN
	end

Route12_EventScript_FishingSign::
	msgbox Route12_Text_SportfishingArea, MSGBOX_SIGN
	end

Route12_Text_RouteSign::
	.string "ROUTE 12 \n"
	.string "North to LAVENDER$"


Route12_Text_SportfishingArea::
	.string "SPORTFISHING AREA$"
