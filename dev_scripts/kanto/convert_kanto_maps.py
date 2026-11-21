#!/usr/bin/env python3
"""
Convert the FRLG (Kanto/Sevii) maps so they can be linked into the Emerald build
as a freely explorable, story-free region.

Usage (from the repo root):
    python3 dev_scripts/kanto/convert_kanto_maps.py <orig_maps_dir> [--report out.json]

<orig_maps_dir> must contain pristine copies of the data/maps/*_Frlg folders
(e.g. extracted from the commit before this conversion with
`git archive <base> data/maps | tar -x`).  The converted map.json and
scripts.inc are written over data/maps/*_Frlg/.

What it does, per map:
  * object events
      - trainers, item balls, script-less cutscene actors, Team Rocket, and any
        NPC whose script does more than talk (gives items, battles, moves the
        story, ...) are removed
      - simple talkers (msgbox/yes-no chatter, cries, ...) are kept with their
        hide flag cleared.  Story flags are folded as "set" (post-game state)
        and never referenced at runtime, since FRLG flag/var numbers collide
        with Emerald's.
      - Pokemon Center nurses use Emerald's Common_EventScript_PkmnCenterNurse,
        Mart clerks use Emerald's standard pokemart flow with the FRLG lists
      - Cut trees / Rock Smash rocks / Strength boulders use Emerald's common
        field-move scripts, always present (flag 0)
  * bg events: signs kept when their script is simple, hidden items removed
  * coord events: all removed (story triggers)
  * map scripts: reduced to weather / respawn / metatile / layout changes,
    with story flags folded as "set".  No FRLG flag or var is referenced.
  * music: replaced by Hoenn songs (see music_for_map)
"""

import json
import os
import re
import sys
import glob
import collections

ROOT = os.getcwd()
MAPS_DIR = os.path.join(ROOT, 'data', 'maps')

# ---------------------------------------------------------------------------
# Script parsing
# ---------------------------------------------------------------------------

LABEL_RE = re.compile(r'^([A-Za-z_]\w*)(::?)\s*(@.*)?$')


class Block:
    def __init__(self, name, glob_):
        self.name = name
        self.is_global = glob_
        self.lines = []


def parse_scripts(text):
    preamble = []
    blocks = []
    order = {}
    cur = None
    for raw in text.split('\n'):
        line = raw.rstrip()
        m = LABEL_RE.match(line)
        if m and not line.startswith('\t') and not line.startswith(' '):
            cur = Block(m.group(1), m.group(2) == '::')
            order[cur.name] = len(blocks)
            blocks.append(cur)
            continue
        if cur is None:
            preamble.append(line)
        else:
            cur.lines.append(line)
    return preamble, blocks, order


def split_cmd(line):
    s = line.split('@', 1)[0].strip()
    if not s:
        return None, []
    parts = s.split(None, 1)
    cmd = parts[0]
    args = []
    if len(parts) > 1:
        args = [a for a in re.split(r'\s*,\s*|\s+', parts[1].strip()) if a]
    return cmd, args


# ---------------------------------------------------------------------------
# Classification helpers
# ---------------------------------------------------------------------------

SAFE_VARS = re.compile(r'^(VAR_TEMP_[0-9A-F]+|VAR_RESULT|VAR_0x800[0-9AB]|VAR_FACING|VAR_LAST_TALKED|VAR_SPECIAL_\w+)$')
TEMP_FLAG = re.compile(r'^FLAG_TEMP_[0-9A-F]+$')

MSG_CMDS = {'msgbox', 'message', 'waitmessage', 'closemessage', 'waitbuttonpress',
            'lock', 'lockall', 'faceplayer', 'release', 'releaseall', 'textcolor',
            'playse', 'waitse', 'playmoncry', 'waitmoncry', 'delay', 'checkplayergender',
            'bufferspeciesname', 'bufferitemname', 'buffermovename', 'bufferstdstring',
            'buffernumberstring', 'showmonpic', 'hidemonpic', 'random', 'waitmovement',
            'braillemsgbox', 'signmsg', 'normalmsg', 'yesnobox', 'getpartysize',
            'waitfanfare', 'playfanfare'}
# commands that are simply removed (FRLG-only bookkeeping)
DROP_CMDS = {'famechecker', 'setworldmapflag', 'incrementgamestat'}
TERMINATORS = {'end', 'return', 'goto', 'releaseall_end'}
COND_GOTO = {'goto_if_eq', 'goto_if_ne', 'goto_if_lt', 'goto_if_ge', 'goto_if_le', 'goto_if_gt'}
COND_CALL = {'call_if_eq', 'call_if_ne', 'call_if_lt', 'call_if_ge', 'call_if_le', 'call_if_gt'}

PLAYER_IDS = {'LOCALID_PLAYER', 'OBJ_EVENT_ID_PLAYER', 'VAR_LAST_TALKED', 'OBJ_EVENT_ID_CAMERA'}

# Map script commands allowed in on-load/on-transition/on-resume scripts
MAPSCRIPT_CMDS = {'setweather', 'doweather', 'setmetatile', 'setmaplayoutindex', 'setflashlevel',
                  'setescapewarp', 'setdivewarp', 'setholewarp', 'setstepcallback',
                  'setobjectxyperm', 'setobjectmovementtype', 'turnobject', 'special_ok'}

# Specials that are harmless / meaningful for both games
SAFE_SPECIALS = {'SetSeenMon'}


