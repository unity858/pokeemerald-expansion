#!/usr/bin/env python3
"""
Generate src/data/custom_learnsets.h: the R.O.W.E. learnsets used in Custom
data mode (see GetSpeciesLevelUpLearnset / GetSpeciesTeachableLearnset /
GetSpeciesEggMoves / GetTutorMoves in src/pokemon.c). Vanilla mode never reads
this file.

HOW TO RERUN
------------
This script is NOT part of the build, so building never needs R.O.W.E.'s
source. Rerun it by hand whenever R.O.W.E.'s learnsets, the official
learnsets, TMs, tutors or evolutions change:

    make -j16                     # official data is read from the built ROM
    python3 tools/custom_learnsets/make_custom_learnsets.py [--rowe ../RoweSource]
    make -j16                     # rebuild with the new header

Run it from the repository root. It needs:
  * a built pokeemerald.elf / pokeemerald.gba (official learnsets, evolutions
    and species flags are read from gSpeciesInfo in the ROM, so whatever the
    configs and make_teachables.py produced is what gets compared against),
  * arm-none-eabi-gcc / arm-none-eabi-nm (struct layout and constant values),
  * git history containing expansion commit 10f4b48215 (R.O.W.E.'s base, for
    its HM08 Dive compatibility),
  * R.O.W.E.'s source tree (read-only): level_up_learnsets.h,
    level_up_learnset_pointers.h, tmhm_learnsets.h, tutor_learnsets.h,
    egg_moves.h, party_menu.h (TM list) and constants.

Any R.O.W.E. species or move that can't be resolved to this repo's canonical
constants makes the script fail. After writing the header it re-reads it and
verifies the rules below, printing a report.

RULES
-----
Per species and per category (level-up, TM, tutor, egg), Custom data comes
from R.O.W.E. if R.O.W.E. has a list for it. Battle/cosmetic forms without
their own list mirror the species they share the official learnset with
(e.g. Megas use their base form's Custom learnset). Otherwise the official
data is used (NULL entry = official learnset).

 1. Every level-up move that is a TM or tutor move is made TM/tutor
    compatible (the teachable list holds TM and tutor moves together, so a
    move that is both a TM and a tutor move is compatible through both).
    Dive learned as an egg move also gives TM121 compatibility.
 2. An evolution inherits its pre-evolution's (whole chain's) TM and tutor
    compatibility. Egg moves follow expansion's convention: they're stored on
    the family's base species (and on species that can hatch without an
    incense, e.g. Marill), which evolutions use.
 3. Species without any R.O.W.E. learnset data use official data. If such a
    species has a pre-evolution with Custom data, its teachable list is the
    official one plus rule 1, the HM superset and the chain's inherited
    compatibility (level-up stays official).
 4. HM moves: Cut/Strength/Flash/Rock Smash come from R.O.W.E.'s tutor lists,
    Fly/Surf/Waterfall from its TM76/94/98 lists, Dive (TM121) from the HM08
    bit of R.O.W.E.'s base (expansion 10f4b48215) plus level-up/egg learners.
    Custom compatibility with these 8 moves is a superset of Vanilla: anything
    Vanilla lets a species learn them by (TM, tutor, level-up, egg) is made
    TM/tutor compatible, before rule 2 so it carries down evolution lines.
 5. Clean-ups: duplicate entries removed, level-up lists sorted by level
    (Lv0 evolution moves, then Lv1 moves first), egg moves defined on an
    evolved species moved to the family's base species.
 Teachable moves R.O.W.E. had no TM/tutor for (e.g. TM122 Tera Blast, the
 universal move) use expansion's normal rule, i.e. the official compatibility.
"""

import argparse
import collections
import os
import re
import subprocess
import sys
import tempfile

ROM_BASE = 0x08000000
BASE_COMMIT = "10f4b48215"
HEADER_PATH = "src/data/custom_learnsets.h"

HM_TUTOR_MOVES = ["MOVE_CUT", "MOVE_STRENGTH", "MOVE_FLASH", "MOVE_ROCK_SMASH"]
HM_MOVES = ["MOVE_CUT", "MOVE_FLY", "MOVE_SURF", "MOVE_STRENGTH", "MOVE_FLASH",
            "MOVE_ROCK_SMASH", "MOVE_WATERFALL", "MOVE_DIVE"]

# R.O.W.E. arrays that exist but aren't referenced by its pointer tables.
EXTRA_LEVELUP_HOOKUPS = {
    "SPECIES_ROTOM_HEAT": "sRotomHeatLevelUpLearnset",
    "SPECIES_ROTOM_WASH": "sRotomWashLevelUpLearnset",
    "SPECIES_ROTOM_FROST": "sRotomFrostLevelUpLearnset",
    "SPECIES_ROTOM_FAN": "sRotomFanLevelUpLearnset",
    "SPECIES_ROTOM_MOW": "sRotomMowLevelUpLearnset",
}
EXTRA_TM_HOOKUPS = {
    "SPECIES_MEOWTH_GALARIAN": "sMeowthGalarianTMHMLearnset",
    "SPECIES_SLOWPOKE_GALARIAN": "sSlowpokeGalarianTMHMLearnset",
}
EXTRA_TUTOR_HOOKUPS = {
    "SPECIES_TOXTRICITY_LOW_KEY": "sToxtricityLowKeyTutorLearnset",
}

# R.O.W.E. -> expansion species name rules.
SPECIES_SUFFIX_RULES = [("_ALOLAN", "_ALOLA"), ("_GALARIAN", "_GALAR"), ("_HUSIAN", "_HISUI")]
SPECIES_MANUAL = {
    "SPECIES_MIMEJR": "SPECIES_MIME_JR",
    "SPECIES_INDEEDEE_FEMALE": "SPECIES_INDEEDEE_F",
    "SPECIES_MEOWSTIC_FEMALE": "SPECIES_MEOWSTIC_F",
}
SPECIES_FALLBACK_RULES = [
    ("_CLOAK", ""), ("_EAST_SEA", "_EAST"), ("_DRIVE", ""), ("_FLOWER", ""), ("_TRIM", ""),
    ("_CAP", ""), ("_ZEN_MODE", "_ZEN"), ("PH_D", "PHD"), ("EMARK", "EXCLAMATION"),
    ("QMARK", "QUESTION"), ("POKE_BALL", "POKEBALL"), ("PA_U", "PAU"), ("_COLOR", ""),
    ("NOICE_FACE", "NOICE"), ("CROWNED_SWORD", "CROWNED"), ("CROWNED_SHIELD", "CROWNED"),
    ("RAPID_STRIKE_STYLE", "RAPID_STRIKE"), ("_RIDER", ""),
]
MOVE_MANUAL = {"MOVE_SMELLING_SALT": "MOVE_SMELLING_SALTS"}


