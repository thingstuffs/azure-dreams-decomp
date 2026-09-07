#!/usr/bin/env python3
"""Canonical live-truth service for the decomp campaign (program TF-1).

Every planner and dashboard used to answer "what remains / how close is it / can
it land" from a different store, and they disagreed.  `progress.py` gave a landed
``MATCH`` terminal precedence; `overlay_status.classify_row` checked the ``parked``
marker first and so imprisoned 23 already-landed rows; the campaign controller
checked ``parked`` before fresh oracle exactness; the raw row ``words_off`` is a
frozen first-pass snapshot while the current aligned distance lives only in the
content-addressed census cache; a stored aligned score can silently belong to a
stale tool/evidence epoch.

This module is the single reducer/service they all consult:

* :func:`overlay_verdict` — the one canonical ``(state, status, reason)`` reducer.
  Terminal precedence: a landed source plus a verified-exact result outranks any
  later park marker.  A *fresh* oracle-exact record is evaluated **before** the
  parked diagnosis, so a park self-heals when a new instrument lands.  Data
  segments get their own ``data`` state and can never enter a code lane.
* :func:`keyed_of` (compiler leg :func:`bridge_of`) / :data:`STATUS_BRIDGED` —
  the one place that decides whether a row's bytes needed a PER-FUNCTION KEYED
  configuration: a non-stock ``toolchain/compilers/`` directory or a
  ``-fretail-``/``-fsn-``/``-fdriver-`` compiler flag, a ``--retail-*`` maspsx
  dial from ``config/overlays/<family>.as_flags.jsonl`` /
  ``configure.py::AS_FLAGS``, or a maspsx function-name table.  A byte-exact row
  that needed any of them is ``wip`` / ``bridged``, never ``done``.
* :func:`is_terminal_exact` — the guard S7 uses so a plateau park can never be
  written onto a MATCH/landed row.
* :func:`current_score` / :func:`current_state` — primary score is the current
  census-cache record; the legacy row ``words_off`` is an explicitly labelled,
  aged fallback.  A stored score whose tool/evidence epoch no longer matches the
  request is rejected (never silently reused) and triggers re-verification.
* :func:`instrument_revalidation_targets` — the entry point (data shape now, full
  loop in a later wave) for re-scoring banked/parked candidates a new instrument
  affects.
* :func:`gcc_diagnostic` — preserve the first ``file:line`` diagnostic plus a
  bounded multi-line tail instead of a blind 120-char head slice.
* ``python3 tools/live_truth.py --reconcile`` — one command that asserts every
  consumer agrees on remaining code counts/bytes by scope.

Design note: this module imports only the standard library at top level.  The
heavier project modules (`overlay_status`, `progress`, `oracle_census`) are
imported lazily inside the functions that need them, so `overlay_status` and
`progress` can import *this* module for the reducer without an import cycle.
"""

from __future__ import annotations

import argparse
from dataclasses import dataclass, field
import json
import os
import re
import sys
from pathlib import Path
import tempfile
from typing import Any, Callable

ROOT = Path(__file__).resolve().parents[1]
DEFAULT_CACHE = ROOT / "build" / "oracle_census" / "cache"

# The separated inventories (program TF-1 deliverable 3).  Data can never enter a
# code lane, so it is kept structurally distinct rather than folded into "parked".
INVENTORY_CODE = "code"
INVENTORY_DATA = "data"


def _atomic_json(path: Path, value: Any) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    descriptor, temporary = tempfile.mkstemp(prefix=f".{path.name}.", dir=path.parent)
    try:
        with os.fdopen(descriptor, "w", encoding="utf-8") as stream:
            json.dump(value, stream, indent=2, sort_keys=True)
            stream.write("\n")
            stream.flush()
            os.fsync(stream.fileno())
        os.replace(temporary, path)
    finally:
        try:
            os.unlink(temporary)
        except FileNotFoundError:
            pass

# Canonical states.  ``data`` is first-class and excluded from code totals.
STATE_DONE = "done"
STATE_WIP = "wip"
STATE_PARKED = "parked"
STATE_TODO = "todo"
STATE_DATA = "data"

CODE_STATES = (STATE_DONE, STATE_WIP, STATE_PARKED, STATE_TODO)

SCOPE_MAIN = "main"
SCOPE_OVERLAY_PREFIX = "overlay:"


def canonical_scope(*, overlay: str | None = None,
                    legacy_scope: str | None = None,
                    binary_kind: str | None = None) -> str:
    """Return the explicit binary scope used by current truth records.

    ``main`` is the resident executable.  An overlay literally named ``main``
    is ``overlay:main``.  Legacy ``slus`` remains readable only through the
    explicit ``legacy_scope`` adapter; new records never emit it.  Other bare
    legacy names are treated as overlay display names.
    """
    if legacy_scope is not None:
        raw = str(legacy_scope).strip()
        if raw in ("slus", "resident", "main-exe"):
            return SCOPE_MAIN
        if raw == SCOPE_MAIN:
            # Canonical spelling wins.  The formerly ambiguous overlay must be
            # requested explicitly as overlay:main.
            return SCOPE_MAIN
        if raw.startswith(SCOPE_OVERLAY_PREFIX) and raw[len(SCOPE_OVERLAY_PREFIX):]:
            return raw
        if raw:
            return f"{SCOPE_OVERLAY_PREFIX}{raw}"
        raise ValueError("empty legacy scope")
    if binary_kind == "main":
        return SCOPE_MAIN
    if overlay is None:
        if binary_kind == "overlay":
            raise ValueError("overlay scope requires a name")
        return SCOPE_MAIN
    name = str(overlay).strip()
    if name.startswith(SCOPE_OVERLAY_PREFIX):
        name = name[len(SCOPE_OVERLAY_PREFIX):]
    if not name:
        raise ValueError("empty overlay scope")
    return f"{SCOPE_OVERLAY_PREFIX}{name}"


def display_scope(scope: str) -> str:
    """Human-facing scope name; never use this value as an identity."""
    return (scope[len(SCOPE_OVERLAY_PREFIX):]
            if scope.startswith(SCOPE_OVERLAY_PREFIX) else "slus")


# --------------------------------------------------------------------------- #
# small pure helpers (no project imports)
# --------------------------------------------------------------------------- #
def _words_off(row: dict) -> int | None:
    """Positional distance the row carries.  ``words_off_resweep`` wins because a
    resweep is the newer measurement; both are frozen first-pass style numbers."""
    for key in ("words_off_resweep", "words_off"):
        val = row.get(key)
        if isinstance(val, bool):
            continue
        if isinstance(val, int):
            return val
        if isinstance(val, str):
            try:
                return int(val, 0)
            except ValueError:
                pass
    return None


def _is_gateable(row: dict, window: dict | None) -> bool:
    if not window:
        return False
    foff = row.get("foff")
    size = row.get("size")
    return (isinstance(foff, int) and isinstance(size, int)
            and window.get("file_start", 1) <= foff
            and foff + size <= window.get("file_end", -1))


def _note(row: dict, default: str = "") -> str:
    return str(row.get("note") or default)


def inventory_of(state: str, data_segment: bool = False) -> str:
    """Which separated inventory a classified row belongs to."""
    if state == STATE_DATA or data_segment:
        return INVENTORY_DATA
    return INVENTORY_CODE


# The status carried by a PSY-Q BIOS vector stub: a 16-byte kernel-table
# dispatch wrapper (``li t2,<0xA0|0xB0>; jr t2; li t1,<selector>; nop``) that is
# landed as checked-in ``asm/psyq`` assembly, never as C.  Its ``jr`` delay-slot
# schedule cannot be expressed in policy-compliant C, so it is NOT an asm->C
# conversion candidate and must never enter a wave/batch lane.  It is also not
# "done" work for a PC port: the port has to supply a real implementation of the
# BIOS call.  Hence its own parked status with a port-facing reason string.
# Evidence: work/town_100_20260808/BIOS_STUB_PARK.md.
STATUS_BIOS_STUB = "bios-stub"


def bios_stub_reason(row: dict) -> str:
    """Port-facing one-liner for a BIOS-stub row, built from its own evidence.

    The dashboard leaf schema is deliberately tiny (name/addr/size/state/status/
    reason), so ``reason`` is where a row carries what a porter needs: the
    vector, the selector, the canonical BIOS function name, and the park doc.
    """
    stub = row.get("bios_stub")
    if not isinstance(stub, dict):
        return _note(row, "PSY-Q BIOS vector stub; a port must implement this BIOS call")
    note = str(stub.get("port_note") or "").strip()
    if not note:
        vector = stub.get("vector", "?")
        selector = stub.get("selector", "?")
        bios = stub.get("bios_function", "?")
        note = (f"PSX kernel-table dispatch wrapper; a port must implement "
                f"BIOS {vector}:{selector} {bios}()")
    reference = str(stub.get("reference") or "").strip()
    return f"{note} See {reference}." if reference else note


