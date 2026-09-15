#!/usr/bin/env python3
"""Land an honest-C lane pack at its TRUE base: promote the row's rowbase region with the honest
candidate as the byte-exact recompile proof, register the true-space name, carry the per-row maspsx
dial across to that name.  Read-only until --apply (round 25 recipe, docs/HANDOVER.md part 3/4).

    python3 tools/lanes/promote_honest.py [--apply] [--decision-b] [--only id,id] [--out-glob 'out/*/*.c'] LANE...

Per lane output (work/native_lane/<lane>/out/<container>/<name>.c) the plan is:
  promote      the region is `solved`: `rowbase.py promote` compiles the candidate at the true base NOW
               (the discriminating proof) and turns the record `proven`;
  register     `true_name` in ledger/splits/<family>.jsonl is not the expected `func_<foff+delta>`
               (the WINDOW gate links a row at the true base only when its true name is registered);
  as_flags     config/overlays/<family>.as_flags.jsonl has a dial keyed on the synthetic name with no
               `true_name` field (the landing gate asks the resolver for the true name only, so the
               dial would be dropped silently -- round 25 part 4 rolled two town rows back for this).

Two deliberate readings of the recipe, both to keep the tool honest on already-landed packs:
  * the plan is a property of the ROW, so it is computed for every lane output; the land_lanes.sh
    filter (fresh .base_sha, pins strictly lower, no scaffolding kind grown) only blocks WORK -- a row
    with nothing left to do prints `OK` even when its base went stale after it landed;
  * the shared-region (decision B) screen gates on a planned `promote`, because promotion is the
    rename event for every row in the region; a per-row `register` touches only that row's split
    record.  A region mate that is not re-landing in this run is a mate even if its own lane output
    is in the set but cannot land (it would be linked at the true base with text never shown exact).

--apply writes: registrations first, then tools/registry.py + tools/row_db.py check (abort on
non-zero), then rowbase.py promote per row, then the as_flags dials.  It does NOT land anything:
afterwards run `bash tools/lanes/land_lanes.sh <tag> LANE...` (candidates, cascade, tidy, T2) and the
gate it ends with.
"""
import argparse
import bisect
import collections
import glob
import hashlib
import json
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "build_ovl/tools"))
import rowbase  # noqa: E402  the build_ovl copy; tools/gate's copy resolves ROOT wrongly
assert Path(rowbase.__file__).resolve().parent == ROOT / "build_ovl/tools", rowbase.__file__
from common import rows, clean_path  # noqa: E402
from pin_census import sites_of  # noqa: E402

FAMILIES = ("dungeon", "town", "main")
BAD = re.compile(r"ASM_[A-Z0-9_]+(?=\()|while\s*\(\s*0\s*\)|__asm__|\bvolatile\b")  # land_lanes.sh
OK_FILTER = ("ok", "landed")


def kinds(text):
    body = re.sub(r"/\*.*?\*/", "", text, flags=re.S)
    return collections.Counter(m.group(0).replace(" ", "") for m in BAD.finditer(body))


def filter_status(cand_file, cand, cur):
    """land_lanes.sh's landing filter, plus `landed` for a candidate already in the tree."""
    if cand == cur:
        return "landed"
    sha = Path(str(cand_file) + ".base_sha")
    if hashlib.sha256(cur.encode()).hexdigest() != (sha.read_text().strip() if sha.exists() else ""):
        return "stale base"
    kc, ku = kinds(cand), kinds(cur)
    grew = [k for k in kc if kc[k] > ku[k]]
    if grew:
        return "scaffolding grew %s" % ",".join(sorted(grew))
    so, sn = len(sites_of(cur)), len(sites_of(cand))
    if sn >= so:
        return "pins not lower %d -> %d" % (so, sn)
    return "ok"


_REGIONS = None


def region_of(fam, foff):
    global _REGIONS
    if _REGIONS is None:
        _REGIONS = {f: sorted(rowbase._records(f), key=lambda g: g["start"]) for f in FAMILIES}
    recs = _REGIONS.get(fam) or []
    i = bisect.bisect_right([g["start"] for g in recs], foff) - 1
    if i >= 0 and recs[i]["start"] <= foff < recs[i]["end"]:
        return recs[i]
    return None


