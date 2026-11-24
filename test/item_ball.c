#include "global.h"
#include "event_data.h"
#include "item.h"
#include "string_util.h"
#include "constants/characters.h"
#include "test/overworld_script.h"
#include "test/test.h"

// Std_FindItem, Std_ObtainItem and the hidden item/berry scripts call
// EventScript_BufferPocketNameAndTryFanfare. It must return for every pocket;
// falling through its switch ends the whole script, so the item is never picked up.
TEST("EventScript_BufferPocketNameAndTryFanfare returns for every pocket")
{
    enum Item item = ITEM_NONE;

    PARAMETRIZE { item = ITEM_REPEL; }
    PARAMETRIZE { item = ITEM_POTION; }
    PARAMETRIZE { item = ITEM_POKE_BALL; }
    PARAMETRIZE { item = ITEM_X_ATTACK; }
    PARAMETRIZE { item = ITEM_CHARCOAL; }
    PARAMETRIZE { item = ITEM_VENUSAURITE; }
    PARAMETRIZE { item = ITEM_ORAN_BERRY; }
    PARAMETRIZE { item = ITEM_RARE_CANDY; }
    PARAMETRIZE { item = ITEM_TM01; }
    PARAMETRIZE { item = ITEM_BICYCLE; }

    gSpecialVar_0x8004 = item;
    gStringVar3[0] = EOS;
    RUN_OVERWORLD_SCRIPT(
        setvar VAR_0x8007, FALSE;
        setvar VAR_0x8008, FALSE;
        checkitemtype VAR_0x8004;
        call EventScript_BufferPocketNameAndTryFanfare;
        setvar VAR_0x8008, TRUE;
    );
    EXPECT_EQ(gSpecialVar_0x8008, TRUE);
    EXPECT_NE(gStringVar3[0], EOS);
}

TEST("EventScript_BufferPutAwayPocketName returns for every pocket")
{
    u32 pocket = 0;

    for (u32 i = 0; i < POCKETS_COUNT; i++)
        PARAMETRIZE { pocket = i; }

    gStringVar3[0] = EOS;
    gSpecialVar_Result = pocket;
    RUN_OVERWORLD_SCRIPT(
        setvar VAR_0x8008, FALSE;
        call EventScript_BufferPutAwayPocketName;
        setvar VAR_0x8008, TRUE;
    );
    EXPECT_EQ(gSpecialVar_0x8008, TRUE);
    EXPECT_NE(gStringVar3[0], EOS);
}
