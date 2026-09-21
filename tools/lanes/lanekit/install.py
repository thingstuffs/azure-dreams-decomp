#!/usr/bin/env python3
"""Put the kit in front of a lane.

    python3 tools/lanes/lanekit/install.py work/native_lane/r68_foo work/native_lane/r68_bar
    from install import install; install("work/native_lane/r68_foo")

WHAT IT WRITES: one file, `TOOLS.md`, in the lane - the tool table with ABSOLUTE paths and one
exact invocation line each, plus the row list the lane was served.

WHY IT DOES NOT COPY THE KIT.  Copying is how the lanes got into trouble in the first place: a
model lane read `work/native_lane/r62_astra_big/lab.py` and string-replaced the lane name into it;
another was handed an `evidence/lab.py` that still pointed at a third lane's directory and had to
throw it away and rebuild.  A copy is a fork, and a fork of a harness is a silent
wrong-lane/stale-tool bug waiting to be found by whoever reads the numbers.  One absolute path per
tool cannot go stale, a fix to the kit reaches every running lane at once, and nothing in the lane
directory can be mistaken for the lane's own work.

Nothing is copied for the compiler-cwd shim either: `env.sh` puts the kit directory itself on
PYTHONPATH, so `sitecustomize.py` is auto-imported from there (and `kitlib.bootstrap()` does the
same for a tool started without sourcing anything).
"""
from __future__ import annotations

import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import kitlib                                                             # noqa: E402

KIT = Path(__file__).resolve().parent
ROOT = kitlib.ROOT

TEMPLATE = """# Tools for this lane

Everything below is an absolute path: copy the line, do not guess a relative one.  (Seven astra
lanes and four sol lanes lost a command each to `tools/lanes/screen.py`, `tools/xform/pin_sites.py`
and `../r58_order/REPORT.md` - none of which exist.)  There is no `RUNBOOK.md`: this file and
`{kit}/README.md` are the index.

Lane directory: `{lane}`
Rows served ({nrows}): {rows}

    cd {lane}
    source {kit}/env.sh          # optional; then lab / erase / why are commands

## The kit - use these before writing any harness of your own

| what you want | command |
|---|---|
| calibrate: the pinned text MUST score exact | `python3 {kit}/lab.py baseline <row> --score` |
| what each pin holds, which pins fall together | `python3 {kit}/erase.py <row>` |
| screen variants (files) | `python3 {kit}/lab.py <row> v1.c v2.c --score` |
| screen variants (substitutions) | `python3 {kit}/lab.py <row> --subs shapes1.json --score` |
| the REPORT.md table, from what was measured | `python3 {kit}/lab.py report` |
| WHY the scheduler emitted that order | `python3 {kit}/why.py <row> --pass sched --around <var>` |
| WHY that variable got that register | `python3 {kit}/why.py <row> --pass greg --around <var>` |
| WHY that constant stayed in the loop | `python3 {kit}/why.py <row> --pass loop` |
| what changed at cse / combine / flow / jump | `python3 {kit}/why.py <row> --pass combine --around <var>` |

`why.py` compares two texts: `--vs` (default the pinned text) against `--variant` (default all pins
erased, or a path to your candidate).

## The shared tools underneath (correct paths, verified)

| tool | path | one line |
|---|---|---|
| byte scorer (the only authority) | `{root}/tools/verify.py` | `python3 {root}/tools/verify.py <row> <abs path to .c>`; `--diff` prints generated \\| retail |
| cc1-listing screen, CLI + `Screen` class | `{root}/tools/xform/variant_screen.py` | `python3 {root}/tools/xform/variant_screen.py <row> variants.json [--verify] [--context 4]` |
| listing normalisation used by the screen | `{root}/tools/xform/screen.py` | `from screen import compile_s, sdiff` |
| the pins of a text | `{root}/tools/pin_census.py` | `from pin_census import sites_of` |
| erase pins / site facts | `{root}/tools/pin_sites.py` | `from pin_sites import erase_many` |
| rows, recipes, paths | `{root}/tools/common.py` | `from common import rows, clean_path, parse_cfg` |
| scheduler dumps, ready lists, insn pairs | `{root}/tools/xform/sched_trace.py` | `compile_text(row, text, dumps=True)`, `decisions()`, `diagnose()` |
| per-pass RTL features, first differing pass | `{root}/tools/xform/reg_state.py` | `observe(row, text)`, `comparison(a, b)` |
| the gcc 2.x allocator model | `{root}/tools/alloc_sim.py` | `read(row, text)`, `simulate(rd)`, `decl_pseudos(text, first)` |
| the allocator's real reason, under gdb | `{root}/tools/alloc_trace.py` | `python3 {root}/tools/alloc_trace.py <row> [--source cand.c]` |
| loop-pass decisions | `{root}/tools/lanes/loop_census.py` | `dump_loop`, `split_functions`, `compare` |
| joint erasure subsets | `{root}/tools/lanes/joint_scan.py` | `subsets_of(sites, pair_pins, exhaustive_pins)` (the scan itself is repo-scale: use `erase.py`) |
| gcc sources for every cell | `{root}/toolchain/gcc-src/<version>/` | search ONE version directory, `--max-filesize 4M` |

Do not run `tools/sweep.py`, `tools/pin_search.py` or `tools/apply_candidates.py` from a lane, and
never edit `src/` or run git.
"""


def install(lane_dir):
    """Write `TOOLS.md` into the lane.  Returns the path written."""
    lane = Path(lane_dir).resolve()
    if not lane.is_dir():
        raise SystemExit("install: %s is not a directory" % lane)
    if lane == ROOT:
        raise SystemExit("install: refusing to install into the repository root")
    rows = kitlib.lane_rows(lane)
    out = lane / "TOOLS.md"
    out.write_text(TEMPLATE.format(
        kit=KIT, root=ROOT, lane=lane, nrows=len(rows),
        rows=", ".join("`%s`" % r for r in rows) or "(none found under base/)"))
    return out


def main():
    if len(sys.argv) < 2:
        raise SystemExit(__doc__)
    for d in sys.argv[1:]:
        print("wrote %s" % install(d))


if __name__ == "__main__":
    main()