# ``hand_asm``: the sibling identity of ``bios_stub`` for HAND-WRITTEN GAME
# assembly.  Where a BIOS stub is a kernel-vector wrapper, these are the game's
# own SDK-style routines whose retail ABI no compiler configuration in this
# project emits -- typically a zero-frame ``$ra``-to-fixed-global save plus an
# inline BIOS vector dispatch (MAIN's boot installers at 0x800217C8 /
# 0x800218A0 / 0x80021958).  Like ``bios_stub`` this is a row IDENTITY, not a
# plateau diagnosis: it outranks the exact/park ladder so the row can never be
# re-dispatched to an asm->C wave, and it is NOT "done" for a PC port, which
# has to reimplement the routine.  A row carrying it may or may not have a
# landed ``asm/nonmatchings`` source; the identity is about representability,
# the ``result``/``gate_verified`` fields about byte proof.
STATUS_HAND_ASM = "hand-asm"


def hand_asm_reason(row: dict) -> str:
    """Port-facing one-liner for a hand-written-assembly row."""
    info = row.get("hand_asm")
    if not isinstance(info, dict):
        return _note(row, "hand-written assembly; no portable-C form exists")
    note = str(info.get("port_note") or "").strip()
    if not note:
        abi = str(info.get("abi") or "non-C calling convention").strip()
        note = (f"hand-written {str(info.get('family') or 'SDK')} assembly "
                f"({abi}); a port must reimplement this routine")
    source = str(info.get("source") or "").strip()
    if source:
        note = f"{note} Landed source: {source}."
    reference = str(info.get("reference") or "").strip()
    return f"{note} See {reference}." if reference else note


# --------------------------------------------------------------------------- #
# bridge detection — a MATCH that only exists through a per-function compiler
# --------------------------------------------------------------------------- #
# THE RULE (work/bridge_remediation_20260905/REPORT.md, verified 2026-09-05):
# a row counts as matched only if a STOCK cc1 plus a general-purpose maspsx
# produce the retail bytes from the checked-in C.  79 DUNGEON rows (51,988 B,
# 3.33 % of matched code bytes) were byte-exact only because their ``config``
# names one of 82 per-function compiler directories under
# toolchain/compilers/ — either a Python ``gcc`` wrapper that runs the stock
# base compiler and then TEXT-EDITS the emitted ``.s`` (swap two register
# colours, rotate a delay slot, reorder a prologue save), or a cc1 rebuilt with
# a ``strcmp(current_function_name, "func_X")`` in sched/reorg/local-alloc that
# picks the retail tie-break for that one function.  None of the 79 is exact at
# any of the 13 stock cells (1,027 compiles, 09-01 audit).  Counting them as
# "done" made the DUNGEON dashboard read 2742/2742 when the honest stock-exact
# number is 2663/2742.
#
# Detection is DYNAMIC, from the row's own ``config`` string — there is no
# ``bridged`` flag in the row DB and there must not be one, because the moment a
# row is re-landed at a stock cell it must stop being bridged with no separate
# bookkeeping step.  ``config/bridge_burndown/baseline.json`` (written by
# tools/bridge_census.py) grandfathers today's set so a NEW bridge is a visible
# regression; it is never consulted to decide whether a row is bridged.
STOCK_CELLS = frozenset({
    "2.6.3", "2.7.2", "2.7.2-cdk", "2.8.0", "2.8.1", "2.91.66", "2.95.2",
})

# Flags that only a bridge compiler understands: ``-fretail-func-<hex>-<tag>``
# gates a selector, ``-fsn-*`` arms a per-function patched cc1 pass, and
# ``-fdriver-qid/-context/-geometry/-true-name`` hand the wrapper the function
# identity it keys on.  A stock cell carrying one of these is just as bridged as
# a non-stock directory.
BRIDGE_FLAG_RE = re.compile(r"^-f(?:retail|sn|driver)-")

# Config labels that name NO COMPILER AT ALL.  The two assembly landing routes
# (tools/overlay_land_function.py) record ``asm_kind.replace("_", "-")`` in the
# row's ``config`` field for a source that is checked-in assembly, never
# compiled C: MAIN's 3 and TOWN's 6 PSY-Q BIOS vector stubs all read
# ``platform-asm``.  Those rows are already held out of the code lane by the
# ``bios_stub`` / ``hand_asm`` identity rules above; they are not bridges, and a
# purely syntactic "head not in STOCK_CELLS" test would libel them.
NON_COMPILER_CONFIGS = frozenset({"platform-asm", "nonmatching-asm"})

# The plan the reason strings point at (owned by the Phase-0 doc author).
BRIDGE_PLAN_DOC = "docs/bridge_remediation_plan_20260905.md"

# A row whose byte-exactness comes from a bridge compiler.  NOT done: it is open
# decomp work (burn it down at a stock cell), so it carries STATE_WIP.  A sixth
# state would have to be threaded through progress.py's STATES/CSS, the treemap
# colours and every consumer's state_counts; the honest reading — "not finished,
# someone still has to close it" — is exactly what ``wip`` already means.
STATUS_BRIDGED = "bridged"

_PARSE_CONFIG_LABEL: Callable[[str], tuple[str, str]] | None = None


def _config_head_flags(label: str) -> tuple[str, str]:
    """(compiler cell, flag string) for a config label, via the ONE parser.

    ``tools/match.py:parse_config_label`` is the canonical parser for both
    circulating dialects (``"2.7.2-cdk -G0 …"`` and ``"2.8.1+-G0 …"``) and knows
    that a glued ``-G0`` is a flag, not a version.  It is imported lazily and
    cached: ``match`` imports *this* module at load time, so a top-level import
    here would be a cycle, and ``match``'s module body reads configure.py plus
    the symbol censuses (~0.1 s) which no dashboard should pay per row.
    """
    global _PARSE_CONFIG_LABEL
    if _PARSE_CONFIG_LABEL is None:
        tools_dir = str(Path(__file__).resolve().parent)
        if tools_dir not in sys.path:
            sys.path.insert(0, tools_dir)
        import match  # noqa: PLC0415 - lazy by design (see docstring)
        _PARSE_CONFIG_LABEL = match.parse_config_label
    return _PARSE_CONFIG_LABEL(label)


def bridge_of(config: Any) -> str | None:
    """Name the per-function compiler a config label selects, else ``None``.

    Returns ``"gcc-<head>"`` when the compiler cell is not one of the seven
    stock drops (that string IS the directory name under
    ``toolchain/compilers/``), or ``"flags:<flag>"`` when the cell is stock but
    a ``-fretail-``/``-fsn-``/``-fdriver-`` flag arms a bridge pass.  ``None``
    for an honest stock configuration — including the empty/absent config a
    never-swept row carries, and the assembly-route markers above.
    """
    label = str(config or "").strip()
    if not label:
        return None
    head, flags = _config_head_flags(label)
    if head in NON_COMPILER_CONFIGS:
        return None
    # A worker reports the verifier's banner spelling ("gcc-2.8.1"); rows and
    # configure.py's CC_VER carry the bare cell ("2.8.1").  Both must reduce to
    # the same answer, and for a bridge both reduce to the same DIRECTORY NAME.
    if head.startswith("gcc-"):
        head = head[len("gcc-"):]
    # A label that names only flags ("-G0 -fno-schedule-insns", as integrate.py's
    # CC_VER pairs can) leaves the cell to the caller's stock default: the
    # leading token is a flag, not a compiler directory.  Scan it as one rather
    # than libelling every such row.
    tokens = flags.split()
    if head.startswith("-"):
        tokens.insert(0, head)
        head = ""
    if head and head not in STOCK_CELLS:
        return f"gcc-{head}"
    for token in tokens:
        if BRIDGE_FLAG_RE.match(token):
            return f"flags:{token}"
    return None


def bridged_reason(row: dict, bridge: str | None = None) -> str:
    """One line that says what the bytes actually came from, and where to look."""
    if bridge is None:
        bridge = bridge_of(row.get("config"))
    if not bridge:
        return ""
    if bridge.startswith("flags:"):
        what = (f"bridge compiler flag {bridge[len('flags:'):]} on stock cell "
                f"{_config_head_flags(str(row.get('config') or ''))[0]}")
    else:
        what = (f"per-function compiler selector {bridge} (post-compile assembly "
                f"rewrite or a cc1 patched with a strcmp on the function name)")
    return (f"byte-exact only through {what}; not stock-exact — "
            f"see {BRIDGE_PLAN_DOC}")


def bridge_refusal_message(config: Any, *, func: str = "", tool: str = "") -> str:
    """The refusal every landing path prints when a bridge config is selected."""
    bridge = bridge_of(config)
    where = f" {func}" if func else ""
    who = f"{tool}: " if tool else ""
    return (
        f"{who}BRIDGE LANDING REFUSED{where}: config {str(config)!r} selects "
        f"{bridge}, a per-function compiler (non-stock compiler directory or a "
        f"-fretail-/-fsn-/-fdriver- bridge flag). A row counts as matched only "
        f"if a stock cc1 + general-purpose maspsx produce the bytes from the "
        f"checked-in C. Re-close this function at one of the stock cells "
        f"({', '.join(sorted(STOCK_CELLS))}) and land that. "
        f"See {BRIDGE_PLAN_DOC}. "
        f"Override (audited, loud, and only for a sanctioned re-land of an "
        f"already-grandfathered row): AZURE_ALLOW_BRIDGE_LANDING=1."
    )


def bridge_landing_override_active(env: dict | None = None) -> bool:
    """The ONE escape hatch: env AZURE_ALLOW_BRIDGE_LANDING=1."""
    source = os.environ if env is None else env
    return str(source.get("AZURE_ALLOW_BRIDGE_LANDING", "")).strip() == "1"


