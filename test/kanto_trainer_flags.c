#include "global.h"
#include "battle_setup.h"
#include "test/test.h"
#include "constants/opponents.h"

#if EXTRA_TRAINER_FLAGS_BYTES > 0
TEST("Kanto trainer flags keep the SaveBlock3 layout")
{
    // staticEncounterFlags must stay right after the capped kantoTrainerFlags so older saves line up.
    EXPECT_LE(sizeof(gSaveBlock3Ptr->kantoTrainerFlags), EXTRA_TRAINER_FLAGS_BYTES_1_MAX);
    EXPECT_EQ(offsetof(struct SaveBlock3, staticEncounterFlags),
              offsetof(struct SaveBlock3, kantoTrainerFlags) + sizeof(gSaveBlock3Ptr->kantoTrainerFlags));
}

TEST("Kanto trainer flags are set, read and cleared independently")
{
    u32 lastId = TRAINERS_COUNT - 1; // past the first EXTRA_TRAINER_FLAGS_BYTES_1_MAX bytes once they overflow
    u32 firstId = TRAINER_FLAGS_COUNT;

    ClearTrainerFlag(firstId);
    ClearTrainerFlag(lastId);
    ClearTrainerFlag(TRAINER_KANTO_BOSS_GIOVANNI);
    ClearTrainerFlag(TRAINER_KANTO_TEAM_ROCKET_GRUNT_ICEFALL);

    SetTrainerFlag(lastId);
    EXPECT(HasTrainerBeenFought(lastId));
    EXPECT(!HasTrainerBeenFought(firstId));
    EXPECT(!HasTrainerBeenFought(lastId - 1));

    SetTrainerFlag(TRAINER_KANTO_BOSS_GIOVANNI);
    EXPECT(HasTrainerBeenFought(TRAINER_KANTO_BOSS_GIOVANNI));
    EXPECT(!HasTrainerBeenFought(TRAINER_KANTO_TEAM_ROCKET_GRUNT_ICEFALL));

    ClearTrainerFlag(lastId);
    ClearTrainerFlag(TRAINER_KANTO_BOSS_GIOVANNI);
    EXPECT(!HasTrainerBeenFought(lastId));
    EXPECT(!HasTrainerBeenFought(TRAINER_KANTO_BOSS_GIOVANNI));
}
#endif