def die(msg):
    print("ERROR: " + msg, file=sys.stderr)
    sys.exit(1)


def strip_comments(t):
    t = re.sub(r"/\*.*?\*/", "", t, flags=re.S)
    return re.sub(r"//[^\n]*", "", t)


def read(path):
    with open(path, encoding="utf-8", errors="replace") as f:
        return strip_comments(f.read())


# --------------------------------------------------------------------------
# This repo: constants, layout and official data from the built ROM
# --------------------------------------------------------------------------

def enum_names(path, prefix):
    """Constant names in file order, with whether each is an alias."""
    t = read(path)
    out = []
    for m in re.finditer(r"\b(" + prefix + r"\w+)\s*(=\s*([^,\n]+))?\s*,", t):
        rhs = (m.group(3) or "").strip()
        out.append((m.group(1), rhs.startswith(prefix)))
    for m in re.finditer(r"#define\s+(" + prefix + r"\w+)\s+(\S+)", t):
        out.append((m.group(1), m.group(2).startswith(prefix)))
    seen, res = set(), []
    for n, a in out:
        if n not in seen:
            seen.add(n)
            res.append((n, a))
    return res


def probe(exprs):
    """Evaluate integer C expressions with the ARM compiler."""
    src = ['#include "global.h"', '#include "pokemon.h"', '#include "constants/moves.h"',
           '#include "constants/species.h"', '#include "constants/pokemon.h"', '#include <stddef.h>']
    for key, e in exprs.items():
        src.append(f"char probe_{key}[({e}) + 1];")
    with tempfile.TemporaryDirectory() as d:
        c = os.path.join(d, "p.c")
        s = os.path.join(d, "p.s")
        with open(c, "w") as f:
            f.write("\n".join(src) + "\n")
        cmd = ["arm-none-eabi-gcc", "-S", "-mthumb", "-mabi=apcs-gnu", "-mtune=arm7tdmi",
               "-march=armv4t", "-iquote", "include", "-DMODERN=1", "-DTESTING=0", "-DEMERALD",
               "-std=gnu17", "-I", "tools/agbcc/include", "-w", c, "-o", s]
        r = subprocess.run(cmd, capture_output=True, text=True)
        if r.returncode:
            die("probe compile failed:\n" + r.stderr[:3000])
        asm = open(s).read()
    vals = {}
    for m in re.finditer(r"\.size\s+probe_(\w+),\s*(\d+)", asm):
        vals[m.group(1)] = int(m.group(2)) - 1
    for m in re.finditer(r"\.comm\s+probe_(\w+),(\d+)", asm):
        vals.setdefault(m.group(1), int(m.group(2)) - 1)
    missing = set(exprs) - set(vals)
    if missing:
        die("probe missing values: " + ", ".join(sorted(missing)[:10]))
    return vals


class Rom:
    def __init__(self):
        if not os.path.exists("pokeemerald.elf") or not os.path.exists("pokeemerald.gba"):
            die("build the ROM first (make -j16): pokeemerald.elf/.gba not found")
        self.data = open("pokeemerald.gba", "rb").read()
        r = subprocess.run(["arm-none-eabi-nm", "-S", "pokeemerald.elf"], capture_output=True, text=True)
        self.syms = {}
        for line in r.stdout.splitlines():
            p = line.split()
            if len(p) == 4:
                self.syms[p[3]] = (int(p[0], 16), int(p[1], 16))

    def u16(self, addr):
        o = addr - ROM_BASE
        return self.data[o] | (self.data[o + 1] << 8)

    def u32(self, addr):
        o = addr - ROM_BASE
        return int.from_bytes(self.data[o:o + 4], "little")

    def u16_list(self, addr, end=0xFFFF):
        out = []
        while True:
            v = self.u16(addr)
            if v == end:
                return out
            out.append(v)
            addr += 2


