// Species base stat and ability overrides for Custom data mode (ported from R.O.W.E.).
//
// Applied by GetSpeciesBaseHP/.../GetSpeciesBaseSpeed (and so GetSpeciesBaseStat,
// stat calculation, Pokédex, Battle Dome, AI, ...) and by GetSpeciesAbility
// (GetAbilityBySpecies, summary, trainer parties, ...) in src/pokemon.c, only
// when IsCustomDataMode() is TRUE. Vanilla mode always uses gSpeciesInfo.
//
// One entry per species; leave a field out (or 0 / ABILITY_NONE) to keep the
// vanilla value. abilities[0] = slot 1, abilities[1] = slot 2, abilities[2] = hidden.
// Comments show vanilla (current gSpeciesInfo) -> custom.
//
// Only R.O.W.E.'s own edits are listed: values were diffed against the
// expansion revision R.O.W.E. was built on (10f4b48215, 2020-12-31), so later
// upstream changes stay vanilla. Abilities that only exist in R.O.W.E. were
// not ported, except Striker (ABILITY_STRIKER). R.O.W.E.'s "Blademaster" is
// ABILITY_SHARPNESS.

const struct SpeciesInfoOverride gCustomSpeciesInfo[NUM_SPECIES + 1] =
{
    [SPECIES_BULBASAUR] = { .abilities[1] = ABILITY_CHLOROPHYLL }, // Slot 2: None->Chlorophyll
    [SPECIES_IVYSAUR] = { .abilities[1] = ABILITY_CHLOROPHYLL }, // Slot 2: None->Chlorophyll
    [SPECIES_VENUSAUR] = { .abilities[1] = ABILITY_CHLOROPHYLL }, // Slot 2: None->Chlorophyll
    [SPECIES_CHARMANDER] = { .abilities[1] = ABILITY_SOLAR_POWER }, // Slot 2: None->Solar Power
    [SPECIES_CHARMELEON] = { .abilities[1] = ABILITY_SOLAR_POWER }, // Slot 2: None->Solar Power
    [SPECIES_CHARIZARD] = { .abilities[1] = ABILITY_SOLAR_POWER }, // Slot 2: None->Solar Power
    [SPECIES_SQUIRTLE] = { .abilities[1] = ABILITY_RAIN_DISH }, // Slot 2: None->Rain Dish
    [SPECIES_WARTORTLE] = { .abilities[1] = ABILITY_RAIN_DISH }, // Slot 2: None->Rain Dish
    [SPECIES_BLASTOISE] = { .abilities[1] = ABILITY_MEGA_LAUNCHER }, // Slot 2: None->Mega Launcher
    [SPECIES_CATERPIE] = { .abilities[1] = ABILITY_RUN_AWAY }, // Slot 2: None->Run Away
    [SPECIES_BUTTERFREE] = { .baseSpeed = 80, .baseSpAttack = 95, .abilities[1] = ABILITY_TINTED_LENS }, // Spe 70->80, SpA 90->95, Slot 2: None->Tinted Lens
    [SPECIES_BEEDRILL] = { .abilities[1] = ABILITY_ANGER_POINT }, // Slot 2: None->Anger Point
    [SPECIES_PIDGEY] = { .baseAttack = 35, .baseSpAttack = 45 }, // Atk 45->35, SpA 35->45
    [SPECIES_PIDGEOTTO] = { .baseAttack = 45, .baseSpAttack = 65 }, // Atk 60->45, SpA 50->65
    [SPECIES_PIDGEOT] = { .baseAttack = 60, .baseSpAttack = 110 }, // Atk 80->60, SpA 70->110
    [SPECIES_RATICATE] = { .baseHP = 60, .baseAttack = 95, .baseSpeed = 100, .abilities[0] = ABILITY_STRONG_JAW }, // HP 55->60, Atk 81->95, Spe 97->100, Slot 1: Run Away->Strong Jaw
    [SPECIES_RATICATE_ALOLA] = { .abilities[1] = ABILITY_STRONG_JAW }, // Slot 2: Hustle->Strong Jaw
    [SPECIES_SPEAROW] = { .abilities[1] = ABILITY_BIG_PECKS }, // Slot 2: None->Big Pecks
    [SPECIES_FEAROW] = { .baseAttack = 100, .baseSpeed = 115, .abilities[1] = ABILITY_TECHNICIAN }, // Atk 90->100, Spe 100->115, Slot 2: None->Technician
    [SPECIES_ARBOK] = { .baseHP = 75, .baseDefense = 75, .abilities[2] = ABILITY_STRONG_JAW }, // HP 60->75, Def 69->75, Hidden: Unnerve->Strong Jaw
    [SPECIES_PIKACHU] = { .baseAttack = 50, .baseSpAttack = 55, .abilities[1] = ABILITY_LIGHTNING_ROD }, // Atk 55->50, SpA 50->55, Slot 2: None->Lightning Rod
    [SPECIES_PIKACHU_PARTNER] = { .baseHP = 75, .baseAttack = 85, .baseDefense = 80, .baseSpeed = 120, .baseSpAttack = 110, .baseSpDefense = 80 }, // HP 35->75, Atk 55->85, Def 40->80, Spe 90->120, SpA 50->110, SpD 50->80
    [SPECIES_RAICHU] = { .baseHP = 70, .baseAttack = 100, .baseSpAttack = 110, .abilities[1] = ABILITY_LIGHTNING_ROD }, // HP 60->70, Atk 90->100, SpA 90->110, Slot 2: None->Lightning Rod
    [SPECIES_RAICHU_ALOLA] = { .baseSpAttack = 110 }, // SpA 95->110
    [SPECIES_SANDSHREW_ALOLA] = { .abilities[0] = ABILITY_SLUSH_RUSH, .abilities[1] = ABILITY_ICE_BODY, .abilities[2] = ABILITY_SNOW_CLOAK }, // Slot 1: Snow Cloak->Slush Rush, Slot 2: None->Ice Body, Hidden: Slush Rush->Snow Cloak
    [SPECIES_SANDSLASH] = { .baseAttack = 110, .baseDefense = 120, .baseSpAttack = 25 }, // Atk 100->110, Def 110->120, SpA 45->25
    [SPECIES_SANDSLASH_ALOLA] = { .baseAttack = 110, .abilities[0] = ABILITY_SLUSH_RUSH, .abilities[2] = ABILITY_ICE_SCALES }, // Atk 100->110, Slot 1: Snow Cloak->Slush Rush, Hidden: Slush Rush->Ice Scales
    [SPECIES_NIDOKING] = { .baseAttack = 92, .baseSpAttack = 95 }, // Atk 102->92, SpA 85->95
    [SPECIES_CLEFABLE] = { .baseAttack = 60, .baseDefense = 83 }, // Atk 70->60, Def 73->83
    [SPECIES_WIGGLYTUFF] = { .abilities[0] = ABILITY_SHEER_FORCE }, // Slot 1: Cute Charm->Sheer Force
    [SPECIES_ZUBAT] = { .abilities[1] = ABILITY_CORROSION }, // Slot 2: None->Corrosion
    [SPECIES_GOLBAT] = { .abilities[1] = ABILITY_CORROSION }, // Slot 2: None->Corrosion
    [SPECIES_PARASECT] = { .baseHP = 80, .baseAttack = 110 }, // HP 60->80, Atk 95->110
    [SPECIES_VENOMOTH] = { .baseDefense = 65 }, // Def 60->65
    [SPECIES_MEOWTH] = { .baseHP = 50, .baseAttack = 55 }, // HP 40->50, Atk 45->55
    [SPECIES_PERSIAN] = { .baseHP = 70, .baseAttack = 80, .baseSpeed = 120, .baseSpAttack = 60 }, // HP 65->70, Atk 70->80, Spe 115->120, SpA 65->60
    [SPECIES_GOLDUCK] = { .baseAttack = 78, .baseDefense = 82, .baseSpeed = 100, .baseSpAttack = 100 }, // Atk 82->78, Def 78->82, Spe 85->100, SpA 95->100
    [SPECIES_VICTREEBEL] = { .baseDefense = 70, .baseSpDefense = 75 }, // Def 65->70, SpD 70->75
    [SPECIES_TENTACRUEL] = { .baseAttack = 60, .baseSpAttack = 90 }, // Atk 70->60, SpA 80->90
    [SPECIES_GOLEM_ALOLA] = { .abilities[1] = ABILITY_ROCK_HEAD }, // Slot 2: Sturdy->Rock Head
    [SPECIES_RAPIDASH] = { .baseSpeed = 125, .baseSpAttack = 60, .abilities[0] = ABILITY_RECKLESS }, // Spe 105->125, SpA 80->60, Slot 1: Run Away->Reckless
    [SPECIES_FARFETCHD] = { .baseHP = 75, .baseAttack = 110, .baseDefense = 70, .baseSpeed = 100, .baseSpDefense = 77, .abilities[0] = ABILITY_DEFIANT, .abilities[1] = ABILITY_JUSTIFIED, .abilities[2] = ABILITY_SHARPNESS }, // HP 52->75, Atk 90->110, Def 55->70, Spe 60->100, SpD 62->77, Slot 1: Keen Eye->Defiant, Slot 2: Inner Focus->Justified, Hidden: Defiant->Sharpness
    [SPECIES_FARFETCHD_GALAR] = { .abilities[1] = ABILITY_JUSTIFIED }, // Slot 2: None->Justified
    [SPECIES_DODRIO] = { .abilities[0] = ABILITY_ROCK_HEAD }, // Slot 1: Run Away->Rock Head
    [SPECIES_SEEL] = { .abilities[1] = ABILITY_ICE_BODY, .abilities[2] = ABILITY_HYDRATION }, // Slot 2: Hydration->Ice Body, Hidden: Ice Body->Hydration
    [SPECIES_DEWGONG] = { .baseAttack = 50, .baseSpAttack = 90, .abilities[1] = ABILITY_ICE_BODY, .abilities[2] = ABILITY_ICE_SCALES }, // Atk 70->50, SpA 70->90, Slot 2: Hydration->Ice Body, Hidden: Ice Body->Ice Scales
    [SPECIES_MUK] = { .abilities[0] = ABILITY_REGENERATOR, .abilities[1] = ABILITY_GOOEY }, // Slot 1: Stench->Regenerator, Slot 2: Sticky Hold->Gooey
    [SPECIES_GASTLY] = { .abilities[0] = ABILITY_CURSED_BODY, .abilities[1] = ABILITY_LEVITATE }, // Slot 1: Levitate->Cursed Body, Slot 2: None->Levitate
    [SPECIES_HAUNTER] = { .abilities[0] = ABILITY_CURSED_BODY, .abilities[1] = ABILITY_LEVITATE }, // Slot 1: Levitate->Cursed Body, Slot 2: None->Levitate
    [SPECIES_GENGAR] = { .abilities[1] = ABILITY_LEVITATE }, // Slot 2: None->Levitate
    [SPECIES_ONIX] = { .abilities[2] = ABILITY_SAND_SPIT }, // Hidden: Weak Armor->Sand Spit
    [SPECIES_HYPNO] = { .abilities[2] = ABILITY_BAD_DREAMS }, // Hidden: Inner Focus->Bad Dreams
    [SPECIES_VOLTORB] = { .abilities[2] = ABILITY_GALVANIZE }, // Hidden: Aftermath->Galvanize
    [SPECIES_ELECTRODE] = { .baseAttack = 55, .abilities[2] = ABILITY_GALVANIZE }, // Atk 50->55, Hidden: Aftermath->Galvanize
    [SPECIES_HITMONLEE] = { .abilities[2] = ABILITY_STRIKER }, // Hidden: Unburden->Striker
    [SPECIES_HITMONCHAN] = { .baseAttack = 115 }, // Atk 105->115
    [SPECIES_WEEZING_GALAR] = { .abilities[0] = ABILITY_WHITE_SMOKE }, // Slot 1: Levitate->White Smoke
    [SPECIES_KANGASKHAN] = { .abilities[0] = ABILITY_INNER_FOCUS, .abilities[2] = ABILITY_PARENTAL_BOND }, // Slot 1: Early Bird->Inner Focus, Hidden: Inner Focus->Parental Bond
    [SPECIES_STARYU] = { .baseAttack = 40, .baseSpAttack = 75 }, // Atk 45->40, SpA 70->75
    [SPECIES_STARMIE] = { .baseAttack = 70, .baseSpAttack = 105 }, // Atk 75->70, SpA 100->105
    [SPECIES_JYNX] = { .baseDefense = 50, .baseSpeed = 100 }, // Def 35->50, Spe 95->100
    [SPECIES_TAUROS] = { .baseSpAttack = 70 }, // SpA 40->70
    [SPECIES_MAGIKARP] = { .abilities[1] = ABILITY_RATTLED }, // Slot 2: None->Rattled
    [SPECIES_GYARADOS] = { .abilities[1] = ABILITY_MOXIE }, // Slot 2: None->Moxie
    [SPECIES_DITTO] = { .baseHP = 70 }, // HP 48->70
    [SPECIES_JOLTEON] = { .baseAttack = 60, .baseDefense = 65 }, // Atk 65->60, Def 60->65
    [SPECIES_FLAREON] = { .baseSpeed = 95, .baseSpAttack = 65, .baseSpDefense = 100 }, // Spe 65->95, SpA 95->65, SpD 110->100
    [SPECIES_KABUTOPS] = { .abilities[2] = ABILITY_SHARPNESS }, // Hidden: Weak Armor->Sharpness
    [SPECIES_ARTICUNO] = { .baseAttack = 70, .baseSpeed = 105, .abilities[1] = ABILITY_SNOW_CLOAK, .abilities[2] = ABILITY_SHIELD_DUST }, // Atk 85->70, Spe 85->105, Slot 2: None->Snow Cloak, Hidden: Snow Cloak->Shield Dust
    [SPECIES_ZAPDOS] = { .abilities[1] = ABILITY_LIGHTNING_ROD }, // Slot 2: None->Lightning Rod
    [SPECIES_MOLTRES] = { .baseAttack = 80, .baseDefense = 95, .baseSpeed = 95, .baseSpDefense = 95, .abilities[1] = ABILITY_FLAME_BODY }, // Atk 100->80, Def 90->95, Spe 90->95, SpD 85->95, Slot 2: None->Flame Body
    [SPECIES_CHIKORITA] = { .abilities[1] = ABILITY_LEAF_GUARD }, // Slot 2: None->Leaf Guard
    [SPECIES_BAYLEEF] = { .abilities[1] = ABILITY_LEAF_GUARD }, // Slot 2: None->Leaf Guard
    [SPECIES_MEGANIUM] = { .abilities[1] = ABILITY_TRIAGE, .abilities[2] = ABILITY_TRIAGE }, // Slot 2: None->Triage, Hidden: Leaf Guard->Triage
    [SPECIES_CYNDAQUIL] = { .abilities[1] = ABILITY_FLASH_FIRE }, // Slot 2: None->Flash Fire
    [SPECIES_QUILAVA] = { .abilities[1] = ABILITY_FLASH_FIRE }, // Slot 2: None->Flash Fire
    [SPECIES_TYPHLOSION] = { .abilities[1] = ABILITY_FLASH_FIRE, .abilities[2] = ABILITY_FRISK }, // Slot 2: None->Flash Fire, Hidden: Flash Fire->Frisk
    [SPECIES_TOTODILE] = { .abilities[1] = ABILITY_SHEER_FORCE }, // Slot 2: None->Sheer Force
    [SPECIES_CROCONAW] = { .abilities[1] = ABILITY_SHEER_FORCE }, // Slot 2: None->Sheer Force
    [SPECIES_FERALIGATR] = { .abilities[1] = ABILITY_SHEER_FORCE }, // Slot 2: None->Sheer Force
    [SPECIES_FURRET] = { .abilities[2] = ABILITY_ADAPTABILITY }, // Hidden: Frisk->Adaptability
    [SPECIES_NOCTOWL] = { .baseHP = 110, .baseSpeed = 80, .baseSpAttack = 90, .baseSpDefense = 100 }, // HP 100->110, Spe 70->80, SpA 86->90, SpD 96->100
    [SPECIES_LEDYBA] = { .baseHP = 45, .baseAttack = 50, .baseSpAttack = 30, .baseSpDefense = 65, .abilities[1] = ABILITY_SKILL_LINK }, // HP 40->45, Atk 20->50, SpA 40->30, SpD 80->65, Slot 2: Early Bird->Skill Link
    [SPECIES_LEDIAN] = { .baseHP = 60, .baseAttack = 95, .baseSpAttack = 35, .abilities[1] = ABILITY_SKILL_LINK }, // HP 55->60, Atk 35->95, SpA 55->35, Slot 2: Early Bird->Skill Link
    [SPECIES_SPINARAK] = { .baseHP = 50, .baseSpeed = 45 }, // HP 40->50, Spe 30->45
    [SPECIES_ARIADOS] = { .baseAttack = 100, .baseSpeed = 70, .baseSpAttack = 45, .abilities[1] = ABILITY_NO_GUARD }, // Atk 90->100, Spe 40->70, SpA 60->45, Slot 2: Insomnia->No Guard
    [SPECIES_CROBAT] = { .baseSpAttack = 90, .abilities[1] = ABILITY_CORROSION }, // SpA 70->90, Slot 2: None->Corrosion
    [SPECIES_LANTURN] = { .baseAttack = 50, .baseDefense = 65, .baseSpeed = 70, .baseSpAttack = 90 }, // Atk 58->50, Def 58->65, Spe 67->70, SpA 76->90
    [SPECIES_PICHU] = { .abilities[1] = ABILITY_LIGHTNING_ROD }, // Slot 2: None->Lightning Rod
    [SPECIES_XATU] = { .baseSpeed = 105, .baseSpAttack = 105 }, // Spe 95->105, SpA 95->105
    [SPECIES_MAREEP] = { .abilities[1] = ABILITY_FLUFFY }, // Slot 2: None->Fluffy
    [SPECIES_FLAAFFY] = { .abilities[1] = ABILITY_ILLUMINATE }, // Slot 2: None->Illuminate
    [SPECIES_AMPHAROS] = { .abilities[1] = ABILITY_ILLUMINATE }, // Slot 2: None->Illuminate
    [SPECIES_BELLOSSOM] = { .baseHP = 85, .baseAttack = 70, .baseSpAttack = 100, .baseSpDefense = 90, .abilities[1] = ABILITY_HEALER, .abilities[2] = ABILITY_DANCER }, // HP 75->85, Atk 80->70, SpA 90->100, SpD 100->90, Slot 2: None->Healer, Hidden: Healer->Dancer
    [SPECIES_SUDOWOODO] = { .baseHP = 90, .abilities[2] = ABILITY_PRANKSTER }, // HP 70->90, Hidden: Rattled->Prankster
    [SPECIES_POLITOED] = { .baseSpAttack = 100, .abilities[1] = ABILITY_DRIZZLE }, // SpA 90->100, Slot 2: Damp->Drizzle
    [SPECIES_JUMPLUFF] = { .baseAttack = 85, .baseSpAttack = 35, .abilities[2] = ABILITY_AERILATE }, // Atk 55->85, SpA 55->35, Hidden: Infiltrator->Aerilate
    [SPECIES_SUNKERN] = { .baseHP = 40, .baseDefense = 35, .baseSpAttack = 50, .baseSpDefense = 70 }, // HP 30->40, Def 30->35, SpA 30->50, SpD 30->70
    [SPECIES_SUNFLORA] = { .baseHP = 95, .baseDefense = 85, .baseSpeed = 65, .baseSpAttack = 115, .abilities[2] = ABILITY_FLOWER_GIFT }, // HP 75->95, Def 55->85, Spe 30->65, SpA 105->115, Hidden: Early Bird->Flower Gift
    [SPECIES_QUAGSIRE] = { .baseHP = 100, .baseDefense = 90 }, // HP 95->100, Def 85->90
    [SPECIES_MISDREAVUS] = { .abilities[0] = ABILITY_CURSED_BODY, .abilities[1] = ABILITY_PIXILATE }, // Slot 1: Levitate->Cursed Body, Slot 2: None->Pixilate
    [SPECIES_UNOWN] = { .baseHP = 80, .baseAttack = 70, .baseDefense = 80, .baseSpeed = 95, .baseSpAttack = 95, .baseSpDefense = 80, .abilities[0] = ABILITY_PSYCHIC_SURGE }, // HP 48->80, Atk 72->70, Def 48->80, Spe 48->95, SpA 72->95, SpD 48->80, Slot 1: Levitate->Psychic Surge
    [SPECIES_UNOWN_B] = { .abilities[0] = ABILITY_PSYCHIC_SURGE }, // Slot 1: Levitate->Psychic Surge
    [SPECIES_UNOWN_C] = { .abilities[0] = ABILITY_PSYCHIC_SURGE }, // Slot 1: Levitate->Psychic Surge
    [SPECIES_UNOWN_D] = { .abilities[0] = ABILITY_PSYCHIC_SURGE }, // Slot 1: Levitate->Psychic Surge
    [SPECIES_UNOWN_E] = { .abilities[0] = ABILITY_PSYCHIC_SURGE }, // Slot 1: Levitate->Psychic Surge
    [SPECIES_UNOWN_F] = { .abilities[0] = ABILITY_PSYCHIC_SURGE }, // Slot 1: Levitate->Psychic Surge
    [SPECIES_UNOWN_G] = { .abilities[0] = ABILITY_PSYCHIC_SURGE }, // Slot 1: Levitate->Psychic Surge
    [SPECIES_UNOWN_H] = { .abilities[0] = ABILITY_PSYCHIC_SURGE }, // Slot 1: Levitate->Psychic Surge
    [SPECIES_UNOWN_I] = { .abilities[0] = ABILITY_PSYCHIC_SURGE }, // Slot 1: Levitate->Psychic Surge
    [SPECIES_UNOWN_J] = { .abilities[0] = ABILITY_PSYCHIC_SURGE }, // Slot 1: Levitate->Psychic Surge
    [SPECIES_UNOWN_K] = { .abilities[0] = ABILITY_PSYCHIC_SURGE }, // Slot 1: Levitate->Psychic Surge
    [SPECIES_UNOWN_L] = { .abilities[0] = ABILITY_PSYCHIC_SURGE }, // Slot 1: Levitate->Psychic Surge
    [SPECIES_UNOWN_M] = { .abilities[0] = ABILITY_PSYCHIC_SURGE }, // Slot 1: Levitate->Psychic Surge
    [SPECIES_UNOWN_N] = { .abilities[0] = ABILITY_PSYCHIC_SURGE }, // Slot 1: Levitate->Psychic Surge
    [SPECIES_UNOWN_O] = { .abilities[0] = ABILITY_PSYCHIC_SURGE }, // Slot 1: Levitate->Psychic Surge
    [SPECIES_UNOWN_P] = { .abilities[0] = ABILITY_PSYCHIC_SURGE }, // Slot 1: Levitate->Psychic Surge
    [SPECIES_UNOWN_Q] = { .abilities[0] = ABILITY_PSYCHIC_SURGE }, // Slot 1: Levitate->Psychic Surge
    [SPECIES_UNOWN_R] = { .abilities[0] = ABILITY_PSYCHIC_SURGE }, // Slot 1: Levitate->Psychic Surge
    [SPECIES_UNOWN_S] = { .abilities[0] = ABILITY_PSYCHIC_SURGE }, // Slot 1: Levitate->Psychic Surge
    [SPECIES_UNOWN_T] = { .abilities[0] = ABILITY_PSYCHIC_SURGE }, // Slot 1: Levitate->Psychic Surge
    [SPECIES_UNOWN_U] = { .abilities[0] = ABILITY_PSYCHIC_SURGE }, // Slot 1: Levitate->Psychic Surge
    [SPECIES_UNOWN_V] = { .abilities[0] = ABILITY_PSYCHIC_SURGE }, // Slot 1: Levitate->Psychic Surge
    [SPECIES_UNOWN_W] = { .abilities[0] = ABILITY_PSYCHIC_SURGE }, // Slot 1: Levitate->Psychic Surge
    [SPECIES_UNOWN_X] = { .abilities[0] = ABILITY_PSYCHIC_SURGE }, // Slot 1: Levitate->Psychic Surge
    [SPECIES_UNOWN_Y] = { .abilities[0] = ABILITY_PSYCHIC_SURGE }, // Slot 1: Levitate->Psychic Surge
    [SPECIES_UNOWN_Z] = { .abilities[0] = ABILITY_PSYCHIC_SURGE }, // Slot 1: Levitate->Psychic Surge
    [SPECIES_UNOWN_EXCLAMATION] = { .abilities[0] = ABILITY_PSYCHIC_SURGE }, // Slot 1: Levitate->Psychic Surge
    [SPECIES_UNOWN_QUESTION] = { .abilities[0] = ABILITY_PSYCHIC_SURGE }, // Slot 1: Levitate->Psychic Surge
    [SPECIES_GIRAFARIG] = { .abilities[0] = ABILITY_SAP_SIPPER }, // Slot 1: Inner Focus->Sap Sipper
    [SPECIES_DUNSPARCE] = { .baseAttack = 80, .baseDefense = 80, .baseSpeed = 65, .baseSpDefense = 75 }, // Atk 70->80, Def 70->80, Spe 45->65, SpD 65->75
    [SPECIES_STEELIX] = { .abilities[1] = ABILITY_SHEER_FORCE, .abilities[2] = ABILITY_SAND_SPIT }, // Slot 2: Sturdy->Sheer Force, Hidden: Sheer Force->Sand Spit
    [SPECIES_GRANBULL] = { .abilities[1] = ABILITY_ANGER_POINT, .abilities[2] = ABILITY_STRONG_JAW }, // Slot 2: Quick Feet->Anger Point, Hidden: Rattled->Strong Jaw
    [SPECIES_QWILFISH] = { .baseAttack = 105, .abilities[0] = ABILITY_POISON_TOUCH }, // Atk 95->105, Slot 1: Poison Point->Poison Touch
    [SPECIES_SHUCKLE] = { .abilities[1] = ABILITY_SOLID_ROCK }, // Slot 2: Gluttony->Solid Rock
    [SPECIES_HERACROSS] = { .abilities[0] = ABILITY_MOXIE, .abilities[2] = ABILITY_SWARM }, // Slot 1: Swarm->Moxie, Hidden: Moxie->Swarm
    [SPECIES_SNEASEL] = { .abilities[1] = ABILITY_TECHNICIAN }, // Slot 2: Keen Eye->Technician
    [SPECIES_SLUGMA] = { .baseHP = 50, .baseDefense = 60, .baseSpeed = 45, .baseSpDefense = 50 }, // HP 40->50, Def 40->60, Spe 20->45, SpD 40->50
    [SPECIES_MAGCARGO] = { .baseHP = 80, .baseAttack = 40, .baseDefense = 110, .baseSpeed = 60, .baseSpDefense = 100, .abilities[0] = ABILITY_SOLID_ROCK, .abilities[2] = ABILITY_SIMPLE }, // HP 60->80, Atk 50->40, Def 120->110, Spe 30->60, SpD 80->100, Slot 1: Magma Armor->Solid Rock, Hidden: Weak Armor->Simple
    [SPECIES_OCTILLERY] = { .abilities[0] = ABILITY_SKILL_LINK, .abilities[2] = ABILITY_MEGA_LAUNCHER }, // Slot 1: Suction Cups->Skill Link, Hidden: Moody->Mega Launcher
    [SPECIES_DELIBIRD] = { .baseAttack = 95, .baseSpeed = 95, .abilities[0] = ABILITY_REFRIGERATE, .abilities[2] = ABILITY_UNBURDEN }, // Atk 55->95, Spe 75->95, Slot 1: Vital Spirit->Refrigerate, Hidden: Insomnia->Unburden
    [SPECIES_MANTINE] = { .baseSpAttack = 90 }, // SpA 80->90
    [SPECIES_KINGDRA] = { .baseAttack = 100, .baseSpAttack = 100 }, // Atk 95->100, SpA 95->100
    [SPECIES_DONPHAN] = { .abilities[1] = ABILITY_SAND_VEIL, .abilities[2] = ABILITY_TECHNICIAN }, // Slot 2: None->Sand Veil, Hidden: Sand Veil->Technician
    [SPECIES_STANTLER] = { .abilities[1] = ABILITY_RECKLESS }, // Slot 2: Frisk->Reckless
    [SPECIES_MILTANK] = { .baseAttack = 90 }, // Atk 80->90
    [SPECIES_RAIKOU] = { .abilities[1] = ABILITY_VOLT_ABSORB }, // Slot 2: None->Volt Absorb
    [SPECIES_ENTEI] = { .abilities[1] = ABILITY_FLASH_FIRE }, // Slot 2: None->Flash Fire
    [SPECIES_SUICUNE] = { .abilities[1] = ABILITY_WATER_ABSORB }, // Slot 2: None->Water Absorb
    [SPECIES_TREECKO] = { .baseAttack = 65, .baseSpAttack = 45, .abilities[1] = ABILITY_UNBURDEN }, // Atk 45->65, SpA 65->45, Slot 2: None->Unburden
    [SPECIES_GROVYLE] = { .abilities[1] = ABILITY_LIGHTNING_ROD }, // Slot 2: None->Lightning Rod
    [SPECIES_SCEPTILE] = { .baseSpAttack = 110, .abilities[1] = ABILITY_LIGHTNING_ROD }, // SpA 105->110, Slot 2: None->Lightning Rod
    [SPECIES_MUDKIP] = { .baseAttack = 75, .baseSpAttack = 45, .abilities[1] = ABILITY_SWIFT_SWIM }, // Atk 70->75, SpA 50->45, Slot 2: None->Swift Swim
    [SPECIES_MARSHTOMP] = { .baseAttack = 90, .baseSpAttack = 55, .abilities[1] = ABILITY_SWIFT_SWIM }, // Atk 85->90, SpA 60->55, Slot 2: None->Swift Swim
    [SPECIES_SWAMPERT] = { .baseAttack = 120, .baseSpeed = 70, .baseSpAttack = 65, .abilities[1] = ABILITY_SWIFT_SWIM }, // Atk 110->120, Spe 60->70, SpA 85->65, Slot 2: None->Swift Swim
    [SPECIES_SWAMPERT_MEGA] = { .baseAttack = 160, .baseSpAttack = 85 }, // Atk 150->160, SpA 95->85
    [SPECIES_MIGHTYENA] = { .baseAttack = 110 }, // Atk 90->110
    [SPECIES_LINOONE] = { .baseHP = 80, .baseAttack = 100, .baseDefense = 65, .abilities[0] = ABILITY_SCRAPPY }, // HP 78->80, Atk 70->100, Def 61->65, Slot 1: Pickup->Scrappy
    [SPECIES_WURMPLE] = { .abilities[1] = ABILITY_RUN_AWAY, .abilities[2] = ABILITY_POISON_POINT }, // Slot 2: None->Run Away, Hidden: Run Away->Poison Point
    [SPECIES_BEAUTIFLY] = { .baseSpeed = 90, .baseSpAttack = 110, .abilities[1] = ABILITY_RIVALRY, .abilities[2] = ABILITY_HONEY_GATHER }, // Spe 65->90, SpA 100->110, Slot 2: None->Rivalry, Hidden: Rivalry->Honey Gather
    [SPECIES_DUSTOX] = { .baseDefense = 60, .baseSpeed = 95, .baseSpAttack = 95, .baseSpDefense = 60, .abilities[1] = ABILITY_COMPOUND_EYES, .abilities[2] = ABILITY_MERCILESS }, // Def 70->60, Spe 65->95, SpA 50->95, SpD 90->60, Slot 2: None->Compound Eyes, Hidden: Compound Eyes->Merciless
    [SPECIES_LUDICOLO] = { .baseSpeed = 90, .baseSpAttack = 100 }, // Spe 70->90, SpA 90->100
    [SPECIES_SHIFTRY] = { .baseAttack = 105, .baseSpAttack = 105 }, // Atk 100->105, SpA 90->105
    [SPECIES_TAILLOW] = { .baseAttack = 60, .baseSpAttack = 55 }, // Atk 55->60, SpA 30->55
    [SPECIES_SWELLOW] = { .baseAttack = 100, .baseSpAttack = 90 }, // Atk 85->100, SpA 75->90
    [SPECIES_WINGULL] = { .baseAttack = 25, .baseSpAttack = 60 }, // Atk 30->25, SpA 55->60
    [SPECIES_PELIPPER] = { .baseHP = 65, .baseAttack = 40, .baseDefense = 110, .baseSpAttack = 100, .baseSpDefense = 80 }, // HP 60->65, Atk 50->40, Def 100->110, SpA 95->100, SpD 70->80
    [SPECIES_KIRLIA] = { .baseAttack = 30, .baseDefense = 40 }, // Atk 35->30, Def 35->40
    [SPECIES_GARDEVOIR] = { .baseAttack = 60, .baseSpeed = 100 }, // Atk 65->60, Spe 80->100
    [SPECIES_GARDEVOIR_MEGA] = { .baseAttack = 60, .baseDefense = 90, .baseSpAttack = 175, .baseSpDefense = 140 }, // Atk 85->60, Def 65->90, SpA 165->175, SpD 135->140
    [SPECIES_SURSKIT] = { .abilities[1] = ABILITY_RAIN_DISH, .abilities[2] = ABILITY_WATER_VEIL }, // Slot 2: None->Rain Dish, Hidden: Rain Dish->Water Veil
    [SPECIES_MASQUERAIN] = { .baseDefense = 70, .baseSpeed = 100, .baseSpAttack = 120, .baseSpDefense = 110, .abilities[1] = ABILITY_KEEN_EYE, .abilities[2] = ABILITY_KEEN_EYE }, // Def 62->70, Spe 80->100, SpA 100->120, SpD 82->110, Slot 2: None->Keen Eye, Hidden: Unnerve->Keen Eye
    [SPECIES_NINJASK] = { .baseAttack = 100 }, // Atk 90->100
    [SPECIES_SHEDINJA] = { .baseAttack = 100, .baseSpeed = 70 }, // Atk 90->100, Spe 40->70
    [SPECIES_EXPLOUD] = { .baseSpeed = 75, .baseSpAttack = 110 }, // Spe 68->75, SpA 91->110
    [SPECIES_HARIYAMA] = { .baseDefense = 80, .baseSpDefense = 80 }, // Def 60->80, SpD 60->80
    [SPECIES_DELCATTY] = { .baseAttack = 95, .baseSpAttack = 65 }, // Atk 65->95, SpA 55->65
    [SPECIES_SABLEYE] = { .baseHP = 70, .baseDefense = 80, .baseSpDefense = 80 }, // HP 50->70, Def 75->80, SpD 65->80
    [SPECIES_SABLEYE_MEGA] = { .baseHP = 70 }, // HP 50->70
    [SPECIES_MAWILE] = { .baseSpeed = 75 }, // Spe 50->75
    [SPECIES_AGGRON] = { .baseHP = 85 }, // HP 70->85
    [SPECIES_MEDICHAM] = { .baseHP = 65, .baseAttack = 70, .baseSpAttack = 50 }, // HP 60->65, Atk 60->70, SpA 60->50
    [SPECIES_MEDICHAM_MEGA] = { .baseHP = 65, .baseAttack = 105, .baseSpAttack = 75 }, // HP 60->65, Atk 100->105, SpA 80->75
    [SPECIES_ELECTRIKE] = { .abilities[2] = ABILITY_INTIMIDATE }, // Hidden: Minus->Intimidate
    [SPECIES_MANECTRIC] = { .baseSpAttack = 125, .abilities[2] = ABILITY_INTIMIDATE }, // SpA 105->125, Hidden: Minus->Intimidate
    [SPECIES_PLUSLE] = { .baseSpeed = 101, .baseSpAttack = 95, .baseSpDefense = 85, .abilities[1] = ABILITY_LIGHTNING_ROD, .abilities[2] = ABILITY_BATTERY }, // Spe 95->101, SpA 85->95, SpD 75->85, Slot 2: None->Lightning Rod, Hidden: Lightning Rod->Battery
    [SPECIES_MINUN] = { .baseSpeed = 101, .baseSpAttack = 95, .abilities[1] = ABILITY_LIGHTNING_ROD, .abilities[2] = ABILITY_BATTERY }, // Spe 95->101, SpA 75->95, Slot 2: None->Lightning Rod, Hidden: Volt Absorb->Battery
    [SPECIES_VOLBEAT] = { .baseAttack = 50, .baseSpeed = 95, .baseSpAttack = 90 }, // Atk 73->50, Spe 85->95, SpA 47->90
    [SPECIES_ILLUMISE] = { .baseAttack = 50, .baseSpeed = 95, .baseSpAttack = 90 }, // Atk 47->50, Spe 85->95, SpA 73->90
    [SPECIES_GULPIN] = { .abilities[2] = ABILITY_GOOEY }, // Hidden: Gluttony->Gooey
    [SPECIES_SWALOT] = { .baseAttack = 90, .baseSpeed = 30, .baseSpAttack = 90, .abilities[2] = ABILITY_GOOEY }, // Atk 73->90, Spe 55->30, SpA 73->90, Hidden: Gluttony->Gooey
    [SPECIES_SHARPEDO] = { .abilities[1] = ABILITY_INTIMIDATE }, // Slot 2: None->Intimidate
    [SPECIES_WAILORD] = { .baseHP = 200, .baseAttack = 60, .baseSpAttack = 110 }, // HP 170->200, Atk 90->60, SpA 90->110
    [SPECIES_TORKOAL] = { .baseHP = 90, .baseDefense = 120, .baseSpeed = 10, .baseSpDefense = 90 }, // HP 70->90, Def 140->120, Spe 20->10, SpD 70->90
    [SPECIES_GRUMPIG] = { .baseSpeed = 40, .baseSpAttack = 110, .abilities[2] = ABILITY_OWN_TEMPO }, // Spe 80->40, SpA 90->110, Hidden: Gluttony->Own Tempo
    [SPECIES_SPINDA] = { .baseHP = 80, .baseAttack = 95, .baseSpeed = 85 }, // HP 60->80, Atk 60->95, Spe 60->85
    [SPECIES_TRAPINCH] = { .abilities[0] = ABILITY_SHEER_FORCE, .abilities[1] = ABILITY_STRONG_JAW, .abilities[2] = ABILITY_ARENA_TRAP }, // Slot 1: Hyper Cutter->Sheer Force, Slot 2: Arena Trap->Strong Jaw, Hidden: Sheer Force->Arena Trap
    [SPECIES_VIBRAVA] = { .abilities[2] = ABILITY_ARENA_TRAP }, // Hidden: Levitate->Arena Trap
    [SPECIES_FLYGON] = { .baseHP = 90, .baseDefense = 90, .baseSpAttack = 130, .baseSpDefense = 90, .abilities[2] = ABILITY_SAND_FORCE }, // HP 80->90, Def 80->90, SpA 80->130, SpD 80->90, Hidden: Levitate->Sand Force
    [SPECIES_CACTURNE] = { .baseAttack = 130, .baseDefense = 75, .baseSpAttack = 80, .baseSpDefense = 70, .abilities[2] = ABILITY_ROUGH_SKIN }, // Atk 115->130, Def 60->75, SpA 115->80, SpD 60->70, Hidden: Water Absorb->Rough Skin
    [SPECIES_SWABLU] = { .abilities[1] = ABILITY_COTTON_DOWN }, // Slot 2: None->Cotton Down
    [SPECIES_ALTARIA] = { .baseAttack = 80, .baseSpAttack = 80, .abilities[1] = ABILITY_COTTON_DOWN }, // Atk 70->80, SpA 70->80, Slot 2: None->Cotton Down
    [SPECIES_ALTARIA_MEGA] = { .baseSpeed = 95, .baseSpDefense = 110 }, // Spe 80->95, SpD 105->110
    [SPECIES_ZANGOOSE] = { .baseHP = 75, .baseSpeed = 110, .abilities[1] = ABILITY_TOUGH_CLAWS }, // HP 73->75, Spe 90->110, Slot 2: None->Tough Claws
    [SPECIES_SEVIPER] = { .baseHP = 75, .baseSpeed = 85, .abilities[1] = ABILITY_INFILTRATOR }, // HP 73->75, Spe 65->85, Slot 2: None->Infiltrator
    [SPECIES_LUNATONE] = { .abilities[1] = ABILITY_INTIMIDATE }, // Slot 2: None->Intimidate
    [SPECIES_SOLROCK] = { .abilities[1] = ABILITY_SOLAR_POWER }, // Slot 2: None->Solar Power
    [SPECIES_WHISCASH] = { .baseHP = 120, .baseAttack = 95, .baseDefense = 78, .baseSpAttack = 78 }, // HP 110->120, Atk 78->95, Def 73->78, SpA 76->78
    [SPECIES_CORPHISH] = { .baseSpAttack = 35, .baseSpDefense = 50 }, // SpA 50->35, SpD 35->50
    [SPECIES_CRAWDAUNT] = { .baseSpAttack = 55, .baseSpDefense = 90, .abilities[1] = ABILITY_ADAPTABILITY, .abilities[2] = ABILITY_SHELL_ARMOR }, // SpA 90->55, SpD 55->90, Slot 2: Shell Armor->Adaptability, Hidden: Adaptability->Shell Armor
    [SPECIES_BALTOY] = { .abilities[2] = ABILITY_MAGIC_GUARD }, // Hidden: None->Magic Guard
    [SPECIES_CLAYDOL] = { .abilities[2] = ABILITY_MAGIC_GUARD }, // Hidden: None->Magic Guard
    [SPECIES_CRADILY] = { .baseHP = 90, .baseAttack = 71, .baseSpeed = 30, .baseSpDefense = 130 }, // HP 86->90, Atk 81->71, Spe 43->30, SpD 107->130
    [SPECIES_ANORITH] = { .abilities[0] = ABILITY_SOLID_ROCK, .abilities[1] = ABILITY_TOUGH_CLAWS }, // Slot 1: Battle Armor->Solid Rock, Slot 2: None->Tough Claws
    [SPECIES_ARMALDO] = { .baseHP = 85, .baseSpeed = 75, .baseSpAttack = 40, .baseSpDefense = 85, .abilities[0] = ABILITY_SOLID_ROCK, .abilities[1] = ABILITY_TOUGH_CLAWS }, // HP 75->85, Spe 45->75, SpA 70->40, SpD 80->85, Slot 1: Battle Armor->Solid Rock, Slot 2: None->Tough Claws
    [SPECIES_MILOTIC] = { .abilities[1] = ABILITY_MULTISCALE }, // Slot 2: Competitive->Multiscale
    [SPECIES_DUSKULL] = { .abilities[0] = ABILITY_PRANKSTER }, // Slot 1: Levitate->Prankster
    [SPECIES_TROPIUS] = { .baseHP = 110, .baseDefense = 90, .baseSpeed = 30, .baseSpAttack = 90, .baseSpDefense = 100, .abilities[1] = ABILITY_THICK_FAT }, // HP 99->110, Def 83->90, Spe 51->30, SpA 72->90, SpD 87->100, Slot 2: Solar Power->Thick Fat
    [SPECIES_CHIMECHO] = { .baseHP = 80, .baseAttack = 40, .baseSpeed = 85 }, // HP 75->80, Atk 50->40, Spe 65->85
    [SPECIES_ABSOL_MEGA] = { .baseSpeed = 130, .baseSpAttack = 100 }, // Spe 115->130, SpA 115->100
    [SPECIES_GLALIE] = { .baseAttack = 100, .baseDefense = 90, .baseSpeed = 85, .baseSpAttack = 100, .baseSpDefense = 90, .abilities[0] = ABILITY_INTIMIDATE }, // Atk 80->100, Def 80->90, Spe 80->85, SpA 80->100, SpD 80->90, Slot 1: Inner Focus->Intimidate
    [SPECIES_GLALIE_MEGA] = { .baseDefense = 90, .baseSpeed = 120, .baseSpAttack = 100, .baseSpDefense = 90, .abilities[0] = ABILITY_SOLID_ROCK, .abilities[1] = ABILITY_SOLID_ROCK, .abilities[2] = ABILITY_SOLID_ROCK }, // Def 80->90, Spe 100->120, SpA 120->100, SpD 80->90, Slot 1: Refrigerate->Solid Rock, Slot 2: Refrigerate->Solid Rock, Hidden: Refrigerate->Solid Rock
    [SPECIES_WALREIN] = { .baseHP = 100, .baseAttack = 95, .baseDefense = 95, .baseSpAttack = 75, .baseSpDefense = 100, .abilities[2] = ABILITY_SLUSH_RUSH }, // HP 110->100, Atk 80->95, Def 90->95, SpA 95->75, SpD 90->100, Hidden: Oblivious->Slush Rush
    [SPECIES_RELICANTH] = { .baseSpeed = 75 }, // Spe 55->75
    [SPECIES_LUVDISC] = { .baseHP = 60, .baseDefense = 70, .baseSpeed = 100, .baseSpAttack = 80, .baseSpDefense = 80, .abilities[1] = ABILITY_HYDRATION, .abilities[2] = ABILITY_MULTISCALE }, // HP 43->60, Def 55->70, Spe 97->100, SpA 40->80, SpD 65->80, Slot 2: None->Hydration, Hidden: Hydration->Multiscale
    [SPECIES_BAGON] = { .abilities[1] = ABILITY_SHEER_FORCE }, // Slot 2: None->Sheer Force
    [SPECIES_SHELGON] = { .abilities[1] = ABILITY_OVERCOAT }, // Slot 2: None->Overcoat
    [SPECIES_SALAMENCE] = { .abilities[1] = ABILITY_MOXIE }, // Slot 2: None->Moxie
    [SPECIES_METAGROSS] = { .abilities[1] = ABILITY_IRON_FIST }, // Slot 2: None->Iron Fist
    [SPECIES_LATIAS] = { .abilities[0] = ABILITY_TELEPATHY }, // Slot 1: Levitate->Telepathy
    [SPECIES_LATIAS_MEGA] = { .abilities[0] = ABILITY_TELEPATHY, .abilities[1] = ABILITY_TELEPATHY, .abilities[2] = ABILITY_TELEPATHY }, // Slot 1: Levitate->Telepathy, Slot 2: Levitate->Telepathy, Hidden: Levitate->Telepathy
    [SPECIES_LATIOS] = { .abilities[0] = ABILITY_TELEPATHY }, // Slot 1: Levitate->Telepathy
    [SPECIES_LATIOS_MEGA] = { .abilities[0] = ABILITY_TELEPATHY, .abilities[1] = ABILITY_TELEPATHY, .abilities[2] = ABILITY_TELEPATHY }, // Slot 1: Levitate->Telepathy, Slot 2: Levitate->Telepathy, Hidden: Levitate->Telepathy
    [SPECIES_TURTWIG] = { .abilities[1] = ABILITY_SHELL_ARMOR }, // Slot 2: None->Shell Armor
    [SPECIES_GROTLE] = { .abilities[1] = ABILITY_SHELL_ARMOR }, // Slot 2: None->Shell Armor
    [SPECIES_TORTERRA] = { .abilities[1] = ABILITY_SHELL_ARMOR }, // Slot 2: None->Shell Armor
    [SPECIES_CHIMCHAR] = { .abilities[1] = ABILITY_IRON_FIST }, // Slot 2: None->Iron Fist
    [SPECIES_MONFERNO] = { .abilities[1] = ABILITY_IRON_FIST }, // Slot 2: None->Iron Fist
    [SPECIES_INFERNAPE] = { .abilities[1] = ABILITY_IRON_FIST }, // Slot 2: None->Iron Fist
    [SPECIES_STARLY] = { .abilities[1] = ABILITY_RECKLESS }, // Slot 2: None->Reckless
    [SPECIES_STARAVIA] = { .abilities[1] = ABILITY_RECKLESS }, // Slot 2: None->Reckless
    [SPECIES_STARAPTOR] = { .abilities[1] = ABILITY_RECKLESS }, // Slot 2: None->Reckless
    [SPECIES_KRICKETOT] = { .baseHP = 53, .baseAttack = 55, .baseDefense = 61, .baseSpeed = 40, .baseSpAttack = 40, .baseSpDefense = 61, .abilities[1] = ABILITY_TECHNICIAN, .abilities[2] = ABILITY_TINTED_LENS }, // HP 37->53, Atk 25->55, Def 41->61, Spe 25->40, SpA 25->40, SpD 41->61, Slot 2: None->Technician, Hidden: Run Away->Tinted Lens
    [SPECIES_KRICKETUNE] = { .baseHP = 75, .baseAttack = 90, .baseDefense = 65, .baseSpeed = 80, .baseSpAttack = 50, .baseSpDefense = 65, .abilities[1] = ABILITY_TECHNICIAN, .abilities[2] = ABILITY_TINTED_LENS }, // HP 77->75, Atk 85->90, Def 51->65, Spe 65->80, SpA 55->50, SpD 51->65, Slot 2: None->Technician, Hidden: Technician->Tinted Lens
    [SPECIES_SHINX] = { .abilities[0] = ABILITY_STRONG_JAW }, // Slot 1: Rivalry->Strong Jaw
    [SPECIES_LUXIO] = { .abilities[0] = ABILITY_STRONG_JAW }, // Slot 1: Rivalry->Strong Jaw
    [SPECIES_LUXRAY] = { .abilities[0] = ABILITY_STRONG_JAW }, // Slot 1: Rivalry->Strong Jaw
    [SPECIES_RAMPARDOS] = { .abilities[1] = ABILITY_ROCK_HEAD }, // Slot 2: None->Rock Head
    [SPECIES_BUNEARY] = { .abilities[1] = ABILITY_SCRAPPY }, // Slot 2: Klutz->Scrappy
    [SPECIES_LOPUNNY] = { .baseAttack = 106, .abilities[1] = ABILITY_SCRAPPY }, // Atk 76->106, Slot 2: Klutz->Scrappy
    [SPECIES_LOPUNNY_MEGA] = { .baseAttack = 146, .baseDefense = 104, .baseSpDefense = 106 }, // Atk 136->146, Def 94->104, SpD 96->106
    [SPECIES_MISMAGIUS] = { .baseSpeed = 110, .baseSpAttack = 110, .baseSpDefense = 110, .abilities[1] = ABILITY_CURSED_BODY, .abilities[2] = ABILITY_PIXILATE }, // Spe 105->110, SpA 105->110, SpD 105->110, Slot 2: None->Cursed Body, Hidden: None->Pixilate
    [SPECIES_PURUGLY] = { .baseAttack = 92 }, // Atk 82->92
    [SPECIES_BRONZOR] = { .abilities[0] = ABILITY_HEATPROOF }, // Slot 1: Levitate->Heatproof
    [SPECIES_BRONZONG] = { .abilities[0] = ABILITY_HEATPROOF }, // Slot 1: Levitate->Heatproof
    [SPECIES_CHATOT] = { .baseDefense = 65, .baseSpeed = 96, .baseSpAttack = 112, .baseSpDefense = 62 }, // Def 45->65, Spe 91->96, SpA 92->112, SpD 42->62
    [SPECIES_SPIRITOMB] = { .abilities[1] = ABILITY_INFILTRATOR }, // Slot 2: None->Infiltrator
    [SPECIES_GARCHOMP_MEGA] = { .baseDefense = 105, .baseSpeed = 102 }, // Def 115->105, Spe 92->102
    [SPECIES_CARNIVINE] = { .baseHP = 80, .baseAttack = 110, .baseSpeed = 80, .baseSpAttack = 70, .abilities[0] = ABILITY_STRONG_JAW, .abilities[2] = ABILITY_CHLOROPHYLL }, // HP 74->80, Atk 100->110, Spe 46->80, SpA 90->70, Slot 1: Levitate->Strong Jaw, Hidden: None->Chlorophyll
    [SPECIES_WEAVILE] = { .abilities[0] = ABILITY_TECHNICIAN, .abilities[1] = ABILITY_PRESSURE }, // Slot 1: Pressure->Technician, Slot 2: None->Pressure
    [SPECIES_MAGMORTAR] = { .abilities[1] = ABILITY_MEGA_LAUNCHER }, // Slot 2: None->Mega Launcher
    [SPECIES_GLISCOR] = { .abilities[1] = ABILITY_POISON_HEAL, .abilities[2] = ABILITY_SAND_VEIL }, // Slot 2: Sand Veil->Poison Heal, Hidden: Poison Heal->Sand Veil
    [SPECIES_MAMOSWINE] = { .abilities[1] = ABILITY_THICK_FAT, .abilities[2] = ABILITY_SNOW_CLOAK }, // Slot 2: Snow Cloak->Thick Fat, Hidden: Thick Fat->Snow Cloak
    [SPECIES_GALLADE_MEGA] = { .abilities[0] = ABILITY_SHARPNESS, .abilities[1] = ABILITY_SHARPNESS, .abilities[2] = ABILITY_SHARPNESS }, // Slot 1: Inner Focus->Sharpness, Slot 2: Inner Focus->Sharpness, Hidden: Inner Focus->Sharpness
    [SPECIES_ROTOM_HEAT] = { .abilities[1] = ABILITY_MOTOR_DRIVE }, // Slot 2: None->Motor Drive
    [SPECIES_ROTOM_WASH] = { .abilities[1] = ABILITY_MOTOR_DRIVE }, // Slot 2: None->Motor Drive
    [SPECIES_ROTOM_FROST] = { .abilities[1] = ABILITY_MOTOR_DRIVE }, // Slot 2: None->Motor Drive
    [SPECIES_ROTOM_FAN] = { .abilities[1] = ABILITY_MOTOR_DRIVE }, // Slot 2: None->Motor Drive
    [SPECIES_ROTOM_MOW] = { .abilities[1] = ABILITY_MOTOR_DRIVE }, // Slot 2: None->Motor Drive
    [SPECIES_UXIE] = { .abilities[0] = ABILITY_TELEPATHY, .abilities[1] = ABILITY_LEVITATE }, // Slot 1: Levitate->Telepathy, Slot 2: None->Levitate
    [SPECIES_MESPRIT] = { .abilities[0] = ABILITY_TELEPATHY, .abilities[1] = ABILITY_LEVITATE }, // Slot 1: Levitate->Telepathy, Slot 2: None->Levitate
    [SPECIES_AZELF] = { .abilities[0] = ABILITY_TELEPATHY, .abilities[1] = ABILITY_LEVITATE }, // Slot 1: Levitate->Telepathy, Slot 2: None->Levitate
    [SPECIES_GIRATINA_ORIGIN] = { .abilities[2] = ABILITY_TELEPATHY }, // Hidden: None->Telepathy
    [SPECIES_SNIVY] = { .abilities[1] = ABILITY_CONTRARY }, // Slot 2: None->Contrary
    [SPECIES_SERVINE] = { .abilities[1] = ABILITY_CONTRARY }, // Slot 2: None->Contrary
    [SPECIES_SERPERIOR] = { .baseAttack = 65, .baseSpAttack = 85, .abilities[1] = ABILITY_CONTRARY }, // Atk 75->65, SpA 75->85, Slot 2: None->Contrary
    [SPECIES_TEPIG] = { .abilities[1] = ABILITY_THICK_FAT }, // Slot 2: None->Thick Fat
    [SPECIES_PIGNITE] = { .abilities[1] = ABILITY_THICK_FAT }, // Slot 2: None->Thick Fat
    [SPECIES_EMBOAR] = { .abilities[1] = ABILITY_RECKLESS }, // Slot 2: None->Reckless
    [SPECIES_OSHAWOTT] = { .abilities[1] = ABILITY_SHELL_ARMOR }, // Slot 2: None->Shell Armor
    [SPECIES_DEWOTT] = { .baseAttack = 85, .baseSpAttack = 73, .abilities[1] = ABILITY_SHELL_ARMOR }, // Atk 75->85, SpA 83->73, Slot 2: None->Shell Armor
    [SPECIES_SAMUROTT] = { .baseHP = 90, .baseAttack = 115, .baseDefense = 80, .baseSpeed = 85, .baseSpAttack = 93, .abilities[1] = ABILITY_SHARPNESS, .abilities[2] = ABILITY_SHARPNESS }, // HP 95->90, Atk 100->115, Def 85->80, Spe 70->85, SpA 108->93, Slot 2: None->Sharpness, Hidden: Shell Armor->Sharpness
    [SPECIES_PANSAGE] = { .abilities[1] = ABILITY_OVERGROW }, // Slot 2: None->Overgrow
    [SPECIES_SIMISAGE] = { .abilities[1] = ABILITY_OVERGROW }, // Slot 2: None->Overgrow
    [SPECIES_PANSEAR] = { .abilities[1] = ABILITY_BLAZE }, // Slot 2: None->Blaze
    [SPECIES_SIMISEAR] = { .abilities[1] = ABILITY_BLAZE }, // Slot 2: None->Blaze
    [SPECIES_PANPOUR] = { .abilities[1] = ABILITY_TORRENT }, // Slot 2: None->Torrent
    [SPECIES_SIMIPOUR] = { .abilities[1] = ABILITY_TORRENT }, // Slot 2: None->Torrent
    [SPECIES_PIDOVE] = { .baseAttack = 36, .baseSpAttack = 55 }, // Atk 55->36, SpA 36->55
    [SPECIES_TRANQUILL] = { .baseAttack = 45, .baseSpAttack = 82 }, // Atk 77->45, SpA 50->82
    [SPECIES_UNFEZANT] = { .baseAttack = 65, .baseSpAttack = 115 }, // Atk 115->65, SpA 65->115
    [SPECIES_BLITZLE] = { .abilities[0] = ABILITY_STRIKER }, // Slot 1: Lightning Rod->Striker
    [SPECIES_ZEBSTRIKA] = { .abilities[0] = ABILITY_STRIKER }, // Slot 1: Lightning Rod->Striker
    [SPECIES_AUDINO_MEGA] = { .abilities[0] = ABILITY_REGENERATOR, .abilities[1] = ABILITY_REGENERATOR, .abilities[2] = ABILITY_REGENERATOR }, // Slot 1: Healer->Regenerator, Slot 2: Healer->Regenerator, Hidden: Healer->Regenerator
    [SPECIES_LEAVANNY] = { .abilities[2] = ABILITY_SHARPNESS }, // Hidden: Overcoat->Sharpness
    [SPECIES_WHIMSICOTT] = { .baseHP = 80, .baseDefense = 90, .baseSpDefense = 80 }, // HP 60->80, Def 85->90, SpD 75->80
    [SPECIES_BASCULIN_RED_STRIPED] = { .baseAttack = 102, .baseSpAttack = 70 }, // Atk 92->102, SpA 80->70
    [SPECIES_SIGILYPH] = { .baseHP = 82, .baseAttack = 38, .baseSpAttack = 113, .abilities[0] = ABILITY_TINTED_LENS, .abilities[2] = ABILITY_PSYCHIC_SURGE }, // HP 72->82, Atk 58->38, SpA 103->113, Slot 1: Wonder Skin->Tinted Lens, Hidden: Tinted Lens->Psychic Surge
    [SPECIES_YAMASK] = { .baseAttack = 25, .baseSpDefense = 70 }, // Atk 30->25, SpD 65->70
    [SPECIES_COFAGRIGUS] = { .baseAttack = 40, .baseSpDefense = 115 }, // Atk 50->40, SpD 105->115
    [SPECIES_SWANNA] = { .baseAttack = 67, .baseSpAttack = 107, .abilities[0] = ABILITY_DRIZZLE, .abilities[1] = ABILITY_FRIEND_GUARD }, // Atk 87->67, SpA 87->107, Slot 1: Keen Eye->Drizzle, Slot 2: Big Pecks->Friend Guard
    [SPECIES_SAWSBUCK_SPRING] = { .baseAttack = 110, .baseSpeed = 105 }, // Atk 100->110, Spe 95->105
    [SPECIES_SAWSBUCK_SUMMER] = { .baseAttack = 110, .baseSpeed = 105 }, // Atk 100->110, Spe 95->105
    [SPECIES_SAWSBUCK_AUTUMN] = { .baseAttack = 110, .baseSpeed = 105 }, // Atk 100->110, Spe 95->105
    [SPECIES_SAWSBUCK_WINTER] = { .baseAttack = 110, .baseSpeed = 105 }, // Atk 100->110, Spe 95->105
    [SPECIES_FERROTHORN] = { .baseHP = 84 }, // HP 74->84
    [SPECIES_KLINK] = { .abilities[0] = ABILITY_STEELWORKER, .abilities[1] = ABILITY_CLEAR_BODY }, // Slot 1: Plus->Steelworker, Slot 2: Minus->Clear Body
    [SPECIES_KLANG] = { .abilities[0] = ABILITY_STEELWORKER, .abilities[1] = ABILITY_CLEAR_BODY }, // Slot 1: Plus->Steelworker, Slot 2: Minus->Clear Body
    [SPECIES_KLINKLANG] = { .abilities[0] = ABILITY_STEELWORKER, .abilities[1] = ABILITY_CLEAR_BODY }, // Slot 1: Plus->Steelworker, Slot 2: Minus->Clear Body
    [SPECIES_BEHEEYEM] = { .abilities[0] = ABILITY_PSYCHIC_SURGE }, // Slot 1: Telepathy->Psychic Surge
    [SPECIES_FRAXURE] = { .abilities[0] = ABILITY_SHARPNESS }, // Slot 1: Rivalry->Sharpness
    [SPECIES_HAXORUS] = { .abilities[0] = ABILITY_SHARPNESS }, // Slot 1: Rivalry->Sharpness
    [SPECIES_BEARTIC] = { .baseHP = 85, .baseDefense = 70, .baseSpeed = 95, .baseSpDefense = 70 }, // HP 95->85, Def 80->70, Spe 50->95, SpD 80->70
    [SPECIES_CRYOGONAL] = { .abilities[1] = ABILITY_SNOW_CLOAK, .abilities[2] = ABILITY_SLUSH_RUSH }, // Slot 2: None->Snow Cloak, Hidden: None->Slush Rush
    [SPECIES_STUNFISK_GALAR] = { .abilities[0] = ABILITY_ROUGH_SKIN }, // Slot 1: Mimicry->Rough Skin
    [SPECIES_DEINO] = { .abilities[2] = ABILITY_REGENERATOR }, // Hidden: None->Regenerator
    [SPECIES_ZWEILOUS] = { .abilities[2] = ABILITY_REGENERATOR }, // Hidden: None->Regenerator
    [SPECIES_HYDREIGON] = { .abilities[0] = ABILITY_MEGA_LAUNCHER, .abilities[1] = ABILITY_LEVITATE }, // Slot 1: Levitate->Mega Launcher, Slot 2: None->Levitate
    [SPECIES_TORNADUS_INCARNATE] = { .baseSpAttack = 130, .abilities[1] = ABILITY_REGENERATOR, .abilities[2] = ABILITY_COMPETITIVE }, // SpA 125->130, Slot 2: None->Regenerator, Hidden: Defiant->Competitive
    [SPECIES_TORNADUS_THERIAN] = { .baseSpAttack = 115 }, // SpA 110->115
    [SPECIES_THUNDURUS_INCARNATE] = { .baseSpAttack = 130, .abilities[1] = ABILITY_LIGHTNING_ROD, .abilities[2] = ABILITY_COMPETITIVE }, // SpA 125->130, Slot 2: None->Lightning Rod, Hidden: Defiant->Competitive
    [SPECIES_THUNDURUS_THERIAN] = { .baseSpAttack = 150 }, // SpA 145->150
    [SPECIES_LANDORUS_INCARNATE] = { .baseSpAttack = 120, .abilities[1] = ABILITY_SHEER_FORCE }, // SpA 115->120, Slot 2: None->Sheer Force
    [SPECIES_KELDEO_ORDINARY] = { .abilities[0] = ABILITY_SHARPNESS }, // Slot 1: Justified->Sharpness
    [SPECIES_KELDEO_RESOLUTE] = { .abilities[0] = ABILITY_SHARPNESS }, // Slot 1: Justified->Sharpness
    [SPECIES_CHESPIN] = { .abilities[1] = ABILITY_SHELL_ARMOR }, // Slot 2: None->Shell Armor
    [SPECIES_QUILLADIN] = { .abilities[1] = ABILITY_SHELL_ARMOR }, // Slot 2: None->Shell Armor
    [SPECIES_CHESNAUGHT] = { .abilities[1] = ABILITY_SHELL_ARMOR }, // Slot 2: None->Shell Armor
    [SPECIES_FENNEKIN] = { .abilities[1] = ABILITY_MAGIC_GUARD }, // Slot 2: None->Magic Guard
    [SPECIES_BRAIXEN] = { .abilities[1] = ABILITY_MAGIC_GUARD }, // Slot 2: None->Magic Guard
    [SPECIES_DELPHOX] = { .abilities[1] = ABILITY_MAGIC_GUARD }, // Slot 2: None->Magic Guard
    [SPECIES_FROAKIE] = { .abilities[1] = ABILITY_PROTEAN }, // Slot 2: None->Protean
    [SPECIES_FROGADIER] = { .abilities[1] = ABILITY_PROTEAN }, // Slot 2: None->Protean
    [SPECIES_GRENINJA] = { .baseAttack = 100, .abilities[1] = ABILITY_PROTEAN }, // Atk 95->100, Slot 2: None->Protean
    [SPECIES_DIGGERSBY] = { .abilities[1] = ABILITY_HUGE_POWER }, // Slot 2: Cheek Pouch->Huge Power
    [SPECIES_LITLEO] = { .abilities[2] = ABILITY_SOUL_HEART }, // Hidden: Moxie->Soul-Heart
    [SPECIES_PYROAR] = { .abilities[2] = ABILITY_SOUL_HEART }, // Hidden: Moxie->Soul-Heart
    [SPECIES_FLORGES_RED] = { .abilities[1] = ABILITY_MISTY_SURGE }, // Slot 2: None->Misty Surge
    [SPECIES_SKIDDO] = { .baseHP = 70, .baseDefense = 50, .baseSpeed = 55, .baseSpAttack = 60, .baseSpDefense = 60, .abilities[1] = ABILITY_GRASS_PELT, .abilities[2] = ABILITY_CHLOROPHYLL }, // HP 66->70, Def 48->50, Spe 52->55, SpA 62->60, SpD 57->60, Slot 2: None->Grass Pelt, Hidden: Grass Pelt->Chlorophyll
    [SPECIES_GOGOAT] = { .baseHP = 100, .baseAttack = 115, .baseDefense = 70, .baseSpeed = 95, .baseSpAttack = 60, .baseSpDefense = 80, .abilities[1] = ABILITY_GRASS_PELT, .abilities[2] = ABILITY_GRASSY_SURGE }, // HP 123->100, Atk 100->115, Def 62->70, Spe 68->95, SpA 97->60, SpD 81->80, Slot 2: None->Grass Pelt, Hidden: Grass Pelt->Grassy Surge
    [SPECIES_MEOWSTIC_M] = { .baseSpeed = 110, .baseSpAttack = 100 }, // Spe 104->110, SpA 83->100
    [SPECIES_HONEDGE] = { .abilities[1] = ABILITY_SHARPNESS, .abilities[2] = ABILITY_JUSTIFIED }, // Slot 2: None->Sharpness, Hidden: None->Justified
    [SPECIES_DOUBLADE] = { .abilities[1] = ABILITY_SHARPNESS, .abilities[2] = ABILITY_JUSTIFIED }, // Slot 2: None->Sharpness, Hidden: None->Justified
    [SPECIES_INKAY] = { .abilities[1] = ABILITY_INFILTRATOR }, // Slot 2: Suction Cups->Infiltrator
    [SPECIES_MALAMAR] = { .baseAttack = 100, .baseSpeed = 90, .abilities[1] = ABILITY_INFILTRATOR }, // Atk 92->100, Spe 73->90, Slot 2: Suction Cups->Infiltrator
    [SPECIES_NOIBAT] = { .baseAttack = 25, .baseSpAttack = 50 }, // Atk 30->25, SpA 45->50
    [SPECIES_NOIVERN] = { .baseSpAttack = 112 }, // SpA 97->112
    [SPECIES_HOOPA_CONFINED] = { .abilities[0] = ABILITY_PRANKSTER }, // Slot 1: Magician->Prankster
    [SPECIES_ROWLET] = { .abilities[1] = ABILITY_LONG_REACH }, // Slot 2: None->Long Reach
    [SPECIES_DARTRIX] = { .abilities[1] = ABILITY_LONG_REACH }, // Slot 2: None->Long Reach
    [SPECIES_DECIDUEYE] = { .baseSpeed = 95, .baseSpAttack = 75, .abilities[1] = ABILITY_LONG_REACH }, // Spe 70->95, SpA 100->75, Slot 2: None->Long Reach
    [SPECIES_LITTEN] = { .abilities[1] = ABILITY_INTIMIDATE }, // Slot 2: None->Intimidate
    [SPECIES_TORRACAT] = { .abilities[1] = ABILITY_INTIMIDATE }, // Slot 2: None->Intimidate
    [SPECIES_INCINEROAR] = { .abilities[1] = ABILITY_INTIMIDATE }, // Slot 2: None->Intimidate
    [SPECIES_POPPLIO] = { .abilities[1] = ABILITY_LIQUID_VOICE }, // Slot 2: None->Liquid Voice
    [SPECIES_BRIONNE] = { .abilities[1] = ABILITY_LIQUID_VOICE }, // Slot 2: None->Liquid Voice
    [SPECIES_PRIMARINA] = { .abilities[1] = ABILITY_LIQUID_VOICE }, // Slot 2: None->Liquid Voice
    [SPECIES_VIKAVOLT] = { .baseAttack = 93, .baseSpeed = 109, .baseSpDefense = 86, .abilities[1] = ABILITY_BATTERY }, // Atk 70->93, Spe 43->109, SpD 75->86, Slot 2: None->Battery
    [SPECIES_CRABRAWLER] = { .abilities[0] = ABILITY_ANGER_POINT, .abilities[2] = ABILITY_VITAL_SPIRIT }, // Slot 1: Hyper Cutter->Anger Point, Hidden: Anger Point->Vital Spirit
    [SPECIES_CRABOMINABLE] = { .baseSpeed = 65, .abilities[0] = ABILITY_ANGER_POINT, .abilities[2] = ABILITY_FUR_COAT }, // Spe 43->65, Slot 1: Hyper Cutter->Anger Point, Hidden: Anger Point->Fur Coat
    [SPECIES_LYCANROC_DUSK] = { .abilities[1] = ABILITY_SAND_RUSH, .abilities[2] = ABILITY_VITAL_SPIRIT }, // Slot 2: None->Sand Rush, Hidden: None->Vital Spirit
    [SPECIES_MAREANIE] = { .baseDefense = 67, .baseSpAttack = 33, .baseSpDefense = 57 }, // Def 62->67, SpA 43->33, SpD 52->57
    [SPECIES_TOXAPEX] = { .baseHP = 60, .baseSpAttack = 43 }, // HP 50->60, SpA 53->43
    [SPECIES_TSAREENA] = { .abilities[2] = ABILITY_STRIKER }, // Hidden: Sweet Veil->Striker
    [SPECIES_SILVALLY_NORMAL] = { .baseHP = 100, .baseAttack = 100, .baseDefense = 100, .baseSpeed = 100, .baseSpAttack = 100, .baseSpDefense = 100 }, // HP 95->100, Atk 95->100, Def 95->100, Spe 95->100, SpA 95->100, SpD 95->100
    [SPECIES_SILVALLY_FIGHTING] = { .baseHP = 100, .baseAttack = 100, .baseDefense = 100, .baseSpeed = 100, .baseSpAttack = 100, .baseSpDefense = 100 }, // HP 95->100, Atk 95->100, Def 95->100, Spe 95->100, SpA 95->100, SpD 95->100
    [SPECIES_SILVALLY_FLYING] = { .baseHP = 100, .baseAttack = 100, .baseDefense = 100, .baseSpeed = 100, .baseSpAttack = 100, .baseSpDefense = 100 }, // HP 95->100, Atk 95->100, Def 95->100, Spe 95->100, SpA 95->100, SpD 95->100
    [SPECIES_SILVALLY_POISON] = { .baseHP = 100, .baseAttack = 100, .baseDefense = 100, .baseSpeed = 100, .baseSpAttack = 100, .baseSpDefense = 100 }, // HP 95->100, Atk 95->100, Def 95->100, Spe 95->100, SpA 95->100, SpD 95->100
    [SPECIES_SILVALLY_GROUND] = { .baseHP = 100, .baseAttack = 100, .baseDefense = 100, .baseSpeed = 100, .baseSpAttack = 100, .baseSpDefense = 100 }, // HP 95->100, Atk 95->100, Def 95->100, Spe 95->100, SpA 95->100, SpD 95->100
    [SPECIES_SILVALLY_ROCK] = { .baseHP = 100, .baseAttack = 100, .baseDefense = 100, .baseSpeed = 100, .baseSpAttack = 100, .baseSpDefense = 100 }, // HP 95->100, Atk 95->100, Def 95->100, Spe 95->100, SpA 95->100, SpD 95->100
    [SPECIES_SILVALLY_BUG] = { .baseHP = 100, .baseAttack = 100, .baseDefense = 100, .baseSpeed = 100, .baseSpAttack = 100, .baseSpDefense = 100 }, // HP 95->100, Atk 95->100, Def 95->100, Spe 95->100, SpA 95->100, SpD 95->100
    [SPECIES_SILVALLY_GHOST] = { .baseHP = 100, .baseAttack = 100, .baseDefense = 100, .baseSpeed = 100, .baseSpAttack = 100, .baseSpDefense = 100 }, // HP 95->100, Atk 95->100, Def 95->100, Spe 95->100, SpA 95->100, SpD 95->100
    [SPECIES_SILVALLY_STEEL] = { .baseHP = 100, .baseAttack = 100, .baseDefense = 100, .baseSpeed = 100, .baseSpAttack = 100, .baseSpDefense = 100 }, // HP 95->100, Atk 95->100, Def 95->100, Spe 95->100, SpA 95->100, SpD 95->100
    [SPECIES_SILVALLY_FIRE] = { .baseHP = 100, .baseAttack = 100, .baseDefense = 100, .baseSpeed = 100, .baseSpAttack = 100, .baseSpDefense = 100 }, // HP 95->100, Atk 95->100, Def 95->100, Spe 95->100, SpA 95->100, SpD 95->100
    [SPECIES_SILVALLY_WATER] = { .baseHP = 100, .baseAttack = 100, .baseDefense = 100, .baseSpeed = 100, .baseSpAttack = 100, .baseSpDefense = 100 }, // HP 95->100, Atk 95->100, Def 95->100, Spe 95->100, SpA 95->100, SpD 95->100
    [SPECIES_SILVALLY_GRASS] = { .baseHP = 100, .baseAttack = 100, .baseDefense = 100, .baseSpeed = 100, .baseSpAttack = 100, .baseSpDefense = 100 }, // HP 95->100, Atk 95->100, Def 95->100, Spe 95->100, SpA 95->100, SpD 95->100
    [SPECIES_SILVALLY_ELECTRIC] = { .baseHP = 100, .baseAttack = 100, .baseDefense = 100, .baseSpeed = 100, .baseSpAttack = 100, .baseSpDefense = 100 }, // HP 95->100, Atk 95->100, Def 95->100, Spe 95->100, SpA 95->100, SpD 95->100
    [SPECIES_SILVALLY_PSYCHIC] = { .baseHP = 100, .baseAttack = 100, .baseDefense = 100, .baseSpeed = 100, .baseSpAttack = 100, .baseSpDefense = 100 }, // HP 95->100, Atk 95->100, Def 95->100, Spe 95->100, SpA 95->100, SpD 95->100
    [SPECIES_SILVALLY_ICE] = { .baseHP = 100, .baseAttack = 100, .baseDefense = 100, .baseSpeed = 100, .baseSpAttack = 100, .baseSpDefense = 100 }, // HP 95->100, Atk 95->100, Def 95->100, Spe 95->100, SpA 95->100, SpD 95->100
    [SPECIES_SILVALLY_DRAGON] = { .baseHP = 100, .baseAttack = 100, .baseDefense = 100, .baseSpeed = 100, .baseSpAttack = 100, .baseSpDefense = 100 }, // HP 95->100, Atk 95->100, Def 95->100, Spe 95->100, SpA 95->100, SpD 95->100
    [SPECIES_SILVALLY_DARK] = { .baseHP = 100, .baseAttack = 100, .baseDefense = 100, .baseSpeed = 100, .baseSpAttack = 100, .baseSpDefense = 100 }, // HP 95->100, Atk 95->100, Def 95->100, Spe 95->100, SpA 95->100, SpD 95->100
    [SPECIES_SILVALLY_FAIRY] = { .baseHP = 100, .baseAttack = 100, .baseDefense = 100, .baseSpeed = 100, .baseSpAttack = 100, .baseSpDefense = 100 }, // HP 95->100, Atk 95->100, Def 95->100, Spe 95->100, SpA 95->100, SpD 95->100
    [SPECIES_TOGEDEMARU] = { .abilities[2] = ABILITY_ELECTRIC_SURGE }, // Hidden: Sturdy->Electric Surge
    [SPECIES_ZERAORA] = { .abilities[1] = ABILITY_IRON_FIST }, // Slot 2: None->Iron Fist
    [SPECIES_RILLABOOM] = { .abilities[1] = ABILITY_GRASSY_SURGE }, // Slot 2: None->Grassy Surge
    [SPECIES_SCORBUNNY] = { .abilities[1] = ABILITY_LIBERO }, // Slot 2: None->Libero
    [SPECIES_RABOOT] = { .abilities[1] = ABILITY_LIBERO }, // Slot 2: None->Libero
    [SPECIES_CINDERACE] = { .abilities[1] = ABILITY_LIBERO }, // Slot 2: None->Libero
    [SPECIES_SOBBLE] = { .abilities[1] = ABILITY_SNIPER }, // Slot 2: None->Sniper
    [SPECIES_DRIZZILE] = { .abilities[1] = ABILITY_SNIPER }, // Slot 2: None->Sniper
    [SPECIES_INTELEON] = { .abilities[1] = ABILITY_SNIPER }, // Slot 2: None->Sniper
    [SPECIES_THIEVUL] = { .baseHP = 60, .baseAttack = 100, .baseDefense = 60, .baseSpeed = 110, .baseSpAttack = 70, .baseSpDefense = 70 }, // HP 70->60, Atk 58->100, Def 58->60, Spe 90->110, SpA 87->70, SpD 92->70
    [SPECIES_APPLIN] = { .baseHP = 50, .baseAttack = 60, .baseDefense = 70, .baseSpeed = 35 }, // HP 40->50, Atk 40->60, Def 80->70, Spe 20->35
    [SPECIES_SIRFETCHD] = { .abilities[0] = ABILITY_SHARPNESS, .abilities[1] = ABILITY_JUSTIFIED }, // Slot 1: Steadfast->Sharpness, Slot 2: None->Justified
    [SPECIES_FALINKS] = { .abilities[1] = ABILITY_JUSTIFIED }, // Slot 2: None->Justified
};
