@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

SSAnne_1F_Room1_Frlg_MapScripts::
	.byte 0

SSAnne_1F_Room1_EventScript_Gentleman::
	msgbox SSAnne_1F_Room1_Text_ImAGlobalPoliceAgent, MSGBOX_NPC
	end

SSAnne_1F_Room1_Text_ImAGlobalPoliceAgent::
	.string "Ssh…!\n"
	.string "I'm a GLOBAL POLICE agent.\p"
	.string "I'm on the trail of TEAM ROCKET.\n"
	.string "They're up to nothing good!$"