class Repo:
    def __init__(self):
        self.species_names = enum_names("include/constants/species.h", "SPECIES_")
        self.move_names = enum_names("include/constants/moves.h", "MOVE_")
        skip = {"MOVE_UNAVAILABLE", "MOVES_COUNT", "MOVES_COUNT_ALL"}
        exprs = {}
        for n, _ in self.species_names:
            exprs["S_" + n] = n
        for n, _ in self.move_names:
            if not n.startswith("MOVES_COUNT") and n not in skip:
                exprs["M_" + n] = n
        lay = {
            "SI_SIZE": "sizeof(struct SpeciesInfo)",
            "SI_LVL": "offsetof(struct SpeciesInfo, levelUpLearnset)",
            "SI_TEACH": "offsetof(struct SpeciesInfo, teachableLearnset)",
            "SI_EGG": "offsetof(struct SpeciesInfo, eggMoveLearnset)",
            "SI_EVO": "offsetof(struct SpeciesInfo, evolutions)",
            "SI_HP": "offsetof(struct SpeciesInfo, baseHP)",
            "EV_SIZE": "sizeof(struct Evolution)",
            "EV_METHOD": "offsetof(struct Evolution, method)",
            "EV_TARGET": "offsetof(struct Evolution, targetSpecies)",
            "LU_SIZE": "sizeof(struct LevelUpMove)",
            "LU_MOVE": "offsetof(struct LevelUpMove, move)",
            "LU_LEVEL": "offsetof(struct LevelUpMove, level)",
            "NUM_SPECIES": "NUM_SPECIES",
        }
        exprs.update(lay)
        v = probe(exprs)
        self.lay = {k: v[k] for k in lay}
        self.species_id = {n: v["S_" + n] for n, _ in self.species_names}
        self.move_id = {n: v["M_" + n] for n, _ in self.move_names if "M_" + n in v}
        # canonical names: first non-alias name per value
        self.species_by_id = {}
        for n, alias in self.species_names:
            if not alias and n != "SPECIES_EGG":
                self.species_by_id.setdefault(self.species_id[n], n)
        self.move_by_id = {}
        for n, alias in self.move_names:
            if not alias and n in self.move_id:
                self.move_by_id.setdefault(self.move_id[n], n)
        self.read_rom()
        self.read_tms_tutors()

    def canon_species(self, name):
        if name not in self.species_id:
            return None
        return self.species_by_id.get(self.species_id[name])

    def canon_move(self, name):
        name = MOVE_MANUAL.get(name, name)
        if name not in self.move_id:
            return None
        return self.move_by_id.get(self.move_id[name])

    def read_rom(self):
        rom = Rom()
        L = self.lay
        base, size = rom.syms["gSpeciesInfo"]
        n = size // L["SI_SIZE"]
        if n < L["NUM_SPECIES"]:
            die("gSpeciesInfo smaller than NUM_SPECIES; rebuild the ROM")
        self.enabled = set()
        self.off_lvl, self.off_teach, self.off_egg = {}, {}, {}
        self.ptr_lvl, self.ptr_teach, self.ptr_egg = {}, {}, {}
        self.evos = {}
        for sid in range(n):
            name = self.species_by_id.get(sid)
            a = base + sid * L["SI_SIZE"]
            if name is None:
                continue
            if rom.data[a + L["SI_HP"] - ROM_BASE] == 0:
                continue
            self.enabled.add(name)
            pl = rom.u32(a + L["SI_LVL"])
            pt = rom.u32(a + L["SI_TEACH"])
            pe = rom.u32(a + L["SI_EGG"])
            pv = rom.u32(a + L["SI_EVO"])
            self.ptr_lvl[name], self.ptr_teach[name], self.ptr_egg[name] = pl, pt, pe
            lvl = []
            if pl:
                p = pl
                while True:
                    mv = rom.u16(p + L["LU_MOVE"])
                    if mv == 0xFFFF:
                        break
                    lvl.append((rom.u16(p + L["LU_LEVEL"]), self.move_by_id[mv]))
                    p += L["LU_SIZE"]
            self.off_lvl[name] = lvl
            self.off_teach[name] = [self.move_by_id[m] for m in rom.u16_list(pt)] if pt else []
            self.off_egg[name] = [self.move_by_id[m] for m in rom.u16_list(pe)] if pe else []
            ev = []
            if pv:
                p = pv
                while True:
                    meth = rom.u16(p + L["EV_METHOD"])
                    if meth == 0xFFFF:
                        break
                    ev.append(self.species_by_id.get(rom.u16(p + L["EV_TARGET"])))
                    p += L["EV_SIZE"]
            self.evos[name] = ev
        # GetSpeciesPreEvolution: lowest-ID enabled species with an evolution to it
        self.prevo = {}
        order = sorted(self.enabled, key=lambda s: self.species_id[s])
        for s in order:
            if self.species_id[s] == 0:
                continue
            for t in self.evos.get(s, []):
                if t in self.enabled and t not in self.prevo:
                    self.prevo[t] = s
        self.order = [s for s in order if self.species_id[s] != 0]

    def read_tms_tutors(self):
        t = read("include/constants/tms_hms.h")
        m = re.search(r"#define\s+FOREACH_TM\(F\)((?:[^\n]*\\\n)*[^\n]*)", t)
        self.tms = ["MOVE_" + x for x in re.findall(r"F\((\w+)\)", m.group(1))]
        self.tm_number = {mv: i + 1 for i, mv in enumerate(self.tms)}
        self.tutors = [x for x in re.findall(r"MOVE_\w+", read("src/data/tutor_moves.h")) if x != "MOVE_UNAVAILABLE"]
        cfg = read("include/config/pokedex_plus_hgss.h")
        mm = re.search(r"#define\s+HGSS_SORT_TMS_BY_NUM\s+(\w+)", cfg)
        self.sort_tms_by_num = mm is not None and mm.group(1) in ("TRUE", "1")

    def first_of_chain(self, s):
        seen = set()
        while s in self.prevo and s not in seen:
            seen.add(s)
            s = self.prevo[s]
        return s

    def chain(self, s):
        out, seen = [], set()
        while s in self.prevo and s not in seen:
            seen.add(s)
            s = self.prevo[s]
            out.append(s)
        return out


# --------------------------------------------------------------------------
# R.O.W.E.
# --------------------------------------------------------------------------

