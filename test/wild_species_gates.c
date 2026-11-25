#include "global.h"
#include "event_data.h"
#include "wild_encounter.h"
#include "test/test.h"
#include "constants/flags.h"

TEST("Postgame wild species are swapped until the game is cleared")
{
    FlagClear(FLAG_SYS_GAME_CLEAR);
    EXPECT_EQ(GetWildEncounterSpecies(SPECIES_PHEROMOSA), SPECIES_BUZZWOLE);
    EXPECT_EQ(GetWildEncounterSpecies(SPECIES_IRON_BUNDLE), SPECIES_RAGING_BOLT);
    EXPECT_EQ(GetWildEncounterSpecies(SPECIES_FLUTTER_MANE), SPECIES_IRON_THORNS);
    EXPECT_EQ(GetWildEncounterSpecies(SPECIES_ROARING_MOON), SPECIES_IRON_VALIANT);
    EXPECT_EQ(GetWildEncounterSpecies(SPECIES_IRON_THORNS), SPECIES_IRON_THORNS);
    EXPECT_EQ(GetWildEncounterSpecies(SPECIES_GREAT_TUSK), SPECIES_GREAT_TUSK);

    FlagSet(FLAG_SYS_GAME_CLEAR);
    EXPECT_EQ(GetWildEncounterSpecies(SPECIES_PHEROMOSA), SPECIES_PHEROMOSA);
    EXPECT_EQ(GetWildEncounterSpecies(SPECIES_IRON_BUNDLE), SPECIES_IRON_BUNDLE);
    EXPECT_EQ(GetWildEncounterSpecies(SPECIES_FLUTTER_MANE), SPECIES_FLUTTER_MANE);
    EXPECT_EQ(GetWildEncounterSpecies(SPECIES_ROARING_MOON), SPECIES_ROARING_MOON);
    EXPECT_EQ(GetWildEncounterSpecies(SPECIES_BUZZWOLE), SPECIES_BUZZWOLE);
    FlagClear(FLAG_SYS_GAME_CLEAR);
}