# FLAG_WORLD_MAP_* flags that the Emerald build backs with real (formerly unused) flags,
# so visiting these towns unlocks them as Fly destinations.
KANTO_FLY_FLAGS = {'FLAG_WORLD_MAP_' + n for n in (
    'PALLET_TOWN', 'VIRIDIAN_CITY', 'PEWTER_CITY', 'CERULEAN_CITY', 'LAVENDER_TOWN', 'VERMILION_CITY',
    'CELADON_CITY', 'FUCHSIA_CITY', 'CINNABAR_ISLAND', 'INDIGO_PLATEAU_EXTERIOR', 'SAFFRON_CITY',
    'ONE_ISLAND', 'TWO_ISLAND', 'THREE_ISLAND', 'FOUR_ISLAND', 'FIVE_ISLAND', 'SIX_ISLAND', 'SEVEN_ISLAND',
    'ROUTE4_POKEMON_CENTER_1F', 'ROUTE10_POKEMON_CENTER_1F')}
DROP_MOVEMENTS = {'Common_Movement_FaceOriginalDirection'}
VAR_FINAL = {}   # story var -> value assumed at runtime (max value any FRLG script sets)


def compute_var_final(orig):
    for d in os.listdir(orig):
        p = os.path.join(orig, d, 'scripts.inc')
        if not os.path.exists(p):
            continue
        for l in open(p):
            mm = re.match(r'^\s*setvar\s+(VAR_\w+)\s*,\s*(\d+)', l)
            if mm and not SAFE_VARS.match(mm.group(1)):
                VAR_FINAL[mm.group(1)] = max(VAR_FINAL.get(mm.group(1), 0), int(mm.group(2)))


class Ctx:
    def __init__(self, mapname, blocks, order, equs, kept_localids, syms, heal_ids, layout_ids):
        self.mapname = mapname
        self.blocks = blocks
        self.order = order
        self.equs = equs
        self.kept_localids = kept_localids  # set or None (provisional)
        self.syms = syms
        self.heal_ids = heal_ids
        self.layout_ids = layout_ids

    def resolve(self, tok):
        seen = 0
        while tok in self.equs and seen < 5:
            tok = self.equs[tok]
            seen += 1
        return tok


def is_story_flag(ctx, tok):
    t = ctx.resolve(tok)
    return t.startswith('FLAG_') and not TEMP_FLAG.match(t)


def is_story_var(ctx, tok):
    t = ctx.resolve(tok)
    return t.startswith('VAR_') and not SAFE_VARS.match(t)


class Reject(Exception):
    pass