class Rowe:
    def __init__(self, root, repo):
        self.root = root
        self.repo = repo
        p = lambda f: os.path.join(root, f)
        for f in ("src/data/pokemon/level_up_learnsets.h", "src/data/pokemon/level_up_learnset_pointers.h",
                  "src/data/pokemon/tmhm_learnsets.h", "src/data/pokemon/tutor_learnsets.h",
                  "src/data/pokemon/egg_moves.h", "src/data/party_menu.h", "include/constants/species.h"):
            if not os.path.exists(p(f)):
                die(f"R.O.W.E. file not found: {p(f)} (pass --rowe)")
        self.species = self.parse_species(read(p("include/constants/species.h")))
        self.errors = []

        # level-up
        t = read(p("src/data/pokemon/level_up_learnsets.h"))
        self.lvl_arrays = {}
        for m in re.finditer(r"struct LevelUpMove\s+(\w+)\[\]\s*=\s*\{(.*?)\};", t, re.S):
            self.lvl_arrays[m.group(1)] = [(int(a), self.move(b)) for a, b in
                                           re.findall(r"LEVEL_UP_MOVE\(\s*(\d+)\s*,\s*(\w+)\s*\)", m.group(2))]
        self.lvl_ptr = self.ptr_table(read(p("src/data/pokemon/level_up_learnset_pointers.h")), "gLevelUpLearnsets")
        self.lvl_ptr.update(EXTRA_LEVELUP_HOOKUPS)

        # TM list (party_menu.h sTMHMMoves)
        t = read(p("src/data/party_menu.h"))
        i = t.index("sTMHMMoves[TMHM_COUNT]")
        mv = re.findall(r"(MOVE_\w+)", t[i:t.index("};", i)])
        self.tm_moves = {n + 1: self.move(x) for n, x in enumerate(mv[:200]) if x != "MOVE_NONE"}

        t = read(p("src/data/pokemon/tmhm_learnsets.h"))
        self.tm_arrays = {}
        for m in re.finditer(r"u8\s+(\w+)\[\w*\]\s*=\s*\{(.*?)\};", t, re.S):
            nums = []
            for item in re.findall(r"TMHM\((\w+)\)", m.group(2)):
                mm = re.match(r"TM(\d+)_", item)
                if not mm:
                    self.errors.append(f"unexpected TM/HM item {item} in {m.group(1)}")
                    continue
                n = int(mm.group(1))
                if n not in self.tm_moves:
                    self.errors.append(f"TM{n} in {m.group(1)} has no move")
                    continue
                nums.append(self.tm_moves[n])
            self.tm_arrays[m.group(1)] = nums
        self.tm_ptr = self.ptr_table(t, "gTMHMLearnsets")
        self.tm_ptr.update(EXTRA_TM_HOOKUPS)

        t = read(p("src/data/pokemon/tutor_learnsets.h"))
        i = t.index("gTutorMoves")
        self.tutor_moves = [self.move(x) for x in re.findall(r"=\s*(MOVE_\w+)", t[i:t.index("};", i)])]
        self.tutor_arrays = {}
        for m in re.finditer(r"u8\s+(\w+)\[\w*\]\s*=\s*\{(.*?)\};", t, re.S):
            self.tutor_arrays[m.group(1)] = [self.move(x) for x in re.findall(r"TUTOR\((MOVE_\w+)\)", m.group(2))]
        self.tutor_ptr = self.ptr_table(t, "sTutorLearnsets")
        self.tutor_ptr.update(EXTRA_TUTOR_HOOKUPS)

        t = read(p("src/data/pokemon/egg_moves.h"))
        self.eggs = collections.OrderedDict()
        for m in re.finditer(r"egg_moves\(\s*(\w+)\s*,(.*?)\)\s*,?", t, re.S):
            if m.group(1) == "species":
                continue
            sp = "SPECIES_" + m.group(1)
            self.eggs.setdefault(sp, []).extend(self.move(x) for x in re.findall(r"MOVE_\w+", m.group(2)))

        # base (expansion 10f4b48215) HM08 Dive bits
        r = subprocess.run(["git", "show", f"{BASE_COMMIT}:src/data/pokemon/tmhm_learnsets.h"],
                           capture_output=True, text=True)
        if r.returncode:
            die(f"git show {BASE_COMMIT} failed: {r.stderr}")
        bt = strip_comments(r.stdout)
        self.base_dive = set()
        for m in re.finditer(r"\[(SPECIES_\w+)\]\s*=\s*TMHM_LEARNSET\((.*?)\)\s*,?\s*(?=\[|\})", bt, re.S):
            if "HM08_DIVE" in m.group(2) and m.group(1) != "SPECIES_NONE":
                c = self.map_species(m.group(1))
                if c is None:
                    self.errors.append(f"base species {m.group(1)} unresolved")
                else:
                    self.base_dive.add(c)

        for tbl, arrs, what in ((self.lvl_ptr, self.lvl_arrays, "level-up"), (self.tm_ptr, self.tm_arrays, "TM"),
                                (self.tutor_ptr, self.tutor_arrays, "tutor")):
            for s, a in tbl.items():
                if a not in arrs:
                    self.errors.append(f"{what} array {a} for {s} not found")
                if s not in self.species:
                    self.errors.append(f"{what} table species {s} not a R.O.W.E. species")
        for s in self.eggs:
            if s not in self.species:
                self.errors.append(f"egg species {s} not a R.O.W.E. species")

        # species mapping
        self.to_repo = {}
        for s in self.species:
            c = self.map_species(s)
            if c is None:
                self.errors.append(f"R.O.W.E. species {s} unresolved")
            else:
                self.to_repo[s] = c
        if self.errors:
            die("unresolved R.O.W.E. data:\n  " + "\n  ".join(self.errors))

        # verify R.O.W.E.'s TM numbering matches this repo
        for n, mv in self.tm_moves.items():
            if n > len(repo.tms) or repo.tms[n - 1] != mv:
                die(f"R.O.W.E. TM{n} {mv} doesn't match this repo's TM{n}")

    def parse_species(self, t):
        defs = {}
        for m in re.finditer(r"#define\s+(SPECIES_\w+|\w+_START)\s+([^\n]+)", t):
            defs[m.group(1)] = m.group(2).strip()
        cache = {}

        def ev(name):
            if name in cache:
                return cache[name]
            e = re.sub(r"\b(SPECIES_\w+|\w+_START)\b", lambda m: str(ev(m.group(1))), defs[name])
            try:
                v = eval(e)
            except Exception:
                v = None
            cache[name] = v
            return v
        out = {}
        for k in defs:
            if k.startswith("SPECIES_") and k not in ("SPECIES_NONE", "SPECIES_EGG"):
                v = ev(k)
                if isinstance(v, int):
                    out[k] = v
        return out

    @staticmethod
    def ptr_table(t, name):
        i = t.index(name)
        return {m.group(1): m.group(2) for m in re.finditer(r"\[(SPECIES_\w+)\]\s*=\s*(\w+)", t[i:])
                if m.group(1) != "SPECIES_NONE"}

    def move(self, m):
        c = self.repo.canon_move(m)
        if c is None:
            self.errors.append(f"R.O.W.E. move {m} unresolved")
            return m
        return c

    def map_species(self, s):
        repo = self.repo
        cands = []
        if s in SPECIES_MANUAL:
            cands.append(SPECIES_MANUAL[s])
        cands.append(s)
        t = s
        for a, b in SPECIES_SUFFIX_RULES:
            t = t.replace(a, b)
        cands.append(t)
        t = re.sub(r"_ZEN_MODE_GALAR$", "_GALAR_ZEN", t)
        for a, b in SPECIES_FALLBACK_RULES:
            t = t.replace(a, b)
        cands.append(t)
        for c in cands:
            cc = repo.canon_species(c)
            if cc:
                return cc
        return None


# --------------------------------------------------------------------------
# Build Custom data
# --------------------------------------------------------------------------

def dedupe(seq):
    return list(dict.fromkeys(seq))


def clean_levelup(lst, stats):
    out, seen_exact, first_above1 = [], set(), {}
    for lv, mv in lst:
        if (lv, mv) in seen_exact:
            stats["levelup exact duplicates removed"] += 1
            continue
        seen_exact.add((lv, mv))
        out.append((lv, mv))
    res = []
    for lv, mv in out:
        if lv > 1:
            if mv in first_above1:
                stats["levelup same move above Lv1 removed"] += 1
                if lv < first_above1[mv][0]:  # keep the earlier level
                    res.remove(first_above1[mv])
                    first_above1[mv] = (lv, mv)
                    res.append((lv, mv))
                continue
            first_above1[mv] = (lv, mv)
        res.append((lv, mv))
    srt = sorted(res, key=lambda x: x[0])  # stable: keeps order within a level
    if srt != res:
        stats["levelup lists re-sorted"] += 1
    return srt


