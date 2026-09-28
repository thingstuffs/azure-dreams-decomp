"""variants8.py: readability folds on top of draft8/, each kept only if the cc1 listing stays identical (listing8.one).
   Writes the accepted text back to draft8/ and prints accept/reject per row."""
import re, sys, json, shutil
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
import listing8
LANE = listing8.LANE; D = LANE / "draft8"
def fold_1E70(t):   # s16 views on the GameView pointer at a short field -> the field
    names = {0x94: "unk_094", 0x96: "unk_096", 0x98: "unk_098", 0xA4: "unk_0A4", 0xA6: "unk_0A6", 0xA8: "unk_0A8"}
    return re.sub(r"\*\(s16 \*\)\(\(char \*\)state \+ 0x([0-9A-F]+)\)", lambda m: "state->%s" % names[int(m.group(1), 16)] if int(m.group(1), 16) in names else m.group(0), t)
def fold_B2614(t):
    t = t.replace("((S_800B7D74_4 *)game_state)->unk_B0", "game_state->viewAngle")
    if len(re.findall(r"\bS_800B7D74_4\b", t)) == 2:
        t = re.sub(r"typedef struct S_800B7D74_4 \{\n    u8 pad_00\[0xB0\];\n    s16 unk_B0;\n\} S_800B7D74_4;[^\n]*\n\n?", "", t)
    return t
def fold_angle(t):
    return t.replace("*(s16 *)((u8 *)((s16 *)(&gameWork.view.unk_090)) + 0x20)", "gameWork.view.viewAngle")
def fold_root(t):
    t = t.replace("/* Same address as D_80083160 (0x80083178 - 0x18), spelled off D_80083178.", "/* gameWork's own base (0x80083160), formerly spelled as D_80083178 - 0x18.")
    return t.replace("(((u8 *)(&gameWork.view)) - 0x18)", "((u8 *)&gameWork)")
V = {"dungeon/func_800C1E70": fold_1E70, "dungeon/func_800B2614": fold_B2614, "dungeon/func_809CA53C": fold_angle,
     "dungeon/func_80E0EF2C": fold_angle, "dungeon/func_819112CC": fold_root, "dungeon/func_81910EC0": fold_root}
for rid, f in V.items():
    p = D / (rid + ".c"); t0 = p.read_text(); t1 = f(t0)
    if t1 == t0: print(rid, "no change"); continue
    shutil.copy(p, str(p) + ".prev"); p.write_text(t1)
    rec = listing8.one(rid)
    if rec.get("identical"): print(rid, "ACCEPT"); Path(str(p) + ".prev").unlink()
    else: shutil.move(str(p) + ".prev", p); print(rid, "reject", json.dumps(rec.get("diff"))[:300])
