#!/usr/bin/env python3
"""Land one overlay C function, platform-library assembly twin, or hand-written
game assembly source through the standalone overlay gate.

The script first stages the candidate through tools/overlay_local_gate.py without
editing tracked overlay files.  Only after that staged window compare passes does
it copies the C file into first_pass_matched/ (or records the existing canonical
asm/psyq or asm/nonmatchings source), updates the selected result row to MATCH,
and reruns the gate from the persisted files.

The two assembly routes are symmetric and equally fail-closed: each accepts an
in-tree ``.s`` under its own directory boundary
(tools/overlay_local_gate.ASM_SOURCE_ROOTS), stages it through the same
whole-window byte compare as a C candidate, and only then flips row metadata.
Neither ever copies a source into first_pass_matched/ -- the in-tree file IS the
landed source, and the row records its path.  Read the DURABILITY REQUIREMENT
note beside ASM_SOURCE_ROOTS before landing anything through them: all of
``asm/`` is gitignored and regenerated, so only a source something regenerates
from the disc may be referenced by a tracked row.
"""

from __future__ import annotations

import argparse
import fcntl
import hashlib
import json
import os
import re
import subprocess
import sys
import tempfile
import time
from pathlib import Path
from typing import Any, Callable

import yaml

sys.path.insert(0, str(Path(__file__).resolve().parent))
from overlay_evidence import family_for  # noqa: E402
import live_truth  # noqa: E402
import portability_lint  # noqa: E402
import decomp_audit_ratchet  # noqa: E402
import rowbase_naming_debt  # noqa: E402
from overlay_local_gate import (  # noqa: E402
    ASM_SOURCE_ROOTS, validate_asm_source)


ROOT = Path(__file__).resolve().parents[1]
DEFAULT_CONFIG = ROOT / "config/overlays/dungeon_engine.overlay.yaml"
GATE = ROOT / "tools/overlay_local_gate.py"


def rel(path: Path) -> str:
    try:
        return str(path.relative_to(ROOT))
    except ValueError:
        return str(path)


def cfg_path(raw: str | Path) -> Path:
    p = Path(raw)
    return p if p.is_absolute() else ROOT / p


def load_json_list(path: Path) -> list[dict[str, Any]]:
    with path.open() as f:
        data = json.load(f)
    if not isinstance(data, list):
        raise SystemExit(f"{rel(path)} must contain a JSON list")
    return data


def dump_json_list(path: Path, rows: list[dict[str, Any]]) -> None:
    _atomic_write(path, (json.dumps(rows, indent=1) + "\n").encode())


def _atomic_write(path: Path, data: bytes) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    fd, temp_name = tempfile.mkstemp(prefix=f".{path.name}.", suffix=".tmp", dir=path.parent)
    temp = Path(temp_name)
    try:
        mode = (path.stat().st_mode & 0o777) if path.exists() else 0o664
        os.fchmod(fd, mode)
        with os.fdopen(fd, "wb") as out:
            out.write(data)
            out.flush()
            os.fsync(out.fileno())
        os.replace(temp, path)
        try:
            dir_fd = os.open(path.parent, os.O_RDONLY)
            try:
                os.fsync(dir_fd)
            finally:
                os.close(dir_fd)
        except OSError:
            pass
    finally:
        temp.unlink(missing_ok=True)


def _durable_unlink(path: Path) -> None:
    path.unlink(missing_ok=True)
    try:
        dir_fd = os.open(path.parent, os.O_RDONLY)
        try:
            os.fsync(dir_fd)
        finally:
            os.close(dir_fd)
    except OSError:
        pass


def run_gate(args: list[str]) -> str:
    cmd = ["nice", "-n", "10", sys.executable, str(GATE), *args]
    proc = subprocess.run(cmd, cwd=ROOT, text=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    if proc.returncode != 0:
        raise RuntimeError("command failed: " + " ".join(cmd) + "\n" + proc.stdout)
    return proc.stdout


def refuse_keyed_config(func: str, config: Any, *, overlay: str | None = None,
                        row: dict[str, Any] | None = None,
                        as_flags: str | None = None) -> None:
    """Refuse a landing that needs a PER-FUNCTION KEYED configuration.

    Three legs, one rule (live_truth.keyed_of): a non-stock compiler directory
    or a ``-fretail-``/``-fsn-``/``-fdriver-`` compiler flag; a ``--retail-*``
    maspsx dial resolved for this row from
    ``config/overlays/<family>.as_flags.jsonl`` (or an explicit ``as_flags``
    the caller already resolved); or the row being in the measured set of maspsx
    function-name-TABLE dependents.  Workstream C measured the assembler legs on
    2026-09-05: 47 of 49 dialled rows and 7 table-dependent rows stop being
    exact when the name-keyed layer is removed
    (work/bridge_remediation_20260905/C_maspsx_nameblind/RESULTS.md §2, §5).

    ``config`` is the COMPILER cell being landed (``--match-config`` overrides
    the row's own), which is why it is passed separately from ``row``.
    """
    probe = dict(row or {})
    probe["func_vram"] = probe.get("func_vram") or func
    probe["config"] = config
    keyed = live_truth.keyed_of(probe, overlay=overlay, as_flags=as_flags)
    if keyed is None:
        return
    message = live_truth.keyed_refusal_message(
        keyed, func=func, tool="tools/overlay_land_function.py")
    if not live_truth.bridge_landing_override_active():
        raise SystemExit(message)
    print(f"WARNING: AZURE_ALLOW_BRIDGE_LANDING=1 admitted a keyed landing. "
          f"{message}", file=sys.stderr)


def refuse_bridge_config(func: str, config: Any) -> None:
    """Compiler-leg-only entry point (kept for callers that hold no row).

    The ratchet half of the bridge remediation (Phase 0a,
    work/bridge_remediation_20260905/REPORT.md).  79 DUNGEON rows are byte-exact
    only because their config names a ``toolchain/compilers/gcc-<base>-<vram>-
    <tag>`` directory whose ``gcc`` is a Python wrapper that text-edits the
    emitted assembly, or a cc1 rebuilt with a ``strcmp`` on the function name.
    Nothing in the gate can see that: the staged window compare is byte-exact
    either way, which is precisely why this class grew to 79 unremarked.

    Placement matters as much as the check.  Like the portability and fidelity
    refusals it sits AFTER every mutable input has been re-resolved inside the
    critical section and BEFORE the first file, journal or backup write, so a
    refusal leaves nothing to roll back.

    ONE escape hatch, ``AZURE_ALLOW_BRIDGE_LANDING=1``, for a sanctioned re-land
    of an already-grandfathered row (config/bridge_burndown/baseline.json).  It
    is loud on stderr and never silent — the 09-01 fidelity-override postmortem
    is the reason: an override nothing records is an override nothing learns
    from.  There is no flag, no config key and no per-call argument.
    """
    if live_truth.bridge_of(config) is None:
        return
    message = live_truth.bridge_refusal_message(
        config, func=func, tool="tools/overlay_land_function.py")
    if not live_truth.bridge_landing_override_active():
        raise SystemExit(message)
    print(f"WARNING: AZURE_ALLOW_BRIDGE_LANDING=1 admitted a bridged landing. "
          f"{message}", file=sys.stderr)


def regenerate_census(family: str) -> None:
    subprocess.run(
        [sys.executable, str(ROOT / "tools/gen_noreturn_syms.py"),
         "--container", family],
        cwd=ROOT, check=True, stdout=subprocess.DEVNULL)


def landing_lock_path(overlay: str) -> Path:
    if not re.fullmatch(r"[A-Za-z0-9_]+", overlay):
        raise SystemExit(f"invalid overlay lock identity: {overlay!r}")
    return ROOT / "work" / "overlay_landing_locks" / f"{overlay}.lock"


def family_lock_path(family: str) -> Path:
    if not re.fullmatch(r"[A-Za-z0-9_]+", family):
        raise SystemExit(f"invalid family lock identity: {family!r}")
    return ROOT / "work" / "overlay_landing_locks" / f"family-{family}.lock"


class LandingRollbackError(RuntimeError):
    pass


def _file_state(path: Path) -> str:
    if not path.exists():
        return "absent"
    if not path.is_file():
        return "non-file"
    return hashlib.sha256(path.read_bytes()).hexdigest()


def _state_sha(state: dict[str, str]) -> str:
    raw = json.dumps(state, sort_keys=True, separators=(",", ":")).encode()
    return hashlib.sha256(raw).hexdigest()


def _landing_transaction_dir(family: str) -> Path:
    return ROOT / "work" / "overlay_landing_transactions" / family


def _write_landing_journal(path: Path, journal: dict[str, Any]) -> None:
    _atomic_write(path, (json.dumps(journal, indent=1, sort_keys=True) + "\n").encode())


def _transition_landing_journal(path: Path, journal: dict[str, Any],
                                state: str, **extra: Any) -> None:
    journal.update(extra)
    journal["state"] = state
    journal.setdefault("history", []).append({
        "state": state, "at": time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime())})
    _write_landing_journal(path, journal)