_MEMBERS = None


def members(all_rows, fam, region):
    """One pass over the registry: (family, region) -> the landed rows inside it."""
    global _MEMBERS
    if _MEMBERS is None:
        _MEMBERS = collections.defaultdict(list)
        for r in all_rows:
            g = None if r.get("foff") is None else region_of(r["container"], int(r["foff"]))
            if g is not None:
                _MEMBERS[(r["container"], g["rec"]["region"])].append(r)
    return _MEMBERS[(fam, region)]


def as_flags_missing(fam, func):
    """A dial keyed on the synthetic name that carries no true_name (records whose true_name equals
    the func are legitimate: that row's true name IS its synthetic name)."""
    p = ROOT / f"config/overlays/{fam}.as_flags.jsonl"
    for line in (p.read_text().splitlines() if p.exists() else []):
        if line.strip() and not line.startswith("#"):
            rec = json.loads(line)
            if rec.get("func") == func and "true_name" not in rec:
                return True
    return False


def row_info(r, lane=None, cand=None, filt=None, dials=True):
    """The plan's view of a row.  `dials=False` for a region mate: mates are not dialled here and a
    big region has hundreds of them, one as_flags read each."""
    foff = None if r.get("foff") is None else int(r["foff"])
    g = None if foff is None else region_of(r["container"], foff)
    return dict(id=r["id"], lane=lane, cand=cand, family=r["container"], func=r["func"], foff=foff,
                region=g["rec"]["region"] if g else None,
                conf=g["rec"].get("base_confidence") if g else None,
                expected=("func_%08X" % (foff + g["delta"])) if g else None,
                true_name=r.get("true_name"), cfg=r.get("cfg"), filter=filt, row=r,
                as_flags_missing=dials and as_flags_missing(r["container"], r["func"]))


def plan_row(info, mates=(), decision_b=False, verify_fn=None):
    """Pure plan for one row.  `mates` are the landed rows of the same region that are NOT re-landing
    in this run.  Returns (status, steps, note); steps are ("promote"|"register"|"as_flags", ...)."""
    if info.get("region") is None:
        return "SKIP", [], "no rowbase region"
    steps = []
    if info.get("conf") == "solved":
        steps.append(("promote", info["family"], info["func"], info["cand"], info["cfg"], info["region"]))
    tn, exp = info.get("true_name"), info["expected"]
    if tn != exp:
        if tn not in (None, "", info["func"]):
            return "REFUSE", [], "true_name is %s, expected %s" % (tn, exp)
        steps.append(("register", info["family"], info["func"], exp))
    if info.get("as_flags_missing"):
        steps.append(("as_flags", info["family"], info["func"], exp))
    if not steps:
        blocked = "" if info.get("filter") in OK_FILTER else "; %s" % info.get("filter")
        return "OK", [], "nothing to do (%s, true name %s%s)" % (info.get("conf"), tn, blocked)
    if info.get("filter") not in OK_FILTER:
        return "SKIP", [], str(info.get("filter"))
    if any(s[0] == "promote" for s in steps) and mates:
        if not decision_b:
            return "SKIP", [], "shared region %s holds %s" % (
                info["region"], ", ".join(m["id"] for m in mates))
        for m in mates:
            if m["true_name"] not in (None, "", m["func"], m["expected"]):
                return "SKIP", [], "decision B: mate %s true_name is %s" % (m["id"], m["true_name"])
            res = (verify_fn(m) or {}) if verify_fn else {}
            if not res.get("exact"):
                return "SKIP", [], "decision B: mate %s not exact at the true base (%s)" % (
                    m["id"], res.get("result") or res.get("class") or res.get("aligned"))
        for m in mates:
            if m["true_name"] != m["expected"]:
                steps.append(("register", m["family"], m["func"], m["expected"]))
        return "DO", steps, "decision B: %d mate(s) exact" % len(mates)
    return "DO", steps, ""


