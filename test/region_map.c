#include "global.h"
#include "event_data.h"
#include "heal_location.h"
#include "main.h"
#include "overworld.h"
#include "region_map.h"
#include "regions.h"
#include "script.h"
#include "sprite.h"
#include "constants/characters.h"
#include "constants/heal_locations.h"
#include "constants/region_map_sections.h"
#include "test/test.h"

// Same offsets as region_map.c: grid cell (0,0) is cursor (1,2).
#define CURSOR_X(gridX) ((gridX) + 1)
#define CURSOR_Y(gridY) ((gridY) + 2)

EWRAM_DATA static struct RegionMap sTestRegionMap = {0};

static void SetPlayerMap(u32 mapGroup, u32 mapNum)
{
    gSaveBlock1Ptr->location.mapGroup = mapGroup;
    gSaveBlock1Ptr->location.mapNum = mapNum;
    gSaveBlock1Ptr->pos.x = 5;
    gSaveBlock1Ptr->pos.y = 5;
    gMapHeader = *Overworld_GetMapHeaderByGroupAndId(mapGroup, mapNum);
}

// Moves the fly map cursor one cell from (gridX, gridY) in direction 'key'
// through the real input callbacks, the way CB_HandleFlyMapInput does.
static void MoveFlyCursor(u32 gridX, u32 gridY, u16 key)
{
    u32 i, input = MAP_INPUT_NONE;

    ResetSpriteData();
    FreeAllSpritePalettes();
    InitRegionMap(&sTestRegionMap, FALSE);
    CreateRegionMapCursor(0, 0); // its sprite callback advances cursor movement
    sTestRegionMap.cursorPosX = CURSOR_X(gridX);
    sTestRegionMap.cursorPosY = CURSOR_Y(gridY);
    gMain.newKeys = 0;
    gMain.heldKeys = key;
    for (i = 0; i < 16 && input != MAP_INPUT_MOVE_END; i++)
    {
        input = DoRegionMapInputCallback();
        gMain.heldKeys = 0;
        AnimateSprites();
    }
    EXPECT_EQ(input, MAP_INPUT_MOVE_END);
}

static bool32 FlyMapAButtonAccepts(void)
{
    gMain.heldKeys = 0;
    gMain.newKeys = A_BUTTON;
    if (DoRegionMapInputCallback() != MAP_INPUT_A_BUTTON)
        return FALSE;
    gMain.newKeys = 0;
    // Same check as CB_HandleFlyMapInput.
    return sTestRegionMap.mapSecType == MAPSECTYPE_CITY_CANFLY
        || sTestRegionMap.mapSecType == MAPSECTYPE_BATTLE_FRONTIER;
}

static bool32 IsHealLocationWalkable(u32 healLocationId)
{
    const struct HealLocation *loc = GetHealLocation(healLocationId);
    const struct MapLayout *layout = Overworld_GetMapHeaderByGroupAndId(loc->mapGroup, loc->mapNum)->mapLayout;
    u16 block = layout->map[loc->y * layout->width + loc->x];
    return UNPACK_COLLISION(block) == 0 && UNPACK_ELEVATION(block) != 1; // elevation 1 is surf water
}

TEST("Fly map: Southern Island is selectable after the island is visited")
{
    SetPlayerMap(MAP_GROUP(MAP_LITTLEROOT_TOWN), MAP_NUM(MAP_LITTLEROOT_TOWN));
    FlagSet(FLAG_LANDMARK_SOUTHERN_ISLAND);

    EXPECT_EQ(GetRegionMapSecIdAt(CURSOR_X(12), CURSOR_Y(14)), MAPSEC_SOUTHERN_ISLAND);
    MoveFlyCursor(11, 14, DPAD_RIGHT);
    EXPECT_EQ(sTestRegionMap.mapSecId, MAPSEC_SOUTHERN_ISLAND);
    EXPECT(FlyMapAButtonAccepts());
    EXPECT_EQ(FilterFlyDestination(&sTestRegionMap), HEAL_LOCATION_SOUTHERN_ISLAND_EXTERIOR);
    EXPECT_EQ(GetHealLocation(HEAL_LOCATION_SOUTHERN_ISLAND_EXTERIOR)->mapGroup, MAP_GROUP(MAP_SOUTHERN_ISLAND_EXTERIOR));
    EXPECT_EQ(GetHealLocation(HEAL_LOCATION_SOUTHERN_ISLAND_EXTERIOR)->mapNum, MAP_NUM(MAP_SOUTHERN_ISLAND_EXTERIOR));
    EXPECT(IsHealLocationWalkable(HEAL_LOCATION_SOUTHERN_ISLAND_EXTERIOR));
}