def build(repo, rowe):
    stats = collections.Counter()
    tm_set = set(repo.tms)
    rowe_tm_universe = set(rowe.tm_moves.values())
    rowe_tutor_universe = set(rowe.tutor_moves)
    custom_tutors = sorted(set(repo.tutors) | rowe_tutor_universe)
    tutor_class = set(custom_tutors) | set(HM_TUTOR_MOVES)
    tutor_class -= tm_set
    teach_universe = tm_set | tutor_class
    official_universe = tm_set | set(repo.tutors) | set(HM_TUTOR_MOVES)
    not_in_rowe = sorted((official_universe - rowe_tm_universe - rowe_tutor_universe) - {"MOVE_DIVE"})

    def collect(table, arrays, what):
        own = {}
        for rs, arr in table.items():
            c = rowe.to_repo[rs]
            if c not in repo.enabled:
                continue
            data = arrays[arr]
            if c in own and own[c][1] != data:
                die(f"{what}: R.O.W.E. {rs} and {own[c][0]} both map to {c} with different data")
            own.setdefault(c, (rs, data))
        return {c: v[1] for c, v in own.items()}

    own_lvl = collect(rowe.lvl_ptr, rowe.lvl_arrays, "level-up")
    own_tm = collect(rowe.tm_ptr, rowe.tm_arrays, "TM")
    own_tutor = collect(rowe.tutor_ptr, rowe.tutor_arrays, "tutor")
    own_egg = collections.OrderedDict()
    for rs, mv in rowe.eggs.items():
        c = rowe.to_repo[rs]
        if c in repo.enabled:
            own_egg.setdefault(c, []).extend(mv)
    rowe_species = {rowe.to_repo[s] for s in rowe.species} & repo.enabled

    # mirror owners: species sharing an official learnset pointer
    def owners(ptrs, has_own):
        groups = collections.defaultdict(list)
        for s in repo.order:
            if ptrs.get(s):
                groups[ptrs[s]].append(s)
        own = {}
        for s in repo.order:
            if s in has_own or not ptrs.get(s):
                continue
            cands = [x for x in groups[ptrs[s]] if x in has_own]
            if cands:
                own[s] = cands[0]
        return own

    mirror_lvl = owners(repo.ptr_lvl, own_lvl)
    mirror_tm = owners(repo.ptr_teach, own_tm)
    mirror_tutor = owners(repo.ptr_teach, own_tutor)

    src = {"levelup": {}, "tm": {}, "tutor": {}, "egg": {}}

    # ---- level-up
    lvl = {}
    for s in repo.order:
        if s in own_lvl:
            lvl[s] = clean_levelup(own_lvl[s], stats)
            src["levelup"][s] = "rowe"
    for s in repo.order:
        if s not in lvl and s in mirror_lvl:
            lvl[s] = lvl[mirror_lvl[s]]
            src["levelup"][s] = "mirror"
    for s in repo.order:
        if s not in lvl:
            lvl[s] = repo.off_lvl[s]
            src["levelup"][s] = "official"

    custom_any = {s for s in repo.order if s in own_lvl or s in own_tm or s in own_tutor or s in own_egg
                  or s in mirror_lvl or s in mirror_tm or s in mirror_tutor}

    # ---- egg moves (base-species convention)
    egg = {}
    family_eggs = collections.OrderedDict()
    for s in repo.order:
        if s not in own_egg:
            continue
        lst = own_egg[s]
        d = dedupe(lst)
        stats["egg duplicates removed"] += len(lst) - len(d)
        root = repo.first_of_chain(s)
        if root != s:
            stats["egg lists moved to base species"] += 1
            stats["egg moves moved to base species"] += len(d)
            src.setdefault("egg_moved", []).append((s, root))
        family_eggs.setdefault(root, [])
        family_eggs[root].extend(d)
    for root in family_eggs:
        before = family_eggs[root]
        # root's own entries first, then moved ones (already in that order if root
        # comes first in species order; keep insertion order otherwise)
        family_eggs[root] = dedupe(before)
        stats["egg duplicates merged when moving to base"] += len(before) - len(family_eggs[root])
    for s in repo.order:
        root = repo.first_of_chain(s)
        carrier = (root == s) or bool(repo.off_egg[s])
        if carrier and root in family_eggs:
            egg[s] = family_eggs[root]
            src["egg"][s] = "rowe"
        else:
            egg[s] = repo.off_egg[s]
            src["egg"][s] = "official"

    # ---- teachables
    off_teach = {s: set(repo.off_teach[s]) for s in repo.order}
    teach = {}
    added1 = collections.Counter()
    added1_list = []
    added2 = collections.Counter()
    added2_list = []
    inherited_from_official = set()
    added_hm = collections.Counter()
    added_hm_list = []
    visiting = set()

    def base_parts(s):
        parts = set()
        # TM category
        if s in own_tm:
            parts |= set(own_tm[s])
            if s in rowe.base_dive:
                parts.add("MOVE_DIVE")
            src["tm"][s] = "rowe"
        elif s in mirror_tm:
            parts |= final(mirror_tm[s]) & tm_set
            src["tm"][s] = "mirror"
        else:
            parts |= off_teach[s] & tm_set
            src["tm"][s] = "official"
        # tutor category
        if s in own_tutor:
            parts |= set(own_tutor[s])
            src["tutor"][s] = "rowe"
        elif s in mirror_tutor:
            parts |= final(mirror_tutor[s]) & tutor_class
            src["tutor"][s] = "mirror"
        else:
            parts |= off_teach[s] & tutor_class
            src["tutor"][s] = "official"
        # moves R.O.W.E. had no TM/tutor for: expansion's rule (official)
        parts |= off_teach[s] & set(not_in_rowe)
        return parts

    # Fully official species whose pre-evolution chain has Custom data: official
    # teachables + rule 1 + HM superset + the chain's inherited compatibility.
    inherit_fb = {s for s in repo.order if s not in custom_any
                  and any(p in custom_any for p in repo.chain(s))}

    def vanilla_hm(s):
        learn = set(repo.off_teach[s]) | {m for _, m in repo.off_lvl[s]} | set(repo.off_egg[s])
        learn |= set(repo.off_egg[repo.first_of_chain(s)])
        return learn & set(HM_MOVES)

    def final(s):
        if s in teach:
            return teach[s]
        if s not in custom_any and s not in inherit_fb:
            teach[s] = off_teach[s]
            src["tm"][s] = src["tutor"][s] = "official"
            return teach[s]
        if s in visiting:
            die(f"cycle computing {s}")
        visiting.add(s)
        if s in inherit_fb:
            cur = set(off_teach[s])
            src["tm"][s] = src["tutor"][s] = "official+inherited"
        else:
            cur = base_parts(s)
        # rule 1
        for _, mv in lvl[s]:
            if mv in teach_universe and mv not in cur:
                cur.add(mv)
                kind = "TM" if mv in tm_set else "tutor"
                added1[kind] += 1
                added1_list.append((s, mv, kind))
        if "MOVE_DIVE" in egg[s] and "MOVE_DIVE" not in cur:
            cur.add("MOVE_DIVE")
            added1["TM"] += 1
            added1_list.append((s, "MOVE_DIVE", "TM (egg)"))
        # HM superset: whatever Vanilla lets it learn of the 8 former HM moves
        for mv in sorted(vanilla_hm(s) - cur):
            cur.add(mv)
            added_hm[mv] += 1
            added_hm_list.append((s, mv))
        # rule 2
        p = repo.prevo.get(s)
        if p is not None:
            pf = final(p)
            if p not in custom_any:
                inherited_from_official.add((s, p))
            for mv in sorted(pf - cur):
                cur.add(mv)
                kind = "TM" if mv in tm_set else "tutor"
                added2[kind] += 1
                added2_list.append((s, mv, p))
        visiting.discard(s)
        teach[s] = cur
        return cur

    for s in repo.order:
        final(s)

    # rule 1 G2 count: dual moves where R.O.W.E.'s TM and tutor lists disagree
    dual = rowe_tm_universe & rowe_tutor_universe
    g2 = 0
    for s in repo.order:
        if s in own_tm and s in own_tutor:
            for mv in dual:
                if (mv in own_tm[s]) != (mv in own_tutor[s]):
                    g2 += 1
    dup_tm = sum(len(v) - len(set(v)) for v in own_tm.values())
    dup_tutor = sum(len(v) - len(set(v)) for v in own_tutor.values())
    stats["TM duplicates removed"] = dup_tm
    stats["tutor duplicates removed"] = dup_tutor

    fb_changed = sorted((s for s in inherit_fb if teach[s] != off_teach[s]), key=repo.species_id.get)
    return dict(inherit_fb=inherit_fb, fb_changed=fb_changed, added_hm=added_hm,
                added_hm_list=added_hm_list, vanilla_hm=vanilla_hm, stats=stats, lvl=lvl, egg=egg, teach=teach, src=src, custom_tutors=custom_tutors,
                tm_set=tm_set, tutor_class=tutor_class, not_in_rowe=not_in_rowe, added1=added1,
                added1_list=added1_list, added2=added2, added2_list=added2_list, g2=g2,
                inherited_from_official=inherited_from_official, custom_any=custom_any,
                rowe_species=rowe_species, rowe_tutor_universe=rowe_tutor_universe,
                rowe_tm_universe=rowe_tm_universe, own_lvl=own_lvl, own_tm=own_tm,
                own_tutor=own_tutor, own_egg=own_egg)