def _backup_bytes(txndir: Path, data: bytes) -> tuple[str, str]:
    sha = hashlib.sha256(data).hexdigest()
    path = txndir / "backups" / f"{sha}.bin"
    if path.exists():
        if path.read_bytes() != data:
            raise RuntimeError(f"landing backup collision: {path}")
    else:
        _atomic_write(path, data)
    return sha, str(path)


def _prepare_landing_journal(*, family: str, overlay: str, func: str,
                             config_path: Path, dest: Path, results_path: Path,
                             census: Path, candidate_bytes: bytes,
                             intended_results: bytes,
                             staged_output: str,
                             sources: list[tuple[str, Path, bytes]] | None = None,
                             ) -> tuple[Path, dict[str, Any]]:
    """Journal one landing transaction.

    ``sources`` (batch landings, 2026-08-22) carries (func, dest, bytes) for
    EVERY source the transaction writes; the single-source call omits it and
    the journal keeps its historical ``paths.source`` key byte-for-byte.  The
    recovery paths iterate ``paths``/``original``/``intended`` generically, so
    an N-source journal rolls back and completes exactly like a 1-source one.
    """
    txndir = _landing_transaction_dir(family)
    txndir.mkdir(parents=True, exist_ok=True)
    if sources is None:
        source_paths = {"source": dest}
        source_intended = {"source": hashlib.sha256(candidate_bytes).hexdigest()}
        funcs = [func]
    else:
        if not sources:
            raise RuntimeError("batch landing journal with no sources")
        source_paths = {}
        source_intended = {}
        funcs = []
        for item_func, item_dest, item_bytes in sources:
            key = f"source::{item_func}"
            if key in source_paths:
                raise RuntimeError(f"duplicate source in landing batch: {item_func}")
            source_paths[key] = item_dest
            source_intended[key] = hashlib.sha256(item_bytes).hexdigest()
            funcs.append(item_func)
    paths = {**source_paths, "results": results_path, "census": census}
    original: dict[str, str] = {}
    backups: dict[str, str | None] = {}
    for name, path in paths.items():
        if path.is_file():
            original[name], backups[name] = _backup_bytes(txndir, path.read_bytes())
        elif path.exists():
            raise RuntimeError(f"landing target is not a regular file: {path}")
        else:
            original[name], backups[name] = "absent", None
    intended = {
        **source_intended,
        "results": hashlib.sha256(intended_results).hexdigest(),
        "census": None,
    }
    txid = f"{overlay}.{func}.{time.time_ns()}.{os.getpid()}"
    journal = {
        "schema": "overlay_landing_transaction/1",
        "transaction_id": txid, "state": "prepared",
        "family": family, "overlay": overlay, "func": func, "funcs": funcs,
        "config_path": str(config_path.resolve()),
        "config_sha256": _file_state(config_path),
        "paths": {name: str(path.resolve()) for name, path in paths.items()},
        "original": original, "backups": backups, "intended": intended,
        "staged_output": staged_output,
        "created_at": time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime()),
        "history": [{"state": "prepared"}],
    }
    path = txndir / f"{txid}.json"
    _write_landing_journal(path, journal)
    return path, journal


def _load_landing_journal(path: Path) -> dict[str, Any]:
    try:
        journal = json.loads(path.read_text(encoding="utf-8"))
    except (OSError, ValueError) as exc:
        raise RuntimeError(f"unreadable landing journal {path}: {exc}; manual artifact: {path}") from exc
    if journal.get("schema") != "overlay_landing_transaction/1":
        raise RuntimeError(f"unknown landing journal schema; manual artifact: {path}")
    return journal


def _current_landing_state(journal: dict[str, Any]) -> dict[str, str]:
    state = {name: _file_state(Path(path)) for name, path in journal["paths"].items()}
    state["config"] = _file_state(Path(journal["config_path"]))
    return state


def _landing_manual_command(path: Path, state_sha: str, strategy: str = "rollback") -> str:
    return (f"python3 tools/overlay_land_function.py --recover-journal {path} "
            f"--strategy {strategy} --expect-current-state-sha {state_sha}")


