#!/usr/bin/env python3
"""Cross CPU source mutations with a small, observed-site compiler oracle search.

The mutation set comes from sweep transform modules t36..t87 and the lane
perturbation catalogues.  Each distinct admissible source that reaches cc1 is
searched independently.  A hit is a mutation from which a raw-exact *single*
intervention is reachable.  This is diagnostic evidence, never stageable C.
"""
from __future__ import annotations

import argparse
import hashlib
import importlib
import json
import os
import re
import tempfile
from pathlib import Path

import kitlib
import oracle_search
import pass_oracle
import sncheck


def _text_values(value):
    """Conservatively extract C texts from the generators' tuple/list records."""
    if isinstance(value, str):
        if "\n" in value and "{" in value:
            yield value
    elif isinstance(value, (tuple, list)):
        for item in value:
            yield from _text_values(item)
    elif isinstance(value, dict):
        for key in ("text", "candidate", "source"):
            if key in value:
                yield from _text_values(value[key])


def transform_names(root):
    out = []
    for path in sorted((root / "tools/xform").glob("t*.py")):
        match = re.match(r"t(\d+)", path.stem)
        if match and 36 <= int(match.group(1)) <= 87:
            out.append(path.stem)
    return out


def census_row(root, row_id):
    path = root / "ledger/census.jsonl"
    if not path.is_file():
        return {}
    with path.open(errors="replace") as stream:
        for line in stream:
            try:
                rec = json.loads(line)
            except ValueError:
                continue
            if rec.get("id") == row_id:
                return rec
    return {}


def generator_mutations(root, row, text, names, per_generator=6):
    """Yield (generator, label, source); generator failures are evidence, not fatal."""
    import sys

    for path in (root / "tools", root / "tools/xform", root / "tools/lanes"):
        if str(path) not in sys.path:
            sys.path.insert(0, str(path))
    census = census_row(root, row["id"])
    results, diagnostics = [], []
    for name in names:
        try:
            module = importlib.import_module("xform." + name)
            transform = module.T
            why = transform.eligible(text, row, census)
            if why:
                diagnostics.append({"generator": name, "status": "ineligible", "reason": str(why)})
                continue
            captured = []
            candidate_fn = getattr(module, "candidates", None)
            if candidate_fn:
                try:
                    for source in _text_values(candidate_fn(text)):
                        if source != text and source not in captured:
                            captured.append(source)
                        if len(captured) >= per_generator:
                            break
                except Exception as exc:
                    diagnostics.append({"generator": name, "status": "candidate-error", "reason": repr(exc)[:300]})
            if not captured and getattr(transform, "needs_verify", False):
                def observe(candidate, cfg=None):
                    if candidate != text and candidate not in captured and len(captured) < per_generator:
                        captured.append(candidate)
                    return {"exact": False, "status": "mutation-capture", "total": None}
                try:
                    transform.apply_verified(text, row, census, observe)
                except Exception as exc:
                    diagnostics.append({"generator": name, "status": "apply-error", "reason": repr(exc)[:300]})
            elif not captured and hasattr(transform, "apply"):
                try:
                    source = transform.apply(text, row, census)
                    if source and source != text:
                        captured.append(source)
                except Exception as exc:
                    diagnostics.append({"generator": name, "status": "apply-error", "reason": repr(exc)[:300]})
            for index, source in enumerate(captured[:per_generator]):
                results.append((name, "%s:%d" % (name, index + 1), source))
            diagnostics.append({"generator": name, "status": "enumerated", "count": len(captured[:per_generator])})
        except Exception as exc:
            diagnostics.append({"generator": name, "status": "load-error", "reason": repr(exc)[:300]})

    for module_name in ("perturb_basic", "perturb_struct"):
        try:
            module = importlib.import_module(module_name)
            for kind, fn in module.PERTURBATIONS:
                try:
                    instances = fn(text)
                except Exception as exc:
                    diagnostics.append({"generator": module_name + ":" + kind, "status": "apply-error", "reason": repr(exc)[:300]})
                    continue
                for params, source in instances[:per_generator]:
                    results.append((module_name + ":" + kind, params.get("label", kind), source))
                diagnostics.append({"generator": module_name + ":" + kind, "status": "enumerated", "count": min(len(instances), per_generator)})
        except Exception as exc:
            diagnostics.append({"generator": module_name, "status": "load-error", "reason": repr(exc)[:300]})
    return results, diagnostics


