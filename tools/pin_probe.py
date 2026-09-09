#!/usr/bin/env python3
"""Pin probe: how far is each pinned row from pin-free, and what stands in the way?

    python3 tools/pin_probe.py --strip --workers 12          # measure, write ledger/pins_strip.jsonl
    python3 tools/pin_probe.py --report                      # docs/PIN_FAMILIES.md

`tools/pin_census.py` measures one pin at a time against the *frozen* pinned text; T2's journal
measures one pin at a time against the reduced text.  Neither answers the question a family
campaign needs: **erase every pin of the row at once - what is left?**  That residue is the row's
real debt, and rows whose residue is the same shape share one mechanism, so one C-shape recipe
closes all of them.  The probe writes no source: it measures the current clean text.

Per row it records the strip damage (the scorer's aligned distance with every ASM_* site erased)
and a normalised signature of the disassembly residue:

  reg_perm    every mismatched word is the same instruction with registers renamed, and the
              renaming is a consistent permutation - a pure colouring residue
  reg_local   same instruction, registers differ, but not one global permutation
  order       the multiset of instructions is equal on both sides: a pure reordering
  indel       the instruction counts differ (retail keeps or drops a word gcc does not)
  mixed       none of the above

plus the mnemonic edit pairs (got -> tgt), which is what clusters rows into families.
Diff texts go to the scratchpad, never into work/ (agents search work/).
"""
import argparse, collections, json, os, re, sys, tempfile, time
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import ROOT, LEDGER, rows, read_jsonl, append_jsonl, sha_text
from pin_census import sites_of, erase
from verify import verify

INCLUDE = ROOT / "include"
OUT = LEDGER / "pins_strip.jsonl"
SCRATCH = Path(os.environ.get("PIN_PROBE_DIFFS", "/tmp/pin_probe_diffs"))

# "! [ 5] sw s0,24(sp)   | sw s1,28(sp)  raw 0x1800b0af vs 0x1c00b1af"
DIFF_RE = re.compile(r"^(!|\+|-|\s)\s*\[\s*(\d+)\]\s*(.*?)\s*\|\s*(.*?)(?:\s+raw\s+\S+\s+vs\s+\S+)?\s*$")
REG_RE = re.compile(r"\b(zero|at|v[01]|a[0-3]|t[0-9]|s[0-8]|k[01]|gp|sp|fp|ra)\b")


def parse_diff(text):
    """[(marker, index, got, tgt)] for the disasm block of a --diff run."""
    out, started = [], False
    for line in text.splitlines():
        if line.startswith("  disasm (got | tgt):"):
            started = True
            continue
        if not started:
            continue
        m = DIFF_RE.match(line)
        if not m:
            if line.strip() and not line.startswith(("   ", "  ", "!", "+", "-")):
                break
            continue
        out.append((m.group(1).strip() or " ", int(m.group(2)), m.group(3).strip(), m.group(4).strip()))
    return out


def mnemonic(ins):
    return ins.split()[0] if ins else ""


def skeleton(ins):
    """The instruction with every register name replaced by '#': shape without colouring."""
    return REG_RE.sub("#", ins)


def classify(pairs):
    """Normalise the residue of a stripped row into a family signature."""
    bad = [p for p in pairs if p[0] == "!"]
    if not bad:
        return {"sig": "none", "edits": [], "nbad": 0}
    got_regs, tgt_regs, skel_equal = [], [], True
    for _, _, got, tgt in bad:
        if skeleton(got) != skeleton(tgt):
            skel_equal = False
        got_regs += REG_RE.findall(got)
        tgt_regs += REG_RE.findall(tgt)
    edits = collections.Counter((mnemonic(g), mnemonic(t)) for _, _, g, t in bad)
    got_all = [p[2] for p in pairs if p[0] in "! "]
    tgt_all = [p[3] for p in pairs if p[0] in "! "]
    if skel_equal:
        # is the register renaming one consistent permutation over the whole residue?
        mapping, consistent = {}, True
        for _, _, got, tgt in bad:
            for a, b in zip(REG_RE.findall(got), REG_RE.findall(tgt)):
                if mapping.setdefault(a, b) != b:
                    consistent = False
        sig = "reg_perm" if consistent else "reg_local"
        return {"sig": sig, "edits": sorted(edits.items()), "nbad": len(bad),
                "perm": sorted(mapping.items())[:12] if consistent else []}
    if collections.Counter(got_all) == collections.Counter(tgt_all):
        return {"sig": "order", "edits": sorted(edits.items()), "nbad": len(bad)}
    if any(p[0] in "+-" for p in pairs) or len(got_all) != len(tgt_all):
        return {"sig": "indel", "edits": sorted(edits.items()), "nbad": len(bad)}
    return {"sig": "mixed", "edits": sorted(edits.items()), "nbad": len(bad)}


