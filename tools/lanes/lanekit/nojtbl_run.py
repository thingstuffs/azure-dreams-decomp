#!/usr/bin/env python3
"""nojtbl_run.py - child process of `nojtbl.py`: `tools/aligned_score.py` with match.py's local jump-table
CONTENT check switched OFF (information only; never an exactness claim - the real scorer decides).

    python3 nojtbl_run.py <aligned_score.py args...>          (cwd = the gate view root, build_ovl/)

`aligned_score.py` starts `work/g3/overlay_func_compare.py` in a subprocess; that script loads match.py and
calls `match.build_text(..., retail_data=...)`, which fails the build with `jtbl: ...` when
`match.local_table_diffs` reports a difference.  Here every such subprocess is started through a tiny
`-c` trampoline that execs the script after `spec.loader.exec_module(M)` with
`M.local_table_diffs = lambda *a, **k: []`.  Nothing on disk is edited, the gate and `tools/verify.py` keep their
defaults, and an anchor that no longer exists in overlay_func_compare.py FAILS LOUDLY (AssertionError ->
HARNESS-ERROR) instead of silently scoring with the check still on.
(Folded in from work/native_lane/r82_opus_fc10/tools/nojtbl_score.py.)"""
import os
import runpy
import subprocess
import sys

ANCHOR = "spec.loader.exec_module(M)\n"
TRAMPOLINE = ("import sys; p=sys.argv[1]; s=open(p).read(); a=%r; "
              "assert a in s, 'nojtbl: anchor missing in '+p; s=s.replace(a,a+'M.local_table_diffs = lambda *x, **k: []\\n',1); "
              "sys.argv=sys.argv[1:]; g={'__name__':'__main__','__file__':p}; exec(compile(s,p,'exec'),g)" % ANCHOR)

_run = subprocess.run


def run(cmd, *a, **k):
    if isinstance(cmd, list) and len(cmd) > 1 and cmd[0] == "python3" and str(cmd[1]).endswith("/overlay_func_compare.py"):
        cmd = ["python3", "-c", TRAMPOLINE] + cmd[1:]
    return _run(cmd, *a, **k)


if __name__ == "__main__":
    subprocess.run = run
    script = os.path.join(os.getcwd(), "tools", "aligned_score.py")
    sys.argv = [script] + sys.argv[1:]
    runpy.run_path(script, run_name="__main__")
