"""Recover conservative bank-anchor rows through the normal runner gates.

The planner in :mod:`single_plan` can find complete bodies in a bank without
using the preceding 0x6000 bank.  This wrapper is deliberately transaction
oriented: its default mode is a read-only census/count pass, while ``--apply``
is refused until the parallel bank and single-window queues have stopped.  An
apply run calls the existing ``twins.run`` for one-bank stubs, merges the
result into the original family's bank record, and archives the temporary
stub result below ``evidence/anchor_transactions``.

The wrapper does not alter ``twins.py`` or any shared runner.  It sets
``TWINS_NO_PACKAGE=1`` so the normal package hook is disabled during each
transaction, then re-emits the cumulative package after every four admitting
parent families and once at the end.
"""

import argparse
import copy
import json
import os
import shutil
import subprocess
import sys
from datetime import datetime, timezone
from pathlib import Path

# Keep this guard before importing twins: twins reads these at module import.
os.environ["TWINS_NO_PACKAGE"] = "1"
try:
    os.environ["TWINS_WORKERS"] = str(min(6, int(os.environ.get("TWINS_WORKERS", "6"))))
except ValueError:
    os.environ["TWINS_WORKERS"] = "6"

MAIN_SCRIPTS = Path(__file__).resolve().parent
sys.path.insert(0, str(MAIN_SCRIPTS))

import bank_anchor_plan  # noqa: E402
import single_plan  # noqa: E402
from twins import L, R, PY, World, jl, load_families, command, run as twins_run  # noqa: E402


ARCHIVE_ROOT = L / "evidence" / "anchor_transactions"
SINGLE_ROOT = L / "evidence" / "single_plans"


def now():
    return datetime.now(timezone.utc).isoformat()


def json_load(path, fallback):
    if not path.is_file():
        return copy.deepcopy(fallback)
    return json.loads(path.read_text())


def json_write(path, value):
    """Write one small transaction document atomically."""

    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    temporary = path.with_name(path.name + ".anchor-tmp")
    temporary.write_text(json.dumps(value, indent=1) + "\n")
    temporary.replace(path)


def refresh_world_splits(world):
    """Use the current staging split ledgers for this in-memory World."""

    for container in world.B:
        path = R / "ledger" / "splits" / (container + ".jsonl")
        world.splits[container] = jl(path)
    return world


def current_extents(world):
    """Return live extents after replacing BASE split views with staging."""

    refresh_world_splits(world)
    return {
        container: list(single_plan.existing_extents(world, container))
        for container in world.B
    }


def make_stub(family, bank):
    """Build the stable one-bank transaction identity requested by the runner."""

    start = bank_anchor_plan.as_int(bank["start"])
    stub = dict(family)
    stub["id"] = "%s__anchor_%s" % (family["id"], hex(start))
    stub["kind"] = "single-window"
    stub["source_family"] = family["id"]
    stub["banks"] = [dict(bank)]
    return stub


def family_result(family_id):
    return L / "evidence" / family_id / "result.json"


def family_bank_record(family_id, window):
    value = json_load(family_result(family_id), {})
    for bank in value.get("banks", []):
        if bank.get("window") == window:
            return bank, value
    return None, value


def bank_is_eligible(family, bank):
    """Allow gap recovery in every bank; live extents protect accepted rows."""
    return True


def eligible_stubs(families, limit=None):
    out = []
    for family in families:
        if family.get("kind") not in ("bank-family", "single-window"):
            continue
        for bank in family["banks"]:
            if bank_is_eligible(family, bank):
                out.append((family, bank, make_stub(family, bank)))
                if limit is not None and len(out) >= limit:
                    return out
    return out


def proof_report(rows, holds):
    return {
        "candidates": len(rows),
        "bytes": sum(int(row.get("size", 0)) for row in rows),
        "holds": len(holds),
        "source_valid": sum(bool(row.get("src") and row.get("source_sha256")) for row in rows),
        "relocation_valid": sum(row.get("relocation_proof") is not None for row in rows),
        "contract_valid": sum(
            all(call.get("contract") and call.get("target_body_proof") for call in row.get("contracts", []))
            for row in rows
        ),
    }


