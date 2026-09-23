#!/usr/bin/env python3
"""Row lists for the r76 model A/B (docs/evidence/r76_measurement_protocol.md).  Builds nothing, launches nothing.

    python3 tools/lanes/ab_plan.py plan [--seed 76] [--out docs/evidence]     # the stratified single-serve design
    python3 tools/lanes/ab_plan.py feed --tier agy --packs 6 --prefix r76_gemf --out F   # F.whole.json, F.cluster.json
    python3 tools/lanes/ab_plan.py escalate --out FILE                         # failed single-serve rows, next tier
    python3 tools/lanes/ab_plan.py paired [--per-band 40]                      # the retired 120-lane paired plan

Design v2 (owner, 2026-09-23: small, mostly progress, but fair - "luna could solve 9/10 super trivial rows and astra
1/4 and we decide that's not good"):
  single serve   rows of bands 1-2 and 3-7 are STRATIFIED by band x container (dungeon | other) x difficulty tercile
                 and dealt at random within strata to the arms, so every arm sees the same difficulty mix and no row
                 is served twice.  Difficulty = the cc1 listing distance of erasing EVERY pin of the row (lines
                 added + removed in the normalised listing diff, tools/xform/screen.py - the same diff the pack's
                 rows.md shows the lane); a row whose erased text does not build is put in the hardest tercile.
                 Quotas per band: luna6, sol6(+residual_to_form), agy (Gemini), opus, sonnet 10 rows (2 packs) each,
                 astra 5 (1 pack).
  overlap        5 rows per band served to ALL six arms (lanes r76o_<arm>_<band>: outside land_finished2's r7[0-9]_*
                 glob, so nothing lands until every arm has finished), the head-to-head on identical rows.
  8+             cluster packs (--cluster 3-5) for astra only (2 packs); Gemini gets 8+ cluster packs from `feed`.
The pool: pinned rows (not ovmovie, not slus) no kit-era strong lane served at the current text (served.py
strong_kit_pool) and no launched lane of any arm's tier served at the current text (8+: as a cluster).
"""
import argparse
import json
import os
import random
import sys
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
sys.path.insert(0, str(Path(__file__).resolve().parent))
import served  # noqa: E402

ARMS = ("luna6", "sol6", "astra", "opus", "sonnet", "agy")
QUOTA = {"luna6": 10, "sol6": 10, "agy": 10, "opus": 10, "sonnet": 10, "astra": 5}   # rows per band
OVERLAP = 5
BANDS = (("b12", "1-2"), ("b37", "3-7"), ("b8c", "8+"))


def eligible(texts, root=ROOT, arms=ARMS):
    """[{row, pins, band, status}] of the A/B pool (see the module docstring)."""
    sk = served.strong_kit_serves(root)
    hit = set()
    for r in served.serve_records(root):
        cur = texts.get(r["row"])
        if not r["launched"] or r["tier"] not in arms or cur is None or r["sha"] != cur[0]:
            continue
        if (r["scope"] == "whole") == (cur[1] < 8):     # whole serves block whole packs, cluster serves cluster packs
            hit.add(r["row"])
    out = []
    for rid, (sha, pins, container) in sorted(texts.items()):
        if pins == 0 or container in ("ovmovie", "slus") or rid in hit:
            continue
        recs = sk.get(rid, [])
        if pins < 8 and any(r["sha"] == sha for r in recs):
            continue
        out.append({"row": rid, "pins": pins, "band": served.band_of(pins),
                    "status": "older-text" if recs and not any(r["sha"] == sha for r in recs)
                    else ("served-whole-at-this-text" if recs else "never")})
    return out


