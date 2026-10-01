#!/usr/bin/env python3
"""prefs_gdb.py - ground truth for prefs.py: read global.c's preference state out of the cell's own cc1 under gdb.

    python3 prefs_gdb.py <row> <candidate.c|pinned|erased> [--json OUT]

Breakpoints (2.7.2-cdk / 2.8.x cc1 are unstripped; addresses from `nm`):
  expand_preferences entry  -> hard_reg_{preferences,copy_preferences,full_preferences} after global_conflicts
                               (set_preference) and the eliminable-register removal
  prune_preferences entry   -> the same three after expand_preferences
  dump_conflicts entry      -> after prune: the three + regs_someone_prefers, hard_reg_conflicts, regs_used_so_far,
                               no_global_alloc_regs, regs_ever_live, allocno_order/reg/size/calls/refs/live
  find_reg entry + finish   -> (allocno, alt_regs_p, accept_call_clobbered, retrying) and reg_renumber afterwards
This is a VALIDATION ORACLE only (one gdb run per text); prefs.py must reproduce it from the dumps alone.
"""
from __future__ import annotations

import argparse
import json
import os
import subprocess
import sys
import tempfile
from pathlib import Path

_HERE = Path(__file__).resolve().parent
ROOT = next(p for p in _HERE.parents if (p / "tools/common.py").is_file())
sys.path.insert(0, str(ROOT / "tools/lanes/lanekit"))
sys.path.insert(0, str(ROOT / "tools"))

GDB_SCRIPT = r'''
import gdb, json, struct
C = json.load(open('cfg.json')); A = C['addresses']; FIRST = C['first']; W = (FIRST + 31) // 32
mem = lambda a, n: bytes(gdb.selected_inferior().read_memory(a, n))
def i32(a): return struct.unpack('<i', mem(a, 4))[0]
def ptr(n): return struct.unpack('<I', mem(A[n], 4))[0]
def scalar(n): return i32(A[n])
def fname(): return mem(ptr('current_function_name'), 160).split(b'\x00')[0].decode(errors='replace')
def vec(n, cnt): return list(struct.unpack('<' + 'i' * cnt, mem(ptr(n), 4 * cnt))) if cnt else []
def mask(addr):
    w = struct.unpack('<' + 'I' * W, mem(addr, 4 * W)); return [r for r in range(FIRST) if w[r // 32] & (1 << (r % 32))]
def sets(n, cnt): return [mask(ptr(n) + 4 * W * i) for i in range(cnt)]
def args(k):
    sp = int(gdb.parse_and_eval('$esp')); return [i32(sp + 4 * (i + 1)) for i in range(k)]
out = {'stages': [], 'find_reg': [], 'errors': []}
PREFS = ['hard_reg_preferences', 'hard_reg_copy_preferences', 'hard_reg_full_preferences']
class Stage(gdb.Breakpoint):
    def __init__(self, where, name):
        super().__init__(where, internal=True); self.name = name
    def stop(self):
        try:
            n = scalar('max_allocno')
            g = {'stage': self.name, 'function': fname(), 'allocno_reg': vec('allocno_reg', n)}
            for k in PREFS: g[k] = sets(k, n)
            if self.name == 'dump':
                for k in ['allocno_order', 'allocno_size', 'allocno_calls_crossed', 'allocno_n_refs', 'allocno_live_length']:
                    g[k] = vec(k, n)
                g['regs_someone_prefers'] = sets('regs_someone_prefers', n)
                g['hard_reg_conflicts'] = sets('hard_reg_conflicts', n)
                g['regs_used_so_far'] = mask(A['regs_used_so_far'])
                g['no_global_alloc_regs'] = mask(A['no_global_alloc_regs'])
                g['regs_ever_live'] = [r for r, b in enumerate(mem(A['regs_ever_live'], FIRST)) if b]
                g['local_reg_n_refs'] = list(struct.unpack('<' + 'i' * FIRST, mem(A['local_reg_n_refs'], 4 * FIRST)))
            out['stages'].append(g)
        except Exception as e:
            out['errors'].append('%s: %s' % (self.name, e))
        return False
class Fin(gdb.FinishBreakpoint):
    def __init__(self, e):
        super().__init__(gdb.newest_frame(), internal=True); self.e = e
    def stop(self):
        self.e['result'] = struct.unpack('<h', mem(ptr('reg_renumber') + 2 * self.e['pseudo'], 2))[0]; return False
class Find(gdb.Breakpoint):
    def stop(self):
        try:
            a = args(5); i = a[0]
            e = {'function': fname(), 'allocno': i, 'pseudo': i32(ptr('allocno_reg') + 4 * i), 'alt': a[2],
                 'accept': a[3], 'retrying': a[4], 'used_so_far': mask(A['regs_used_so_far']),
                 'conflicts': mask(ptr('hard_reg_conflicts') + 4 * W * i)}
            out['find_reg'].append(e); Fin(e)
        except Exception as e:
            out['errors'].append('find_reg: %s' % e)
        return False
Stage('*' + str(A['expand_preferences']), 'expand')
Stage('*' + str(A['prune_preferences']), 'prune')
Stage('*' + str(A['dump_conflicts']), 'dump')
Find('*' + str(A['find_reg']), internal=True)
gdb.execute('run')
json.dump(out, open('oracle.json', 'w'), separators=(',', ':'))
'''


