"""build9.py: compose every phase-9 edit per row on the CURRENT src text -> draft9/<row>.c + results/plan9.json.
   Stages (in order, each only where it applies): t1 (volumeScale, task 1), t2 (D_8006DE24 base-forming class, task 2),
   pre (dead `extern short D_80084808[8];` copies), e (EntityRec pointer views, drive9e.fold), p:<obj> (local
   pointer folds, rewrite_pointers mode recorded by drive9g + respell8), tidy (unused local views).
   Rows of each stage: t1/t2/pre from the lists below, e/p from their result files (ok rows)."""
import json, re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
from cc import REPO
import consolidate as C
from respell8 import respell
from drive9e import fold as efold
from tidy9 import tidy
from t1 import edit as t1edit
LANE = Path(__file__).resolve().parent.parent
T1_ROWS = ["slus/w_80053DF0", "slus/w_80053E20", "slus/w_80053E90", "slus/w_80054D64", "slus/w_800552C8", "slus/w_8005560C", "slus/w_800559B4"]
T1_COMMENTS = {
 "slus/w_80053DF0": [("/* Sets volumeScale[1] to the new value and calls func_800552C8. */", "/* Sets volume scale [1] and re-applies it through func_800552C8. */")],
 "slus/w_80053E20": [("/* Sets the indexed player stat and invokes its update routine when needed. */", "/* Sets volume scale [0] / [1] / [2] for selector 2 / 1 / 4; [1] and [2] are re-applied at once. */")],
 "slus/w_80053E90": [("/* Returns the player stat selected by index 1, 2, or 4, or zero for other indices. */", "/* Returns volume scale [0] / [1] / [2] for selector 2 / 1 / 4, zero for any other selector. */"),
                     ("stat_index", "selector"), ("stat_value", "scale")],
 "slus/w_80054D64": [("/* Apply the scaled pitch bend to both channels when status flag 0x400 is set. */", "/* When status flag 0x400 is set: D_80084858's level, scaled by volume scale [2], goes to func_8005A56C (mode 0). */"),
                     ("pitch_task", "task"), ("scaled_pitch", "scaled"), ("s16 pitch;", "s16 level;"), ("pitch = ", "level = "), ("pitch * ", "level * "), ("pitch, pitch", "level, level")],
 "slus/w_8005560C": [("/* Scales the gauge value and updates its primary and optional secondary segments. */", "/* Scales D_800847EE's level by volume scale [0] and starts the voices with a primary and an optional secondary gain. */")],
}
T2 = {
 "dungeon/func_8009E0C0": [("    int entry_offset = entry_index * 0x14;\n    return D_8006DE24[entry_offset + 0x13];", "    DefEntry *entry = &D_8006DE24[entry_index];\n    return entry->unk_13;")],
 "dungeon/func_800BB400": [("D_8006DE24[item * 20 + 16]", "D_8006DE24[item].unk_10")],
 "dungeon/func_80A1F0C4": [("D_8006DE24[anim_id * 0x14 + 0x12]", "D_8006DE24[anim_id].kind")],
 "dungeon/func_80B9913C": [("D_8006DE24[item_id * 20 + 0x12]", "D_8006DE24[item_id].kind")],
 "dungeon/func_80C412B4": [("D_8006DE24[(*move_id * 20) + 0x12]", "D_8006DE24[*move_id].kind")],
 "dungeon/func_80CEAF2C": [("D_8006DE24[*move * 20 + 0x12]", "D_8006DE24[*move].kind")],
 "dungeon/func_80E0F7C0": [("D_8006DE24[*effect_id * 0x14 + 0x12]", "D_8006DE24[*effect_id].kind")],
 "dungeon/func_80EE1FB0": [("D_8006DE24[*action_data * 0x14 + 0x12]", "D_8006DE24[*action_data].kind")],
 "dungeon/func_80F5F040": [("D_8006DE24[(*move_slot * 20) + 0x12]", "D_8006DE24[*move_slot].kind")],
 "dungeon/func_810860B4": [("D_8006DE24[item_id * 20 + 0x12]", "D_8006DE24[item_id].kind")],
 "dungeon/func_81252D6C": [("D_8006DE24[*action_entry * 20 + 0x12]", "D_8006DE24[*action_entry].kind")],
 "dungeon/func_800A3D40": [("struct S_8006DE24_Entry;\ntypedef struct S_8006DE24_Entry S_8006DE24_Entry;\nstruct S_8006DE24_Entry {\n    s32 unk0;\n    u8 pad4[4];\n    s32 unk8;\n    u8 padC[8];\n};\nextern S_8006DE24_Entry D_8006DE24[];\n", ""),
                           ("D_8006DE24[name_index].unk8", "D_8006DE24[name_index].unk_08"), ("S_8006DE24_Entry *name_table;", "DefEntry *name_table;"),
                           ("name_table[effect_index].unk0", "name_table[effect_index].unk_00")],
}
PRE = ["town/func_8009CA88", "dungeon/func_800AB7F0", "dungeon/func_800D5F00", "dungeon/func_81946800", "dungeon/func_818B0E10", "dungeon/func_80B97C10"]
PTR = {"gameWork": "t3g.jsonl", "dungeonStatus": "t3_dungeonStatus.jsonl", "D_80083780": "t3_D_80083780.jsonl", "D_80082E80": "t3_D_80082E80.jsonl"}
def add_inc(t, h, after='#include "common.h"\n'):
    line = '#include "%s"\n' % h
    if line in t: return t
    i = t.index(after) + len(after); return t[:i] + line + t[i:]
