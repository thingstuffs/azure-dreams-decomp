"""drive9e.py: task 3a - the two EntityRec POINTER globals (record_ptrs.h: D_800814A8, D_800E3D7C are `EntityRec *`).
   ((V *)P)->m with V a local view typedef  -> P->field (entity._emit: the EntityRec field at V.m's offset; a cast or a
   view at the use where width/sign disagree);  ((EntityRec *)P)->f -> P->f (redundant cast).  Only rows that take P
   from shared/record_ptrs.h (no local declaration of P).  Adds shared/entity.h when missing; drops a view typedef
   nothing else uses.  Verified with check() (listing + verify.py byte score); staged in cand9e/ when exact.
   -> results/t3e.jsonl"""
import json, re, sys, hashlib
from concurrent.futures import ProcessPoolExecutor
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
from cc import row_index, clean_path, REPO
from check import check
from consolidate import parse_views, code_spans
from entity import _emit, field_table, KEY_OF
LANE = Path(__file__).resolve().parent.parent
PTRS = ("D_800814A8", "D_800E3D7C")
def fold(text):
    tab = field_table(); notes = []; n = 0; used = set()
    if '#include "shared/record_ptrs.h"' not in text: return None, "no record_ptrs.h"
    for P in PTRS:
        if re.search(r"^\s*extern[^;]*\b%s\b" % P, text, re.M): return None, "local declaration of " + P
    for P in PTRS:
        rx = re.compile(r"\(\s*\(\s*((?:struct\s+)?\w+)\s*\*\s*\)\s*(\(\s*%s\s*\)|%s)\s*\)\s*->\s*(\w+)" % (P, P))
        while True:
            views = parse_views(text); spans = code_spans(text); done = False
            for m in rx.finditer(text):
                if not any(a <= m.start() < b for a, b in spans): continue
                V, mem = m.group(1).replace("struct ", "").strip(), m.group(3)
                if V == "EntityRec":
                    rep = "%s->%s" % (P, mem); notes.append("cast")
                else:
                    v = views.get(V) or views.get("struct " + V)
                    if v is None or mem not in v[0]: continue
                    o, sz, sg, cty, cnt, sub = v[0][mem]
                    if cnt or sub: continue
                    key = "pv" if cty.endswith("*") else KEY_OF.get(cty)
                    if key is None: continue
                    try: rep = _emit(text, m.start(), m.end(), P, o, key, tab, notes)
                    except ValueError: continue
                    used.add(V)
                text = text[:m.start()] + rep + text[m.end():]; n += 1; done = True; break
            if not done: break
    if not n: return None, "nothing to fold"
    for V in used:
        vv = parse_views(text).get(V)
        code = "".join(text[a:b] for a, b in code_spans(text))
        if vv and len(re.findall(r"\b%s\b" % V, code)) == 1:
            text = text[:vv[1]] + text[vv[2]:].lstrip("\n"); notes.append("dropped " + V)
        # a forward `struct V; typedef struct V V;` pair left alone (harmless)
    if '#include "shared/entity.h"' not in text:
        i = text.index('#include "shared/record_ptrs.h"\n') + len('#include "shared/record_ptrs.h"\n')
        text = text[:i] + '#include "shared/entity.h"\n' + text[i:]
    return text, "%d sites; %s" % (n, ", ".join(dict.fromkeys(notes)))
R = row_index()
def one(rid):
    r = R[rid]; src = clean_path(r); t = src.read_text(errors="replace")
    d = LANE / "draft9" / (rid + ".c")
    if d.is_file(): t = d.read_text()
    new, why = fold(t)
    if new is None: return {"id": rid, "ok": False, "refused": why}
    rec = check(r, new); rec.update(note=why, src_sha=hashlib.sha256(src.read_bytes()).hexdigest())
    rec["ok"] = bool((rec.get("score") or {}).get("exact"))
    if rec["ok"]:
        p = LANE / "cand9e" / (rid + ".c"); p.parent.mkdir(parents=True, exist_ok=True); p.write_text(new); rec.pop("diff", None)
    return rec
if __name__ == "__main__":
    ids = sorted(rid for rid, r in R.items() if re.search(r"\(\s*(?:struct\s+)?\w+\s*\*\s*\)\s*\(?\s*(%s)\b" % "|".join(PTRS), clean_path(r).read_text(errors="replace")))
    n = ok = 0; ref = {}
    with ProcessPoolExecutor(12) as ex, open(LANE / "results/t3e.jsonl", "w") as fh:
        for rec in ex.map(one, ids, chunksize=2):
            fh.write(json.dumps(rec) + "\n"); n += 1; ok += rec["ok"]
            if rec.get("refused"): ref[rec["refused"]] = ref.get(rec["refused"], 0) + 1
            elif not rec["ok"]: print("MISS", rec["id"], rec.get("note"), rec.get("listing"), rec.get("score"), (rec.get("diff") or [])[:3])
    print(n, "rows", ok, "ok", ref)
