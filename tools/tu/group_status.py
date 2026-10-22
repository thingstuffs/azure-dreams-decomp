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


def destination_facts(group, images, by_row, reg, regions=()):
    """Account for unindexed homes and registry-only copies before saying none.

    A span containing placements cannot be mistaken for independent home
    definitions. Numeric group IDs never substitute for ordered memberships.
    """
    members = [m for m in group['member_rows'].split(';') if m]
    homes, missing, placed, home_regions = {}, [], [], []
    for rid in members:
        row = reg.get(rid)
        if row is None:
            missing.append('unregistered member ' + rid)
            continue
        home = row.get('source_row') or rid
        homes[rid] = home
        if home != rid:
            placed.append(rid + '->' + home)
        if rid in by_row:
            continue
        image = images.get(group['image'])
        mapped = [(lo, hi, delta, name) for lo, hi, delta, confidence, name in regions
                  if confidence == 'proven' and row.get('foff') is not None
                  and lo <= row['foff'] < row['foff'] + row['size'] <= hi]
        if len(mapped) == 1:
            home_regions.append(rid + '@' + mapped[0][3] + ':delta=' + hex(mapped[0][2]))
        elif not image or image.get('vma') is None or row.get('foff') is None or not (
                image['foff'] <= row['foff'] < row['foff'] + row['size'] <= image['foff'] + image['size']):
            missing.append('no indexed entry or enclosing load image for ' + rid)
    ultimate = set(homes.values())
    for rid, row in reg.items():
        if row.get('source_row') in ultimate and rid not in by_row:
            missing.append('registry copy lacks link-list entry ' + rid + '->' + row['source_row'])
    destinations = sorted({e['image'] for rid, e in by_row.items()
                           if e['home'] in ultimate and rid not in members})
    return dict(home_rows=';'.join(dict.fromkeys(homes.values())), home_regions=';'.join(home_regions), linked_images=';'.join(destinations),
                placed_members=';'.join(placed), missing_facts=';'.join(missing))


def status(root, groups):
    root = Path(root)
    copies = copy_homes(root)
    images, by_place, by_row, _ = L.load(root)
    reg, by_foff = own_file_rows(root)
    regs = {c: rowbase(root, c) for c in ("main", "town", "dungeon", "ovmovie")}
    out_groups, out_images = [], []
    for g in groups:
        facts = destination_facts(g, images, by_row, reg, regs.get(L.family(g['container']), ()))
        members = [m for m in g["member_rows"].split(";") if m]
        cont = g["container"]
        hom = [by_row.get(m) for m in members]
        per_image, duplicates = {}, {}
        for rid, e in by_row.items():
            if e["home"] in members and rid not in members:
                previous = per_image.get(e['image'], {}).get(e['home'])
                if previous is not None:
                    duplicates.setdefault(e['image'], []).append(previous['row'] + ',' + e['row'])
                per_image.setdefault(e["image"], {})[e["home"]] = e
        states = []
        for img, hits in sorted(per_image.items()):
            dimg = images[img]
            delta = dimg["vma"] - dimg["foff"]
            disp = {(e["foff"] - reg[h]["foff"]) for h, e in hits.items() if h in reg}
            row = dict(group=g["group_id"], image=img, placed=len(hits), members=len(members), delta=hex(delta))
            if img in duplicates:
                row.update(state='duplicate_home_placements', detail='multiple copies of one home: ' + ';'.join(duplicates[img]))
            elif img == g["image"] and len(hits) < len(members):
                row.update(state="in_image_copy", detail="decision 75: merged home needs all members; missing " +
                           ';'.join(m for m in members if m not in hits))
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
        if counts and set(counts) == {'complete'}:
            hard = [b for b in hard if b != 'member_has_in_image_placement_copy']
        if not states:
            dest = 'member_sites_are_placements' if facts['placed_members'] else 'no_destination_images'
        elif set(counts) == {"complete"}:
            dest = "all_complete"
        else:
            dest = ",".join("%s:%d" % kv for kv in sorted(counts.items()))
        if facts['missing_facts']:
            hard.append('destination_membership_unresolved')
        if facts['placed_members']:
            hard.append('group_contains_placement_members')
        mergeable = not hard and dest in ("no_destination_images", "all_complete")
        out_groups.append(dict(group=g["group_id"], image=g["image"], level=g.get("level", ""), container=cont,
                               members=len(members), tu7_blockers=",".join(sorted(blockers)) or "none",
                               hard_blockers=",".join(hard) or "none", destinations=dest,
                               mergeable_now="yes" if mergeable else "no", **facts))
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