def analyze(ctx, entry, mode):
    """
    Walk the script starting at `entry`.
    mode: 'npc' (object/bg event), or 'map' (map script: unknown commands are dropped)
    Returns (transforms, reached_blocks, refs, deps)
      transforms: {(block, idx): new_line or None(drop)}  only for lines that change
      reached: set of block names to emit
      refs: set of referenced labels (texts/movements/data/other scripts)
      deps: set of LOCALIDs the script needs
    Raises Reject(reason) for npc mode when the script does something non-trivial.
    """
    transforms = {}
    reached = set()
    refs = set()
    deps = set()
    visited = set()
    work = [(entry, 0)]

    def local_label(lbl):
        return lbl in ctx.order

    def follow(lbl, key=None, is_goto=False):
        if local_label(lbl):
            work.append((lbl, 0))
        elif mode == 'map' and key is not None and not (lbl in ctx.syms and lbl.startswith('Common_')):
            transforms[key] = '\tend' if is_goto else None
        elif lbl in ctx.syms:
            # external script we trust only if it's an Emerald common one
            if mode == 'npc' and not lbl.startswith('Common_'):
                raise Reject('calls external ' + lbl)
            refs.add(lbl)
        else:
            raise Reject('calls unknown ' + lbl)

    def need_obj(tok, idx_key):
        t = ctx.resolve(tok)
        if t in PLAYER_IDS:
            return True
        if t.startswith('LOCALID_'):
            if ctx.kept_localids is not None and t not in ctx.kept_localids:
                return False
            deps.add(t)
            return True
        return False

    def bad(reason, key):
        if mode == 'npc':
            raise Reject(reason)
        transforms[key] = None

    while work:
        bname, start = work.pop()
        if (bname, start) in visited:
            continue
        visited.add((bname, start))
        if bname not in ctx.order:
            follow(bname)
            continue
        reached.add(bname)
        bi = ctx.order[bname]
        blk = ctx.blocks[bi]
        terminated = False
        for i in range(start, len(blk.lines)):
            line = blk.lines[i]
            key = (bname, i)
            st = line.strip()
            if st.startswith('#'):
                continue
            cmd, args = split_cmd(line)
            if cmd is None:
                continue
            if cmd in ('.string', '.braille', '.2byte', '.byte', '.4byte', '.align'):
                # data reached by fallthrough -> not code
                raise Reject('fell into data in ' + bname) if mode == 'npc' else None
                terminated = True
                break
            if cmd in ('end', 'return', 'releaseall_end'):
                terminated = True
                break
            if cmd == 'goto':
                follow(args[0], key, True)
                terminated = True
                break
            if cmd == 'call':
                if args[0] == 'EventScript_PkmnCenterNurse_Frlg':
                    raise Reject('nurse')
                follow(args[0], key)
                continue
            if cmd in ('goto_if_set', 'goto_if_unset', 'call_if_set', 'call_if_unset'):
                flag, lbl = args[0], args[1]
                is_goto = cmd.startswith('goto')
                if is_story_flag(ctx, flag):
                    taken = cmd.endswith('_set')  # story flags are SET
                    if taken:
                        transforms[key] = '\t%s %s' % ('goto' if is_goto else 'call', lbl)
                        follow(lbl, key, is_goto)
                        if is_goto:
                            terminated = True
                            break
                    else:
                        transforms[key] = None
                    continue
                follow(lbl, key)
                continue
            if cmd in ('goto_if_defeated', 'goto_if_not_defeated', 'call_if_defeated', 'call_if_not_defeated'):
                lbl = args[1]
                is_goto = cmd.startswith('goto')
                taken = '_not_' not in cmd
                if taken:
                    transforms[key] = '\t%s %s' % ('goto' if is_goto else 'call', lbl)
                    follow(lbl, key, is_goto)
                    if is_goto:
                        terminated = True
                        break
                else:
                    transforms[key] = None
                continue
            if cmd in COND_GOTO or cmd in COND_CALL:
                var = args[0]
                rv = ctx.resolve(var)
                if is_story_var(ctx, var) and rv in VAR_FINAL and re.match(r'^\d+$', args[1]):
                    cur, val = VAR_FINAL[rv], int(args[1])
                    op = cmd.split('_')[-1]
                    taken = {'eq': cur == val, 'ne': cur != val, 'lt': cur < val, 'ge': cur >= val,
                             'le': cur <= val, 'gt': cur > val}[op]
                    is_goto = cmd in COND_GOTO
                    if taken:
                        transforms[key] = '\t%s %s' % ('goto' if is_goto else 'call', args[2])
                        follow(args[2], key, is_goto)
                        if is_goto:
                            terminated = True
                            break
                    else:
                        transforms[key] = None
                    continue
                if is_story_var(ctx, var):
                    bad('reads story var ' + var, key)
                    continue
                follow(args[2], key)
                continue
            if cmd == 'switch':
                if is_story_var(ctx, args[0]):
                    bad('switch on story var', key)
                continue
            if cmd == 'case':
                follow(args[1], key)
                continue
            if cmd in ('setflag', 'clearflag'):
                if is_story_flag(ctx, args[0]):
                    transforms[key] = None
                continue
            if cmd in ('setvar', 'addvar', 'subvar', 'copyvar'):
                if is_story_var(ctx, args[0]) or (cmd == 'copyvar' and is_story_var(ctx, args[1])):
                    if mode == 'npc' and cmd == 'copyvar' and not is_story_var(ctx, args[0]):
                        raise Reject('copies story var')
                    transforms[key] = None
                continue
            if cmd == 'setworldmapflag' and args and args[0] in KANTO_FLY_FLAGS:
                continue   # real Emerald flag (include/constants/flags.h): enables flying here
            if cmd in DROP_CMDS:
                transforms[key] = None
                continue
            if cmd in ('applymovement', 'turnobject'):
                if not need_obj(args[0], key):
                    bad('moves object ' + args[0], key)
                    continue
                if cmd == 'applymovement':
                    mv = args[1]
                    if mv in DROP_MOVEMENTS:
                        transforms[key] = None
                        continue
                    if local_label(mv):
                        refs.add(mv)
                    elif mv not in ctx.syms:
                        raise Reject('unknown movement ' + mv)
                continue
            if cmd in MSG_CMDS:
                if cmd in ('msgbox', 'message', 'braillemsgbox', 'signmsg') and args:
                    t = args[0]
                    if local_label(t):
                        refs.add(t)
                    elif re.match(r'^[A-Za-z_]\w*$', t):
                        if t not in ctx.syms:
                            raise Reject('unknown text ' + t)
                continue
            if cmd == 'pokemart':
                raise Reject('mart')
            if cmd == 'special' and args and args[0] in SAFE_SPECIALS:
                continue
            if cmd == 'setrespawn':
                if args[0] in ctx.heal_ids:
                    continue
                transforms[key] = None
                continue
            if mode == 'map' and cmd in MAPSCRIPT_CMDS:
                if cmd in ('setobjectxyperm', 'setobjectmovementtype', 'turnobject'):
                    if not need_obj(args[0], key):
                        transforms[key] = None
                elif cmd == 'setmaplayoutindex':
                    if args[0] not in ctx.layout_ids:
                        transforms[key] = None
                continue
            if mode == 'map' and cmd == 'map_script_2':
                continue
            bad('cmd ' + cmd + (' ' + args[0] if cmd in ('special', 'specialvar') and args else ''), key)
        if not terminated:
            # falls through into next block
            if bi + 1 < len(ctx.blocks):
                work.append((ctx.blocks[bi + 1].name, 0))
    return transforms, reached, refs, deps


# ---------------------------------------------------------------------------
# Data that is referenced (texts, movements, item lists)
# ---------------------------------------------------------------------------

def collect_data_closure(ctx, names):
    """Given referenced labels, add fallthrough blocks for data (e.g. text split across labels)."""
    out = set()
    for n in names:
        if n not in ctx.order:
            continue
        bi = ctx.order[n]
        out.add(n)
        # if the block doesn't end in a terminator ($ string end / step_end / ITEM_NONE),
        # include following blocks
        while True:
            blk = ctx.blocks[bi]
            body = [l.strip() for l in blk.lines if l.strip() and not l.strip().startswith('@')]
            if not body:
                bi += 1
                if bi >= len(ctx.blocks):
                    break
                out.add(ctx.blocks[bi].name)
                continue
            last = body[-1]
            if last.endswith('$"') or last.startswith('step_end') or 'ITEM_NONE' in last or last.startswith('.byte') or last.startswith('.2byte') or last.startswith('.align') or last.startswith('end') or last.startswith('release'):
                break
            bi += 1
            if bi >= len(ctx.blocks):
                break
            out.add(ctx.blocks[bi].name)
    return out


# ---------------------------------------------------------------------------
# Music
# ---------------------------------------------------------------------------

