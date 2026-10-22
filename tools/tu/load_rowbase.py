#!/usr/bin/env python3
"""Proven rowbase records for link images whose load base the bytes already prove (item 3, opus_place1).

    python3 tools/tu/load_rowbase.py --images town/ll34_552000_80016000 ... [--write] [--out OUT.json]
    python3 tools/tu/load_rowbase.py --all-load-evidence [--write]

A module placement (docs/LL5_MODULE_PLACEMENTS.md, tools/tu/tu_placements.py) needs every member byte inside
a PROVEN rowbase region at the destination image's delta.  LL4 placements in images that carry only a
`load_evidence` record (ledger/instance_load_regions.jsonl, accepted by linklist.placement_vma) already link
at that base, but no rowbase region records it.  This tool mints one region per image, ONLY when all hold:

  L1  the image binds an exact current load record (sha256) whose method linklist accepts
      (validated loader record / internal link-evidence) and whose base/delta equal the image's;
  L2  the bytes pin the delta: >= 1 absolute internal reference in retail code of the image (jal into the
      image landing on a registered function start of the image, at image vma = foff + delta);
  L3  every registered split row inside the extent links at foff + delta (true name / true vram), and no row
      straddles the extent;
  L4  no existing rowbase record overlaps the extent (a same-delta overlap is reported for `tu_merge region`
      widening instead; a different delta is a conflict);
  L5  the code rows inside are proven byte-exact at that base by their windows (ledger/gate.jsonl MATCH at
      the current inputs, or the scoped gate the caller runs after --write; the record cites the windows).

Unprovable images are reported with the failed condition; nothing is guessed.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(ROOT / "tools"), str(ROOT / "tools/gate")]
import linklist as L  # noqa: E402

CONTAINER_BIN = {"town": "work/disc/extract/TOWN/TOWN.BIN", "dungeon": "work/disc/containers/DUNGEON_DUNGEON.BIN",
                 "main": "work/disc/containers/MAIN_MAIN.BIN", "ovmovie": "work/disc/containers/OVMOVIE.BIN"}


def jl(p):
    p = Path(p)
    return [json.loads(l) for l in p.read_text().splitlines() if l.strip().startswith("{")] if p.exists() else []


def rec_sha(r):
    return hashlib.sha256(json.dumps(r, sort_keys=True, separators=(",", ":")).encode()).hexdigest()


def assess(root, image, images, splits, rowbase, gate, wm):
    from common import covering_windows
    img = images[image]
    cont = img["container"]
    lo, hi, vma = img["foff"], img["foff"] + img["size"], img["vma"]
    delta = vma - lo
    out = dict(image=image, foff_start="0x%X" % lo, foff_end="0x%X" % hi, delta="0x%X" % delta, ok=False)
    proof = img.get("load_evidence")
    if not proof:
        return dict(out, reason="L1: no load_evidence record bound to the image")
    hits = [r for r in jl(root / proof["path"]) if rec_sha(r) == proof["record_sha256"]]
    if len(hits) != 1:
        return dict(out, reason="L1: load record missing or stale")
    r = hits[0]
    if (not str(r.get("method", "")).startswith(L.LOAD_METHODS) or L.num(r["delta"]) != delta
            or not L.num(r["foff"]) <= lo < hi <= L.num(r["foff"]) + L.num(r["size"])):
        return dict(out, reason="L1: load record method/base/extent disagrees")
    out["load_record_sha256"] = proof["record_sha256"]
    out["load_method"] = r["method"]
    # L3: trim the extent off split rows that straddle the image edges (the split table partitions the
    # container, not the image); every row inside the trimmed extent must link at foff + delta
    for s_ in splits:
        if s_.get("rerun") or not isinstance(s_.get("foff"), int):
            continue
        a, b = s_["foff"], s_["foff"] + int(s_.get("size") or 0)
        if (a < lo < b or a < hi < b) and s_.get("result") == "MATCH":
            return dict(out, reason="L3: registered code row %s (0x%X..0x%X) straddles the image edge: the image "
                                    "extent itself is not proven" % (s_["func_vram"], a, b))
        if a < lo < b:
            lo = b
        if a < hi < b:
            hi = a
    if lo >= hi:
        return dict(out, reason="L3: straddling rows leave no extent")
    out["trimmed"] = [hex(lo), hex(hi)]
    inside, bad = [], []
    for s_ in splits:
        if s_.get("rerun") or not isinstance(s_.get("foff"), int):
            continue
        a, b = s_["foff"], s_["foff"] + int(s_.get("size") or 0)
        if b <= lo or a >= hi:
            continue
        v = L.split_vma(s_)
        if s_.get("result") == "MATCH" and v != a + delta:
            bad.append("%s links at %s" % (s_["func_vram"], hex(v or 0)))
        inside.append(s_)
    if bad:
        return dict(out, reason="L3: " + "; ".join(bad[:6]))
    # L4: existing records stay untouched; new records fill only the gaps between same-delta PROVEN records
    over = sorted((int(x["foff_start"], 0), int(x["foff_end"], 0), x) for x in rowbase
                  if int(x["foff_start"], 0) < hi and lo < int(x["foff_end"], 0))
    conflict = [x["region"] for _, _, x in over if int(x["delta"], 0) != delta]
    if conflict:
        return dict(out, reason="L4: overlaps region(s) at another delta %s" % conflict)
    weak = [x["region"] for _, _, x in over if x.get("base_confidence") != "proven"]
    if weak:
        return dict(out, reason="L4: same-delta region(s) not proven (promote first) %s" % weak)
    gaps, cur = [], lo
    for a, b, _ in over:
        if a > cur:
            gaps.append((cur, min(a, hi)))
        cur = max(cur, b)
    if cur < hi:
        gaps.append((cur, hi))
    out["existing"] = [x["region"] for _, _, x in over]
    if not gaps:
        return dict(out, reason="L4: already covered by proven regions at this delta")
    # L2: absolute internal calls in retail code of the image
    data = (root / CONTAINER_BIN[cont]).read_bytes()
    starts = {L.split_vma(s) for s in inside if s.get("result") == "MATCH"}
    calls = 0
    for s in inside:
        if s.get("result") != "MATCH":
            continue
        for o in range(s["foff"], s["foff"] + s["size"], 4):
            w = int.from_bytes(data[o:o + 4], "little")
            if w >> 26 == 3:  # jal
                t = ((o + delta + 4) & 0xF0000000) | ((w & 0x03FFFFFF) << 2)
                if vma <= t < vma + img["size"] and t in starts:
                    calls += 1
    out["internal_calls"] = calls
    if not calls:
        return dict(out, reason="L2: no absolute internal reference pins the delta")
    # L5
    wins = sorted({w[0] for s in inside if s.get("result") == "MATCH" for w in covering_windows(cont, s["foff"], s["size"], wm)})
    out["windows"] = ["config/overlays/" + w for w in wins]
    out["gate_match_at_base"] = sorted(w for w in wins if gate.get(w) == "MATCH")
    out["rows"] = sum(1 for s in inside if s.get("result") == "MATCH")
    out["ok"] = True
    out["reason"] = ""
    base_proof = ("opus_place1 load map (item 3): link image config/link/%s.json loads file 0x%X..0x%X at 0x%X "
                  "(delta 0x%X). L1 load record %s (%s, ledger/instance_load_regions.jsonl sha256 %s); L2 %d absolute "
                  "jal(s) in retail code of the image land on registered function starts inside it at this delta; L3 "
                  "all %d registered rows inside the trimmed extent 0x%X..0x%X link at foff+delta; L4 existing proven "
                  "same-delta regions kept unchanged: %s; L5 byte-exact window gates at this base: %s."
                  % (image, img["foff"], img["foff"] + img["size"], vma, delta, r.get("evidence"), r["method"],
                     proof["record_sha256"][:16], calls, out["rows"], lo, hi, ", ".join(out["existing"]) or "none",
                     ", ".join(wins)))
    out["records"] = [dict(schema="azure-clean.rowbase.v1",
                           region="load_%s%s" % (image.split("/", 1)[1], "" if len(gaps) == 1 else "_%X" % a),
                           foff_start="0x%X" % a, foff_end="0x%X" % b, delta="0x%X" % delta, base_confidence="proven",
                           reviewer="opus_place1", load_record_sha256=proof["record_sha256"], proof=base_proof)
                      for a, b in gaps]
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--root", type=Path, default=ROOT)
    ap.add_argument("--images", nargs="*", default=[])
    ap.add_argument("--all-load-evidence", action="store_true")
    ap.add_argument("--write", action="store_true")
    ap.add_argument("--out")
    a = ap.parse_args()
    root = a.root.resolve()
    from common import window_map
    images, _, _, _ = L.load(root)
    names = list(a.images)
    if a.all_load_evidence:
        names += sorted(k for k, v in images.items() if v.get("load_evidence") and k not in names)
    res = []
    gate = {}
    for g in jl(root / "ledger/gate.jsonl"):
        gate[g.get("window")] = g.get("result")
    wm = window_map()
    by_cont = {}
    for name in names:
        cont = images[name]["container"]
        if cont not in by_cont:
            by_cont[cont] = (jl(root / f"ledger/splits/{cont}.jsonl"), jl(root / f"config/overlays/{cont}.rowbase.jsonl"))
        splits, rowbase = by_cont[cont]
        res.append(assess(root, name, images, splits, rowbase, gate, wm))
    # records minted in one run must not overlap each other (different images, different deltas)
    minted = sorted((int(rr["foff_start"], 0), int(rr["foff_end"], 0), x["image"]) for x in res if x["ok"] for rr in x["records"])
    for (a1, b1, i1), (a2, b2, i2) in zip(minted, minted[1:]):
        if a2 < b1:
            for x in res:
                if x["image"] in (i1, i2) and x["ok"]:
                    x.update(ok=False, reason="L4: extent overlaps the load image %s (two bases for one file range)"
                             % (i2 if x["image"] == i1 else i1))
    if a.write:
        for cont in sorted({images[x["image"]]["container"] for x in res if x["ok"]}):
            p = root / f"config/overlays/{cont}.rowbase.jsonl"
            have = {x.get("region") for x in jl(p)}
            add = [rr for x in res if x["ok"] and images[x["image"]]["container"] == cont
                   for rr in x["records"] if rr["region"] not in have]
            if add:
                text = p.read_text()
                if text and not text.endswith("\n"):
                    text += "\n"
                p.write_text(text + "".join(json.dumps(r, sort_keys=True) + "\n" for r in add))
                print("wrote %d records to %s" % (len(add), p.relative_to(root)))
    if a.out:
        Path(a.out).write_text(json.dumps(res, indent=1) + "\n")
    for x in res:
        state = "OK" if x["ok"] else ("ALREADY" if x["reason"].startswith("L4: already covered") else "HOLD")
        print(x["image"], state, x.get("internal_calls", ""), x["reason"][:160])


if __name__ == "__main__":
    main()
