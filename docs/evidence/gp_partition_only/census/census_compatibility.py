#!/usr/bin/env python3
"""Bind the frozen census fixture to the proposed transition payload."""

from __future__ import annotations

from collections import Counter
import difflib
import hashlib
import json
from pathlib import Path


HERE = Path(__file__).resolve().parent
FIXTURE = HERE / "census_fixture"
TRANSITION = HERE / "transition"


def sha(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main() -> None:
    inventory_path = TRANSITION / "inventory.json"
    inventory = json.loads(inventory_path.read_text())
    hygiene_path = TRANSITION / "inputs/source_hygiene/receipt.json"
    hygiene = json.loads(hygiene_path.read_text())
    assert hygiene["status"] == "MATCH"
    bridges = {record["source"]: record for record in hygiene["records"]}
    assert len(bridges) == 4
    canonical_path = TRANSITION / "inputs/canonical_sources/receipt.json"
    canonical = json.loads(canonical_path.read_text())
    assert canonical["status"] == "MATCH_EXCEPT_FILE_METADATA"
    canonical_targets = {"src/slus/" + name: digest
                         for name, digest in canonical["proposed_sources"].items()}
    assert len(canonical_targets) == 4
    for record in canonical["records"]:
        assert record["identical_except_file_metadata"] is True
        assert record["compiler_assembly_identical"] is False
        before = (TRANSITION / "inputs/canonical_sources/before" /
                  (record["owner"] + ".s")).read_text().splitlines()
        after = (TRANSITION / "inputs/canonical_sources/after" /
                 (record["owner"] + ".s")).read_text().splitlines()
        assert [line for line in before if not line.lstrip().startswith(".file")] == [
            line for line in after if not line.lstrip().startswith(".file")]

    fixture_configure = (FIXTURE / "tools/build/configure.py").read_text().splitlines(keepends=True)
    final_configure_path = HERE.parent / "gp_ready29_collectors/stage/tools/configure.py"
    final_configure = final_configure_path.read_text().splitlines(keepends=True)
    opcode = [op for op in difflib.SequenceMatcher(a=fixture_configure,
                                                   b=final_configure,
                                                   autojunk=False).get_opcodes()
              if op[0] != "equal"]
    assert len(opcode) == 1 and opcode[0][0] == "insert", opcode
    _, i, j, k, l = opcode[0]
    assert i == j and fixture_configure[i - 1].startswith("nonmatch = ")
    added = "".join(final_configure[k:l])
    assert added.count("CC_VER.update({") == 2
    assert added.count('"src/w_') == 15
    assert sha(final_configure_path) == next(
        file["after_sha256"] for file in inventory["files"]
        if file["target"] == "tools/build/configure.py")

    fixture_ledger = FIXTURE / "ledger/splits/slus.jsonl"
    transition_ledger = TRANSITION / "serialized_slus.jsonl"
    ledger_a = [json.loads(line) for line in fixture_ledger.read_text().splitlines()]
    ledger_b = [json.loads(line) for line in transition_ledger.read_text().splitlines()]
    assert len(ledger_a) == len(ledger_b) == 884 and ledger_a == ledger_b

    classifications = Counter()
    file_results = []
    for file in inventory["files"]:
        target = file["target"]
        fixture_path = FIXTURE / target
        if fixture_path.is_file() and sha(fixture_path) == file["after_sha256"]:
            kind = "byte_identical"
        elif target == "src/slus/gp_d92c_owned.c":
            bridge = bridges[target]
            canonical_before = TRANSITION / "inputs/canonical_sources/before/gp_d92c_owned.c"
            canonical_after = TRANSITION / "inputs/canonical_sources/after/gp_d92c_owned.c"
            assert sha(fixture_path) == bridge["before_sha256"]
            assert sha(canonical_before) == bridge["after_sha256"]
            assert sha(canonical_after) == file["after_sha256"] == canonical_targets[target]
            assert bridge["compiler_assembly_identical"] is True
            assert bridge["before_assembly_sha256"] == bridge["after_assembly_sha256"]
            kind = "hygiene_then_canonical_source_bridge"
        elif target in bridges:
            bridge = bridges[target]
            assert sha(fixture_path) == bridge["before_sha256"]
            assert file["after_sha256"] == bridge["after_sha256"]
            assert bridge["compiler_assembly_identical"] is True
            assert bridge["before_assembly_sha256"] == bridge["after_assembly_sha256"]
            kind = "assembly_identical_source_bridge"
        elif target in canonical_targets:
            canonical_after = TRANSITION / "inputs/canonical_sources/after" / Path(target).name
            assert sha(canonical_after) == file["after_sha256"] == canonical_targets[target]
            if Path(target).name == "gp_order_bytes_owner.c":
                canonical_before = TRANSITION / "inputs/canonical_sources/before/gp_order_bytes_owner.c"
                assert sha(canonical_before) == sha(fixture_path)
                kind = "canonical_owner_metadata_only_bridge"
            else:
                assert file["before_sha256"] == sha(fixture_path)
                kind = "canonical_fragment_moved_body"
        elif target == "tools/build/configure.py":
            kind = "retired_whole_row_recipe_policy"
        elif target == "ledger/splits/slus.jsonl":
            assert sha(transition_ledger) == file["after_sha256"]
            kind = "ordered_semantic_ledger_equal"
        elif target.startswith("tools/maspsx/tests/"):
            kind = "test_only_difference"
        elif target in {"docs/SLUS_MODULES.md",
                        "tools/tests/test_slus_partition_only_build.py",
                        "tools/tests/test_slus_partition_only_evidence.py"}:
            assert not fixture_path.exists()
            kind = "new_doc_or_test"
        else:
            raise RuntimeError(f"Unclassified transition/fixture difference: {target}")
        classifications[kind] += 1
        file_results.append({"target": target, "classification": kind,
                             "transition_sha256": file["after_sha256"],
                             "fixture_sha256": sha(fixture_path) if fixture_path.is_file() else None})
    assert len(file_results) == inventory["total_changed_or_new_files"] == 57
    expected_classifications = Counter({
        "byte_identical": 38,
        "assembly_identical_source_bridge": 3,
        "hygiene_then_canonical_source_bridge": 1,
        "canonical_owner_metadata_only_bridge": 1,
        "canonical_fragment_moved_body": 2,
        "retired_whole_row_recipe_policy": 1,
        "ordered_semantic_ledger_equal": 1,
        "test_only_difference": 7,
        "new_doc_or_test": 3,
    })
    assert classifications == expected_classifications, (classifications, expected_classifications)

    result = {
        "schema": 1,
        "status": "COMPATIBLE_WITH_EXPLICIT_SOURCE_BRIDGE",
        "inventory_sha256": sha(inventory_path),
        "transition_patch_sha256": sha(TRANSITION / "transition.patch"),
        "hygiene_receipt_sha256": sha(hygiene_path),
        "canonical_receipt_sha256": sha(canonical_path),
        "fixture_setup_receipt_sha256": sha(FIXTURE / "census_setup_receipt.json"),
        "ledger_records": len(ledger_a),
        "fixture_ledger_sha256": sha(fixture_ledger),
        "transition_ledger_sha256": sha(transition_ledger),
        "configure_inserted_cc_ver_rows": 15,
        "classifications": dict(classifications),
        "files": file_results,
    }
    out = HERE / "census_transition_compatibility.json"
    out.write_text(json.dumps(result, indent=2) + "\n")
    print(json.dumps({k: result[k] for k in ("status", "classifications", "ledger_records")},
                     indent=2))


if __name__ == "__main__":
    main()
