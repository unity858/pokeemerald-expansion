@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

FourIsland_LoreleisHouse_Frlg_MapScripts::
	.byte 0

FourIsland_LoreleisHouse_EventScript_Lorelei::
	lock
	faceplayer
	goto FourIsland_LoreleisHouse_EventScript_Lorelei3

FourIsland_LoreleisHouse_EventScript_Lorelei3::
	msgbox FourIsland_LoreleisHouse_Text_WillDoWhatICanHereAndNow
	release
	end

FourIsland_LoreleisHouse_EventScript_Doll::
	lock
	msgbox FourIsland_LoreleisHouse_Text_StuffedMonDollsGalore
	release
	end

FourIsland_LoreleisHouse_Text_WillDoWhatICanHereAndNow::
	.string "I don't know what will happen in\n"
	.string "the future, but…\p"
	.string "I will do what I can here and now.\n"
	.string "That's all I can do.$"


FourIsland_LoreleisHouse_Text_StuffedMonDollsGalore::
	.string "Stuffed POKéMON dolls galore!$"