TEST("Fly map: Southern Island is not selectable before the island is visited")
{
    SetPlayerMap(MAP_GROUP(MAP_LITTLEROOT_TOWN), MAP_NUM(MAP_LITTLEROOT_TOWN));
    FlagClear(FLAG_LANDMARK_SOUTHERN_ISLAND);

    MoveFlyCursor(11, 14, DPAD_RIGHT);
    EXPECT_EQ(sTestRegionMap.mapSecId, MAPSEC_SOUTHERN_ISLAND);
    EXPECT(!FlyMapAButtonAccepts());
}

TEST("Fly map: Battle Frontier is selectable after it is visited")
{
    SetPlayerMap(MAP_GROUP(MAP_LITTLEROOT_TOWN), MAP_NUM(MAP_LITTLEROOT_TOWN));
    FlagSet(FLAG_LANDMARK_BATTLE_FRONTIER);

    MoveFlyCursor(21, 12, DPAD_RIGHT);
    EXPECT_EQ(sTestRegionMap.mapSecId, MAPSEC_BATTLE_FRONTIER);
    EXPECT(FlyMapAButtonAccepts());
    EXPECT_EQ(FilterFlyDestination(&sTestRegionMap), HEAL_LOCATION_BATTLE_FRONTIER_OUTSIDE_EAST);
    EXPECT(IsHealLocationWalkable(HEAL_LOCATION_BATTLE_FRONTIER_OUTSIDE_EAST));
}

TEST("Fly map: a visited town is selectable")
{
    SetPlayerMap(MAP_GROUP(MAP_LITTLEROOT_TOWN), MAP_NUM(MAP_LITTLEROOT_TOWN));
    FlagSet(FLAG_VISITED_SLATEPORT_CITY);

    MoveFlyCursor(8, 11, DPAD_UP); // Route 109 -> Slateport (8,10)
    EXPECT_EQ(sTestRegionMap.mapSecId, MAPSEC_SLATEPORT_CITY);
    EXPECT(FlyMapAButtonAccepts());
    EXPECT_EQ(FilterFlyDestination(&sTestRegionMap), HEAL_LOCATION_SLATEPORT_CITY);
}

TEST("Fly map: Route 135 is a Hoenn route, not a Fly destination")
{
    u8 name[MAP_NAME_LENGTH + 1];

    EXPECT_EQ(GetRegionForSectionId(MAPSEC_ROUTE_135), REGION_HOENN);
    EXPECT_EQ(GetRegionMapType(MAPSEC_ROUTE_135), REGION_MAP_HOENN);

    SetPlayerMap(MAP_GROUP(MAP_ROUTE135), MAP_NUM(MAP_ROUTE135));
    EXPECT_EQ(gMapHeader.regionMapSectionId, MAPSEC_ROUTE_135);
    EXPECT_EQ(GetRegionMapSecIdAt(CURSOR_X(9), CURSOR_Y(14)), MAPSEC_ROUTE_135);
    EXPECT_EQ(GetRegionMapSecIdAt(CURSOR_X(11), CURSOR_Y(14)), MAPSEC_ROUTE_135);

    MoveFlyCursor(8, 14, DPAD_RIGHT);
    EXPECT_EQ(sTestRegionMap.mapSecId, MAPSEC_ROUTE_135);
    EXPECT_EQ(sTestRegionMap.mapSecType, MAPSECTYPE_ROUTE);
    EXPECT(!FlyMapAButtonAccepts());

    GetMapNameGeneric(name, MAPSEC_ROUTE_135);
    EXPECT_EQ(name[0], CHAR_R);
}

// Arriving by ferry (warp) and surfing in from Route 135 (map connection) both
// run the exterior's ON_TRANSITION script, which marks the island visited.
TEST("Fly map: entering Southern Island Exterior sets its fly flag")
{
    FlagClear(FLAG_LANDMARK_SOUTHERN_ISLAND);
    SetPlayerMap(MAP_GROUP(MAP_SOUTHERN_ISLAND_EXTERIOR), MAP_NUM(MAP_SOUTHERN_ISLAND_EXTERIOR));
    RunOnTransitionMapScript();
    EXPECT(FlagGet(FLAG_LANDMARK_SOUTHERN_ISLAND));
}
