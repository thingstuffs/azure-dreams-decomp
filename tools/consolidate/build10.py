"""build10.py: compose the phase-10 edits per row on the CURRENT src text and verify each composition.
   stages: r = respell10 (GameWork flat 0x1DC..0x1FC -> map.* / randSeed; REQUIRED with the game_work.h update),
           p = pre8333C (a TU's own `extern V D_8008333C;` -> gameWork.map), f = fold10 (local views -> shared fields).
   Per row: try r+p+f, then r+p, then r (a row that needs r must land with the header even if its fold misses).
   check() = listing identity (lane inc/ = post-apply shared headers) + verify.py byte score.
   flag: hdr = the src spells a renamed GameWork member, so the row MUST land with the header update; post = the text
   needs the new headers (gameWork.map / buttons / dirSpriteFlag) but the old src still compiles after the update (lands
   in the full run, skipped when busy / stale); opt = compiles against either header.
   -> draft10/<row>.c, results/plan10.json"""
import json, re, sys, hashlib, collections, glob
from concurrent.futures import ProcessPoolExecutor
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
from cc import row_index, REPO
from fold10 import fold
from respell10 import respell, pre8333C, t3flag
LANE = Path(__file__).resolve().parent.parent; R = row_index()
SKIP = {"slus/code", "slus/code2", "slus/w_8003E34C", "dungeon/func_800AFA68", "slus/w_8004D5D0"}
PINFREE = {"dungeon/func_8195A480": ["ASM_MEM_BARRIER"]}   # pins2 (results/pins10.jsonl): freed by the typed objectFlagBlock access
NEEDS = re.compile(r"\bgameWork\s*\.\s*(map|randSeed|buttons)\b|\bMapGrid\b|->\s*(map|randSeed|buttons)\b|\bdirSpriteFlag\b")
def variants(t):
    a, nr = respell(t); b, npre = pre8333C(a)
    c, notes, ref = fold(b)
    base = []
    if c is not None and c != b: base.append(("r" * bool(nr) + "p" * bool(npre) + "f", c, notes, ref))
    # (no p-without-f variant: `((V *)&gameWork.map)->m` with the local view kept is less readable than the TU's own
    #  D_8008333C declaration - a p row lands only when fold10 maps its view onto MapGrid fields)
    if nr: base.append(("r", a, [], ref))
    out = []
    for st, x, nt, rf in base + [("", t, [], ref)]:
        y, ns = t3flag(x)
        if ns: out.append((st + "s", y, nt, rf))
    out += base
    return out, bool(nr)
def one(rid):
    src = REPO / "src" / (rid + ".c"); t = src.read_text(errors="replace"); sha = hashlib.sha256(src.read_bytes()).hexdigest()
    vs, need_r = variants(t)
    rec = {"id": rid, "src_sha": sha, "need_r": need_r, "tries": []}
    from check import check
    for stages, new, notes, ref in vs:
        c = check(R[rid], new)
        ok = bool((c.get("score") or {}).get("exact")); rebase = (not ok) and c.get("abs_listing") == "identical"
        rec["tries"].append({"stages": stages, "listing": c.get("listing"), "score": c.get("score"), "err": (c.get("err") or "")[-160:], "diff": (c.get("diff") or [])[:4]})
        if (ok or rebase) and rid in PINFREE:
            import kitlib
            e = kitlib.erase(new, [s for s in kitlib.sites(new) if s[1] in PINFREE[rid]])
            ce = check(R[rid], e)
            if (ce.get("score") or {}).get("exact"): new = e; stages += "+pin"; rec["pin_freed"] = PINFREE[rid]
        if ok or rebase:
            p = LANE / "draft10" / (rid + ".c"); p.parent.mkdir(parents=True, exist_ok=True); p.write_text(new)
            rec.update(ok=True, stages=stages, notes=notes, refusals=ref, rebaseline=rebase, cand_sha=hashlib.sha256(new.encode()).hexdigest(),
                       flag=("hdr" if need_r else "post") if NEEDS.search(new) else "opt")
            return rec
    rec["ok"] = False; rec["refusals"] = vs[0][3] if vs else []
    return rec
if __name__ == "__main__":
    ids = set(json.loads(l)["id"] for l in open(LANE / "census/views10.jsonl"))
    for p in glob.glob(str(REPO / "src/*/*.c")):
        t = open(p, errors="replace").read()
        if re.search(r"gameWork|D_8008333C|GameWork", t) and (respell(t)[1] or pre8333C(t)[1]) or t3flag(t)[1]: ids.add(p.split("/src/")[1][:-2])
    ids = sorted(i for i in ids if i in R and i not in SKIP)
    import shutil
    if (LANE / "draft10").exists(): shutil.rmtree(LANE / "draft10")
    C = collections.Counter(); plan = {}
    with ProcessPoolExecutor(14) as ex:
        for rec in ex.map(one, ids, chunksize=2):
            plan[rec["id"]] = rec
            C[("ok:" + rec["stages"] + ":" + rec["flag"]) if rec.get("ok") else ("FAIL-needs-r" if rec["need_r"] else ("miss" if rec["tries"] else "nothing"))] += 1
    json.dump(plan, open(LANE / "results/plan10.json", "w"), indent=0)
    print(len(ids), dict(sorted(C.items())))
    for rid, rec in sorted(plan.items()):
        if rec["need_r"] and not rec.get("ok"): print("NEEDS R, NOT EXACT:", rid, rec["tries"])