# --------------------------------------------------------------------------
# Output
# --------------------------------------------------------------------------

def camel(species):
    return "".join(w.capitalize() for w in species[len("SPECIES_"):].split("_"))


def order_teach(repo, moves, tm_set):
    tms = [m for m in moves if m in tm_set]
    tms = sorted(tms, key=lambda m: repo.tm_number[m]) if repo.sort_tms_by_num else sorted(tms)
    return tms + sorted(m for m in moves if m not in tm_set)


def emit(repo, res, out_path, rowe_root):
    lvl_ptr, teach_ptr, egg_ptr = {}, {}, {}
    arrays = []
    lvl_seen, teach_seen, egg_seen = {}, {}, {}
    sizes = collections.Counter()
    for s in repo.order:
        if s not in res["custom_any"] and s not in res["inherit_fb"]:
            continue
        L = res["lvl"][s]
        if L != repo.off_lvl[s]:
            key = tuple(L)
            if key not in lvl_seen:
                name = f"sCustom{camel(s)}LevelUpLearnset"
                lvl_seen[key] = name
                body = "".join(f"    LEVEL_UP_MOVE({lv:2d}, {mv}),\n" for lv, mv in L)
                arrays.append(f"static const struct LevelUpMove {name}[] = {{\n{body}    LEVEL_UP_END\n}};\n")
                sizes["levelup"] += 4 * (len(L) + 1)
            lvl_ptr[s] = lvl_seen[key]
        T = res["teach"][s]
        if T != set(repo.off_teach[s]):
            key = tuple(order_teach(repo, T, res["tm_set"]))
            if key not in teach_seen:
                name = f"sCustom{camel(s)}TeachableLearnset"
                teach_seen[key] = name
                body = "".join(f"    {mv},\n" for mv in key)
                arrays.append(f"static const u16 {name}[] = {{\n{body}    MOVE_UNAVAILABLE,\n}};\n")
                sizes["teachable"] += 2 * (len(key) + 1)
            teach_ptr[s] = teach_seen[key]
    for s in repo.order:
        E = res["egg"][s]
        if set(E) != set(repo.off_egg[s]) and res["src"]["egg"][s] == "rowe":
            key = tuple(E)
            if key not in egg_seen:
                name = f"sCustom{camel(s)}EggMoveLearnset"
                egg_seen[key] = name
                body = "".join(f"    {mv},\n" for mv in key)
                arrays.append(f"static const u16 {name}[] = {{\n{body}    MOVE_UNAVAILABLE,\n}};\n")
                sizes["egg"] += 2 * (len(key) + 1)
            egg_ptr[s] = egg_seen[key]

    def table(ctype, name, ptrs):
        lines = [f"const {ctype} *const {name}[NUM_SPECIES] =\n{{"]
        for s in repo.order:
            if s in ptrs:
                lines.append(f"    [{s}] = {ptrs[s]},")
        lines.append("};\n")
        return "\n".join(lines)

    hdr = [
        "//",
        "// DO NOT MODIFY THIS FILE! It is generated by tools/custom_learnsets/make_custom_learnsets.py",
        "// from R.O.W.E.'s learnsets and this repo's official data. See that script for",
        "// the rules and for how to rerun it.",
        "//",
        "// Custom data mode learnsets, read by GetSpeciesLevelUpLearnset,",
        "// GetSpeciesTeachableLearnset, GetSpeciesEggMoves and GetTutorMoves in",
        "// src/pokemon.c only when IsCustomDataMode() is TRUE. A species without an",
        "// entry (NULL) uses its official learnset for that category.",
        "//",
        "// Teachable moves R.O.W.E. had no TM/tutor for use the official rule: "
        + ", ".join(res["not_in_rowe"]),
        "//",
        "",
        "#ifndef LEVEL_UP_MOVE",
        "#define LEVEL_UP_MOVE(lvl, moveLearned) {.move = moveLearned, .level = lvl}",
        "#endif",
        "#ifndef LEVEL_UP_END",
        "#define LEVEL_UP_END {.move = LEVEL_UP_MOVE_END, .level = 0}",
        "#endif",
        "",
        "// Tutor-move relearner list in Custom mode: official tutors + R.O.W.E.'s tutor moves.",
        "const u16 gCustomTutorMoves[] =",
        "{",
    ]
    hdr += [f"    {m}," for m in res["custom_tutors"]]
    hdr += ["    MOVE_UNAVAILABLE", "};", ""]
    sizes["tutors"] = 2 * (len(res["custom_tutors"]) + 1)
    text = "\n".join(hdr) + "\n" + "\n".join(arrays) + "\n"
    text += table("struct LevelUpMove", "gCustomLevelUpLearnsets", lvl_ptr) + "\n"
    text += table("u16", "gCustomTeachableLearnsets", teach_ptr) + "\n"
    text += table("u16", "gCustomEggMoveLearnsets", egg_ptr)
    with open(out_path, "w") as f:
        f.write(text)
    sizes["pointer tables"] = 3 * 4 * repo.lay["NUM_SPECIES"]
    return lvl_ptr, teach_ptr, egg_ptr, sizes