def unresolved(plans):
    """Rows this plan refuses whose candidate still passes the landing filter: land_lanes.sh has no
    exclusion list, so it would land them unregistered in a solved/proven region and the window gate
    would link them at the synthetic base (round 25 part 2: 30 failed windows, tree reverted).  A
    region-less row is not one of these -- its lane verified it at the synthetic base."""
    return [i["id"] for i, (st, _s, _n) in plans
            if st in ("SKIP", "REFUSE") and i["filter"] == "ok" and i["region"]]


def describe(steps, note):
    """The plan column: `promote <region>, register <name>, as_flags <name> [note]`."""
    if not steps:
        return note
    what = ", ".join("%s %s" % (s[0], s[5] if s[0] == "promote" else s[3]) for s in steps)
    return what + ((" [%s]" % note) if note else "")


def set_true_name(fam, func, name):
    """Register a true-space name in ledger/splits/<fam>.jsonl, preserving the record's other
    fields and every unrelated line; refuses a differing true_name already in place."""
    p = ROOT / f"ledger/splits/{fam}.jsonl"
    lines = p.read_text().splitlines(keepends=True)
    done = False
    for i, line in enumerate(lines):
        if not line.strip() or line.startswith("#"):
            continue
        j = json.loads(line)
        if j.get("func_vram") == func:
            if j.get("true_name") == name:
                return "already"
            if j.get("true_name") not in (None, func):
                raise SystemExit(f"{func}: true_name is {j.get('true_name')!r}")
            new = {"func_vram": func, "true_name": name}
            new.update({k: v for k, v in j.items() if k not in ("func_vram", "true_name")})
            lines[i] = json.dumps(new, separators=(",", ":")) + "\n"
            done = True
    if not done:
        raise SystemExit(f"{func}: not in {p}")
    p.write_text("".join(lines))
    return "set"


def set_as_flags_true_name(fam, func, name):
    """Add the true_name alias to the per-row maspsx dial, rewriting only its line."""
    p = ROOT / f"config/overlays/{fam}.as_flags.jsonl"
    lines = p.read_text().splitlines(keepends=True)
    hit = False
    for i, line in enumerate(lines):
        if not line.strip() or line.startswith("#"):
            continue
        rec = json.loads(line)
        if rec.get("func") == func and "true_name" not in rec:
            new = {}
            for k, v in rec.items():
                new[k] = v
                if k == "func":
                    new["true_name"] = name
            lines[i] = json.dumps(new, separators=(",", ":")) + "\n"
            hit = True
    if not hit:
        return "absent"
    p.write_text("".join(lines))
    return "set"


