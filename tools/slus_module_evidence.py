"""Freshness checks for verified SLUS module placement, independent of L4/L5 policy.

The existing ladder still decides pins, tail jumps, source fidelity and toolchain
residue. A module certificate supplies only its reviewed, verified placement.
"""
from __future__ import annotations

import hashlib
import json
from pathlib import Path

from common import ROOT
from slus_module_context import fingerprint, modules


def digest(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def verifier_fingerprint():
    from fidelity.aspsx_diff import tool_fingerprint
    return tool_fingerprint()


def certificate_reason(module, cert, root=ROOT, tool_fp=None):
    """None means current evidence; a string explains why placement is unproved."""
    root = Path(root)
    ids = [m["id"] for m in module["members"]]
    if not isinstance(cert, dict):
        return "certificate is not an object"
    if cert.get("schema") != 1 or cert.get("module") != module["name"] or cert.get("members") != ids:
        return "certificate does not describe this module and its members"
    row = {"kind": "slus", "id": ids[0]}
    if cert.get("module_fingerprint") != fingerprint(row, root):
        return "module sources, headers or manifest changed"
    if cert.get("tool_fingerprint") != (tool_fp if tool_fp is not None else verifier_fingerprint()):
        return "verification inputs changed"
    review = cert.get("review", {})
    if not isinstance(review, dict) or review.get("path") != module["evidence"] or not review.get("reviewer"):
        return "module membership/type review is missing"
    if review.get("sha256") != digest(root / module["evidence"]):
        return "module membership/type review changed"
    gate = cert.get("gate", {})
    if not isinstance(gate, dict) or gate.get("result") != "MATCH" or gate.get("recipe_sha256") != digest(root / "ledger/splits/slus.build.ninja"):
        return "linked proof does not describe the pinned recipe"
    retail = hashlib.sha1((root / "baserom/slus_006.14").read_bytes()).hexdigest()
    if cert.get("image_sha1") != retail:
        return "linked image does not match the retail reference"
    rows = cert.get("rows", {})
    if not isinstance(rows, dict) or set(rows) != set(ids):
        return "missing member verification"
    for member in module["members"]:
        rec = rows[member["id"]]
        if not isinstance(rec, dict) or not isinstance(rec.get("genuine"), dict):
            return "invalid member verification: " + member["id"]
        genuine = rec.get("genuine", {}).get("2.79", {})
        if not isinstance(genuine, dict):
            return "invalid genuine verification: " + member["id"]
        expected = len(member["functions"])
        cfg = " ".join(filter(None, (module["recipe"]["ccver"], module["recipe"]["ccflags"])))
        if (rec.get("row") != member["id"] or rec.get("status") != "ok"
                or rec.get("cfg") != cfg or rec.get("module") != module["name"]
                or rec.get("selfcheck") is not True or rec.get("maspsx_exact") is not True
                or rec.get("funcs") != expected or genuine.get("exact") is not True
                or genuine.get("retail") != [0, 0]
                or rec.get("maspsx_retail") != {"diff": 0, "masked": 0, "checked": expected}
                or rec.get("module_fingerprint") != cert["module_fingerprint"]):
            return "member lacks unmasked genuine and retail proof: " + member["id"]
    return None


def module_status(root=ROOT, tool_fp=None):
    """Return every declared module, including missing/stale certificates."""
    result = []
    declared = modules(root)
    if declared and tool_fp is None:
        tool_fp = verifier_fingerprint()
    for module in declared:
        path = Path(root) / "ledger/modules" / (module["name"] + ".json")
        cert = None
        try:
            cert = json.loads(path.read_text())
            reason = certificate_reason(module, cert, root, tool_fp)
        except (OSError, ValueError, KeyError, TypeError) as exc:
            reason = "certificate unavailable or invalid: " + str(exc).replace(str(root), "<repo>")
        result.append({"module": module, "certificate": cert, "valid": reason is None, "reason": reason})
    return result


def valid_placements(root=ROOT):
    """The module criterion only; unchanged levels.evaluate_row applies the ladder."""
    return {member["id"]: {"outcome": "applied", "module": entry["module"]["name"],
                            "module_fingerprint": entry["certificate"]["module_fingerprint"]}
            for entry in module_status(root) if entry["valid"] for member in entry["module"]["members"]}
