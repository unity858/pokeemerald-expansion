@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

SilphCo_1F_Frlg_MapScripts::
	.byte 0

SilphCo_1F_EventScript_Receptionist::
	msgbox SilphCo_1F_Text_WelcomePresidentInBoardroom, MSGBOX_NPC
	end

SilphCo_1F_EventScript_FloorSign::
	msgbox SilphCo_1F_Text_FloorSign, MSGBOX_SIGN
	end

SilphCo_1F_Text_WelcomePresidentInBoardroom::
	.string "Welcome.\p"
	.string "The PRESIDENT is in the boardroom\n"
	.string "on 11F.$"


SilphCo_1F_Text_FloorSign::
	.string "SILPH CO. HEAD OFFICE\n"
	.string "1F$"