def run(row, text, out, mutations=8, oracle_trials=24, workers=2, timeout=30, generators=None, per_generator=4,
        discovery_hook_cap=256):
    out = Path(out).resolve()
    if not out.is_relative_to(kitlib.lane_dir()):
        raise ValueError("mutation output must be lane-owned")
    out.mkdir(parents=True, exist_ok=True)
    (out / ".ignore").write_text("*\n")
    tempfile.tempdir = str(out / "tmp")
    Path(tempfile.tempdir).mkdir(exist_ok=True)
    names = generators or transform_names(kitlib.ROOT)
    generated, diagnostics = generator_mutations(kitlib.ROOT, row, text, names, per_generator)
    unique, seen = [], set()
    for generator, label, source in generated:
        digest = hashlib.sha256(source.encode()).hexdigest()
        if digest in seen:
            continue
        seen.add(digest)
        refusal = kitlib.admissible(text, source, equal_pins=True)
        if refusal:
            diagnostics.append({"generator": generator, "status": "inadmissible", "reason": "; ".join(refusal)})
            continue
        unique.append((generator, label, source, digest))
        if len(unique) >= mutations:
            break
    records = []
    for index, (generator, label, source, digest) in enumerate(unique):
        target = out / "mutations" / ("%03d" % index)
        target.mkdir(parents=True, exist_ok=True)
        (target / "source.c").write_text(source)
        report = oracle_search.search(row, source, target / "oracle", oracle_trials, workers, timeout, True, 0,
                                      discovery_hook_cap=discovery_hook_cap)
        singles = [change for change in report.get("exact_interventions", []) if len(pass_oracle.members(change)) == 1]
        records.append({
            "index": index,
            "generator": generator,
            "label": label,
            "source_sha256": digest,
            "status": report["status"],
            "baseline_aligned_distance": (report.get("baseline") or {}).get("aligned_distance"),
            "closest_trial": report.get("best"),
            "trials": len(report.get("trials", [])),
            "exact_single_interventions": singles,
            "hit": bool(singles),
            "errors": report.get("errors", []),
            "discovery_truncated": report.get("discovery_truncated", False),
            "discovery_skipped_hooks": report.get("discovery_skipped_hooks", []),
            "report": str((target / "oracle/report.json").relative_to(out)),
        })
        (out / "state.json").write_text(json.dumps({"rows": records}, indent=2) + "\n")
    result = {
        "version": 1,
        "row": row["id"],
        "cfg": row["cfg"],
        "counterfactual": True,
        "stageable": False,
        "reviewer": "pending",
        "generator_count": len(names),
        "generated": len(generated),
        "mutations_run": len(records),
        "oracle_trials_per_mutation": oracle_trials,
        "discovery_hook_cap": discovery_hook_cap,
        "hits": [record for record in records if record["hit"]],
        "mutations": records,
        "generator_diagnostics": diagnostics,
    }
    (out / "mutation_search.json").write_text(json.dumps(result, indent=2) + "\n")
    (out / "mutation_search.md").write_text(render(result))
    return result


def render(result):
    lines = ["# Mutation x oracle: " + result["row"], "", "%d source mutations searched; %d exposes an exact single intervention. Counterfactual, reviewer pending. Discovery hook cap: %s; every capped tail is listed in JSON." % (result["mutations_run"], len(result["hits"]), result.get("discovery_hook_cap")), "", "| mutation | generator | base distance | closest trial distance / aligned word diff | exact single intervention | status |", "|---:|---|---:|---|---|---|"]
    for record in result["mutations"]:
        changes = "; ".join("`" + oracle_search.key(c) + "`" for c in record["exact_single_interventions"])
        closest=record.get("closest_trial") or {};diff=json.dumps(closest.get("aligned_word_diff",[]),separators=(",",":"))
        lines.append("| %d | %s | %s | %s / `%s` | %s | %s |" % (record["index"], record["generator"], record["baseline_aligned_distance"], closest.get("aligned_distance","none"), diff.replace("|","/")[:600], changes or "none", record["status"].replace("|", "/")))
    return "\n".join(lines) + "\n"


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("row")
    parser.add_argument("text")
    parser.add_argument("--out", required=True, type=Path)
    parser.add_argument("--mutations", type=int, default=8)
    parser.add_argument("--oracle-trials", type=int, default=24)
    parser.add_argument("--workers", type=int, default=2)
    parser.add_argument("--timeout", type=float, default=30)
    parser.add_argument("--per-generator", type=int, default=4)
    parser.add_argument("--discovery-hook-cap", type=int, default=256, help="per-breakpoint discovery cap; skipped tails are retained in the report")
    parser.add_argument("--generators", help="comma-separated xform module names; default t36..t87 plus perturb catalogues")
    args = parser.parse_args(argv)
    lane = kitlib.bootstrap()
    if not 1 <= args.mutations <= 256 or not 1 <= args.oracle_trials <= 512 or not 1 <= args.workers <= 8 or not 1 <= args.discovery_hook_cap <= 100000:
        parser.error("mutations 1..256, oracle-trials 1..512, workers 1..8, discovery-hook-cap 1..100000 required")
    row = kitlib.row_of(args.row)
    text = sncheck.input_text(args.text, row, lane)
    names = [name for name in args.generators.split(",") if name] if args.generators else None
    result = run(row, text, args.out, args.mutations, args.oracle_trials, args.workers, args.timeout, names, args.per_generator,
                 args.discovery_hook_cap)
    print(json.dumps({"row": result["row"], "mutations": result["mutations_run"], "hits": len(result["hits"])}, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
