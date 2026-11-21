@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

FiveIsland_House1_Frlg_MapScripts::
	.byte 0

FiveIsland_House1_EventScript_Woman::
	msgbox FiveIsland_House1_Text_HusbandWentOffFishing, MSGBOX_NPC
	end

FiveIsland_House1_Text_HusbandWentOffFishing::
	.string "Don't worry about buying anything\n"
	.string "for dinner tonight!\p"
	.string "…That's what my husband said when\n"
	.string "he went off fishing today.\p"
	.string "I'm not sure if I can count on him\n"
	.string "to live up to that promise.$"
