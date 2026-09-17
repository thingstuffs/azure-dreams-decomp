#!/usr/bin/env python3
"""Validate and inspect the evidence-led pin research case ledger.

The ledger is deliberately small and hand-authored.  This tool checks the parts
that are easy to lose during a long investigation: source identity, concrete
next actions, the scope of negative results, and the gates between a promising
candidate, a verified repair, a transfer, and a landable resolution.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import re
import sys
from pathlib import Path
from typing import Any


ROOT = Path(__file__).resolve().parents[1]
DEFAULT_LEDGER = ROOT / "docs/evidence/pin_research_cases_20260917.json"
STATUSES = {
    "unresolved",
    "experiment_ready",
    "repair_verified",
    "transfer_testing",
    "resolved",
}
CLAIMS = {"unresolved", "bounded_negative", "verified_repair", "impossibility"}
CONFIDENCE = {"low", "medium", "high"}
REVIEW_STATES = {"pending", "pass", "fail", "not_applicable"}
EVIDENCE_KINDS = {
    "observation",
    "bounded_negative",
    "positive_candidate",
    "architecture_limit",
}
SHA256_RE = re.compile(r"[0-9a-f]{64}")


def sha256_file(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def _nonempty(value: Any) -> bool:
    return isinstance(value, str) and bool(value.strip())


def _need(mapping: Any, keys: tuple[str, ...], where: str, errors: list[str]) -> None:
    if not isinstance(mapping, dict):
        errors.append(f"{where}: expected an object")
        return
    for key in keys:
        if key not in mapping or not _nonempty(mapping[key]):
            errors.append(f"{where}.{key}: required non-empty string")


def _review_state(
    case: dict[str, Any],
    name: str,
    evidence: dict[str, str],
    errors: list[str],
) -> str | None:
    where = f"{case.get('id', '<case>')}.verification.{name}"
    item = case.get("verification", {}).get(name)
    if not isinstance(item, dict):
        errors.append(f"{where}: required object")
        return None
    state = item.get("state")
    if state not in REVIEW_STATES:
        errors.append(f"{where}.state: expected one of {sorted(REVIEW_STATES)}")
    refs = item.get("evidence_refs", [])
    if not isinstance(refs, list):
        errors.append(f"{where}.evidence_refs: expected list")
    else:
        if state in {"pass", "fail"} and not refs:
            errors.append(f"{where}.evidence_refs: required when state is {state!r}")
        for ref in refs:
            if ref not in evidence:
                errors.append(f"{where}.evidence_refs: unknown evidence id {ref!r}")
    return state


def _validate_source(case: dict[str, Any], root: Path, errors: list[str]) -> None:
    cid = case.get("id", "<case>")
    source = case.get("source")
    if not isinstance(source, dict):
        errors.append(f"{cid}.source: required object")
        return
    _need(source, ("path", "sha256"), f"{cid}.source", errors)
    rel = source.get("path")
    expected = source.get("sha256")
    if not _nonempty(rel) or not _nonempty(expected):
        return
    if not SHA256_RE.fullmatch(expected):
        errors.append(f"{cid}.source.sha256: expected lowercase SHA-256")
        return
    path = (root / rel).resolve()
    try:
        path.relative_to(root.resolve())
    except ValueError:
        errors.append(f"{cid}.source.path: escapes repository root: {rel}")
        return
    if not path.is_file():
        errors.append(f"{cid}.source.path: missing file: {rel}")
        return
    actual = sha256_file(path)
    if actual != expected:
        errors.append(
            f"{cid}.source.sha256: stale source hash for {rel}: "
            f"recorded {expected}, current {actual}"
        )


def _validate_identity(case: dict[str, Any], errors: list[str]) -> None:
    cid = case.get("id", "<case>")
    retail = case.get("retail")
    if not isinstance(retail, dict):
        errors.append(f"{cid}.retail: required object")
        return
    for part in ("identity", "recipe"):
        item = retail.get(part)
        where = f"{cid}.retail.{part}"
        if not isinstance(item, dict):
            errors.append(f"{where}: required object")
            continue
        _need(item, ("value", "basis"), where, errors)
        if item.get("confidence") not in CONFIDENCE:
            errors.append(f"{where}.confidence: expected one of {sorted(CONFIDENCE)}")


def _validate_artifact(artifact: Any, where: str, root: Path, errors: list[str]) -> None:
    if not isinstance(artifact, dict):
        errors.append(f"{where}: required object with a repository path")
        return
    _need(artifact, ("path",), where, errors)
    rel = artifact.get("path")
    if not _nonempty(rel):
        return
    path = (root / rel).resolve()
    try:
        path.relative_to(root.resolve())
    except ValueError:
        errors.append(f"{where}.path: escapes repository root: {rel}")
        return
    if not path.is_file():
        errors.append(f"{where}.path: missing artifact: {rel}")
    anchor = artifact.get("anchor")
    if anchor is not None and (not _nonempty(anchor) or not anchor.startswith("#")):
        errors.append(f"{where}.anchor: expected a non-empty #anchor")


def _validate_evidence(case: dict[str, Any], root: Path, errors: list[str]) -> dict[str, str]:
    cid = case.get("id", "<case>")
    evidence = case.get("evidence")
    if not isinstance(evidence, list):
        errors.append(f"{cid}.evidence: required list")
        return {}
    ids: dict[str, str] = {}
    for index, item in enumerate(evidence):
        where = f"{cid}.evidence[{index}]"
        if not isinstance(item, dict):
            errors.append(f"{where}: expected object")
            continue
        _need(item, ("id", "summary"), where, errors)
        _validate_artifact(item.get("artifact"), f"{where}.artifact", root, errors)
        eid = item.get("id")
        if _nonempty(eid):
            if eid in ids:
                errors.append(f"{where}.id: duplicate evidence id {eid!r}")
            else:
                ids[eid] = item.get("kind")
        kind = item.get("kind")
        if kind not in EVIDENCE_KINDS:
            errors.append(f"{where}.kind: expected one of {sorted(EVIDENCE_KINDS)}")
        if kind == "bounded_negative":
            bounds = item.get("bounds")
            _need(bounds, ("tested", "untested"), f"{where}.bounds", errors)
        if kind == "positive_candidate":
            candidate = item.get("candidate")
            _need(
                candidate,
                ("source_change", "recipe", "result", "remaining_question"),
                f"{where}.candidate",
                errors,
            )
        if kind == "architecture_limit":
            limit = item.get("limit")
            _need(
                limit,
                ("architecture_or_instruction", "demonstration", "reproduction"),
                f"{where}.limit",
                errors,
            )
            if not isinstance(limit, dict) or limit.get("independently_confirmed") is not True:
                errors.append(
                    f"{where}.limit.independently_confirmed: must be true for an architecture limit"
                )
    return ids


def _validate_candidate(case: dict[str, Any], root: Path, errors: list[str]) -> None:
    cid = case.get("id", "<case>")
    candidate = case.get("candidate")
    required = case.get("status") in {"repair_verified", "transfer_testing", "resolved"}
    if candidate is None and not required:
        return
    if not isinstance(candidate, dict):
        errors.append(f"{cid}.candidate: required object for status {case.get('status')}")
        return
    _need(candidate, ("path", "sha256", "base_source_sha256", "recipe"), f"{cid}.candidate", errors)
    expected = candidate.get("sha256")
    base_sha = candidate.get("base_source_sha256")
    if _nonempty(expected) and not SHA256_RE.fullmatch(expected):
        errors.append(f"{cid}.candidate.sha256: expected lowercase SHA-256")
    if _nonempty(base_sha) and not SHA256_RE.fullmatch(base_sha):
        errors.append(f"{cid}.candidate.base_source_sha256: expected lowercase SHA-256")
    current_sha = case.get("source", {}).get("sha256")
    if current_sha not in {base_sha, expected}:
        errors.append(
            f"{cid}.candidate: current source hash must equal the candidate's baseline or output hash"
        )
    rel = candidate.get("path")
    if not _nonempty(rel) or not _nonempty(expected) or not SHA256_RE.fullmatch(expected):
        return
    path = (root / rel).resolve()
    try:
        path.relative_to(root.resolve())
    except ValueError:
        errors.append(f"{cid}.candidate.path: escapes repository root: {rel}")
        return
    if not path.is_file():
        errors.append(f"{cid}.candidate.path: missing candidate: {rel}")
        return
    actual = sha256_file(path)
    if actual != expected:
        errors.append(
            f"{cid}.candidate.sha256: stale candidate hash for {rel}: "
            f"recorded {expected}, current {actual}"
        )


def _validate_next(case: dict[str, Any], errors: list[str]) -> None:
    cid = case.get("id", "<case>")
    status = case.get("status")
    nxt = case.get("next_experiment")
    if status == "resolved":
        if nxt is not None:
            errors.append(f"{cid}.next_experiment: resolved cases must use null")
        return
    _need(
        nxt,
        ("action", "measurement", "success_criterion", "failure_criterion", "bounds"),
        f"{cid}.next_experiment",
        errors,
    )


def _validate_transfer(
    case: dict[str, Any],
    root: Path,
    evidence: dict[str, str],
    errors: list[str],
) -> None:
    cid = case.get("id", "<case>")
    status = case.get("status")
    transfer = case.get("transfer")
    if not isinstance(transfer, dict) or not isinstance(transfer.get("enabled"), bool):
        errors.append(f"{cid}.transfer.enabled: required boolean")
        return
    if status == "transfer_testing" and not transfer["enabled"]:
        errors.append(f"{cid}.transfer.enabled: transfer_testing requires true")
    if not transfer["enabled"]:
        return
    _need(transfer, ("family", "rule"), f"{cid}.transfer", errors)
    controls = transfer.get("controls")
    if not isinstance(controls, dict):
        errors.append(f"{cid}.transfer.controls: required object")
        return
    seen: list[str] = []
    for role in ("positive", "negative"):
        control = controls.get(role)
        where = f"{cid}.transfer.controls.{role}"
        _need(control, ("case_id", "expected", "source_path", "source_sha256"), where, errors)
        if not isinstance(control, dict):
            continue
        if control.get("independent") is not True:
            errors.append(f"{where}.independent: must be true")
        csha = control.get("source_sha256")
        if _nonempty(csha) and not SHA256_RE.fullmatch(csha):
            errors.append(f"{where}.source_sha256: expected lowercase SHA-256")
        cpath = control.get("source_path")
        if _nonempty(cpath) and _nonempty(csha) and SHA256_RE.fullmatch(csha):
            path = (root / cpath).resolve()
            try:
                path.relative_to(root.resolve())
            except ValueError:
                errors.append(f"{where}.source_path: escapes repository root: {cpath}")
            else:
                if not path.is_file():
                    errors.append(f"{where}.source_path: missing file: {cpath}")
                else:
                    actual = sha256_file(path)
                    if actual != csha:
                        errors.append(
                            f"{where}.source_sha256: stale control hash for {cpath}: "
                            f"recorded {csha}, current {actual}"
                        )
        if _nonempty(control.get("case_id")):
            seen.append(control["case_id"])
            if control["case_id"] == cid:
                errors.append(f"{where}.case_id: control must differ from the exemplar {cid!r}")
        result = control.get("result")
        baseline = control.get("baseline_exact_bytes")
        observed = control.get("observed")
        refs = control.get("evidence_refs", [])
        if not isinstance(refs, list):
            errors.append(f"{where}.evidence_refs: expected list")
        else:
            if (result != "pending" or baseline != "pending" or observed != "pending") and not refs:
                errors.append(f"{where}.evidence_refs: measured controls require evidence")
            for ref in refs:
                if ref not in evidence:
                    errors.append(f"{where}.evidence_refs: unknown evidence id {ref!r}")
        if result not in {"pending", "pass", "fail"}:
            errors.append(f"{where}.result: expected pending, pass, or fail")
        if baseline not in {"pending", "pass", "fail"}:
            errors.append(f"{where}.baseline_exact_bytes: expected pending, pass, or fail")
        allowed_observed = {
            "pending",
            "repair_exact",
            "repair_rejected",
            "mismatch_as_predicted",
            "unexpected",
        }
        if observed not in allowed_observed:
            errors.append(f"{where}.observed: expected one of {sorted(allowed_observed)}")
        if status == "resolved":
            expected_observed = {"repair_exact"} if role == "positive" else {
                "repair_rejected",
                "mismatch_as_predicted",
            }
            if result != "pass" or baseline != "pass" or observed not in expected_observed:
                errors.append(
                    f"{where}: resolved transfer requires an exact baseline and the expected "
                    f"{'exact repair' if role == 'positive' else 'rejection/mismatch'}"
                )
    if len(seen) == 2 and seen[0] == seen[1]:
        errors.append(f"{cid}.transfer.controls: positive and negative controls must be distinct")


def _validate_gates(case: dict[str, Any], evidence: dict[str, str], errors: list[str]) -> None:
    cid = case.get("id", "<case>")
    status = case.get("status")
    verification = case.get("verification")
    if not isinstance(verification, dict):
        errors.append(f"{cid}.verification: required object")
        return
    states = {
        name: _review_state(case, name, evidence, errors)
        for name in ("exact_bytes", "semantic_review", "caller_review", "publication_gate")
    }
    gate = verification.get("publication_gate", {})
    if isinstance(gate, dict) and gate.get("kind") not in {
        "overlay_window",
        "slus_image",
        "not_applicable",
    }:
        errors.append(
            f"{cid}.verification.publication_gate.kind: expected overlay_window, "
            "slus_image, or not_applicable"
        )
    if status in {"repair_verified", "transfer_testing", "resolved"}:
        for name in ("exact_bytes", "semantic_review"):
            if states[name] != "pass":
                errors.append(f"{cid}: status {status} requires {name}=pass")
        if states["caller_review"] not in {"pass", "not_applicable"}:
            errors.append(f"{cid}: status {status} requires caller_review=pass/not_applicable")
        exact_refs = verification.get("exact_bytes", {}).get("evidence_refs", [])
        if not any(evidence.get(ref) == "positive_candidate" for ref in exact_refs):
            errors.append(f"{cid}: verified repair exact_bytes must cite positive_candidate evidence")
    if status == "resolved" and states["publication_gate"] != "pass":
        errors.append(f"{cid}: resolved requires publication_gate=pass")


def validate_ledger(data: Any, root: Path = ROOT) -> list[str]:
    """Return every semantic validation error in a ledger."""
    errors: list[str] = []
    if not isinstance(data, dict):
        return ["ledger: expected an object"]
    if data.get("schema_version") != 1:
        errors.append("ledger.schema_version: expected 1")
    baseline = data.get("baseline")
    if not isinstance(baseline, dict):
        errors.append("ledger.baseline: required object")
    else:
        for key in ("pins", "pinned_rows"):
            value = baseline.get(key)
            if not isinstance(value, int) or isinstance(value, bool) or value < 0:
                errors.append(f"ledger.baseline.{key}: expected a nonnegative integer")
        if baseline.get("target_pins") != 0:
            errors.append("ledger.baseline.target_pins: expected zero")
    cases = data.get("cases")
    if not isinstance(cases, list) or not cases:
        errors.append("ledger.cases: required non-empty list")
        return errors
    case_ids: set[str] = set()
    for index, case in enumerate(cases):
        if not isinstance(case, dict):
            errors.append(f"ledger.cases[{index}]: expected object")
            continue
        cid = case.get("id")
        if not _nonempty(cid):
            errors.append(f"ledger.cases[{index}].id: required non-empty string")
            cid = f"<case-{index}>"
        elif cid in case_ids:
            errors.append(f"ledger.cases[{index}].id: duplicate id {cid!r}")
        else:
            case_ids.add(cid)
        if case.get("status") not in STATUSES:
            errors.append(f"{cid}.status: expected one of {sorted(STATUSES)}")
        claim = case.get("claim")
        if not isinstance(claim, dict) or claim.get("level") not in CLAIMS:
            errors.append(f"{cid}.claim.level: expected one of {sorted(CLAIMS)}")
        elif not _nonempty(claim.get("summary")):
            errors.append(f"{cid}.claim.summary: required non-empty string")
        causal = case.get("causal")
        _need(causal, ("question", "prediction"), f"{cid}.causal", errors)
        _validate_source(case, root, errors)
        _validate_identity(case, errors)
        evidence_ids = _validate_evidence(case, root, errors)
        if isinstance(claim, dict) and claim.get("level") == "impossibility":
            limits = [e for e in case.get("evidence", []) if isinstance(e, dict) and e.get("kind") == "architecture_limit"]
            if not limits:
                errors.append(
                    f"{cid}.claim: impossibility requires demonstrated architecture_limit evidence; "
                    "bounded negatives remain unresolved"
                )
        if case.get("status") == "resolved" and isinstance(claim, dict) and claim.get("level") != "verified_repair":
            errors.append(f"{cid}.claim.level: resolved requires verified_repair")
        if case.get("status") in {"experiment_ready", "repair_verified", "transfer_testing", "resolved"} and not evidence_ids:
            errors.append(f"{cid}: status {case.get('status')} requires evidence")
        _validate_candidate(case, root, errors)
        _validate_next(case, errors)
        _validate_transfer(case, root, evidence_ids, errors)
        _validate_gates(case, evidence_ids, errors)
    return errors


def load_ledger(path: Path) -> Any:
    try:
        return json.loads(path.read_text())
    except FileNotFoundError:
        raise ValueError(f"ledger not found: {path}") from None
    except json.JSONDecodeError as exc:
        raise ValueError(f"invalid JSON in {path}: {exc}") from None


def is_landable(case: dict[str, Any]) -> bool:
    if case.get("status") != "resolved":
        return False
    verification = case.get("verification", {})
    if verification.get("exact_bytes", {}).get("state") != "pass":
        return False
    if verification.get("semantic_review", {}).get("state") != "pass":
        return False
    if verification.get("caller_review", {}).get("state") not in {"pass", "not_applicable"}:
        return False
    if verification.get("publication_gate", {}).get("state") != "pass":
        return False
    transfer = case.get("transfer", {})
    if transfer.get("enabled"):
        controls = transfer.get("controls", {})
        for role in ("positive", "negative"):
            control = controls.get(role, {})
            expected = {"repair_exact"} if role == "positive" else {
                "repair_rejected",
                "mismatch_as_predicted",
            }
            if (
                control.get("result") != "pass"
                or control.get("baseline_exact_bytes") != "pass"
                or control.get("observed") not in expected
            ):
                return False
    return True


def _validated(path: Path, root: Path) -> tuple[dict[str, Any] | None, list[str]]:
    try:
        data = load_ledger(path)
    except ValueError as exc:
        return None, [str(exc)]
    errors = validate_ledger(data, root)
    return data, errors


def cmd_validate(args: argparse.Namespace) -> int:
    data, errors = _validated(args.ledger, args.root)
    if args.json:
        print(json.dumps({"ok": not errors, "errors": errors}, indent=2))
    elif errors:
        for error in errors:
            print(f"ERROR: {error}", file=sys.stderr)
    else:
        cases = data["cases"] if data else []
        landable = sum(is_landable(case) for case in cases)
        print(f"OK: {len(cases)} cases; source hashes current; {landable} landable")
    return 1 if errors else 0


def cmd_list(args: argparse.Namespace) -> int:
    data, errors = _validated(args.ledger, args.root)
    if errors:
        for error in errors:
            print(f"ERROR: {error}", file=sys.stderr)
        return 1
    assert data is not None
    for case in data["cases"]:
        recipe = case["retail"]["recipe"]["value"]
        print(
            f"{case['id']}\t{case['status']}\tclaim={case['claim']['level']}\t"
            f"landable={'yes' if is_landable(case) else 'no'}\t{recipe}"
        )
    return 0


def cmd_next(args: argparse.Namespace) -> int:
    data, errors = _validated(args.ledger, args.root)
    if errors:
        for error in errors:
            print(f"ERROR: {error}", file=sys.stderr)
        return 1
    assert data is not None
    for case in data["cases"]:
        nxt = case.get("next_experiment")
        if nxt:
            print(f"{case['id']} [{case['status']}]\n  {nxt['action']}\n  measure: {nxt['measurement']}")
    return 0


def cmd_show(args: argparse.Namespace) -> int:
    data, errors = _validated(args.ledger, args.root)
    if errors:
        for error in errors:
            print(f"ERROR: {error}", file=sys.stderr)
        return 1
    assert data is not None
    case = next((item for item in data["cases"] if item["id"] == args.case_id), None)
    if case is None:
        print(f"unknown case: {args.case_id}", file=sys.stderr)
        return 2
    out = dict(case)
    out["landable"] = is_landable(case)
    print(json.dumps(out, indent=2, sort_keys=True))
    return 0


def parser() -> argparse.ArgumentParser:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--ledger", type=Path, default=DEFAULT_LEDGER)
    p.add_argument("--root", type=Path, default=ROOT)
    sub = p.add_subparsers(dest="command", required=True)
    val = sub.add_parser("validate", help="check schema, evidence gates, and live source hashes")
    val.add_argument("--json", action="store_true")
    val.set_defaults(func=cmd_validate)
    ls = sub.add_parser("list", help="list cases and whether they are landable")
    ls.set_defaults(func=cmd_list)
    nxt = sub.add_parser("next", help="print the next bounded experiment for each open case")
    nxt.set_defaults(func=cmd_next)
    show = sub.add_parser("show", help="show one validated case")
    show.add_argument("case_id")
    show.set_defaults(func=cmd_show)
    return p


def main(argv: list[str] | None = None) -> int:
    args = parser().parse_args(argv)
    return args.func(args)


if __name__ == "__main__":
    raise SystemExit(main())
