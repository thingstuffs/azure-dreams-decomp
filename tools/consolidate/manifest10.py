"""manifest10.py: cand10/ + cand10/MANIFEST.tsv (row, path, verified src sha, stages, flag) + payload10/ (UPDATES.tsv +
   the post-apply include/shared/game_work.h) + sample10_rows.txt (40 opt rows across binaries and stages).
   opt = compiles against the old and the new headers; hdr = must land with the header update (its src spells a renamed
   GameWork member); post = needs the new headers, optional (full run only)."""
import json, hashlib, shutil, random, collections
from pathlib import Path
LANE = Path(__file__).resolve().parent.parent; REPO = LANE.parent.parent.parent
sha = lambda b: hashlib.sha256(b).hexdigest()
plan = json.load(open(LANE / "results/plan10.json"))
out = LANE / "cand10"
if out.exists(): shutil.rmtree(out)
rows = []
for rid, rec in sorted(plan.items()):
    if not rec.get("ok"): continue
    d = LANE / "draft10" / (rid + ".c"); assert sha(d.read_bytes()) == rec["cand_sha"], rid
    assert sha((REPO / "src" / (rid + ".c")).read_bytes()) == rec["src_sha"], "src moved: " + rid
    p = out / (rid + ".c"); p.parent.mkdir(parents=True, exist_ok=True); shutil.copy(d, p)
    rows.append((rid, rid + ".c", rec["src_sha"], rec["stages"], rec["flag"] + (",rebaseline" if rec.get("rebaseline") else "")))
with open(out / "MANIFEST.tsv", "w") as fh:
    fh.write("# row\tcandidate (under cand10/)\tsrc sha256 it was verified against\tstages (r respell10, p pre8333C, f fold10, pin)\tflag\n")
    for r in rows: fh.write("\t".join(r) + "\n")
pay = LANE / "payload10"
if pay.exists(): shutil.rmtree(pay)
(pay / "include/shared").mkdir(parents=True)
ups = []
for h in ("include/shared/game_work.h", "include/shared/dir_step.h"):
    shutil.copy(LANE / "inc/shared" / Path(h).name, pay / h)
    ups.append("%s\t%s\t%s\n" % (h, sha((REPO / h).read_bytes()), sha((pay / h).read_bytes())))
(pay / "UPDATES.tsv").write_text("".join(ups))
shutil.copy(LANE / "names_add.tsv", pay / "names_add10.tsv")
opt = [r for r in rows if r[4].startswith("opt")]
by = collections.defaultdict(list)
for r in opt: by[(r[0].split("/")[0], r[3])].append(r[0])
random.seed(10); keys = sorted(by); sample = []
if "dungeon/func_8195A480" in {r[0] for r in opt}: sample.append("dungeon/func_8195A480")      # the freed pin
while len(sample) < 40 and any(by[k] for k in keys):
    for k in sorted(keys, key=lambda k: (k[0] == "dungeon", k)):
        if by[k] and len(sample) < 40:
            x = by[k].pop(random.randrange(len(by[k])))
            if x not in sample: sample.append(x)
(LANE / "sample10_rows.txt").write_text("\n".join(sample) + "\n")
print(len(rows), "manifest rows", collections.Counter(r[4] for r in rows), collections.Counter(r[0].split("/")[0] for r in rows))
print("sample", len(sample), collections.Counter(s.split("/")[0] for s in sample))
