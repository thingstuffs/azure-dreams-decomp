"""manifest9.py: cand9/ + cand9/MANIFEST.tsv (row, path, verified src sha, plan, flag[,rebaseline]) + sample9_rows.txt.
   opt rows = draft9 rows exact by check() (final9.jsonl); hdr = slus/code (lands only with the globals.h update;
   proven by listing9 against the complete post-apply include tree + the apply's partition / image gates)."""
import json, hashlib, shutil, random, collections
from pathlib import Path
LANE = Path(__file__).resolve().parent.parent; REPO = LANE.parent.parent.parent
plan = json.load(open(LANE / "results/plan9.json"))
fin = {json.loads(l)["id"]: json.loads(l) for l in open(LANE / "results/final9.jsonl")}
out = LANE / "cand9"
if out.exists(): shutil.rmtree(out)
rows = []
for rid, rec in sorted(fin.items()):
    if not rec["ok"]: continue
    d = LANE / "draft9" / (rid + ".c"); assert hashlib.sha256(d.read_bytes()).hexdigest() == rec["cand_sha"], rid
    assert hashlib.sha256((REPO / "src" / (rid + ".c")).read_bytes()).hexdigest() == rec["src_sha"], "src moved: " + rid
    p = out / (rid + ".c"); p.parent.mkdir(parents=True, exist_ok=True); shutil.copy(d, p)
    flag = "opt" + (",rebaseline" if rec.get("rebaseline_slus") else "")
    rows.append((rid, rid + ".c", rec["src_sha"], "+".join(plan[rid]["stages"]), flag))
rid = "slus/code"; d = LANE / "draft9/slus/code.c"; p = out / "slus/code.c"; shutil.copy(d, p)
rows.append((rid, "slus/code.c", hashlib.sha256((REPO / "src/slus/code.c").read_bytes()).hexdigest(), "t1", "hdr"))
with open(out / "MANIFEST.tsv", "w") as fh:
    fh.write("# row\tcandidate (under cand9/)\tsrc sha256 it was verified against\tplan\tflag\n")
    for r in rows: fh.write("\t".join(r) + "\n")
# 40-row cross-binary sample of opt rows: every task-1 SLUS row, then round-robin over binaries and stages
opt = [r for r in rows if r[4].startswith("opt")]
by = collections.defaultdict(list)
for r in opt: by[(r[0].split("/")[0], r[3].split("+")[0].split(":")[0] + (":" + r[3].split(":")[1] if r[3].startswith("p:") else ""))].append(r[0])
sample = [r[0] for r in opt if r[3].startswith("t1")]
random.seed(9); keys = sorted(by)
while len(sample) < 40 and any(by[k] for k in keys):
    for k in keys:
        if by[k] and len(sample) < 40:
            x = by[k].pop(random.randrange(len(by[k])))
            if x not in sample: sample.append(x)
(LANE / "sample9_rows.txt").write_text("\n".join(sample) + "\n")
print(len(rows), "manifest rows", collections.Counter(r[4] for r in rows), "sample", len(sample), collections.Counter(s.split("/")[0] for s in sample))
