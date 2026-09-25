#!/usr/bin/env python3
"""Summarize the private full ASPSX census while retaining physical-unit scopes."""

from __future__ import annotations

from collections import Counter, defaultdict
import hashlib
import json
from pathlib import Path
import subprocess
import sys

HERE = Path(__file__).resolve().parent
FIXTURE = HERE / "census_fixture"
FULL = HERE / "census_reconciled"
OUT = HERE / "census_report"
OWNERS = {
    "accessors_814c8": "src/c8_accessors_owned.c",
    "table_counters_b1b_b1c": "src/b1b_b1c_table_owned.c",
}


def sha(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main() -> None:
    receipt = json.loads((FULL / "receipt.json").read_text())
    if receipt.get("rows") != 6767 or not receipt.get("whole_registry") or not receipt.get("unchanged_inputs"):
        raise RuntimeError("complete pinned census receipt is unavailable")
    if sha(FULL / "journal.jsonl") != receipt["journal_sha256"]:
        raise RuntimeError("census journal differs from receipt")
    if sha(FULL / "inputs.json") != receipt["inputs_sha256"]:
        raise RuntimeError("census inputs differ from receipt")
    inputs = json.loads((FULL / "inputs.json").read_text())
    setup = json.loads((FIXTURE / "census_setup_receipt.json").read_text())
    if inputs["registry_sha256"] != setup["registry_sha256"] or inputs["rows"] != 6767:
        raise RuntimeError("census measured a different registry")
    if set(inputs.get("source_fixture_exceptions") or []) != {
            "slus/w_8003D92C", "slus/w_80049F68"}:
        raise RuntimeError("canonical-source replacements are not explicit")
    replacements = receipt.get("replacements") or []
    if len(replacements) != 2 or set(r["row"] for r in replacements) != set(
            inputs["source_fixture_exceptions"]):
        raise RuntimeError("reconciliation receipt lacks two-row provenance")
    rows = [json.loads(line) for line in (FULL / "journal.jsonl").read_text().splitlines()]
    if len(rows) != 6767 or len({row["row"] for row in rows}) != 6767:
        raise RuntimeError("census journal lost or duplicated a row")
    by_id = {row["row"]: row for row in rows}
    if set(by_id) != set(inputs["source_sha256"]):
        raise RuntimeError("census journal differs from frozen source set")

    OUT.mkdir(exist_ok=False)
    (OUT / ".ignore").write_text("*\n")
    command = [sys.executable, str(FIXTURE / "tools/fidelity/aspsx_report.py"),
               "--journal", str(FULL / "journal.jsonl"), "--out-dir", str(OUT)]
    with (OUT / "tables_raw.md").open("w") as output:
        result = subprocess.run(command, cwd=FIXTURE, stdout=output,
                                stderr=subprocess.PIPE, text=True)
    (OUT / "aspsx_report.stderr.log").write_text(result.stderr)
    if result.returncode:
        raise RuntimeError("private aspsx_report failed: " + result.stderr[-1000:])

    status = Counter(row.get("status") for row in rows)
    container = defaultdict(Counter)
    for row in rows:
        count = container[row["container"]]
        count["rows"] += 1
        count["pipeline_exact"] += row.get("maspsx_exact") is True
        count["selfcheck"] += row.get("selfcheck") is True
        count["genuine_common"] += bool(row.get("exact_versions"))
        retail = row.get("maspsx_retail") or {}
        if not all(isinstance(retail.get(key), int) and retail[key] >= 0
                   for key in ("diff", "masked", "checked")):
            raise RuntimeError("row lacks complete scoped retail comparison: " + row["row"])
        count["retail_unmasked_differences"] += retail["diff"]
        count["retail_masked_words"] += retail["masked"]
        count["retail_masked_rows"] += retail["masked"] > 0
        units = row.get("physical_units") or []
        if units and not row.get("exact_versions") and all(u.get("exact_versions") for u in units):
            count["genuine_ownerwise_no_common"] += 1
        if row.get("n_gp_externs"):
            count["gp_extern_rows"] += 1
    selected = {}
    for name, source in OWNERS.items():
        measurements = [(row["row"], unit) for row in rows for unit in
                        (row.get("physical_units") or []) if unit.get("source") == source]
        if len(measurements) != 1:
            raise RuntimeError("selected physical owner lacks unique census unit: " + name)
        rid, unit = measurements[0]
        selected[name] = {
            "collector_row": rid, "source": source,
            "functions": unit.get("functions"), "expected_functions": unit.get("expected_functions"),
            "words": unit.get("words"), "pipeline_retail": unit.get("maspsx_retail"),
            "genuine_exact_versions": unit.get("exact_versions"),
            "genuine_279": unit.get("genuine", {}).get("2.79"),
            "gp_externs": unit.get("gp_externs"),
        }
    collectors = {}
    for rid in ("slus/code", "slus/code2"):
        row = by_id[rid]
        collectors[rid] = {
            "status": row.get("status"), "pipeline_exact": row.get("maspsx_exact"),
            "selfcheck": row.get("selfcheck"),
            "logical_functions": row.get("funcs"), "logical_words": row.get("words"),
            "common_genuine_exact_versions": row.get("exact_versions"),
            "physical_units": [{
                "source": unit.get("source"), "role": unit.get("role"),
                "module": unit.get("module"), "functions": len(unit.get("functions") or []),
                "words": unit.get("words"), "genuine_exact_versions": unit.get("exact_versions"),
                "best": unit.get("best"), "gp_externs": unit.get("gp_externs"),
                "best_ablation_fixes": (unit.get("attrib") or {}).get(unit.get("best"), {}).get("fix"),
            } for unit in row.get("physical_units") or []],
        }
    errors = [{"row": row["row"], "status": row.get("status"), "err": row.get("err")}
              for row in rows if row.get("status") != "ok"]
    stage_path = HERE.parent / "gp_ready29_collectors/receipt.json"
    stage = json.loads(stage_path.read_text())
    modules = json.loads((FIXTURE / "config/slus_modules.json").read_text())["modules"]
    plural = [row for row in rows if row.get("physical_units")]
    scope = {
        "registered_rows": len(rows), "slus_logical_rows": container["slus"]["rows"],
        "slus_physical_objects": stage["graph"]["physical"],
        "slus_modules": len(modules),
        "slus_partition_only_modules": sum(bool(m.get("partition_only")) for m in modules),
        "plural_logical_rows": len(plural),
        "plural_physical_unit_measurements": sum(len(r["physical_units"]) for r in plural),
        "plural_distinct_physical_sources": len({u["source"] for r in plural
                                                 for u in r["physical_units"]}),
    }
    if scope != {"registered_rows": 6767, "slus_logical_rows": 884,
                  "slus_physical_objects": 860, "slus_modules": 33,
                  "slus_partition_only_modules": 2, "plural_logical_rows": 20,
                  "plural_physical_unit_measurements": 29,
                  "plural_distinct_physical_sources": 10}:
        raise RuntimeError("candidate census/graph physical scopes changed: " + str(scope))
    owner_extern_abs = sorted((r["row"], u["source"])
        for r in rows for u in r.get("physical_units") or []
        if "extern-abs" in (((u.get("attrib") or {}).get(u.get("best")) or {}).get("fix") or []))
    single_extern_abs = sorted(r["row"] for r in rows if not r.get("physical_units")
        and "extern-abs" in (((r.get("attrib") or {}).get(r.get("best")) or {}).get("fix") or []))
    metadata_probe_path = HERE / "code_metadata_probe/receipt.json"
    metadata_probe = json.loads(metadata_probe_path.read_text())
    if (metadata_probe["status"] != "ATTRIBUTED" or
            metadata_probe["inputs_unchanged"] is not True or
            metadata_probe["fresh_normal_matches_measured_object_disassembly_and_relocations"] is not True or
            metadata_probe["extern_strip_equals_disable_store_delay_listing"] is not True or
            any(record["gprel_relocations"] != 0 for record in metadata_probe["records"].values()) or
            metadata_probe["records"]["strip_externs"]["object_sha256"] !=
            metadata_probe["records"]["disable_store_delay"]["object_sha256"]):
        raise RuntimeError("code remainder metadata attribution is not complete")
    gp_model = {
        "detected_external_gp_rows": sum(bool(r.get("n_gp_externs")) for r in rows),
        "detected_external_gp_symbols": sorted({s for r in rows for s in r.get("gp_externs") or []}),
        "single_stream_extern_abs_ablations": single_extern_abs,
        "owner_only_extern_abs_ablations": owner_extern_abs,
        "metadata_probe_sha256": sha(metadata_probe_path),
        "metadata_probe_status": metadata_probe["status"],
        "interpretation": "The detector found no named external-GP sites. The code remainder's "
                          "sole extern-abs ablation is caused by extern-size metadata gating "
                          "the store-delay rewrite: stripping externs and disabling that rewrite "
                          "produce identical listings and objects, and all three arms have zero "
                          "GPREL relocations. This case is scheduling debt, not GP addressing debt.",
    }
    pass_probe = {}
    for name in ("_sink_call_separated_la", "_split_funcaddr_la"):
        fired_rows = sorted(r["row"] for r in rows if name in (r.get("fired") or []))
        fired_units = sorted((r["row"], u["source"]) for r in rows
            for u in r.get("physical_units") or [] if name in (u.get("fired") or []))
        required_rows = sorted(r["row"] for r in rows if not r.get("physical_units")
            and "no:" + name in (((r.get("attrib") or {}).get(r.get("best")) or {}).get("fix") or []))
        required_units = sorted((r["row"], u["source"]) for r in rows
            for u in r.get("physical_units") or []
            if "no:" + name in (((u.get("attrib") or {}).get(u.get("best")) or {}).get("fix") or []))
        pass_probe[name] = {"fired_rows": fired_rows, "fired_units": fired_units,
                            "required_rows": required_rows, "required_units": required_units}
    if gp_model["owner_only_extern_abs_ablations"] != [("slus/code", "src/code.c")]:
        raise RuntimeError("small-extern-GP owner dependence changed")
    if pass_probe["_sink_call_separated_la"] != {"fired_rows": [], "fired_units": [],
                                                  "required_rows": [], "required_units": []}:
        raise RuntimeError("call separated-la pass evidence changed")
    if pass_probe["_split_funcaddr_la"]["fired_rows"] != ["dungeon/func_818D4E68"]:
        raise RuntimeError("function-address split pass firing scope changed")
    slus_remaining = [r["row"] for r in rows if r["container"] == "slus"
                      and not r.get("exact_versions")]
    if len(slus_remaining) != 13:
        raise RuntimeError("SLUS genuine dependent row count changed")
    mask_scope = {name: {"masked_rows": count["retail_masked_rows"],
                         "masked_words": count["retail_masked_words"],
                         "unmasked_differences": count["retail_unmasked_differences"]}
                  for name, count in container.items()}
    if mask_scope != {
            "main": {"masked_rows": 26, "masked_words": 133, "unmasked_differences": 0},
            "town": {"masked_rows": 83, "masked_words": 244, "unmasked_differences": 0},
            "dungeon": {"masked_rows": 192, "masked_words": 492, "unmasked_differences": 0},
            "ovmovie": {"masked_rows": 1, "masked_words": 3, "unmasked_differences": 0},
            "slus": {"masked_rows": 0, "masked_words": 0, "unmasked_differences": 0},
    }:
        raise RuntimeError("scoped retail mask counts changed: " + str(mask_scope))
    retail_scope = {
        "comparator": "maspsx_retail",
        "unmasked_differences": sum(v["unmasked_differences"] for v in mask_scope.values()),
        "masked_words": sum(v["masked_words"] for v in mask_scope.values()),
        "rows_with_masked_words": sum(v["masked_rows"] for v in mask_scope.values()),
        "by_container": mask_scope,
        "interpretation": "All 6,767 rows have zero unmasked retail differences, but 872 words "
                          "in 302 overlay rows are relocation-masked. This comparator alone "
                          "does not prove direct byte identity for those words. SLUS has zero masks.",
    }
    scope_note = (
        "# Comparison scope\n\n"
        "The genuine-version counts below compare genuine ASPSX output with the traced "
        "generic pipeline at each declared function or physical-unit scope. They are not "
        "unqualified direct-retail byte counts. The separate `maspsx_retail` comparator "
        "reports zero unmasked differences across all 6,767 rows, with 872 masked words "
        "across 302 overlay rows (main 133/26, town 244/83, dungeon 492/192, "
        "ovmovie 3/1; SLUS 0/0). Full SLUS image and active-window byte gates "
        "are separate stronger evidence.\n\n"
    )
    (OUT / "tables.md").write_text(scope_note + (OUT / "tables_raw.md").read_text())
    report = {
        "schema": 1,
        "status": "PASS" if not errors and receipt.get("maspsx_exact") == 6767
                  and receipt.get("selfcheck") == 6767 else "DIAGNOSTIC",
        "rows": len(rows), "status_counts": dict(status),
        "pipeline_exact": receipt.get("maspsx_exact"),
        "selfcheck": receipt.get("selfcheck"),
        "common_genuine_exact": sum(bool(row.get("exact_versions")) for row in rows),
        "container": {name: dict(values) for name, values in container.items()},
        "selected_owners": selected, "collectors": collectors, "errors": errors,
        "scope": scope, "retail_scope": retail_scope,
        "gp_model": gp_model, "pass_probe": pass_probe,
        "slus_genuine_dependent_rows": slus_remaining,
        "journal_sha256": receipt["journal_sha256"],
        "inputs_sha256": receipt["inputs_sha256"],
        "reconciliation_receipt_sha256": sha(FULL / "receipt.json"),
        "frozen_original_receipt_sha256": receipt["original_receipt_sha256"],
        "canonical_two_row_receipt_sha256": receipt["corrected_receipt_sha256"],
        "transition_compatibility_sha256": receipt["transition_compatibility_sha256"],
        "source_replacements": replacements,
        "registry_sha256": setup["registry_sha256"],
        "aspsx_report_sha256": sha(FIXTURE / "tools/fidelity/aspsx_report.py"),
        "ready29_receipt_sha256": sha(stage_path),
        "tables_sha256": sha(OUT / "tables.md"),
        "tables_raw_sha256": sha(OUT / "tables_raw.md"),
        "production_snapshot": str(FIXTURE / "production_after_census.json"),
    }
    (OUT / "summary.json").write_text(json.dumps(report, indent=2) + "\n")
    md = [
        "# Guarded generic whole-tree ASPSX census",
        "",
        f"Measured **{len(rows)}** private registered rows with unchanged candidate tools. "
        "Two canonical-source records were remeasured in a separate pinned fixture and explicitly "
        "stitched into the frozen whole-tree journal. "
        f"Pipeline exact: **{receipt.get('maspsx_exact')}**; self-check: **{receipt.get('selfcheck')}**; "
        f"status errors: **{len(errors)}**. "
        f"Rows matching the traced generic pipeline under at least one common genuine "
        f"version: **{report['common_genuine_exact']}**. The retail comparator found zero "
        f"unmasked differences, with **{retail_scope['masked_words']}** masked words across "
        f"**{retail_scope['rows_with_masked_words']}** overlay rows.",
        "",
        "| Container | Rows | Pipeline exact | Self-check | Genuine equals pipeline | Retail masked words / rows |",
        "| --- | ---: | ---: | ---: | ---: | ---: |",
    ]
    for name in ("slus", "main", "town", "dungeon", "ovmovie"):
        c = container[name]
        md.append(f"| {name} | {c['rows']} | {c['pipeline_exact']} | {c['selfcheck']} "
                  f"| {c['genuine_common']} | {c['retail_masked_words']} / {c['retail_masked_rows']} |")
    md += [
        "",
        "The two selected partition-only owners retain complete physical-unit measurements. "
        "The code and code2 collector records retain their full logical functions and separate "
        "remainder measurements; owner-specific genuine results do not imply genuine equality "
        "for those remainders.",
        "",
        "The six-version tables measure genuine-versus-pipeline equality. Direct retail "
        "comparison has zero unmasked differences, but its 872 relocation-masked words are "
        "not direct byte proofs. SLUS has zero masks in this census; the full SLUS image and "
        "active-window byte gates are separate stronger checks.",
        "",
        f"SLUS scope: **{scope['slus_logical_rows']}** logical rows, "
        f"**{scope['slus_physical_objects']}** physical objects, **{scope['slus_modules']}** "
        f"modules including **{scope['slus_partition_only_modules']}** partition-only owners. "
        f"The **{scope['plural_logical_rows']}** partitioned logical records contain "
        f"**{scope['plural_physical_unit_measurements']}** physical-unit measurements across "
        f"**{scope['plural_distinct_physical_sources']}** sources. SLUS genuine-dependent rows: "
        f"**{len(slus_remaining)}**.",
        "",
        "Small-extern GP: the named-symbol detector lists zero rows. The sole `extern-abs` "
        "ablation is on the `slus/code` remainder; a pinned three-arm probe shows stripping "
        "externs and disabling `_expand_store_to_symbol_in_delay` produce identical listings "
        "and objects, with zero GPREL relocations in every arm. Its remaining difference is "
        "metadata-gated scheduling, not GP addressing. "
        "`_sink_call_separated_la` fired zero times and was required zero times; "
        "`_split_funcaddr_la` fired once and was required by `dungeon/func_818D4E68`.",
        "",
        "The original raw journal and input pins are preserved in census_full/; its two old owner "
        "records remain there. The replacement records and source hashes are in census_final_two/, "
        "and the explicit old/new keys are in census_reconciled/receipt.json. Tables and physical-unit/pass TSVs "
        "from the unchanged private aspsx_report.py are in census_report/. The prior registry's "
        "428 cfg_corrected annotations and one town assembler-flag override remain present; "
        "only 15 SLUS recipe fields were projected from the fresh registry.",
    ]
    (HERE / "census_report.md").write_text("\n".join(md) + "\n")
    print(json.dumps({k: report[k] for k in ("status", "rows", "pipeline_exact",
                                             "selfcheck", "common_genuine_exact")},
                     indent=2))


if __name__ == "__main__":
    main()