def symbols(cc1):
    out = subprocess.run(["nm", "-S", str(cc1)], capture_output=True, text=True, check=True).stdout
    sy = {}
    for line in out.splitlines():
        p = line.split()
        if len(p) >= 3:
            sy.setdefault(p[-1], []).append(int(p[0], 16))
    anchor = sy["hard_reg_preferences"][0]
    return {n: min(v, key=lambda a: abs(a - anchor)) for n, v in sy.items()}


def trace(row, text, timeout=180):
    """The oracle dict for `text` compiled as `row` (single-unit rows; the slus module context is not built)."""
    from common import parse_cfg
    import alloc_sim
    cell, flags = parse_cfg(row["cfg"])
    first = alloc_sim.FIRST.get(cell)
    D = ROOT / "toolchain/compilers" / ("gcc-" + cell)
    addr = symbols(D / "cc1")
    with tempfile.TemporaryDirectory(prefix="prefsgdb_") as td:
        d = Path(td)
        (d / "f.c").write_text(text)
        r = subprocess.run([str(D / "gcc"), "-B" + str(D) + "/", "-E", "-O2", *flags, "-I" + str(ROOT / "include"),
                            "-w", "f.c", "-o", "f.i"], cwd=d, capture_output=True, text=True, timeout=60)
        if r.returncode:
            return {"error": r.stderr[-800:]}
        (d / "cfg.json").write_text(json.dumps({"addresses": addr, "first": first}))
        (d / "t.py").write_text(GDB_SCRIPT)
        (d / "t.gdb").write_text("set pagination off\nset confirm off\nset debuginfod enabled off\n"
                                 "set startup-with-shell off\nsource t.py\n")
        r = subprocess.run(["gdb", "--batch", "--nx", "-x", "t.gdb", "--args", str(D / "cc1"), "f.i", "-quiet",
                            "-O2", *flags, "-w", "-da", "-o", "f.s"], cwd=d, capture_output=True, text=True,
                           timeout=timeout)
        if not (d / "oracle.json").exists():
            return {"error": (r.stdout + r.stderr)[-1500:]}
        res = json.loads((d / "oracle.json").read_text())
        res["greg"] = "".join(p.read_text(errors="replace") for p in d.glob("*.greg"))
        return res


def main(argv=None):
    import kitlib
    ap = argparse.ArgumentParser()
    ap.add_argument("row")
    ap.add_argument("text")
    ap.add_argument("--json")
    a = ap.parse_args(argv)
    lane = kitlib.bootstrap()
    row = kitlib.row_of(a.row)
    base = kitlib.base_text(row, lane)
    text = base if a.text == "pinned" else kitlib.erased_text(base) if a.text == "erased" else Path(a.text).read_text()
    res = trace(row, text)
    if a.json:
        Path(a.json).write_text(json.dumps(res))
    print("errors:", res.get("errors") or res.get("error"))
    for s in res.get("stages", []):
        print(s["stage"], s["function"], len(s["allocno_reg"]))
    print("find_reg calls:", len(res.get("find_reg", [])))


if __name__ == "__main__":
    main()