# --------------------------------------------------------------------------
# Verification (re-reads the written header)
# --------------------------------------------------------------------------

def verify(repo, res, out_path):
    t = open(out_path).read()
    arrays = {}
    for m in re.finditer(r"static const struct LevelUpMove (\w+)\[\] = \{(.*?)\};", t, re.S):
        arrays[m.group(1)] = [(int(a), b) for a, b in re.findall(r"LEVEL_UP_MOVE\(\s*(\d+), (\w+)\)", m.group(2))]
    for m in re.finditer(r"static const u16 (\w+)\[\] = \{(.*?)\};", t, re.S):
        arrays[m.group(1)] = [x for x in re.findall(r"MOVE_\w+", m.group(2)) if x != "MOVE_UNAVAILABLE"]

    def tbl(name):
        i = t.index(name + "[NUM_SPECIES]")
        body = t[i:t.index("};", i)]
        return {a: arrays[b] for a, b in re.findall(r"\[(SPECIES_\w+)\] = (\w+)", body)}
    L, T, E = tbl("gCustomLevelUpLearnsets"), tbl("gCustomTeachableLearnsets"), tbl("gCustomEggMoveLearnsets")
    i = t.index("gCustomTutorMoves[]")
    tutors = [x for x in re.findall(r"MOVE_\w+", t[i:t.index("};", i)]) if x != "MOVE_UNAVAILABLE"]

    lvl = lambda s: L.get(s, repo.off_lvl[s])
    teach = lambda s: set(T.get(s, repo.off_teach[s]))
    eggs = lambda s: E.get(s, repo.off_egg[s])
    tm_set = set(repo.tms)
    universe = tm_set | set(tutors) | set(HM_TUTOR_MOVES)
    fails = []
    for s in repo.order:
        tch = teach(s)
        missing_hm = res["vanilla_hm"](s) - tch
        if missing_hm:
            fails.append(f"HM superset: {s} misses {sorted(missing_hm)}")
        if s not in res["custom_any"]:
            if s in L or s in E or (s in T and s not in res["inherit_fb"]):
                fails.append(f"{s} has no R.O.W.E. data but has Custom entries")
            if s not in res["inherit_fb"]:
                continue
        tch = teach(s)
        for _, mv in lvl(s):
            if mv in universe and mv not in tch:
                fails.append(f"rule 1: {s} learns {mv} by level-up but isn't TM/tutor compatible")
        if "MOVE_DIVE" in eggs(s) and "MOVE_DIVE" not in tch:
            fails.append(f"rule 1: {s} has Dive egg move but no TM121")
        p = repo.prevo.get(s)
        if p is not None and not teach(p) <= tch:
            fails.append(f"rule 2: {s} misses {sorted(teach(p) - tch)[:5]} from {p}")
        lv = lvl(s)
        if s in L:
            if [x[0] for x in lv] != sorted(x[0] for x in lv):
                fails.append(f"{s} level-up not sorted")
            if len(set(lv)) != len(lv):
                fails.append(f"{s} level-up exact duplicate")
            above = [m for l_, m in lv if l_ > 1]
            if len(set(above)) != len(above):
                fails.append(f"{s} same move twice above Lv1")
        if s in T and len(T[s]) != len(set(T[s])):
            fails.append(f"{s} teachable duplicate")
        if s in E and len(E[s]) != len(set(E[s])):
            fails.append(f"{s} egg duplicate")
    if len(tutors) != len(set(tutors)):
        fails.append("gCustomTutorMoves duplicate")
    return fails, lvl, teach, eggs, L, T, E, tutors


# --------------------------------------------------------------------------

