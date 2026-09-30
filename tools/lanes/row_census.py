#!/usr/bin/env python3
"""Row-level census: EVERY live pin of a row erased at once, scored at the registered cfg and at the module
census recipe, with the scorer's residue classified per region.  The joint counterpart of erase_census.py.

    python3 tools/lanes/row_census.py OUT.jsonl [--procs 4] [--only ROWS.txt] [--no-census] [--no-classify]
    python3 tools/lanes/row_census.py summary OUT.jsonl

Why: the lone-erasure census (`erase_census.py`) says nothing about a far-band site - 68% of all sites on
2026-09-30 (r81_opus_gaps section 1): its lone erasure cascades, so the mechanism is only visible at the ROW
level.  This census ranks rows by what the erased text is at each cell, which is the question a cell-move or
whole-row lane starts from.

One record per pinned row:
    {"id", "pins", "cfg", "census_cfg", "module", "d_listing",
     "at": {"<cfg>": {"exact", "total", "status", "err", "classes": {ORDER, COLOUR, OPCODE, COUNT}, "regions",
                      "labels": {label: n regions}}}, "pinned_at_census": {"exact", "total"}}
`d_listing` = the cc1-listing distance (xform.screen, context-aware for slus rows) of the erased text against the
pinned text at the registered cfg.  `at[cfg]` is the BYTE scorer (tools/verify.py via kitlib.score_at) of the
erased text; `classes` is `retailmap.classify` of its `--diff` listing (what `diff.py --scorer --classify` prints,
ORDER = moved, COLOUR = allocation only, OPCODE = different instruction, COUNT = insertion/deletion).  When the
module census recipe (ledger/module_recipe_census.jsonl `best_recipe`, row -> module via ledger/modules.jsonl)
differs from the registered cfg, the erased text is scored there as well, and so is the PINNED text
(`pinned_at_census`: exact = the recipe switch alone is byte-neutral, rule 2).  slus module / partitioned rows
are scored at their registered cfg only (a per-row recipe trial is refused for them by design); slus scorer
output has no aligned listing, so their records carry totals, not classes.

Nothing under ledger/, config/ or src/ is written; compiles run in a TemporaryDirectory under OUT's directory
(the lane kit's bootstrap).  Keep OUT out of agent-searched work/ subtrees if it grows past a few MB (a whole
tree run is ~0.3 MB).  Resumable: rows already in OUT are skipped.  ~5-10 s a row (two to four scorer runs).
"""
from __future__ import annotations

import collections
import json
import sys
import time
from multiprocessing import Pool
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
KIT = Path(__file__).resolve().parent / "lanekit"
sys.path.insert(0, str(KIT))
import kitlib                                                             # noqa: E402

CENSUS = ROOT / "ledger/module_recipe_census.jsonl"
MODULES = ROOT / "ledger/modules.jsonl"
OPTS = {"census": True, "classify": True}
_CACHE = {}


def census_map():
    """row id -> (module, best_recipe) from the module census (rows without a module are absent)."""
    if "census" not in _CACHE:
        best = {}
        if CENSUS.is_file():
            for line in CENSUS.read_text().splitlines():
                if line.strip():
                    d = json.loads(line)
                    if d.get("best_recipe"):
                        best[(d["container"], d["module"])] = d["best_recipe"]
        out = {}
        if MODULES.is_file():
            for line in MODULES.read_text().splitlines():
                if line.strip():
                    d = json.loads(line)
                    k = (d.get("container"), d.get("module"))
                    if k in best:
                        out[d["id"]] = (d["module"], best[k])
        _CACHE["census"] = out
    return _CACHE["census"]


def per_row_trial_ok(row):
    """False for a slus module / partitioned row: its recipe is the module's (kitlib.row_at_cfg refuses)."""
    return row.get("kind") != "slus" or kitlib.module_fingerprint(row) is None


def classify(text):
    import retailmap as RM                                               # noqa: E402
    rows = RM.scorer_rows(text or "")
    if not rows:
        return None
    regions, totals = RM.classify(rows)
    return {"classes": totals, "regions": len(regions),
            "labels": dict(collections.Counter(r["label"] for r in regions))}


def score(row, text, cfg, want_classes):
    v = kitlib.score_at(row, text, cfg if cfg != row["cfg"] else None)
    rec = {k: v.get(k) for k in ("exact", "total", "status")}
    if v.get("err"):
        rec["err"] = str(v["err"])[:200]
    if want_classes and not v.get("exact") and row.get("kind") != "slus" and v.get("status") not in ("failed",):
        c = classify(kitlib.score_at(row, text, cfg if cfg != row["cfg"] else None, diff=True).get("text"))
        if c:
            rec.update(c)
    return rec


