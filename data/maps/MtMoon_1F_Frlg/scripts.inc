@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

MtMoon_1F_Frlg_MapScripts::
	.byte 0

MtMoon_1F_EventScript_ZubatSign::
	msgbox MtMoon_1F_Text_ZubatIsABloodsucker, MSGBOX_SIGN
	end

MtMoon_1F_Text_ZubatIsABloodsucker::
	.string "Beware!\n"
	.string "ZUBAT is a bloodsucker!$"
