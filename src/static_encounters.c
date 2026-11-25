#include "global.h"
#include "event_data.h"
#include "script.h"
#include "static_encounters.h"
#include "constants/static_encounters.h"

// Two bits per encounter ID, packed four IDs to a byte:
//   bit 0 = STATIC_ENC_BIT_DEFEATED, bit 1 = STATIC_ENC_BIT_CAUGHT (= _RECEIVED).
// See include/constants/static_encounters.h.

STATIC_ASSERT(STATIC_ENC_COUNT <= STATIC_ENC_MAX, StaticEncounterCountFitsSave);
STATIC_ASSERT(STATIC_ENC_BITS_PER_ID == 2, StaticEncounterTwoBitsPerId);
// The staticenc_bit script macro (asm/macros/event.inc) hardcodes these.
STATIC_ASSERT(STATIC_ENC_BIT_DEFEATED == 0 && STATIC_ENC_BIT_CAUGHT == 1 && STATIC_ENC_BIT_RECEIVED == 1, StaticEncounterBitsMatchMacros);

#define BYTE_INDEX(id)       ((id) / 4)
#define BIT_MASK(id, bit)    (1 << (((id) % 4) * STATIC_ENC_BITS_PER_ID + (bit)))
// The DEFEATED bit of all four IDs in a byte.
#define ALL_DEFEATED_MASK    ((1 << (0 + STATIC_ENC_BIT_DEFEATED)) \
                            | (1 << (2 + STATIC_ENC_BIT_DEFEATED)) \
                            | (1 << (4 + STATIC_ENC_BIT_DEFEATED)) \
                            | (1 << (6 + STATIC_ENC_BIT_DEFEATED)))

static inline bool32 IsValid(u32 id, u32 bit)
{
    return id < STATIC_ENC_MAX && bit < STATIC_ENC_BITS_PER_ID;
}

bool32 GetStaticEncounterBit(u32 id, u32 bit)
{
    if (!IsValid(id, bit))
        return FALSE;
    return (gSaveBlock3Ptr->staticEncounterFlags[BYTE_INDEX(id)] & BIT_MASK(id, bit)) != 0;
}

void SetStaticEncounterBit(u32 id, u32 bit)
{
    if (IsValid(id, bit))
        gSaveBlock3Ptr->staticEncounterFlags[BYTE_INDEX(id)] |= BIT_MASK(id, bit);
}

void ClearStaticEncounterBit(u32 id, u32 bit)
{
    if (IsValid(id, bit))
        gSaveBlock3Ptr->staticEncounterFlags[BYTE_INDEX(id)] &= ~BIT_MASK(id, bit);
}

bool32 IsStaticEncounterDefeated(u32 id) { return GetStaticEncounterBit(id, STATIC_ENC_BIT_DEFEATED); }
bool32 IsStaticEncounterCaught(u32 id)   { return GetStaticEncounterBit(id, STATIC_ENC_BIT_CAUGHT); }
bool32 IsGiftReceived(u32 id)            { return GetStaticEncounterBit(id, STATIC_ENC_BIT_RECEIVED); }
void SetStaticEncounterDefeated(u32 id)   { SetStaticEncounterBit(id, STATIC_ENC_BIT_DEFEATED); }
void SetStaticEncounterCaught(u32 id)     { SetStaticEncounterBit(id, STATIC_ENC_BIT_CAUGHT); }
void SetGiftReceived(u32 id)              { SetStaticEncounterBit(id, STATIC_ENC_BIT_RECEIVED); }
void ClearStaticEncounterDefeated(u32 id) { ClearStaticEncounterBit(id, STATIC_ENC_BIT_DEFEATED); }
void ClearStaticEncounterCaught(u32 id)   { ClearStaticEncounterBit(id, STATIC_ENC_BIT_CAUGHT); }
void ClearGiftReceived(u32 id)            { ClearStaticEncounterBit(id, STATIC_ENC_BIT_RECEIVED); }

void ClearAllStaticEncounterDefeated(void)
{
    for (u32 i = 0; i < ARRAY_COUNT(gSaveBlock3Ptr->staticEncounterFlags); i++)
        gSaveBlock3Ptr->staticEncounterFlags[i] &= ~ALL_DEFEATED_MASK;
}

void ResetStaticEncounters(void)
{
    memset(gSaveBlock3Ptr->staticEncounterFlags, 0, sizeof(gSaveBlock3Ptr->staticEncounterFlags));
}

// ---- Script commands (asm/macros/event.inc) ----

// checkstaticenc id, bit: VAR_RESULT = TRUE if the bit is set. 'id' may be a var.
bool8 ScrCmd_checkstaticenc(struct ScriptContext *ctx)
{
    u32 id = VarGet(ScriptReadHalfword(ctx));
    u32 bit = ScriptReadByte(ctx);

    Script_RequestEffects(SCREFF_V1);
    gSpecialVar_Result = GetStaticEncounterBit(id, bit);
    return FALSE;
}

// setstaticenc id, bit
bool8 ScrCmd_setstaticenc(struct ScriptContext *ctx)
{
    u32 id = VarGet(ScriptReadHalfword(ctx));
    u32 bit = ScriptReadByte(ctx);

    Script_RequestEffects(SCREFF_V1 | SCREFF_SAVE);
    SetStaticEncounterBit(id, bit);
    return FALSE;
}

// clearstaticenc id, bit
bool8 ScrCmd_clearstaticenc(struct ScriptContext *ctx)
{
    u32 id = VarGet(ScriptReadHalfword(ctx));
    u32 bit = ScriptReadByte(ctx);

    Script_RequestEffects(SCREFF_V1 | SCREFF_SAVE);
    ClearStaticEncounterBit(id, bit);
    return FALSE;
}

// clearallstaticencdefeated
bool8 ScrCmd_clearallstaticencdefeated(struct ScriptContext *ctx)
{
    Script_RequestEffects(SCREFF_V1 | SCREFF_SAVE);
    ClearAllStaticEncounterDefeated();
    return FALSE;
}

// setupstaticenc id, hideFlag, gateFlag: for a map's ON_TRANSITION script.
// Sets hideFlag (the static's object flag) unless the static should be there:
// gateFlag set (0 = no gate), not caught and not knocked out.
bool8 ScrCmd_setupstaticenc(struct ScriptContext *ctx)
{
    u32 id = VarGet(ScriptReadHalfword(ctx));
    u32 hideFlag = ScriptReadHalfword(ctx);
    u32 gateFlag = ScriptReadHalfword(ctx);

    Script_RequestEffects(SCREFF_V1 | SCREFF_SAVE);
    if ((gateFlag == 0 || FlagGet(gateFlag))
     && !IsStaticEncounterCaught(id)
     && !IsStaticEncounterDefeated(id))
        FlagClear(hideFlag);
    else
        FlagSet(hideFlag);
    return FALSE;
}
