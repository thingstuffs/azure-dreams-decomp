"""Freshness checks for verified SLUS module placement, independent of L4/L5 policy.

The existing ladder still decides pins, tail jumps, source fidelity and toolchain
residue. A module certificate supplies only its reviewed, verified placement.
"""
from __future__ import annotations

import hashlib
import json
from pathlib import Path

from common import ROOT
from slus_module_context import fingerprint, modules, partition_context, module_anchor


def physical_descriptor(module, root=ROOT):
    """Declare a connected destination's complete TU, including incoming parts.

    Contributor IDs document function provenance; they are not placement grants.
    The manifest's whole-member list remains the only placement candidate list.
    """
    row = module_anchor(module, root)
    parents, owners, _ = partition_context(row, root)
    if not parents:
        return None
    if module not in owners:
        raise ValueError("destination is absent from its connected context")
    contributors = [{"row": member["id"], "source": member["source"], "kind": "member",
                     "functions": list(member["functions"])} for member in module["members"]]
    for parent in parents:
        for part in parent["parts"]:
            if part["module"] == module["name"]:
                contributors.append({"row": parent["id"], "source": parent["source"], "kind": "part",
                                     "functions": list(part["functions"])})
    functions = [name for contributor in contributors for name in contributor["functions"]]
    if not functions or len(set(functions)) != len(functions):
        raise ValueError("destination has empty or duplicate contributor coverage")
    return {"source": module["source"], "module": module["name"], "recipe": module["recipe"],
            "functions": sorted(functions), "contributors": contributors}


def check_physical_record(record, member, descriptor, expected_fingerprint):
    """Require one coherent, unmasked genuine result for the complete owner.

    A member-sized success cannot replace the physical comparison. Likewise a
    collector record cannot replace a whole member and silently grant placement.
    Return the measured physical unit after validating both scopes.
    """
    expected = {"diff": 0, "masked": 0, "checked": len(member["functions"])}
    units = record.get("physical_units")
    if (record.get("row") != member["id"] or record.get("status") != "ok"
            or record.get("selfcheck") is not True or record.get("maspsx_exact") is not True
            or record.get("functions") != member["functions"] or record.get("funcs") != len(member["functions"])
            or record.get("maspsx_retail") != expected
            or record.get("module_fingerprint") != expected_fingerprint
            or not isinstance(units, list) or len(units) != 1):
        raise ValueError("connected member lacks complete pipeline/retail proof: " + member["id"])
    unit = units[0]
    if not isinstance(unit, dict):
        raise ValueError("destination physical record is not an object")
    cfg = " ".join(filter(None, (descriptor["recipe"]["ccver"], descriptor["recipe"]["ccflags"])))
    full = {"diff": 0, "masked": 0, "checked": len(descriptor["functions"])}
    if (unit.get("source") != descriptor["source"] or unit.get("module") != descriptor["module"]
            or unit.get("role") != "module" or unit.get("recipe") != descriptor["recipe"]
            or unit.get("cfg") != cfg or record.get("cfg") != cfg
            or unit.get("functions") != member["functions"]
            or unit.get("expected_functions") != descriptor["functions"]
            or unit.get("row") != member["id"] or unit.get("status") != "ok"
            or unit.get("selfcheck") is not True or unit.get("maspsx_exact") is not True
            or unit.get("module_fingerprint") != expected_fingerprint
            or unit.get("maspsx_retail") != expected or unit.get("maspsx_physical_retail") != full
            or unit.get("compiler_model") or unit.get("model") or record.get("compiler_model") or record.get("model")):
        raise ValueError("destination physical context or pipeline proof differs: " + descriptor["source"])
    if not isinstance(unit.get("genuine"), dict) or not isinstance(record.get("genuine"), dict):
        raise ValueError("destination genuine results are not objects")
    genuine = unit.get("genuine", {}).get("2.79", {})
    if not isinstance(genuine, dict):
        raise ValueError("destination genuine result is not an object")
    physical = genuine.get("physical", {})
    aggregate = record.get("genuine", {}).get("2.79", {})
    if not isinstance(physical, dict) or not isinstance(aggregate, dict):
        raise ValueError("destination physical or aggregate result is not an object")
    if (genuine.get("exact") is not True or genuine.get("retail") != [0, 0]
            or genuine.get("retail_checked") != len(member["functions"])
            or "err" in genuine or genuine.get("missing") or genuine.get("lnk_unknown")
            or not isinstance(genuine.get("mode"), str)
            or aggregate.get("exact") is not True or aggregate.get("retail") != [0, 0]
            or aggregate.get("retail_checked") != len(member["functions"])
            or aggregate.get("modes") != {descriptor["source"]: genuine["mode"]}
            or "err" in aggregate or aggregate.get("missing") or aggregate.get("lnk_unknown")
            or physical.get("exact") is not True or physical.get("diff") != 0
            or physical.get("missing") != [] or physical.get("retail") != full
            or not isinstance(physical.get("len_m"), int) or physical["len_m"] <= 0
            or physical.get("len_g") != physical["len_m"]):
        raise ValueError("destination lacks coherent full-TU direct genuine proof: " + descriptor["source"])
    return unit


