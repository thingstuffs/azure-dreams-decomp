"""manifest8.py: cand8/ + cand8/MANIFEST.tsv from draft8/ (+ cand8x/ task-3 texts when present, verified).
   columns: row  path  verified_src_sha  plan  flag   (flag hdr = must land with the game_work.h/game.h/globals.h
   update; opt = independent; plan: respell | hand | variant | preamble | task3 joined by +; `partition` = not a row)."""
import hashlib, json, shutil, subprocess, sys
from pathlib import Path
LANE = Path(__file__).resolve().parent.parent; REPO = LANE.parent.parent.parent
sys.path.insert(0, str(LANE / "tools"))
from respell8 import respell
sys.path.insert(0, str(REPO / "tools")); import os; os.chdir(REPO)
from common import rows
R = {r["id"] for r in rows()}
HAND = {"dungeon/func_800C6654", "dungeon/func_800C1E70", "dungeon/func_800B2614", "dungeon/func_8191696C", "dungeon/func_81984E94",
        "slus/w_80044724", "slus/w_8004D5D0", "dungeon/func_800AFA68", "slus/code2"}
VAR = {"dungeon/func_800C1E70", "dungeon/func_800B2614", "dungeon/func_809CA53C", "dungeon/func_80E0EF2C", "dungeon/func_819112CC", "dungeon/func_81910EC0"}
PRE = {l.strip() for l in open(LANE / "results/preamble8_rows.txt") if l.strip()}
T3 = {}
if (LANE / "results/t3_ok.tsv").exists():
    for l in open(LANE / "results/t3_ok.tsv"):
        rid, tag = l.split()[:2]; T3[rid] = tag
out = LANE / "cand8"; shutil.rmtree(out, ignore_errors=True)
lines = []
ids = sorted({str(p.relative_to(LANE / "draft8"))[:-2] for p in (LANE / "draft8").rglob("*.c")} | set(T3))
for rid in ids:
    src = REPO / "src" / (rid + ".c"); s = src.read_text(errors="replace")
    d = (LANE / "cand8x" / (rid + ".c")) if rid in T3 else (LANE / "draft8" / (rid + ".c"))
    t = d.read_text()
    plan = []
    if respell(s)[1]: plan.append("respell")
    if rid in HAND: plan.append("hand")
    if rid in VAR: plan.append("variant")
    if rid in PRE: plan.append("preamble")
    if rid in T3: plan.append(T3[rid])
    hdr = bool({"respell", "hand"} & set(plan))
    flag = ("hdr" if hdr else "opt") + ("" if rid in R else ",partition")
    p = out / (rid + ".c"); p.parent.mkdir(parents=True, exist_ok=True); p.write_text(t)
    lines.append("%s\t%s\t%s\t%s\t%s" % (rid, rid + ".c", hashlib.sha256(src.read_bytes()).hexdigest(), "+".join(plan), flag))
(out / "MANIFEST.tsv").write_text("# row\tpath\tverified_src_sha\tplan\tflag\n" + "\n".join(lines) + "\n")
import collections
print(len(lines), collections.Counter(l.split("\t")[4] for l in lines), collections.Counter(l.split("\t")[3] for l in lines))
