@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

CeladonCity_Condominiums_2F_Frlg_MapScripts::
	.byte 0

CeladonCity_Condominiums_2F_EventScript_MeetingRoomSign::
	msgbox CeladonCity_Condominiums_2F_Text_GameFreakMeetingRoom, MSGBOX_SIGN
	end

CeladonCity_Condominiums_2F_Text_GameFreakMeetingRoom::
	.string "GAME FREAK Meeting Room$"
