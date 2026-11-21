@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.
@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.

SilphCo_6F_Frlg_MapScripts::
	.byte 0

SilphCo_6F_EventScript_WorkerM2::
	lock
	faceplayer
	goto SilphCo_6F_EventScript_WorkerM2RocketsGone

SilphCo_6F_EventScript_WorkerM2RocketsGone::
	msgbox SilphCo_6F_Text_ComeWorkForSilphWhenYoureOlder
	release
	end

SilphCo_6F_EventScript_WorkerM3::
	lock
	faceplayer
	goto SilphCo_6F_EventScript_WorkerM3RocketsGone

SilphCo_6F_EventScript_WorkerM3RocketsGone::
	msgbox SilphCo_6F_Text_BetterGetBackToWork
	release
	end

SilphCo_6F_EventScript_WorkerM1::
	lock
	faceplayer
	goto SilphCo_6F_EventScript_WorkerM1RocketsGone

SilphCo_6F_EventScript_WorkerM1RocketsGone::
	msgbox SilphCo_6F_Text_WeGotEngaged
	release
	end

SilphCo_6F_EventScript_WorkerF1::
	lock
	faceplayer
	goto SilphCo_6F_EventScript_WorkerF1RocketsGone

SilphCo_6F_EventScript_WorkerF1RocketsGone::
	msgbox SilphCo_6F_Text_NeedsMeToLookAfterHim
	release
	end

SilphCo_6F_EventScript_WorkerF2::
	lock
	faceplayer
	goto SilphCo_6F_EventScript_WorkerF2RocketsGone

SilphCo_6F_EventScript_WorkerF2RocketsGone::
	msgbox SilphCo_6F_Text_RocketsRanAwayBecauseOfYou
	release
	end

SilphCo_6F_EventScript_FloorSign::
	msgbox SilphCo_6F_Text_FloorSign, MSGBOX_SIGN
	end

SilphCo_6F_Text_BetterGetBackToWork::
	.string "Well, better get back to work.$"


SilphCo_6F_Text_WeGotEngaged::
	.string "We got engaged.\n"
	.string "Heheh!$"


SilphCo_6F_Text_NeedsMeToLookAfterHim::
	.string "He's so helpless, he needed\n"
	.string "someone like me to look after him.$"


SilphCo_6F_Text_RocketsRanAwayBecauseOfYou::
	.string "TEAM ROCKET ran away, and it's all\n"
	.string "because of you!$"


SilphCo_6F_Text_ComeWorkForSilphWhenYoureOlder::
	.string "Come work for SILPH when you\n"
	.string "get older.$"


SilphCo_6F_Text_FloorSign::
	.string "SILPH CO. HEAD OFFICE\n"
	.string "6F$"