def draw(rows, per_band, pack, seed, arms=ARMS):
    """({lane: rows}, {band: [chosen rows]}): per band a seeded shuffle, cut to per_band, split into packs."""
    rng = random.Random(seed)
    lanes, chosen = {}, {}
    for tag, band in BANDS:
        b = sorted(r["row"] for r in rows if r["band"] == band)
        rng.shuffle(b)
        b = b[:per_band - per_band % pack] if len(b) >= per_band else b[:len(b) - len(b) % pack]
        chosen[band] = b
        for k in range(len(b) // pack):
            for arm in arms:
                lanes["r76_%s_%s_%d" % (arm, tag, k + 1)] = b[k * pack:(k + 1) * pack]
    return lanes, chosen


def listing_distance(rid, row=None, text=None):
    """Lines added + removed in the normalised cc1 listing when every pin of the row is erased; None if it does not
    build.  The difficulty proxy of the stratified draw."""
    import difflib
    sys.path[:0] = [str(ROOT / "tools"), str(ROOT / "tools/xform")]
    from common import clean_path
    from pin_census import sites_of
    from pin_sites import erase_many
    import screen
    t = text if text is not None else clean_path(row).read_text(errors="replace")
    a = screen.compile_s(row, t)
    b = screen.compile_s(row, erase_many(t, sites_of(t), clean_notes=True))
    if a is None or b is None:
        return None
    return sum(1 for l in difflib.unified_diff(a, b, lineterm="", n=0)
               if l[:1] in "+-" and not l.startswith(("+++", "---")))


def strata(rows, dist):
    """{row: (band, container group, tercile)} - terciles of the listing distance within each band x container."""
    out, groups = {}, {}
    for r in rows:
        cg = "dungeon" if r["row"].startswith("dungeon/") else "other"
        groups.setdefault((r["band"], cg), []).append(r["row"])
    for (band, cg), ids in groups.items():
        big = 10 ** 9
        ids = sorted(ids, key=lambda i: (big if dist.get(i) is None else dist[i], i))
        n = len(ids)
        for k, i in enumerate(ids):
            out[i] = (band, cg, "easy" if k < n / 3 else ("mid" if k < 2 * n / 3 else "hard"))
    return out


def assign(rows, strat, seed, quota=QUOTA, overlap=OVERLAP, pack=5):
    """Stratified random single-serve assignment for ONE band.
    Returns ({arm: [rows]}, [overlap rows], [sampled rows]).  The band's rows are ordered by stratum (random within),
    a systematic sample of sum(quota) + overlap rows is taken (so the sample keeps the strata proportions), `overlap`
    of them go to every arm, and the rest are dealt through blocks of one slot per quota unit (block order shuffled per
    block): consecutive rows of one stratum go to different arms, so each arm gets the same mix."""
    rng = random.Random(seed)
    ids = [r["row"] for r in rows]
    key = {i: rng.random() for i in ids}
    ids.sort(key=lambda i: (strat[i], key[i]))
    need = sum(quota.values()) + overlap
    if len(ids) < need:
        raise SystemExit("band has %d eligible rows, the design needs %d" % (len(ids), need))
    step = len(ids) / need
    start = rng.random() * step
    sample = [ids[int(start + k * step)] for k in range(need)]
    ostep = need / overlap
    ostart = int(rng.random() * ostep)
    ov = [sample[int(ostart + k * ostep)] for k in range(overlap)]
    rest = [i for i in sample if i not in ov]
    unit = min(quota.values())                                  # astra 5 -> a block holds 2,2,2,2,2,1 slots
    slots = [a for a, q in quota.items() for _ in range(q // unit)]
    out = {a: [] for a in quota}
    j = 0
    while j < len(rest):
        block = slots[:]
        rng.shuffle(block)
        for a in block:
            if j >= len(rest):
                break
            out[a].append(rest[j])
            j += 1
    for a in out:
        rng.shuffle(out[a])
    return out, ov, sample


def plan_v2(texts, seed=76, root=ROOT):
    """The stratified design: {lane: rows}, and the plan record."""
    sys.path.insert(0, str(ROOT / "tools"))
    from common import rows as all_rows
    by = {r["id"]: r for r in all_rows()}
    ok = [p for p in eligible(texts, root) if p["band"] in ("1-2", "3-7")]
    dist = {p["row"]: listing_distance(p["row"], by[p["row"]]) for p in ok}
    st = strata(ok, dist)
    lanes, rec = {}, {"seed": seed, "quota_per_band": QUOTA, "overlap_per_band": OVERLAP, "bands": {}}
    for tag, band in BANDS[:2]:
        rows_b = [p for p in ok if p["band"] == band]
        arms, ov, sample = assign(rows_b, st, seed + (0 if band == "1-2" else 1))
        for a, ids in arms.items():
            for k in range(0, len(ids), 5):
                lanes["r76_%s_%s_%d" % (a, tag, k // 5 + 1)] = ids[k:k + 5]
        for a in ARMS:
            lanes["r76o_%s_%s" % (a, tag)] = list(ov)
        pins = {p["row"]: p["pins"] for p in rows_b}
        mix = {}
        for a, ids in list(arms.items()) + [("overlap", ov)]:
            m = {}
            for i in ids:
                m["/".join(st[i][1:])] = m.get("/".join(st[i][1:]), 0) + 1
            mix[a] = m
        rec["bands"][band] = {"eligible": len(rows_b), "sampled": len(sample),
                              "arms": {a: [{"row": i, "pins": pins[i], "distance": dist[i], "stratum": "/".join(st[i][1:])}
                                           for i in ids] for a, ids in arms.items()},
                              "overlap": [{"row": i, "pins": pins[i], "distance": dist[i], "stratum": "/".join(st[i][1:])}
                                          for i in ov], "strata_mix": mix}
    big = sorted(p["row"] for p in eligible(texts, root) if p["band"] == "8+")
    rng = random.Random(seed + 8)
    rng.shuffle(big)
    for k in range(2):
        lanes["r76_astra_b8c_%d" % (k + 1)] = big[k * 5:(k + 1) * 5]
    rec["bands"]["8+"] = {"eligible": len(big), "astra_cluster": big[:10]}
    return lanes, rec


def feed(texts, tier, packs, root=ROOT, exclude=(), pack=5):
    """The next `packs` packs for a continuous pool of `tier` (the Gemini feed), in the owner's order:
    (1) escalation leftovers - rows a finished r76 single-serve lane failed, still at the text it was served;
    (2) never-strong-served rows by band (1-2, then 3-7), (3) 8+ rows as cluster packs.
    Rows `tier` already served at the current text (served.tier_overlap) and rows in `exclude` are skipped.
    Returns [(kind, [rows])] with kind 'whole' or 'cluster'."""
    recs = served.serve_records(root)
    seen = {r["row"] for r in recs if r["launched"] and r["tier"] == tier and texts.get(r["row"], (None,))[0] == r["sha"]}
    reserved = set(exclude)
    for r in recs:        # rows of an r76 lane still to run or running, and every overlap row: another arm's rows
        d = Path(root) / "work/native_lane" / r["lane"]
        if ((r["round"] or 0) >= 76 and not (d / "last_message.txt").exists()) or r["lane"].startswith("r76o_"):
            reserved.add(r["row"])
    esc = []
    for r in recs:
        cur = texts.get(r["row"])
        if (r["launched"] and r["lane"].startswith("r76_") and cur and cur[1] and r["sha"] == cur[0]
                and cur[1] < 8 and not (Path(root) / "work/native_lane" / r["lane"] / "out" / (r["row"] + ".c")).exists()
                and (Path(root) / "work/native_lane" / r["lane"] / "last_message.txt").exists()):
            esc.append(r["row"])
    order = []
    for rid in esc:
        if rid not in order:
            order.append(rid)
    pool = served.strong_kit_pool(root, texts)
    for band in ("1-2", "3-7"):
        order += [p["row"] for p in pool if p["band"] == band and p["row"] not in order]
    whole = [i for i in order if i not in seen and i not in reserved and not i.startswith(("slus/", "ovmovie/"))]
    out = []
    for k in range(0, len(whole), pack):
        if len(out) >= packs:
            return out
        out.append(("whole", whole[k:k + pack]))
    big = [rid for rid, (sha, pins, c) in sorted(texts.items())
           if pins >= 8 and c not in ("ovmovie", "slus") and rid not in reserved
           and not any(r["row"] == rid and r["tier"] == tier and r["launched"] and r["sha"] == sha and r["scope"] != "whole"
                       for r in recs)]
    for k in range(0, len(big), pack):
        if len(out) >= packs:
            break
        out.append(("cluster", big[k:k + pack]))
    return out


def escalate(texts, root=ROOT):
    """{next tier: [rows]}: rows a finished r76 single-serve lane failed, at the text it was served, sent up the
    ladder luna6/agy -> sol6 -> opus|astra (alternating), minus rows that tier already served at this text."""
    nxt = {"luna6": ["sol6"], "agy": ["sol6"], "sol6": ["opus", "astra"]}
    out, alt = {}, 0
    for r in served.serve_records(root):
        cur = texts.get(r["row"])
        d = Path(root) / "work/native_lane" / r["lane"]
        if not (r["launched"] and r["lane"].startswith("r76_") and cur and cur[1] and r["sha"] == cur[0]
                and (d / "last_message.txt").exists() and not (d / "out" / (r["row"] + ".c")).exists()):
            continue
        ups = nxt.get(r["tier"])
        if not ups:
            continue
        up = ups[alt % len(ups)]
        alt += 1
        if served.tier_overlap([r["row"]], up, texts, root):
            continue
        out.setdefault(up, [])
        if r["row"] not in out[up]:
            out[up].append(r["row"])
    return out


def paired_main(argv=None):
    ap = argparse.ArgumentParser(description="the retired paired plan (5 arms x 3 bands x 8 packs)")
    ap.add_argument("--per-band", type=int, default=40)
    ap.add_argument("--pack", type=int, default=5)
    ap.add_argument("--seed", type=int, default=76)
    ap.add_argument("--out", default=str(ROOT / "docs/evidence"))
    a = ap.parse_args(argv)
    texts = served.current_texts()
    pool = served.strong_kit_pool(texts=texts)
    ok = eligible(texts)
    lanes, chosen = draw(ok, a.per_band, a.pack, a.seed)
    info = {rid: p for p in ok for rid in [p["row"]]}
    counts = {}
    for p in pool + ok:
        counts.setdefault(p["band"], {"strong_kit_pool": 0, "eligible": 0, "eligible_pins": 0, "never": 0})
    for p in pool:
        counts[p["band"]]["strong_kit_pool"] += 1
    for p in ok:
        c = counts[p["band"]]
        c["eligible"] += 1
        c["eligible_pins"] += p["pins"]
        c["never"] += p["status"] == "never"
    plan = {"schema": "azure-clean.r76-ab-plan.v1", "seed": a.seed, "per_band": a.per_band, "pack": a.pack,
            "arms": list(ARMS), "bands": {band: tag for tag, band in BANDS}, "pool_counts": counts,
            "rows": {band: [{"row": r, "pins": info[r]["pins"], "status": info[r]["status"]} for r in rs]
                     for band, rs in chosen.items()}}
    out = Path(a.out)
    (out / "r76_ab_rows.json").write_text(json.dumps(lanes, indent=0) + "\n")
    (out / "r76_ab_plan.json").write_text(json.dumps(plan, indent=1) + "\n")
    for band, c in counts.items():
        print("band %-4s strong-kit pool %3d, eligible %3d (%d pins, %d never served), drawn %d" % (
            band, c["strong_kit_pool"], c["eligible"], c["eligible_pins"], c["never"], len(chosen.get(band, []))))
    print("%d lanes (%d arms) -> %s" % (len(lanes), len(ARMS), out / "r76_ab_rows.json"))
    return 0


def main(argv=None):
    argv = list(sys.argv[1:] if argv is None else argv)
    cmd = argv.pop(0) if argv and not argv[0].startswith("-") else "plan"
    if cmd == "paired":
        return paired_main(argv)
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--seed", type=int, default=76)
    ap.add_argument("--out", default=str(ROOT / "docs/evidence"))
    ap.add_argument("--tier", default="agy")
    ap.add_argument("--packs", type=int, default=6)
    ap.add_argument("--prefix", default="r76_gemf", help="feed: lane name prefix (r7x_ so land_finished2 lands it)")
    a = ap.parse_args(argv)
    texts = served.current_texts()
    if cmd == "plan":
        lanes, rec = plan_v2(texts, a.seed)
        out = Path(a.out)
        (out / "r76_ab_rows.json").write_text(json.dumps(lanes, indent=0) + "\n")
        (out / "r76_ab_plan.json").write_text(json.dumps(dict(rec, schema="azure-clean.r76-ab-plan.v2"), indent=1) + "\n")
        for band, b in rec["bands"].items():
            if "arms" in b:
                print("band %s: eligible %d, sampled %d; %s; overlap %d" % (band, b["eligible"], b["sampled"],
                      ", ".join("%s %d" % (x, len(v)) for x, v in b["arms"].items()), len(b["overlap"])))
                for x, m in b["strata_mix"].items():
                    print("   %-8s %s" % (x, " ".join("%s:%d" % kv for kv in sorted(m.items()))))
        print("%d lanes -> %s" % (len(lanes), out / "r76_ab_rows.json"))
        return 0
    if cmd == "feed":
        existing = sorted(e.name for e in os.scandir(ROOT / "work/native_lane") if e.name.startswith(a.prefix + "_"))
        n0 = 1 + max([int(x.rsplit("_", 1)[1]) for x in existing if x.rsplit("_", 1)[1].isdigit()] or [0])
        plan_rows = ROOT / "docs/evidence/r76_ab_rows.json"            # the A/B rows are never fed elsewhere
        excl = {i for v in json.loads(plan_rows.read_text()).values() for i in v} if plan_rows.is_file() else set()
        packs = feed(texts, a.tier, a.packs, exclude=excl)
        whole = {"%s_w_%d" % (a.prefix, n0 + k): ids for k, (kind, ids) in enumerate(packs) if kind == "whole"}
        clus = {"%s_c_%d" % (a.prefix, n0 + k): ids for k, (kind, ids) in enumerate(packs) if kind == "cluster"}
        Path(a.out + ".whole.json").write_text(json.dumps(whole, indent=0) + "\n")
        Path(a.out + ".cluster.json").write_text(json.dumps(clus, indent=0) + "\n")
        print("feed: %d whole packs, %d cluster packs -> %s.{whole,cluster}.json" % (len(whole), len(clus), a.out))
        return 0
    if cmd == "escalate":
        esc = escalate(texts)
        Path(a.out).write_text(json.dumps(esc, indent=0) + "\n")
        print("escalate: " + ", ".join("%s %d rows" % kv for kv in ((k, len(v)) for k, v in esc.items())) or "nothing")
        return 0
    ap.error("plan | feed | escalate | paired")


if __name__ == "__main__":
    sys.exit(main())
