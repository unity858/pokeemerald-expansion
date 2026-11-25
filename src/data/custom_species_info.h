// Species base stat, ability, type, wild held item, EV yield, catch rate, exp yield,
// gender ratio and evolution overrides for Custom data mode (ported from R.O.W.E.,
// except the evolution overrides).
//
// Applied by GetSpeciesBaseHP/.../GetSpeciesBaseSpeed (and so GetSpeciesBaseStat,
// stat calculation, Pokédex, Battle Dome, AI, ...) and by GetSpeciesAbility
// (GetAbilityBySpecies, summary, trainer parties, ...) and by GetSpeciesType
// (battle switch-in types, default Tera Type, Pokédex, summary, AI, ...) in src/pokemon.c, only
// when IsCustomDataMode() is TRUE. Vanilla mode always uses gSpeciesInfo.
//
// One entry per species; leave a field out (or 0 / ABILITY_NONE) to keep the
// vanilla value. abilities[0] = slot 1, abilities[1] = slot 2, abilities[2] = hidden.
// types[0] = Type1, types[1] = Type2 (0 = TYPE_NONE = keep vanilla); a pure type
// has Type1 == Type2, so making a species mono-type sets the differing slot.
// itemCommon / itemRare: wild held items, read by GetSpeciesItemCommon/Rare
// (wild encounters, DexNav). ITEM_NONE = keep vanilla, CUSTOM_HELD_ITEM_NONE =
// remove the vanilla item. Common = 50%, rare = 5% (60% / 20% with Compound
// Eyes etc.); common == rare means always held, the same as R.O.W.E.'s
// item1 == item2. Where R.O.W.E. made a species always hold an item, both
// fields are set so that meaning is kept.
// evYield[STAT_*] (GetSpeciesEvYield: EV gain, HGSS Pokédex) holds
// CUSTOM_EV_YIELD(n) = n + 1 because 0 EVs is a real value; 0 = keep vanilla.
// catchRate (GetSpeciesCatchRate: ball catch odds, Safari Zone, HGSS Pokédex):
// 0 = keep vanilla.
// expYield (GetSpeciesExpYield: battle exp, HGSS Pokédex): 0 = keep vanilla.
// genderRatio (GetSpeciesGenderRatio: gender from personality, trainer and
// wild mon generation, HGSS Pokédex) holds CUSTOM_GENDER_RATIO(r) because
// MON_MALE is 0; 0 = keep vanilla.
// evolutions (GetSpeciesEvolutions: level-up/item/trade evolution, Exiolite,
// pre-evolutions, breeding, HGSS Pokédex evolution page) is an EVOLUTION(...)
// list in the gSpeciesInfo format that replaces the whole vanilla list;
// NULL = keep vanilla. Not from R.O.W.E.: custom to this hack.
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
    [SPECIES_RATTATA] = { .itemRare = ITEM_CHILAN_BERRY }, // Rare None→Chilan Berry
    [SPECIES_RATICATE] = { .baseHP = 60, .baseAttack = 95, .baseSpeed = 100, .abilities[0] = ABILITY_STRONG_JAW, .itemRare = ITEM_CHILAN_BERRY }, // HP 55->60, Atk 81->95, Spe 97->100, Slot 1: Run Away->Strong Jaw, Rare None→Chilan Berry
    [SPECIES_RATICATE_ALOLA] = { .abilities[1] = ABILITY_STRONG_JAW }, // Slot 2: Hustle->Strong Jaw
    [SPECIES_SPEAROW] = { .abilities[1] = ABILITY_BIG_PECKS, .types[0] = TYPE_FLYING }, // Slot 2: None->Big Pecks, Type1 Normal→Flying (now pure Flying)
    [SPECIES_FEAROW] = { .baseAttack = 100, .baseSpeed = 115, .abilities[1] = ABILITY_TECHNICIAN, .types[0] = TYPE_FLYING }, // Atk 90->100, Spe 100->115, Slot 2: None->Technician, Type1 Normal→Flying (now pure Flying)
    [SPECIES_ARBOK] = { .baseHP = 75, .baseDefense = 75, .abilities[2] = ABILITY_STRONG_JAW, .types[1] = TYPE_DARK, .itemRare = ITEM_POISON_BARB }, // HP 60->75, Def 69->75, Hidden: Unnerve->Strong Jaw, Type2 Poison→Dark, Rare None→Poison Barb
    [SPECIES_PIKACHU] = { .baseAttack = 50, .baseSpAttack = 55, .abilities[1] = ABILITY_LIGHTNING_ROD, .itemCommon = ITEM_ORAN_BERRY }, // Atk 55->50, SpA 50->55, Slot 2: None->Lightning Rod, Common None→Oran Berry
    [SPECIES_PIKACHU_PARTNER] = { .baseHP = 75, .baseAttack = 85, .baseDefense = 80, .baseSpeed = 120, .baseSpAttack = 110, .baseSpDefense = 80 }, // HP 35->75, Atk 55->85, Def 40->80, Spe 90->120, SpA 50->110, SpD 50->80
    [SPECIES_RAICHU] = { .baseHP = 70, .baseAttack = 100, .baseSpAttack = 110, .abilities[1] = ABILITY_LIGHTNING_ROD, .itemCommon = ITEM_ORAN_BERRY, .itemRare = ITEM_LIGHT_BALL }, // HP 60->70, Atk 90->100, SpA 90->110, Slot 2: None->Lightning Rod, Common None→Oran Berry, Rare None→Light Ball
    [SPECIES_RAICHU_ALOLA] = { .baseSpAttack = 110 }, // SpA 95->110
    [SPECIES_SANDSHREW_ALOLA] = { .abilities[0] = ABILITY_SLUSH_RUSH, .abilities[1] = ABILITY_ICE_BODY, .abilities[2] = ABILITY_SNOW_CLOAK }, // Slot 1: Snow Cloak->Slush Rush, Slot 2: None->Ice Body, Hidden: Slush Rush->Snow Cloak
    [SPECIES_SANDSLASH] = { .baseAttack = 110, .baseDefense = 120, .baseSpAttack = 25 }, // Atk 100->110, Def 110->120, SpA 45->25
    [SPECIES_SANDSLASH_ALOLA] = { .baseAttack = 110, .abilities[0] = ABILITY_SLUSH_RUSH, .abilities[2] = ABILITY_ICE_SCALES }, // Atk 100->110, Slot 1: Snow Cloak->Slush Rush, Hidden: Slush Rush->Ice Scales
    [SPECIES_NIDOKING] = { .baseAttack = 92, .baseSpAttack = 95 }, // Atk 102->92, SpA 85->95
    [SPECIES_CLEFAIRY] = { .itemCommon = ITEM_LEPPA_BERRY }, // Common None→Leppa Berry
    [SPECIES_CLEFABLE] = { .baseAttack = 60, .baseDefense = 83, .itemCommon = ITEM_LEPPA_BERRY }, // Atk 70->60, Def 73->83, Common None→Leppa Berry
    [SPECIES_VULPIX] = { .itemCommon = ITEM_RAWST_BERRY }, // Common None→Rawst Berry
    [SPECIES_NINETALES] = { .itemCommon = ITEM_RAWST_BERRY }, // Common None→Rawst Berry
    [SPECIES_JIGGLYPUFF] = { .itemCommon = ITEM_ORAN_BERRY }, // Common None→Oran Berry
    [SPECIES_WIGGLYTUFF] = { .abilities[0] = ABILITY_SHEER_FORCE, .itemCommon = ITEM_ORAN_BERRY }, // Slot 1: Cute Charm->Sheer Force, Common None→Oran Berry
    [SPECIES_ZUBAT] = { .abilities[1] = ABILITY_CORROSION }, // Slot 2: None->Corrosion
    [SPECIES_GOLBAT] = { .abilities[1] = ABILITY_CORROSION }, // Slot 2: None->Corrosion
    [SPECIES_PARASECT] = { .baseHP = 80, .baseAttack = 110 }, // HP 60->80, Atk 95->110
    [SPECIES_VENOMOTH] = { .baseDefense = 65 }, // Def 60->65
    [SPECIES_MEOWTH] = { .baseHP = 50, .baseAttack = 55, .itemRare = ITEM_AMULET_COIN }, // HP 40->50, Atk 45->55, Rare Quick Claw→Amulet Coin
    [SPECIES_PERSIAN] = { .baseHP = 70, .baseAttack = 80, .baseSpeed = 120, .baseSpAttack = 60, .itemCommon = ITEM_NUGGET, .itemRare = ITEM_NUGGET }, // HP 65->70, Atk 70->80, Spe 115->120, SpA 65->60, Common None→Nugget, Rare Quick Claw→Nugget (always held)
    [SPECIES_GOLDUCK] = { .baseAttack = 78, .baseDefense = 82, .baseSpeed = 100, .baseSpAttack = 100, .types[1] = TYPE_PSYCHIC }, // Atk 82->78, Def 78->82, Spe 85->100, SpA 95->100, Type2 Water→Psychic
    [SPECIES_MANKEY] = { .itemCommon = ITEM_PAYAPA_BERRY }, // Common None→Payapa Berry
    [SPECIES_PRIMEAPE] = { .itemCommon = ITEM_PAYAPA_BERRY, .itemRare = ITEM_EXPERT_BELT }, // Common None→Payapa Berry, Rare None→Expert Belt
    [SPECIES_VICTREEBEL] = { .baseDefense = 70, .baseSpDefense = 75 }, // Def 65->70, SpD 70->75
    [SPECIES_TENTACRUEL] = { .baseAttack = 60, .baseSpAttack = 90 }, // Atk 70->60, SpA 80->90
    [SPECIES_GOLEM_ALOLA] = { .abilities[1] = ABILITY_ROCK_HEAD }, // Slot 2: Sturdy->Rock Head
    [SPECIES_PONYTA] = { .itemRare = ITEM_FIRE_GEM }, // Rare None→Fire Gem
    [SPECIES_RAPIDASH] = { .baseSpeed = 125, .baseSpAttack = 60, .abilities[0] = ABILITY_RECKLESS, .types[1] = TYPE_FAIRY, .itemCommon = ITEM_FIRE_GEM, .itemRare = ITEM_FIRE_GEM }, // Spe 105->125, SpA 80->60, Slot 1: Run Away->Reckless, Type2 Fire→Fairy, Common None→Fire Gem, Rare None→Fire Gem (always held)
    [SPECIES_MAGNEMITE] = { .itemRare = ITEM_MAGNET }, // Rare Metal Coat→Magnet
    [SPECIES_MAGNETON] = { .itemRare = ITEM_MAGNET }, // Rare Metal Coat→Magnet
    [SPECIES_FARFETCHD] = { .baseHP = 75, .baseAttack = 110, .baseDefense = 70, .baseSpeed = 100, .baseSpDefense = 77, .abilities[0] = ABILITY_DEFIANT, .abilities[1] = ABILITY_JUSTIFIED, .abilities[2] = ABILITY_SHARPNESS, .types[0] = TYPE_FIGHTING }, // HP 52->75, Atk 90->110, Def 55->70, Spe 60->100, SpD 62->77, Slot 1: Keen Eye->Defiant, Slot 2: Inner Focus->Justified, Hidden: Defiant->Sharpness, Type1 Normal→Fighting
    [SPECIES_FARFETCHD_GALAR] = { .abilities[1] = ABILITY_JUSTIFIED }, // Slot 2: None->Justified
    [SPECIES_DODRIO] = { .abilities[0] = ABILITY_ROCK_HEAD }, // Slot 1: Run Away->Rock Head
    [SPECIES_SEEL] = { .abilities[1] = ABILITY_ICE_BODY, .abilities[2] = ABILITY_HYDRATION, .itemCommon = ITEM_ASPEAR_BERRY }, // Slot 2: Hydration->Ice Body, Hidden: Ice Body->Hydration, Common None→Aspear Berry
    [SPECIES_DEWGONG] = { .baseAttack = 50, .baseSpAttack = 90, .abilities[1] = ABILITY_ICE_BODY, .abilities[2] = ABILITY_ICE_SCALES, .itemCommon = ITEM_ASPEAR_BERRY, .itemRare = ITEM_NEVER_MELT_ICE }, // Atk 70->50, SpA 70->90, Slot 2: Hydration->Ice Body, Hidden: Ice Body->Ice Scales, Common None→Aspear Berry, Rare None→Never-Melt Ice
    [SPECIES_MUK] = { .abilities[0] = ABILITY_REGENERATOR, .abilities[1] = ABILITY_GOOEY, .itemCommon = ITEM_BLACK_SLUDGE, .itemRare = ITEM_TOXIC_ORB }, // Slot 1: Stench->Regenerator, Slot 2: Sticky Hold->Gooey, Common None→Black Sludge, Rare Black Sludge→Toxic Orb
    [SPECIES_MUK_ALOLA] = { .itemCommon = ITEM_BLACK_SLUDGE, .itemRare = ITEM_TOXIC_ORB }, // Common None→Black Sludge, Rare Black Sludge→Toxic Orb
    [SPECIES_GASTLY] = { .abilities[0] = ABILITY_CURSED_BODY, .abilities[1] = ABILITY_LEVITATE }, // Slot 1: Levitate->Cursed Body, Slot 2: None->Levitate
    [SPECIES_HAUNTER] = { .abilities[0] = ABILITY_CURSED_BODY, .abilities[1] = ABILITY_LEVITATE, .itemRare = ITEM_SPELL_TAG }, // Slot 1: Levitate->Cursed Body, Slot 2: None->Levitate, Rare None→Spell Tag
    [SPECIES_GENGAR] = { .abilities[1] = ABILITY_LEVITATE, .itemRare = ITEM_SPELL_TAG }, // Slot 2: None->Levitate, Rare None→Spell Tag
    [SPECIES_ONIX] = { .abilities[2] = ABILITY_SAND_SPIT, .itemRare = ITEM_HARD_STONE }, // Hidden: Weak Armor->Sand Spit, Rare None→Hard Stone
    [SPECIES_HYPNO] = { .abilities[2] = ABILITY_BAD_DREAMS }, // Hidden: Inner Focus->Bad Dreams
    [SPECIES_VOLTORB] = { .abilities[2] = ABILITY_GALVANIZE, .itemRare = ITEM_ELECTRIC_GEM }, // Hidden: Aftermath->Galvanize, Rare None→Electric Gem
    [SPECIES_ELECTRODE] = { .baseAttack = 55, .abilities[2] = ABILITY_GALVANIZE, .itemCommon = ITEM_ELECTRIC_GEM, .itemRare = ITEM_ELECTRIC_GEM }, // Atk 50->55, Hidden: Aftermath->Galvanize, Common None→Electric Gem, Rare None→Electric Gem (always held)
    [SPECIES_HITMONLEE] = { .abilities[2] = ABILITY_STRIKER }, // Hidden: Unburden->Striker
    [SPECIES_HITMONCHAN] = { .baseAttack = 115 }, // Atk 105->115
    [SPECIES_WEEZING_GALAR] = { .abilities[0] = ABILITY_WHITE_SMOKE }, // Slot 1: Levitate->White Smoke
    [SPECIES_CHANSEY] = { .itemCommon = ITEM_OVAL_STONE, .itemRare = ITEM_LUCKY_EGG }, // Common Oval Stone→Oval Stone, Rare None→Lucky Egg
    [SPECIES_TANGELA] = { .itemRare = ITEM_BIG_ROOT }, // Rare None→Big Root
    [SPECIES_KANGASKHAN] = { .abilities[0] = ABILITY_INNER_FOCUS, .abilities[2] = ABILITY_PARENTAL_BOND }, // Slot 1: Early Bird->Inner Focus, Hidden: Inner Focus->Parental Bond
    [SPECIES_STARYU] = { .baseAttack = 40, .baseSpAttack = 75 }, // Atk 45->40, SpA 70->75
    [SPECIES_STARMIE] = { .baseAttack = 70, .baseSpAttack = 105 }, // Atk 75->70, SpA 100->105
    [SPECIES_MR_MIME] = { .itemRare = ITEM_LEPPA_BERRY }, // Rare None→Leppa Berry
    [SPECIES_JYNX] = { .baseDefense = 50, .baseSpeed = 100, .itemCommon = ITEM_ASPEAR_BERRY, .itemRare = ITEM_ASPEAR_BERRY }, // Def 35->50, Spe 95->100, Common None→Aspear Berry, Rare None→Aspear Berry (always held)
    [SPECIES_TAUROS] = { .baseSpAttack = 70 }, // SpA 40->70
    [SPECIES_MAGIKARP] = { .abilities[1] = ABILITY_RATTLED }, // Slot 2: None->Rattled
    [SPECIES_GYARADOS] = { .abilities[1] = ABILITY_MOXIE }, // Slot 2: None->Moxie
    [SPECIES_DITTO] = { .baseHP = 70, .itemCommon = ITEM_EVERSTONE, .itemRare = ITEM_DESTINY_KNOT }, // HP 48->70, Common Quick Powder→Everstone, Rare Metal Powder→Destiny Knot
    [SPECIES_JOLTEON] = { .baseAttack = 60, .baseDefense = 65 }, // Atk 65->60, Def 60->65
    [SPECIES_FLAREON] = { .baseSpeed = 95, .baseSpAttack = 65, .baseSpDefense = 100 }, // Spe 65->95, SpA 95->65, SpD 110->100
    [SPECIES_KABUTOPS] = { .abilities[2] = ABILITY_SHARPNESS }, // Hidden: Weak Armor->Sharpness
    [SPECIES_ARTICUNO] = { .baseAttack = 70, .baseSpeed = 105, .abilities[1] = ABILITY_SNOW_CLOAK, .abilities[2] = ABILITY_SHIELD_DUST }, // Atk 85->70, Spe 85->105, Slot 2: None->Snow Cloak, Hidden: Snow Cloak->Shield Dust
    [SPECIES_ZAPDOS] = { .abilities[1] = ABILITY_LIGHTNING_ROD }, // Slot 2: None->Lightning Rod
    [SPECIES_MOLTRES] = { .baseAttack = 80, .baseDefense = 95, .baseSpeed = 95, .baseSpDefense = 95, .abilities[1] = ABILITY_FLAME_BODY }, // Atk 100->80, Def 90->95, Spe 90->95, SpD 85->95, Slot 2: None->Flame Body
    [SPECIES_MEWTWO] = { .itemCommon = ITEM_MEWTWONITE_X, .itemRare = ITEM_MEWTWONITE_Y }, // Mewtwonite X / Mewtwonite Y, same as vanilla (R.O.W.E. had Mewtwonite Y always held)
    [SPECIES_CHIKORITA] = { .abilities[1] = ABILITY_LEAF_GUARD }, // Slot 2: None->Leaf Guard
    [SPECIES_BAYLEEF] = { .abilities[1] = ABILITY_LEAF_GUARD }, // Slot 2: None->Leaf Guard
    [SPECIES_MEGANIUM] = { .abilities[1] = ABILITY_TRIAGE, .abilities[2] = ABILITY_TRIAGE }, // Slot 2: None->Triage, Hidden: Leaf Guard->Triage
    [SPECIES_CYNDAQUIL] = { .abilities[1] = ABILITY_FLASH_FIRE }, // Slot 2: None->Flash Fire
    [SPECIES_QUILAVA] = { .abilities[1] = ABILITY_FLASH_FIRE }, // Slot 2: None->Flash Fire
    [SPECIES_TYPHLOSION] = { .abilities[1] = ABILITY_FLASH_FIRE, .abilities[2] = ABILITY_FRISK }, // Slot 2: None->Flash Fire, Hidden: Flash Fire->Frisk
    [SPECIES_TOTODILE] = { .abilities[1] = ABILITY_SHEER_FORCE }, // Slot 2: None->Sheer Force
    [SPECIES_CROCONAW] = { .abilities[1] = ABILITY_SHEER_FORCE }, // Slot 2: None->Sheer Force
    [SPECIES_FERALIGATR] = { .abilities[1] = ABILITY_SHEER_FORCE }, // Slot 2: None->Sheer Force
    [SPECIES_SENTRET] = { .itemRare = ITEM_ORAN_BERRY }, // Rare None→Oran Berry
    [SPECIES_FURRET] = { .abilities[2] = ABILITY_ADAPTABILITY, .itemCommon = ITEM_ORAN_BERRY, .itemRare = ITEM_SITRUS_BERRY }, // Hidden: Frisk->Adaptability, Common None→Oran Berry, Rare None→Sitrus Berry
    [SPECIES_NOCTOWL] = { .baseHP = 110, .baseSpeed = 80, .baseSpAttack = 90, .baseSpDefense = 100, .types[0] = TYPE_PSYCHIC }, // HP 100->110, Spe 70->80, SpA 86->90, SpD 96->100, Type1 Normal→Psychic
    [SPECIES_LEDYBA] = { .baseHP = 45, .baseAttack = 50, .baseSpAttack = 30, .baseSpDefense = 65, .abilities[1] = ABILITY_SKILL_LINK }, // HP 40->45, Atk 20->50, SpA 40->30, SpD 80->65, Slot 2: Early Bird->Skill Link
    [SPECIES_LEDIAN] = { .baseHP = 60, .baseAttack = 95, .baseSpAttack = 35, .abilities[1] = ABILITY_SKILL_LINK }, // HP 55->60, Atk 35->95, SpA 55->35, Slot 2: Early Bird->Skill Link
    [SPECIES_SPINARAK] = { .baseHP = 50, .baseSpeed = 45 }, // HP 40->50, Spe 30->45
    [SPECIES_ARIADOS] = { .baseAttack = 100, .baseSpeed = 70, .baseSpAttack = 45, .abilities[1] = ABILITY_NO_GUARD }, // Atk 90->100, Spe 40->70, SpA 60->45, Slot 2: Insomnia->No Guard
    [SPECIES_CROBAT] = { .baseSpAttack = 90, .abilities[1] = ABILITY_CORROSION }, // SpA 70->90, Slot 2: None->Corrosion
    [SPECIES_LANTURN] = { .baseAttack = 50, .baseDefense = 65, .baseSpeed = 70, .baseSpAttack = 90 }, // Atk 58->50, Def 58->65, Spe 67->70, SpA 76->90
    [SPECIES_PICHU] = { .abilities[1] = ABILITY_LIGHTNING_ROD, .itemCommon = ITEM_ORAN_BERRY }, // Slot 2: None->Lightning Rod, Common None→Oran Berry
    [SPECIES_PICHU_SPIKY_EARED] = { .genderRatio = CUSTOM_GENDER_RATIO(MON_FEMALE) }, // Gender 50% female→always female
    [SPECIES_CLEFFA] = { .itemCommon = ITEM_LEPPA_BERRY }, // Common None→Leppa Berry
    [SPECIES_IGGLYBUFF] = { .itemCommon = ITEM_ORAN_BERRY }, // Common None→Oran Berry
    [SPECIES_XATU] = { .baseSpeed = 105, .baseSpAttack = 105 }, // Spe 95->105, SpA 95->105
    [SPECIES_MAREEP] = { .abilities[1] = ABILITY_FLUFFY }, // Slot 2: None->Fluffy
    [SPECIES_FLAAFFY] = { .abilities[1] = ABILITY_ILLUMINATE }, // Slot 2: None->Illuminate
    [SPECIES_AMPHAROS] = { .abilities[1] = ABILITY_ILLUMINATE, .types[1] = TYPE_DRAGON }, // Slot 2: None->Illuminate, Type2 Electric→Dragon
    [SPECIES_BELLOSSOM] = { .baseHP = 85, .baseAttack = 70, .baseSpAttack = 100, .baseSpDefense = 90, .abilities[1] = ABILITY_HEALER, .abilities[2] = ABILITY_DANCER, .types[1] = TYPE_FAIRY }, // HP 75->85, Atk 80->70, SpA 90->100, SpD 100->90, Slot 2: None->Healer, Hidden: Healer->Dancer, Type2 Grass→Fairy
    [SPECIES_SUDOWOODO] = { .baseHP = 90, .abilities[2] = ABILITY_PRANKSTER, .itemCommon = ITEM_ROCK_GEM, .itemRare = ITEM_ROCK_GEM }, // HP 70->90, Hidden: Rattled->Prankster, Common None→Rock Gem, Rare None→Rock Gem (always held)
    [SPECIES_POLITOED] = { .baseSpAttack = 100, .abilities[1] = ABILITY_DRIZZLE, .types[1] = TYPE_NORMAL }, // SpA 90->100, Slot 2: Damp->Drizzle, Type2 Water→Normal
    [SPECIES_JUMPLUFF] = { .baseAttack = 85, .baseSpAttack = 35, .abilities[2] = ABILITY_AERILATE }, // Atk 55->85, SpA 55->35, Hidden: Infiltrator->Aerilate
    [SPECIES_SUNKERN] = { .baseHP = 40, .baseDefense = 35, .baseSpAttack = 50, .baseSpDefense = 70, .itemRare = ITEM_GREEN_SHARD }, // HP 30->40, Def 30->35, SpA 30->50, SpD 30->70, Rare None→Green Shard
    [SPECIES_SUNFLORA] = { .baseHP = 95, .baseDefense = 85, .baseSpeed = 65, .baseSpAttack = 115, .abilities[2] = ABILITY_FLOWER_GIFT, .itemCommon = ITEM_GREEN_SHARD, .itemRare = ITEM_GREEN_SHARD }, // HP 75->95, Def 55->85, Spe 30->65, SpA 105->115, Hidden: Early Bird->Flower Gift, Common None→Green Shard, Rare None→Green Shard (always held)
    [SPECIES_QUAGSIRE] = { .baseHP = 100, .baseDefense = 90 }, // HP 95->100, Def 85->90
    [SPECIES_MISDREAVUS] = { .abilities[0] = ABILITY_CURSED_BODY, .abilities[1] = ABILITY_PIXILATE, .types[1] = TYPE_FAIRY, .itemRare = ITEM_SPELL_TAG }, // Slot 1: Levitate->Cursed Body, Slot 2: None->Pixilate, Type2 Ghost→Fairy, Rare None→Spell Tag
    [SPECIES_UNOWN] = { .baseHP = 80, .baseAttack = 70, .baseDefense = 80, .baseSpeed = 95, .baseSpAttack = 95, .baseSpDefense = 80, .abilities[0] = ABILITY_PSYCHIC_SURGE, .evYield[STAT_ATK] = CUSTOM_EV_YIELD(0), .evYield[STAT_SPEED] = CUSTOM_EV_YIELD(1), .catchRate = 150, .expYield = 200 }, // HP 48->80, Atk 72->70, Def 48->80, Spe 48->95, SpA 72->95, SpD 48->80, Slot 1: Levitate->Psychic Surge, EV Atk 1→0, EV Spe 0→1, Catch rate 225→150, Exp yield 118→200
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
    [SPECIES_GIRAFARIG] = { .abilities[0] = ABILITY_SAP_SIPPER, .itemRare = ITEM_PERSIM_BERRY }, // Slot 1: Inner Focus->Sap Sipper, Rare None→Persim Berry
    [SPECIES_PINECO] = { .itemRare = ITEM_BUG_GEM }, // Rare None→Bug Gem
    [SPECIES_FORRETRESS] = { .itemCommon = ITEM_BUG_GEM, .itemRare = ITEM_BUG_GEM }, // Common None→Bug Gem, Rare None→Bug Gem (always held)
    [SPECIES_DUNSPARCE] = { .baseAttack = 80, .baseDefense = 80, .baseSpeed = 65, .baseSpDefense = 75 }, // Atk 70->80, Def 70->80, Spe 45->65, SpD 65->75
    [SPECIES_STEELIX] = { .abilities[1] = ABILITY_SHEER_FORCE, .abilities[2] = ABILITY_SAND_SPIT }, // Slot 2: Sturdy->Sheer Force, Hidden: Sheer Force->Sand Spit
    [SPECIES_GRANBULL] = { .abilities[1] = ABILITY_ANGER_POINT, .abilities[2] = ABILITY_STRONG_JAW, .types[1] = TYPE_FIGHTING }, // Slot 2: Quick Feet->Anger Point, Hidden: Rattled->Strong Jaw, Type2 Fairy→Fighting
    [SPECIES_QWILFISH] = { .baseAttack = 105, .abilities[0] = ABILITY_POISON_TOUCH }, // Atk 95->105, Slot 1: Poison Point->Poison Touch
    [SPECIES_SHUCKLE] = { .abilities[1] = ABILITY_SOLID_ROCK }, // Slot 2: Gluttony->Solid Rock
    [SPECIES_HERACROSS] = { .abilities[0] = ABILITY_MOXIE, .abilities[2] = ABILITY_SWARM }, // Slot 1: Swarm->Moxie, Hidden: Moxie->Swarm
    [SPECIES_SNEASEL] = { .abilities[1] = ABILITY_TECHNICIAN, .itemCommon = ITEM_GRIP_CLAW }, // Slot 2: Keen Eye->Technician, Common None→Grip Claw
    [SPECIES_TEDDIURSA] = { .itemCommon = ITEM_ORAN_BERRY, .itemRare = ITEM_SITRUS_BERRY }, // Common None→Oran Berry, Rare Honey→Sitrus Berry
    [SPECIES_URSARING] = { .types[1] = TYPE_GROUND, .itemCommon = ITEM_ORAN_BERRY, .itemRare = ITEM_SITRUS_BERRY }, // Type2 Normal→Ground, Common None→Oran Berry, Rare None→Sitrus Berry
    [SPECIES_SLUGMA] = { .baseHP = 50, .baseDefense = 60, .baseSpeed = 45, .baseSpDefense = 50 }, // HP 40->50, Def 40->60, Spe 20->45, SpD 40->50
    [SPECIES_MAGCARGO] = { .baseHP = 80, .baseAttack = 40, .baseDefense = 110, .baseSpeed = 60, .baseSpDefense = 100, .abilities[0] = ABILITY_SOLID_ROCK, .abilities[2] = ABILITY_SIMPLE }, // HP 60->80, Atk 50->40, Def 120->110, Spe 30->60, SpD 80->100, Slot 1: Magma Armor->Solid Rock, Hidden: Weak Armor->Simple
    [SPECIES_SWINUB] = { .itemCommon = ITEM_ASPEAR_BERRY }, // Common None→Aspear Berry
    [SPECIES_PILOSWINE] = { .itemCommon = ITEM_ASPEAR_BERRY, .itemRare = ITEM_NEVER_MELT_ICE }, // Common None→Aspear Berry, Rare None→Never-Melt Ice
    [SPECIES_CORSOLA] = { .itemRare = ITEM_RED_SHARD }, // Rare Luminous Moss→Red Shard
    [SPECIES_CORSOLA_GALAR] = { .itemRare = ITEM_GHOST_GEM }, // Rare None→Ghost Gem
    [SPECIES_OCTILLERY] = { .abilities[0] = ABILITY_SKILL_LINK, .abilities[2] = ABILITY_MEGA_LAUNCHER }, // Slot 1: Suction Cups->Skill Link, Hidden: Moody->Mega Launcher
    [SPECIES_DELIBIRD] = { .baseAttack = 95, .baseSpeed = 95, .abilities[0] = ABILITY_REFRIGERATE, .abilities[2] = ABILITY_UNBURDEN }, // Atk 55->95, Spe 75->95, Slot 1: Vital Spirit->Refrigerate, Hidden: Insomnia->Unburden
    [SPECIES_MANTINE] = { .baseSpAttack = 90 }, // SpA 80->90
    [SPECIES_KINGDRA] = { .baseAttack = 100, .baseSpAttack = 100 }, // Atk 95->100, SpA 95->100
    [SPECIES_PHANPY] = { .itemRare = ITEM_PASSHO_BERRY }, // Rare None→Passho Berry
    [SPECIES_DONPHAN] = { .abilities[1] = ABILITY_SAND_VEIL, .abilities[2] = ABILITY_TECHNICIAN, .itemRare = ITEM_PASSHO_BERRY }, // Slot 2: None->Sand Veil, Hidden: Sand Veil->Technician, Rare None→Passho Berry
    [SPECIES_PORYGON2] = { .itemCommon = ITEM_NORMAL_GEM, .itemRare = ITEM_UPGRADE }, // Common None→Normal Gem, Rare None→Upgrade
    [SPECIES_STANTLER] = { .abilities[1] = ABILITY_RECKLESS, .types[1] = TYPE_PSYCHIC }, // Slot 2: Frisk->Reckless, Type2 Normal→Psychic
    [SPECIES_SMOOCHUM] = { .itemCommon = ITEM_ASPEAR_BERRY, .itemRare = ITEM_ASPEAR_BERRY }, // Common None→Aspear Berry, Rare None→Aspear Berry (always held)
    [SPECIES_MILTANK] = { .baseAttack = 90 }, // Atk 80->90
    [SPECIES_BLISSEY] = { .itemCommon = ITEM_LUCKY_EGG, .itemRare = ITEM_LUCKY_EGG }, // Common Oval Stone→Lucky Egg, Rare None→Lucky Egg (always held)
    [SPECIES_RAIKOU] = { .abilities[1] = ABILITY_VOLT_ABSORB }, // Slot 2: None->Volt Absorb
    [SPECIES_ENTEI] = { .abilities[1] = ABILITY_FLASH_FIRE }, // Slot 2: None->Flash Fire
    [SPECIES_SUICUNE] = { .abilities[1] = ABILITY_WATER_ABSORB }, // Slot 2: None->Water Absorb
    [SPECIES_TYRANITAR] = { .itemCommon = ITEM_SMOOTH_ROCK }, // Common None→Smooth Rock
    [SPECIES_TREECKO] = { .baseAttack = 65, .baseSpAttack = 45, .abilities[1] = ABILITY_UNBURDEN }, // Atk 45->65, SpA 65->45, Slot 2: None->Unburden
    [SPECIES_GROVYLE] = { .abilities[1] = ABILITY_LIGHTNING_ROD, .types[1] = TYPE_DRAGON }, // Slot 2: None->Lightning Rod, Type2 Grass→Dragon
    [SPECIES_SCEPTILE] = { .baseSpAttack = 110, .abilities[1] = ABILITY_LIGHTNING_ROD, .types[1] = TYPE_DRAGON }, // SpA 105->110, Slot 2: None->Lightning Rod, Type2 Grass→Dragon
    [SPECIES_MUDKIP] = { .baseAttack = 75, .baseSpAttack = 45, .abilities[1] = ABILITY_SWIFT_SWIM }, // Atk 70->75, SpA 50->45, Slot 2: None->Swift Swim
    [SPECIES_MARSHTOMP] = { .baseAttack = 90, .baseSpAttack = 55, .abilities[1] = ABILITY_SWIFT_SWIM }, // Atk 85->90, SpA 60->55, Slot 2: None->Swift Swim
    [SPECIES_SWAMPERT] = { .baseAttack = 120, .baseSpeed = 70, .baseSpAttack = 65, .abilities[1] = ABILITY_SWIFT_SWIM }, // Atk 110->120, Spe 60->70, SpA 85->65, Slot 2: None->Swift Swim
    [SPECIES_SWAMPERT_MEGA] = { .baseAttack = 160, .baseSpAttack = 85 }, // Atk 150->160, SpA 95->85
    [SPECIES_POOCHYENA] = { .itemRare = ITEM_PECHA_BERRY }, // Rare None→Pecha Berry
    [SPECIES_MIGHTYENA] = { .baseAttack = 110, .itemRare = ITEM_PECHA_BERRY }, // Atk 90->110, Rare None→Pecha Berry
    [SPECIES_LINOONE] = { .baseHP = 80, .baseAttack = 100, .baseDefense = 65, .abilities[0] = ABILITY_SCRAPPY }, // HP 78->80, Atk 70->100, Def 61->65, Slot 1: Pickup->Scrappy
    [SPECIES_WURMPLE] = { .abilities[1] = ABILITY_RUN_AWAY, .abilities[2] = ABILITY_POISON_POINT }, // Slot 2: None->Run Away, Hidden: Run Away->Poison Point
    [SPECIES_BEAUTIFLY] = { .baseSpeed = 90, .baseSpAttack = 110, .abilities[1] = ABILITY_RIVALRY, .abilities[2] = ABILITY_HONEY_GATHER }, // Spe 65->90, SpA 100->110, Slot 2: None->Rivalry, Hidden: Rivalry->Honey Gather
    [SPECIES_DUSTOX] = { .baseDefense = 60, .baseSpeed = 95, .baseSpAttack = 95, .baseSpDefense = 60, .abilities[1] = ABILITY_COMPOUND_EYES, .abilities[2] = ABILITY_MERCILESS }, // Def 70->60, Spe 65->95, SpA 50->95, SpD 90->60, Slot 2: None->Compound Eyes, Hidden: Compound Eyes->Merciless
    [SPECIES_LUDICOLO] = { .baseSpeed = 90, .baseSpAttack = 100 }, // Spe 70->90, SpA 90->100
    [SPECIES_SHIFTRY] = { .baseAttack = 105, .baseSpAttack = 105 }, // Atk 100->105, SpA 90->105
    [SPECIES_TAILLOW] = { .baseAttack = 60, .baseSpAttack = 55, .itemRare = ITEM_CHARTI_BERRY }, // Atk 55->60, SpA 30->55, Rare None→Charti Berry
    [SPECIES_SWELLOW] = { .baseAttack = 100, .baseSpAttack = 90, .itemRare = ITEM_CHARTI_BERRY }, // Atk 85->100, SpA 75->90, Rare None→Charti Berry
    [SPECIES_WINGULL] = { .baseAttack = 25, .baseSpAttack = 60 }, // Atk 30->25, SpA 55->60
    [SPECIES_PELIPPER] = { .baseHP = 65, .baseAttack = 40, .baseDefense = 110, .baseSpAttack = 100, .baseSpDefense = 80, .itemCommon = ITEM_DAMP_ROCK, .itemRare = ITEM_LUCKY_EGG }, // HP 60->65, Atk 50->40, Def 100->110, SpA 95->100, SpD 70->80, Common Pretty Feather→Damp Rock, Rare None→Lucky Egg
    [SPECIES_KIRLIA] = { .baseAttack = 30, .baseDefense = 40 }, // Atk 35->30, Def 35->40
    [SPECIES_GARDEVOIR] = { .baseAttack = 60, .baseSpeed = 100 }, // Atk 65->60, Spe 80->100
    [SPECIES_GARDEVOIR_MEGA] = { .baseAttack = 60, .baseDefense = 90, .baseSpAttack = 175, .baseSpDefense = 140 }, // Atk 85->60, Def 65->90, SpA 165->175, SpD 135->140
    [SPECIES_SURSKIT] = { .abilities[1] = ABILITY_RAIN_DISH, .abilities[2] = ABILITY_WATER_VEIL }, // Slot 2: None->Rain Dish, Hidden: Rain Dish->Water Veil
    [SPECIES_MASQUERAIN] = { .baseDefense = 70, .baseSpeed = 100, .baseSpAttack = 120, .baseSpDefense = 110, .abilities[1] = ABILITY_KEEN_EYE, .abilities[2] = ABILITY_KEEN_EYE, .types[1] = TYPE_WATER, .evYield[STAT_SPATK] = CUSTOM_EV_YIELD(2), .evYield[STAT_SPDEF] = CUSTOM_EV_YIELD(0) }, // Def 62->70, Spe 80->100, SpA 100->120, SpD 82->110, Slot 2: None->Keen Eye, Hidden: Unnerve->Keen Eye, Type2 Flying→Water, EV SpA 1→2, EV SpD 1→0
    [SPECIES_SHROOMISH] = { .itemRare = ITEM_KEBIA_BERRY }, // Rare Big Mushroom→Kebia Berry
    [SPECIES_BRELOOM] = { .itemRare = ITEM_KEBIA_BERRY }, // Rare Big Mushroom→Kebia Berry
    [SPECIES_NINJASK] = { .baseAttack = 100 }, // Atk 90->100
    [SPECIES_SHEDINJA] = { .baseAttack = 100, .baseSpeed = 70 }, // Atk 90->100, Spe 40->70
    [SPECIES_WHISMUR] = { .itemRare = ITEM_CHESTO_BERRY }, // Rare None→Chesto Berry
    [SPECIES_LOUDRED] = { .itemRare = ITEM_CHESTO_BERRY }, // Rare None→Chesto Berry
    [SPECIES_EXPLOUD] = { .baseSpeed = 75, .baseSpAttack = 110, .itemRare = ITEM_CHESTO_BERRY }, // Spe 68->75, SpA 91->110, Rare None→Chesto Berry
    [SPECIES_MAKUHITA] = { .itemRare = ITEM_FIGHTING_GEM }, // Rare Black Belt→Fighting Gem
    [SPECIES_HARIYAMA] = { .baseDefense = 80, .baseSpDefense = 80, .itemCommon = ITEM_FIGHTING_GEM, .itemRare = ITEM_FIGHTING_GEM }, // Def 60->80, SpD 60->80, Common None→Fighting Gem, Rare King's Rock→Fighting Gem (always held)
    [SPECIES_SKITTY] = { .itemCommon = ITEM_PECHA_BERRY, .itemRare = ITEM_LEPPA_BERRY }, // Common None→Pecha Berry, Rare None→Leppa Berry
    [SPECIES_DELCATTY] = { .baseAttack = 95, .baseSpAttack = 65, .itemCommon = ITEM_NUGGET, .itemRare = ITEM_NUGGET }, // Atk 65->95, SpA 55->65, Common None→Nugget, Rare None→Nugget (always held)
    [SPECIES_SABLEYE] = { .baseHP = 70, .baseDefense = 80, .baseSpDefense = 80 }, // HP 50->70, Def 75->80, SpD 65->80
    [SPECIES_SABLEYE_MEGA] = { .baseHP = 70 }, // HP 50->70
    [SPECIES_MAWILE] = { .baseSpeed = 75, .itemCommon = ITEM_IRON_BALL, .itemRare = ITEM_OCCA_BERRY }, // Spe 50->75, Common None→Iron Ball, Rare Iron Ball→Occa Berry
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
    [SPECIES_CARVANHA] = { .itemRare = ITEM_BLUE_SHARD }, // Rare Deep Sea Tooth→Blue Shard
    [SPECIES_SHARPEDO] = { .abilities[1] = ABILITY_INTIMIDATE, .itemCommon = ITEM_BLUE_SHARD, .itemRare = ITEM_BLUE_SHARD }, // Slot 2: None->Intimidate, Common None→Blue Shard, Rare Deep Sea Tooth→Blue Shard (always held)
    [SPECIES_WAILORD] = { .baseHP = 200, .baseAttack = 60, .baseSpAttack = 110 }, // HP 170->200, Atk 90->60, SpA 90->110
    [SPECIES_NUMEL] = { .itemCommon = ITEM_RAWST_BERRY, .itemRare = ITEM_RED_SHARD }, // Common None→Rawst Berry, Rare None→Red Shard
    [SPECIES_CAMERUPT] = { .itemCommon = ITEM_RED_SHARD, .itemRare = ITEM_RED_SHARD }, // Common None→Red Shard, Rare None→Red Shard (always held)
    [SPECIES_TORKOAL] = { .baseHP = 90, .baseDefense = 120, .baseSpeed = 10, .baseSpDefense = 90, .itemCommon = ITEM_HEAT_ROCK, .itemRare = ITEM_ASSAULT_VEST }, // HP 70->90, Def 140->120, Spe 20->10, SpD 70->90, Common None→Heat Rock, Rare Charcoal→Assault Vest
    [SPECIES_SPOINK] = { .itemCommon = ITEM_PERSIM_BERRY, .itemRare = ITEM_TANGA_BERRY }, // Common None→Persim Berry, Rare None→Tanga Berry
    [SPECIES_GRUMPIG] = { .baseSpeed = 40, .baseSpAttack = 110, .abilities[2] = ABILITY_OWN_TEMPO, .itemCommon = ITEM_PERSIM_BERRY, .itemRare = ITEM_TANGA_BERRY }, // Spe 80->40, SpA 90->110, Hidden: Gluttony->Own Tempo, Common None→Persim Berry, Rare None→Tanga Berry
    [SPECIES_SPINDA] = { .baseHP = 80, .baseAttack = 95, .baseSpeed = 85, .types[1] = TYPE_PSYCHIC, .itemRare = ITEM_CHESTO_BERRY }, // HP 60->80, Atk 60->95, Spe 60->85, Type2 Normal→Psychic, Rare None→Chesto Berry
    [SPECIES_TRAPINCH] = { .abilities[0] = ABILITY_SHEER_FORCE, .abilities[1] = ABILITY_STRONG_JAW, .abilities[2] = ABILITY_ARENA_TRAP }, // Slot 1: Hyper Cutter->Sheer Force, Slot 2: Arena Trap->Strong Jaw, Hidden: Sheer Force->Arena Trap
    [SPECIES_VIBRAVA] = { .abilities[2] = ABILITY_ARENA_TRAP }, // Hidden: Levitate->Arena Trap
    [SPECIES_FLYGON] = { .baseHP = 90, .baseDefense = 90, .baseSpAttack = 130, .baseSpDefense = 90, .abilities[2] = ABILITY_SAND_FORCE }, // HP 80->90, Def 80->90, SpA 80->130, SpD 80->90, Hidden: Levitate->Sand Force
    [SPECIES_CACTURNE] = { .baseAttack = 130, .baseDefense = 75, .baseSpAttack = 80, .baseSpDefense = 70, .abilities[2] = ABILITY_ROUGH_SKIN }, // Atk 115->130, Def 60->75, SpA 115->80, SpD 60->70, Hidden: Water Absorb->Rough Skin
    [SPECIES_SWABLU] = { .abilities[1] = ABILITY_COTTON_DOWN, .itemRare = ITEM_DRAGON_GEM }, // Slot 2: None->Cotton Down, Rare None→Dragon Gem
    [SPECIES_ALTARIA] = { .baseAttack = 80, .baseSpAttack = 80, .abilities[1] = ABILITY_COTTON_DOWN, .itemCommon = ITEM_DRAGON_GEM, .itemRare = ITEM_DRAGON_GEM }, // Atk 70->80, SpA 70->80, Slot 2: None->Cotton Down, Common None→Dragon Gem, Rare None→Dragon Gem (always held)
    [SPECIES_ALTARIA_MEGA] = { .baseSpeed = 95, .baseSpDefense = 110 }, // Spe 80->95, SpD 105->110
    [SPECIES_ZANGOOSE] = { .baseHP = 75, .baseSpeed = 110, .abilities[1] = ABILITY_TOUGH_CLAWS }, // HP 73->75, Spe 90->110, Slot 2: None->Tough Claws
    [SPECIES_SEVIPER] = { .baseHP = 75, .baseSpeed = 85, .abilities[1] = ABILITY_INFILTRATOR, .itemCommon = ITEM_PERSIM_BERRY }, // HP 73->75, Spe 65->85, Slot 2: None->Infiltrator, Common None→Persim Berry
    [SPECIES_LUNATONE] = { .abilities[1] = ABILITY_INTIMIDATE }, // Slot 2: None->Intimidate
    [SPECIES_SOLROCK] = { .abilities[1] = ABILITY_SOLAR_POWER }, // Slot 2: None->Solar Power
    [SPECIES_WHISCASH] = { .baseHP = 120, .baseAttack = 95, .baseDefense = 78, .baseSpAttack = 78 }, // HP 110->120, Atk 78->95, Def 73->78, SpA 76->78
    [SPECIES_CORPHISH] = { .baseSpAttack = 35, .baseSpDefense = 50, .itemRare = ITEM_WATER_GEM }, // SpA 50->35, SpD 35->50, Rare None→Water Gem
    [SPECIES_CRAWDAUNT] = { .baseSpAttack = 55, .baseSpDefense = 90, .abilities[1] = ABILITY_ADAPTABILITY, .abilities[2] = ABILITY_SHELL_ARMOR, .itemCommon = ITEM_WATER_GEM, .itemRare = ITEM_WATER_GEM }, // SpA 90->55, SpD 55->90, Slot 2: Shell Armor->Adaptability, Hidden: Adaptability->Shell Armor, Common None→Water Gem, Rare None→Water Gem (always held)
    [SPECIES_BALTOY] = { .abilities[2] = ABILITY_MAGIC_GUARD }, // Hidden: None->Magic Guard
    [SPECIES_CLAYDOL] = { .abilities[2] = ABILITY_MAGIC_GUARD }, // Hidden: None->Magic Guard
    [SPECIES_CRADILY] = { .baseHP = 90, .baseAttack = 71, .baseSpeed = 30, .baseSpDefense = 130 }, // HP 86->90, Atk 81->71, Spe 43->30, SpD 107->130
    [SPECIES_ANORITH] = { .abilities[0] = ABILITY_SOLID_ROCK, .abilities[1] = ABILITY_TOUGH_CLAWS }, // Slot 1: Battle Armor->Solid Rock, Slot 2: None->Tough Claws
    [SPECIES_ARMALDO] = { .baseHP = 85, .baseSpeed = 75, .baseSpAttack = 40, .baseSpDefense = 85, .abilities[0] = ABILITY_SOLID_ROCK, .abilities[1] = ABILITY_TOUGH_CLAWS }, // HP 75->85, Spe 45->75, SpA 70->40, SpD 80->85, Slot 1: Battle Armor->Solid Rock, Slot 2: None->Tough Claws
    [SPECIES_MILOTIC] = { .abilities[1] = ABILITY_MULTISCALE }, // Slot 2: Competitive->Multiscale
    [SPECIES_KECLEON] = { .itemRare = ITEM_PERSIM_BERRY }, // Rare None→Persim Berry
    [SPECIES_BANETTE] = { .types[1] = TYPE_NORMAL }, // Type2 Ghost→Normal
    [SPECIES_BANETTE_MEGA] = { .types[1] = TYPE_NORMAL }, // Type2 Ghost→Normal
    [SPECIES_DUSKULL] = { .abilities[0] = ABILITY_PRANKSTER, .itemRare = ITEM_KASIB_BERRY }, // Slot 1: Levitate->Prankster, Rare Spell Tag→Kasib Berry
    [SPECIES_DUSCLOPS] = { .itemRare = ITEM_KASIB_BERRY }, // Rare Spell Tag→Kasib Berry
    [SPECIES_TROPIUS] = { .baseHP = 110, .baseDefense = 90, .baseSpeed = 30, .baseSpAttack = 90, .baseSpDefense = 100, .abilities[1] = ABILITY_THICK_FAT }, // HP 99->110, Def 83->90, Spe 51->30, SpA 72->90, SpD 87->100, Slot 2: Solar Power->Thick Fat
    [SPECIES_CHIMECHO] = { .baseHP = 80, .baseAttack = 40, .baseSpeed = 85, .itemCommon = ITEM_CLEANSE_TAG, .itemRare = ITEM_COLBUR_BERRY }, // HP 75->80, Atk 50->40, Spe 65->85, Common None→Cleanse Tag, Rare Cleanse Tag→Colbur Berry
    [SPECIES_ABSOL] = { .itemRare = ITEM_LIFE_ORB }, // Rare None→Life Orb
    [SPECIES_ABSOL_MEGA] = { .baseSpeed = 130, .baseSpAttack = 100 }, // Spe 115->130, SpA 115->100
    [SPECIES_SNORUNT] = { .itemCommon = ITEM_SNOWBALL, .itemRare = ITEM_BABIRI_BERRY }, // Common None→Snowball, Rare Snowball→Babiri Berry
    [SPECIES_GLALIE] = { .baseAttack = 100, .baseDefense = 90, .baseSpeed = 85, .baseSpAttack = 100, .baseSpDefense = 90, .abilities[0] = ABILITY_INTIMIDATE, .itemCommon = ITEM_SNOWBALL, .itemRare = ITEM_NEVER_MELT_ICE }, // Atk 80->100, Def 80->90, Spe 80->85, SpA 80->100, SpD 80->90, Slot 1: Inner Focus->Intimidate, Common None→Snowball, Rare None→Never-Melt Ice
    [SPECIES_GLALIE_MEGA] = { .baseDefense = 90, .baseSpeed = 120, .baseSpAttack = 100, .baseSpDefense = 90, .abilities[0] = ABILITY_SOLID_ROCK, .abilities[1] = ABILITY_SOLID_ROCK, .abilities[2] = ABILITY_SOLID_ROCK }, // Def 80->90, Spe 100->120, SpA 120->100, SpD 80->90, Slot 1: Refrigerate->Solid Rock, Slot 2: Refrigerate->Solid Rock, Hidden: Refrigerate->Solid Rock
    [SPECIES_WALREIN] = { .baseHP = 100, .baseAttack = 95, .baseDefense = 95, .baseSpAttack = 75, .baseSpDefense = 100, .abilities[2] = ABILITY_SLUSH_RUSH }, // HP 110->100, Atk 80->95, Def 90->95, SpA 95->75, SpD 90->100, Hidden: Oblivious->Slush Rush
    [SPECIES_CLAMPERL] = { .itemRare = ITEM_BLUE_SHARD }, // Rare Big Pearl→Blue Shard
    [SPECIES_RELICANTH] = { .baseSpeed = 75, .itemRare = ITEM_GREEN_SHARD }, // Spe 55->75, Rare Deep Sea Scale→Green Shard
    [SPECIES_LUVDISC] = { .baseHP = 60, .baseDefense = 70, .baseSpeed = 100, .baseSpAttack = 80, .baseSpDefense = 80, .abilities[1] = ABILITY_HYDRATION, .abilities[2] = ABILITY_MULTISCALE, .itemRare = ITEM_HEART_SCALE }, // HP 43->60, Def 55->70, Spe 97->100, SpA 40->80, SpD 65->80, Slot 2: None->Hydration, Hidden: Hydration->Multiscale, Rare None→Heart Scale (always held)
    [SPECIES_BAGON] = { .abilities[1] = ABILITY_SHEER_FORCE }, // Slot 2: None->Sheer Force
    [SPECIES_SHELGON] = { .abilities[1] = ABILITY_OVERCOAT }, // Slot 2: None->Overcoat
    [SPECIES_SALAMENCE] = { .abilities[1] = ABILITY_MOXIE }, // Slot 2: None->Moxie
    [SPECIES_BELDUM] = { .catchRate = 45 }, // Catch rate 3→45
    [SPECIES_METANG] = { .catchRate = 45 }, // Catch rate 3→45
    [SPECIES_METAGROSS] = { .abilities[1] = ABILITY_IRON_FIST, .catchRate = 45 }, // Slot 2: None->Iron Fist, Catch rate 3→45
    [SPECIES_LATIAS] = { .abilities = { ABILITY_LEVITATE, ABILITY_LEVITATE, ABILITY_LEVITATE }, .itemCommon = ITEM_LATIASITE, .itemRare = ITEM_LATIASITE }, // Slot 2: None->Levitate, Hidden: None->Levitate, Common None→Latiasite, Rare None→Latiasite (always held)
    [SPECIES_LATIAS_MEGA] = { .abilities = { ABILITY_LEVITATE, ABILITY_LEVITATE, ABILITY_LEVITATE } }, // Levitate in all slots (same as vanilla)
    [SPECIES_LATIOS] = { .abilities = { ABILITY_LEVITATE, ABILITY_LEVITATE, ABILITY_LEVITATE }, .itemCommon = ITEM_LATIOSITE, .itemRare = ITEM_LATIOSITE }, // Slot 2: None->Levitate, Hidden: None->Levitate, Common None→Latiosite, Rare None→Latiosite (always held)
    [SPECIES_LATIOS_MEGA] = { .abilities = { ABILITY_LEVITATE, ABILITY_LEVITATE, ABILITY_LEVITATE } }, // Levitate in all slots (same as vanilla)
    [SPECIES_TURTWIG] = { .abilities[1] = ABILITY_SHELL_ARMOR }, // Slot 2: None->Shell Armor
    [SPECIES_GROTLE] = { .abilities[1] = ABILITY_SHELL_ARMOR }, // Slot 2: None->Shell Armor
    [SPECIES_TORTERRA] = { .abilities[1] = ABILITY_SHELL_ARMOR }, // Slot 2: None->Shell Armor
    [SPECIES_CHIMCHAR] = { .abilities[1] = ABILITY_IRON_FIST }, // Slot 2: None->Iron Fist
    [SPECIES_MONFERNO] = { .abilities[1] = ABILITY_IRON_FIST }, // Slot 2: None->Iron Fist
    [SPECIES_INFERNAPE] = { .abilities[1] = ABILITY_IRON_FIST }, // Slot 2: None->Iron Fist
    [SPECIES_STARLY] = { .abilities[1] = ABILITY_RECKLESS, .itemRare = ITEM_YACHE_BERRY }, // Slot 2: None->Reckless, Rare None→Yache Berry
    [SPECIES_STARAVIA] = { .abilities[1] = ABILITY_RECKLESS, .itemRare = ITEM_YACHE_BERRY }, // Slot 2: None->Reckless, Rare None→Yache Berry
    [SPECIES_STARAPTOR] = { .abilities[1] = ABILITY_RECKLESS, .itemRare = ITEM_YACHE_BERRY }, // Slot 2: None->Reckless, Rare None→Yache Berry
    [SPECIES_BIBAREL] = { .itemCommon = ITEM_ORAN_BERRY, .itemRare = ITEM_SITRUS_BERRY }, // Common None→Oran Berry, Rare None→Sitrus Berry
    [SPECIES_KRICKETOT] = { .baseHP = 53, .baseAttack = 55, .baseDefense = 61, .baseSpeed = 40, .baseSpAttack = 40, .baseSpDefense = 61, .abilities[1] = ABILITY_TECHNICIAN, .abilities[2] = ABILITY_TINTED_LENS }, // HP 37->53, Atk 25->55, Def 41->61, Spe 25->40, SpA 25->40, SpD 41->61, Slot 2: None->Technician, Hidden: Run Away->Tinted Lens
    [SPECIES_KRICKETUNE] = { .baseHP = 75, .baseAttack = 90, .baseDefense = 65, .baseSpeed = 80, .baseSpAttack = 50, .baseSpDefense = 65, .abilities[1] = ABILITY_TECHNICIAN, .abilities[2] = ABILITY_TINTED_LENS }, // HP 77->75, Atk 85->90, Def 51->65, Spe 65->80, SpA 55->50, SpD 51->65, Slot 2: None->Technician, Hidden: Technician->Tinted Lens
    [SPECIES_SHINX] = { .abilities[0] = ABILITY_STRONG_JAW }, // Slot 1: Rivalry->Strong Jaw
    [SPECIES_LUXIO] = { .abilities[0] = ABILITY_STRONG_JAW, .types[1] = TYPE_DARK }, // Slot 1: Rivalry->Strong Jaw, Type2 Electric→Dark
    [SPECIES_LUXRAY] = { .abilities[0] = ABILITY_STRONG_JAW, .types[1] = TYPE_DARK }, // Slot 1: Rivalry->Strong Jaw, Type2 Electric→Dark
    [SPECIES_RAMPARDOS] = { .abilities[1] = ABILITY_ROCK_HEAD }, // Slot 2: None->Rock Head
    [SPECIES_COMBEE] = { .itemRare = ITEM_HONEY }, // Rare None→Honey (always held)
    [SPECIES_BUIZEL] = { .itemRare = ITEM_WACAN_BERRY }, // Rare None→Wacan Berry
    [SPECIES_FLOATZEL] = { .itemRare = ITEM_WACAN_BERRY }, // Rare None→Wacan Berry
    [SPECIES_DRIFLOON] = { .itemRare = ITEM_AIR_BALLOON }, // Rare None→Air Balloon
    [SPECIES_DRIFBLIM] = { .itemRare = ITEM_AIR_BALLOON }, // Rare None→Air Balloon
    [SPECIES_BUNEARY] = { .abilities[1] = ABILITY_SCRAPPY, .itemCommon = ITEM_PECHA_BERRY, .itemRare = ITEM_CHOPLE_BERRY }, // Slot 2: Klutz->Scrappy, Common None→Pecha Berry, Rare None→Chople Berry
    [SPECIES_LOPUNNY] = { .baseAttack = 106, .abilities[1] = ABILITY_SCRAPPY, .itemCommon = ITEM_PECHA_BERRY, .itemRare = ITEM_ASSAULT_VEST }, // Atk 76->106, Slot 2: Klutz->Scrappy, Common None→Pecha Berry, Rare None→Assault Vest
    [SPECIES_LOPUNNY_MEGA] = { .baseAttack = 146, .baseDefense = 104, .baseSpDefense = 106 }, // Atk 136->146, Def 94->104, SpD 96->106
    [SPECIES_MISMAGIUS] = { .baseSpeed = 110, .baseSpAttack = 110, .baseSpDefense = 110, .abilities[1] = ABILITY_CURSED_BODY, .abilities[2] = ABILITY_PIXILATE, .types[1] = TYPE_FAIRY }, // Spe 105->110, SpA 105->110, SpD 105->110, Slot 2: None->Cursed Body, Hidden: None->Pixilate, Type2 Ghost→Fairy
    [SPECIES_GLAMEOW] = { .itemRare = ITEM_CHERI_BERRY }, // Rare None→Cheri Berry
    [SPECIES_PURUGLY] = { .baseAttack = 92, .itemRare = ITEM_CHERI_BERRY }, // Atk 82->92, Rare None→Cheri Berry
    [SPECIES_CHINGLING] = { .itemCommon = ITEM_CLEANSE_TAG, .itemRare = ITEM_COLBUR_BERRY }, // Common None→Cleanse Tag, Rare Cleanse Tag→Colbur Berry
    [SPECIES_STUNKY] = { .itemRare = ITEM_PECHA_BERRY }, // Rare None→Pecha Berry
    [SPECIES_SKUNTANK] = { .itemRare = ITEM_PECHA_BERRY }, // Rare None→Pecha Berry
    [SPECIES_BRONZOR] = { .abilities[0] = ABILITY_HEATPROOF, .itemRare = ITEM_STEEL_GEM }, // Slot 1: Levitate->Heatproof, Rare Metal Coat→Steel Gem
    [SPECIES_BRONZONG] = { .abilities[0] = ABILITY_HEATPROOF, .itemCommon = ITEM_STEEL_GEM, .itemRare = ITEM_STEEL_GEM }, // Slot 1: Levitate->Heatproof, Common None→Steel Gem, Rare Metal Coat→Steel Gem (always held)
    [SPECIES_BONSLY] = { .itemRare = ITEM_ROCK_GEM }, // Rare None→Rock Gem
    [SPECIES_MIME_JR] = { .itemRare = ITEM_LEPPA_BERRY }, // Rare None→Leppa Berry
    [SPECIES_HAPPINY] = { .itemCommon = ITEM_OVAL_STONE, .itemRare = ITEM_LUCKY_PUNCH }, // Common None→Oval Stone, Rare Oval Stone→Lucky Punch
    [SPECIES_CHATOT] = { .baseDefense = 65, .baseSpeed = 96, .baseSpAttack = 112, .baseSpDefense = 62 }, // Def 45->65, Spe 91->96, SpA 92->112, SpD 42->62
    [SPECIES_SPIRITOMB] = { .abilities[1] = ABILITY_INFILTRATOR, .itemCommon = ITEM_SMOKE_BALL, .itemRare = ITEM_ODD_KEYSTONE }, // Slot 2: None->Infiltrator, Common None→Smoke Ball, Rare None→Odd Keystone
    [SPECIES_GIBLE] = { .itemRare = ITEM_HABAN_BERRY }, // Rare None→Haban Berry
    [SPECIES_GABITE] = { .itemRare = ITEM_HABAN_BERRY }, // Rare None→Haban Berry
    [SPECIES_GARCHOMP] = { .itemRare = ITEM_HABAN_BERRY }, // Rare None→Haban Berry
    [SPECIES_GARCHOMP_MEGA] = { .baseDefense = 105, .baseSpeed = 102 }, // Def 115->105, Spe 92->102
    [SPECIES_CARNIVINE] = { .baseHP = 80, .baseAttack = 110, .baseSpeed = 80, .baseSpAttack = 70, .abilities[0] = ABILITY_STRONG_JAW, .abilities[2] = ABILITY_CHLOROPHYLL }, // HP 74->80, Atk 100->110, Spe 46->80, SpA 90->70, Slot 1: Levitate->Strong Jaw, Hidden: None->Chlorophyll
    [SPECIES_FINNEON] = { .itemRare = ITEM_RINDO_BERRY }, // Rare None→Rindo Berry
    [SPECIES_LUMINEON] = { .itemRare = ITEM_RINDO_BERRY }, // Rare None→Rindo Berry
    [SPECIES_ABOMASNOW] = { .itemRare = ITEM_ICY_ROCK }, // Rare Never-Melt Ice→Icy Rock
    [SPECIES_WEAVILE] = { .abilities[0] = ABILITY_TECHNICIAN, .abilities[1] = ABILITY_PRESSURE, .itemCommon = ITEM_GRIP_CLAW }, // Slot 1: Pressure->Technician, Slot 2: None->Pressure, Common None→Grip Claw
    [SPECIES_MAGNEZONE] = { .itemRare = ITEM_MAGNET }, // Rare Metal Coat→Magnet
    [SPECIES_TANGROWTH] = { .itemCommon = ITEM_BIG_ROOT, .itemRare = ITEM_BIG_ROOT }, // Common None→Big Root, Rare None→Big Root (always held)
    [SPECIES_ELECTIVIRE] = { .types[1] = TYPE_FIGHTING }, // Type2 Electric→Fighting
    [SPECIES_MAGMORTAR] = { .abilities[1] = ABILITY_MEGA_LAUNCHER }, // Slot 2: None->Mega Launcher
    [SPECIES_GLISCOR] = { .abilities[1] = ABILITY_POISON_HEAL, .abilities[2] = ABILITY_SAND_VEIL }, // Slot 2: Sand Veil->Poison Heal, Hidden: Poison Heal->Sand Veil
    [SPECIES_MAMOSWINE] = { .abilities[1] = ABILITY_THICK_FAT, .abilities[2] = ABILITY_SNOW_CLOAK }, // Slot 2: Snow Cloak->Thick Fat, Hidden: Thick Fat->Snow Cloak
    [SPECIES_PORYGON_Z] = { .itemCommon = ITEM_NORMAL_GEM, .itemRare = ITEM_NORMAL_GEM }, // Common None→Normal Gem, Rare None→Normal Gem (always held)
    [SPECIES_GALLADE_MEGA] = { .abilities[0] = ABILITY_SHARPNESS, .abilities[1] = ABILITY_SHARPNESS, .abilities[2] = ABILITY_SHARPNESS }, // Slot 1: Inner Focus->Sharpness, Slot 2: Inner Focus->Sharpness, Hidden: Inner Focus->Sharpness
    [SPECIES_DUSKNOIR] = { .itemRare = ITEM_KASIB_BERRY }, // Rare Spell Tag→Kasib Berry
    [SPECIES_ROTOM] = { .itemCommon = ITEM_YELLOW_SHARD, .itemRare = ITEM_YELLOW_SHARD }, // Common None→Yellow Shard, Rare None→Yellow Shard (always held)
    [SPECIES_ROTOM_HEAT] = { .abilities[1] = ABILITY_MOTOR_DRIVE }, // Slot 2: None->Motor Drive
    [SPECIES_ROTOM_WASH] = { .abilities[1] = ABILITY_MOTOR_DRIVE }, // Slot 2: None->Motor Drive
    [SPECIES_ROTOM_FROST] = { .abilities[1] = ABILITY_MOTOR_DRIVE }, // Slot 2: None->Motor Drive
    [SPECIES_ROTOM_FAN] = { .abilities[1] = ABILITY_MOTOR_DRIVE }, // Slot 2: None->Motor Drive
    [SPECIES_ROTOM_MOW] = { .abilities[1] = ABILITY_MOTOR_DRIVE }, // Slot 2: None->Motor Drive
    [SPECIES_UXIE] = { .abilities[0] = ABILITY_TELEPATHY, .abilities[1] = ABILITY_LEVITATE }, // Slot 1: Levitate->Telepathy, Slot 2: None->Levitate
    [SPECIES_MESPRIT] = { .abilities[0] = ABILITY_TELEPATHY, .abilities[1] = ABILITY_LEVITATE }, // Slot 1: Levitate->Telepathy, Slot 2: None->Levitate
    [SPECIES_AZELF] = { .abilities[0] = ABILITY_TELEPATHY, .abilities[1] = ABILITY_LEVITATE }, // Slot 1: Levitate->Telepathy, Slot 2: None->Levitate
    [SPECIES_GIRATINA_ORIGIN] = { .abilities[2] = ABILITY_TELEPATHY }, // Hidden: None->Telepathy
    [SPECIES_PHIONE] = { .evolutions = EVOLUTION({EVO_LEVEL, 50, SPECIES_MANAPHY, CONDITIONS({IF_MIN_FRIENDSHIP, 220}, {IF_HOLD_ITEM, ITEM_MYSTIC_WATER, EVO_KEEP_HELD_ITEM})}) }, // Evolutions: None->Manaphy (Lv. 50, friendship 220, holding Mystic Water; the item is kept)
    [SPECIES_SNIVY] = { .abilities[1] = ABILITY_CONTRARY }, // Slot 2: None->Contrary
    [SPECIES_SERVINE] = { .abilities[1] = ABILITY_CONTRARY }, // Slot 2: None->Contrary
    [SPECIES_SERPERIOR] = { .baseAttack = 65, .baseSpAttack = 85, .abilities[1] = ABILITY_CONTRARY, .types[1] = TYPE_DRAGON }, // Atk 75->65, SpA 75->85, Slot 2: None->Contrary, Type2 Grass→Dragon
    [SPECIES_TEPIG] = { .abilities[1] = ABILITY_THICK_FAT }, // Slot 2: None->Thick Fat
    [SPECIES_PIGNITE] = { .abilities[1] = ABILITY_THICK_FAT, .types[1] = TYPE_GROUND }, // Slot 2: None->Thick Fat, Type2 Fighting→Ground
    [SPECIES_EMBOAR] = { .abilities[1] = ABILITY_RECKLESS, .types[1] = TYPE_GROUND }, // Slot 2: None->Reckless, Type2 Fighting→Ground
    [SPECIES_OSHAWOTT] = { .abilities[1] = ABILITY_SHELL_ARMOR }, // Slot 2: None->Shell Armor
    [SPECIES_DEWOTT] = { .baseAttack = 85, .baseSpAttack = 73, .abilities[1] = ABILITY_SHELL_ARMOR, .types[1] = TYPE_FIGHTING }, // Atk 75->85, SpA 83->73, Slot 2: None->Shell Armor, Type2 Water→Fighting
    [SPECIES_SAMUROTT] = { .baseHP = 90, .baseAttack = 115, .baseDefense = 80, .baseSpeed = 85, .baseSpAttack = 93, .abilities[1] = ABILITY_SHARPNESS, .abilities[2] = ABILITY_SHARPNESS, .types[1] = TYPE_FIGHTING }, // HP 95->90, Atk 100->115, Def 85->80, Spe 70->85, SpA 108->93, Slot 2: None->Sharpness, Hidden: Shell Armor->Sharpness, Type2 Water→Fighting
    [SPECIES_PANSAGE] = { .abilities[1] = ABILITY_OVERGROW, .itemCommon = ITEM_ORAN_BERRY, .itemRare = ITEM_OCCA_BERRY }, // Slot 2: None->Overgrow, Common None→Oran Berry, Rare None→Occa Berry
    [SPECIES_SIMISAGE] = { .abilities[1] = ABILITY_OVERGROW, .itemCommon = ITEM_ORAN_BERRY, .itemRare = ITEM_OCCA_BERRY }, // Slot 2: None->Overgrow, Common None→Oran Berry, Rare None→Occa Berry
    [SPECIES_PANSEAR] = { .abilities[1] = ABILITY_BLAZE, .itemCommon = ITEM_ORAN_BERRY, .itemRare = ITEM_PASSHO_BERRY }, // Slot 2: None->Blaze, Common None→Oran Berry, Rare None→Passho Berry
    [SPECIES_SIMISEAR] = { .abilities[1] = ABILITY_BLAZE, .itemCommon = ITEM_ORAN_BERRY, .itemRare = ITEM_PASSHO_BERRY }, // Slot 2: None->Blaze, Common None→Oran Berry, Rare None→Passho Berry
    [SPECIES_PANPOUR] = { .abilities[1] = ABILITY_TORRENT, .itemCommon = ITEM_ORAN_BERRY, .itemRare = ITEM_RINDO_BERRY }, // Slot 2: None->Torrent, Common None→Oran Berry, Rare None→Rindo Berry
    [SPECIES_SIMIPOUR] = { .abilities[1] = ABILITY_TORRENT, .itemCommon = ITEM_ORAN_BERRY, .itemRare = ITEM_RINDO_BERRY }, // Slot 2: None->Torrent, Common None→Oran Berry, Rare None→Rindo Berry
    [SPECIES_PIDOVE] = { .baseAttack = 36, .baseSpAttack = 55 }, // Atk 55->36, SpA 36->55
    [SPECIES_TRANQUILL] = { .baseAttack = 45, .baseSpAttack = 82 }, // Atk 77->45, SpA 50->82
    [SPECIES_UNFEZANT] = { .baseAttack = 65, .baseSpAttack = 115 }, // Atk 115->65, SpA 65->115
    [SPECIES_BLITZLE] = { .abilities[0] = ABILITY_STRIKER, .itemCommon = ITEM_CHERI_BERRY }, // Slot 1: Lightning Rod->Striker, Common None→Cheri Berry
    [SPECIES_ZEBSTRIKA] = { .abilities[0] = ABILITY_STRIKER, .itemCommon = ITEM_CHERI_BERRY }, // Slot 1: Lightning Rod->Striker, Common None→Cheri Berry
    [SPECIES_AUDINO] = { .expYield = 608 }, // Exp yield 390→608
    [SPECIES_AUDINO_MEGA] = { .abilities[0] = ABILITY_REGENERATOR, .abilities[1] = ABILITY_REGENERATOR, .abilities[2] = ABILITY_REGENERATOR }, // Slot 1: Healer->Regenerator, Slot 2: Healer->Regenerator, Hidden: Healer->Regenerator
    [SPECIES_TYMPOLE] = { .itemCommon = ITEM_PERSIM_BERRY }, // Common None→Persim Berry
    [SPECIES_PALPITOAD] = { .itemCommon = ITEM_PERSIM_BERRY }, // Common None→Persim Berry
    [SPECIES_SEISMITOAD] = { .itemCommon = ITEM_PERSIM_BERRY }, // Common None→Persim Berry
    [SPECIES_SAWK] = { .itemRare = ITEM_EXPERT_BELT }, // Rare Black Belt→Expert Belt
    [SPECIES_LEAVANNY] = { .abilities[2] = ABILITY_SHARPNESS, .itemCommon = ITEM_MENTAL_HERB, .itemRare = ITEM_WHITE_HERB }, // Hidden: Overcoat->Sharpness, Common None→Mental Herb, Rare Mental Herb→White Herb
    [SPECIES_VENIPEDE] = { .itemCommon = ITEM_PECHA_BERRY }, // Common None→Pecha Berry
    [SPECIES_WHIRLIPEDE] = { .itemCommon = ITEM_PECHA_BERRY }, // Common None→Pecha Berry
    [SPECIES_SCOLIPEDE] = { .itemCommon = ITEM_PECHA_BERRY }, // Common None→Pecha Berry
    [SPECIES_WHIMSICOTT] = { .baseHP = 80, .baseDefense = 90, .baseSpDefense = 80 }, // HP 60->80, Def 85->90, SpD 75->80
    [SPECIES_BASCULIN_RED_STRIPED] = { .baseAttack = 102, .baseSpAttack = 70 }, // Atk 92->102, SpA 80->70
    [SPECIES_DARUMAKA] = { .itemCommon = ITEM_RAWST_BERRY }, // Common None→Rawst Berry
    [SPECIES_DARMANITAN_STANDARD] = { .itemCommon = ITEM_RAWST_BERRY }, // Common None→Rawst Berry
    [SPECIES_DARMANITAN_GALAR_STANDARD] = { .itemCommon = ITEM_CHOICE_SCARF }, // Common None→Choice Scarf
    [SPECIES_SCRAFTY] = { .itemRare = ITEM_MUSCLE_BAND }, // Rare Shed Shell→Muscle Band
    [SPECIES_SIGILYPH] = { .baseHP = 82, .baseAttack = 38, .baseSpAttack = 113, .abilities[0] = ABILITY_TINTED_LENS, .abilities[2] = ABILITY_PSYCHIC_SURGE }, // HP 72->82, Atk 58->38, SpA 103->113, Slot 1: Wonder Skin->Tinted Lens, Hidden: Tinted Lens->Psychic Surge
    [SPECIES_YAMASK] = { .baseAttack = 25, .baseSpDefense = 70 }, // Atk 30->25, SpD 65->70
    [SPECIES_COFAGRIGUS] = { .baseAttack = 40, .baseSpDefense = 115 }, // Atk 50->40, SpD 105->115
    [SPECIES_MINCCINO] = { .itemCommon = ITEM_CHESTO_BERRY }, // Common None→Chesto Berry
    [SPECIES_CINCCINO] = { .itemCommon = ITEM_CHESTO_BERRY }, // Common None→Chesto Berry
    [SPECIES_GOTHITA] = { .itemCommon = ITEM_PERSIM_BERRY }, // Common None→Persim Berry
    [SPECIES_GOTHORITA] = { .itemCommon = ITEM_PERSIM_BERRY }, // Common None→Persim Berry
    [SPECIES_GOTHITELLE] = { .types[1] = TYPE_DARK, .itemCommon = ITEM_PERSIM_BERRY }, // Type2 Psychic→Dark, Common None→Persim Berry
    [SPECIES_SOLOSIS] = { .itemCommon = ITEM_PERSIM_BERRY }, // Common None→Persim Berry
    [SPECIES_DUOSION] = { .itemCommon = ITEM_PERSIM_BERRY }, // Common None→Persim Berry
    [SPECIES_REUNICLUS] = { .itemCommon = ITEM_PERSIM_BERRY }, // Common None→Persim Berry
    [SPECIES_SWANNA] = { .baseAttack = 67, .baseSpAttack = 107, .abilities[0] = ABILITY_DRIZZLE, .abilities[1] = ABILITY_FRIEND_GUARD }, // Atk 87->67, SpA 87->107, Slot 1: Keen Eye->Drizzle, Slot 2: Big Pecks->Friend Guard
    [SPECIES_VANILLUXE] = { .types[1] = TYPE_FAIRY }, // Type2 Ice→Fairy
    [SPECIES_SAWSBUCK_SPRING] = { .baseAttack = 110, .baseSpeed = 105 }, // Atk 100->110, Spe 95->105
    [SPECIES_SAWSBUCK_SUMMER] = { .baseAttack = 110, .baseSpeed = 105 }, // Atk 100->110, Spe 95->105
    [SPECIES_SAWSBUCK_AUTUMN] = { .baseAttack = 110, .baseSpeed = 105 }, // Atk 100->110, Spe 95->105
    [SPECIES_SAWSBUCK_WINTER] = { .baseAttack = 110, .baseSpeed = 105 }, // Atk 100->110, Spe 95->105
    [SPECIES_EMOLGA] = { .itemCommon = ITEM_CHERI_BERRY, .itemRare = ITEM_YELLOW_SHARD }, // Common None→Cheri Berry, Rare None→Yellow Shard
    [SPECIES_FERROTHORN] = { .baseHP = 84 }, // HP 74->84
    [SPECIES_KLINK] = { .abilities[0] = ABILITY_STEELWORKER, .abilities[1] = ABILITY_CLEAR_BODY }, // Slot 1: Plus->Steelworker, Slot 2: Minus->Clear Body
    [SPECIES_KLANG] = { .abilities[0] = ABILITY_STEELWORKER, .abilities[1] = ABILITY_CLEAR_BODY }, // Slot 1: Plus->Steelworker, Slot 2: Minus->Clear Body
    [SPECIES_KLINKLANG] = { .abilities[0] = ABILITY_STEELWORKER, .abilities[1] = ABILITY_CLEAR_BODY }, // Slot 1: Plus->Steelworker, Slot 2: Minus->Clear Body
    [SPECIES_BEHEEYEM] = { .abilities[0] = ABILITY_PSYCHIC_SURGE }, // Slot 1: Telepathy->Psychic Surge
    [SPECIES_FRAXURE] = { .abilities[0] = ABILITY_SHARPNESS }, // Slot 1: Rivalry->Sharpness
    [SPECIES_HAXORUS] = { .abilities[0] = ABILITY_SHARPNESS }, // Slot 1: Rivalry->Sharpness
    [SPECIES_CUBCHOO] = { .itemCommon = ITEM_ASPEAR_BERRY }, // Common None→Aspear Berry
    [SPECIES_BEARTIC] = { .baseHP = 85, .baseDefense = 70, .baseSpeed = 95, .baseSpDefense = 70, .types[1] = TYPE_FIGHTING, .itemCommon = ITEM_ASPEAR_BERRY, .expYield = 200 }, // HP 95->85, Def 80->70, Spe 50->95, SpD 80->70, Type2 Ice→Fighting, Common None→Aspear Berry, Exp yield 177→200
    [SPECIES_CRYOGONAL] = { .abilities[1] = ABILITY_SNOW_CLOAK, .abilities[2] = ABILITY_SLUSH_RUSH }, // Slot 2: None->Snow Cloak, Hidden: None->Slush Rush
    [SPECIES_STUNFISK] = { .itemRare = ITEM_YELLOW_SHARD }, // Rare Soft Sand→Yellow Shard
    [SPECIES_STUNFISK_GALAR] = { .abilities[0] = ABILITY_ROUGH_SKIN }, // Slot 1: Mimicry->Rough Skin
    [SPECIES_HEATMOR] = { .itemRare = ITEM_FLAME_ORB }, // Rare None→Flame Orb
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
    [SPECIES_DRAGALGE] = { .itemCommon = ITEM_CHOICE_SPECS }, // Common None→Choice Specs
    [SPECIES_HELIOPTILE] = { .itemRare = ITEM_YELLOW_SHARD }, // Rare None→Yellow Shard
    [SPECIES_HELIOLISK] = { .types[1] = TYPE_GROUND, .itemCommon = ITEM_YELLOW_SHARD, .itemRare = ITEM_YELLOW_SHARD }, // Type2 Normal→Ground, Common None→Yellow Shard, Rare None→Yellow Shard (always held)
    [SPECIES_HAWLUCHA] = { .itemCommon = ITEM_KINGS_ROCK, .itemRare = ITEM_POWER_HERB }, // Common None→King's Rock, Rare King's Rock→Power Herb
    [SPECIES_GOODRA] = { .types[0] = TYPE_WATER }, // Type1 Dragon→Water
    [SPECIES_BERGMITE] = { .itemRare = ITEM_ICE_GEM }, // Rare None→Ice Gem
    [SPECIES_AVALUGG] = { .itemCommon = ITEM_ICE_GEM, .itemRare = ITEM_ICE_GEM }, // Common None→Ice Gem, Rare None→Ice Gem (always held)
    [SPECIES_NOIBAT] = { .baseAttack = 25, .baseSpAttack = 50 }, // Atk 30->25, SpA 45->50
    [SPECIES_NOIVERN] = { .baseSpAttack = 112 }, // SpA 97->112
    [SPECIES_DIANCIE] = { .itemCommon = ITEM_DIANCITE, .itemRare = ITEM_DIANCITE }, // Common None→Diancite, Rare None→Diancite (always held)
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
    [SPECIES_FOMANTIS] = { .itemRare = ITEM_GRASS_GEM }, // Rare Miracle Seed→Grass Gem
    [SPECIES_LURANTIS] = { .types[1] = TYPE_FIGHTING, .itemCommon = ITEM_GRASS_GEM, .itemRare = ITEM_GRASS_GEM }, // Type2 Grass→Fighting, Common None→Grass Gem, Rare Miracle Seed→Grass Gem (always held)
    [SPECIES_TSAREENA] = { .abilities[2] = ABILITY_STRIKER, .types[1] = TYPE_FIGHTING }, // Hidden: Sweet Veil->Striker, Type2 Grass→Fighting
    [SPECIES_GOLISOPOD] = { .itemCommon = ITEM_RED_CARD }, // Common None→Red Card
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
    [SPECIES_NICKIT] = { .itemRare = ITEM_DARK_GEM }, // Rare None→Dark Gem
    [SPECIES_THIEVUL] = { .baseHP = 60, .baseAttack = 100, .baseDefense = 60, .baseSpeed = 110, .baseSpAttack = 70, .baseSpDefense = 70, .itemCommon = ITEM_DARK_GEM, .itemRare = ITEM_DARK_GEM }, // HP 70->60, Atk 58->100, Def 58->60, Spe 90->110, SpA 87->70, SpD 92->70, Common None→Dark Gem, Rare None→Dark Gem (always held)
    [SPECIES_APPLIN] = { .baseHP = 50, .baseAttack = 60, .baseDefense = 70, .baseSpeed = 35 }, // HP 40->50, Atk 40->60, Def 80->70, Spe 20->35
    [SPECIES_SILICOBRA] = { .itemRare = ITEM_GROUND_GEM }, // Rare None→Ground Gem
    [SPECIES_SANDACONDA] = { .itemCommon = ITEM_GROUND_GEM, .itemRare = ITEM_GROUND_GEM }, // Common None→Ground Gem, Rare None→Ground Gem (always held)
    [SPECIES_CURSOLA] = { .itemCommon = ITEM_GHOST_GEM, .itemRare = ITEM_GHOST_GEM }, // Common None→Ghost Gem, Rare None→Ghost Gem (always held)
    [SPECIES_SIRFETCHD] = { .abilities[0] = ABILITY_SHARPNESS, .abilities[1] = ABILITY_JUSTIFIED }, // Slot 1: Steadfast->Sharpness, Slot 2: None->Justified
    [SPECIES_FALINKS] = { .abilities[1] = ABILITY_JUSTIFIED }, // Slot 2: None->Justified
};
