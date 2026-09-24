#!/usr/bin/env python3
"""Is a row RETAIL-exact at another compiler cell, under maspsx AND under genuine ASPSX? (measurement only)

`aspsx_diff.py` names a genuine version "exact" when its object equals the MASPSX leg's (token
streams), which is "genuine reproduces retail" only while the maspsx leg is itself retail-exact -
true at a row's registered recipe (the gate), NOT at a trial cell. At a trial cell a row whose
maspsx leg misses retail can still list every genuine version in `exact_versions`: genuine ==
maspsx != retail. This tool keeps the two questions apart. Per row and cfg it reports

  maspsx_exact    the per-row scorer's verdict (linked words equal retail) on the maspsx leg
  maspsx_retail   positional differing words vs retail (relocations resolved), with the positions
  genuine_eq      genuine versions whose object equals the maspsx leg's (aspsx_diff `exact_versions`)
  genuine_retail  per genuine version: differing words vs retail (relocations resolved), best mode
  genuine_retail_exact  True when some genuine version resolves to 0 differing words vs retail, with 0
                  masked words - or with masked (unresolvable) relocations only, while its object equals a
                  scorer-exact maspsx leg

and, with --asflags-variants, the maspsx leg again with the row's as-flags dropped one at a time and
all dropped (the dial ablation). The trial cfg is the row's registered cfg with the CELL replaced
(`--cell 2.7.2-cdk`: '2.8.0-G0' -> '2.7.2-cdk-G0', '2.7.2-G0 -fno-schedule-insns' ->
'2.7.2-cdk-G0 -fno-schedule-insns'), or an explicit `--cfg`.

    .venv/bin/python tools/fidelity/cell_retail_check.py --rows @work/fidelity/cdk35/rows.txt \
        --cell 2.7.2-cdk --out work/fidelity/cdk35/check_cdk.jsonl [--workers 8] [--registered] \
        [--asflags-variants] [--cfile-dir work/fidelity/cdk35/cands]

Scratch lives under work/fidelity/cdk35/tmp (never the shared work/fidelity/tmp); nothing outside
the --out file is written.
"""
from __future__ import annotations

import argparse
import json
import os
import struct
import subprocess
import sys
import tempfile
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(HERE))
SCRATCH = ROOT / "work/fidelity/cdk35/tmp"


def trial_cfg(cfg: str, cell: str) -> str:
    """The registered cfg with its compiler cell replaced; -G0 and every other flag kept."""
    from common import parse_cfg
    head, flags = parse_cfg(cfg)
    g0 = "-G0" in flags
    rest = [f for f in flags if f != "-G0"]
    return (cell + ("-G0" if g0 else "") + (" " + " ".join(rest) if rest else "")).strip()


def genuine_retail_exact(maspsx_exact, genuine_eq, genuine_retail) -> bool:
    """Retail-exact under some genuine version: 0 differing and 0 masked words vs retail, or 0 differing
    with masked (unresolvable) relocations only while that version's object equals a scorer-exact maspsx
    leg. `genuine_eq` alone (aspsx_diff's `exact_versions`) is NOT evidence: it is genuine == maspsx."""
    eq = set(genuine_eq or [])
    return any(d == 0 and (m == 0 or (bool(maspsx_exact) and v in eq)) for v, (d, m) in genuine_retail.items())