def dry_run(stubs, world, occupied):
    reports = []
    for family, bank, stub in stubs:
        rows, holds = single_plan.runner_plan(
            stub,
            world,
            occupied=occupied.get(bank["container"], ()),
        )
        item = {
            "family": family["id"],
            "stub": stub["id"],
            "window": bank["window"],
            "container": bank["container"],
            "start": int(bank["start"]),
            "proof": proof_report(rows, holds),
            "hold_reasons": sorted({hold.get("reason", "unknown") for hold in holds}),
            "read_only": True,
        }
        reports.append(item)
        print(
            "%s candidates=%d bytes=%d holds=%d"
            % (stub["id"], item["proof"]["candidates"], item["proof"]["bytes"], item["proof"]["holds"]),
            flush=True,
        )
    totals = {
        "eligible_banks": len(reports),
        "candidates": sum(item["proof"]["candidates"] for item in reports),
        "bytes": sum(item["proof"]["bytes"] for item in reports),
        "holds": sum(item["proof"]["holds"] for item in reports),
        "read_only": True,
    }
    print("DRY-RUN " + json.dumps(totals, sort_keys=True), flush=True)
    return totals, reports


def process_argv():
    """Return command lines that identify active queue owners."""

    found = []
    proc = Path("/proc")
    for item in proc.iterdir():
        if not item.name.isdigit():
            continue
        try:
            argv = [arg.decode(errors='replace') for arg in (item / 'cmdline').read_bytes().split(b'\0') if arg]
            raw = ' '.join(argv)
        except (OSError, ValueError):
            continue
        if not raw or str(os.getpid()) == item.name:
            continue
        names = {Path(arg).name for arg in argv
                 if arg.startswith(str(L / 'scripts') + '/') or arg.startswith('scripts/')}
        owner = bool(names & {'parallel.py', 'after_banks.py', 'recover_bank_anchors.py',
                              'recover_extra_plans.py', 'recover_short_aspsx.py', 'final_shared_windows.py'})
        owner = owner or ('twins.py' in names and 'run' in argv)
        if owner:
            try:
                here = (item / 'cwd').resolve()
            except OSError:
                continue
            if here == L or L in here.parents:
                found.append((int(item.name), raw.strip()))
    return found


def require_quiescent():
    active = process_argv()
    if active:
        lines = "\n".join("pid=%d %s" % item for item in active[:12])
        raise RuntimeError("refusing --apply while runner queues are active:\n" + lines)


def row_key(row):
    return (
        row.get("id"),
        bank_anchor_plan.as_int(row.get("foff", -1)),
        bank_anchor_plan.as_int(row.get("size", 0)),
    )


def unique_append(items, additions):
    seen = {json.dumps(value, sort_keys=True) for value in items}
    for value in additions:
        marker = json.dumps(value, sort_keys=True)
        if marker not in seen:
            items.append(copy.deepcopy(value))
            seen.add(marker)


