#!/usr/bin/env python3
"""Verify a reviewed module's live build and record placement evidence.

Read the manifest's evidence document and review membership, shared types,
global declarations and names before passing --reviewer. This records module
placement; it does not override any L4/L5 source or toolchain-residue criterion.
Run under the shared landing lock when writing authoritative evidence.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
from common import rows
from slus_module_context import fingerprint, modules
from slus_module_evidence import certificate_reason, digest, verifier_fingerprint, physical_descriptor
from fidelity import aspsx_diff as A
from fidelity.slus_iso import SlusView


def certify(name, reviewer):
    module = next((m for m in modules() if m["name"] == name), None)
    if module is None:
        raise ValueError("module is not declared: " + name)
    review = ROOT / module["evidence"]
    if not review.is_file() or not reviewer.strip():
        raise ValueError("a reviewed evidence document and reviewer are required")
    if not any(h != "include/common.h" for h in module["headers"]):
        raise ValueError("module placement requires its own shared header")
    by_id = {r["id"]: r for r in rows()}
    members = [m["id"] for m in module["members"]]
    descriptor = physical_descriptor(module)
    start = fingerprint(by_id[members[0]])
    tool_fp = verifier_fingerprint()
    import tempfile
    with tempfile.TemporaryDirectory(prefix="module_certificate_") as td:
        view = SlusView(Path(td) / "build")
        gate = view.calibrate()
        if gate["result"] != "MATCH":
            raise ValueError("module build is not retail-exact: " + str(gate))
        recipe = (view.dest / "build.ninja").read_bytes()
        if recipe != (ROOT / "ledger/splits/slus.build.ninja").read_bytes():
            raise ValueError("module build is not the pinned recipe")
        image = (view.dest / "build/slus_006.14").read_bytes()
    old_versions = A.VERSIONS
    A.VERSIONS = ["2.79"]
    try:
        results = {rid: A.process_row(by_id[rid]) for rid in members}
    finally:
        A.VERSIONS = old_versions
    cert = {"schema": 1, "module": name, "members": members,
            "at": time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime()),
            "module_fingerprint": start, "tool_fingerprint": tool_fp,
            "review": {"path": module["evidence"], "sha256": digest(review), "reviewer": reviewer},
            "gate": dict(gate, recipe_sha256=hashlib.sha256(recipe).hexdigest()),
            "image_sha1": hashlib.sha1(image).hexdigest(), "rows": results}
    if descriptor:
        cert.update(schema=2, physical=descriptor)
    why = certificate_reason(module, cert)
    if why:
        raise ValueError(why)
    return cert


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("module")
    ap.add_argument("--reviewer", required=True)
    ap.add_argument("--write", action="store_true", help="write ledger/modules/<module>.json after all proofs pass")
    args = ap.parse_args()
    cert = certify(args.module, args.reviewer)
    if args.write:
        target = ROOT / "ledger/modules" / (args.module + ".json")
        target.parent.mkdir(parents=True, exist_ok=True)
        temp = target.with_suffix(".tmp")
        temp.write_text(json.dumps(cert, indent=2) + "\n")
        temp.replace(target)
    print(json.dumps({"module": cert["module"], "members": cert["members"], "gate": cert["gate"],
                      "genuine": "2.79 exact; zero masked relocations", "written": args.write}, indent=2))


if __name__ == "__main__":
    main()