def _positions(view, fname, ctx, A):
    """Positional word differences (index, ours, retail) of an overlay row vs retail, resolved as
    aspsx_diff.retail_compare resolves them."""
    tgt, base, gp = ctx["retail"], ctx["link_vram"], ctx["gp"]

    def addr_of(n):
        m = A.NAME_ADDR.match(n or "")
        return int(m.group(1), 16) if m else None
    if fname not in view.funcs:
        return None
    lay = view.unit_layout(fname)
    words, mk = A.resolve_tokens(view, fname, base + lay.get(fname, 0), addr_of, gp, slice_base=base, layout=lay)
    ret = [struct.unpack_from("<I", tgt, 4 * i)[0] for i in range(len(tgt) // 4)]
    out = []
    for i in range(max(len(words), len(ret))):
        if i in mk:
            continue
        a = words[i] if i < len(words) else None
        b = ret[i] if i < len(ret) else None
        if a != b:
            out.append([i, a, b])
    return out


def check_row(rid: str, cfg: str, asflags_variants: bool, cfile: str | None = None):
    """Run inside a worker process (process_row mutates os.environ)."""
    import aspsx_diff as A
    from common import rows
    A.TMP = SCRATCH / "rows"
    A.TMP.mkdir(parents=True, exist_ok=True)
    row = {r["id"]: r for r in rows()}[rid]
    captured = {}
    orig_rc = A.retail_compare

    def rc(view, scope, kind, overlay_ctx=None):          # also keep the maspsx leg's positions
        res = orig_rc(view, scope, kind, overlay_ctx)
        if kind == "overlay" and "m" not in captured:
            captured["m"] = _positions(view, scope[0], overlay_ctx, A)
        return res
    A.retail_compare = rc
    rec = A.process_row(row, cfile, cfg, None, keep=False)
    out = {"row": rid, "cfg": cfg, "cfile": cfile, "status": rec.get("status"), "err": rec.get("err"),
           "asflags": rec.get("asflags"), "fired": rec.get("fired"),
           "maspsx_exact": rec.get("maspsx_exact"), "maspsx_retail": (rec.get("maspsx_retail") or {}).get("diff"),
           "words": rec.get("words"), "maspsx_diff_pos": captured.get("m"),
           "genuine_eq": rec.get("exact_versions")}
    gr = {}
    for v, g in (rec.get("genuine") or {}).items():
        if "retail" in g:
            gr[v] = g["retail"]
    out["genuine_retail"] = gr
    out["genuine_retail_exact"] = genuine_retail_exact(rec.get("maspsx_exact"), rec.get("exact_versions"), gr)
    if asflags_variants and rec.get("status") == "ok":
        fl = (rec.get("asflags") or "").split()
        variants = {"drop:all": ""}
        for f in fl:
            variants["drop:" + f] = " ".join(x for x in fl if x != f)
        vres = {}
        for name, af in variants.items():
            captured.clear()
            r2 = A.process_row(row, cfile, cfg, af, keep=False)
            vres[name] = {"asflags": af, "maspsx_exact": r2.get("maspsx_exact"),
                          "maspsx_retail": (r2.get("maspsx_retail") or {}).get("diff"),
                          "genuine_eq": r2.get("exact_versions")}
        out["asflags_variants"] = vres
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--rows", required=True, help="comma list or @file (one id per line)")
    ap.add_argument("--cell", help="replace the registered cell with this one")
    ap.add_argument("--cfg", help="explicit cfg for every row (overrides --cell)")
    ap.add_argument("--registered", action="store_true", help="run at the registered cfg (control)")
    ap.add_argument("--asflags-variants", action="store_true")
    ap.add_argument("--workers", type=int, default=8)
    ap.add_argument("--out", required=True)
    ap.add_argument("--cfile-dir", help="use DIR/<func>.c as the row text when it exists (candidate texts)")
    ap.add_argument("--worker", nargs="+", help=argparse.SUPPRESS)
    a = ap.parse_args()
    if a.worker:
        cf = a.worker[2] if len(a.worker) > 2 else None
        print(json.dumps(check_row(a.worker[0], a.worker[1], a.asflags_variants, cf), separators=(",", ":")))
        return
    from common import rows
    by = {r["id"]: r for r in rows()}
    ids = [x.strip() for x in (Path(a.rows[1:]).read_text().split() if a.rows.startswith("@") else a.rows.split(","))]
    jobs = []
    for i in ids:
        r = by[i]
        cfg = r["cfg"] if a.registered else (a.cfg or trial_cfg(r["cfg"], a.cell))
        cf = None
        if a.cfile_dir and (Path(a.cfile_dir) / (r["func"] + ".c")).exists():
            cf = str((Path(a.cfile_dir) / (r["func"] + ".c")).resolve())
        jobs.append((i, cfg, cf))
    SCRATCH.mkdir(parents=True, exist_ok=True)

    def one(job):
        cmd = ["nice", "-n10", str(ROOT / ".venv/bin/python"), str(Path(__file__)), "--rows", "-", "--out", "-",
               "--worker", job[0], job[1]] + ([job[2]] if job[2] else []) + (["--asflags-variants"] if a.asflags_variants else [])
        p = subprocess.run(cmd, capture_output=True, text=True, cwd=str(ROOT), timeout=3600)
        try:
            return json.loads(p.stdout.strip().splitlines()[-1])
        except Exception:
            return {"row": job[0], "cfg": job[1], "status": "error", "err": (p.stderr or p.stdout)[-400:]}
    Path(a.out).parent.mkdir(parents=True, exist_ok=True)
    with ThreadPoolExecutor(max_workers=min(a.workers, 8)) as ex, open(a.out, "w") as fh:
        for rec in ex.map(one, jobs):
            fh.write(json.dumps(rec, separators=(",", ":")) + "\n"); fh.flush()
            print(f"{rec['row']:28s} {rec['cfg']:36s} maspsx_exact={rec.get('maspsx_exact')} "
                  f"m_ret={rec.get('maspsx_retail')} g_eq={len(rec.get('genuine_eq') or [])} "
                  f"g_ret={sorted(set(tuple(x) for x in (rec.get('genuine_retail') or {}).values()))} "
                  f"{rec.get('status')} {rec.get('err') or ''}", flush=True)


if __name__ == "__main__":
    main()