def merge_bank_record(original, transaction, stub_id):
    """Merge one stub bank without replacing a pre-existing accepted row."""

    merged = copy.deepcopy(original) if original else {"window": transaction.get("window"), "rows": []}
    old_rows = list(merged.get("rows", []))
    by_key = {row_key(row): row for row in old_rows}
    added = []
    conflicts = []
    for row in transaction.get("rows", []):
        key = row_key(row)
        if key in by_key:
            old_hash = by_key[key].get("source_sha256")
            new_hash = row.get("source_sha256")
            if old_hash and new_hash and old_hash != new_hash:
                conflicts.append({"id": row.get("id"), "old": old_hash, "new": new_hash})
            continue
        merged.setdefault("rows", []).append(copy.deepcopy(row))
        by_key[key] = row
        added.append(row)

    if transaction.get("status") == "MATCH":
        assert all(g.get("ok") for g in transaction.get("gates", []))
        refreshed = {gate['window'] for gate in transaction.get('gates', [])}
        superseded = [gate for gate in merged.get('gates', [])
                      if not gate.get('ok') and gate['window'] in refreshed]
        if superseded:
            merged.setdefault('superseded_failed_gates', [])
            unique_append(merged['superseded_failed_gates'], superseded)
            merged['gates'] = [gate for gate in merged.get('gates', []) if gate not in superseded]
        for field in ("gates", "promotions"):
            merged.setdefault(field, [])
            unique_append(merged[field], transaction.get(field, []))
    merged.setdefault("anchor_transactions", [])
    if not any(item.get("stub") == stub_id for item in merged["anchor_transactions"]):
        merged["anchor_transactions"].append(
            {
                "stub": stub_id,
                "merged_at": now(),
                "status": transaction.get("status"),
                "added_rows": [row.get("id") for row in added],
                "conflicts": conflicts,
            }
        )
    if added and transaction.get("status") == "MATCH":
        merged["status"] = "MATCH"
        merged.pop("reason", None)
    return merged, added, conflicts


def merge_document(original, transaction, family_id, stub_id):
    """Pure merge used for result.json and checkpoint fixtures/documents."""

    if isinstance(original, list):
        holder = {"family": family_id, "banks": copy.deepcopy(original), "holds": []}
        merged, additions, conflicts = merge_document(holder, transaction, family_id, stub_id)
        return merged["banks"], additions, conflicts

    merged = copy.deepcopy(original) if original else {"family": family_id, "banks": [], "holds": []}
    merged["family"] = family_id
    transaction_banks = transaction.get("banks", [])
    if not transaction_banks:
        return merged, [], []
    transaction_bank = transaction_banks[0]
    window = transaction_bank.get("window")
    target = next((bank for bank in merged["banks"] if bank.get("window") == window), None)
    if target is None:
        target = {"window": window, "rows": []}
        merged["banks"].append(target)
    merged_bank, additions, conflicts = merge_bank_record(target, transaction_bank, stub_id)
    target.clear()
    target.update(merged_bank)
    annotated_holds = []
    if transaction_bank.get("status") != "MATCH":
        annotated_holds.append({"window": window, "anchor_stub": stub_id,
            "reason": "bank-anchor attempt held: " + transaction_bank.get("reason", "no admitted source/raw pair")})
    for hold in transaction.get("holds", []):
        item = copy.deepcopy(hold)
        item.setdefault("window", window)
        item["anchor_stub"] = stub_id
        item["anchor_family"] = family_id
        annotated_holds.append(item)
    for conflict in conflicts:
        annotated_holds.append(
            {
                "window": window,
                "reason": "anchor_row_hash_conflict_kept_existing",
                "anchor_stub": stub_id,
                "detail": conflict,
            }
        )
    merged.setdefault("holds", [])
    unique_append(merged["holds"], annotated_holds)
    return merged, additions, conflicts


def merge_family(family, stub, transaction):
    """Merge a completed stub transaction into result/checkpoint/holds."""

    family_dir = L / "evidence" / family["id"]
    result_path = family_dir / "result.json"
    checkpoint_path = family_dir / "checkpoint.json"
    checkpoint_seed = json_load(checkpoint_path, [])
    if isinstance(checkpoint_seed, dict):
        checkpoint_seed = checkpoint_seed.get("banks", [])
    result = json_load(
        result_path,
        {"family": family["id"], "banks": copy.deepcopy(checkpoint_seed), "holds": []},
    )
    merged_result, added, conflicts = merge_document(result, transaction, family["id"], stub["id"])
    json_write(result_path, merged_result)

    checkpoint = json_load(checkpoint_path, merged_result.get("banks", []))
    merged_checkpoint, _, _ = merge_document(checkpoint, transaction, family["id"], stub["id"])
    json_write(checkpoint_path, merged_checkpoint)

    holds_path = family_dir / "holds.json"
    holds = json_load(holds_path, [])
    transaction_holds = []
    for hold in transaction.get("holds", []):
        item = copy.deepcopy(hold)
        item.setdefault("window", stub["banks"][0]["window"])
        item["anchor_stub"] = stub["id"]
        transaction_holds.append(item)
    for conflict in conflicts:
        transaction_holds.append(
            {
                "window": stub["banks"][0]["window"],
                "reason": "anchor_row_hash_conflict_kept_existing",
                "anchor_stub": stub["id"],
                "detail": conflict,
            }
        )
    unique_append(holds, transaction_holds)
    json_write(holds_path, holds)
    return added, conflicts