def _block_landing_recovery(path: Path, journal: dict[str, Any], message: str) -> None:
    current = _current_landing_state(journal)
    digest = _state_sha(current)
    command = _landing_manual_command(path, digest)
    _transition_landing_journal(
        path, journal, "recovery_blocked", recovery_error=message,
        observed_state=current, observed_state_sha256=digest,
        manual_recovery_command=command)
    raise RuntimeError(f"{message}; family landing blocked. Manual recovery: {command}")


def _restore_landing(path: Path, journal: dict[str, Any], *,
                     gate_runner: Callable[[list[str]], str]) -> dict[str, Any]:
    for name, raw_path in journal["paths"].items():
        target = Path(raw_path)
        expected = journal["original"][name]
        if expected == "absent":
            _durable_unlink(target)
            if target.exists():
                raise LandingRollbackError(f"failed to restore absent {name}: {target}")
            continue
        backup = Path(journal["backups"][name])
        data = backup.read_bytes()
        if hashlib.sha256(data).hexdigest() != expected:
            raise LandingRollbackError(f"landing backup hash mismatch: {backup}")
        _atomic_write(target, data)
    current = _current_landing_state(journal)
    expected_state = {**journal["original"], "config": journal["config_sha256"]}
    if current != expected_state:
        raise LandingRollbackError(
            f"restored landing state mismatch: expected {expected_state}, got {current}")
    gate_runner(["--config", journal["config_path"], "--clean"])
    _transition_landing_journal(path, journal, "rolled_back",
                                recovery={"baseline_proven": True})
    return {"state": "rolled_back", "baseline_proven": True}


def _complete_landing(path: Path, journal: dict[str, Any], *,
                      gate_runner: Callable[[list[str]], str]) -> dict[str, Any]:
    intended = journal["intended"]
    if not intended.get("census"):
        raise RuntimeError("journal has no intended census identity")
    expected = {**intended, "config": journal["config_sha256"]}
    if _current_landing_state(journal) != expected:
        raise RuntimeError("persisted state is not the exact intended landing state")
    persisted_output = gate_runner(["--config", journal["config_path"], "--clean"])
    if _current_landing_state(journal) != expected:
        raise RuntimeError("persisted state changed during recovery proof")
    _transition_landing_journal(
        path, journal, "committed",
        recovery={"global_proven": True,
                  "persisted_output": persisted_output})
    return {"state": "committed", "global_proven": True,
            "persisted_output": persisted_output}


def _recover_landing_one(path: Path, journal: dict[str, Any], *,
                         gate_runner: Callable[[list[str]], str]) -> dict[str, Any]:
    if journal.get("state") in ("committed", "rolled_back"):
        return {"state": journal["state"]}
    if journal.get("state") == "recovery_blocked":
        command = journal.get("manual_recovery_command")
        raise RuntimeError(f"blocked family landing journal {path}; manual recovery: {command}")
    current = _current_landing_state(journal)
    if current["config"] != journal.get("config_sha256"):
        _block_landing_recovery(path, journal, "gate config changed during interrupted landing")
    original = journal["original"]
    intended = journal["intended"]
    # Every path the transaction owns -- one "source" for a single landing,
    # one "source::<func>" per member for a batch -- plus results and census.
    names = [name for name in journal["paths"] if name != "config"]
    known = True
    for name in names:
        allowed = {original[name]}
        if intended.get(name):
            allowed.add(intended[name])
        if current[name] not in allowed:
            known = False
    if not known:
        _block_landing_recovery(
            path, journal, f"landing files contain hashes outside original/intended evidence: {current}")
    exact_intended = bool(intended.get("census")) and all(
        current[name] == intended[name] for name in names)
    if exact_intended:
        try:
            return _complete_landing(path, journal, gate_runner=gate_runner)
        except BaseException as complete_exc:
            try:
                return _restore_landing(path, journal, gate_runner=gate_runner)
            except BaseException as rollback_exc:
                _block_landing_recovery(
                    path, journal,
                    f"landing completion failed ({complete_exc}); rollback failed ({rollback_exc})")
    try:
        return _restore_landing(path, journal, gate_runner=gate_runner)
    except BaseException as exc:
        _block_landing_recovery(path, journal, f"landing rollback proof failed ({exc})")
    raise AssertionError("unreachable")


def recover_family_landings(family: str, *,
                            gate_runner: Callable[[list[str]], str] = run_gate) -> list[dict[str, Any]]:
    """Recover nonterminal journals. Caller holds gate-apply + family locks."""
    txndir = _landing_transaction_dir(family)
    if not txndir.exists():
        return []
    recovered = []
    for path in sorted(txndir.glob("*.json")):
        journal = _load_landing_journal(path)
        if journal.get("state") not in ("committed", "rolled_back"):
            overlay_lock = landing_lock_path(str(journal["overlay"]))
            overlay_lock.parent.mkdir(parents=True, exist_ok=True)
            with overlay_lock.open("a+b") as lock:
                fcntl.flock(lock, fcntl.LOCK_EX)
                recovered.append({"journal": str(path), **_recover_landing_one(
                    path, journal, gate_runner=gate_runner)})
    return recovered


def recover_landing_journal(path: Path, *, strategy: str, expect_current: str,
                            gate_runner: Callable[[list[str]], str] = run_gate) -> dict[str, Any]:
    journal = _load_landing_journal(path)
    current = _current_landing_state(journal)
    digest = _state_sha(current)
    if digest != expect_current:
        raise RuntimeError(f"landing state changed again: expected {expect_current}, observed {digest}")
    try:
        if strategy == "complete":
            return _complete_landing(path, journal, gate_runner=gate_runner)
        return _restore_landing(path, journal, gate_runner=gate_runner)
    except BaseException as exc:
        _block_landing_recovery(path, journal, f"explicit {strategy} recovery failed ({exc})")
        raise AssertionError("unreachable")


def find_landing_group(sb: dict[str, Any], overlay: str) -> tuple[Path, Path]:
    want_results = cfg_path(f"overlays/{overlay}/overlay_first_pass_results.json")
    for group in sb.get("matched_sources", []):
        results = cfg_path(group["results"])
        if results == want_results:
            return results, cfg_path(group["source_dir"])
    raise SystemExit(f"{overlay} is not a matched_sources group in the configured gate")


def find_row(rows: list[dict[str, Any]], func: str) -> dict[str, Any]:
    hits = [row for row in rows if row.get("func_vram") == func and not row.get("rerun")]
    if len(hits) != 1:
        raise SystemExit(f"expected one non-rerun row for {func}, found {len(hits)}")
    return hits[0]