def check_partition_record(record, contributor, descriptor, expected_fingerprint, root=ROOT):
    """Prove a part-only owner from its real collector measurement.

    The collector must have complete pipeline/retail coverage. Its unrelated
    streams need not be genuine-exact: direct genuine equality is required for
    this destination's entire TU, including every other incoming contributor.
    This result grants data ownership, never whole-collector placement.
    """
    import slus_partitions as partitions
    if (contributor.get("kind") != "part"
            or contributor not in descriptor["contributors"]):
        raise ValueError("partition proof has no declared contributor")
    row = {"kind": "slus", "id": contributor["row"]}
    parents, owners, _ = partition_context(row, root)
    parent = next((p for p in parents if p["id"] == row["id"]), None)
    if parent is None or parent["source"] != contributor["source"]:
        raise ValueError("partition proof has no matching collector")
    units = partitions.row_units(row["id"], parents, owners)
    emitted = partitions.expected_units(parents, owners)
    measured = record.get("physical_units")
    total = {"diff": 0, "masked": 0, "checked": len(parent["functions"])}
    if (record.get("row") != row["id"] or record.get("status") != "ok"
            or record.get("selfcheck") is not True or record.get("maspsx_exact") is not True
            or record.get("functions") != parent["functions"]
            or record.get("funcs") != len(parent["functions"])
            or record.get("maspsx_retail") != total
            or record.get("module_fingerprint") != expected_fingerprint
            or record.get("compiler_model") or record.get("model")
            or not isinstance(measured, list) or len(measured) != len(units)
            or any(not isinstance(u, dict) for u in measured)):
        raise ValueError("collector lacks complete pipeline/retail proof")
    for expected, actual in zip(units, measured):
        scope = {"diff": 0, "masked": 0, "checked": len(expected["functions"])}
        if (any(actual.get(key) != value for key, value in expected.items())
                or actual.get("row") != row["id"] or actual.get("status") != "ok"
                or actual.get("selfcheck") is not True or actual.get("maspsx_exact") is not True
                or actual.get("module_fingerprint") != expected_fingerprint
                or actual.get("funcs") != len(expected["functions"])
                or actual.get("maspsx_retail") != scope
                or actual.get("expected_functions") != sorted(emitted[expected["source"]])):
            raise ValueError("collector physical coverage or context differs")
    matches = [u for u in measured if u.get("source") == descriptor["source"]]
    if len(matches) != 1:
        raise ValueError("partition destination proof is missing or ambiguous")
    unit = matches[0]
    cfg = " ".join(filter(None, (descriptor["recipe"]["ccver"], descriptor["recipe"]["ccflags"])))
    full = {"diff": 0, "masked": 0, "checked": len(descriptor["functions"])}
    if (unit.get("module") != descriptor["module"] or unit.get("role") != "module"
            or unit.get("recipe") != descriptor["recipe"] or unit.get("cfg") != cfg
            or unit.get("functions") != contributor["functions"]
            or unit.get("expected_functions") != descriptor["functions"]
            or unit.get("maspsx_physical_retail") != full
            or unit.get("compiler_model") or unit.get("model")):
        raise ValueError("partition destination physical proof differs")
    versions = unit.get("genuine")
    genuine = versions.get("2.79") if isinstance(versions, dict) else None
    if not isinstance(genuine, dict):
        raise ValueError("partition destination genuine result is missing")
    physical = genuine.get("physical")
    if (genuine.get("exact") is not True or genuine.get("retail") != [0, 0]
            or genuine.get("retail_checked") != len(contributor["functions"])
            or "err" in genuine or genuine.get("missing") or genuine.get("lnk_unknown")
            or not isinstance(genuine.get("mode"), str)
            or not isinstance(physical, dict)
            or physical.get("exact") is not True or physical.get("diff") != 0
            or physical.get("missing") != [] or physical.get("retail") != full
            or type(physical.get("len_m")) is not int or physical["len_m"] <= 0
            or physical.get("len_g") != physical["len_m"]):
        raise ValueError("partition destination lacks direct full-TU genuine proof")
    return unit


