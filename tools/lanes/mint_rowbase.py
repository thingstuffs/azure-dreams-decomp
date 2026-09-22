#!/usr/bin/env python3
"""Mint the FIRST `solved` rowbase record for a row whose true base is already determined.

    python3 tools/lanes/mint_rowbase.py [--only id,id] [--family main] [--l0] [--apply]

Why this exists.  `build_ovl/tools/rowbase.py` only READS `config/overlays/<fam>.rowbase.jsonl`;
a region's first record is manual j-solve evidence and `tools/lanes/promote_honest.py` only
promotes `solved` -> `proven` once a candidate recompiles byte-exact at the base.  On 2026-09-22
the LABEL_AS_CALL mid-row class hit 14 MAIN rows that had NO record and therefore scored with
their own internal `j` linked at the synthetic dashboard address -- unclosable by any C shape --
even though every one of them already carried a registered `true_name` and

    foff + 0x80197000 == int(true_name)

held exactly, for all 14.  That identity IS the j-solve: the row's true base is not in doubt, only
the scoring table was missing the line.  All 14 were minted by hand, landed byte-exact and
promoted to `proven`; this tool is that hand-work written down.

Two evidence grades, never mixed:

  registered-identity  the row has a `true_name` AND `foff + delta == int(true_name)` for the delta
                       carried by neighbouring records of the same family.  The row database and
                       the rowbase table are then simply saying the same thing; minting is
                       bookkeeping.  This is the only grade `--apply` will write.

  target-containment   the row has NO `true_name`.  The delta is taken from the neighbouring
                       records and is accepted only when EVERY LABEL_AS_CALL / intra-row tail-call
                       target of the row lands inside [foff+delta, foff+delta+size) -- the classic
                       j-solve -- and at least one target does NOT land inside the row's extent at
                       the synthetic base (otherwise the record decides nothing).  Reported, never
                       written: a row with no `true_name` also needs its true name registered
                       (ledger/splits/<fam>.jsonl) before the WINDOW gate will link it at the base,
                       which is `promote_honest.py`'s job, not this tool's.

Refusals are loud and listed: no neighbouring delta, neighbours disagreeing, an extent that
overlaps an existing region, or a `true_name` that contradicts the family delta (that last one is
corruption -- `overlay_local_gate.py` raises WINDOW-LINK DIVERGENCE on it).

Dry run is the default and prints one line per row plus a per-family tally.  `--apply` appends the
records (fail-loud re-parse after every write) and prints the region names; it does NOT promote --
land the row's byte-exact honest C first, then

    python3 build_ovl/tools/rowbase.py promote --family <fam> --func <synthetic> \
        --candidate <cand.c> --config <cfg>
"""
from __future__ import annotations

import argparse
import collections
import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "build_ovl/tools"))
import rowbase  # noqa: E402  the build_ovl copy; tools/gate's copy resolves ROOT wrongly
assert Path(rowbase.__file__).resolve().parent == ROOT / "build_ovl/tools", rowbase.__file__
from common import LEDGER, clean_path, read_jsonl, rows  # noqa: E402
from census import audit_sites, live_sites  # noqa: E402
from levels import tail_jump_targets  # noqa: E402

FAMILIES = ("main", "town", "dungeon", "ovmovie")
NEIGHBOUR_WINDOW = 0x40000        # foff radius searched for the family/bank delta


def _nearest(family: str, foff: int, k: int = 2):
    """The k nearest records below and above `foff` by file offset.  A banked overlay carries a
    DIFFERENT delta every few KiB (dungeon has 60+ banks), so the unit of agreement is the
    immediate neighbourhood, never the family."""
    recs = sorted(rowbase._records(family), key=lambda r: r["start"])
    below = [r for r in recs if r["end"] <= foff][-k:]
    above = [r for r in recs if r["start"] >= foff][:k]
    return below + above


def corroborate(family: str, foff: int, delta: int):
    """[region names] of nearby records carrying exactly `delta`, else (None, reason)."""
    near = _nearest(family, foff)
    same = [r["rec"]["region"] for r in near if r["delta"] == delta]
    if not same:
        return None, ("no neighbouring record carries delta 0x%X (nearest: %s)" % (
            delta, ", ".join(f"{r['rec']['region']}=0x{r['delta']:X}" for r in near) or "none"))
    return same, None