# --------------------------------------------------------------------------- #
# the ASSEMBLER legs of the same defect
# --------------------------------------------------------------------------- #
# A per-function COMPILER is not the only way a name-keyed configuration can
# manufacture a byte match.  Workstream C measured the assembler side on
# 2026-09-05 (work/bridge_remediation_20260905/C_maspsx_nameblind/RESULTS.md):
#
#   leg 2 — a per-function maspsx DIAL.  ``config/overlays/<family>.as_flags.jsonl``
#     hands 49 landed MATCH rows a ``--retail-*`` option (mostly
#     ``--retail-func-<hex>-<tag>``, plus five per-site ones); 47 of the 49 stop
#     reproducing when it is stripped and nothing else changes (RESULTS §5).
#     ``tools/configure.py::AS_FLAGS`` does the same for 19 main-EXE TUs, and
#     19/19 are load-bearing (§6b).
#   leg 3 — a maspsx function-name TABLE with no flag at all: five dungeon rows
#     and two MAIN.BIN rows stop being exact under a name-blind maspsx whose
#     ``func_*`` tables are emptied (§2).  There is nothing in the row, the
#     config or the as-flags to read here, so the measured set is tracked in
#     ``config/bridge_burndown/asm_table_dependents.json`` and regenerated by
#     C's ``run_rescore.py`` — the ONE thing in this module that is a recorded
#     measurement rather than a live read.
#
# All three legs fail the same rule and get the same status: a row counts as
# matched only if a STOCK cc1 plus a GENERAL-PURPOSE maspsx produce the bytes
# from the checked-in C.
ASM_KEYED_FLAG_RE = re.compile(r"^--retail-")

ASM_TABLE_DEPENDENTS_PATH = "config/bridge_burndown/asm_table_dependents.json"

_ASM_TABLES: tuple[Any, dict[str, dict[str, Any]]] | None = None


def asm_table_dependents(root: Path | None = None) -> dict[str, dict[str, Any]]:
    """``{overlay: {func: {"tables": [...], ...}}}`` — the measured leg-3 set.

    Cached on the file's (mtime, size) so a dashboard pays one read.  A missing
    file is not an error: it means nothing has been measured yet, and every row
    falls through to "not keyed" exactly as before.
    """
    global _ASM_TABLES
    path = (root or ROOT) / ASM_TABLE_DEPENDENTS_PATH
    try:
        stat = path.stat()
        signature = (str(path), stat.st_mtime_ns, stat.st_size)
    except OSError:
        signature = (str(path), None, None)
    if _ASM_TABLES is not None and _ASM_TABLES[0] == signature:
        return _ASM_TABLES[1]
    try:
        data = json.loads(path.read_text(encoding="utf-8"))
    except (OSError, ValueError):
        data = {}
    rows = data.get("rows") if isinstance(data, dict) else None
    out: dict[str, dict[str, Any]] = {}
    for entry in rows or []:
        if not isinstance(entry, dict):
            continue
        overlay = str(entry.get("overlay") or "")
        func = str(entry.get("func") or "")
        if overlay and func:
            out.setdefault(overlay, {})[func] = entry
    _ASM_TABLES = (signature, out)
    return out


def resolved_as_flags(row: dict, overlay: str | None) -> str:
    """This row's per-function assembler options, via the ONE resolver.

    ``tools/overlay_as_flags.py`` is that resolver (LEAD 12b): it normalises the
    overlay to its container FAMILY (so ``dungeon_engine`` reads dungeon's
    table, which is right — it is a verbatim mirror), resolves region-qualified
    rather than by the shared bare slot label, and falls back to the main-EXE
    ``configure.py::AS_FLAGS`` route.  Re-implementing the lookup here would be
    a second chance to disagree about the same row, which is the exact defect
    that module was written to end.

    Imported lazily and never allowed to take a dashboard down: the resolver
    fails LOUDLY on ambiguous evidence (by design), but ``overlay_verdict`` runs
    over every row of every container on every render.  An unresolvable lookup
    is therefore reported as the sentinel ``"--retail-<unresolved>"`` — FAIL
    CLOSED, because "we could not tell" is not evidence of a stock build.
    """
    func = str(row.get("func_vram") or row.get("func") or row.get("name") or "")
    if not func:
        return ""
    try:
        tools_dir = str(Path(__file__).resolve().parent)
        if tools_dir not in sys.path:
            sys.path.insert(0, tools_dir)
        from overlay_as_flags import default_as_flags  # noqa: PLC0415
        return default_as_flags(func, overlay, row.get("true_name"),
                                foff=row.get("foff")) or ""
    except (Exception, SystemExit):
        return "--retail-<unresolved>"


def keyed_of(row: dict, *, overlay: str | None = None,
             as_flags: str | None = None) -> str | None:
    """Name the per-function keyed configuration this row's bytes needed.

    Returns, in precedence order:

    * the compiler bridge (``"gcc-<dir>"`` / ``"flags:<flag>"``) — see
      :func:`bridge_of`;
    * ``"asm:<token>"`` — the first ``--retail-*`` maspsx option the row's
      resolved as-flags carry;
    * ``"asm-table:<table>"`` — the row is in the measured set of maspsx
      function-name-TABLE dependents (no flag involved at all);
    * ``None`` — an honest stock + general-purpose-maspsx build.

    ``as_flags`` lets a caller that already resolved them (a landing path) pass
    them in rather than paying the lookup twice; ``None`` means "look them up".
    """
    bridge = bridge_of(row.get("config"))
    if bridge:
        return bridge
    flags = resolved_as_flags(row, overlay) if as_flags is None else str(as_flags or "")
    for token in flags.split():
        if ASM_KEYED_FLAG_RE.match(token):
            return f"asm:{token}"
    if overlay:
        entry = asm_table_dependents().get(overlay, {}).get(
            str(row.get("func_vram") or row.get("func") or row.get("name") or ""))
        if entry:
            tables = entry.get("tables") or []
            return "asm-table:" + (", ".join(str(t) for t in tables) or "unnamed")
    return None


def main_exe_as_flags(root: Path | None = None) -> dict[str, str]:
    """``{TU stem: as-flags}`` from ``tools/configure.py::AS_FLAGS``.

    The main-EXE analogue of ``config/overlays/<family>.as_flags.jsonl``.  Read
    as a literal by AST rather than by importing configure.py (which builds the
    whole ninja graph).  This is deliberately the RAW table keyed by TU stem:
    the ``src/w_<hex>.c -> func_<hex>`` derivation used for per-FUNCTION lookups
    stays in ``match.py`` (``DEFAULT_FUNC_AS_FLAGS``) and is reached through
    ``overlay_as_flags``; there is still exactly one copy of that rule.  What is
    needed here is the whole table, including TUs whose stem is not a function
    name, because the ratchet asks "does any TU carry a new per-function dial?".
    """
    import ast  # noqa: PLC0415 - stdlib, and only this function needs it
    path = (root or ROOT) / "tools" / "configure.py"
    try:
        tree = ast.parse(path.read_text(encoding="utf-8"), filename=str(path))
    except (OSError, SyntaxError):
        return {}
    for node in tree.body:
        if not isinstance(node, ast.Assign):
            continue
        if not any(isinstance(t, ast.Name) and t.id == "AS_FLAGS"
                   for t in node.targets):
            continue
        try:
            table = ast.literal_eval(node.value)
        except ValueError:
            return {}
        return {Path(str(cfile)).stem: str(flags or "")
                for cfile, flags in dict(table).items()}
    return {}


_MAIN_KEYED: tuple[Any, dict[str, str]] | None = None


def main_exe_keyed_funcs(root: Path | None = None) -> dict[str, str]:
    """``func_<HEX> -> keyed marker`` for main-EXE TUs that need a keyed layer.

    Two measured populations, both per TRANSLATION UNIT (the resident executable
    has no overlay row DB), from
    work/bridge_remediation_20260905/C_maspsx_nameblind/RESULTS.md §6/§6b:

    * a ``--retail-*`` option in ``tools/configure.py::AS_FLAGS`` — 19 TUs,
      19/19 load-bearing when stripped;
    * a TU whose object changes under a name-blind maspsx — 14 TUs, recorded in
      ``config/bridge_burndown/asm_table_dependents.json["main_exe"]["name_table"]``.

    Two TUs are in both and report the dial (the nearer cause).  Union: 31.
    Cached on the two files' (mtime, size) — the dashboard classifies ~1,100
    resident functions per render and must not re-parse configure.py each time.
    """
    global _MAIN_KEYED
    base = root or ROOT
    paths = (base / "tools" / "configure.py",
             base / ASM_TABLE_DEPENDENTS_PATH)
    signature = []
    for path in paths:
        try:
            stat = path.stat()
            signature.append((str(path), stat.st_mtime_ns, stat.st_size))
        except OSError:
            signature.append((str(path), None, None))
    key = tuple(signature)
    if _MAIN_KEYED is not None and _MAIN_KEYED[0] == key:
        return _MAIN_KEYED[1]

    out: dict[str, str] = {}
    try:
        document = json.loads(paths[1].read_text(encoding="utf-8"))
    except (OSError, ValueError):
        document = {}
    block = (document.get("main_exe") or {}) if isinstance(document, dict) else {}
    for src in block.get("name_table") or []:
        stem = str(src).rsplit("/", 1)[-1].removesuffix(".c")
        if stem.startswith("w_"):
            out[f"func_{stem[2:].upper()}"] = "asm-table:maspsx-name-tables"
    for stem, flags in main_exe_as_flags(base).items():
        if not stem.startswith("w_"):
            continue
        for token in str(flags or "").split():
            if ASM_KEYED_FLAG_RE.match(token):
                out[f"func_{stem[2:].upper()}"] = f"asm:{token}"
                break
    _MAIN_KEYED = (key, out)
    return out


