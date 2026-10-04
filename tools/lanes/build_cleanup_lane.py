#!/usr/bin/env python3
"""Build a byte-neutral cleanup lane (round 93; the r91 luna cleanup lanes r91_luna_{rename,proto,nm}* as a builder).

    python3 tools/lanes/build_cleanup_lane.py <lane> --task rename|proto|nm --pick 6 [--busy FILE ...] [--max-size N]
    python3 tools/lanes/build_cleanup_lane.py <lane> --task rename --rows id,id,...
    python3 tools/lanes/build_cleanup_lane.py --census                     # pool sizes per task, nothing built

Tasks (briefs in tools/lanes/cleanup_briefs/: core.md + <task>.md):
  rename  temp_/var_/phi_ locals, argN parameters, spXX names -> honest names ("never a false name")
  proto   M2C_UNK prototypes/params/locals -> real types
  nm      dead/stale #if(n)def NON_MATCHING arms
--pick takes the pin-free rows with the most task tokens (densest first), skipping rows a cleanup lane already served
at the same text (ledger/cleanup_lanes.jsonl, plus the r91_luna_* bases) and rows named in --busy files.
Launch on codex: tools/lanes/pool.py / launch_lane.sh (PROMPT.txt); land: LAND_ISOLATED=1 tools/lanes/land_gap.sh
(land_lanes counts fewer decompiler leftovers as a landing; kitlib.admissible stages them).
"""
import argparse, glob, hashlib, json, re, sys, time
from pathlib import Path
ROOT = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(ROOT / "tools"), str(ROOT / "tools/lanes/lanekit")]
from common import rows
from pin_census import sites_of

LEDGER = ROOT / "ledger/cleanup_lanes.jsonl"
BRIEFS = ROOT / "tools/lanes/cleanup_briefs"
PILOT = ROOT / "work/native_lane/r79_sonnet_g1"
TASKS = {
    "rename": ("decompiler local names", re.compile(r"\b(?:temp|var|phi)_[a-z][a-z0-9_]*\b|\barg[0-9]\b|\bsp[0-9A-F]{2,3}\b")),
    "proto": ("M2C_UNK prototypes", re.compile(r"\bM2C_UNK\b")),
    "nm": ("NON_MATCHING blocks", re.compile(r"\bNON_MATCHING\b")),
}


def sha(t):
    return hashlib.sha256(t.encode()).hexdigest()


def strip_comments(t):
    return re.sub(r"//[^\n]*", "", re.sub(r"/\*.*?\*/", "", t, flags=re.S))


def served():
    out = set()
    if LEDGER.exists():
        for l in LEDGER.read_text().splitlines():
            d = json.loads(l); out |= {(r, s) for r, s in d["rows"].items()}
    for f in glob.glob(str(ROOT / "work/native_lane/r91_luna_*/base/*/*.c.base_sha")):
        p = Path(f); out.add((p.parent.name + "/" + p.name[:-len(".c.base_sha")], p.read_text().split()[0]))
    return out


def pool(task, busy=frozenset(), max_size=12000):
    rx = TASKS[task][1]; seen = served(); ids = {r["id"] for r in rows()}; out = []
    for f in sorted(glob.glob(str(ROOT / "src/*/*.c"))):
        rid = "/".join(f.split("/")[-2:])[:-2]
        if rid not in ids or rid in busy or rid.startswith("ovmovie/"): continue
        t = Path(f).read_text(errors="replace")
        if len(t) > max_size or (rid, sha(t)) in seen or sites_of(t): continue
        n = len(rx.findall(strip_comments(t)))
        if n: out.append((n, rid))
    return sorted(out, key=lambda x: (-x[0], x[1]))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("lane", nargs="?"); ap.add_argument("--task", choices=sorted(TASKS)); ap.add_argument("--rows")
    ap.add_argument("--pick", type=int, default=6); ap.add_argument("--busy", action="append", default=[])
    ap.add_argument("--max-size", type=int, default=12000); ap.add_argument("--census", action="store_true")
    a = ap.parse_args()
    busy = set()
    for f in a.busy: busy |= set(Path(f).read_text().split())
    if a.census:
        for t in sorted(TASKS):
            p = pool(t, busy, a.max_size); print("%-7s %4d rows  %5d tokens" % (t, len(p), sum(n for n, _ in p)))
        return
    if not (a.lane and a.task): ap.error("give a lane and --task (or --census)")
    lane = ROOT / "work/native_lane" / a.lane
    if lane.exists(): sys.exit("lane exists: %s" % lane)
    if a.rows:
        ids = a.rows.split(",")
    else:
        p = pool(a.task, busy, a.max_size); ids = [r for _, r in p[:a.pick]]
        print("pool %d rows; picked %d" % (len(p), len(ids)))
    if not ids: sys.exit("nothing to serve")
    shas = {}
    for rid in ids:
        src = ROOT / "src" / (rid + ".c"); t = src.read_text(errors="replace")
        d = lane / "base" / rid.split("/")[0]; d.mkdir(parents=True, exist_ok=True)
        (d / src.name).write_text(t); shas[rid] = sha(t)
        (d / (src.name + ".base_sha")).write_text(shas[rid] + "\n")
    for sub in ("out", "experiments", "tmp"): (lane / sub).mkdir(exist_ok=True)
    brief = (BRIEFS / "core.md").read_text() + "\n" + (BRIEFS / (a.task + ".md")).read_text()
    brief = brief.replace("<REPO>", str(ROOT)).replace("<LANE>", a.lane).replace("<TASK>", TASKS[a.task][0])
    brief += "\n| row |\n|---|\n" + "".join("| %s |\n" % r for r in ids)
    (lane / "BRIEF.md").write_text(brief)
    rl = ", ".join("`%s`" % r for r in ids)
    tools = (PILOT / "TOOLS.md").read_text().replace("r79_sonnet_g1", a.lane)
    tools = re.sub(r"^Rows served \(\d+\): .*$", "Rows served (%d): %s" % (len(ids), rl), tools, flags=re.M)
    (lane / "TOOLS.md").write_text(tools)
    (lane / "PROMPT.txt").write_text(
        "cd %s && source %s/tools/lanes/lanekit/env.sh - work ONLY inside that directory. Read BRIEF.md and TOOLS.md "
        "there and follow them exactly. Do every row in the table: baseline, edit, score, stage, next row. Do not stop "
        "until every row has a result. Write REPORT.md as the brief says, then end with one line per row.\n" % (lane, ROOT))
    with open(LEDGER, "a") as f:
        f.write(json.dumps({"lane": a.lane, "task": a.task, "built": time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime()),
                            "rows": shas}) + "\n")
    print("built %s (%s): %s" % (a.lane, a.task, " ".join(ids)))


if __name__ == "__main__":
    main()