def neighbour_delta(family: str, foff: int):
    """(delta, [region names]) when the immediate neighbours agree on one delta, else (None, reason).
    Only used for rows with no registered true_name -- when there IS one, the identity decides the
    delta and the neighbours only corroborate it."""
    near = _nearest(family, foff)
    if not near:
        return None, f"no rowbase record anywhere near foff 0x{foff:X}"
    deltas = {r["delta"] for r in near}
    if len(deltas) != 1:
        return None, "immediate neighbours disagree: " + ", ".join(
            f"{r['rec']['region']}=0x{r['delta']:X}" for r in near)
    return deltas.pop(), [r["rec"]["region"] for r in near]


def row_targets(row, text):
    """The row's tail-jump dependencies as true-space addresses.  This is levels.tail_jump_targets,
    the SAME detector tools/split_audit.py uses, so a delta this tool j-solves is judged against the
    pairs the audit will then have to resolve -- a private copy drifted from it once already."""
    out = set()
    for tgt in tail_jump_targets(row, text):
        if re.fullmatch(r"func_[0-9A-F]{8}", tgt):
            out.add(int(tgt[5:], 16))
    for key in (f"{row['container']}/{f}" for f in (row.get("defs") or [row["func"]])):
        for s in live_sites(text, audit_sites().get(key, [])):
            cls, t2 = (s.split("|") + ["", ""])[:2]
            if cls == "LABEL_AS_CALL" and re.fullmatch(r"func_[0-9A-F]{8}", t2):
                out.add(int(t2[5:], 16))
    return sorted(out)