REGION_BAND = 12          # rows this close to pin-free get the aligned-regions view

REGION_RE = re.compile(r"^--- (insert|delete|replace) got\[(\d+):(\d+)\] tgt\[(\d+):(\d+)\]")


def region_ops(text):
    """[(op, got_words, tgt_words, [got mnemonics], [tgt mnemonics])] from an aligned-regions run."""
    out, cur = [], None
    for line in text.splitlines():
        m = REGION_RE.match(line)
        if m:
            if cur:
                out.append(cur)
            cur = {"op": m.group(1), "n_got": int(m.group(3)) - int(m.group(2)),
                   "n_tgt": int(m.group(5)) - int(m.group(4)), "got": [], "tgt": []}
            continue
        if cur is None or "|" not in line:
            continue
        left, _, right = line.partition("|")
        for side, txt in (("got", left), ("tgt", right)):
            w = txt.strip().split()
            if w:
                cur[side].append(w[0])
    if cur:
        out.append(cur)
    return out


def strip_text(text):
    cur = text
    for s in sorted(sites_of(text), key=lambda s: s[3], reverse=True):
        cur = erase(cur, s)
    return cur


def probe(row):
    from common import clean_path
    p = clean_path(row)
    if not p.exists():
        return None
    text = p.read_text(errors="replace")
    sites = sites_of(text)
    if not sites:
        return None
    macros = collections.Counter(s[1] for s in sites)
    rec = {"id": row["id"], "container": row["container"], "size": row["size"], "cfg": row["cfg"],
           "in_sha": sha_text(text), "pins": len(sites), "macros": dict(macros)}
    cand = strip_text(text)
    t0 = time.time()
    with tempfile.TemporaryDirectory() as td:
        f = Path(td) / Path(row["c_path"]).name
        f.write_text(cand)
        v = verify(row, f, include_root=INCLUDE)
        rec.update({"status": v.get("status"), "exact": bool(v.get("exact")), "subs": v.get("subs"),
                    "indels": v.get("indels"), "total": v.get("total"), "class": v.get("class"),
                    "signals": v.get("signals")})
        if v.get("exact") or v.get("status") not in ("ok", "OK", None) and not v.get("total"):
            rec["secs"] = round(time.time() - t0, 2)
            return rec
        # the aligned-regions view is the family axis: a one-word insertion reads as one region,
        # not as hundreds of shifted positional rows.  Only the actionable band pays for it.
        if (v.get("total") or 99) <= REGION_BAND:
            d = verify(row, f, include_root=INCLUDE, regions=True)
            rec["regions"] = region_ops(d.get("text", ""))
            SCRATCH.mkdir(parents=True, exist_ok=True)
            (SCRATCH / (row["id"].replace("/", "__") + ".regions")).write_text(d.get("text", ""))
        else:
            d = verify(row, f, include_root=INCLUDE, diff=True)
            rec.update(classify(parse_diff(d.get("text", ""))))
    rec["secs"] = round(time.time() - t0, 2)
    return rec


CELLS_OUT = LEDGER / "pins_cells.jsonl"


def probe_cells(row):
    """Score the row's stripped text at EVERY stock cell in one scorer run.

    A pin can be an artefact of the row being compiled at the wrong cell: the scaffolding was
    added to make the recorded cell reproduce retail.  This is a measurement only - a cell is a
    claim about the original build, so a cell that only wins for a rewrite is recorded, never
    landed.  `--report-cells` names the ones whose *pinned* text is exact at the new cell too
    (genuine ambiguity) and the ones that are not.
    """
    from common import clean_path, STOCK_CELLS
    p = clean_path(row)
    if not p.exists():
        return None
    text = p.read_text(errors="replace")
    if not sites_of(text):
        return None
    inc = f"-I{INCLUDE.resolve()}"
    cells = sorted(STOCK_CELLS) + [c + "-G0" for c in sorted(STOCK_CELLS)]
    cfgs = ",".join(f"{c} {inc}" for c in cells)
    rec = {"id": row["id"], "cfg": row["cfg"], "in_sha": sha_text(text), "cells": len(cells)}
    with tempfile.TemporaryDirectory() as td:
        f = Path(td) / Path(row["c_path"]).name
        f.write_text(strip_text(text))
        v = verify(dict(row, cfg=cfgs), f)
        rec.update({"best_total": v.get("total"), "best_exact": bool(v.get("exact")),
                    "class": v.get("class"), "secs": v.get("secs")})
        if v.get("exact"):
            # which cell won, and is the row's PINNED text exact there too?
            for c in cells:
                r2 = dict(row, cfg=f"{c} {inc}")
                if verify(r2, f).get("exact"):
                    rec["cell"] = c
                    g = Path(td) / ("pinned_" + Path(row["c_path"]).name)
                    g.write_text(text)
                    rec["pinned_exact_at_cell"] = bool(verify(r2, g).get("exact"))
                    break
    return rec


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--strip", action="store_true")
    ap.add_argument("--cells", action="store_true")
    ap.add_argument("--report", action="store_true")
    ap.add_argument("--workers", type=int, default=10)
    ap.add_argument("--limit", type=int)
    ap.add_argument("--only")
    ap.add_argument("--force", action="store_true")
    a = ap.parse_args()

    if a.report:
        report()
        return

    out_path = CELLS_OUT if a.cells else OUT
    fn = probe_cells if a.cells else probe
    done = {}
    for r in read_jsonl(out_path):
        done[r["id"]] = r
    todo = []
    only = None
    if a.only:
        p = Path(a.only)
        only = set(p.read_text().split()) if p.exists() else set(a.only.split(","))
    from common import clean_path
    for row in rows():
        if row["container"] == "ovmovie":
            continue
        if only and row["id"] not in only:
            continue
        p = clean_path(row)
        if not p.exists():
            continue
        text = p.read_text(errors="replace")
        if "ASM_" not in text or not sites_of(text):
            continue
        if not a.force and done.get(row["id"], {}).get("in_sha") == sha_text(text):
            continue
        todo.append(row)
    if a.limit:
        todo = todo[:a.limit]
    print(f"pin_probe: {len(todo)} rows to probe ({len(done)} journalled)", flush=True)
    t0, n = time.time(), 0
    with ThreadPoolExecutor(max_workers=a.workers) as ex:
        for rec in ex.map(fn, todo):
            if rec is None:
                continue
            append_jsonl(out_path, rec)
            n += 1
            if n % 100 == 0:
                print(f"  {n}/{len(todo)}  {time.time()-t0:.0f}s", flush=True)
    print(f"done {n} rows in {time.time()-t0:.0f}s", flush=True)


