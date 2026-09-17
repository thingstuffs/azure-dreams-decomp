#!/usr/bin/env python3
"""Bounded, read-only byte probes for mechanical aggregate-copy candidates.

The input manifest chooses every row, source file and stock cell explicitly::

  {
    "schema": 1,
    "rows": [
      {"id": "town/func_800B0994",
       "source": "work/native_lane/r42_copy68/base.c",
       "cells": ["2.8.1-G0", "2.7.2-cdk-G0"]}
    ]
  }

At most five rows and four cells per row are accepted.  Results and generated C
go below the requested lane directory.  This command never edits source,
recipes, ledgers or build roots, and every exact result remains explicitly
unreviewed: byte verification is not semantic/caller approval.
"""
from __future__ import annotations

import argparse
import datetime
import json
from pathlib import Path
import tempfile

from aggregate_copy import analyze, candidates
from common import ROOT, clean_path, is_stock_cfg, parse_cfg, rows, sha_text
from verify import verify


MAX_ROWS = 5
MAX_CELLS = 4
MAX_CANDIDATES = 4
INCLUDE = ROOT / "include"


def _stamp():
    return datetime.datetime.now(datetime.timezone.utc).isoformat()


def _summary(v):
    keys = ("exact", "status", "class", "total", "subs", "indels",
            "gen_words", "tgt_words", "secs", "err")
    out = {k: v.get(k) for k in keys if v.get(k) is not None}
    if "exact" not in out:
        out["exact"] = False
    if out.get("err"):
        out["err"] = str(out["err"])[:300].replace(str(ROOT), "<repo>")
    return out


def _at(row, cfg):
    cell, flags = parse_cfg(cfg)
    return dict(row, cfg=cfg, cell=cell, flags=" ".join(flags))


def _score(row, cfg, text, verifier):
    with tempfile.TemporaryDirectory(prefix="aggregate_copy_probe_") as td:
        p = Path(td) / Path(row["c_path"]).name
        p.write_text(text)
        return _summary(verifier(_at(row, cfg), p.resolve(), include_root=INCLUDE))


def _source_path(value):
    p = Path(value)
    p = p if p.is_absolute() else ROOT / p
    p = p.resolve()
    if not p.is_relative_to(ROOT) or not p.is_file():
        raise ValueError("source must be an existing file inside the repository: %s" % value)
    return p


def validate_manifest(manifest, by_id):
    if manifest.get("schema") != 1:
        raise ValueError("manifest schema must be 1")
    specs = manifest.get("rows")
    if not isinstance(specs, list) or not 1 <= len(specs) <= MAX_ROWS:
        raise ValueError("manifest must select 1..%d rows" % MAX_ROWS)
    seen = set()
    for spec in specs:
        if set(spec) - {"id", "source", "cells", "review_refs"}:
            raise ValueError("unknown manifest fields for %s" % spec.get("id", "<missing>"))
        rid = spec.get("id")
        if rid not in by_id or rid in seen:
            raise ValueError("unknown or duplicate row: %s" % rid)
        seen.add(rid)
        row = by_id[rid]
        cells = spec.get("cells")
        if not isinstance(cells, list) or not 1 <= len(cells) <= MAX_CELLS or len(cells) != len(set(cells)):
            raise ValueError("%s must select 1..%d distinct cells" % (rid, MAX_CELLS))
        if row["cfg"] not in cells:
            raise ValueError("%s cells must explicitly include recorded recipe %s" % (rid, row["cfg"]))
        bad = [c for c in cells if not isinstance(c, str) or not is_stock_cfg(c)]
        if bad:
            raise ValueError("%s has non-stock cells: %s" % (rid, bad))
        _source_path(spec.get("source", ""))
        refs = spec.get("review_refs", [])
        if not isinstance(refs, list) or any(not _source_path(x) for x in refs):
            raise ValueError("review_refs must name repository files")
    return specs


