"""Conservative census-anchor plans for individual banks of bank families.

``twins.bank_plan`` derives a candidate from the preceding 0x6000 bank.  That
relationship is useful for the repeated-bank families, but it cannot close a
gap when the preceding bank has no registered complete donor.  This read-only
pass gives each bank its own single-window stub and sends it through
``single_plan.runner_plan``.  The single-window planner still requires a
census entry anchor, a complete body inside the span and window, an exact
unmasked relocation proof, and complete direct-callee contracts.

All output is kept below ``evidence/bank_anchor_plans``.  Current staging
ledger extents are added to the BASE ledger extents before planning, so a
candidate cannot overlap a row admitted by another worker while this pass is
running.  No staging, source, or package files are changed.
"""

import argparse
import collections
import json
import sys
from pathlib import Path

MAIN_SCRIPTS = Path(__file__).resolve().parent
sys.path.insert(0, str(MAIN_SCRIPTS))

from twins import L, R, World, load_families  # noqa: E402
import single_plan  # noqa: E402


OUTPUT_DIR = "bank_anchor_plans"


def as_int(value):
    """Parse ledger integers, including decimal and 0x-prefixed strings."""

    if isinstance(value, int):
        return value
    text = str(value).strip()
    try:
        return int(text, 0)
    except ValueError:
        return int(text)


def read_jsonl(path):
    if not path.is_file():
        return []
    rows = []
    for line in path.read_text().splitlines():
        if not line or line.startswith("#"):
            continue
        try:
            rows.append(json.loads(line))
        except json.JSONDecodeError:
            # A concurrently written ledger line is not evidence.  The next
            # pass can read it once its writer has completed the JSON line.
            continue
    return rows


def current_staging_extents(world, container):
    """Return BASE plus current staging extents for one binary container."""

    out = []
    seen = set()
    for start, size, ident in single_plan.existing_extents(world, container):
        item = (int(start), int(size), str(ident))
        key = item[:2]
        if key not in seen:
            out.append(item)
            seen.add(key)

    # The split ledger is a known narrow path.  Read the container file only;
    # do not recurse through staging, which also contains build manifests.
    ledger = R / "ledger" / "splits" / (container + ".jsonl")
    for record in read_jsonl(ledger):
        if record.get("foff") is None or record.get("size") is None:
            continue
        try:
            start = as_int(record["foff"])
            size = as_int(record["size"])
        except (TypeError, ValueError):
            continue
        if size <= 0:
            continue
        ident = record.get("id") or record.get("func_vram") or "staging-split"
        key = (start, size)
        if key in seen:
            continue
        out.append((start, size, str(ident)))
        seen.add(key)
    return out


def one_bank_stub(family, bank):
    """Make a one-bank family accepted by the generic single-window planner."""

    start = as_int(bank["start"])
    stub = dict(family)
    stub["id"] = "%s__%s" % (family["id"], hex(start))
    stub["kind"] = "single-window"
    stub["source_family"] = family["id"]
    stub["banks"] = [dict(bank)]
    return stub


def proof_counts(rows):
    """Summarize proof material that survived all planner gates."""

    source_valid = 0
    relocation_valid = 0
    contract_valid = 0
    relocation_words = 0
    direct_calls = 0
    for row in rows:
        if row.get("source_sha256") and row.get("src"):
            source_valid += 1
        relocation = row.get("relocation_proof")
        # ``proof`` returns [] for an exact body copy.  That is a valid exact
        # proof; only a missing proof field indicates a planner defect.
        if relocation is not None:
            relocation_valid += 1
        relocation = relocation or []
        relocation_words += len(relocation)
        calls = row.get("contracts") or []
        direct_calls += len(calls)
        if all(call.get("contract") and call.get("target_body_proof") for call in calls):
            contract_valid += 1
    return {
        "source_valid": source_valid,
        "relocation_valid": relocation_valid,
        "contract_valid": contract_valid,
        "relocation_words": relocation_words,
        "direct_calls": direct_calls,
    }


def plan_bank(family, bank, world, occupied):
    """Plan one bank and attach provenance needed by the aggregate report."""

    stub = one_bank_stub(family, bank)
    rows, holds = single_plan.runner_plan(
        stub,
        world,
        evidence_dir=OUTPUT_DIR,
        occupied=occupied.get(bank["container"], ()),
    )
    reasons = collections.Counter(item.get("reason", "unknown") for item in holds)
    proof = proof_counts(rows)
    return {
        "family": family["id"],
        "stub": stub["id"],
        "window": bank["window"],
        "container": bank["container"],
        "start": int(bank["start"]),
        "end": int(bank["end"]),
        "vram": int(bank["vram"]),
        "status": "CANDIDATES" if rows else "HOLD",
        "extra_candidate_count": len(rows),
        "candidate_bytes": sum(int(row["size"]) for row in rows),
        "hold_count": len(holds),
        "hold_reasons": dict(sorted(reasons.items())),
        "current_extent_count": len(occupied.get(bank["container"], ())),
        "proof": proof,
    }