def digest(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def check_data_piece_record(module, record, descriptor=None):
    """A split owner needs a bound transform and complete unmasked TU proof."""
    if not module.get("data_pieces"):
        return
    import slus_data_pieces
    from slus_modules import data_piece_plan
    expected_functions = (descriptor["functions"] if descriptor else
                          sorted(f for m in module["members"] for f in m["functions"]))
    if not isinstance(record, dict):
        raise ValueError("data-piece record is not an object")
    units = record.get("physical_units", [])
    if descriptor and (not isinstance(units, list) or any(not isinstance(u, dict) for u in units)):
        raise ValueError("data-piece physical records are malformed")
    candidates = ([u for u in units
                   if u.get("source") == module["source"]] if descriptor else [record])
    if len(candidates) != 1:
        raise ValueError("data-piece owner has ambiguous physical proof")
    unit = candidates[0]
    receipt = unit.get("data_piece_transform")
    if (not isinstance(receipt, dict) or receipt.get("schema") != 1
            or receipt.get("module") != module["name"]
            or receipt.get("plan") != data_piece_plan(module)
            or receipt.get("core_sha256") != digest(slus_data_pieces.__file__)
            or unit.get("data_piece_functions") != expected_functions):
        raise ValueError("data-piece transformation is missing, stale or incorrectly scoped")
    inner = receipt.get("split_elf", {})
    if not isinstance(inner, dict):
        raise ValueError("data-piece split proof is not an object")
    for outer, nested in (("pre_object_sha256", "input_sha256"), ("post_object_sha256", "output_sha256")):
        value = receipt.get(outer)
        if (not isinstance(value, str) or len(value) != 64
                or any(c not in "0123456789abcdef" for c in value) or inner.get(nested) != value):
            raise ValueError("data-piece object hashes are not bound to transformation")
    if (inner.get("relocation_entries_unchanged") is not True
            or inner.get("original_nondata_payloads_unchanged") is not True
            or inner.get("symbol_indices_and_order_unchanged") is not True):
        raise ValueError("data-piece transformation does not preserve code and relocations")
    expected = {"diff": 0, "masked": 0, "checked": len(expected_functions)}
    versions = unit.get("genuine", {})
    if not isinstance(versions, dict):
        raise ValueError("data-piece genuine versions are malformed")
    genuine = versions.get("2.79", {})
    if not isinstance(genuine, dict):
        raise ValueError("data-piece genuine result is malformed")
    physical = genuine.get("physical", {})
    if not isinstance(physical, dict):
        raise ValueError("data-piece physical genuine result is malformed")
    if (unit.get("maspsx_physical_retail") != expected
            or genuine.get("lnk_unknown") or genuine.get("missing") or genuine.get("err")
            or physical.get("exact") is not True or physical.get("diff") != 0
            or physical.get("missing") != [] or physical.get("retail") != expected
            or not isinstance(physical.get("len_m"), int) or physical["len_m"] <= 0
            or physical.get("len_m") != physical.get("len_g")):
        raise ValueError("data-piece owner lacks complete unmasked genuine/retail proof")


def verifier_fingerprint():
    from fidelity.aspsx_diff import tool_fingerprint
    return tool_fingerprint()


def certificate_reason(module, cert, root=ROOT, tool_fp=None):
    """None means current evidence; a string explains why placement is unproved."""
    root = Path(root)
    if module.get("partition_only"):
        return "partition-only owners have no whole-row placement grants; use data ownership proof"
    ids = [m["id"] for m in module["members"]]
    if not isinstance(cert, dict):
        return "certificate is not an object"
    descriptor = physical_descriptor(module, root)
    if cert.get("schema") != (2 if descriptor else 1) or cert.get("module") != module["name"] or cert.get("members") != ids:
        return "certificate does not describe this module and its members"
    if descriptor and cert.get("physical") != descriptor:
        return "certificate physical contributors or destination changed"
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
        try:
            check_data_piece_record(module, rec, descriptor)
        except (ValueError, TypeError, KeyError) as exc:
            return "invalid data-piece verification: " + str(exc)
        if descriptor:
            try:
                check_physical_record(rec, member, descriptor, cert["module_fingerprint"])
            except (ValueError, TypeError, KeyError) as exc:
                return "invalid connected member verification: " + str(exc)
            continue
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
