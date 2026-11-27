#ifndef GUARD_CONSTANTS_STATIC_ENCOUNTERS_H
#define GUARD_CONSTANTS_STATIC_ENCOUNTERS_H

// IDs of the hack's single encounters: static legendaries and gift Pokémon.
// Their state lives in gSaveBlock3Ptr->staticEncounterFlags (2 bits per ID) instead of
// event flags, so adding an encounter costs no FLAG_UNUSED slot:
//   bit STATIC_ENC_BIT_DEFEATED: knocked out, back after the next Hall of Fame
//                                (ClearAllStaticEncounterDefeated)
//   bit STATIC_ENC_BIT_CAUGHT:   caught, gone for good
//   bit STATIC_ENC_BIT_RECEIVED: gift received (the same permanent bit as CAUGHT)
// Accessors: src/static_encounters.c. Script macros: checkstaticenc, setstaticenc,
// clearstaticenc, setupstaticenc, staticencounter, givegiftmon (asm/macros/event.inc).
// Shared scripts: data/scripts/hack_statics.inc.
//
// These are #defines rather than an enum because the event scripts use them too.
// To add an encounter, take the next number and bump STATIC_ENC_COUNT. Never renumber
// existing IDs once a save exists that uses them.
// The vanilla statics (Regirock, Kyogre, Mew, Lugia, ...) keep their vanilla flags.

// Static legendaries
#define STATIC_ENC_ARTICUNO      0
#define STATIC_ENC_ZAPDOS        1
#define STATIC_ENC_MOLTRES       2
#define STATIC_ENC_LATIAS        3
#define STATIC_ENC_LATIOS        4
#define STATIC_ENC_REGIGIGAS     5
#define STATIC_ENC_CRESSELIA     6
#define STATIC_ENC_TAPU_KOKO     7
#define STATIC_ENC_TAPU_LELE     8
#define STATIC_ENC_TAPU_BULU     9
#define STATIC_ENC_TAPU_FINI     10
#define STATIC_ENC_REGIELEKI     11
#define STATIC_ENC_REGIDRAGO     12
#define STATIC_ENC_KYUREM        13
#define STATIC_ENC_TERRAKION     14
#define STATIC_ENC_COBALION      15
#define STATIC_ENC_WO_CHIEN      16
#define STATIC_ENC_TING_LU       17
#define STATIC_ENC_CHIEN_PAO     18
#define STATIC_ENC_CHI_YU        19
#define STATIC_ENC_OKIDOGI       20
#define STATIC_ENC_MUNKIDORI     21
#define STATIC_ENC_FEZANDIPITI   22

// Gift Pokémon (only the RECEIVED bit is used)
#define GIFT_TYPE_NULL           23
#define GIFT_POIPOLE             24
#define GIFT_KUBFU               25
#define GIFT_COSMOG              26

// Static legendaries, continued
#define STATIC_ENC_GOUGING_FIRE  27
#define STATIC_ENC_ZYGARDE       28
#define STATIC_ENC_MEWTWO        29
#define STATIC_ENC_LANDORUS      30
#define STATIC_ENC_ENAMORUS      31
#define STATIC_ENC_ZEKROM        32
#define STATIC_ENC_MIRAIDON      33
#define STATIC_ENC_RESHIRAM      34
#define STATIC_ENC_XERNEAS       35
#define STATIC_ENC_YVELTAL       36
#define STATIC_ENC_VOLCANION     37

#define STATIC_ENC_COUNT         38

// Capacity reserved in the save: the one constant to raise if the encounters ever
// outgrow it (in steps of 4 IDs = 1 byte). 128 IDs = 32 bytes of SaveBlock3; the plan
// is about 95 encounters. src/static_encounters.c asserts STATIC_ENC_COUNT fits, and
// the SaveBlock3 static assert in src/save.c checks the save still fits.
#define STATIC_ENC_MAX           128

#define STATIC_ENC_BITS_PER_ID   2
#define STATIC_ENC_FLAGS_BYTES   ((STATIC_ENC_MAX * STATIC_ENC_BITS_PER_ID + 7) / 8)

#define STATIC_ENC_BIT_DEFEATED  0
#define STATIC_ENC_BIT_CAUGHT    1
#define STATIC_ENC_BIT_RECEIVED  STATIC_ENC_BIT_CAUGHT

#endif // GUARD_CONSTANTS_STATIC_ENCOUNTERS_H