def keyed_refusal_message(keyed: str, *, func: str = "", tool: str = "") -> str:
    """The refusal every landing path prints for ANY keyed leg."""
    if not keyed.startswith(("asm:", "asm-table:")):
        return bridge_refusal_message(keyed_config_hint(keyed), func=func, tool=tool)
    where = f" {func}" if func else ""
    who = f"{tool}: " if tool else ""
    if keyed.startswith("asm-table:"):
        what = (f"the maspsx function-name table(s) {keyed[len('asm-table:'):]} "
                f"(maspsx keys on this function's own name; no flag is passed, "
                f"so removing the dial is not enough — the table has to go)")
        fix = ("Re-close this function so a GENERAL-PURPOSE maspsx reproduces it, "
               "or replace the table with a corpus-validated general rule")
    else:
        what = (f"the per-function assembler dial {keyed[len('asm:'):]} "
                f"(a --retail-* maspsx option armed for this one function, from "
                f"config/overlays/<family>.as_flags.jsonl or "
                f"tools/configure.py::AS_FLAGS)")
        fix = "Re-close this function without the dial and land that"
    return (
        f"{who}KEYED LANDING REFUSED{where}: the bytes need {what}. A row counts "
        f"as matched only if a stock cc1 + general-purpose maspsx produce them "
        f"from the checked-in C. {fix}. See {BRIDGE_PLAN_DOC}. "
        f"Override (audited, loud, and only for a sanctioned re-land of an "
        f"already-grandfathered row): AZURE_ALLOW_BRIDGE_LANDING=1."
    )


def keyed_config_hint(keyed: str) -> str:
    """Recover a config-shaped label from a compiler-leg ``keyed_of`` answer."""
    if keyed.startswith("flags:"):
        return "2.7.2 " + keyed[len("flags:"):]
    return keyed[len("gcc-"):] if keyed.startswith("gcc-") else keyed


def keyed_reason(row: dict, keyed: str) -> str:
    """One line that says which layer produced the bytes, and where to look."""
    if keyed.startswith("asm-table:"):
        what = (f"per-function assembler name table {keyed[len('asm-table:'):]} "
                f"(maspsx keys on the function's own name; no flag is passed)")
    elif keyed.startswith("asm:"):
        what = (f"per-function assembler dial {keyed[len('asm:'):]} "
                f"(a maspsx option armed for this one function)")
    else:
        return bridged_reason(row, keyed)
    return (f"byte-exact only through {what}; not stock-exact — "
            f"see {BRIDGE_PLAN_DOC}")


# A row's ``frontier`` block: the LIVE, re-verified aligned distance of the best
# known candidate, as opposed to ``words_off`` — which is a frozen first-pass
# POSITIONAL number and is meaningless once a candidate drifts in length.  A
# 2296-byte row can read "448 words off" positionally while its best candidate is
# 189 aligned; the same row read "m2c empty" long after five campaign rounds had
# scored it, because its own first pass never produced a draft.
# Aligned distance is the metric every closeness claim in this project must use
# (tools/aligned_score.py), so it is what the truth layer reports.
#
# Required keys: aligned (int), config (str), candidate (repo-relative path),
# verified (ISO date).  Optional: subs, indels, sha256, devices, blocker, reopen.
# A block missing ``aligned`` or ``candidate`` is ignored rather than trusted —
# the frontier must be reproducible by re-running the named candidate, or it is
# just another stale number.
# A frontier that has reached aligned 0: the byte-exact C exists and is verified,
# but no source is landed under ``first_pass_matched/`` yet, so the row is not
# done.  Distinct from ``match/missing-source`` (which is a row whose SWEEP said
# MATCH and whose source went missing) — here the sweep never matched and the
# match came from campaign work that is waiting on an owner-run integrate.
STATUS_EXACT_UNLANDED = "exact/awaiting-land"


def frontier_of(row: dict) -> dict | None:
    """The row's re-verified aligned frontier, or None when it carries none."""
    block = row.get("frontier")
    if not isinstance(block, dict):
        return None
    aligned = block.get("aligned")
    if isinstance(aligned, bool) or not isinstance(aligned, int) or aligned < 0:
        return None
    if not str(block.get("candidate") or "").strip():
        return None
    return block


def frontier_reason(block: dict) -> str:
    """One line a reader can act on: distance, decomposition, and the blocker."""
    parts = [f"aligned {block['aligned']}"]
    subs, indels = block.get("subs"), block.get("indels")
    if isinstance(subs, int) and isinstance(indels, int):
        parts[0] += f" ({subs} subs + {indels} indels)"
    if block.get("config"):
        parts[0] += f" at {block['config']}"
    if block.get("verified"):
        parts[0] += f", re-verified {block['verified']}"
    if block.get("devices"):
        parts.append(f"devices: {block['devices']}")
    if block.get("blocker"):
        parts.append(str(block["blocker"]))
    if block.get("reopen"):
        parts.append(f"Reopen: {block['reopen']}")
    if block.get("candidate"):
        parts.append(f"Candidate: {block['candidate']}")
    return ". ".join(str(part).rstrip(".") for part in parts) + "."


# --------------------------------------------------------------------------- #
# terminal precedence reducer (deliverable 1)
# --------------------------------------------------------------------------- #
def overlay_verdict(
    row: dict,
    *,
    has_source: bool,
    window: dict | None = None,
    window_aware: bool = True,
    oracle: dict | None = None,
    overlay: str | None = None,
) -> tuple[str, str, str]:
    """The one canonical ``(state, status, reason)`` for an overlay row.

    Precedence, strongest evidence first:

    1. a confirmed ``data_segment`` becomes ``data`` (never a code lane);
    1b. a confirmed ``bios_stub`` becomes ``parked``/``bios-stub`` (never an
       asm->C lane) — like ``data_segment`` this is a row IDENTITY, not a
       diagnosis, so it outranks the exact/park ladder below;
    1c. a confirmed ``hand_asm`` becomes ``parked``/``hand-asm`` for the same
       reason: hand-written game assembly with a non-C retail ABI;
    2. a verified-exact result (``MATCH`` / resweep ``MATCH``) with a landed
       source is terminally ``done`` — this OUTRANKS any later park marker (the
       23-row plateau-vs-MATCH defect);
    3. a fresh oracle-exact record is surfaced as a recovered row **before** the
       park diagnosis, so a park self-heals after a relevant instrument change;
    4. only then is an owner/plateau ``parked`` marker honoured;
    5. NOMATCH / CFAIL / M2C_FAIL fall through as before.

    ``window_aware`` distinguishes the overlay planner (which knows the gate
    window and can label ``gate-verified`` / ``match/outside-current-gate``) from
    the lean dashboard (which does not carry a window).
    """
    result = str(row.get("result") or "").upper()
    resweep = str(row.get("result_resweep") or "").upper()
    exact_result = result == "MATCH" or resweep == "MATCH"

    # 1 — data segment: its own inventory, never code work.
    if row.get("data_segment"):
        return STATE_DATA, "data-segment", _note(row, "confirmed data, not code")

    # 1b — PSY-Q BIOS vector stub: real code, but permanently outside the asm->C
    # lane (see STATUS_BIOS_STUB).  These rows ARE byte-exact and gate-verified
    # via checked-in asm/psyq assembly, so without this rule the exact branch
    # below reads them as ``wip``/``match/missing-source`` — i.e. as six open
    # candidates with a lost C source — and every wave picker dispatches them
    # (observed on TOWN func_802F1644..CC, 2026-08-10).  Parked keeps them
    # counted, visible, and carrying their port instructions.
    if row.get("bios_stub"):
        return STATE_PARKED, STATUS_BIOS_STUB, bios_stub_reason(row)

    # 1c — hand-written game assembly: same identity precedence, same reason.
    if row.get("hand_asm"):
        return STATE_PARKED, STATUS_HAND_ASM, hand_asm_reason(row)

    # 1d — BRIDGED: the row's MATCH/resweep-MATCH was produced by a PER-FUNCTION
    # KEYED configuration rather than by a stock cc1 + general-purpose maspsx —
    # a compiler bridge, a ``--retail-*`` assembler dial, or a maspsx
    # function-name table (see STATUS_BRIDGED and :func:`keyed_of`).  This must
    # sit ABOVE rule 2, because rule 2 is terminal: once a landed source plus an
    # exact result is seen the row can never be re-examined, and that is exactly
    # how 79 DUNGEON rows read "done / gate-verified" on a dashboard that had no
    # way to know the bytes came from a text-edit of the assembly.  It sits BELOW
    # the three identity rules because those are about what a row IS (data, a
    # BIOS vector stub, hand-written assembly) — a BIOS stub records
    # ``platform-asm`` in its config field and names no compiler at all.
    # Not a park: this is open decomp work with a known next step (close it at a
    # stock cell / without the dial; tools/bridge_census.py tracks the
    # burn-down), so ``wip``.
    if exact_result:
        keyed = keyed_of(row, overlay=overlay)
        if keyed:
            return STATE_WIP, STATUS_BRIDGED, keyed_reason(row, keyed)

    # 2 — terminal exact: landed source + exact result beats every park marker.
    if exact_result:
        if has_source:
            if window_aware:
                gateable = _is_gateable(row, window)
                if gateable and row.get("gate_verified"):
                    status = "gate-verified"
                elif not gateable:
                    status = "match/outside-current-gate"
                else:
                    status = "MATCH"
            else:
                status = "gate-verified" if row.get("gate_verified") else "MATCH"
            return STATE_DONE, status, "byte-exact sweep match; landed C source exists"
        return (STATE_WIP, "match/missing-source",
                "row says MATCH but first_pass_matched source is missing")

    # 3 — fresh oracle exact: recovered, surfaced before the park (self-heal).
    if oracle is not None and oracle.get("exact") is True:
        return (STATE_WIP, "oracle-exact-recovered",
                "fresh compact-oracle proves byte-exact; re-audit/land "
                "(prior park superseded by a newer instrument)")

    # 4 — owner/plateau park (data handled above; exact handled above).
    if row.get("data_segment"):  # defensive; already returned
        return STATE_DATA, "data-segment", _note(row, "confirmed data, not code")
    if row.get("parked"):
        return STATE_PARKED, str(row.get("parked")), _note(row, "owner-parked")

    # 4b — a re-verified aligned frontier outranks the frozen first-pass residue
    # ladder below.  Without this a row that five campaign rounds drove to two
    # words still reads as its original first-pass verdict ("m2c-fail /
    # m2c empty", or a positional "175 word(s) off" measured on a candidate that
    # no longer exists).  Such a row is unambiguously wip: a named candidate
    # compiles and scores, it just is not exact yet.
    frontier = frontier_of(row)
    if frontier is not None:
        # aligned 0 is a byte-exact candidate that has not been landed yet.  It
        # is NOT done — done requires a landed source under first_pass_matched/
        # — but calling it "near-0" would read as a rounding artifact rather
        # than as the actionable state it is: the C exists, someone has to
        # integrate it.
        status = (STATUS_EXACT_UNLANDED if frontier["aligned"] == 0
                  else f"near-{frontier['aligned']}")
        return STATE_WIP, status, frontier_reason(frontier)

    # 5 — the ordinary residue ladder.
    words = _words_off(row)
    if result == "NOMATCH":
        if words is not None:
            return (STATE_WIP, f"near-{words}",
                    f"{words} word(s) off at {row.get('config') or '?'}")
        return STATE_WIP, "nomatch", "compiled but did not byte-match"
    if result == "CFAIL":
        return STATE_TODO, "cfail", "warm C draft failed to compile"
    if result == "M2C_FAIL":
        return (STATE_TODO, "m2c-fail",
                _note(row, "m2c did not produce a usable draft"))
    return STATE_TODO, result.lower() or "unknown", _note(row)