def land_functions(*, config_path: Path, overlay: str,
                   items: list[dict[str, Any]],
                   gate_runner: Callable[[list[str]], str] = run_gate,
                   census_runner: Callable[[str], None] = regenerate_census,
                   fault: Callable[[str], None] | None = None,
                   allow_fidelity_regression: bool = False) -> dict[str, Any]:
    """Land N C functions of ONE gate window as one transaction.

    WHY: the per-function route rebuilds the whole window TWICE per function
    (staged proof + persisted proof).  On a 335 KB window that is ~5 minutes of
    gate per landed leaf, so a 150-row free-match harvest costs ~13 hours of
    pure rebuild.  Batching amortises it to two rebuilds for the whole group.

    The PROOF IS NOT WEAKENED.  The staged run compiles every member as a
    matched segment and requires the window byte-identical with all of them in
    place; the persisted run re-proves the same thing from the written files.
    That is exactly the end state N sequential landings would leave -- the only
    thing given up is the intermediate proof of each prefix, which nothing
    consumes.  Every guarded input (candidate bytes, gate YAML, results JSON,
    census, rowbase evidence) is re-hashed after the staged proof exactly as in
    land_function, and the transaction journals all N sources so a crash rolls
    the whole group back.

    A staged FAILURE is not attributed to a member -- the caller must retry the
    group one at a time (or bisect) to find the offender.  C sources only; the
    assembly routes stay single-function.
    """
    if not items:
        return {"landed": [], "stage_only": False}
    # One baseline load + one set of mmapped containers for the whole batch.
    fidelity_override = decomp_audit_ratchet.override_active(allow_fidelity_regression)
    fidelity = decomp_audit_ratchet.session()
    fam = family_for(overlay)
    family_lock = family_lock_path(fam)
    lock_path = landing_lock_path(overlay)
    lock_path.parent.mkdir(parents=True, exist_ok=True)
    apply_lock_path = ROOT / "work" / "gate_carver" / ".apply.lock"
    apply_lock_path.parent.mkdir(parents=True, exist_ok=True)
    with apply_lock_path.open("a+b") as apply_lock, family_lock.open("a+b") as family_guard:
        fcntl.flock(apply_lock, fcntl.LOCK_SH)
        fcntl.flock(family_guard, fcntl.LOCK_EX)
        recover_family_landings(fam, gate_runner=gate_runner)
        with lock_path.open("a+b") as lock:
            fcntl.flock(lock, fcntl.LOCK_EX)
            config_bytes = config_path.read_bytes()
            cfg = yaml.safe_load(config_bytes)
            sb = cfg.get("standalone_build")
            if not isinstance(sb, dict):
                raise SystemExit(f"{rel(config_path)} lacks a standalone_build block")
            results_path, source_dir = find_landing_group(sb, overlay)
            original_json = results_path.read_bytes()
            rows = load_json_list(results_path)

            prepared: list[dict[str, Any]] = []
            seen: set[str] = set()
            stage_args = ["--config", str(config_path), "--clean"]
            for item in items:
                func = str(item["func"])
                if func in seen:
                    raise SystemExit(f"duplicate function in landing batch: {func}")
                seen.add(func)
                candidate_file = cfg_path(item["c_file"])
                if not candidate_file.is_file():
                    raise SystemExit(f"candidate source missing: {rel(candidate_file)}")
                candidate_bytes = candidate_file.read_bytes()
                text = candidate_bytes.decode("utf-8", errors="replace")
                refusals = portability_lint.landing_refusals(
                    text, rel(source_dir / f"{func}.c"))
                if refusals:
                    raise SystemExit(
                        f"portability lint REFUSED {func} (stays INCLUDE_ASM): {refusals[0]}")
                row = find_row(rows, func)
                # Fidelity ratchet (intake B.3 / G-12; docs/fidelity_ratchet.md).
                # Refuses ONLY a landing that ADDS a blocking-class site this row
                # does not already carry in config/decomp_audit_baseline.json; a
                # site that disappears never blocks. Audits this ONE row (~0.1 s),
                # never the tree.
                # ALWAYS audited, even under the override. The override used
                # to short-circuit this call entirely, so nothing ever learned
                # what it admitted -- 44 would-refuse sites entered the tree
                # that way (baseline_report.md 2026-09-01). What the override
                # PERMITS is unchanged; it is no longer silent.
                fid = fidelity.refusals(overlay, func, text, row=row)
                waived: list[str] = []
                if fid:
                    if not fidelity_override:
                        raise SystemExit(decomp_audit_ratchet.refusal_message(
                            func, fid, "tools/overlay_land_function.py"))
                    decomp_audit_ratchet.record_waiver(
                        overlay, func, fid, "tools/overlay_land_function.py")
                    waived = list(fid)
                selected_config = item.get("match_config") or row.get("config")
                if not selected_config:
                    raise SystemExit(f"{func} has no config; pass match_config")
                # Keyed-configuration ratchet — same position and same
                # fail-closed shape as the portability/fidelity refusals above,
                # and still before any write (the batch only stages after this
                # loop completes).  Covers the compiler bridge AND the two
                # assembler legs (a --retail-* maspsx dial resolved for this
                # row, or a maspsx function-name table it depends on).
                refuse_keyed_config(func, selected_config, overlay=overlay,
                                    row=row)
                identity = rowbase_naming_debt.check_landing_identity(
                    overlay, func, row.get("foff"),
                    rowbase_naming_debt.file_definitions(text),
                    size=row.get("size"), source_dir=source_dir, root=ROOT,
                    action="landing")
                for note in identity["notes"]:
                    print(f"LANDING IDENTITY: {note}")
                dest = source_dir / f"{func}.c"
                prepared.append({
                    "func": func, "row": row, "dest": dest,
                    "fidelity_waived": waived,
                    "candidate_file": candidate_file, "candidate_bytes": candidate_bytes,
                    "candidate_sha": hashlib.sha256(candidate_bytes).hexdigest(),
                    "config": str(selected_config), "identity": identity,
                })
                stage_args += ["--stage-match", func, str(candidate_file),
                               str(selected_config)]

            census = ROOT / ("config/noreturn_syms.txt" if fam == "main"
                             else f"config/noreturn_syms.{fam}.txt")
            census_state = _file_state(census)
            rowbase_evidence = ROOT / f"config/overlays/{fam}.rowbase.jsonl"
            rowbase_state = _file_state(rowbase_evidence)

            staged_output = gate_runner(stage_args)
            for entry in prepared:
                if (hashlib.sha256(entry["candidate_file"].read_bytes()).hexdigest()
                        != entry["candidate_sha"]):
                    raise RuntimeError(
                        f"candidate changed during staged gate proof: {entry['func']}")
            if config_path.read_bytes() != config_bytes:
                raise RuntimeError("gate config changed during staged gate proof")
            if _file_state(census) != census_state or results_path.read_bytes() != original_json:
                raise RuntimeError("overlay evidence/results changed during staged gate proof")
            if _file_state(rowbase_evidence) != rowbase_state:
                raise RuntimeError("rowbase evidence changed during staged gate proof")

            source_dir.mkdir(parents=True, exist_ok=True)
            rowbase_records = []
            rowbase_path = ROOT / f"config/overlays/{fam}.rowbase.jsonl"
            if rowbase_path.exists():
                for rb_line in rowbase_path.read_text().splitlines():
                    rb_line = rb_line.strip()
                    if not rb_line or rb_line.startswith("#"):
                        continue
                    rowbase_records.append(json.loads(rb_line))
            for entry in prepared:
                row = entry["row"]
                row["result"] = "MATCH"
                row["config"] = entry["config"]
                row["words_off"] = 0
                row["c_path"] = rel(entry["dest"])
                row.pop("asm_path", None)
                row.pop("source_kind", None)
                row.pop("frontier", None)
                row["gate_verified"] = True
                row["gate_config"] = rel(config_path)
                for rec in rowbase_records:
                    if (rec.get("base_confidence") == "proven"
                            and int(str(rec["foff_start"]), 0) <= int(row["foff"])
                            < int(str(rec["foff_end"]), 0)):
                        true_name = "func_%08X" % (
                            int(row["foff"]) + int(str(rec["delta"]), 0))
                        if true_name in rowbase_naming_debt.file_definitions(
                                entry["candidate_bytes"].decode(errors="replace")):
                            row["true_name"] = true_name
                        break

            intended_results = (json.dumps(rows, indent=1) + "\n").encode()
            journal_path, journal = _prepare_landing_journal(
                family=fam, overlay=overlay, func=prepared[0]["func"],
                config_path=config_path, dest=prepared[0]["dest"],
                results_path=results_path, census=census,
                candidate_bytes=prepared[0]["candidate_bytes"],
                intended_results=intended_results, staged_output=staged_output,
                sources=[(e["func"], e["dest"], e["candidate_bytes"]) for e in prepared])
            try:
                for entry in prepared:
                    _atomic_write(entry["dest"], entry["candidate_bytes"])
                _atomic_write(results_path, intended_results)
                _transition_landing_journal(journal_path, journal, "source_results")
                if fault:
                    fault("after-source-results")
                census_runner(fam)
                intended_census = _file_state(census)
                if intended_census == "non-file":
                    raise RuntimeError(f"census generator produced a non-file: {census}")
                journal["intended"]["census"] = intended_census
                _transition_landing_journal(journal_path, journal, "census_updated")
                if fault:
                    fault("after-census")
                persisted_output = gate_runner(["--config", str(config_path), "--clean"])
                if fault:
                    fault("after-persisted-proof")
                expected = {**journal["intended"], "config": journal["config_sha256"]}
                current = _current_landing_state(journal)
                if current != expected:
                    raise RuntimeError(
                        f"persisted landing state changed during global proof: {current}")
                _transition_landing_journal(
                    journal_path, journal, "committed",
                    recovery={"global_proven": True,
                              "persisted_output": persisted_output})
                return {
                    "staged_output": staged_output, "persisted_output": persisted_output,
                    "stage_only": False, "journal": str(journal_path),
                    "landed": [{"func": e["func"], "dest": str(e["dest"]),
                                "match_config": e["config"],
                                "candidate_sha256": e["candidate_sha"],
                                "identity": e["identity"],
                                # What the blanket override let through on this
                                # row, on the landing record itself.
                                "fidelity_waived": e.get("fidelity_waived") or []}
                               for e in prepared],
                }
            except BaseException as exc:
                try:
                    _restore_landing(journal_path, journal, gate_runner=gate_runner)
                except BaseException as rollback_exc:
                    try:
                        _block_landing_recovery(
                            journal_path, journal,
                            f"batch landing failed ({exc}); rollback/global proof failed "
                            f"({rollback_exc})")
                    except RuntimeError as blocked_exc:
                        raise LandingRollbackError(str(blocked_exc)) from rollback_exc
                raise