def ok_rows(fname):
    out = {}
    for l in open(LANE / "results" / fname):
        r = json.loads(l)
        if r.get("ok"): out[r["id"]] = r.get("mode")
    return out
def plan():
    P = {}
    for rid in T1_ROWS: P.setdefault(rid, []).append("t1")
    for rid in T2: P.setdefault(rid, []).append("t2")
    for rid in PRE: P.setdefault(rid, []).append("pre")
    for rid in ok_rows("t3e.jsonl"): P.setdefault(rid, []).append("e")
    for o, f in PTR.items():
        for rid, mode in ok_rows(f).items(): P.setdefault(rid, []).append("p:%s:%s" % (o, mode))
    return P
def compose(rid, stages, t):
    for s in stages:
        if s == "t1":
            t = t1edit(t)
            for o, n in T1_COMMENTS.get(rid, []): assert o in t, (rid, o); t = t.replace(o, n)
        elif s == "t2":
            for o, n in T2[rid]: assert o in t, (rid, o); t = t.replace(o, n)
            t = re.sub(r"^extern (u8|s8|unsigned char|char) D_8006DE24\[\w*\];\n", "", t, flags=re.M)
            t = add_inc(t, "shared/def_table.h")
        elif s == "pre":
            assert "extern short D_80084808[8];\n" in t, rid; t = t.replace("extern short D_80084808[8];\n", "")
        elif s == "e":
            n, why = efold(t)
            if n is None: return None, "e: " + why
            t = n
        elif s.startswith("p:"):
            _, o, mode = s.split(":")
            n, why = C.rewrite_pointers(t, C.load(LANE / "objects" / (o + ".json")), mode)
            if n is None: return None, s + ": " + why
            t, _ = respell(n)
    t2, _ = tidy(t)
    return t2, None
if __name__ == "__main__":
    P = plan(); out = {}
    (LANE / "draft9").mkdir(exist_ok=True)
    for rid, st in sorted(P.items()):
        src = (REPO / "src" / (rid + ".c")).read_text(errors="replace")
        t, why = compose(rid, st, src)
        if t is None or t == src: out[rid] = {"stages": st, "refused": why or "unchanged"}; continue
        p = LANE / "draft9" / (rid + ".c"); p.parent.mkdir(parents=True, exist_ok=True); p.write_text(t)
        out[rid] = {"stages": st}
    json.dump(out, open(LANE / "results/plan9.json", "w"), indent=0)
    import collections
    print(len(out), "rows", collections.Counter(len(v["stages"]) for v in out.values()), [ (k, v) for k, v in out.items() if "refused" in v][:10])
