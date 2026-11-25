#ifndef GUARD_STATIC_ENCOUNTERS_H
#define GUARD_STATIC_ENCOUNTERS_H

// State of the hack's static and gift encounters (STATIC_ENC_* / GIFT_* IDs,
// include/constants/static_encounters.h), kept in gSaveBlock3Ptr->staticEncounterFlags.

bool32 IsStaticEncounterDefeated(u32 id);
bool32 IsStaticEncounterCaught(u32 id);
bool32 IsGiftReceived(u32 id);
void SetStaticEncounterDefeated(u32 id);
void SetStaticEncounterCaught(u32 id);
void SetGiftReceived(u32 id);
void ClearStaticEncounterDefeated(u32 id);
void ClearStaticEncounterCaught(u32 id);
void ClearGiftReceived(u32 id);

// Generic access by bit (STATIC_ENC_BIT_DEFEATED / _CAUGHT / _RECEIVED).
bool32 GetStaticEncounterBit(u32 id, u32 bit);
void SetStaticEncounterBit(u32 id, u32 bit);
void ClearStaticEncounterBit(u32 id, u32 bit);

// Hall of Fame: every knocked-out static comes back. Caught and received stay.
void ClearAllStaticEncounterDefeated(void);
// New game.
void ResetStaticEncounters(void);

#endif // GUARD_STATIC_ENCOUNTERS_H