def main_verdict(row: dict, *, oracle: dict | None = None) -> tuple[str, str, str]:
    """Canonical verdict for a resident-executable progress row.

    Main progress state comes from the live INCLUDE_ASM scan plus status.tsv;
    overlay result/window semantics do not apply.  A fresh exact oracle still
    self-heals an older park before the stored state is honoured.
    """
    if row.get("data_segment") or row.get("state") == STATE_DATA:
        return STATE_DATA, "data-segment", _note(row, "confirmed data, not code")
    # Same rule 1d as overlay_verdict, on the resident executable's own evidence:
    # a TU that needs a --retail-* maspsx dial or a maspsx function-name table is
    # not stock-exact, however green the build is.
    func = str(row.get("name") or row.get("func") or "")
    keyed = main_exe_keyed_funcs().get(func.upper().replace("FUNC_", "func_"))
    if keyed and str(row.get("state") or "") == STATE_DONE:
        return STATE_WIP, STATUS_BRIDGED, keyed_reason(row, keyed)
    if oracle is not None and oracle.get("exact") is True:
        if row.get("state") == STATE_DONE:
            return STATE_DONE, "MATCH", "resident function is landed and byte-exact"
        return (STATE_WIP, "oracle-exact-recovered",
                "fresh compact-oracle proves byte-exact; re-audit/land")
    state = str(row.get("state") or STATE_TODO)
    if state not in CODE_STATES:
        state = STATE_TODO
    status = str(row.get("status") or ("unstarted" if state == STATE_TODO else state))
    return state, status, str(row.get("reason") or row.get("note") or "")


def is_terminal_exact(
    row: dict,
    landed_sources: set[str] | None = None,
    *,
    source_exists_fn: Callable[[str], bool] | None = None,
) -> bool:
    """True when a plateau park must never be written onto this row (deliverable
    1: S7 never parks MATCH/landed).

    A ``MATCH`` (or resweep ``MATCH``) result is exact evidence on its own; a
    landed source makes it terminally done.  Either is enough to refuse a park.

    Deliberately unchanged for a BRIDGED row (:data:`STATUS_BRIDGED`): it IS
    byte-exact and its landed C IS the best source anyone has, so writing a
    plateau park over it would still destroy evidence.  ``overlay_verdict``
    already downgrades it out of ``done``, which is where the honest count is
    made; this guard is only about not clobbering the row.
    """
    result = str(row.get("result") or "").upper()
    resweep = str(row.get("result_resweep") or "").upper()
    if result == "MATCH" or resweep == "MATCH":
        return True
    func = str(row.get("func_vram") or row.get("func") or row.get("name") or "")
    if landed_sources is not None and func in landed_sources:
        return True
    if source_exists_fn is not None and func:
        try:
            return bool(source_exists_fn(func))
        except Exception:
            return False
    return False


# --------------------------------------------------------------------------- #
# current-score / current-state service (deliverable 2)
# --------------------------------------------------------------------------- #
def _aligned_total(oracle: dict | None) -> int | None:
    if not isinstance(oracle, dict):
        return None
    aligned = oracle.get("aligned")
    if isinstance(aligned, dict):
        total = aligned.get("total")
        if isinstance(total, int):
            return total
    total = oracle.get("aligned_total")
    return total if isinstance(total, int) else None


def census_score(request: dict, cache_dir: Path = DEFAULT_CACHE) -> tuple[int | None, dict]:
    """Current-epoch compact-oracle score for a request.

    The census cache is content-addressed on ``cache_key`` = (source, target,
    config, compiler, oracle-tool fingerprint).  A hit therefore *is* the current
    tool/evidence epoch.  A miss means no current-epoch score exists — the caller
    must not substitute a stale-epoch or legacy number as if it were live.  A
    record filed under a different (older) tool epoch has a different key and is,
    correctly, a miss here.
    """
    key = request.get("cache_key")
    if not request.get("runnable"):
        return None, {"cache_status": "not-runnable"}
    if not key:
        return None, {"cache_status": "miss"}
    path = Path(cache_dir) / f"{key}.json"
    try:
        record = json.loads(path.read_text())
    except (OSError, ValueError):
        return None, {"cache_status": "miss"}
    if record.get("cache_key") != key or not isinstance(record.get("oracle"), dict):
        return None, {"cache_status": "invalid"}
    oracle = record["oracle"]
    return _aligned_total(oracle), {
        "cache_status": "hit",
        "exact": oracle.get("exact") is True,
        "created_at": record.get("created_at"),
        "positional_words_off": oracle.get("positional_words_off"),
        "residue_class": ((oracle.get("residue") or {}).get("class")
                          if isinstance(oracle.get("residue"), dict) else None),
        "oracle": oracle,
    }


def current_score(
    row: dict,
    request: dict | None,
    cache_dir: Path = DEFAULT_CACHE,
) -> dict:
    """The one current-score answer, with an explicitly labelled legacy fallback.

    Primary = the current census-cache record (current tool/evidence epoch).
    Fallback = the frozen first-pass row ``words_off``, labelled ``source:
    legacy-words-off`` with its age so no caller mistakes it for a live number.
    When a score existed but not under the current epoch, ``needs_reverify`` is
    set so a scheduler re-scores instead of trusting a stale base (the
    zq_permsweep stale-base regressions).
    """
    meta: dict = {"cache_status": "not-runnable"}
    aligned = None
    if request is not None:
        aligned, meta = census_score(request, cache_dir)

    if meta.get("cache_status") == "hit":
        return {
            "value": aligned,
            "source": "census-cache",
            "epoch": "current",
            "stale": False,
            "needs_reverify": False,
            "exact": bool(meta.get("exact")),
            "residue_class": meta.get("residue_class"),
            "positional_words_off": meta.get("positional_words_off"),
            "created_at": meta.get("created_at"),
            "cache_status": "hit",
        }

    legacy = _words_off(row)
    # An attempt frontier is a second, still-non-live source of evidence.
    attempt_aligned = _best_attempt_aligned(row)
    had_prior_score = legacy is not None or attempt_aligned is not None
    return {
        "value": legacy if legacy is not None else attempt_aligned,
        "source": "legacy-words-off" if legacy is not None else (
            "attempt-aligned" if attempt_aligned is not None else None),
        "epoch": "frozen-first-pass" if legacy is not None else (
            "prior-attempt" if attempt_aligned is not None else None),
        "stale": had_prior_score,
        # No current-epoch score, but a prior score existed: re-verify rather
        # than route on the stale number.
        "needs_reverify": had_prior_score,
        "exact": False,
        "residue_class": None,
        "cache_status": meta.get("cache_status", "miss"),
    }