def run(argv, label):
    r = subprocess.run([sys.executable] + [str(x) for x in argv], capture_output=True, text=True, cwd=ROOT)
    print("  %s rc %d %s" % (label, r.returncode, (r.stdout or r.stderr).strip()[-300:]), flush=True)
    return r.returncode


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("lanes", nargs="+")
    ap.add_argument("--apply", action="store_true", help="perform the writes (default: dry run)")
    ap.add_argument("--decision-b", action="store_true", help="promote a shared region once every mate verifies exact NOW")
    ap.add_argument("--only", help="comma-separated row ids")
    ap.add_argument("--out-glob", default="out/*/*.c")
    a = ap.parse_args()
    only = set(a.only.split(",")) if a.only else None
    all_rows = rows()
    R = {r["id"]: r for r in all_rows}

    infos, skipped = [], []
    for lane in a.lanes:
        for f in sorted(glob.glob(str(ROOT / "work/native_lane" / lane / a.out_glob))):
            rid = "%s/%s" % (Path(f).parent.name, Path(f).stem)
            if only and rid not in only:
                continue
            r = R.get(rid)
            if r is None or not clean_path(r).exists():
                skipped.append((lane, rid, "unknown row"))
                continue
            cand = Path(f).read_text(errors="replace")
            infos.append(row_info(r, lane, f, filter_status(f, cand, clean_path(r).read_text(errors="replace"))))
    in_set = {i["id"] for i in infos if i["filter"] in OK_FILTER}

    def verify_fn(m):
        from verify import verify  # lazy: a plain dry run must not pay for the scorer
        print("    verify mate %s at the true base ..." % m["id"], flush=True)
        return verify(m["row"], clean_path(m["row"]))

    plans = []
    for info in infos:
        mates = [row_info(m, dials=False) for m in members(all_rows, info["family"], info["region"])
                 if m["id"] != info["id"] and m["id"] not in in_set] if info["region"] else []
        if mates and a.decision_b and info.get("conf") == "solved":
            print("%s: region %s holds %d row(s) not re-landing: %s"
                  % (info["id"], info["region"], len(mates), ", ".join(m["id"] for m in mates)), flush=True)
        plans.append((info, plan_row(info, mates, a.decision_b, verify_fn)))

    print("%-34s %-28s %-7s %-12s %s" % ("row", "region", "conf", "filter", "status / plan"))
    n = collections.Counter()
    for info, (status, steps, note) in plans:
        n[status] += 1
        for s in steps:
            n[s[0]] += 1
        print("%-34s %-28s %-7s %-12s %s %s" % (info["id"], info["region"], info["conf"], info["filter"],
                                                status, describe(steps, note)))
    for lane, rid, why in skipped:
        print("%-34s %s (%s)" % (rid, "SKIP " + why, lane))
    print("plan: %d row(s) -- %s" % (len(plans), ", ".join("%s %d" % kv for kv in sorted(n.items()))))

    loose = unresolved(plans)   # both modes: the warning matters most just before the land
    if loose:
        print("WARNING: land_lanes.sh would still land %d unresolved row(s): %s"
              % (len(loose), ", ".join(loose)))
        print("  move them out of out/ or resolve them (--decision-b, a true_name fix) before landing.")
    if not a.apply:
        print("dry run: nothing written.  " + ("Apply, then land:" if n["DO"] else "Land the pack with:"))
        if n["DO"]:
            print("  python3 tools/lanes/promote_honest.py --apply%s %s"
                  % (" --decision-b" if a.decision_b else "", " ".join(a.lanes)))
        print("  bash tools/lanes/land_lanes.sh <tag> %s" % " ".join(a.lanes))
        return 0
    done = collections.Counter()
    regs, seen = [], set()   # two candidates of one region name the same mate once
    for s in [s for _, (st, steps, _n) in plans if st == "DO" for s in steps if s[0] == "register"]:
        if (s[1], s[2]) not in seen:
            seen.add((s[1], s[2]))
            regs.append(s)
    for _k, fam, func, name in regs:
        print(func, "register", name, set_true_name(fam, func, name), flush=True)
        done["register"] += 1
    if regs:
        if run([ROOT / "tools/registry.py"], "registry") or run([ROOT / "tools/row_db.py", "check"], "row_db check"):
            raise SystemExit("registry/row_db check failed: nothing promoted, fix the split table first")
    for _k, fam, func, cand, cfg, _reg in [s for _, (st, steps, _n) in plans if st == "DO"
                                           for s in steps if s[0] == "promote"]:
        rc = run([ROOT / "build_ovl/tools/rowbase.py", "promote", "--family", fam, "--func", func,
                  "--candidate", Path(cand).resolve(), "--config", cfg], "%s promote" % func)
        done["promote" if rc == 0 else "promote-failed"] += 1
    for _k, fam, func, name in [s for _, (st, steps, _n) in plans if st == "DO"
                                for s in steps if s[0] == "as_flags"]:
        print(func, "as_flags true_name", name, set_as_flags_true_name(fam, func, name), flush=True)
        done["as_flags"] += 1
    print("applied: %s.  Now: bash tools/lanes/land_lanes.sh <tag> %s (then its gate)"
          % (", ".join("%s %d" % kv for kv in sorted(done.items())) or "nothing", " ".join(a.lanes)))
    if done["promote-failed"]:
        print("STOP: %d promote(s) failed.  Their true names are registered but the region is still"
              " `solved`, so the gate ignores the true_name and links the honest text at the SYNTHETIC"
              " base: do NOT land until every promote succeeds." % done["promote-failed"])
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