MUS_LAND = 'MUS_ROUTE101'
MUS_WATER = 'MUS_ROUTE104'
MUS_LAVENDER = 'MUS_MT_PYRE'
MUS_CITY = 'MUS_RUSTBORO'
MUS_TOWN = 'MUS_LITTLEROOT'
MUS_CENTER = 'MUS_POKE_CENTER'
MUS_MART = 'MUS_POKE_MART'
MUS_GYM = 'MUS_GYM'
MUS_CAVE = 'MUS_PETALBURG_WOODS'   # Granite Cave's song
MUS_FOREST = 'MUS_PETALBURG_WOODS'

TOWN_NAMES = ['PalletTown', 'ViridianCity', 'PewterCity', 'CeruleanCity', 'LavenderTown', 'VermilionCity',
              'CeladonCity', 'FuchsiaCity', 'CinnabarIsland', 'IndigoPlateau', 'SaffronCity',
              'OneIsland', 'TwoIsland', 'ThreeIsland', 'FourIsland', 'FiveIsland', 'SixIsland', 'SevenIsland']

# Outdoor (non-town) Sevii areas, keyed by name prefix
SEVII_ROUTES = ['OneIsland_KindleRoad', 'OneIsland_TreasureBeach', 'TwoIsland_CapeBrink', 'ThreeIsland_BondBridge',
                'ThreeIsland_Port', 'FiveIsland_ResortGorgeous', 'FiveIsland_WaterLabyrinth', 'FiveIsland_Meadow',
                'FiveIsland_MemorialPillar', 'SixIsland_OutcastIsland', 'SixIsland_GreenPath', 'SixIsland_WaterPath',
                'SixIsland_RuinValley', 'SevenIsland_TrainerTower', 'SevenIsland_SevaultCanyon_Entrance',
                'SevenIsland_SevaultCanyon', 'SevenIsland_TanobyRuins']

DUNGEON_MUSIC = [
    # (prefix, music)  -- first match wins
    ('PokemonLeague_HallOfFame', 'MUS_HALL_OF_FAME_ROOM'),
    ('PokemonLeague_', 'MUS_VICTORY_ROAD'),
    ('VictoryRoad_', 'MUS_VICTORY_ROAD'),
    ('ViridianForest', MUS_FOREST),
    ('ThreeIsland_BerryForest', MUS_FOREST),
    ('SixIsland_PatternBush', MUS_FOREST),
    ('PokemonTower_', 'MUS_MT_PYRE'),
    ('PokemonMansion_', 'MUS_ABANDONED_SHIP'),
    ('RocketHideout_', 'MUS_AQUA_MAGMA_HIDEOUT'),
    ('FiveIsland_RocketWarehouse', 'MUS_AQUA_MAGMA_HIDEOUT'),
    ('SilphCo_', MUS_CITY),
    ('SSAnne_', 'MUS_SAILING'),
    ('SafariZone_', 'MUS_SAFARI_ZONE'),
    ('PowerPlant', 'MUS_MT_PYRE'),            # like New Mauville
    ('CeruleanCave_', 'MUS_CAVE_OF_ORIGIN'),
    ('MtEmber_', 'MUS_MT_CHIMNEY'),
    ('SevenIsland_TanobyRuins_', 'MUS_SEALED_CHAMBER'),
    ('SixIsland_DottedHole_', 'MUS_SEALED_CHAMBER'),
    ('TrainerTower_', 'MUS_B_FRONTIER'),
    ('NavelRock_', 'MUS_SEALED_CHAMBER'),
    ('BirthIsland_', 'MUS_SEALED_CHAMBER'),
    ('BattleColosseum_', 'MUS_EVER_GRANDE'),
    ('TradeCenter', 'MUS_EVER_GRANDE'),
    ('RecordCorner', 'MUS_EVER_GRANDE'),
    ('UnionRoom', 'MUS_EVER_GRANDE'),
    ('MtMoon_', MUS_CAVE),
    ('RockTunnel_', MUS_CAVE),
    ('DiglettsCave_', MUS_CAVE),
    ('SeafoamIslands_', MUS_CAVE),
    ('UndergroundPath_', MUS_CAVE),
    ('FourIsland_IcefallCave_', MUS_CAVE),
    ('FiveIsland_LostCave_', MUS_CAVE),
    ('SixIsland_AlteringCave', MUS_CAVE),
    ('ThreeIsland_DunsparceTunnel', MUS_CAVE),
    ('SevenIsland_SevaultCanyon_TanobyKey', MUS_CAVE),
    ('OneIsland_KindleRoad_EmberSpa', MUS_CAVE),
]

BUILDING_MUSIC = [
    ('_PokemonCenter_', MUS_CENTER),
    ('_Mart', MUS_MART),
    ('_Gym', MUS_GYM),
    ('_GameCorner', 'MUS_GAME_CORNER'),
    ('_Museum_', 'MUS_OCEANIC_MUSEUM'),
    ('_ProfessorOaksLab', 'MUS_BIRCH_LAB'),
    ('_PokemonLab_', 'MUS_BIRCH_LAB'),
]


def music_for_map(name, outdoor_music, water_routes):
    base = name[:-len('_Frlg')]
    for pre, mus in DUNGEON_MUSIC:
        if base.startswith(pre) or base == pre.rstrip('_'):
            return mus, 'dungeon:' + pre
    for pre, mus in BUILDING_MUSIC:
        if pre in base + '_':
            return mus, 'building' + pre
    if base in outdoor_music:
        return outdoor_music[base]
    # indoor map: inherit from the longest matching outdoor prefix
    best = None
    for out in outdoor_music:
        if base.startswith(out + '_') and (best is None or len(out) > len(best)):
            best = out
    if best:
        return outdoor_music[best][0], 'inherit:' + best
    return MUS_LAND, 'fallback'


# ---------------------------------------------------------------------------
# Water classification of outdoor routes
# ---------------------------------------------------------------------------

WATER_MB = None


