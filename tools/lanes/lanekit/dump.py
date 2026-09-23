#!/usr/bin/env python3
"""dump.py - every `-da` pass dump of one text, written to a directory in the lane.

    python3 <KIT>/dump.py <row> <candidate.c|pinned|erased> <outdir> [--cfg CFG]
                          [--pass sched|greg|lreg|loop|combine|cse|jump|flow|rtl|dbr|all]

23 lanes of round 73 wrote this wrapper (`dump.py`, `dumps.py`, `dumpit.sh`), two of them by
re-deriving the raw `gcc -E` / `cc1 -da` calls.  It is `kitlib.dumps` (the compile `why.py` uses)
plus a file per pass: `<outdir>/<stem>.<pass>` and `<outdir>/<stem>.s`, where `<stem>` is the
candidate's file stem or `pinned` / `erased`.  `sched`, `cse` and `jump` include their second
pass (`sched2`, `cse2`, `jump2`).

`--cfg` compiles as if the row were registered at CFG (e.g. `"2.8.1-G0 -mno-split-addresses"`) -
for this compile only; the row's registered cfg is not touched.  `outdir` must be inside the lane.
Nothing is scored and nothing is journalled.
"""
from __future__ import annotations

import argparse
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import kitlib                                                             # noqa: E402

PASSES = {
    "sched": ("sched", "sched2"), "greg": ("greg",), "lreg": ("lreg",), "loop": ("loop",),
    "combine": ("combine",), "cse": ("cse", "cse2"), "jump": ("jump", "jump2"), "flow": ("flow",),
    "rtl": ("rtl",), "dbr": ("dbr",), "all": None,
}


def want_of(pass_name):
    if pass_name not in PASSES:
        raise SystemExit("dump.py: --pass must be one of %s" % ", ".join(PASSES))
    w = PASSES[pass_name]
    return None if w is None else set(w)


def run(row, text, outdir, stem, cfg=None, pass_name="all", dumps=None):
    """Write the dumps; return the list of paths written.  `dumps` defaults to `kitlib.dumps`."""
    dumps = dumps or kitlib.dumps
    d = dumps(kitlib.row_at_cfg(row, cfg), text, want=want_of(pass_name))
    if d is None or d.get("error"):
        raise SystemExit("dump.py: DOES NOT BUILD at %s\n%s"
                         % (cfg or row["cfg"], (d or {}).get("error") or ""))
    outdir = Path(outdir)
    outdir.mkdir(parents=True, exist_ok=True)
    written = []
    for k, v in sorted(d.items()):
        if k == "error" or v is None:
            continue
        p = outdir / ("%s.%s" % (stem, "s" if k == "asm" else k))
        p.write_text(v)
        written.append(p)
    return written


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("row_id")
    ap.add_argument("text", help="candidate .c, or 'pinned' / 'erased'")
    ap.add_argument("outdir", help="directory inside the lane")
    ap.add_argument("--cfg", help="compile at this cfg instead of the row's (this compile only)")
    ap.add_argument("--pass", dest="pass_name", default="all", choices=sorted(PASSES))
    a = ap.parse_args(argv)

    lane = kitlib.bootstrap()
    out = Path(a.outdir).resolve()
    try:
        out.relative_to(lane)
    except ValueError:
        raise SystemExit("dump.py: %s is outside the lane %s - lanes write only inside themselves" % (out, lane))
    row = kitlib.row_of(a.row_id)
    if a.text in ("pinned", "erased"):
        base = kitlib.base_text(row, lane)
        stem, text = a.text, base if a.text == "pinned" else kitlib.erased_text(base)
    else:
        p = Path(a.text)
        if not p.is_file():
            raise SystemExit("dump.py: no such file %s (or say 'pinned' / 'erased')" % p)
        stem, text = p.stem, p.read_text(errors="replace")
    written = run(row, text, out, stem, cfg=a.cfg, pass_name=a.pass_name)
    print("%s at %s%s -> %s" % (stem, a.cfg or row["cfg"], "" if not a.cfg else
                               "  (override for this compile; registered cfg %s unchanged)" % row["cfg"], out))
    for p in written:
        print("  %s  (%d lines)" % (p.relative_to(lane), p.read_text(errors="replace").count("\n")))
    return written


if __name__ == "__main__":
    main()
