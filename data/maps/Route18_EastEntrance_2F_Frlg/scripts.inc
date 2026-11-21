@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

Route18_EastEntrance_2F_Frlg_MapScripts::
	.byte 0

Route18_EastEntrance_2F_EventScript_LeftBinoculars::
	msgbox Route18_EastEntrance_2F_Text_PalletTownInWest, MSGBOX_SIGN
	end

Route18_EastEntrance_2F_EventScript_RightBinoculars::
	msgbox Route18_EastEntrance_2F_Text_PeopleSwimming, MSGBOX_SIGN
	end

Route18_EastEntrance_2F_Text_PalletTownInWest::
	.string "Let's see what the binoculars have\n"
	.string "to show…\p"
	.string "PALLET TOWN is in the west.$"


Route18_EastEntrance_2F_Text_PeopleSwimming::
	.string "Let's see what the binoculars have\n"
	.string "to show…\p"
	.string "There are people swimming.$"