def priority_key(family):
    """Run unresolved/no-row families first, then the remaining bank families."""

    evidence = L / "evidence" / family["id"]
    no_rows = False
    no_donor = False
    for name in ("result.json", "holds.json", "checkpoint.json"):
        path = evidence / name
        if not path.is_file():
            continue
        try:
            value = json.loads(path.read_text())
        except (OSError, json.JSONDecodeError):
            continue
        values = value if isinstance(value, list) else [value]
        text = json.dumps(values)
        no_rows |= '"rows": []' in text or '"candidate_count": 0' in text
        no_donor |= "no matched complete donor rows" in text
    return (0 if (no_rows or no_donor) else 1, family["id"])


def run(families=None):
    all_families = [family for family in load_families() if family.get("kind") == "bank-family"]
    by_id = {family["id"]: family for family in all_families}
    if families:
        missing = [name for name in families if name not in by_id]
        if missing:
            raise SystemExit("unknown bank family: " + ", ".join(missing))
        selected = [by_id[name] for name in families]
    else:
        selected = sorted(all_families, key=priority_key)

    world = World()
    occupied = {
        container: current_staging_extents(world, container)
        for container in ("dungeon", "town", "main", "ovmovie")
    }
    reports = []
    for family in selected:
        for bank in family["banks"]:
            report = plan_bank(family, bank, world, occupied)
            reports.append(report)
            print(
                "%s %s candidates=%d bytes=%d holds=%d"
                % (
                    report["stub"],
                    report["status"],
                    report["extra_candidate_count"],
                    report["candidate_bytes"],
                    report["hold_count"],
                ),
                flush=True,
            )

    totals = {
        "bank_family_count": len(selected),
        "bank_count": len(reports),
        "extra_candidate_count": sum(item["extra_candidate_count"] for item in reports),
        "candidate_bytes": sum(item["candidate_bytes"] for item in reports),
        "hold_count": sum(item["hold_count"] for item in reports),
        "source_valid": sum(item["proof"]["source_valid"] for item in reports),
        "relocation_valid": sum(item["proof"]["relocation_valid"] for item in reports),
        "contract_valid": sum(item["proof"]["contract_valid"] for item in reports),
        "relocation_words": sum(item["proof"]["relocation_words"] for item in reports),
        "direct_calls": sum(item["proof"]["direct_calls"] for item in reports),
        "hold_reasons": dict(
            sorted(
                collections.Counter(
                    reason
                    for item in reports
                    for reason in item["hold_reasons"]
                    for _ in range(item["hold_reasons"][reason])
                ).items()
            )
        ),
        "read_only": True,
        "staging_mutated": False,
        "occupied_source": "BASE ledger rows/splits plus current staging/root/ledger/splits",
    }
    out = L / "evidence" / OUTPUT_DIR
    out.mkdir(parents=True, exist_ok=True)
    (out / "summary.json").write_text(
        json.dumps({"schema": "azure-clean.bank-anchor-summary.v1", "totals": totals, "banks": reports}, indent=1)
        + "\n"
    )
    with (out / "summary.tsv").open("w") as stream:
        stream.write(
            "family\tstub\twindow\tstatus\textra_candidates\tbytes\tholds\tcurrent_extents\t"
            "source_valid\trelocation_valid\tcontract_valid\trelocation_words\tdirect_calls\thold_reasons\n"
        )
        for item in reports:
            stream.write(
                "%s\t%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%s\n"
                % (
                    item["family"],
                    item["stub"],
                    item["window"],
                    item["status"],
                    item["extra_candidate_count"],
                    item["candidate_bytes"],
                    item["hold_count"],
                    item["current_extent_count"],
                    item["proof"]["source_valid"],
                    item["proof"]["relocation_valid"],
                    item["proof"]["contract_valid"],
                    item["proof"]["relocation_words"],
                    item["proof"]["direct_calls"],
                    json.dumps(item["hold_reasons"], sort_keys=True),
                )
            )
    return totals, reports


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("families", nargs="*", help="specific bank-family IDs")
    parser.add_argument("--all", action="store_true", help="quantify all bank families")
    args = parser.parse_args(argv)
    run(None if args.all or not args.families else args.families)


if __name__ == "__main__":
    main()