def load_behaviors():
    global WATER_MB
    txt = open(os.path.join(ROOT, 'include/constants/metatile_behaviors.h')).read()
    body = txt[txt.index('enum {') + 6: txt.index('NUM_METATILE_BEHAVIORS')]
    names = [n.strip().split('=')[0].strip() for n in body.split(',')]
    names = [n for n in names if n]
    ids = {n: i for i, n in enumerate(names)}
    water = ['MB_POND_WATER', 'MB_INTERIOR_DEEP_WATER', 'MB_DEEP_WATER', 'MB_WATERFALL', 'MB_SOOTOPOLIS_DEEP_WATER',
             'MB_OCEAN_WATER', 'MB_EASTWARD_CURRENT', 'MB_WESTWARD_CURRENT', 'MB_NORTHWARD_CURRENT',
             'MB_SOUTHWARD_CURRENT', 'MB_NO_SURFACING', 'MB_SEAWEED', 'MB_SEAWEED_NO_SURFACING']
    WATER_MB = {ids[w] for w in water if w in ids}


def tileset_dir(label):
    # gTileset_General_Frlg -> data/tilesets/primary/general_frlg ...
    hdr = open(os.path.join(ROOT, 'src/data/tilesets/headers.h')).read()
    m = re.search(r'const struct Tileset ' + re.escape(label) + r' =\s*\{(.*?)\};', hdr, re.S)
    attr = re.search(r'\.metatileAttributes = (\w+)', m.group(1)).group(1)
    mt = open(os.path.join(ROOT, 'src/data/tilesets/metatiles.h')).read()
    m2 = re.search(re.escape(attr) + r'\[\] = INCBIN_U\w+\("([^"]+)"\)', mt)
    return m2.group(1)


