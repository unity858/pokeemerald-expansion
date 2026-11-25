#!/usr/bin/env python3
"""Give every overworld item ball holding a TM or a Mega Stone the orange
R.O.W.E. item ball sprite (OBJ_EVENT_GFX_ITEM_BALL_TM), and every other item
ball the standard red one (OBJ_EVENT_GFX_ITEM_BALL).

An item ball is an object event whose script is Common_EventScript_FindItem;
its item is stored in trainer_sight_or_berry_tree_id. An item counts as a TM
or Mega Stone when its .pocket in src/data/items.h is POCKET_TM_HM or
POCKET_MEGA_STONES. Only map.json files that actually change are rewritten.

Run from the repository root:
    python3 dev_scripts/assign_tm_item_balls.py [--check]
--check only lists the balls that would change and exits 1 if any would.
"""

import glob
import json
import os
import re
import sys

ITEM_BALL_SCRIPT = "Common_EventScript_FindItem"
RED_BALL = "OBJ_EVENT_GFX_ITEM_BALL"
ORANGE_BALL = "OBJ_EVENT_GFX_ITEM_BALL_TM"
ORANGE_POCKETS = {"POCKET_TM_HM", "POCKET_MEGA_STONES"}


def load_item_pockets():
    pockets = {}
    current = None
    with open("src/data/items.h", encoding="utf-8") as f:
        for line in f:
            m = re.match(r"\s*\[(ITEM_\w+)\]\s*=", line)
            if m:
                current = m.group(1)
                continue
            m = re.match(r"\s*\.pocket\s*=\s*(POCKET_\w+)", line)
            if m and current is not None:
                pockets[current] = m.group(1)
                current = None
    # Resolve aliases such as "ITEM_X_DEFEND = ITEM_X_DEFENSE," (enum) or
    # "#define ITEM_A ITEM_B".
    with open("include/constants/items.h", encoding="utf-8") as f:
        for line in f:
            m = (re.match(r"\s*(ITEM_\w+)\s*=\s*(ITEM_\w+)\s*,", line)
                 or re.match(r"\s*#define\s+(ITEM_\w+)\s+(ITEM_\w+)\s*$", line))
            if m and m.group(2) in pockets and m.group(1) not in pockets:
                pockets[m.group(1)] = pockets[m.group(2)]
    return pockets


def main():
    if not os.path.exists("Makefile"):
        sys.exit("Please run this script from the repository root.")
    check_only = "--check" in sys.argv[1:]
    pockets = load_item_pockets()
    changed = []

    for path in sorted(glob.glob("data/maps/*/map.json")):
        with open(path, encoding="utf-8") as f:
            text = f.read()
        data = json.loads(text)
        new_text = text
        for obj in data.get("object_events") or []:
            if obj.get("script") != ITEM_BALL_SCRIPT:
                continue
            gfx = obj.get("graphics_id")
            if gfx not in (RED_BALL, ORANGE_BALL):
                continue
            item = obj.get("trainer_sight_or_berry_tree_id")
            if item not in pockets:
                print(f"warning: {path}: unknown item {item}", file=sys.stderr)
                continue
            want = ORANGE_BALL if pockets[item] in ORANGE_POCKETS else RED_BALL
            if gfx == want:
                continue
            changed.append((path, obj.get("x"), obj.get("y"), item, want))
            # Rewrite in place (not json.dump) so the file's formatting stays untouched.
            pattern = re.compile(
                r'("graphics_id":\s*)"' + gfx + r'"(,\s*"x":\s*' + str(obj["x"])
                + r',\s*"y":\s*' + str(obj["y"]) + r',)')
            new_text, n = pattern.subn(r'\1"' + want + r'"\2', new_text, count=1)
            if n != 1:
                sys.exit(f"error: could not rewrite {path} ({obj['x']}, {obj['y']})")
        if new_text != text and not check_only:
            with open(path, "w", encoding="utf-8") as f:
                f.write(new_text)

    for path, x, y, item, want in changed:
        mapname = os.path.basename(os.path.dirname(path))
        print(f"{mapname} ({x}, {y}) {item} -> {want}")
    if not changed:
        print("All item balls already use the right sprite.")
    if check_only and changed:
        sys.exit(1)


if __name__ == "__main__":
    main()
