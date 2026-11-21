@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

CeruleanCity_BikeShop_Frlg_MapScripts::
	.byte 0

CeruleanCity_BikeShop_EventScript_Clerk::
	lock
	faceplayer
	goto CeruleanCity_BikeShop_EventScript_AlreadyGotBicycle

CeruleanCity_BikeShop_EventScript_AlreadyGotBicycle::
	msgbox CeruleanCity_BikeShop_Text_HowDoYouLikeNewBicycle
	release
	end

CeruleanCity_BikeShop_EventScript_Woman::
	msgbox CeruleanCity_BikeShop_Text_CityBikeGoodEnoughForMe, MSGBOX_NPC
	end

CeruleanCity_BikeShop_EventScript_Youngster::
	lock
	faceplayer
	goto CeruleanCity_BikeShop_EventScript_YoungsterHaveBike

CeruleanCity_BikeShop_EventScript_YoungsterHaveBike::
	msgbox CeruleanCity_BikeShop_Text_WowYourBikeIsCool
	release
	end

CeruleanCity_BikeShop_EventScript_Bicycle::
	msgbox CeruleanCity_BikeShop_Text_ShinyNewBicycle, MSGBOX_SIGN
	end

CeruleanCity_BikeShop_Text_HowDoYouLikeNewBicycle::
	.string "How do you like your new BICYCLE?\n"
	.string "Do you like how it rides?\p"
	.string "You can take it out on CYCLING\n"
	.string "ROAD and even into caves!$"


CeruleanCity_BikeShop_Text_CityBikeGoodEnoughForMe::
	.string "A plain city bike is good enough\n"
	.string "for me.\p"
	.string "After all, you can't put a shopping\n"
	.string "basket on a mountain bike.$"


CeruleanCity_BikeShop_Text_WowYourBikeIsCool::
	.string "Wow.\n"
	.string "Your BIKE is really cool!$"

@ Unused

CeruleanCity_BikeShop_Text_ShinyNewBicycle::
	.string "A shiny new BICYCLE!$"