def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--rowe", default=os.path.join("..", "RoweSource"), help="R.O.W.E. source root (read-only)")
    ap.add_argument("--out", default=HEADER_PATH)
    ap.add_argument("--verbose", action="store_true", help="list every rule 1/2 addition")
    args = ap.parse_args()
    if not os.path.exists("include/constants/tms_hms.h"):
        die("run from the repository root")

    repo = Repo()
    rowe = Rowe(args.rowe, repo)
    res = build(repo, rowe)
    lvl_ptr, teach_ptr, egg_ptr, sizes = emit(repo, res, args.out, args.rowe)
    fails, lvl, teach, eggs, L, T, E, tutors = verify(repo, res, args.out)

    st = res["stats"]
    src = res["src"]
    print(f"Wrote {args.out}")
    print(f"R.O.W.E. species: {len(rowe.species)} -> {len(res['rowe_species'])} enabled here "
          f"({sum(1 for s, c in rowe.to_repo.items() if s != c)} renamed); "
          f"repo species: {len(repo.order)}")
    print(f"Species with any R.O.W.E. data: {len(res['custom_any'])}; "
          f"fully official: {len(repo.order) - len(res['custom_any'])}")
    for cat in ("levelup", "tm", "tutor", "egg"):
        c = collections.Counter(src[cat].values())
        print(f"  {cat:8}: R.O.W.E. {c['rowe']}, mirrored form {c['mirror']}, official {c['official']}")
    print(f"Custom entries emitted: level-up {len(lvl_ptr)}, teachable {len(teach_ptr)}, egg {len(egg_ptr)}")
    print(f"Rule 1 additions: TM {res['added1']['TM']}, tutor {res['added1']['tutor']} "
          f"(+ R.O.W.E. TM/tutor disagreements on dual moves resolved by the merged list: {res['g2']})")
    print(f"HM superset additions: {sum(res['added_hm'].values())} " +
          ", ".join(f"{k[5:]} {v}" for k, v in sorted(res['added_hm'].items())))
    print(f"Rule 2 additions: TM-class {res['added2']['TM']}, tutor-class {res['added2']['tutor']}")
    print(f"Fully official species inheriting from a Custom pre-evolution: {len(res['inherit_fb'])}, "
          f"teachables changed: {len(res['fb_changed'])}")
    if res["inherited_from_official"]:
        print("  inherited from a pre-evolution using official data: " +
              ", ".join(f"{a}<-{b}" for a, b in sorted(res["inherited_from_official"])))
    print("Clean-ups: " + ", ".join(f"{k} {v}" for k, v in sorted(st.items())))
    for s, r in src.get("egg_moved", []):
        print(f"  egg moves moved {s} -> {r}")
    print(f"Teachable moves using the official rule (not R.O.W.E. TM/tutor moves): {res['not_in_rowe']}")
    extra = sorted(set(tutors) - set(repo.tutors) - set(repo.tms) - set(HM_TUTOR_MOVES))
    print(f"gCustomTutorMoves: {len(tutors)} moves; R.O.W.E.-only tutor moves ({len(extra)}): {extra}")
    print("Data sizes (bytes): " + ", ".join(f"{k} {v}" for k, v in sizes.items()) +
          f", total {sum(sizes.values())}")

    print("\nHM moves (species compatible through the teachable list, Custom vs Vanilla):")
    for mv in HM_MOVES:
        c = sum(1 for s in repo.order if mv in teach(s))
        v = sum(1 for s in repo.order if mv in set(repo.off_teach[s]))
        vv = sum(1 for s in repo.order if mv in res["vanilla_hm"](s))
        print(f"  {mv:16} Custom {c:4}   Vanilla teachable {v:4}   Vanilla any method {vv:4}")

    print("\nSpot checks (Custom mode):")
    def show(s, what):
        if what == "lvl":
            return " ".join(f"{l}:{m[5:]}" for l, m in lvl(s))
        if what == "tm":
            return " ".join(f"TM{repo.tm_number[m]}" for m in sorted(teach(s) & set(repo.tms), key=repo.tm_number.get))
    checks = [
        ("Beartic Earthquake (TM26)", "MOVE_EARTHQUAKE" in teach("SPECIES_BEARTIC")),
        ("Beartic Close Combat (tutor)", "MOVE_CLOSE_COMBAT" in teach("SPECIES_BEARTIC")
         and "MOVE_CLOSE_COMBAT" in tutors),
        ("Kricketot Cut (tutor)", "MOVE_CUT" in teach("SPECIES_KRICKETOT")),
        ("Wingull Dive (TM121)", "MOVE_DIVE" in teach("SPECIES_WINGULL")),
        ("Pelipper Dive (TM121)", "MOVE_DIVE" in teach("SPECIES_PELIPPER")),
        ("Growlithe-Hisui falls back (no Custom entries)",
         all("SPECIES_GROWLITHE_HISUI" not in x for x in (L, T, E))),
        ("Sprigatito (Gen 9) falls back (no Custom entries)",
         all("SPECIES_SPRIGATITO" not in x for x in (L, T, E))),
        ("Garchomp uses R.O.W.E. level-up", "SPECIES_GARCHOMP" in L),
        ("Eevee uses R.O.W.E. teachables", "SPECIES_EEVEE" in T),
    ]
    for name, ok in checks:
        print(f"  [{'OK' if ok else '--'}] {name}")
    print("  Garchomp level-up: " + show("SPECIES_GARCHOMP", "lvl"))
    print("  Eevee TMs: " + show("SPECIES_EEVEE", "tm"))
    for s in ("SPECIES_KINGAMBIT", "SPECIES_WYRDEER", "SPECIES_KLEAVOR", "SPECIES_ANNIHILAPE", "SPECIES_URSALUNA"):
        if s in res["inherit_fb"]:
            gained = sorted(teach(s) - set(repo.off_teach[s]))
            print(f"  {s[8:]} gains {len(gained)} over official: " + " ".join(m[5:] for m in gained[:12])
                  + (" ..." if len(gained) > 12 else ""))
    print("  Fallback species changed: " + " ".join(s[8:] for s in res["fb_changed"]))
    if args.verbose:
        for s, mv in res["added_hm_list"]:
            print(f"  hm {s} {mv}")
        for s, mv, k in res["added1_list"]:
            print(f"  rule1 {s} {mv} {k}")
        for s, mv, p in res["added2_list"]:
            print(f"  rule2 {s} {mv} <- {p}")

    if fails:
        print(f"\nVERIFICATION FAILED ({len(fails)}):", file=sys.stderr)
        for f in fails[:50]:
            print("  " + f, file=sys.stderr)
        sys.exit(1)
    print("\nVerification passed: rule 1, rule 2, sorting and duplicate checks hold for all species.")


if __name__ == "__main__":
    main()
