#!/usr/bin/env python3
"""Gather a merge group's placements that are split over overlapping same-delta link views into ONE view.

    python3 tools/tu/view_merge.py plan --groups refs/groups.tsv --status gs_images.tsv --work W --out PLAN.json
    python3 tools/tu/view_merge.py apply PLAN.json [--check]

Several v0 link lists describe overlapping views of one physical load (bank_99b000 and s2_img_99b060_8016a860,
image_3e8000 and region_3e8280_3ed488: same container, same load delta).  A placement entry lives in exactly one
of them, so a merged home file's members can be spread over two views and tu_placements reports the image as
partial (tub11 G00278, tub7 G00699, tu7 main.c pair).  This tool moves the group's member entries into the
enclosing view.  Moving an entry changes which link-list rules resolve its symbols (rule 3 local definitions,
rule 4 layout tag, rule 5 image symbols) and changes rule 3 for every other entry of both views, so every
entry of every touched view is re-resolved: each address symbol of its home object (compiled exactly as the
gate compiles the placement, tools/tu/copy_place.py) must resolve to the same address after the move; where
it would not, the old resolution is written as an explicit binding (resolution preserved).  The window gate
remains the proof.
"""
from __future__ import annotations

import argparse
import csv
import json
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(ROOT / "tools"), str(ROOT / "tools/gate"), str(ROOT / "tools/tu")]
import linklist as L  # noqa: E402
import copy_place as CP  # noqa: E402
import source_layout as SL  # noqa: E402

NM = "mipsel-linux-gnu-nm"


def home_symbols(root, home, work, cache):
    """Address symbols (func_/D_<addr>) the home's placement object references or defines."""
    if home in cache:
        return cache[home]
    reg = CP.registry(root)
    h = reg[home]
    w = work / home.replace("/", "_")
    w.mkdir(parents=True, exist_ok=True)
    unit = SL.member_projection(home, root)
    src = w / (home.split("/", 1)[1] + ".c")
    src.write_bytes(unit if unit is not None else (root / SL.row_relative(h, root)).read_bytes())
    o = w / "home.o"
    if not o.exists():
        CP._compile(src, o, h["cfg"], home.split("/", 1)[1], L.family(h["container"]), h["foff"], w / "ev")
    out = subprocess.run([NM, str(o)], capture_output=True, text=True, check=True).stdout
    syms = sorted({int(m.group(2), 16) for m in (L.ADDR.match(l.split()[-1]) for l in out.splitlines() if l.split()) if m})
    cache[home] = syms
    return syms


def plan(root, groups, status, work):
    images, by_place, by_row, local = L.load(root)
    reg = CP.registry(root)
    gs = {g["group_id"]: g for g in groups}
    moves = {}  # row -> target image
    why = {}
    for r in status:
        if r["state"] != "partial":
            continue
        g = gs[r["group"]]
        members = [m for m in g["member_rows"].split(";") if m]
        dimg = images[r["image"]]
        delta = dimg["vma"] - dimg["foff"]
        here = {e["home"]: e for e in by_row.values() if e["image"] == r["image"] and e["row"] != e["home"]}
        placed = [m for m in members if m in here]
        if not placed:
            continue
        d = here[placed[0]]["foff"] - reg[placed[0]]["foff"]
        ents = []
        for m in members:
            f = reg[m]["foff"] + d if m in reg else None
            e = [x for x in by_row.values() if x["home"] == m and x["foff"] == f and x["row"] != m]
            if len(e) != 1:
                ents = None
                break
            ents.append(e[0])
        if not ents:
            continue
        views = {e["image"] for e in ents}
        if any(images[v]["vma"] - images[v]["foff"] != delta for v in views):
            continue
        if any(images[v]["schema"] != L.SCHEMA for v in views):
            continue  # a whole-image byte map (v1) must keep tiling: its code entries never move
        lo = min(e["foff"] for e in ents)
        hi = max(e["foff"] + e["size"] for e in ents)
        cands = [images[v] for v in views | {r["image"]} if images[v]["foff"] <= lo and hi <= images[v]["foff"] + images[v]["size"]
                 and images[v]["schema"] == L.SCHEMA]
        if not cands:
            continue
        target = max(cands, key=lambda i: (i["size"], -len(i["image"])))["image"]
        if any(e["image"] != target and images[e["image"]]["schema"] != L.SCHEMA for e in ents):
            continue
        for e in ents:
            if e["image"] != target:
                if moves.get(e["row"], target) != target:
                    why.setdefault("conflict", []).append(e["row"])
                    continue
                moves[e["row"]] = target
                why.setdefault(e["row"], set()).add(r["group"])
    if not moves:
        return dict(moves={}, bindings={})
    out = preserve(root, moves, work)
    out["groups"] = {k: sorted(v) for k, v in why.items() if isinstance(v, set)}
    return out


