#!/usr/bin/env python3
"""Run the candidate's real controls in a short-ASPSX-scratch detached fixture."""

from __future__ import annotations

import hashlib
import json
import os
from pathlib import Path
import shutil
import sys
import tempfile


HERE = Path(__file__).resolve().parent
LANE = HERE.parent
FIXTURE = HERE / "fixture"
LOG = HERE / "run.log"


def sha(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


class Tee:
    def __init__(self, log):
        self.log = log

    def write(self, value):
        sys.__stdout__.write(value)
        self.log.write(value)

    def flush(self):
        sys.__stdout__.flush()
        self.log.flush()


def main() -> None:
    if LOG.exists() or (HERE / "run_receipt.json").exists():
        raise RuntimeError("control run artifacts already exist")
    sys.path.insert(0, str(LANE))
    from live_ownership_probe import production_snapshot
    setup = json.loads((HERE / "prepare_receipt.json").read_text())
    if setup["status"] != "PREPARED" or setup["registry_sha256"] != sha(
            FIXTURE / "ledger/rows.jsonl"):
        raise RuntimeError("prepared control fixture changed")
    for name, hashes in setup["tool_pins"].items():
        if sha(FIXTURE / "tools/fidelity" / name) != hashes["after"]:
            raise RuntimeError("private control tool changed: " + name)
    for name, digest in setup["historical_casesi_pins"].items():
        if sha(FIXTURE / "work/maspsx_jtbl" / name) != digest:
            raise RuntimeError("historical casesi input changed: " + name)
    before = production_snapshot()
    os.chdir(FIXTURE)
    for name in ("AZURE_MASPSX", "AZURE_MASPSX_COMPANION", "PYTHONPATH"):
        os.environ.pop(name, None)
    sys.path[:0] = [str(FIXTURE / "tools"), str(FIXTURE / "tools/build"),
                   str(FIXTURE / "tools/fidelity")]
    import common
    from fidelity import aspsx_diff as A
    if common.ROOT != FIXTURE or A.ROOT != FIXTURE:
        raise RuntimeError("control code imported outside private fixture")
    by = {row["id"]: row for row in common.rows()}
    if len(by) != 6767:
        raise RuntimeError("private registry lost rows")
    scratch = Path(tempfile.mkdtemp(prefix="pctrl_", dir="/tmp"))
    A.TMP = scratch
    A._SLUS = None
    tool_fingerprint = A.tool_fingerprint()
    with LOG.open("w") as log:
        original_stdout = sys.stdout
        sys.stdout = Tee(log)
        try:
            failed = A.run_controls(by)
        finally:
            sys.stdout = original_stdout
    lines = LOG.read_text().splitlines()
    passed_lines = [line for line in lines if line.startswith("PASS  ")]
    failed_lines = [line for line in lines if line.startswith("FAIL  ")]
    expected_names = (
        "casesi 2026-09-14 maspsx default",
        "casesi maspsx --preserve-casesi-at",
        "casesi live maspsx on sw.c",
        "canonical D92C owner",
        "slus/w_8004AB7C:",
        "slus/w_80041AB0:",
        "slus/w_80043CD0:",
        "dungeon/func_818D4E68:",
    )
    for phrase in expected_names:
        if not any(phrase in line for line in lines):
            raise RuntimeError("expected control was skipped: " + phrase)
    after = production_snapshot()
    receipt = {
        "schema": 1,
        "status": "PASS" if failed == 0 and not failed_lines and before == after else "FAIL",
        "controls_return": failed,
        "passed_controls": len(passed_lines),
        "failed_controls": failed_lines,
        "expected_control_names": list(expected_names),
        "log_sha256": sha(LOG),
        "prepare_receipt_sha256": sha(HERE / "prepare_receipt.json"),
        "tool_fingerprint": tool_fingerprint,
        "tool_pins": setup["tool_pins"],
        "historical_casesi_pins": setup["historical_casesi_pins"],
        "scratch": str(scratch),
        "production_unchanged": before == after,
    }
    (HERE / "run_receipt.json").write_text(json.dumps(receipt, indent=2) + "\n")
    if receipt["status"] == "PASS":
        shutil.rmtree(scratch)
    print(json.dumps({key: receipt[key] for key in
                      ("status", "controls_return", "passed_controls", "failed_controls",
                       "production_unchanged")}, indent=2))
    if receipt["status"] != "PASS":
        raise SystemExit(1)


if __name__ == "__main__":
    main()
