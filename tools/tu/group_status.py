#!/usr/bin/env python3
"""Destination-image status of merge groups (tu7 groups.tsv / tub holds) after copies became placements.

    python3 tools/tu/group_status.py --groups refs/groups.tsv [--groups more.tsv] --out OUT.tsv [--images IMG.tsv]

A merged home file is ONE object, so every other image that links any member must link ALL members at
one displacement (tools/tu/tu_placements.py).  Per group and destination image this reports:

  complete      every member placed, one displacement, every member byte in proven rowbase at the image delta
  no_rowbase    complete, but the image has no proven rowbase over the members (load map gap, item 3)
  partial       some members placed; for each missing member the census of own-file copies at the expected
                displacement says whether a relinked copy still holds the slot (copy_pending) or nothing does
  displaced     members placed but not at one displacement

A group is `mergeable_now` when its image list is all `complete` (or it has no destination images) and its
own tu7 blockers are only soft ones; `--images` writes the per-image rows.
"""
from __future__ import annotations

import argparse
import csv
import json
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(ROOT / "tools"), str(ROOT / "tools/gate"), str(ROOT / "tools/tu")]
import linklist as L  # noqa: E402

SOFT = {"mixed_registered_cells", "needs_module_placements", "member_is_placement", "image_data_outside_region",
        "cross_image_partial", "none", ""}


def jl(p):
    p = Path(p)
    return [json.loads(l) for l in p.read_text().splitlines() if l.strip().startswith("{")] if p.exists() else []


def rowbase(root, container):
    return sorted((int(r["foff_start"], 0), int(r["foff_end"], 0), int(r["delta"], 0), r["base_confidence"], r["region"])
                  for r in jl(Path(root) / ("config/overlays/%s.rowbase.jsonl" % container)))


def covered(regs, extents, delta):
    for start, stop in extents:
        cursor = start
        for lo, hi, d, conf, _ in regs:
            if hi <= cursor or lo >= stop:
                continue
            if lo > cursor or conf != "proven" or d != delta:
                return False
            cursor = min(hi, stop)
        if cursor != stop:
            return False
    return True


def own_file_rows(root):
    reg = {r["id"]: r for r in jl(Path(root) / "ledger/rows.jsonl")}
    by_foff = {}
    for rid, r in reg.items():
        if r.get("foff") is not None and not r.get("source_row"):
            by_foff[(L.family(r["container"]), r["foff"])] = r
    return reg, by_foff


def copy_homes(root):
    """{copy row: ultimate home} from the relinked-copy census (tools/tu/copy_place.py)."""
    import copy_place as CP
    c = CP.copy_rows(root)
    homes = {k: v["home"] for k, v in c.items()}
    return {k: CP.ultimate_home(v["home"], homes) for k, v in c.items()}


def status(root, groups):
    root = Path(root)
    copies = copy_homes(root)
    images, by_place, by_row, _ = L.load(root)
    reg, by_foff = own_file_rows(root)
    regs = {c: rowbase(root, c) for c in ("main", "town", "dungeon", "ovmovie")}
    out_groups, out_images = [], []
    for g in groups:
        members = [m for m in g["member_rows"].split(";") if m]
        cont = g["container"]
        hom = [by_row.get(m) for m in members]
        per_image = {}
        for rid, e in by_row.items():
            if e["home"] in members and rid not in members:
                per_image.setdefault(e["image"], {})[e["home"]] = e
        states = []
        for img, hits in sorted(per_image.items()):
            dimg = images[img]
            delta = dimg["vma"] - dimg["foff"]
            disp = {(e["foff"] - reg[h]["foff"]) for h, e in hits.items() if h in reg}
            row = dict(group=g["group_id"], image=img, placed=len(hits), members=len(members), delta=hex(delta))
            if img == g["image"]:
                row.update(state="in_image_copy", detail="the group's own image places a member copy (72(g))")
            elif len(disp) != 1:
                row.update(state="displaced", detail="members at %d displacements" % len(disp))
            elif len(hits) < len(members):
                d = disp.pop()
                missing = [m for m in members if m not in hits]
                slots = []
                for m in missing:
                    r = reg.get(m)
                    x = by_foff.get((L.family(cont), r["foff"] + d)) if r else None
                    if x is None:
                        slots.append("%s:empty" % m)
                    elif copies.get(x["id"]) == m:
                        slots.append("%s:copy_pending:%s" % (m, x["id"]))
                    else:
                        slots.append("%s:own_file:%s" % (m, x["id"]))
                pend = all(":copy_pending:" in x for x in slots)
                row.update(state="partial_copy_pending" if pend else "partial", detail=";".join(slots))
            else:
                need = [(e["foff"], e["foff"] + e["size"]) for e in hits.values()]
                if covered(regs[L.family(cont)], need, delta):
                    row.update(state="complete", detail="")
                else:
                    row.update(state="no_rowbase", detail="no proven rowbase at delta 0x%X over the members" % delta)
            states.append(row)
            out_images.append(row)
        blockers = set((g.get("blockers") or "").split(",")) - {""}
        counts = {}
        for s in states:
            counts[s["state"]] = counts.get(s["state"], 0) + 1
        hard = sorted(blockers - SOFT)
        if not states:
            dest = "no_destination_images"
        elif set(counts) == {"complete"}:
            dest = "all_complete"
        else:
            dest = ",".join("%s:%d" % kv for kv in sorted(counts.items()))
        mergeable = not hard and dest in ("no_destination_images", "all_complete")
        out_groups.append(dict(group=g["group_id"], image=g["image"], level=g.get("level", ""), container=cont,
                               members=len(members), tu7_blockers=",".join(sorted(blockers)) or "none",
                               hard_blockers=",".join(hard) or "none", destinations=dest,
                               mergeable_now="yes" if mergeable else "no"))
    return out_groups, out_images


def write(rows, path):
    if not rows:
        Path(path).write_text("")
        return
    cols = list(rows[0])
    with open(path, "w") as f:
        f.write("\t".join(cols) + "\n")
        for r in rows:
            f.write("\t".join(str(r.get(c, "")) for c in cols) + "\n")


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--root", type=Path, default=ROOT)
    ap.add_argument("--groups", action="append", required=True)
    ap.add_argument("--out", required=True)
    ap.add_argument("--images")
    a = ap.parse_args()
    groups = []
    for p in a.groups:
        groups.extend(csv.DictReader(open(p), delimiter="\t"))
    g, i = status(a.root, groups)
    write(g, a.out)
    if a.images:
        write(i, a.images)
    from collections import Counter
    print(len(g), "groups;", dict(Counter(x["mergeable_now"] for x in g)),
          dict(Counter(s["state"] for s in i)))


if __name__ == "__main__":
    main()
