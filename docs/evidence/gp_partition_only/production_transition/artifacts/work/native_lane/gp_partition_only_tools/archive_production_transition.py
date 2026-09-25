#!/usr/bin/env python3
"""Archive actual production transition evidence after completion.

Run only after the final activation, fresh census, dependency proposal/import,
and completion audit exist. This script reads source artifacts and writes one
new docs/evidence/gp_partition_only/production_transition directory. It never
edits production inputs and refuses to replace an existing archive.

Example (supply the actual proof/report paths when they exist)::

  python3 work/native_lane/gp_partition_only_tools/archive_production_transition.py \
    --census-run work/native_lane/gp_partition_only_tools/production_census \
    --dependency-proposal work/native_lane/gp_partition_only_tools/production_dependency_proposal \
    --report-file PATH --import-proof PATH \
    --completion-file work/native_lane/gp_partition_only_tools/production_completion.json

All activation attempts sharing the approved run ID are included by default.
Use --activation-run for a later independent run, and --script-file for its runner.
The failed receipts are preserved as failures; the archive requires one actual
PASS_GATES_CENSUS_PENDING activation receipt, not a fabricated success claim.
"""

from __future__ import annotations

import argparse
import gzip
import hashlib
import json
import os
from pathlib import Path
import re
import shutil
import tempfile


HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[2]
DEST = ROOT / "docs/evidence/gp_partition_only/production_transition"
ACTIVATION_PREFIX = "20260925T010431Z_625211"
SCRIPTS = (
    "activate_transition.py",
    "census_runner.py",
    "dependency_import.py",
    "archive_production_transition.py",
)
CHUNK_THRESHOLD = 1_000_000