def probe(manifest, output, row_table=None, verifier=verify):
    """Run one bounded manifest.  ``verifier`` is injectable for safety tests."""
    by_id = row_table or {r["id"]: r for r in rows()}
    specs = validate_manifest(manifest, by_id)
    output = Path(output).resolve()
    if output.exists():
        raise ValueError("output lane must not already exist")
    output.mkdir(parents=True, exist_ok=False)
    report_path = output / "report.json"
    (output / ".ignore").write_text("raw/\n")
    report = {"schema": 1, "started": _stamp(), "row_limit": MAX_ROWS,
              "candidate_limit_per_row": MAX_CANDIDATES,
              "promotion": "not_performed", "semantic_review": "required", "rows": []}
    for spec in specs:
        row = by_id[spec["id"]]
        source = _source_path(spec["source"])
        text = source.read_text(errors="replace")
        source_sha = sha_text(text)
        scan = analyze(text)
        generated = candidates(text)
        if len(generated) > MAX_CANDIDATES:
            raise ValueError("%s generated more than the bounded candidate menu" % row["id"])
        current = clean_path(row)
        live_sha = sha_text(current.read_text(errors="replace")) if current.is_file() else None
        rec = {"id": row["id"], "recorded_recipe": row["cfg"],
               "source": str(source.relative_to(ROOT)), "source_sha": source_sha,
               "live_source_sha": live_sha, "live_source_matches_input": live_sha == source_sha,
               "historical_source": live_sha != source_sha, "promotion_eligible": False,
               "review_refs": spec.get("review_refs", []), "review_state": "unreviewed",
               "recognizer": {"matches": [m.evidence() for m in scan.matches],
                              "refusals": dict(scan.refusals)}, "baseline": {}, "candidates": []}
        for cfg in spec["cells"]:
            rec["baseline"][cfg] = _score(row, cfg, text, verifier)
        for i, cand in enumerate(generated, 1):
            safe_label = cand.label.replace(":", "_")
            cp = output / "raw" / row["id"] / ("%02d_%s.c" % (i, safe_label))
            cp.parent.mkdir(parents=True, exist_ok=True)
            cp.write_text(cand.text)
            Path(str(cp) + ".base_sha").write_text(source_sha + "\n")
            scores = {cfg: _score(row, cfg, cand.text, verifier) for cfg in spec["cells"]}
            recorded_exact = bool(scores[row["cfg"]].get("exact"))
            recorded_baseline_exact = bool(rec["baseline"][row["cfg"]].get("exact"))
            controls = {}
            for cfg in spec["cells"]:
                base_exact = bool(rec["baseline"][cfg].get("exact"))
                exact = bool(scores[cfg].get("exact"))
                controls[cfg] = {
                    "same_recipe_exact": cfg == row["cfg"] and exact,
                    "baseline_exact_at_selected_cell": base_exact,
                    "candidate_exact_at_selected_cell": exact,
                    "standard_cell_switch_controls_pass":
                        cfg != row["cfg"] and exact and base_exact and recorded_baseline_exact and not recorded_exact,
                }
            rec["candidates"].append({
                "label": cand.label, "path": str(cp.relative_to(output)),
                "candidate_sha": sha_text(cand.text), "review_state": "unreviewed",
                "review_required": True, "promotion": "not_performed",
                "scores": scores, "byte_controls": controls,
            })
        report["rows"].append(rec)
        report_path.write_text(json.dumps(report, indent=2, sort_keys=True) + "\n")
    report["finished"] = _stamp()
    report_path.write_text(json.dumps(report, indent=2, sort_keys=True) + "\n")
    return report


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("manifest", help="explicit row/source/cell JSON manifest")
    ap.add_argument("--output", required=True, help="fresh evidence lane; no production files are changed")
    args = ap.parse_args()
    manifest = json.loads(Path(args.manifest).read_text())
    report = probe(manifest, args.output)
    for row in report["rows"]:
        exact = [(c["label"], [cfg for cfg, s in c["scores"].items() if s.get("exact")])
                 for c in row["candidates"]]
        print("%s candidates=%d exact=%s review=required" % (row["id"], len(row["candidates"]), exact))
    print("wrote %s (no source, recipe, ledger or build-root changes)" % (Path(args.output) / "report.json"))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
