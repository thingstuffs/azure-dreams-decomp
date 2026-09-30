#!/usr/bin/env python3
"""nojtbl.py - score a candidate with the switch jump-table CONTENT check OFF (`--no-jtbl`), and parse the
`jtbl:` rejection the real scorer produces.

Since 09-30 the scorer compares the jump-table contents (`tools/gate/match.py local_table_diffs`); a text whose
table differs from retail is rejected with `jtbl: local .rodata at 0x... word N: got 0x..., retail 0x... (the
switch's case->label table differs from retail)` and NO listing, so a real `switch` rewrite that is not exact yet
could not be diffed.  This module is the kit's single implementation of the two halves:

* `parse_jtbl_err(err)` / `jtbl_status(v)` - the rejection as data (`addr`, `word`, `got`, `retail`), used by
  `kitlib.score_at` to report the status `jtbl-mismatch` instead of `build-fail/no-hex`.
* `verify_nojtbl(row, cfile, ...)` - `tools/verify.verify` with the check off, through `nojtbl_run.py`.  The result is
  INFORMATIONAL: `exact` is forced False (so nothing stages it), `text_exact` says whether the text matched, and
  `jtbl_checked` is False.  Exactness is still decided by the real scorer only.  `tools/verify.py`, the gate and
  match.py are untouched and keep the check on by default; overlay rows only.
"""
from __future__ import annotations

import re
import subprocess as _subprocess
import sys
import threading
from pathlib import Path

RUNNER = Path(__file__).resolve().parent / "nojtbl_run.py"
JTBL_RE = re.compile(r"local \.rodata at (0x[0-9a-fA-F]+) word (\d+): got (0x[0-9a-fA-F]+), retail (0x[0-9a-fA-F]+)")
NOTE = "NOTE jump-table content check OFF (--no-jtbl): informational only, exactness is decided by the real scorer."
EXACT_MSG = "text exact, jump table NOT checked"

_tls = threading.local()
_INSTALLED = False


def parse_jtbl_err(err):
    """`jtbl: ...` scorer error -> [{addr, word, got, retail}] (one per reported word), [] when it is not one."""
    if not err or not str(err).startswith("jtbl:"):
        return []
    return [{"addr": m.group(1), "word": int(m.group(2)), "got": m.group(3), "retail": m.group(4)}
            for m in JTBL_RE.finditer(str(err))]


def is_jtbl_err(err):
    return bool(err) and str(err).startswith("jtbl:")


def jtbl_summary(items, err=None):
    if not items:
        return (err or "jtbl mismatch")[:200]
    return "; ".join("table %s word %d: got %s, retail %s" % (i["addr"], i["word"], i["got"], i["retail"]) for i in items)


def jtbl_status(v):
    """Idempotently turn a scorer result that was REJECTED for its jump table into status `jtbl-mismatch`
    (was `failed`, class `build-fail`), with `jtbl` = the parsed words.  Anything else is returned unchanged."""
    if isinstance(v, dict) and is_jtbl_err(v.get("err")) and v.get("status") != "jtbl-mismatch":
        v["jtbl"] = parse_jtbl_err(v["err"])
        v["status"] = "jtbl-mismatch"
    return v


class _Shim:
    """Stands in for the `subprocess` module INSIDE tools/verify.py only: while this thread has the flag set, the
    `python3 tools/aligned_score.py ...` command is routed through nojtbl_run.py; everything else (and every
    thread without the flag) passes straight to the real module."""
    def __getattr__(self, name):
        return getattr(_subprocess, name)

    def run(self, cmd, *a, **k):
        if getattr(_tls, "off", False) and isinstance(cmd, list) and "tools/aligned_score.py" in cmd:
            cmd = [str(RUNNER) if c == "tools/aligned_score.py" else c for c in cmd]   # python3 <runner> <args>
        return _subprocess.run(cmd, *a, **k)


def _install(verify_mod):
    global _INSTALLED
    if not _INSTALLED or not isinstance(verify_mod.subprocess, _Shim):
        verify_mod.subprocess = _Shim()
        _INSTALLED = True


def verify_nojtbl(row, cfile, include_root=None, diff=False, verify_fn=None):
    """`verify.verify(row, cfile, ...)` with the jump-table content check off.  Overlay rows only.
    `verify_fn` (tests) replaces verify.verify; the check-off routing only matters for the real one."""
    if row.get("kind") == "slus":
        raise SystemExit("--no-jtbl applies to overlay rows (the slus scorer has no jump-table content check)")
    if verify_fn is None:
        import verify as verify_mod                                      # noqa: E402
        _install(verify_mod)
        verify_fn = verify_mod.verify
    _tls.off = True
    try:
        v = verify_fn(row, cfile, include_root=include_root, diff=diff) or {}
    finally:
        _tls.off = False
    v = dict(v)
    if diff:
        v["text"] = NOTE + "\n" + (v.get("text") or "")
        return v
    text_exact = bool(v.get("exact"))
    v["text_exact"] = text_exact
    v["exact"] = False               # never an exactness claim
    v["jtbl_checked"] = False
    return v
