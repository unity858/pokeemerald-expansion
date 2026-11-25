#include "global.h"
#include "event_data.h"
#include "static_encounters.h"
#include "test/overworld_script.h"
#include "test/test.h"
#include "constants/static_encounters.h"

TEST("Static encounter capacity fits the IDs")
{
    EXPECT_LE(STATIC_ENC_COUNT, STATIC_ENC_MAX);
    EXPECT_EQ(sizeof(gSaveBlock3Ptr->staticEncounterFlags) * 8, STATIC_ENC_MAX * 2);
}

TEST("Static encounter bits are set, read and cleared independently")
{
    ResetStaticEncounters();

    SetStaticEncounterDefeated(STATIC_ENC_ZAPDOS);
    SetStaticEncounterCaught(STATIC_ENC_MOLTRES);
    SetGiftReceived(GIFT_KUBFU);

    EXPECT(IsStaticEncounterDefeated(STATIC_ENC_ZAPDOS));
    EXPECT(!IsStaticEncounterCaught(STATIC_ENC_ZAPDOS));
    EXPECT(IsStaticEncounterCaught(STATIC_ENC_MOLTRES));
    EXPECT(!IsStaticEncounterDefeated(STATIC_ENC_MOLTRES));
    EXPECT(IsGiftReceived(GIFT_KUBFU));
    // Neighbours in the same byte are untouched.
    EXPECT(!IsStaticEncounterDefeated(STATIC_ENC_ARTICUNO));
    EXPECT(!IsStaticEncounterCaught(STATIC_ENC_ARTICUNO));
    EXPECT(!IsStaticEncounterDefeated(STATIC_ENC_LATIAS));
    EXPECT(!IsStaticEncounterCaught(STATIC_ENC_LATIAS));
    EXPECT(!IsGiftReceived(GIFT_POIPOLE));
    EXPECT(!IsGiftReceived(GIFT_COSMOG));

    ClearStaticEncounterDefeated(STATIC_ENC_ZAPDOS);
    ClearStaticEncounterCaught(STATIC_ENC_MOLTRES);
    ClearGiftReceived(GIFT_KUBFU);
    EXPECT(!IsStaticEncounterDefeated(STATIC_ENC_ZAPDOS));
    EXPECT(!IsStaticEncounterCaught(STATIC_ENC_MOLTRES));
    EXPECT(!IsGiftReceived(GIFT_KUBFU));
}

TEST("Static encounter IDs up to the capacity work, IDs past it are ignored")
{
    u32 i;
    ResetStaticEncounters();

    SetStaticEncounterCaught(STATIC_ENC_MAX - 1);
    EXPECT(IsStaticEncounterCaught(STATIC_ENC_MAX - 1));
    SetStaticEncounterCaught(STATIC_ENC_MAX);
    EXPECT(!IsStaticEncounterCaught(STATIC_ENC_MAX));
    for (i = 0; i < STATIC_ENC_MAX - 1; i++)
        EXPECT(!IsStaticEncounterCaught(i) && !IsStaticEncounterDefeated(i));
}

TEST("ClearAllStaticEncounterDefeated keeps caught and received")
{
    u32 i;
    ResetStaticEncounters();

    for (i = 0; i < STATIC_ENC_MAX; i++)
    {
        SetStaticEncounterDefeated(i);
        if (i % 3 == 0)
            SetStaticEncounterCaught(i);
    }
    ClearAllStaticEncounterDefeated();
    for (i = 0; i < STATIC_ENC_MAX; i++)
    {
        EXPECT(!IsStaticEncounterDefeated(i));
        EXPECT_EQ(IsStaticEncounterCaught(i), (i % 3 == 0));
    }
}

TEST("Static encounter script macros")
{
    ResetStaticEncounters();

    RUN_OVERWORLD_SCRIPT(
        setstaticenc STATIC_ENC_KYUREM, DEFEATED;
        setstaticenc STATIC_ENC_CHI_YU, CAUGHT;
        setstaticenc GIFT_COSMOG, RECEIVED;
    );
    EXPECT(IsStaticEncounterDefeated(STATIC_ENC_KYUREM));
    EXPECT(IsStaticEncounterCaught(STATIC_ENC_CHI_YU));
    EXPECT(IsGiftReceived(GIFT_COSMOG));

    RUN_OVERWORLD_SCRIPT(checkstaticenc STATIC_ENC_KYUREM, DEFEATED;);
    EXPECT_EQ(gSpecialVar_Result, TRUE);
    RUN_OVERWORLD_SCRIPT(checkstaticenc STATIC_ENC_KYUREM, CAUGHT;);
    EXPECT_EQ(gSpecialVar_Result, FALSE);
    RUN_OVERWORLD_SCRIPT(setvar VAR_0x8005, GIFT_COSMOG; checkstaticenc VAR_0x8005, RECEIVED;);
    EXPECT_EQ(gSpecialVar_Result, TRUE);

    RUN_OVERWORLD_SCRIPT(clearallstaticencdefeated;);
    EXPECT(!IsStaticEncounterDefeated(STATIC_ENC_KYUREM));
    EXPECT(IsStaticEncounterCaught(STATIC_ENC_CHI_YU));
    EXPECT(IsGiftReceived(GIFT_COSMOG));

    RUN_OVERWORLD_SCRIPT(clearstaticenc GIFT_COSMOG, RECEIVED;);
    EXPECT(!IsGiftReceived(GIFT_COSMOG));
}

TEST("setupstaticenc hides the static unless gated in and neither caught nor knocked out")
{
    ResetStaticEncounters();

    // Gate not met
    FlagClear(FLAG_TEMP_2);
    FlagClear(FLAG_TEMP_1);
    RUN_OVERWORLD_SCRIPT(setupstaticenc STATIC_ENC_TAPU_FINI, FLAG_TEMP_1, FLAG_TEMP_2;);
    EXPECT(FlagGet(FLAG_TEMP_1));

    // Gate met: shown
    FlagSet(FLAG_TEMP_2);
    RUN_OVERWORLD_SCRIPT(setupstaticenc STATIC_ENC_TAPU_FINI, FLAG_TEMP_1, FLAG_TEMP_2;);
    EXPECT(!FlagGet(FLAG_TEMP_1));

    // Knocked out: hidden until the Hall of Fame clears it
    SetStaticEncounterDefeated(STATIC_ENC_TAPU_FINI);
    RUN_OVERWORLD_SCRIPT(setupstaticenc STATIC_ENC_TAPU_FINI, FLAG_TEMP_1, FLAG_TEMP_2;);
    EXPECT(FlagGet(FLAG_TEMP_1));
    ClearAllStaticEncounterDefeated();
    RUN_OVERWORLD_SCRIPT(setupstaticenc STATIC_ENC_TAPU_FINI, FLAG_TEMP_1, FLAG_TEMP_2;);
    EXPECT(!FlagGet(FLAG_TEMP_1));

    // Caught: hidden for good
    SetStaticEncounterCaught(STATIC_ENC_TAPU_FINI);
    ClearAllStaticEncounterDefeated();
    RUN_OVERWORLD_SCRIPT(setupstaticenc STATIC_ENC_TAPU_FINI, FLAG_TEMP_1, FLAG_TEMP_2;);
    EXPECT(FlagGet(FLAG_TEMP_1));

    // No gate (0)
    ResetStaticEncounters();
    FlagClear(FLAG_TEMP_2);
    RUN_OVERWORLD_SCRIPT(setupstaticenc STATIC_ENC_TAPU_FINI, FLAG_TEMP_1, 0;);
    EXPECT(!FlagGet(FLAG_TEMP_1));
}