def report():
    recs = {r["id"]: r for r in read_jsonl(OUT)}.values()
    recs = list(recs)
    print(f"# Pin families (tools/pin_probe.py --strip)\n")
    print(f"Rows probed: {len(recs)}.  Every ASM_* site of the row erased at once; "
          f"the scorer's aligned distance and the shape of the residue below.\n")
    ex = [r for r in recs if r.get("exact")]
    print(f"- **strip-exact (pin-free for free): {len(ex)} rows**, "
          f"{sum(r['size'] for r in ex):,} B, {sum(r['pins'] for r in ex)} pins\n")
    band = collections.Counter()
    for r in recs:
        t = r.get("total")
        if r.get("exact"):
            band["0"] += 1
        elif t is None:
            band["error"] += 1
        else:
            band["1-3" if t <= 3 else "4-8" if t <= 8 else "9-20" if t <= 20 else "21+"] += 1
    print("| strip damage | rows |\n|---|---:|")
    for k in ("0", "1-3", "4-8", "9-20", "21+", "error"):
        if band[k]:
            print(f"| {k} | {band[k]} |")
    print()
    sig = collections.Counter(r.get("sig", "?") for r in recs if not r.get("exact"))
    print("| residue shape | rows | rows at damage<=8 |\n|---|---:|---:|")
    for k, v in sig.most_common():
        near = sum(1 for r in recs if r.get("sig") == k and (r.get("total") or 99) <= 8)
        print(f"| {k} | {v} | {near} |")
    print()
    near = [r for r in recs if not r.get("exact") and (r.get("total") or 99) <= REGION_BAND]
    print(f"## Families among the {len(near)} rows within {REGION_BAND} words of pin-free "
          f"({sum(r['size'] for r in near):,} B, {sum(r['pins'] for r in near)} pins)\n")
    print("### by scorer residue class\n")
    byclass = collections.Counter(r.get("class") for r in near)
    print("| class | rows | pins | bytes |\n|---|---:|---:|---:|")
    for k, v in byclass.most_common():
        sel = [r for r in near if r.get("class") == k]
        print(f"| {k} | {v} | {sum(r['pins'] for r in sel)} | {sum(r['size'] for r in sel):,} |")
    print("\n### by region shape (the mechanism key)\n")
    fam = collections.Counter()
    famrows = collections.defaultdict(list)
    for r in near:
        ops = r.get("regions") or []
        key = (r.get("class"), tuple(sorted(
            (o["op"], tuple(o["got"][:3]), tuple(o["tgt"][:3])) for o in ops))[:4])
        fam[key] += 1
        famrows[key].append(r["id"])
    print("| # rows | class | regions (op: got -> tgt) | example rows |\n|---:|---|---|---|")
    for k, v in fam.most_common(35):
        shape = "; ".join(f"{op} {'/'.join(g) or '-'} -> {'/'.join(t) or '-'}" for op, g, t in k[1])
        print(f"| {v} | {k[0]} | {shape[:110]} | {', '.join(famrows[k][:3])} |")


if __name__ == "__main__":
    main()