def archive_stub(stub_id):
    source = L / "evidence" / stub_id
    target = ARCHIVE_ROOT / stub_id
    target.parent.mkdir(parents=True, exist_ok=True)
    if source.is_dir():
        if target.exists():
            shutil.copytree(source, target, dirs_exist_ok=True)
            shutil.rmtree(source)
        else:
            source.rename(target)
    return target


def transaction_result_path(stub_id):
    active = L / "evidence" / stub_id / "result.json"
    archived = ARCHIVE_ROOT / stub_id / "result.json"
    if active.is_file():
        return active
    if archived.is_file():
        return archived
    return None


def load_transaction_result(path):
    """Recover a truncated single-bank result from its completed checkpoint."""
    path = Path(path)
    try:
        return json.loads(path.read_text())
    except json.JSONDecodeError:
        checkpoint = json.loads(path.with_name('checkpoint.json').read_text())
        assert isinstance(checkpoint, list) and len(checkpoint) == 1
        bank = checkpoint[0]
        assert bank['status'] in ('MATCH', 'HOLD') and isinstance(bank['rows'], list)
        if bank['status'] == 'MATCH':
            assert bank['rows'] and bank['gates'] and all(g['ok'] for g in bank['gates'])
            for row in bank['rows']:
                for sub, field in [('src', 'source_sha256'), ('raw', 'raw_sha256')]:
                    import hashlib
                    source = R / sub / row['container'] / (row['func'] + '.c')
                    assert hashlib.sha256(source.read_bytes()).hexdigest() == row[field]
        holds = json.loads(path.with_name('holds.json').read_text())
        restored = dict(family=path.parent.name, banks=checkpoint, holds=holds)
        path.replace(path.with_name('result.corrupt.json'))
        json_write(path, restored)
        return restored


def refresh_derived(stub_id):
    """Finish normal derivation if an interruption followed result emission."""
    directory = ARCHIVE_ROOT / stub_id
    directory.mkdir(parents=True, exist_ok=True)
    for args in [[PY, 'tools/row_db.py', 'export', 'build_ovl'],
                 [PY, 'tools/registry.py'],
                 [PY, 'tools/gate/overlay_module_gate.py', '--root', '.', '--graph'],
                 [PY, 'tools/row_db.py', 'check']]:
        process = command(args, log=directory / ('resume_' + Path(args[1]).stem + '.log'))
        assert process.returncode == 0, process.stdout + process.stderr


def package_cumulative(index):
    log = ARCHIVE_ROOT / ("package_%03d.log" % index)
    log.parent.mkdir(parents=True, exist_ok=True)
    env = os.environ.copy()
    env["TWINS_NO_PACKAGE"] = "1"
    process = subprocess.run(
        [str(PY), str(L / "scripts" / "package.py")],
        cwd=L,
        env=env,
        capture_output=True,
        text=True,
        timeout=3600,
    )
    log.write_text(process.stdout + process.stderr)
    if process.returncode:
        raise RuntimeError("cumulative package failed; see " + str(log))
    return log


def transaction_report(family, bank, stub, transaction, added, conflicts, archive):
    return {
        "family": family["id"],
        "stub": stub["id"],
        "window": bank["window"],
        "added_rows": len(added),
        "conflicts": len(conflicts),
        "archive": str(archive.relative_to(L)),
        "status": transaction.get("banks", [{}])[0].get("status"),
    }