def one(rid):
    t0 = time.time()
    out = {"id": rid}
    try:
        row = kitlib.row_of(rid)
        from common import clean_path                                    # noqa: E402
        text = clean_path(row).read_text(errors="replace")               # the TREE's text, never a lane copy
        sites = kitlib.sites(text)
        out.update(pins=len(sites), cfg=row["cfg"])
        if not sites:
            out["skip"] = "no pins"
            return out
        erased = kitlib.erased_text(text)
        from variant_screen import row_listing                           # noqa: E402
        import screen                                                    # noqa: E402
        out["d_listing"] = screen.sdiff(row_listing(row, text), row_listing(row, erased))
        m = census_map().get(rid)
        out["module"], out["census_cfg"] = (m if m else (None, None))
        out["at"] = {row["cfg"]: score(row, erased, row["cfg"], OPTS["classify"])}
        if OPTS["census"] and m and m[1] != row["cfg"] and per_row_trial_ok(row):
            out["at"][m[1]] = score(row, erased, m[1], OPTS["classify"])
            p = kitlib.score_at(row, text, m[1])
            out["pinned_at_census"] = {"exact": p.get("exact"), "total": p.get("total")}
    except BaseException as e:                                           # a row's failure is data, not a crash
        out["err"] = repr(e)[:300]
    out["secs"] = round(time.time() - t0, 1)
    return out


def _init(opts, lane):
    OPTS.update(opts)
    kitlib.bootstrap(lane)


def pinned_ids():
    """Every registered row whose tree text has a live pin (the tree's `src/`, never a lane copy)."""
    kitlib.add_paths()
    from common import rows, clean_path                                  # noqa: E402
    out = []
    for r in rows():
        p = clean_path(r)
        if p.is_file() and kitlib.sites(p.read_text(errors="replace")):
            out.append(r["id"])
    return sorted(out)


def summary(path):
    recs = [json.loads(l) for l in open(path) if l.strip()]
    ok = [r for r in recs if "at" in r]
    print("rows %d  measured %d  errors %d  skipped %d" % (
        len(recs), len(ok), sum(1 for r in recs if "err" in r), sum(1 for r in recs if "skip" in r)))
    print("pins in measured rows: %d" % sum(r["pins"] for r in ok))
    band = collections.Counter()
    cls = collections.Counter()
    for r in ok:
        a = r["at"][r["cfg"]]
        t = a.get("total")
        # a jump-table row whose erased text moves a case target is refused by the scorer (`jtbl: local .rodata ...`,
        # the round-80 jump-table check): no total, but it is NOT exact - booked apart from real build errors
        band["exact" if a.get("exact") else ("jtbl-mismatch" if str(a.get("err", "")).startswith("jtbl") else "error")
             if t is None else "1-4" if t <= 4 else "5-16" if t <= 16 else "17-64" if t <= 64 else "65+"] += 1
        for k, v in (a.get("classes") or {}).items():
            cls[k] += v
    print("erased text at the registered cfg (rows):", dict(band))
    print("residue words by class at the registered cfg:", dict(cls))
    closer = []
    for r in ok:
        if r.get("census_cfg") and r["census_cfg"] in r["at"] and r["census_cfg"] != r["cfg"]:
            a, b = r["at"][r["cfg"]].get("total"), r["at"][r["census_cfg"]].get("total")
            if b is not None and (a is None or b < a) or r["at"][r["census_cfg"]].get("exact"):
                closer.append((b if b is not None else 0, r["id"], r["pins"], r["cfg"], r["census_cfg"], a,
                               (r.get("pinned_at_census") or {}).get("exact")))
    print("rows whose ERASED text is closer at the module census recipe: %d" % len(closer))
    for b, rid, n, cfg, cc, a, p in sorted(closer)[:40]:
        print("  %-26s pins %2d  %s: %s  ->  %s: %s   pinned exact there: %s" % (rid, n, cfg, a, cc, b, p))
    near = sorted((r["at"][r["cfg"]].get("total") or 0, r["id"], r["pins"]) for r in ok
                  if not r["at"][r["cfg"]].get("exact") and r["at"][r["cfg"]].get("total") is not None)[:25]
    print("nearest erased rows at the registered cfg (total, row, pins):")
    for t, rid, n in near:
        print("  %4d  %-26s %d" % (t, rid, n))


def main():
    a = sys.argv[1:]
    if a and a[0] == "summary":
        return summary(a[1])
    if not a:
        raise SystemExit(__doc__)
    out = Path(a.pop(0)).resolve(); procs = 4; only = None; opts = dict(OPTS)
    while a:
        k = a.pop(0)
        if k == "--procs":
            procs = int(a.pop(0))
        elif k == "--only":
            only = [x.split()[0] for x in Path(a.pop(0)).read_text().splitlines() if x.strip()]
        elif k == "--no-census":
            opts["census"] = False
        elif k == "--no-classify":
            opts["classify"] = False
        else:
            raise SystemExit("row_census.py: unknown option %s" % k)
    lane = out.parent
    kitlib.bootstrap(lane)                     # compiles and scorer temp files under OUT's directory
    ids = only if only is not None else pinned_ids()
    done = set()
    if out.exists():
        for l in out.open():
            try:
                done.add(json.loads(l)["id"])
            except Exception:
                pass
    ids = [i for i in ids if i not in done]
    t0 = time.time(); n = 0
    with Pool(procs, initializer=_init, initargs=(opts, str(lane))) as p, out.open("a") as f:
        for rec in p.imap_unordered(one, ids, chunksize=1):
            f.write(json.dumps(rec) + "\n"); f.flush(); n += 1
            if n % 25 == 0:
                print(n, "rows", round(time.time() - t0), "s", flush=True)
    print("done", n, "rows", round(time.time() - t0), "s")


if __name__ == "__main__":
    main()