def preserve(root, moves, work):
    """Preserve resolution globally, including canonical-home namespace changes.

    Moving a code entry changes local lookup only at its home's address. Moving
    an own-home entry also changes the home-image rules for all of its copies.
    Check those critical addresses for every placement; check the full symbol
    inventory of each moved entry or changed-home copy. No other binding input
    changes. Unused ambiguous critical addresses do not create fake refusals.
    """
    images, by_place, by_row, local = L.load(root)
    requested = dict(moves)
    moves = {}
    for rid, target in requested.items():
        if rid not in by_row or target not in images:
            raise ValueError('unknown gather row/image: ' + rid)
        entry = by_row[rid]
        old, new = images[entry['image']], images[target]
        if entry['image'] == target:
            continue
        if (old['schema'] != L.SCHEMA or new['schema'] != L.SCHEMA
                or old['container'] != new['container'] or new.get('vma') is None
                or new['vma'] - new['foff'] != entry['vma'] - entry['foff']
                or not (new['foff'] <= entry['foff']
                        and entry['foff'] + entry['size'] <= new['foff'] + new['size'])):
            raise ValueError('gather requires enclosing same-delta legacy views: ' + rid)
        moves[rid] = target
    touched = {by_row[x]['image'] for x in moves} | set(moves.values())
    changed_homes = {rid for rid in moves if by_row[rid]['home'] == rid}
    critical = {by_row[by_row[rid]['home']]['vma'] for rid in moves}
    new_by_row = dict(by_row)
    for rid, target in moves.items():
        new_by_row[rid] = dict(by_row[rid], image=target)
    new_local = {}
    for entry in new_by_row.values():
        home = new_by_row[entry['home']]
        if entry['row'] != entry['home']:
            new_local.setdefault(entry['image'], {}).setdefault(home['vma'], []).append(
                (home['image'], entry['vma']))
    old_tables = (images, by_place, by_row, local)
    new_tables = (images, by_place, new_by_row, new_local)
    cache, extra, refused = {}, {}, []
    for entry in new_by_row.values():
        if entry['row'] == entry['home']:
            continue
        old_entry = by_row[entry['row']]
        needs_inventory = entry['row'] in moves or entry['home'] in changed_homes
        symbols = None
        try:
            if needs_inventory:
                symbols = set(home_symbols(root, entry['home'], work, cache))
            addresses = critical | (symbols or set())
            for address in sorted(addresses):
                try:
                    before = L._binding(old_tables, old_entry, address)
                except ValueError as exc:
                    if symbols is None:
                        symbols = set(home_symbols(root, entry['home'], work, cache))
                    if address in symbols:
                        refused.append((entry['row'], 'old resolution ambiguous: ' + str(exc)))
                    continue
                try:
                    after = L._binding(new_tables, entry, address)
                except ValueError:
                    after = None
                if before != after:
                    extra.setdefault(entry['row'], {})['0x%08X' % address] = '0x%08X' % before
        except Exception as exc:
            refused.append((entry['row'], 'home compile: ' + str(exc)))
    touched.update(by_row[rid]['image'] for rid in extra)
    return dict(moves=moves, bindings=extra, refused=refused, touched=sorted(touched),
                changed_homes=sorted(changed_homes), critical_addresses=sorted(critical))


def apply(root, p, check=False):
    if p.get("refused"):
        raise ValueError("binding-preservation plan has unresolved refusals")
    moves, extra = p["moves"], p["bindings"]
    docs = {}
    for path in L.files(root):
        docs[path] = json.loads(path.read_text())
    byimg = {d["image"]: path for path, d in docs.items()}
    taken = {}
    for path, d in docs.items():
        for e in list(d["entries"]):
            if not L.is_code(e):
                continue
            row = e["row"]
            if row in extra:
                b = e.setdefault("bindings", {})
                for k, v in extra[row].items():
                    if b.get(k, v) != v:
                        raise SystemExit("explicit binding conflict %s %s" % (row, k))
                    b[k] = v
            if row in moves and d["image"] != moves[row]:
                d["entries"].remove(e)
                e["evidence"] = (e.get("evidence", "") + "; " if e.get("evidence") else "") + \
                    "TU view gather: moved from %s (same load delta) so the merged file's members share one view" % d["image"]
                taken[row] = e
    for row, e in taken.items():
        d = docs[byimg[moves[row]]]
        f = L.num(e["foff"])
        pos = next((k for k, x in enumerate(d["entries"]) if L.num(x["foff"]) > f), len(d["entries"]))
        d["entries"].insert(pos, e)
    if check:
        return dict(moved=len(taken), rebound=len(extra))
    for path, d in docs.items():
        new = json.dumps(d, indent=2) + "\n"
        if path.read_text() != new and (d["image"] in p["touched"]):
            path.write_text(new)
    L.load(root)  # validate
    return dict(moved=len(taken), rebound=len(extra))


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    a = sub.add_parser("plan"); a.add_argument("--groups", action="append", required=True)
    a.add_argument("--status", required=True); a.add_argument("--work", required=True); a.add_argument("--out", required=True)
    a.add_argument("--only", nargs="*")
    a = sub.add_parser("apply"); a.add_argument("plan"); a.add_argument("--check", action="store_true")
    args = ap.parse_args()
    if args.cmd == "plan":
        groups = []
        for g in args.groups:
            groups.extend(csv.DictReader(open(g), delimiter="\t"))
        status = list(csv.DictReader(open(args.status), delimiter="\t"))
        if args.only:
            status = [s for s in status if s["group"] in set(args.only)]
        p = plan(ROOT, groups, status, Path(args.work).absolute())
        Path(args.out).write_text(json.dumps(p, indent=1) + "\n")
        print(json.dumps(dict(moves=len(p["moves"]), rebound_entries=len(p["bindings"]), refused=len(p.get("refused", [])),
                              touched=len(p.get("touched", [])))))
    else:
        print(json.dumps(apply(ROOT, json.loads(Path(args.plan).read_text()), args.check)))


if __name__ == "__main__":
    main()