def _best_attempt_aligned(row: dict) -> int | None:
    best: int | None = None
    for attempt in row.get("prior_attempts") or []:
        if not isinstance(attempt, dict):
            continue
        aligned = attempt.get("best_aligned")
        if not isinstance(aligned, dict):
            score = attempt.get("score")
            aligned = score.get("aligned") if isinstance(score, dict) else None
        total = aligned.get("total") if isinstance(aligned, dict) else None
        if isinstance(total, int) and (best is None or total < best):
            best = total
    return best


def _best_candidate(row: dict, score: dict) -> dict:
    """Carry the current best candidate and its winning/banked config together,
    rather than reconstructing it from whichever results file a caller reads.

    A landed/exact row's candidate is its ``c_path`` at the row config.  Below
    that, the lowest-aligned prior attempt owns a durable ``best_candidate_path``
    plus the compiler config it was proven under (which may differ from the row's
    first-pass config)."""
    result = str(row.get("result") or "").upper()
    if result == "MATCH" and row.get("c_path"):
        return {
            "source": row.get("c_path"),
            "sha256": row.get("c_sha256") or row.get("candidate_sha256"),
            "config": row.get("config"),
            "provenance": "landed-match-row",
        }
    best_attempt = None
    best_total = None
    for attempt in row.get("prior_attempts") or []:
        if not isinstance(attempt, dict) or not attempt.get("best_candidate_path"):
            continue
        aligned = attempt.get("best_aligned")
        if not isinstance(aligned, dict):
            s = attempt.get("score")
            aligned = s.get("aligned") if isinstance(s, dict) else None
        total = aligned.get("total") if isinstance(aligned, dict) else None
        if isinstance(total, int) and (best_total is None or total < best_total):
            best_total, best_attempt = total, attempt
    if best_attempt is not None:
        return {
            "source": best_attempt.get("best_candidate_path"),
            "sha256": best_attempt.get("best_candidate_sha256"),
            "config": best_attempt.get("compiler_config") or row.get("config"),
            "provenance": "attempt-frontier",
        }
    return {
        "source": row.get("c_path"),
        "sha256": row.get("candidate_sha256"),
        "config": row.get("config"),
        "provenance": "first-pass-row",
    }


def _gate_artifact_version(gate_config: str | None) -> str | None:
    """A short content hash of the gate YAML so a stale gate_config is detectable."""
    if not gate_config:
        return None
    import hashlib
    path = Path(gate_config)
    if not path.is_absolute():
        path = ROOT / path
    try:
        return hashlib.sha256(path.read_bytes()).hexdigest()[:12]
    except OSError:
        return None


def current_state(
    scope: str,
    row: dict,
    request: dict | None = None,
    cache_dir: Path = DEFAULT_CACHE,
    *,
    window: dict | None = None,
    landed_sources: set[str] | None = None,
    source_exists_fn: Callable[[str], bool] | None = None,
    binary_kind: str | None = None,
) -> dict:
    """The full current-state record for one function, carrying together:
    the canonical reducer verdict, the current score (census-first, legacy
    labelled), the current best candidate + winning/banked config, live
    gateability + gate-config artifact version, and whether a stored score's
    epoch is stale enough to force re-verification.

    ``row`` may be a raw consolidated results row (``func_vram`` …) or an
    ``overlay_status.function_rows`` projection (``name``/``gateable`` …); this
    tolerates both so the campaign controller can pass whichever it holds.
    """
    raw_scope = str(scope)
    if binary_kind is None:
        legacy_overlay_main_row = (
            raw_scope == SCOPE_MAIN
            and row.get("func_vram") is not None
            and ("result" in row or "foff" in row)
        )
        if (row.get("overlay") is not None
                or raw_scope.startswith(SCOPE_OVERLAY_PREFIX)
                or legacy_overlay_main_row):
            binary_kind = "overlay"
        elif raw_scope in (SCOPE_MAIN, "slus", "resident", "main-exe"):
            binary_kind = "main"
        else:
            binary_kind = "overlay"  # legacy bare overlay display name
    if binary_kind == "main":
        scope = SCOPE_MAIN
    else:
        overlay_name = (raw_scope[len(SCOPE_OVERLAY_PREFIX):]
                        if raw_scope.startswith(SCOPE_OVERLAY_PREFIX)
                        else str(row.get("overlay") or raw_scope))
        scope = canonical_scope(overlay=overlay_name, binary_kind="overlay")
    func = str(row.get("func_vram") or row.get("name") or row.get("func") or "")
    if landed_sources is not None:
        has_source = func in landed_sources
    elif source_exists_fn is not None:
        has_source = bool(source_exists_fn(func)) if func else False
    else:
        has_source = str(row.get("result") or "").upper() == "MATCH" and bool(
            row.get("c_path"))

    score = current_score(row, request, cache_dir)
    oracle = None
    if isinstance((request or {}), dict) and score.get("cache_status") == "hit":
        # Re-read the oracle for the reducer's fresh-exact self-heal path.
        _val, meta = census_score(request, cache_dir)
        oracle = meta.get("oracle")

    is_main = binary_kind == "main" or scope == SCOPE_MAIN
    if is_main:
        state, status, reason = main_verdict(row, oracle=oracle)
    else:
        # function_rows projections carry the already-reduced parked/data state
        # rather than the raw ``parked``/``data_segment`` marker.  Reconstruct
        # only those explicit markers before applying the same reducer.
        verdict_row = row
        projected = row.get("state")
        if projected in (STATE_PARKED, STATE_DATA):
            verdict_row = dict(row)
            if projected == STATE_PARKED:
                verdict_row["parked"] = row.get("status") or "parked"
            else:
                verdict_row["data_segment"] = True
        state, status, reason = overlay_verdict(
            verdict_row, has_source=has_source, window=window,
            window_aware=window is not None or "gateable" in row, oracle=oracle)
        # The reducer still needs the raw row for terminal/park/CFAIL
        # precedence, but a current non-exact census score must also own the
        # displayed WIP distance.  Otherwise routing reads aligned=12 while the
        # inventory tells humans "near-7" from the frozen first-pass snapshot.
        # Never use this presentation refresh to override a park or terminal.
        current_distance = score.get("value")
        if (state == STATE_WIP and status.startswith("near-")
                and score.get("source") == "census-cache"
                and isinstance(current_distance, int)
                and not isinstance(current_distance, bool)
                and not score.get("exact")):
            status = f"near-{current_distance}"
            positional = score.get("positional_words_off")
            reason = f"current aligned distance {current_distance}"
            if isinstance(positional, int) and not isinstance(positional, bool):
                reason += f"; positional distance {positional}"
            config = (request or {}).get("config") if isinstance(request, dict) else None
            if config:
                reason += f" at {config}"

    gate_config = (row.get("gate_config")
                   or (window.get("config") if window else None))
    gateable = True if is_main else row.get("gateable")
    if gateable is None:
        gateable = _is_gateable(row, window)

    candidate = _best_candidate(row, score)
    if not candidate.get("source") and isinstance(request, dict):
        candidate = {
            "source": request.get("candidate"),
            "sha256": request.get("source_sha256"),
            "config": request.get("config"),
            "provenance": "census-request",
        }

    return {
        "scope": scope,
        "func": func,
        "logical_identity": (row.get("logical_identity")
                             or row.get("_logical_identity")),
        "size": int(row.get("size") or 0),
        "state": state,
        "status": status,
        "reason": reason,
        "inventory": inventory_of(state, bool(row.get("data_segment"))),
        "terminal": state in (STATE_DONE, STATE_DATA),
        "score": score,
        "best_candidate": candidate,
        "gateability": {
            "gateable": bool(gateable),
            "gate_config": gate_config,
            "config_artifact_version": _gate_artifact_version(gate_config),
        },
        "needs_reverify": bool(score.get("needs_reverify")),
    }


# --------------------------------------------------------------------------- #
# instrument-triggered revalidation hook (deliverable 4 — stub entry point)
# --------------------------------------------------------------------------- #
@dataclass
class RevalidationTarget:
    """Data shape a later wave's full re-scoring loop will consume."""
    scope: str
    func: str
    reason: str
    changed_instruments: list[str] = field(default_factory=list)
    lead_hint: str | None = None
    residue_class: str | None = None
    needs_reverify: bool = True


