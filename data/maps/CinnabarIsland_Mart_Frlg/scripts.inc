@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

CinnabarIsland_Mart_Frlg_MapScripts::
	.byte 0

CinnabarIsland_Mart_EventScript_Woman::
	msgbox CinnabarIsland_Mart_Text_DontTheyHaveXAttack, MSGBOX_NPC
	end

CinnabarIsland_Mart_EventScript_Scientist::
	msgbox CinnabarIsland_Mart_Text_ExtraItemsNeverHurt, MSGBOX_NPC
	end

CinnabarIsland_Mart_Items::
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_REVIVE
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_NONE
	release
	end


CinnabarIsland_Mart_Text_DontTheyHaveXAttack::
	.string "Don't they have X ATTACK?\p"
	.string "I like it because it raises the\n"
	.string "ATTACK stat in battle.$"


CinnabarIsland_Mart_Text_ExtraItemsNeverHurt::
	.string "It never hurts to have extra items.\n"
	.string "You never know what might happen.$"



CinnabarIsland_Mart_EventScript_ClerkEm0::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart CinnabarIsland_Mart_Items
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end