def plan_row(row):
    """One row -> a dict with `verdict` in mint/skip/refuse and everything the record needs."""
    fam, foff, size = row["container"], row.get("foff"), row["size"]
    out = {"id": row["id"], "family": fam, "foff": foff, "size": size,
           "true_name": row.get("true_name"), "verdict": "refuse", "why": "", "grade": None}
    if fam not in FAMILIES or row["kind"] != "overlay" or foff is None:
        out["why"] = f"not an overlay row of {FAMILIES}"
        return out
    if rowbase.delta_for(fam, foff) is not None:
        reg = next(r for r in rowbase._records(fam) if r["start"] <= foff < r["end"])
        out.update(verdict="skip", why=f"already covered by {reg['rec']['region']} "
                                       f"({reg['rec']['base_confidence']}, delta 0x{reg['delta']:X})")
        return out
    tn = row.get("true_name")
    if tn:
        # The registered identity DECIDES the delta; the neighbours only corroborate it.  (A row
        # sitting between two banks has neighbours that disagree, which says nothing against an
        # identity the row database already carries.)
        delta = int(tn[5:], 16) - foff
        ev, why = corroborate(fam, foff, delta)
        grade = "registered-identity"
        if ev is None:
            # No neighbour carries this delta.  A registered true_name is still one witness; when
            # the row's OWN live pseudo-call targets all land inside the row at that delta -- and
            # do not at the synthetic base -- that is a second, independent one (the classic
            # j-solve), and the two together are the evidence standard a first record asks for.
            # Banked overlays legitimately open a new bank no neighbour has recorded yet.
            text1 = clean_path(row).read_text(errors="replace") if clean_path(row).exists() else ""
            tg1 = row_targets(row, text1)
            syn1 = int(row["func"][5:], 16)
            if tg1 and all(foff + delta <= t < foff + delta + size for t in tg1) \
                    and not all(syn1 <= t < syn1 + size for t in tg1):
                ev, grade = ["none - j-solved instead"], "identity+containment"
                out["targets"] = tg1
            else:
                out.update(delta=delta, why=f"true_name {tn} implies delta 0x{delta:X} but {why}")
                return out
        out["_grade"] = grade
    else:
        # No registered identity: let the row's own pseudo-call targets pick among the deltas the
        # neighbourhood offers.  A banked overlay hands us several; exactly one may contain every
        # target inside the row's extent, and that one IS the j-solve.
        text0 = clean_path(row).read_text(errors="replace") if clean_path(row).exists() else ""
        tg = row_targets(row, text0)
        cands = []
        for r in _nearest(fam, foff, k=3):
            d = r["delta"]
            if d in [c[0] for c in cands]:
                continue
            if tg and all(foff + d <= t < foff + d + size for t in tg):
                cands.append((d, [x["rec"]["region"] for x in _nearest(fam, foff, k=3) if x["delta"] == d]))
        if len(cands) != 1:
            delta, ev = neighbour_delta(fam, foff)
            if delta is None:
                out["why"] = (ev if not tg else
                              ev + f"; and {len(cands)} of those deltas contain all "
                                   f"{len(tg)} pseudo-call target(s) in the row")
                return out
        else:
            delta, ev = cands[0]
    out["delta"], out["neighbours"] = delta, ev
    # `link_vram` looks the row up by its START offset, so the record only has to CONTAIN foff.
    # Where the row's extent runs into an already-recorded region (rows and image/jump-table
    # regions are carved independently and do abut), clamp the end rather than refuse -- but only
    # when the region we back off from carries the same delta, otherwise the neighbourhood is
    # genuinely contested and a human should look.
    end = foff + size
    for r in sorted(rowbase._records(fam), key=lambda x: x["start"]):
        if foff < r["end"] and r["start"] < end:
            if r["start"] <= foff or r["delta"] != delta:
                out["why"] = (f"extent 0x{foff:X}-0x{end:X} overlaps {r['rec']['region']} "
                              f"(0x{r['start']:X}-0x{r['end']:X}, delta 0x{r['delta']:X})")
                return out
            out["clamped_from"] = end
            end = r["start"]
    out["end"] = end
    base = foff + delta
    out["base"] = base
    if tn:
        out.update(verdict="mint", grade=out.pop("_grade"),
                   why=f"foff 0x{foff:X} + 0x{delta:X} == {tn}, already registered; "
                       + (f"corroborated by {', '.join(ev)}" if ev != ["none - j-solved instead"]
                          else f"no neighbour carries this delta, but all {len(out.get('targets', []))} "
                               f"live pseudo-call target(s) land inside the row at it and none does "
                               f"at the synthetic base"))
        return out
    text = clean_path(row).read_text(errors="replace") if clean_path(row).exists() else ""
    tgts = row_targets(row, text)
    if not tgts:
        out["why"] = "no true_name and no live pseudo-call target to solve the base with"
        return out
    inside = [t for t in tgts if base <= t < base + size]
    if len(inside) != len(tgts):
        out["why"] = ("no true_name; targets outside the row at this delta: "
                      + ", ".join(f"0x{t:08X}" for t in tgts if t not in inside))
        return out
    syn = int(row["func"][5:], 16)
    if all(syn <= t < syn + size for t in tgts):
        out["why"] = "no true_name; every target already resolves inside the row at the synthetic base"
        return out
    out.update(verdict="report-only", grade="target-containment", targets=tgts,
               why=(f"{len(tgts)} pseudo-call target(s) land inside [0x{base:08X}, 0x{base + size:08X}) "
                    f"and none does at the synthetic base -- j-solved, but the row has no true_name: "
                    f"register func_{base:08X} (promote_honest.py) before minting"))
    return out