def water_fraction(layout):
    import struct
    if WATER_MB is None:
        load_behaviors()
    prim = open(os.path.join(ROOT, tileset_dir(layout['primary_tileset'])), 'rb').read()
    sec = open(os.path.join(ROOT, tileset_dir(layout['secondary_tileset'])), 'rb').read()
    pa = struct.unpack('<%dI' % (len(prim) // 4), prim)
    sa = struct.unpack('<%dI' % (len(sec) // 4), sec)
    data = open(os.path.join(ROOT, layout['blockdata_filepath']), 'rb').read()
    blocks = struct.unpack('<%dH' % (len(data) // 2), data)
    water = total = 0
    for b in blocks:
        mid = b & 0x3FF
        if mid < 640:
            a = pa[mid] if mid < len(pa) else 0
        else:
            a = sa[mid - 640] if mid - 640 < len(sa) else 0
        beh = a & 0x1FF
        total += 1
        if beh in WATER_MB:
            water += 1
    return water / max(total, 1)


# ---------------------------------------------------------------------------
# Main conversion
# ---------------------------------------------------------------------------

def main():
    orig = sys.argv[1]
    report_path = None
    if '--report' in sys.argv:
        report_path = sys.argv[sys.argv.index('--report') + 1]
    syms = set(open(sys.argv[sys.argv.index('--syms') + 1]).read().split()) if '--syms' in sys.argv else set()

    heal = json.load(open(os.path.join(ROOT, 'src/data/heal_locations.json')))
    heal_ids = {h['id'] for h in heal['heal_locations']} if isinstance(heal, dict) else {h['id'] for h in heal}
    layouts = json.load(open(os.path.join(ROOT, 'data/layouts/layouts.json')))['layouts']
    layout_by_id = {l['id']: l for l in layouts if 'id' in l}
    layout_ids = set(layout_by_id)

    stats = collections.Counter()
    report = {'maps': {}, 'removed_objects': [], 'kept_flagged': [], 'music': {}, 'water_routes': [],
              'map_script_drops': {}}

    names = sorted(os.listdir(orig))
    compute_var_final(orig)

    # Pass 0: outdoor music classification
    outdoor = {}
    for name in names:
        m = json.load(open(os.path.join(orig, name, 'map.json')))
        base = name[:-len('_Frlg')]
        mt = m.get('map_type')
        if base == 'LavenderTown':
            outdoor[base] = (MUS_LAVENDER, 'lavender')
        elif base in TOWN_NAMES or base == 'IndigoPlateau_Exterior' or base == 'SaffronCity_Connection':
            if 'City' in base:
                outdoor[base] = (MUS_CITY, 'city')
            else:
                outdoor[base] = (MUS_TOWN, 'town')
        elif re.match(r'^Route\d+', base) and '_' not in base.replace('_North', '').replace('_South', '') or base in SEVII_ROUTES:
            frac = water_fraction(layout_by_id[m['layout']])
            if frac >= 0.5:
                outdoor[base] = (MUS_WATER, 'water route (%.0f%% water)' % (frac * 100))
                report['water_routes'].append((base, round(frac, 2)))
            else:
                outdoor[base] = (MUS_LAND, 'land route (%.0f%% water)' % (frac * 100))
    # IndigoPlateau indoor prefix
    outdoor.setdefault('IndigoPlateau', (MUS_TOWN, 'town'))

    # Pass 1: per map conversion
    all_kept = {}
    for name in names:
        src_dir = os.path.join(orig, name)
        m = json.load(open(os.path.join(src_dir, 'map.json')))
        text = open(os.path.join(src_dir, 'scripts.inc')).read() if os.path.exists(os.path.join(src_dir, 'scripts.inc')) else ''
        preamble, blocks, order = parse_scripts(text)
        equs = {}
        for l in preamble + [x for b in blocks for x in b.lines]:
            mm = re.match(r'^\s*\.(equ|set)\s+(\w+)\s*,\s*(\w+)', l)
            if mm:
                equs[mm.group(2)] = mm.group(3)

        res = convert_map(name, m, preamble, blocks, order, equs, syms, heal_ids, layout_ids, stats, report)
        new_map, new_scripts = res
        mus, why = music_for_map(name, outdoor, report['water_routes'])
        report['music'][name] = (m.get('music'), mus, why)
        new_map['music'] = mus
        dst = os.path.join(MAPS_DIR, name)
        with open(os.path.join(dst, 'map.json'), 'w') as f:
            json.dump(new_map, f, indent=2, ensure_ascii=False)
            f.write('\n')
        with open(os.path.join(dst, 'scripts.inc'), 'w') as f:
            f.write(new_scripts)

    # Pass 2: drop clone objects whose target object was removed
    kept_ids = {}
    for name in names:
        mm = json.load(open(os.path.join(MAPS_DIR, name, 'map.json')))
        kept_ids[mm['id']] = {o.get('local_id') for o in mm['object_events'] if o.get('type') != 'clone'}
    for name in names:
        path = os.path.join(MAPS_DIR, name, 'map.json')
        mm = json.load(open(path))
        objs = [o for o in mm['object_events']
                if o.get('type') != 'clone' or o.get('target_local_id') in kept_ids.get(o.get('target_map'), set())]
        if len(objs) != len(mm['object_events']):
            stats['obj_clone_removed'] += len(mm['object_events']) - len(objs)
            mm['object_events'] = objs
            with open(path, 'w') as f:
                json.dump(mm, f, indent=2, ensure_ascii=False)
                f.write('\n')

    print(json.dumps(stats, indent=1, sort_keys=True))
    if report_path:
        json.dump(report, open(report_path, 'w'), indent=1)


ROCKET_GFX = re.compile(r'ROCKET|GIOVANNI')
FIELD_OBJ_SCRIPTS = {'EventScript_CutTree', 'EventScript_RockSmash', 'EventScript_StrengthBoulder'}
LINK_ATTENDANTS = {'Common_EventScript_UnionRoomAttendant', 'Common_EventScript_WirelessClubAttendant',
                   'Common_EventScript_DirectCornerAttendant'}

# Objects removed by name even though their script is just talk: story-state actors.
FORCE_REMOVE_LOCALIDS = set()
# Objects whose FRLG hide flag is SET in the post-story state (gone after the story),
# even though their script is simple talk.  Other kept objects with hide flags are
# townsfolk that appear once the story is over (Saffron civilians, Lorelei at home, ...).
FORCE_REMOVE_FLAGS = {
    'FLAG_HIDE_CERULEAN_CAVE_GUARD',        # cave open post-game
    'FLAG_HIDE_ICEFALL_CAVE_LORELEI',
    'FLAG_HIDE_ONE_ISLAND_POKECENTER_BILL',
    'FLAG_HIDE_BULBASAUR_BALL', 'FLAG_HIDE_SQUIRTLE_BALL', 'FLAG_HIDE_CHARMANDER_BALL',
    'FLAG_HIDE_RIVAL_IN_LAB', 'FLAG_HIDE_POKEDEX', 'FLAG_HIDE_TOWN_MAP', 'FLAG_HIDE_OLD_AMBER',
    'FLAG_HIDE_NUGGET_BRIDGE_ROCKET', 'FLAG_HIDE_BILL_CLEFAIRY',
    'FLAG_HIDE_DOJO_HITMONLEE_BALL', 'FLAG_HIDE_DOJO_HITMONCHAN_BALL',
    'FLAG_HIDE_RUIN_VALLEY_SCIENTIST', 'FLAG_HIDE_THREE_ISLAND_BIKERS', 'FLAG_HIDE_CELADON_ROCKETS',
}


def convert_map(name, m, preamble, blocks, order, equs, syms, heal_ids, layout_ids, stats, report):
    mapname = name[:-len('_Frlg')]
    objs = m.get('object_events') or []
    decisions = []   # (obj, action, script_label or generated)
    gen_scripts = []  # generated script text
    emit_reached = set()
    emit_refs = set()
    transforms = {}

    def mk_ctx(kept):
        return Ctx(mapname, blocks, order, equs, kept, syms, heal_ids, layout_ids)

    # --- classify objects (fixpoint on LOCALID deps) ---
    provisional = {}
    for idx, o in enumerate(objs):
        if o.get('type') == 'clone':
            provisional[idx] = ('clone', None)
            continue
        script = o.get('script', '0x0')
        gfx = o.get('graphics_id', '')
        tt = o.get('trainer_type', 'TRAINER_TYPE_NONE')
        if script in FIELD_OBJ_SCRIPTS:
            provisional[idx] = ('field', script)
            continue
        if script in LINK_ATTENDANTS:
            provisional[idx] = ('remove', 'link attendant')
            continue
        if script in ('0x0', '', '0'):
            provisional[idx] = ('remove', 'no script (cutscene actor)')
            continue
        if tt not in ('TRAINER_TYPE_NONE', None, '0'):
            provisional[idx] = ('remove', 'trainer')
            continue
        if ROCKET_GFX.search(gfx):
            provisional[idx] = ('remove', 'team rocket')
            continue
        if o.get('local_id') in FORCE_REMOVE_LOCALIDS or o.get('flag') in FORCE_REMOVE_FLAGS:
            provisional[idx] = ('remove', 'forced')
            continue
        provisional[idx] = ('analyze', script)

    kept = None
    for _ in range(6):
        ctx = mk_ctx(kept)
        results = {}
        new_kept = set()
        for idx, o in enumerate(objs):
            kind, arg = provisional[idx]
            if kind == 'analyze':
                try:
                    t, r, refs, deps = analyze(ctx, arg, 'npc')
                    results[idx] = ('keep', (t, r, refs, deps))
                except Reject as e:
                    reason = str(e)
                    if reason == 'nurse':
                        results[idx] = ('nurse', None)
                    elif reason == 'mart':
                        results[idx] = ('mart', find_mart_lists(blocks, order, arg))
                    else:
                        results[idx] = ('remove', reason)
            else:
                results[idx] = (kind, arg)
            if results[idx][0] in ('keep', 'nurse', 'mart', 'field') and o.get('local_id'):
                new_kept.add(o['local_id'])
        if new_kept == kept:
            break
        kept = new_kept

    new_objs = []
    nurse_done = False
    for idx, o in enumerate(objs):
        kind, arg = results[idx]
        o = dict(o)
        if kind == 'clone':
            new_objs.append(o)  # validated in a later global pass
            stats['obj_clone'] += 1
            continue
        if kind == 'remove' or (kind == 'mart' and not arg):
            report['removed_objects'].append((name, o.get('local_id'), o.get('graphics_id'), o.get('script'), arg if kind == 'remove' else 'mart without list'))
            stats['obj_removed'] += 1
            stats['obj_removed_' + (arg.split()[0] if kind == 'remove' and arg else 'mart')] += 1
            continue
        if o.get('flag', '0') not in ('0', ''):
            report['kept_flagged'].append((name, o.get('local_id'), o.get('graphics_id'), o.get('script'), o['flag'], kind))
        o['flag'] = '0'
        if kind == 'field':
            o['trainer_type'] = 'TRAINER_TYPE_NONE'
            o['trainer_sight_or_berry_tree_id'] = '0'
            stats['obj_field_' + arg] += 1
        elif kind == 'nurse':
            lid = o.get('local_id')
            if not lid:
                lid = 'LOCALID_%s_NURSE_EM' % re.sub(r'(?<!^)(?=[A-Z])', '_', mapname).upper()
                o['local_id'] = lid
            label = '%s_EventScript_NurseEm' % mapname
            gen_scripts.append('%s::\n\tsetvar VAR_0x800B, %s\n\tcall Common_EventScript_PkmnCenterNurse\n\twaitmessage\n\twaitbuttonpress\n\trelease\n\tend\n' % (label, lid))
            o['script'] = label
            stats['obj_nurse'] += 1
        elif kind == 'mart':
            label = '%s_EventScript_ClerkEm%d' % (mapname, idx)
            lists = arg
            if len(lists) == 1:
                gen_scripts.append('%s::\n\tlock\n\tfaceplayer\n\tmessage gText_HowMayIServeYou\n\twaitmessage\n\tpokemart %s\n\tmsgbox gText_PleaseComeAgain, MSGBOX_DEFAULT\n\trelease\n\tend\n' % (label, lists[0]))
            else:
                # Several lists behind one clerk (e.g. by badge count): use the biggest (post-game) one
                best = max(lists, key=lambda l: mart_list_len(blocks, order, l))
                gen_scripts.append('%s::\n\tlock\n\tfaceplayer\n\tmessage gText_HowMayIServeYou\n\twaitmessage\n\tpokemart %s\n\tmsgbox gText_PleaseComeAgain, MSGBOX_DEFAULT\n\trelease\n\tend\n' % (label, best))
                lists = [best]
            for l in lists:
                emit_refs.add(l)
            o['script'] = label
            stats['obj_mart'] += 1
        else:
            t, r, refs, deps = arg
            transforms.update(t)
            emit_reached |= r
            emit_refs |= refs
            stats['obj_kept'] += 1
        new_objs.append(o)

    # --- bg events ---
    ctx = mk_ctx(kept)
    new_bgs = []
    for b in m.get('bg_events') or []:
        if b['type'] != 'sign':
            stats['bg_removed_' + b['type']] += 1
            continue
        s = b.get('script', '')
        if s in syms and not s.startswith(mapname):
            # an external common script (e.g. EventScript_PalletTown_PlayersHouse_2F_TurnOnPC)
            stats['bg_removed_external'] += 1
            continue
        try:
            t, r, refs, deps = analyze(ctx, s, 'npc')
        except Reject as e:
            report['removed_objects'].append((name, 'bg', b['x'], b['y'], s, str(e)))
            stats['bg_removed_sign'] += 1
            continue
        transforms.update(t)
        emit_reached |= r
        emit_refs |= refs
        new_bgs.append(b)
        stats['bg_kept'] += 1

    stats['coord_removed'] += len(m.get('coord_events') or [])

    # --- map scripts ---
    header_name = name + '_MapScripts'
    map_script_lines = []
    tables = []
    drops = []
    if header_name in order:
        hb = blocks[order[header_name]]
        for l in hb.lines:
            cmd, args = split_cmd(l)
            if cmd != 'map_script':
                continue
            typ, lbl = args[0], args[1]
            if typ in ('MAP_SCRIPT_ON_FRAME_TABLE',):
                drops.append(typ + ' ' + lbl)
                continue
            if typ == 'MAP_SCRIPT_ON_RESUME' and lbl == 'CableClub_OnResume':
                map_script_lines.append('\tmap_script %s, %s' % (typ, lbl))
                continue
            if typ == 'MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE':
                ent = filter_warp_table(ctx, blocks, order, lbl, transforms, emit_reached, emit_refs, drops)
                if ent:
                    tables.append((lbl, ent))
                    map_script_lines.append('\tmap_script %s, %s' % (typ, lbl))
                continue
            if lbl not in order:
                drops.append(typ + ' ' + lbl + ' (external)')
                continue
            try:
                t, r, refs, deps = analyze(ctx, lbl, 'map')
            except Reject as e:
                drops.append(typ + ' ' + lbl + ' (' + str(e) + ')')
                continue
            # check that something remains
            useful = False
            for bn in r:
                bi = order[bn]
                for i, line in enumerate(blocks[bi].lines):
                    if (bn, i) in t and t[(bn, i)] is None:
                        continue
                    c, a = split_cmd(t.get((bn, i), line))
                    if c and c not in ('end', 'return', 'goto', 'call', 'lockall', 'releaseall') and not c.startswith('.'):
                        useful = True
            for k, v in t.items():
                if v is None:
                    drops.append('%s: %s' % (typ, blocks[order[k[0]]].lines[k[1]].strip()))
            if useful:
                transforms.update(t)
                emit_reached |= r
                emit_refs |= refs
                map_script_lines.append('\tmap_script %s, %s' % (typ, lbl))
            else:
                drops.append(typ + ' ' + lbl + ' (nothing left)')
    if drops:
        report['map_script_drops'][name] = drops

    # --- emit ---
    data_blocks = collect_data_closure(ctx, emit_refs)
    out = []
    out.append('@ Converted for the Emerald build by dev_scripts/kanto/convert_kanto_maps.py.')
    out.append('@ Story events, trainers and items were removed; FRLG flags/vars are not referenced.')
    out.append('')
    # macros and equs used
    used_text = []
    emit_set = emit_reached | data_blocks
    for b in blocks:
        if b.name in emit_set:
            used_text.extend(b.lines)
    joined = '\n'.join(used_text) + '\n'.join(gen_scripts)
    pre = emit_preamble(preamble, blocks, joined)
    out.extend(pre)
    out.append('%s::' % header_name)
    out.extend(map_script_lines)
    out.append('\t.byte 0')
    out.append('')
    for lbl, ent in tables:
        out.append('%s::' % lbl)
        out.extend(ent)
        out.append('\t.2byte 0')
        out.append('')
    for b in blocks:
        if b.name == header_name or b.name not in emit_set:
            continue
        if any(b.name == t[0] for t in tables):
            continue
        out.append('%s%s' % (b.name, '::' if b.is_global else ':'))
        dead = False
        for i, line in enumerate(b.lines):
            st = line.strip()
            if st.startswith('#'):
                out.append(line)
                continue
            if b.name in emit_reached and b.name not in data_blocks:
                if dead:
                    continue
                key = (b.name, i)
                if key in transforms:
                    nl = transforms[key]
                    if nl is None:
                        continue
                    line = nl
                c, a = split_cmd(line)
                if c in ('end', 'goto', 'return', 'releaseall_end'):
                    out.append(line)
                    dead = True
                    continue
                if c in ('.macro', '.endm', '.equ', '.set'):
                    continue
            else:
                c, a = split_cmd(line)
                if c in ('.macro', '.endm', '.equ', '.set'):
                    continue
            out.append(line)
        out.append('')
    for g in gen_scripts:
        out.append(g)

    new_map = dict(m)
    new_map['object_events'] = new_objs
    new_map['bg_events'] = new_bgs
    new_map['coord_events'] = []
    return new_map, '\n'.join(out).rstrip('\n') + '\n'


def emit_preamble(preamble, blocks, used):
    """Emit .macro blocks and .equ/.set lines that the kept code uses."""
    out = []
    all_lines = preamble + [l for b in blocks for l in b.lines]
    i = 0
    while i < len(all_lines):
        l = all_lines[i]
        mm = re.match(r'^\s*\.macro\s+(\w+)', l)
        if mm:
            j = i
            body = []
            while j < len(all_lines):
                body.append(all_lines[j])
                if all_lines[j].strip().startswith('.endm'):
                    break
                j += 1
            if re.search(r'\b' + mm.group(1) + r'\b', used):
                out.extend(body)
                out.append('')
            i = j + 1
            continue
        mm = re.match(r'^\s*\.(equ|set)\s+(\w+)\s*,\s*(\w+)', l)
        if mm and re.search(r'\b' + mm.group(2) + r'\b', used):
            out.append(l.strip().replace('\t', ' '))
        i += 1
    if out:
        out.append('')
    return out


def find_mart_lists(blocks, order, entry):
    lists = []
    seen = set()
    work = [entry]
    while work:
        b = work.pop()
        if b in seen or b not in order:
            continue
        seen.add(b)
        bi = order[b]
        for l in blocks[bi].lines:
            c, a = split_cmd(l)
            if c == 'pokemart':
                lists.append(a[0])
            elif c in ('goto', 'call') and a:
                work.append(a[0])
            elif c and (c.startswith('goto_if') or c.startswith('call_if')) and len(a) >= 2:
                work.append(a[-1])
        if bi + 1 < len(blocks):
            body = [l for l in blocks[bi].lines if split_cmd(l)[0]]
            if body and split_cmd(body[-1])[0] not in ('end', 'goto', 'return'):
                work.append(blocks[bi + 1].name)
    return lists


def mart_list_len(blocks, order, lbl):
    if lbl not in order:
        return 0
    return sum(1 for l in blocks[order[lbl]].lines if 'ITEM_' in l)


def filter_warp_table(ctx, blocks, order, lbl, transforms, reached, refs, drops):
    if lbl not in order:
        return []
    out = []
    for l in blocks[order[lbl]].lines:
        c, a = split_cmd(l)
        if c != 'map_script_2':
            continue
        var, val, script = a
        if is_story_var(ctx, var):
            drops.append('WARP_INTO %s %s %s (story var)' % (var, val, script))
            continue
        try:
            t, r, rf, deps = analyze(ctx, script, 'npc')
        except Reject as e:
            drops.append('WARP_INTO %s (%s)' % (script, e))
            continue
        transforms.update(t)
        reached |= r
        refs |= rf
        out.append('\tmap_script_2 %s, %s, %s' % (var, val, script))
    return out


if __name__ == '__main__':
    main()