def land_function(*, config_path: Path, overlay: str, func: str,
                  c_file: Path | None = None, asm_file: Path | None = None,
                  asm_kind: str = "platform_asm",
                  match_config: str | None = None, stage_only: bool = False,
                  gate_runner: Callable[[list[str]], str] = run_gate,
                  census_runner: Callable[[str], None] = regenerate_census,
                  fault: Callable[[str], None] | None = None,
                  allow_fidelity_regression: bool = False) -> dict[str, Any]:
    """Land one function under gate-apply, family, then overlay locks."""
    if (c_file is None) == (asm_file is None):
        raise SystemExit("landing requires exactly one of c_file or asm_file")
    asm_landing = asm_file is not None
    fidelity_override = decomp_audit_ratchet.override_active(allow_fidelity_regression)
    if asm_landing:
        if asm_kind not in ASM_SOURCE_ROOTS:
            raise SystemExit(f"unknown assembly source kind: {asm_kind!r}")
        asm_file = validate_asm_source(asm_file, asm_kind, root=ROOT)
        candidate_file = asm_file
    else:
        assert c_file is not None
        candidate_file = c_file
    fam = family_for(overlay)
    family_lock = family_lock_path(fam)
    lock_path = landing_lock_path(overlay)
    lock_path.parent.mkdir(parents=True, exist_ok=True)
    # Gate config installs take this lock exclusively. Landers take it shared,
    # then serialize all overlays which share a census at family scope, then
    # serialize the individual overlay. Never acquire these in another order.
    apply_lock_path = ROOT / "work" / "gate_carver" / ".apply.lock"
    apply_lock_path.parent.mkdir(parents=True, exist_ok=True)
    with apply_lock_path.open("a+b") as apply_lock, family_lock.open("a+b") as family_guard:
        fcntl.flock(apply_lock, fcntl.LOCK_SH)
        fcntl.flock(family_guard, fcntl.LOCK_EX)
        # Family recovery runs before this request takes an overlay lock so it
        # can recover journals for every overlay without reversing lock order.
        recover_family_landings(fam, gate_runner=gate_runner)
        with lock_path.open("a+b") as lock:
            fcntl.flock(lock, fcntl.LOCK_EX)
            # Re-resolve every mutable input only after entering the critical section.
            if not candidate_file.is_file():
                raise SystemExit(f"candidate source missing: {rel(candidate_file)}")
            candidate_bytes = candidate_file.read_bytes()
            candidate_sha = hashlib.sha256(candidate_bytes).hexdigest()
            config_bytes = config_path.read_bytes()
            cfg = yaml.safe_load(config_bytes)
            sb = cfg.get("standalone_build")
            if not isinstance(sb, dict):
                raise SystemExit(f"{rel(config_path)} lacks a standalone_build block")

            results_path, source_dir = find_landing_group(sb, overlay)
            # Portability gate (ROADMAP §3 D/E): the overlay compare bypasses
            # match.py's asm-transcription downgrade, so this route was the historical
            # hole through which non-portable overlay functions landed (8 hard funcs,
            # docs/asm_pinning_portability_analysis.md). Refuse before the staged
            # proof — absolute-HARD (transcription / coupled pin) plus any NEW
            # RAW_PIN/UNSANCTIONED_ASM scaffolding beyond this function's grandfathered
            # baseline. Matches integrate.py's refusal behavior; costs one cheap scan.
            refusals = [] if asm_landing else portability_lint.landing_refusals(
                candidate_bytes.decode("utf-8", errors="replace"),
                rel(source_dir / f"{func}.c"))
            if refusals:
                raise SystemExit(
                    f"portability lint REFUSED {func} (stays INCLUDE_ASM): {refusals[0]}"
                    " -> guard MIPS pins with ASM_REG/ASM_KEEP (include/common.h) or "
                    "restructure to pure C; --write-baseline only for an intended change")
            # Fidelity ratchet (intake B.3 / G-12; docs/fidelity_ratchet.md). Same
            # shape as the portability refusal above and for the same reason: this
            # route bypasses match.py, so it is where a semantically-wrong C would
            # otherwise enter the tree unremarked. Refuses ONLY an ADDED
            # blocking-class site (config/decomp_audit_baseline.json grandfathers
            # every site that exists today); a site that DISAPPEARS never blocks.
            # Assembly landings carry no C to audit. One row, ~0.1 s.
            # ALWAYS audited, even under the override (see the batch path's
            # note): the override changes the VERDICT, never whether the sites
            # are known and recorded.
            fidelity_waived: list[str] = []
            if not asm_landing:
                fid = decomp_audit_ratchet.landing_refusals(
                    overlay, func,
                    candidate_bytes.decode("utf-8", errors="replace"))
                if fid:
                    if not fidelity_override:
                        raise SystemExit(decomp_audit_ratchet.refusal_message(
                            func, fid, "tools/overlay_land_function.py"))
                    decomp_audit_ratchet.record_waiver(
                        overlay, func, fid, "tools/overlay_land_function.py")
                    fidelity_waived = list(fid)
            # Reading the results JSON writes nothing, and the identity screen
            # below needs this row's foff, so both refusals still land before any
            # file, journal or backup is touched.
            original_json = results_path.read_bytes()
            rows = load_json_list(results_path)
            row = find_row(rows, func)
            selected_config = match_config or row.get("config")
            if not asm_landing and not selected_config:
                raise SystemExit(f"{func} has no config; pass --match-config")
            # Keyed-configuration ratchet (see refuse_keyed_config).  C
            # landings only: an assembly landing compiles nothing and records
            # the route marker ``platform-asm``/``nonmatching-asm`` in the row's
            # config field, which names no compiler at all, and passes no
            # assembler dial.
            if not asm_landing:
                refuse_keyed_config(func, selected_config, overlay=overlay,
                                    row=row)
            # Landing-identity screen (option 3 / owner decision 2026-07-29,
            # work/debt_20260729/opt3_region_qualified_names_spec.md §5.3(a)).
            # REPLACES the 2026-07-29 duplicate-symbol screen, whose "one
            # first_pass_matched/ directory = one link unit" model was wrong twice
            # over: config/overlays/dungeon_engine.overlay.yaml:83-95 merges TWO
            # directories into ONE link window, and a bare func_<true vram> is a
            # RAM-SLOT LABEL, not an identity — two genuinely different functions
            # in two different rowbase regions legitimately carry the same one (24
            # such slot groups live today). The canonical identity is
            # region-qualified (func_<VRAM8>__<family>__<region>), derived by
            # tools/rowbase_identity.py and never written into C text; PWU keeps
            # the bare label legal at the link (every proven-region row is
            # mini-linked ALONE and injected as raw bytes,
            # tools/overlay_local_gate.py:915-975) and
            # overlay_local_gate.assert_unique_globals enforces it.
            # So the screen no longer asks "is this name taken?". It refuses
            # exactly one thing — a TU that defines a func_<8hex> global which is
            # neither its synthetic row key nor the true name its OWN foff derives,
            # i.e. a candidate compiled against the wrong link base (the
            # WINDOW-LINK DIVERGENCE class, tools/rowbase_rename_reverify.py:12-18,
            # which no name-uniqueness test can see) — and it ALLOWS and RECORDS a
            # cross-region slot share, which is what makes the 28 TUs of the 14
            # landed pairs re-landable. Structural violations (RIA, stem
            # uniqueness) raise as evidence corruption, never as an owner call.
            # Candidate C text is NEVER required to carry a qualifier (§5.2 B2):
            # identity is re-derived from (unit, foff) at every use, so bare
            # rowbase_true_name values from the frozen w77 packs stay valid input.
            if asm_landing:
                identity = {
                    "kind": asm_kind,
                    "function": func,
                    "source": rel(candidate_file),
                    "source_boundary": ASM_SOURCE_ROOTS[asm_kind].as_posix(),
                    "notes": [],
                }
            else:
                identity = rowbase_naming_debt.check_landing_identity(
                    overlay, func, row.get("foff"),
                    rowbase_naming_debt.file_definitions(
                        candidate_bytes.decode("utf-8", errors="replace")),
                    size=row.get("size"), source_dir=source_dir, root=ROOT,
                    action="landing")
            for note in identity["notes"]:
                print(f"LANDING IDENTITY: {note}")

            census = ROOT / ("config/noreturn_syms.txt" if fam == "main"
                             else f"config/noreturn_syms.{fam}.txt")
            census_state = _file_state(census)
            # Rowbase evidence determines the link base of every in-region
            # staged segment — same guarded-input class as the gate YAML
            # (postmortem 2026-07-29: a 4-minute concurrent revert of this file
            # turned a green landing into a phantom j-word NO MATCH).
            rowbase_evidence = ROOT / f"config/overlays/{fam}.rowbase.jsonl"
            rowbase_state = _file_state(rowbase_evidence)
            if asm_landing:
                stage_args = [
                    "--config", str(config_path), "--clean",
                    f"--stage-{asm_kind.replace('_', '-')}",
                    func, str(candidate_file),
                ]
            else:
                stage_args = [
                    "--config", str(config_path), "--clean", "--stage-match",
                    func, str(candidate_file), str(selected_config),
                ]
            staged_output = gate_runner(stage_args)
            if hashlib.sha256(candidate_file.read_bytes()).hexdigest() != candidate_sha:
                raise RuntimeError("candidate changed during staged gate proof")
            if config_path.read_bytes() != config_bytes:
                raise RuntimeError("gate config changed during staged gate proof")
            if _file_state(census) != census_state or results_path.read_bytes() != original_json:
                raise RuntimeError("overlay evidence/results changed during staged gate proof")
            if _file_state(rowbase_evidence) != rowbase_state:
                raise RuntimeError("rowbase evidence changed during staged gate proof")
            if stage_only:
                return {"staged_output": staged_output, "stage_only": True,
                        "candidate_sha256": candidate_sha,
                        "match_config": selected_config, "identity": identity,
                        "fidelity_waived": fidelity_waived}

            if not asm_landing:
                source_dir.mkdir(parents=True, exist_ok=True)
            # Platform twins already have a canonical checked-in source under
            # asm/psyq.  Keep that source in place and persist only the row's
            # provenance; the transaction still journals its hash so a
            # concurrent edit cannot turn a green proof into a different one.
            dest = candidate_file if asm_landing else source_dir / f"{func}.c"
            row["result"] = "MATCH"
            row["config"] = selected_config if not asm_landing else asm_kind.replace("_", "-")
            row["words_off"] = 0
            if asm_landing:
                row.pop("c_path", None)
                row["source_kind"] = asm_kind
                row["asm_path"] = rel(candidate_file)
            else:
                row["c_path"] = rel(dest)
                row.pop("asm_path", None)
                row.pop("source_kind", None)
            # A landed row is aligned 0 by proof, so any ``frontier`` block it
            # still carries is a strictly worse, superseded candidate.  MAIN's
            # convention (042f1a62) is that no MATCH row carries one; TOWN's 67
            # permuter landings kept theirs only because nothing on the landing
            # path cleared it.  live_truth/overlay_status already ignore a
            # frontier on a done row, so this is staleness, not signal.
            row.pop("frontier", None)
            row["gate_verified"] = True
            row["gate_config"] = rel(config_path)
            # Rowbase naming inversion (owner decision B): in a PROVEN alias
            # region the source defines the function under its true-space name;
            # the row keeps its synthetic key and records the true name.
            rowbase_path = ROOT / f"config/overlays/{fam}.rowbase.jsonl"
            if rowbase_path.exists():
                for rb_line in rowbase_path.read_text().splitlines():
                    rb_line = rb_line.strip()
                    if not rb_line or rb_line.startswith("#"):
                        continue
                    rec = json.loads(rb_line)
                    if (rec.get("base_confidence") == "proven"
                            and int(str(rec["foff_start"]), 0) <= int(row["foff"])
                            < int(str(rec["foff_end"]), 0)):
                        true_name = "func_%08X" % (
                            int(row["foff"]) + int(str(rec["delta"]), 0))
                        if true_name in rowbase_naming_debt.file_definitions(
                                candidate_bytes.decode(errors="replace")):
                            row["true_name"] = true_name
                        break
            intended_results = (json.dumps(rows, indent=1) + "\n").encode()
            journal_path, journal = _prepare_landing_journal(
                family=fam, overlay=overlay, func=func, config_path=config_path,
                dest=dest, results_path=results_path, census=census,
                candidate_bytes=candidate_bytes, intended_results=intended_results,
                staged_output=staged_output)
            try:
                if not asm_landing:
                    _atomic_write(dest, candidate_bytes)
                _atomic_write(results_path, intended_results)
                _transition_landing_journal(journal_path, journal, "source_results")
                if fault:
                    fault("after-source-results")

                if asm_landing:
                    # The source is not C and cannot add noreturn evidence.
                    # Preserve the current census hash as the transaction's
                    # intended state without regenerating it.
                    intended_census = _file_state(census)
                else:
                    census_runner(fam)
                    intended_census = _file_state(census)
                if intended_census == "non-file":
                    raise RuntimeError(f"census generator produced a non-file: {census}")
                journal["intended"]["census"] = intended_census
                _transition_landing_journal(journal_path, journal, "census_updated")
                if fault:
                    fault("after-census")
                persisted_output = gate_runner(["--config", str(config_path), "--clean"])
                if fault:
                    fault("after-persisted-proof")
                expected = {**journal["intended"], "config": journal["config_sha256"]}
                current = _current_landing_state(journal)
                if current != expected:
                    raise RuntimeError(
                        f"persisted landing state changed during global proof: {current}")
                _transition_landing_journal(
                    journal_path, journal, "committed",
                    recovery={"global_proven": True,
                              "persisted_output": persisted_output})
                return {
                    "staged_output": staged_output, "persisted_output": persisted_output,
                    "stage_only": False, "dest": str(dest),
                    "candidate_sha256": candidate_sha, "match_config": selected_config,
                    "journal": str(journal_path), "identity": identity,
                    # What the blanket override let through on THIS landing, on
                    # the landing record rather than only in a log line.
                    "fidelity_waived": fidelity_waived,
                }
            except BaseException as exc:
                try:
                    _restore_landing(journal_path, journal, gate_runner=gate_runner)
                except BaseException as rollback_exc:
                    try:
                        _block_landing_recovery(
                            journal_path, journal,
                            f"landing failed ({exc}); rollback/global proof failed ({rollback_exc})")
                    except RuntimeError as blocked_exc:
                        raise LandingRollbackError(str(blocked_exc)) from rollback_exc
                raise


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--config", default=str(DEFAULT_CONFIG), help="overlay YAML")
    parser.add_argument("--overlay", help="overlay result set to update, e.g. dungeon")
    parser.add_argument("--func", help="function name, e.g. func_8008A2B4")
    parser.add_argument("--c-file", help="candidate C source")
    parser.add_argument(
        "--asm-file", "--platform-asm", "--platform-asm-file", dest="asm_file",
        help="checked-in platform-library assembly source under asm/psyq",
    )
    parser.add_argument(
        "--game-asm-file", "--game-asm", dest="game_asm_file",
        help=("checked-in hand-written GAME assembly source under "
              "asm/nonmatchings, for rows with no portable-C form at all"),
    )
    parser.add_argument(
        "--allow-fidelity-regression", action="store_true",
        help=("land even when the candidate ADDS a fidelity site that "
              "config/decomp_audit_baseline.json does not grandfather (same as "
              "AZ_ALLOW_FIDELITY_REGRESSION=1); afterwards re-run "
              "tools/census/gaps/decomp_audit.py --write-baseline"),
    )
    parser.add_argument("--match-config", default=None, help="compiler config label; defaults to the row config")
    parser.add_argument("--recover-journal", help="explicitly recover this landing journal")
    parser.add_argument("--strategy", choices=("rollback", "complete"))
    parser.add_argument("--expect-current-state-sha")
    parser.add_argument(
        "--stage-only",
        action="store_true",
        help="only run the staged gate; do not update first_pass_matched or JSON",
    )
    parser.add_argument(
        "--batch",
        help=("JSON file: [{\"func\":..., \"c_file\":..., \"match_config\":...}, ...] "
              "for ONE --config window and ONE --overlay. Lands the whole group as a "
              "single transaction (two window rebuilds total instead of two per "
              "function). C sources only."),
    )
    args = parser.parse_args()

    if args.batch:
        if args.overlay is None:
            parser.error("--batch requires --overlay")
        if any(getattr(args, name) is not None
               for name in ("func", "c_file", "asm_file", "game_asm_file")):
            parser.error("--batch cannot be combined with --func/--c-file/--asm-file")
        if args.stage_only:
            parser.error("--batch does not support --stage-only")
        items = json.loads(cfg_path(args.batch).read_text(encoding="utf-8"))
        result = land_functions(
            config_path=cfg_path(args.config), overlay=args.overlay, items=items,
            allow_fidelity_regression=args.allow_fidelity_regression)
        print(json.dumps(result, sort_keys=True))
        return 0

    if args.recover_journal:
        if not args.strategy or not args.expect_current_state_sha:
            parser.error("--recover-journal requires --strategy and --expect-current-state-sha")
        journal_path = cfg_path(args.recover_journal)
        journal = _load_landing_journal(journal_path)
        family = str(journal["family"])
        overlay = str(journal["overlay"])
        apply_path = ROOT / "work/gate_carver/.apply.lock"
        family_path = family_lock_path(family)
        overlay_path = landing_lock_path(overlay)
        overlay_path.parent.mkdir(parents=True, exist_ok=True)
        apply_path.parent.mkdir(parents=True, exist_ok=True)
        with (apply_path.open("a+b") as apply_lock,
              family_path.open("a+b") as family_lock,
              overlay_path.open("a+b") as overlay_lock):
            fcntl.flock(apply_lock, fcntl.LOCK_SH)
            fcntl.flock(family_lock, fcntl.LOCK_EX)
            fcntl.flock(overlay_lock, fcntl.LOCK_EX)
            result = recover_landing_journal(
                journal_path, strategy=args.strategy,
                expect_current=args.expect_current_state_sha)
        print(json.dumps(result, sort_keys=True))
        return 0

    missing = [name for name in ("overlay", "func")
               if getattr(args, name) is None]
    if missing:
        parser.error("landing requires " + ", ".join("--" + name.replace("_", "-")
                                                      for name in missing))
    sources = [name for name in ("c_file", "asm_file", "game_asm_file")
               if getattr(args, name) is not None]
    if len(sources) != 1:
        parser.error("landing requires exactly one of --c-file, --asm-file "
                     "or --game-asm-file")
    asm_kind = {"asm_file": "platform_asm",
                "game_asm_file": "game_asm"}.get(sources[0])

    config_path = cfg_path(args.config)
    candidate = cfg_path(getattr(args, sources[0]))
    result = land_function(
        config_path=config_path, overlay=args.overlay, func=args.func,
        c_file=candidate if asm_kind is None else None,
        asm_file=None if asm_kind is None else candidate,
        asm_kind=asm_kind or "platform_asm",
        match_config=args.match_config, stage_only=args.stage_only,
        allow_fidelity_regression=args.allow_fidelity_regression)
    print(result["staged_output"], end="")
    print(f"STAGED GATE PASS: {args.func} from {rel(candidate)} "
          f"({result.get('match_config') or args.match_config})")
    if not args.stage_only:
        print(result["persisted_output"], end="")
        print(f"LANDED GATE PASS: {args.func} -> {rel(Path(result['dest']))}")
        post_land_census_delta_check(args.func)
    return 0


