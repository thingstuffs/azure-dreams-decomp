#!/usr/bin/env python3
"""Stitch only two canonical-source measurements into the frozen whole-tree census."""

from __future__ import annotations

from collections import Counter
import hashlib
import json
from pathlib import Path


HERE = Path(__file__).resolve().parent
ORIGINAL = HERE / "census_full"
CORRECTED = HERE / "census_final_two"
OUT = HERE / "census_reconciled"
EXPECTED = {"slus/w_8003D92C": "w_8003D92C.c",
            "slus/w_80049F68": "w_80049F68.c"}


def sha(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def read_run(path: Path) -> tuple[dict, dict, list[dict]]:
    receipt = json.loads((path / "receipt.json").read_text())
    inputs = json.loads((path / "inputs.json").read_text())
    assert sha(path / "journal.jsonl") == receipt["journal_sha256"]
    assert sha(path / "inputs.json") == receipt["inputs_sha256"]
    rows = [json.loads(line) for line in (path / "journal.jsonl").read_text().splitlines()]
    assert len(rows) == receipt["rows"]
    assert len({row["row"] for row in rows}) == len(rows)
    return receipt, inputs, rows


def main() -> None:
    if OUT.exists():
        raise RuntimeError("reconciled output already exists")
    original, original_inputs, old_rows = read_run(ORIGINAL)
    corrected, corrected_inputs, new_rows = read_run(CORRECTED)
    assert original["rows"] == original_inputs["rows"] == 6767
    assert original["whole_registry"] and original["unchanged_inputs"]
    assert corrected["rows"] == corrected_inputs["rows"] == 2
    assert not corrected["whole_registry"] and corrected["unchanged_inputs"]
    assert set(row["row"] for row in new_rows) == set(EXPECTED)
    assert original_inputs["registry_sha256"] == corrected_inputs["registry_sha256"]
    assert original_inputs["runner_sha256"] == corrected_inputs["runner_sha256"]
    assert original_inputs["versions"] == corrected_inputs["versions"]
    assert original_inputs["assembler"] == corrected_inputs["assembler"]
    assert set(original_inputs["source_sha256"]) == {row["row"] for row in old_rows}
    assert set(corrected_inputs["source_sha256"]) == set(EXPECTED)
    final_fixture = json.loads((HERE / "census_final_fixture/final_source_fixture_receipt.json").read_text())
    compatibility = json.loads((HERE / "census_transition_compatibility.json").read_text())
    assert final_fixture["status"] == "PREPARED"
    assert compatibility["status"] == "COMPATIBLE_WITH_EXPLICIT_SOURCE_BRIDGE"
    assert final_fixture["transition_compatibility_sha256"] == sha(
        HERE / "census_transition_compatibility.json")

    old_by_id = {row["row"]: row for row in old_rows}
    new_by_id = {row["row"]: row for row in new_rows}
    replacements = []
    for rid, name in EXPECTED.items():
        old = old_by_id[rid]
        new = new_by_id[rid]
        if new["status"] != "ok" or new.get("maspsx_exact") is not True or new.get("selfcheck") is not True:
            raise RuntimeError("corrected canonical row is not fully measured: " + rid)
        if new.get("maspsx_retail", {}).get("diff") != 0 or new["maspsx_retail"]["masked"] != 0:
            raise RuntimeError("corrected canonical row is not retail exact: " + rid)
        if not new.get("exact_versions") or len(new.get("genuine") or {}) != 6:
            raise RuntimeError("corrected canonical row lacks six-version proof: " + rid)
        source_before = original_inputs["source_sha256"][rid]
        source_after = corrected_inputs["source_sha256"][rid]
        assert source_before == final_fixture["source_before_sha256"][name]
        assert source_after == final_fixture["source_after_sha256"][name]
        assert old["key"] != new["key"] and source_before != source_after
        replacements.append({
            "row": rid, "old_status": old["status"], "new_status": new["status"],
            "old_key": old["key"], "new_key": new["key"],
            "old_source_sha256": source_before, "new_source_sha256": source_after,
            "old_record_sha256": hashlib.sha256(json.dumps(old, sort_keys=True).encode()).hexdigest(),
            "new_record_sha256": hashlib.sha256(json.dumps(new, sort_keys=True).encode()).hexdigest(),
            "old_tool_fingerprint": original_inputs["tool_fingerprint"],
            "new_tool_fingerprint": corrected_inputs["tool_fingerprint"],
            "genuine_exact_versions": new["exact_versions"],
            "words": new["words"], "retail": new["maspsx_retail"],
        })
    if any(row["status"] != "ok" for row in old_rows if row["row"] not in EXPECTED):
        raise RuntimeError("frozen run has failures outside the canonical-source repair scope")
    merged_rows = [new_by_id.get(row["row"], row) for row in old_rows]
    if any(row["status"] != "ok" or row.get("maspsx_exact") is not True
           or row.get("selfcheck") is not True for row in merged_rows):
        raise RuntimeError("reconciled run has an incomplete row")
    OUT.mkdir()
    (OUT / ".ignore").write_text("*\n")
    (OUT / "journal.jsonl").write_text("".join(json.dumps(row, separators=(",", ":")) + "\n"
                                             for row in merged_rows))
    inputs = dict(original_inputs)
    inputs["fixture"] = "explicitly stitched frozen census plus two canonical-source measurements"
    inputs["source_sha256"] = dict(original_inputs["source_sha256"])
    inputs["source_sha256"].update(corrected_inputs["source_sha256"])
    inputs["source_fixture_exceptions"] = list(EXPECTED)
    inputs["original_inputs_sha256"] = original["inputs_sha256"]
    inputs["corrected_inputs_sha256"] = corrected["inputs_sha256"]
    (OUT / "inputs.json").write_text(json.dumps(inputs, indent=2) + "\n")
    counts = Counter(row["status"] for row in merged_rows)
    receipt = {
        "schema": 1, "status": "RECONCILED", "rows": len(merged_rows),
        "counts": dict(counts), "whole_registry": True,
        "journal_sha256": sha(OUT / "journal.jsonl"),
        "inputs_sha256": sha(OUT / "inputs.json"),
        "unchanged_inputs": True,
        "maspsx_exact": sum(row.get("maspsx_exact") is True for row in merged_rows),
        "selfcheck": sum(row.get("selfcheck") is True for row in merged_rows),
        "genuine_exact_some_version": sum(bool(row.get("exact_versions")) for row in merged_rows),
        "original_receipt_sha256": sha(ORIGINAL / "receipt.json"),
        "corrected_receipt_sha256": sha(CORRECTED / "receipt.json"),
        "final_source_fixture_receipt_sha256": sha(
            HERE / "census_final_fixture/final_source_fixture_receipt.json"),
        "transition_compatibility_sha256": sha(HERE / "census_transition_compatibility.json"),
        "replacements": replacements,
    }
    (OUT / "receipt.json").write_text(json.dumps(receipt, indent=2) + "\n")
    print(json.dumps({key: receipt[key] for key in
                      ("status", "rows", "counts", "maspsx_exact", "selfcheck")}, indent=2))


if __name__ == "__main__":
    main()
