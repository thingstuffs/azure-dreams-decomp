#!/usr/bin/env python3
"""Build a goto-readability lane pack (round 80; pilot r79_sonnet_g1, Sonnet 5.5: 35 -> 5 gotos on 6 rows).

    python3 tools/lanes/build_goto_lane.py <lane> --rows id,id,...       # exactly these rows
    python3 tools/lanes/build_goto_lane.py <lane> --pick 8 [--seed S] [--busy FILE]

--pick chooses pin-free rows with plain gotos (no computed goto, no NON_MATCHING arm), 1,000-9,000 bytes, that the
CPU generators t122_gotowhile / t123_returntail do not match, or tried at this exact text without applying, that no earlier goto
lane served at the same text (ledger/goto_lanes.jsonl) and that are not in --busy (whitespace-separated row ids,
e.g. a running pin lane's or type phase's list; the file may be any text - every token that is a row id counts).
Writes base/ (+ .base_sha), TOOLS.md, BRIEF.md (tools/lanes/goto_lane_brief.md), AGENT_PROMPT.txt, appends the serve
to ledger/goto_lanes.jsonl.  Launch: Agent tool, model sonnet, "read AGENT_PROMPT.txt and follow it".
"""
import argparse, glob, hashlib, json, random, re, sys, time
from pathlib import Path
ROOT = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(ROOT / "tools"), str(ROOT / "tools/xform")]
from common import rows
from pin_census import sites_of
import t122_gotowhile, t123_returntail

LEDGER = ROOT / "ledger/goto_lanes.jsonl"
PILOT = ROOT / "work/native_lane/r79_sonnet_g1"


def sha(t):
    return hashlib.sha256(t.encode()).hexdigest()


def served():
    out = set()
    if LEDGER.exists():
        for l in LEDGER.read_text().splitlines():
            d = json.loads(l); out |= {(r, s) for r, s in d["rows"].items()}
    return out


def tried_by_generators():
    """{(row, sha)} a t122/t123 sweep already journalled without applying: those rows go to the model lanes."""
    out = set()
    for t in ("t122_gotowhile", "t123_returntail"):
        p = ROOT / "ledger/sweeps" / (t + ".jsonl")
        if p.exists():
            for l in p.read_text().splitlines():
                d = json.loads(l)
                if d.get("outcome") != "applied": out.add((d["id"], d["in_sha"]))
    return out


def pickable(rid, text, tried=frozenset()):
    if "goto" not in text or "goto *" in text or "NON_MATCHING" in text: return False
    if not (1000 <= len(text) <= 9000) or sites_of(text): return False
    if not t122_gotowhile.gotos(text): return False
    if (rid, sha(text)) in tried: return True          # a generator tried this exact text and could not rewrite it
    return not t122_gotowhile.loops(text) and not t123_returntail.sites(text)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("lane"); ap.add_argument("--rows"); ap.add_argument("--pick", type=int)
    ap.add_argument("--seed", type=int, default=80); ap.add_argument("--busy", action="append", default=[])
    ap.add_argument("--budget", type=int, default=150)
    a = ap.parse_args()
    by = {r["id"]: r for r in rows()}
    lane = ROOT / "work/native_lane" / a.lane
    if lane.exists(): sys.exit("lane exists: %s" % lane)
    if a.rows:
        ids = a.rows.split(",")
    else:
        busy = set()
        for f in a.busy: busy |= set(Path(f).read_text().split())
        seen = served(); tried = tried_by_generators(); pool = []
        for f in sorted(glob.glob(str(ROOT / "src/*/*.c"))):
            rid = "/".join(f.split("/")[-2:])[:-2]
            if rid not in by or rid in busy: continue
            t = Path(f).read_text(errors="replace")
            if (rid, sha(t)) in seen or not pickable(rid, t, tried): continue
            pool.append(rid)
        random.seed(a.seed); ids = sorted(random.sample(pool, min(a.pick, len(pool))))
        print("pool %d rows; picked %d" % (len(pool), len(ids)))
    table = ["| row | gotos now | cell |", "|---|---:|---|"]; shas = {}
    for rid in ids:
        src = ROOT / "src" / (rid + ".c"); t = src.read_text(errors="replace")
        d = lane / "base" / rid.split("/")[0]; d.mkdir(parents=True, exist_ok=True)
        (d / src.name).write_text(t); shas[rid] = sha(t)
        (d / (src.name + ".base_sha")).write_text(shas[rid] + "\n")
        table.append("| %s | %d | %s |" % (rid, t122_gotowhile.gotos(t), by[rid]["cfg"]))
    for sub in ("out", "experiments", "tmp"): (lane / sub).mkdir(exist_ok=True)
    tpl = (ROOT / "tools/lanes/goto_lane_brief.md").read_text()
    (lane / "BRIEF.md").write_text(tpl.replace("<REPO>", str(ROOT)).replace("<LANE>", a.lane).replace("<N>", str(len(ids)))
                                   .replace("<ROW_TABLE>", "\n".join(table)))
    rl = ", ".join("`%s`" % r for r in ids)
    tools = (PILOT / "TOOLS.md").read_text().replace("r79_sonnet_g1", a.lane)
    tools = re.sub(r"^Rows served \(\d+\): .*$", "Rows served (%d): %s" % (len(ids), rl), tools, flags=re.M)
    (lane / "TOOLS.md").write_text(tools)
    prompt = (PILOT / "AGENT_PROMPT.txt").read_text().replace("r79_sonnet_g1", a.lane)
    prompt = re.sub(r"Budget \(orchestrator checkpoint, not a hard cap\): \d+", "Budget (orchestrator checkpoint, not a hard cap): %d" % a.budget, prompt)
    (lane / "AGENT_PROMPT.txt").write_text(prompt)
    with open(LEDGER, "a") as f:
        f.write(json.dumps({"lane": a.lane, "built": time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime()), "rows": shas}) + "\n")
    print("built %s: %s" % (a.lane, " ".join(ids)))


if __name__ == "__main__":
    main()
