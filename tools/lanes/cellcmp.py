#!/usr/bin/env python3
# Moved from work/native_lane/r81_sonnet_cellcmp (round 81); run from a lane directory (lanekit bootstrap).
"""cellcmp.py - compare two compiler cells on one row: how much of the cell dependence is carried by the pins.

Cell-sensitivity detectors D0/D1 of r81_fable_late (TAXONOMY.md), as one lanekit tool.  Run inside a lane
directory (kitlib refuses the repo root); compiler dumps stay in <lane>/tmp.

  cellcmp.py <row> [--text pinned|erased|FILE] --cfg A --cfg B
        generated-listing line diff count between cfg A and cfg B (unified diff of the scorer's
        generated column, +/- lines) and the byte-scorer total at each.  Default text: pinned.
  cellcmp.py <row> --carriers --cfg B
        D1: one line per pin: macro, arg, line, cell-diff lines (only that pin kept, registered cfg
        vs B) and the total at B with that pin alone erased from the pinned text.  cell-diff > 0
        names a carrier of the cell dependence.  (--cfg A optional; default = the row's cfg.)
  cellcmp.py --census ROWS.txt --out OUT.jsonl [--procs 4]
        per row: cfg_reg, cfg_cdk (same flags, cell -> 2.7.2-cdk, -G0 kept), D0 lines (all pins erased,
        reg vs cdk), er_reg/er_cdk/pinned_cdk totals, class: P (D0 0 lines) / P-near (1-4) / D (more) /
        CDK (already at a cdk cell); for P and P-near rows also the D1 carriers with minus-carrier
        cdk totals.  Rows already in OUT are skipped (resumable).

Notes: kitlib.score_at(diff=True) returns total=None, so totals come from a second plain score.
The cdk cfg is derived from the row's CURRENT registered cfg (read from the tool, not the list).
"""
import argparse, difflib, json, sys
from multiprocessing import Pool

sys.path.insert(0, str(__import__("pathlib").Path(__file__).resolve().parent / "lanekit"))
import kitlib                                                              # noqa: E402
from retailmap import scorer_rows                                          # noqa: E402

LANE = kitlib.bootstrap()


def cdk_cfg(cfg):
    parts = cfg.split()
    g = "-G0" if parts[0].endswith("-G0") else ""
    return " ".join(["2.7.2-cdk" + g] + parts[1:])


def is_cdk(cfg):
    return "cdk" in cfg.split()[0]


def total(row, text, cfg):
    v = kitlib.score_at(row, text, cfg=cfg)
    return v.get("total") if v.get("status") == "ok" or v.get("total") is not None else v.get("status")


def gen(row, text, cfg):
    v = kitlib.score_at(row, text, cfg=cfg, diff=True)
    return [x[1] for x in scorer_rows(v.get("text") or "")]


def ndiff(a, b):
    d = difflib.unified_diff(a, b, n=0, lineterm="")
    return sum(1 for l in d if l[:1] in "+-" and not l.startswith(("+++", "---")))


def get_text(row, which):
    base = kitlib.base_text(row, LANE)
    if which == "pinned":
        return base
    if which == "erased":
        return kitlib.erased_text(base)
    return open(which).read()


def carriers(row, cfg_a, cfg_b):
    """D1 rows: [{i, macro, arg, line, cell_diff, minus_total}]"""
    base = kitlib.base_text(row, LANE)
    ss = kitlib.sites(base)
    out = []
    for i, s in enumerate(ss):
        keep_only = kitlib.erase(base, [t for j, t in enumerate(ss) if j != i])
        minus = kitlib.erase(base, [s])
        cd = ndiff(gen(row, keep_only, cfg_a), gen(row, keep_only, cfg_b))
        out.append({"i": i, "macro": s[1], "arg": str(s[2]), "line": s[5], "cell_diff": cd,
                    "minus_total": total(row, minus, cfg_b)})
    return out


def census_one(rid):
    try:
        row = kitlib.row_of(rid)
        reg = row["cfg"]
        out = {"id": row["id"], "cfg_reg": reg}
        if is_cdk(reg):
            out["class"] = "CDK"
            return out
        cdk = cdk_cfg(reg)
        out["cfg_cdk"] = cdk
        base = kitlib.base_text(row, LANE)
        er = kitlib.erased_text(base)
        out["pins"] = len(kitlib.sites(base))
        out["d0"] = ndiff(gen(row, er, reg), gen(row, er, cdk))
        out["er_reg"], out["er_cdk"] = total(row, er, reg), total(row, er, cdk)
        out["pinned_cdk"] = total(row, base, cdk)
        out["class"] = "P" if out["d0"] == 0 else "P-near" if out["d0"] <= 4 else "D"
        if out["class"] != "D" and out["pins"]:
            out["carriers"] = carriers(row, reg, cdk)
        return out
    except BaseException as e:                                             # noqa: BLE001
        return {"id": rid, "err": repr(e)[:300]}


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("row", nargs="?")
    ap.add_argument("--text", default="pinned")
    ap.add_argument("--cfg", action="append", default=[])
    ap.add_argument("--carriers", action="store_true")
    ap.add_argument("--census")
    ap.add_argument("--out")
    ap.add_argument("--procs", type=int, default=4)
    a = ap.parse_args()
    if a.census:
        ids = [l.strip() for l in open(a.census) if l.strip()]
        done = set()
        try:
            done = {json.loads(l)["id"] for l in open(a.out) if l.strip()}
        except FileNotFoundError:
            pass
        todo = [i for i in ids if i not in done and kitlib.row_of(i)["id"] not in done]
        with Pool(a.procs) as p, open(a.out, "a") as f:
            for r in p.imap_unordered(census_one, todo):
                f.write(json.dumps(r) + "\n"); f.flush()
                print(r["id"], r.get("class", r.get("err")), r.get("d0"), flush=True)
        return
    if not a.row:
        ap.error("row or --census required")
    row = kitlib.row_of(a.row)
    if a.carriers:
        if not a.cfg:
            ap.error("--carriers needs --cfg B")
        cb = a.cfg[-1]
        ca = a.cfg[0] if len(a.cfg) > 1 else row["cfg"]
        print("%s  reg=%s  B=%s" % (row["id"], ca, cb))
        for c in carriers(row, ca, cb):
            print("pin%-2d %-14s %-22s line %-5s cell-diff %-4s total@B-minus-pin %s"
                  % (c["i"], c["macro"], c["arg"], c["line"], c["cell_diff"], c["minus_total"]))
        return
    if len(a.cfg) != 2:
        ap.error("need --cfg A --cfg B")
    text = get_text(row, a.text)
    ga, gb = gen(row, text, a.cfg[0]), gen(row, text, a.cfg[1])
    print("%s text=%s  gen-line diff = %d" % (row["id"], a.text, ndiff(ga, gb)))
    for c in a.cfg:
        print("  total @ %-40s %s" % (c, total(row, text, c)))


if __name__ == "__main__":
    main()