def file_sha(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for chunk in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(chunk)
    return digest.hexdigest()


def source_path(value: str | Path) -> Path:
    path = Path(value)
    resolved = (path if path.is_absolute() else ROOT / path).resolve()
    if not resolved.is_relative_to(ROOT) or not resolved.is_file():
        raise ValueError(f"expected an existing repository file: {value}")
    if resolved.is_relative_to(DEST):
        raise ValueError("archive cannot include itself")
    return resolved


def directory_path(value: str | Path) -> Path:
    path = Path(value)
    resolved = (path if path.is_absolute() else ROOT / path).resolve()
    if not resolved.is_relative_to(ROOT) or not resolved.is_dir():
        raise ValueError(f"expected an existing repository directory: {value}")
    if resolved.is_relative_to(DEST):
        raise ValueError("archive cannot include itself")
    return resolved


def read_json(path: Path) -> dict:
    value = json.loads(path.read_text())
    if not isinstance(value, dict):
        raise ValueError(f"expected a JSON object: {path}")
    return value


def scrub(data: bytes) -> bytes:
    # The reference checkout and current checkout may both appear in logs and
    # receipts. Keep receipt hash fields intact; only replace path bytes.
    replacements = (
        (str(ROOT.parent / ("azure-" + "decomp")).encode(), b"<reference-repo>"),
        (str(ROOT).encode(), b"<repo>"),
        (str(ROOT.parent).encode(), b"<user-home>"),
    )
    for old, new in replacements:
        data = data.replace(old, new)
    data = re.sub(rb"/" + rb"home/[^/\s\"']+", b"<user-home>", data)
    return data


def add_file(selected: dict[Path, str], value: str | Path, category: str) -> None:
    path = source_path(value)
    if path in selected and selected[path] != category:
        raise ValueError(f"artifact selected in two categories: {path.relative_to(ROOT)}")
    selected[path] = category


def collect(args: argparse.Namespace) -> tuple[dict[Path, str], list[dict], Path, Path]:
    selected: dict[Path, str] = {}
    for name in SCRIPTS:
        add_file(selected, HERE / name, "runner")
    for path in sorted(HERE.glob("resume_approved_activation*.py")):
        add_file(selected, path, "runner")
    for name in ("production_controls.py", "production_census_followthrough.py"):
        path = HERE / name
        if path.is_file():
            add_file(selected, path, "runner")
    for value in args.script_file:
        add_file(selected, value, "runner")
    # The two repair supplements are separate from the approved 60-file packet.
    for name in ("test_configure_slus_data_pieces.py", "test_slus_row_db_aliases.py",
                 "test_slus_module_member_scope.py"):
        add_file(selected, ROOT / "tools/tests" / name, "activation_supplement")
    add_file(selected, ROOT / "tools/row_db.py", "activation_supplement")

    runs = sorted(path for path in (HERE / "activation_runs").iterdir()
                  if path.is_dir() and path.name.startswith(ACTIVATION_PREFIX))
    runs.extend(directory_path(value) for value in args.activation_run)
    attempts = []
    seen_runs: set[Path] = set()
    for run in runs:
        run = directory_path(run)
        if run in seen_runs:
            continue
        seen_runs.add(run)
        activation = run / "activation_receipt.json"
        if not activation.is_file():
            raise ValueError(f"activation receipt missing: {run.relative_to(ROOT)}")
        current = read_json(activation)
        failure = run / "failure_receipt.json"
        decisive = read_json(failure) if failure.is_file() else current
        attempts.append({"run": str(run.relative_to(ROOT)),
                         "status": decisive.get("status"),
                         "phase": decisive.get("phase"),
                         "has_failure_receipt": failure.is_file()})
        for path in sorted(run.iterdir()):
            if path.is_file() and (path.name in {"activation_receipt.json", "failure_receipt.json"}
                                   or path.suffix == ".log"
                                   or path.name in {"ownership_receipt.json", "overlay_journal.jsonl"}):
                add_file(selected, path, "activation")
    if not any(a["status"] == "PASS_GATES_CENSUS_PENDING" for a in attempts):
        raise ValueError("no completed activation gate receipt among selected attempts")

    controls = HERE / "production_controls"
    for name in ("receipt.json", "controls.log"):
        path = controls / name
        if path.is_file():
            add_file(selected, path, "production_controls")

    census = directory_path(args.census_run)
    for name in ("receipt.json", "inputs.json", "journal.jsonl"):
        add_file(selected, census / name, "fresh_production_census")
    receipt = read_json(census / "receipt.json")
    inputs = read_json(census / "inputs.json")
    if (receipt.get("status") != "MEASURED" or receipt.get("rows") != 6767
            or receipt.get("counts", {}).get("ok") != 6767
            or receipt.get("maspsx_exact") != 6767
            or receipt.get("selfcheck") != 6767
            or receipt.get("whole_registry") is not True
            or receipt.get("unchanged_inputs") is not True):
        raise ValueError("fresh census receipt is incomplete")
    if (inputs.get("fixture") != str(ROOT) or inputs.get("rows") != 6767
            or inputs.get("whole_registry") is not True):
        raise ValueError("census inputs do not identify this production root")

    proposal = directory_path(args.dependency_proposal)
    for name in ("receipt.json", "maspsx_dependence.proposed.jsonl"):
        add_file(selected, proposal / name, "dependency_proposal")
    proposal_receipt = read_json(proposal / "receipt.json")
    if proposal_receipt.get("status") != "FRESH_PRODUCTION_VALIDATED":
        raise ValueError("dependency proposal lacks fresh-production validation")
    for value in args.report_file:
        add_file(selected, value, "census_report")
    for value in args.import_proof:
        add_file(selected, value, "dependency_import_proof")
    for value in args.completion_file:
        add_file(selected, value, "completion_audit")
    return selected, attempts, census, proposal


def archive_one(source: Path, category: str, stage: Path) -> dict:
    relative = source.relative_to(ROOT)
    compress = source.stat().st_size >= CHUNK_THRESHOLD
    target_rel = Path("artifacts") / relative
    if compress:
        target_rel = target_rel.with_name(target_rel.name + ".gz")
    target = stage / target_rel
    target.parent.mkdir(parents=True, exist_ok=True)
    source_hash = hashlib.sha256()
    content_hash = hashlib.sha256()
    source_size = 0
    content_size = 0
    before = source.stat()
    with source.open("rb") as origin, target.open("wb") as output:
        sink = gzip.GzipFile(filename="", mode="wb", fileobj=output, mtime=0) if compress else output
        try:
            for line in origin:
                source_hash.update(line)
                source_size += len(line)
                clean = scrub(line)
                content_hash.update(clean)
                content_size += len(clean)
                sink.write(clean)
        finally:
            if compress:
                sink.close()
    after = source.stat()
    if (before.st_size, before.st_mtime_ns) != (after.st_size, after.st_mtime_ns):
        raise ValueError(f"source changed during archive: {relative}")
    return {"category": category, "source": str(relative),
            "archived": str(target_rel), "source_sha256": source_hash.hexdigest(),
            "content_sha256": content_hash.hexdigest(),
            "archived_sha256": file_sha(target),
            "source_bytes": source_size, "content_bytes": content_size,
            "archived_bytes": target.stat().st_size, "gzip": compress}


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--activation-run", action="append", default=[], metavar="DIR",
                        help="additional activation attempt directory; approved run series is automatic")
    parser.add_argument("--script-file", action="append", default=[], metavar="FILE")
    parser.add_argument("--census-run", required=True, metavar="DIR")
    parser.add_argument("--dependency-proposal", required=True, metavar="DIR")
    parser.add_argument("--report-file", action="append", required=True, metavar="FILE")
    parser.add_argument("--import-proof", action="append", required=True, metavar="FILE")
    parser.add_argument("--completion-file", action="append", required=True, metavar="FILE")
    args = parser.parse_args()
    if DEST.exists():
        raise ValueError("refusing to replace an existing production transition archive")
    selected, attempts, census, proposal = collect(args)
    parent = DEST.parent
    parent.mkdir(parents=True, exist_ok=True)
    stage = Path(tempfile.mkdtemp(prefix=".production_transition.", dir=parent))
    try:
        artifacts = [archive_one(path, category, stage)
                     for path, category in sorted(selected.items(), key=lambda item: str(item[0]))]
        by_source = {item["source"]: item for item in artifacts}

        def source_hash(path: Path) -> str:
            return by_source[str(path.relative_to(ROOT))]["source_sha256"]

        for attempt in attempts:
            if attempt["status"] != "PASS_GATES_CENSUS_PENDING":
                continue
            run = ROOT / attempt["run"]
            activation = read_json(run / "activation_receipt.json")
            overlay = run / "overlay_journal.jsonl"
            ownership = run / "ownership_receipt.json"
            if (not overlay.is_file() or not ownership.is_file()
                    or activation.get("overlay_gate", {}).get("journal_sha256") != source_hash(overlay)
                    or activation.get("ownership", {}).get("sha256") != source_hash(ownership)):
                raise ValueError("successful activation lacks matching overlay/ownership proof")

        census_receipt = read_json(census / "receipt.json")
        census_inputs = read_json(census / "inputs.json")
        proposal_receipt = read_json(proposal / "receipt.json")
        if (census_receipt.get("journal_sha256") != source_hash(census / "journal.jsonl")
                or census_receipt.get("inputs_sha256") != source_hash(census / "inputs.json")
                or census_inputs.get("runner_sha256") != source_hash(HERE / "census_runner.py")
                or proposal_receipt.get("run_receipt_sha256") != source_hash(census / "receipt.json")
                or proposal_receipt.get("proposed_ledger_sha256") != source_hash(
                    proposal / "maspsx_dependence.proposed.jsonl")):
            raise ValueError("census or dependency proposal provenance hash mismatch")
        manifest = {
            "schema": 1,
            "status": "PRODUCTION_TRANSITION_EVIDENCE_ARCHIVED",
            "scope": "Actual activation attempts, fresh production census, dependency proposal/import proof and completion audit",
            "attempts": attempts,
            "path_scrubbing": "Original source hashes bind private/production files; content hashes bind scrubbed bytes; archived hashes bind stored bytes. Restore paths and decompress .gz files for replay.",
            "artifacts": artifacts,
        }
        (stage / "archive.json").write_text(json.dumps(manifest, indent=2) + "\n")
        # Publish only after all files and provenance checks have succeeded.
        os.rename(stage, DEST)
    finally:
        if stage.exists():
            shutil.rmtree(stage)
    print(json.dumps({"status": manifest["status"], "files": len(artifacts),
                      "archive": str(DEST.relative_to(ROOT))}))


if __name__ == "__main__":
    main()