def instrument_revalidation_targets(
    entries: list[dict],
    changed_instruments: list[str],
    *,
    affects: Callable[[dict], bool] | None = None,
) -> list[RevalidationTarget]:
    """Entry point (data shape now; full re-run loop lands in TF-9M) for
    re-scoring banked/parked candidates whose residue signature a newly landed
    instrument affects.

    ``entries`` are current-state records (or classification rows).  A candidate
    is a target when it is parked or banked (a stored non-live score) AND either
    the caller-supplied ``affects`` predicate matches or no predicate is given
    (default: every parked/banked row is a conservative candidate).  The default
    predicate is deliberately inclusive: over-revalidation is cheap and safe,
    silent occlusion of a recovered exact row is the expensive failure this
    hook exists to prevent.
    """
    targets: list[RevalidationTarget] = []
    for entry in entries:
        state = entry.get("state")
        score = entry.get("score") or {}
        banked = bool(score.get("stale") or score.get("needs_reverify"))
        if state != STATE_PARKED and not banked:
            continue
        # A BIOS stub is the one park no instrument can ever recover: its wall
        # is the jr delay-slot schedule, which no compiler/flag/oracle change
        # can make a policy-compliant C form emit.  Re-scoring it forever is
        # pure waste, so the inclusive default stops here.
        if entry.get("bios_stub") or entry.get("status") == STATUS_BIOS_STUB:
            continue
        # Same for hand-written game assembly: its wall is the retail ABI, not
        # a compiler configuration, so no instrument change can recover it.
        if entry.get("hand_asm") or entry.get("status") == STATUS_HAND_ASM:
            continue
        if affects is not None and not affects(entry):
            continue
        targets.append(RevalidationTarget(
            scope=str(entry.get("scope") or ""),
            func=str(entry.get("func") or entry.get("name") or ""),
            reason="instrument-changed",
            changed_instruments=list(changed_instruments),
            lead_hint=entry.get("lead_hint"),
            residue_class=(entry.get("residue_class")
                           or score.get("residue_class")),
        ))
    return targets


# --------------------------------------------------------------------------- #
# GCC diagnostic capture (deliverable 5)
# --------------------------------------------------------------------------- #
_GCC_LOC_RE = re.compile(r"^[^\s:][^:]*:\d+:")


def gcc_diagnostic(blob: Any, *, max_chars: int = 400, max_lines: int = 6) -> str:
    """Preserve the first ``file:line:`` diagnostic and a bounded multi-line tail.

    Old GCC 2.x has no ``error:`` prefix and leads with a multi-line
    ``In function `foo':`` banner, so a blind leading 120-char slice usually keeps
    only boilerplate and discards the actual defect line.  This finds the first
    real ``file:line:`` diagnostic, keeps a few following lines for context, and
    otherwise falls back to the tail (where the real error usually is)."""
    if isinstance(blob, (bytes, bytearray)):
        blob = bytes(blob).decode("utf-8", "replace")
    lines = [ln.rstrip() for ln in str(blob).splitlines() if ln.strip()]
    if not lines:
        return ""
    first = next((i for i, ln in enumerate(lines) if _GCC_LOC_RE.search(ln)), None)
    if first is None:
        picked = lines[-max_lines:]
    else:
        picked = lines[first:first + max_lines]
    text = " | ".join(picked)
    if len(text) > max_chars:
        text = text[: max_chars - 1] + "…"
    return text


# --------------------------------------------------------------------------- #
# one-command reconciliation report (deliverable 7)
# --------------------------------------------------------------------------- #
def all_binary_inventory(cache_dir: Path = DEFAULT_CACHE) -> dict:
    """Return canonical current truth for resident main plus headline overlays.

    This is the shared inventory boundary for economics and future planners.
    Rows are keyed by explicit ``(scope, func, logical_identity)`` identities,
    so resident ``main`` and ``overlay:main`` cannot collide and split rows
    sharing a display label remain distinct. Terminal and data rows stay
    present and labelled; consumers decide whether to filter them.
    """
    import oracle_census
    import overlay_status
    import progress

    selector = oracle_census.dossier_select.DossierSelector(ROOT)
    requests = (oracle_census.main_inventory(selector)
                + oracle_census.overlay_inventory(selector))

    def identity_key(scope: str, func: str, logical: Any = None) -> tuple:
        # Split/repair metadata can temporarily contain two physical rows with
        # one legacy function label.  Container-qualified logical identity is
        # the discriminator; resident functions are already globally named.
        if isinstance(logical, (list, tuple)):
            logical = tuple(str(part) for part in logical)
        else:
            logical = None
        return scope, func, logical

    request_map = {}
    for request in requests:
        scope = str(request.get("scope") or
                    (SCOPE_MAIN if request.get("overlay") is None
                     else f"{SCOPE_OVERLAY_PREFIX}{request.get('overlay')}"))
        logical = (request.get("target") or {}).get("logical_identity")
        key = identity_key(scope, str(request.get("func") or ""), logical)
        if key in request_map:
            raise ValueError(f"duplicate census request identity: {key!r}")
        request_map[key] = request

    rows = []
    main = progress.main_binary()
    for row in main.get("functions") or []:
        scope = SCOPE_MAIN
        request = request_map.get(identity_key(scope, str(row.get("name") or "")))
        current = current_state(
            scope, row, request, cache_dir, binary_kind="main")
        rows.append({**current, "binary_kind": "main", "request": request})

    for overlay, meta in sorted(overlay_status.discover_overlays().items()):
        if not meta.get("headline", True):
            continue
        scope = canonical_scope(overlay=overlay, binary_kind="overlay")
        for row in overlay_status.function_rows(overlay):
            request = request_map.get(identity_key(
                scope, str(row.get("name") or ""), row.get("logical_identity")))
            current = current_state(
                scope, row, request, cache_dir, binary_kind="overlay")
            rows.append({**current, "binary_kind": "overlay", "request": request})

    identities = [identity_key(row["scope"], row["func"],
                               row.get("logical_identity")) for row in rows]
    if len(set(identities)) != len(identities):
        duplicates = sorted(
            {item for item in identities if identities.count(item) > 1},
            key=repr,
        )
        raise ValueError(f"duplicate live function identities: {duplicates[:10]}")

    by_scope: dict[str, dict[str, int]] = {}
    for row in rows:
        bucket = by_scope.setdefault(row["scope"], {
            "code_funcs": 0, "code_bytes": 0,
            "remaining_funcs": 0, "remaining_bytes": 0,
            "data_funcs": 0, "data_bytes": 0,
        })
        size = int(row.get("size") or 0)
        if row["inventory"] == INVENTORY_DATA:
            bucket["data_funcs"] += 1
            bucket["data_bytes"] += size
            continue
        bucket["code_funcs"] += 1
        bucket["code_bytes"] += size
        if not row["terminal"]:
            bucket["remaining_funcs"] += 1
            bucket["remaining_bytes"] += size

    totals = {
        key: sum(scope[key] for scope in by_scope.values())
        for key in ("code_funcs", "code_bytes", "remaining_funcs",
                    "remaining_bytes", "data_funcs", "data_bytes")
    }
    rows.sort(key=lambda row: (
        row["scope"], row["func"],
        json.dumps(row.get("logical_identity"), sort_keys=True,
                   separators=(",", ":")),
    ))
    return {
        "schema": "azure-clean.live-truth.inventory.v1",
        "identity": "(canonical scope, function, optional container logical identity)",
        "rows": rows,
        "by_scope": {key: by_scope[key] for key in sorted(by_scope)},
        "totals": totals,
    }


def _reduce_main_scope() -> dict:
    """Reduce resident progress rows and cross-check the incomplete census."""
    import oracle_census
    import progress

    binary = progress.main_binary()
    functions = binary.get("functions") or []
    code = [row for row in functions if row.get("state") != STATE_DATA]
    done = [row for row in code if row.get("state") == STATE_DONE]
    data = [row for row in functions if row.get("state") == STATE_DATA]
    selector = oracle_census.dossier_select.DossierSelector(ROOT)
    census = oracle_census.main_inventory(selector)
    census_funcs = len(census)
    census_bytes = sum(int(row.get("size") or 0) for row in census)
    remaining_funcs = len(code) - len(done)
    remaining_bytes = (sum(int(row.get("size") or 0) for row in code)
                       - sum(int(row.get("size") or 0) for row in done))
    # The oracle census answers a NARROWER question than "remaining": it
    # inventories functions that still carry INCLUDE_ASM.  A BRIDGED row does
    # not — its C is landed and the build is green; what it lacks is a stock
    # toolchain that reproduces the bytes.  Comparing the two totals directly
    # would report a permanent, meaningless disagreement, so the cross-check is
    # made like-for-like and the keyed mass is reported separately.
    bridged = [row for row in code if row.get("status") == STATUS_BRIDGED]
    bridged_bytes = sum(int(row.get("size") or 0) for row in bridged)
    return {
        "scope": SCOPE_MAIN,
        "display_scope": "slus",
        "code_funcs": len(code),
        "code_bytes": sum(int(row.get("size") or 0) for row in code),
        "done_funcs": len(done),
        "done_bytes": sum(int(row.get("size") or 0) for row in done),
        "remaining_funcs": remaining_funcs,
        "remaining_bytes": remaining_bytes,
        "data_funcs": len(data),
        "data_bytes": sum(int(row.get("size") or 0) for row in data),
        "le15_open": 0,
        "parked_landed_violations": [],
        "bridged_funcs": len(bridged),
        "bridged_bytes": bridged_bytes,
        "census_remaining_funcs": census_funcs,
        "census_remaining_bytes": census_bytes,
        "census_agrees": (census_funcs == remaining_funcs - len(bridged)
                          and census_bytes == remaining_bytes - bridged_bytes),
    }


