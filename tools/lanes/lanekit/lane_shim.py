#!/usr/bin/env python3
"""The compiler-cwd shim, as a function.  `sitecustomize.py` is a three-line wrapper around it.

WHAT IT FIXES.  `gcc -da` / `cc1 -da` write their dump files into the process's current directory.
Every lane brief has carried a "FIRST RULE: cd into the lane" sentence because lanes have left
dozens of dump files at the repository root.  Two model lanes invented this shim independently and
four more rewrote it; this is the version the kit hands out.

WHAT IT DOES, precisely:

* `kitlib.bootstrap()` has already set `TMPDIR` and `tempfile.tempdir` to `<lane>/tmp`, so every
  shared tool's `TemporaryDirectory` - and therefore every dump it asks for - is already inside the
  lane.  That is the real fix; this shim is the backstop.
* It wraps `subprocess.Popen`.  When a launched command is a compiler (`gcc`, `cc1`, `cpp`, `cc.sh`,
  `cc_psyq.sh`, possibly behind a `nice`/`ionice` prefix) it appends one line to
  `<lane>/compiler_cwd.log`: the effective cwd and the argv.  That audit trail is what let one lane
  notice a mis-built compile adapter.
* It RE-HOMES a compiler only when the effective cwd is the REPOSITORY ROOT itself - the documented
  failure.  It then absolutizes the relative arguments that exist and runs the compiler in
  `<lane>/tmp/cc`.

WHY IT DOES NOT RE-HOME EVERYTHING.  `tools/verify.py` scores by running `tools/aligned_score.py`
inside `build_ovl/`, and its compilers run with `cwd=` the candidate's own directory or the gate
root.  A shim that forced every compiler into the lane would break the byte scorer - including in
grandchild processes, which inherit this file through `PYTHONPATH`.  Re-homing only the
repository-root case cannot do that: no scoring compile ever runs there.
"""
from __future__ import annotations

import os
import subprocess
from pathlib import Path

COMPILERS = {"gcc", "cc1", "cc1plus", "cpp", "g++", "cc.sh", "cc_psyq.sh"}
_INSTALLED = False


def _repo_root(start):
    for p in [Path(start).resolve()] + list(Path(start).resolve().parents):
        if (p / "tools/common.py").is_file():
            return p
    return None


def _compiler_in(args):
    """The index of the compiler argument, `nice`/`ionice` prefixes skipped (None if there is none)."""
    for i, a in enumerate(args[:6]):
        name = Path(str(a)).name
        if name in COMPILERS:
            return i
        if name not in ("nice", "ionice", "-n10", "-c2", "-n7", "env") and not str(a).startswith("-"):
            if i > 0:
                return None
    return None


def install(lane=None, root=None):
    """Wrap `subprocess.Popen` for this process (and, through PYTHONPATH, its python children)."""
    global _INSTALLED
    if _INSTALLED:
        return False
    lane = Path(lane or os.environ.get("LANEKIT_LANE") or Path.cwd()).resolve()
    root = Path(root).resolve() if root else _repo_root(lane)
    if root is None or lane == root:
        return False                       # not in a lane: do nothing at all
    logp = lane / "compiler_cwd.log"
    home = lane / "tmp" / "cc"
    original = subprocess.Popen

    class LanePopen(original):
        def __init__(self, args, *a, **kw):
            try:
                if isinstance(args, (list, tuple)) and args:
                    argv = [str(x) for x in args]
                    i = _compiler_in(argv)
                    if i is not None:
                        origin = Path(kw.get("cwd") or os.getcwd()).resolve()
                        rehome = origin == root
                        if rehome:
                            home.mkdir(parents=True, exist_ok=True)
                            for j, val in enumerate(argv):
                                if j <= i or not val or val.startswith("-"):
                                    continue
                                p = origin / val
                                if not Path(val).is_absolute() and p.exists():
                                    argv[j] = str(p.resolve())
                            kw["cwd"] = str(home)
                            args = argv
                        with logp.open("a") as f:
                            f.write("%s cwd=%s %s\n" % ("REHOMED" if rehome else "ok",
                                                        kw.get("cwd") or os.getcwd(), argv))
            except Exception:                # a shim must never be the reason a compile fails
                pass
            super().__init__(args, *a, **kw)

    subprocess.Popen = LanePopen
    _INSTALLED = True
    return True