def reconcile_active(families):
    """Finish an interrupted merge before selecting new eligible banks."""

    by_id = {family["id"]: family for family in families}
    reports = []
    evidence_root = L / "evidence"
    for directory in evidence_root.iterdir():
        if not directory.is_dir() or "__anchor_" not in directory.name or "__anchor_extra_" in directory.name:
            continue
        result_path = directory / "result.json"
        if not result_path.is_file():
            continue
        family_id = directory.name.split("__anchor_", 1)[0]
        family = by_id.get(family_id)
        if family is None:
            continue
        transaction = load_transaction_result(result_path)
        window = transaction.get("banks", [{}])[0].get("window")
        bank = next((item for item in family["banks"] if item.get("window") == window), None)
        if bank is None:
            continue
        stub = make_stub(family, bank)
        added, conflicts = merge_family(family, stub, transaction)
        archive = archive_stub(stub["id"])
        refresh_derived(stub['id'])
        reports.append(transaction_report(family, bank, stub, transaction, added, conflicts, archive))
    return reports


def apply(families, limit, world):
    require_quiescent()
    os.environ["TWINS_NO_PACKAGE"] = "1"
    os.environ["TWINS_WORKERS"] = str(min(6, int(os.environ.get("TWINS_WORKERS", "6"))))
    reports = reconcile_active(families)
    admitted_family_ids = {item["family"] for item in reports if item["added_rows"]}
    next_package_family_count = 4
    package_index = 0
    while len(admitted_family_ids) >= next_package_family_count:
        package_index += 1
        package_cumulative(package_index)
        next_package_family_count += 4
    stubs = eligible_stubs(families, limit)
    for family, bank, stub in stubs:
        # An interrupted transaction may have been reconciled above, making
        # this bank no longer eligible in the same invocation.
        if not bank_is_eligible(family, bank):
            continue
        # Re-read current splits before every transaction.  A row admitted by
        # an earlier transaction or resumed process is therefore filtered by
        # the normal live split check before the stub can append it.
        refresh_world_splits(world)
        stub_result_path = transaction_result_path(stub["id"])
        if stub_result_path is None:
            planned, holds = single_plan.runner_plan(stub, world)
            if not planned:
                print("NO EXTRA CANDIDATE " + stub["id"], flush=True)
                continue
            print("RUN " + stub["id"], flush=True)
            twins_run(stub, world)
            stub_result_path = transaction_result_path(stub["id"])
        else:
            print("RESUME-ARCHIVED " + stub["id"], flush=True)
            refresh_derived(stub['id'])
        if stub_result_path is None:
            raise RuntimeError("twins.run produced no result: " + stub["id"])
        transaction = load_transaction_result(stub_result_path)
        added, conflicts = merge_family(family, stub, transaction)
        archive = archive_stub(stub["id"])
        report = transaction_report(family, bank, stub, transaction, added, conflicts, archive)
        reports.append(report)
        print("MERGED " + json.dumps(report, sort_keys=True), flush=True)
        if added:
            admitted_family_ids.add(family["id"])
            if len(admitted_family_ids) >= next_package_family_count:
                package_index += 1
                package_cumulative(package_index)
                next_package_family_count += 4
    json_write(
        ARCHIVE_ROOT / "apply_summary.json",
        {
            "schema": "azure-clean.bank-anchor-recovery.v1",
            "finished_at": now(),
            "families": len({item["family"] for item in reports}),
            "transactions": len(reports),
            "admitted_families": len(admitted_family_ids),
            "added_rows": sum(item["added_rows"] for item in reports),
            "reports": reports,
            "read_only": False,
        },
    )
    package_index += 1
    package_cumulative(package_index)
    return reports


