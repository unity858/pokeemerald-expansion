#ifndef GUARD_REGIONS_H
#define GUARD_REGIONS_H

#include "global.h"
#include "constants/regions.h"

enum KantoSubRegion GetKantoSubregion(u32 mapSecId);

static inline enum Region GetRegionForSectionId(u32 sectionId)
{
    if (sectionId >= KANTO_MAPSEC_START && sectionId < MAPSEC_SPECIAL_AREA)
        return REGION_KANTO;
    return REGION_HOENN;
}

static inline enum Region GetCurrentRegion(void)
{
    return GetRegionForSectionId(gMapHeader.regionMapSectionId);
}

// TRUE when the current map uses an FRLG layout (Kanto/Sevii maps linked into Emerald),
// or always in the FRLG builds. Use this instead of IS_FRLG for map/tileset behaviour.
static inline bool32 IsCurrentMapFrlg(void)
{
    return IS_FRLG || (gMapHeader.mapLayout != NULL && gMapHeader.mapLayout->isFrlg);
}

#endif // GUARD_REGIONS_H
