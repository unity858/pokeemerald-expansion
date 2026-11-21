@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

FiveIsland_MemorialPillar_Frlg_MapScripts::
	.byte 0

FiveIsland_MemorialPillar_EventScript_MemorialMan::
	lock
	goto FiveIsland_MemorialPillar_EventScript_AlreadyGotTM42

FiveIsland_MemorialPillar_EventScript_AlreadyGotTM42::
	msgbox FiveIsland_MemorialPillar_Text_ScrubScrubTectonix
	release
	end

FiveIsland_MemorialPillar_EventScript_Memorial::
	lockall
	goto FiveIsland_MemorialPillar_EventScript_MemorialLemonadeAlreadyPlaced

FiveIsland_MemorialPillar_EventScript_MemorialLemonadeAlreadyPlaced::
	msgbox FiveIsland_MemorialPillar_Text_HereLiesTectonix
	releaseall
	end

FiveIsland_MemorialPillar_Text_ScrubScrubTectonix::
	.string "Scrub, scrub…\p"
	.string "… … …\n"
	.string "TECTONIX…$"


FiveIsland_MemorialPillar_Text_HereLiesTectonix::
	.string "Boulders and rocks are neatly piled\n"
	.string "up as a cairn.\p"
	.string "“Here lies TECTONIX” is engraved\n"
	.string "on a boulder.$"