def self_test():
    old = {
        "family": "fixture",
        "banks": [{"window": "w", "status": "HOLD", "rows": [{"id": "old", "foff": 4, "size": 4, "source_sha256": "a"}]}],
        "holds": [],
    }
    tx = {
        "banks": [{"window": "w", "status": "MATCH", "rows": [{"id": "new", "foff": 8, "size": 4, "source_sha256": "b"}], "gates": [{"window": "w", "ok": True}], "promotions": [{"ok": True}]}],
        "holds": [{"window": "w", "reason": "fixture-hold"}],
    }
    merged, added, conflicts = merge_document(old, tx, "fixture", "fixture__anchor_0x0")
    assert len(added) == 1 and not conflicts
    assert merged["banks"][0]["status"] == "MATCH"
    assert {row["id"] for row in merged["banks"][0]["rows"]} == {"old", "new"}
    assert merged["banks"][0]["gates"] and merged["banks"][0]["promotions"]
    merged_again, added_again, conflicts_again = merge_document(merged, tx, "fixture", "fixture__anchor_0x0")
    assert not added_again and not conflicts_again
    assert len(merged_again["banks"][0]["rows"]) == 2
    checkpoint, checkpoint_added, checkpoint_conflicts = merge_document(
        old["banks"], tx, "fixture", "fixture__anchor_0x0"
    )
    assert len(checkpoint) == 1 and len(checkpoint[0]["rows"]) == 2
    assert checkpoint_added and not checkpoint_conflicts
    held = {"banks": [{"window": "w", "status": "HOLD", "rows": [],
        "reason": "production window gate failed", "gates": [{"ok": False}]}], "holds": []}
    preserved, held_additions, _ = merge_document(merged, held, "fixture", "fixture__anchor_held")
    assert not held_additions and preserved["banks"][0]["status"] == "MATCH"
    assert all(g["ok"] for g in preserved["banks"][0]["gates"])
    assert any("production window gate failed" in h["reason"] for h in preserved["holds"])
    failed_original = {"family": "fixture", "banks": [{"window": "w", "status": "HOLD", "rows": [],
        "gates": [{"window": "w", "ok": False}], "reason": "old production gate failed"}], "holds": []}
    successful_retry = copy.deepcopy(tx)
    successful_retry['banks'][0]['gates'] = [{'window': 'w', 'ok': True}]
    repaired, retry_rows, _ = merge_document(failed_original, successful_retry, 'fixture', 'fixture__anchor_retry')
    assert retry_rows and repaired['banks'][0]['status'] == 'MATCH'
    assert all(g['ok'] for g in repaired['banks'][0]['gates'])
    assert repaired['banks'][0]['superseded_failed_gates'] == [{'window': 'w', 'ok': False}]
    print("self-test merge idempotence: PASS")


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("families", nargs="*", help="optional original bank-family IDs")
    parser.add_argument("--dry-run", action="store_true", help="read-only plan/count mode")
    parser.add_argument("--apply", action="store_true", help="run normal production gates after queues are idle")
    parser.add_argument("--limit", type=int, default=None, help="limit eligible banks for a dry-run or test")
    parser.add_argument("--kind", choices=["bank-family", "single-window", "all"], default="bank-family")
    parser.add_argument("--self-test", action="store_true", help="run in-memory merge assertions")
    args = parser.parse_args(argv)
    if args.self_test:
        self_test()
        return
    if args.apply and args.dry_run:
        parser.error("choose --apply or --dry-run")
    if not args.apply:
        args.dry_run = True
    families = [family for family in load_families() if args.kind == "all" or family.get("kind") == args.kind]
    by_id = {family["id"]: family for family in families}
    if args.families:
        missing = [name for name in args.families if name not in by_id]
        if missing:
            parser.error("unknown bank family: " + ", ".join(missing))
        families = [by_id[name] for name in args.families]
    stubs = eligible_stubs(families, args.limit)
    world = refresh_world_splits(World())
    occupied = current_extents(world)
    if args.dry_run:
        dry_run(stubs, world, occupied)
    else:
        apply(families, args.limit, world)


if __name__ == "__main__":
    main()