def _reduce_overlay_scope(overlay: str) -> dict:
    """Reduce one overlay's raw rows directly, independent of progress/overlay_status
    projection code paths, so the reconcile is a genuine cross-check."""
    import overlay_status

    rows = overlay_status.load_rows(overlay)
    windows = overlay_status.gate_windows(overlay)
    source_dir = overlay_status.cfg_path(overlay_status.OVERLAYS[overlay]["source_dir"])
    landed = {p.stem for p in source_dir.glob("*.c")}
    code_funcs = code_bytes = done_funcs = done_bytes = 0
    data_funcs = data_bytes = 0
    parked_landed = []
    le15 = 0
    for row in rows:
        func = str(row.get("func_vram") or "")
        if not func:
            continue
        window = overlay_status.containing_window(row, windows)
        state, status, _ = overlay_verdict(
            row, has_source=func in landed, window=window, window_aware=True,
            overlay=overlay)
        size = int(row.get("size") or 0)
        if state == STATE_DATA:
            data_funcs += 1
            data_bytes += size
            continue
        code_funcs += 1
        code_bytes += size
        if state == STATE_DONE:
            done_funcs += 1
            done_bytes += size
        elif status != STATUS_BRIDGED:
            # A bridged row's words_off is 0 at the per-function compiler that
            # landed it and unknown at any stock cell, so it is not a near-miss
            # — it is a burn-down row (tools/bridge_census.py).
            words = _words_off(row)
            if isinstance(words, int) and words <= 15:
                le15 += 1
        # Invariant: a landed exact row must never read as parked.  A BIOS
        # stub and a hand-written game-assembly row are the two honest
        # exceptions: each is exact BY WAY OF checked-in assembly, and its park
        # is an identity ("no C representation exists; a port must implement
        # it"), not a plateau diagnosis written over exact evidence — which is
        # the defect this invariant guards.
        if (state == STATE_PARKED and not row.get("bios_stub")
                and not row.get("hand_asm")
                and is_terminal_exact(row, landed)):
            parked_landed.append(func)
    return {
        "scope": canonical_scope(overlay=overlay, binary_kind="overlay"),
        "display_scope": overlay,
        "code_funcs": code_funcs,
        "code_bytes": code_bytes,
        "done_funcs": done_funcs,
        "done_bytes": done_bytes,
        "remaining_funcs": code_funcs - done_funcs,
        "remaining_bytes": code_bytes - done_bytes,
        "data_funcs": data_funcs,
        "data_bytes": data_bytes,
        "le15_open": le15,
        "parked_landed_violations": parked_landed,
    }


def reconcile(scopes: list[str] | None = None) -> dict:
    """Reconcile resident main and overlays against every projection consumer.

    Canonical scope spelling is ``main`` or ``overlay:<name>``.  Legacy bare
    overlay names remain accepted; legacy ``slus`` maps to resident main.
    """
    import overlay_status
    import progress

    if scopes is None:
        scopes = [SCOPE_MAIN] + [
            canonical_scope(overlay=name, binary_kind="overlay")
            for name, meta in sorted(overlay_status.discover_overlays().items())
            if meta.get("headline", True)
        ]
    else:
        scopes = [canonical_scope(legacy_scope=scope) for scope in scopes]

    prog_binaries = {b["id"]: b for b in progress.overlay_binaries()}
    per_scope = []
    disagreements = []
    parked_landed_total = []
    for scope in scopes:
        if scope == SCOPE_MAIN:
            canonical = _reduce_main_scope()
            agree = bool(canonical["census_agrees"])
            if not agree:
                disagreements.append({
                    "scope": scope,
                    "canonical": {"remaining_funcs": canonical["remaining_funcs"],
                                  "remaining_bytes": canonical["remaining_bytes"]},
                    "oracle_census": {
                        "remaining_funcs": canonical["census_remaining_funcs"],
                        "remaining_bytes": canonical["census_remaining_bytes"],
                    },
                })
            per_scope.append({**canonical, "overlay_status_le15": None,
                              "consumers_agree": agree})
            continue

        overlay = scope[len(SCOPE_OVERLAY_PREFIX):]
        canonical = _reduce_overlay_scope(overlay)
        summ = overlay_status.summary(overlay)
        prog = prog_binaries.get(overlay, {})
        # progress and overlay_status remaining = total(code) - done(code).
        s_remaining_funcs = summ.get("total_funcs", 0) - summ.get("done_funcs", 0)
        s_remaining_bytes = summ.get("total_bytes", 0) - summ.get("done_bytes", 0)
        p_remaining_funcs = prog.get("total_funcs", 0) - prog.get("done_funcs", 0)
        p_remaining_bytes = prog.get("total_bytes", 0) - prog.get("done_bytes", 0)
        agree = (
            s_remaining_funcs == canonical["remaining_funcs"] ==
            (p_remaining_funcs if prog else canonical["remaining_funcs"])
            and s_remaining_bytes == canonical["remaining_bytes"] ==
            (p_remaining_bytes if prog else canonical["remaining_bytes"])
        )
        if not agree:
            disagreements.append({
                "scope": scope,
                "canonical": {"remaining_funcs": canonical["remaining_funcs"],
                              "remaining_bytes": canonical["remaining_bytes"]},
                "overlay_status": {"remaining_funcs": s_remaining_funcs,
                                   "remaining_bytes": s_remaining_bytes},
                "progress": {"remaining_funcs": p_remaining_funcs,
                             "remaining_bytes": p_remaining_bytes},
            })
        # ≤15 band cross-check (town/dungeon acceptance).
        s_le15 = summ.get("near_miss_le15")
        if s_le15 is None:
            s_le15 = sum(
                1 for f in summ.get("functions", [])
                if f.get("state") != "done"
                and isinstance(f.get("words_off"), int)
                and f["words_off"] <= 15)
        le15_agree = s_le15 == canonical["le15_open"]
        if not le15_agree:
            disagreements.append({
                "scope": scope, "band": "le15",
                "overlay_status": s_le15, "canonical": canonical["le15_open"]})
        parked_landed_total += [f"{scope}:{f}" for f in canonical["parked_landed_violations"]]
        per_scope.append({**canonical, "overlay_status_le15": s_le15,
                          "consumers_agree": agree and le15_agree})

    totals = {
        "code_funcs": sum(s["code_funcs"] for s in per_scope),
        "code_bytes": sum(s["code_bytes"] for s in per_scope),
        "remaining_funcs": sum(s["remaining_funcs"] for s in per_scope),
        "remaining_bytes": sum(s["remaining_bytes"] for s in per_scope),
        "data_funcs": sum(s["data_funcs"] for s in per_scope),
        "data_bytes": sum(s["data_bytes"] for s in per_scope),
    }
    ok = not disagreements and not parked_landed_total
    return {
        "schema": "azure-clean.live-truth.reconcile.v1",
        "ok": ok,
        "scopes": per_scope,
        "totals": totals,
        "disagreements": disagreements,
        "parked_landed_violations": parked_landed_total,
    }


def main(argv: list[str] | None = None) -> int:
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    mode = ap.add_mutually_exclusive_group(required=True)
    mode.add_argument("--reconcile", action="store_true",
                      help="assert every consumer agrees on remaining code by scope")
    mode.add_argument("--inventory", action="store_true",
                      help="emit the canonical all-binary inventory snapshot")
    ap.add_argument("--scope", action="append", default=[],
                    help="restrict to main, overlay:<name>, legacy slus, or a bare "
                         "overlay name (repeatable)")
    ap.add_argument("--json", action="store_true")
    ap.add_argument("--output", type=Path,
                    help="atomically write the selected JSON report")
    args = ap.parse_args(argv)

    if args.inventory:
        if args.scope:
            ap.error("--scope is valid only with --reconcile")
        report = all_binary_inventory()
        if args.output:
            _atomic_json(args.output, report)
        if args.json or not args.output:
            print(json.dumps(report, indent=2, sort_keys=True))
        else:
            print(json.dumps({"output": str(args.output), **report["totals"]},
                             sort_keys=True))
        return 0

    report = reconcile(args.scope or None)
    if args.output:
        _atomic_json(args.output, report)
    if args.json:
        print(json.dumps(report, indent=2, sort_keys=True))
    else:
        print(f"live-truth reconcile: {'OK' if report['ok'] else 'DISAGREEMENT'}")
        for s in report["scopes"]:
            print(f"  {s['scope']:<16} remaining {s['remaining_funcs']:>5} funcs "
                  f"{s['remaining_bytes']:>9} B  | done {s['done_funcs']:>5} "
                  f"| data {s['data_funcs']:>4} ({s['data_bytes']} B) "
                  f"| ≤15 {s['le15_open']:>4} "
                  f"| {'agree' if s['consumers_agree'] else 'DISAGREE'}")
        t = report["totals"]
        print(f"  {'TOTAL':<16} remaining {t['remaining_funcs']:>5} funcs "
              f"{t['remaining_bytes']:>9} B  | data {t['data_funcs']} funcs "
              f"{t['data_bytes']} B")
        for d in report["disagreements"]:
            print(f"  DISAGREE {d}")
        for v in report["parked_landed_violations"]:
            print(f"  PARKED-LANDED VIOLATION {v}")
    return 0 if report["ok"] else 2


if __name__ == "__main__":
    raise SystemExit(main())