def proof_text(p, row):
    if p["grade"] in ("registered-identity", "identity+containment"):
        return (f"Registered-identity mint (tools/lanes/mint_rowbase.py, {ARGS.date}): this row's "
                f"true name {p['true_name']} is already recorded in ledger/splits/{p['family']}.jsonl and "
                f"foff 0x{p['foff']:X} + 0x{p['delta']:X} == 0x{p['base']:08X} exactly, so the row database "
                f"and the rowbase table state the same base; without the record the row's own internal "
                f"j words link at the synthetic dashboard address and are unclosable by any C shape. The "
                f"same 0x{p['delta']:X} runtime-bank delta is "
                + (("carried by the neighbouring records " + ", ".join(p["neighbours"]))
                   if p["grade"] == "registered-identity" else
                   ("carried by no neighbouring record -- this row opens a bank none of them has "
                    "recorded -- but every retail direct-jump target the row still spells ("
                    + ", ".join(f"0x{t:08X}" for t in p.get("targets", []))
                    + ") lands inside [0x%08X, 0x%08X) at this delta and none of them does at the "
                      "synthetic base, so the identity and the j-solve are two independent witnesses"
                    % (p["base"], p["base"] + p["size"])))
                + ". Scoring-only until a byte-exact recompile at the base promotes it (rowbase.promote).")
    return (f"Target-containment mint (tools/lanes/mint_rowbase.py, {ARGS.date}): every retail direct-jump "
            f"target this row still spells -- " + ", ".join(f"0x{t:08X}" for t in p["targets"])
            + f" -- decodes as internal CFG only at true base 0x{p['base']:08X}, and none of them resolves "
            f"inside the row at the synthetic base. The same 0x{p['delta']:X} runtime-bank delta is carried "
            "by the neighbouring records " + ", ".join(p["neighbours"]) + ".")


def main():
    global ARGS
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--only", help="comma-separated row ids")
    ap.add_argument("--family", choices=FAMILIES)
    ap.add_argument("--l0", action="store_true", help="every row at level 0 (ledger/levels.jsonl)")
    ap.add_argument("--apply", action="store_true", help="append the registered-identity records")
    ap.add_argument("--date", default="2026-09-22")
    ARGS = ap.parse_args()

    want = set(ARGS.only.split(",")) if ARGS.only else None
    l0 = {j["id"] for j in read_jsonl(LEDGER / "levels.jsonl") if j.get("level") == 0} if ARGS.l0 else None
    sel = [r for r in rows()
           if (want is None or r["id"] in want)
           and (ARGS.family is None or r["container"] == ARGS.family)
           and (l0 is None or r["id"] in l0)]
    if want:
        missing = want - {r["id"] for r in sel}
        if missing:
            raise SystemExit(f"unknown row ids: {sorted(missing)}")

    plans = [plan_row(r) for r in sel]
    tally = collections.Counter()
    for p in sorted(plans, key=lambda x: (x["family"], x["foff"] or 0)):
        tally[(p["family"], p["verdict"])] += 1
        if p["verdict"] == "skip":
            continue
        mark = {"mint": "MINT ", "report-only": "REPORT", "refuse": "refuse"}[p["verdict"]]
        clamp = (f" [extent clamped to 0x{p['end']:X}, the next same-delta region]"
                 if p.get("clamped_from") else "")
        foff = f"0x{p['foff']:06X}" if p["foff"] is not None else "-"
        print(f"{mark} {p['id']:<28} foff {foff:<9} size {p['size']:>5} "
              f"{p['grade'] or '-':<20} {p['why']}{clamp}")

    print("\n-- tally (rows) --")
    for fam in FAMILIES:
        line = {v: tally[(fam, v)] for v in ("mint", "report-only", "refuse", "skip") if tally[(fam, v)]}
        if line:
            print(f"  {fam:<8} {line}")

    if not ARGS.apply:
        print("\ndry run (default): nothing written.  Re-run with --apply to append the MINT rows.")
        return
    byid = {r["id"]: r for r in sel}
    for p in plans:
        if p["verdict"] != "mint":
            continue
        row = byid[p["id"]]
        path = ROOT / f"config/overlays/{p['family']}.rowbase.jsonl"
        region = f"row_{p['foff']:x}_{p['base']:08x}"
        if any(r["rec"].get("region") == region for r in rowbase._records(p["family"])):
            print(f"already present: {region}")
            continue
        rec = {"schema": rowbase.SCHEMA, "region": region,
               "foff_start": f"0x{p['foff']:X}", "foff_end": f"0x{p['end']:X}",
               "delta": f"0x{p['delta']:X}", "base_confidence": "solved", "proof": proof_text(p, row)}
        with open(path, "a") as fh:
            fh.write(json.dumps(rec) + "\n")
        rowbase._records(p["family"])          # re-parse: fail loudly if the write broke anything
        print(f"minted {region} -> true base 0x{p['base']:08X}")


if __name__ == "__main__":
    main()