def post_land_census_delta_check(func: str) -> None:
    """Re-score LANDED INCUMBENTS when this landing moved a census.

    THE GATE ABOVE PROVES THE ROW BEING LANDED — and nothing else.  A census
    (``config/noreturn_syms.<container>.txt`` / ``sibcall_syms.*``) is a GLOBAL
    maspsx input, so a landing that sweeps one new symbol into it can silently
    rewrite an instruction in an ALREADY-LANDED TU.  That is not hypothetical:
    commit 3dedba02 swept ``func_80024094`` in from a co-landed TU's noreturn
    decl and flipped one opcode bit (``jal`` -> ``j``, word 54) in the landed
    ``func_818ED25C``, which then sat broken for five days
    (work/wave_20260901_burndown/fid_818ED25C/REPORT.md).

    Advisory here BY DESIGN: the landing already committed, so this cannot undo
    it, and this hook must never change ``main``'s exit contract that the
    landing chains parse.  It PRINTS, loudly.  The authoritative, state-advancing
    run is the batch-end hook in ``tools/land_batch.sh`` /
    ``codex_wave._fire_post_land_twins``, which does fail the batch.

    Skipped when ``POST_LAND_DEFER=1`` (the batch owns the hook, same convention
    as land_one_v2.sh's twin cascade) or ``CENSUS_DELTA_RESCORE=0``.
    """
    if os.environ.get("POST_LAND_DEFER") or os.environ.get("CENSUS_DELTA_RESCORE") == "0":
        return
    try:
        import census_delta_rescore
        report = census_delta_rescore.check(ROOT, update_state=False)
    except Exception as exc:  # noqa: BLE001 - advisory hook, never breaks a landing
        print(f"census-delta check unavailable after landing {func} "
              f"(non-fatal): {type(exc).__name__}: {exc}")
        return
    if not report.get("delta"):
        return
    for rec in report.get("broken", []):
        print(f"!!! CENSUS-DELTA FIDELITY BREAK: landed {rec['scope']}/"
              f"{rec['func']} is NO LONGER byte-exact "
              f"(words_off={rec['words_off']}, refs {', '.join(rec['symbols'])}) "
              f"— this landing's census delta moved an incumbent. "
              f"Do NOT land further on top.")
    if not report.get("broken"):
        print(f"census-delta check after {func}: "
              f"{len(report.get('checked') or [])} incumbent(s) re-scored, "
              f"{len(report.get('unscored') or [])} unscored — {report.get('note')}")


if __name__ == "__main__":
    raise SystemExit(main())
