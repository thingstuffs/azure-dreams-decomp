#!/usr/bin/env python3
"""Build lane packs for the rows that are within a few words of pin-free.

    python3 tools/pin_lane.py --band 8 --size 12 --out work/pin_lane [--only-class reg-rename]

`tools/pin_probe.py --strip` measured, for every pinned row, what retail looks like when the row's
pins are all erased.  A row whose residue is a handful of words is one C shape away from carrying
no scaffolding at all; a row whose residue is fifty words is a rebuild, not a pin problem.  This
tool takes the near band, groups it by residue class (rows in one class share a mechanism, so a
lane that solves one row usually solves its neighbours) and writes a self-contained pack per
batch:

    <out>/batchN/rows.tsv                 one line per row: id, size, cfg, pins, damage, class
    <out>/batchN/base/<container>/<f>.c   the row's text with every pin erased - the lane's start
    <out>/batchN/residue/<row>.txt        the aligned-regions view of that base against retail
    <out>/batchN/BRIEF.md                 what the lane must do, and the recipes that are known

The lane writes exact candidates to `<out>/batchN/out/<container>/<f>.c`; landing is
`tools/apply_candidates.py <out>/batchN/out --transform t13_depin`, then the window gate.
"""
import argparse, collections, json, shutil, sys, tempfile
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import ROOT, LEDGER, rows, read_jsonl, clean_path, sha_text
from pin_census import sites_of
from verify import verify
sys.path.insert(0, str(ROOT / "tools" / "xform"))
from xform.t12_stmtorder import strip_pins

INCLUDE = ROOT / "include"

BRIEF = """# Pin-removal lane — batch {n} ({cls})

Every row here is **byte-exact today** and carries `ASM_*` pins.  A pin is not a justification:
it is an UNRESOLVED C shape.  Your job is to find the C that produces retail's bytes **with no
pin at all**, on rows the machine has already measured as being a few words away.

The residue is pre-measured for you.  `base/` holds each row's text with every pin already
erased, and `residue/<row_id>.txt` is that text scored against retail: the aligned regions are
exactly what your C has to change.  Do not re-derive it.

## What the residue classes mean, and what has worked

- **reg-rename / broad-with-a-colouring-signature** — same instructions, two registers swapped.
  gcc-2.7.x colours by allocno priority ≈ `floor_log2(refs) * refs / live_length`, so the lever
  is the *variable map*, not the register: split one local into one per use-group (the single
  highest-yield edit); merge two short-lived locals into one; give a value a longer or shorter
  live range by moving its first assignment; hoist a block-scoped declaration to function scope
  (or push a function-scope one into the block that uses it).  Declaration order decides the
  frame-slot order and, inside a block, the argument-register colours.
- **reorder-only / code-motion** — same instructions, one moved.  The C order is usually already
  right and the *scheduler* moved it, so re-slotting the statement rarely helps.  What does help:
  change the dependence.  Sink a value's computation into both arms of the `if` that produces it
  (deleting the temp), or lift it into its own local assigned *before* the statement it must
  precede and read only through that local.  A loop counter's increment at the end of the body
  instead of the top is the same lever in a loop.
- **li-expansion / const-remat / addressing** — the address form differs.  `lui;ori` on your side
  against `lui;addiu` on retail's means your C materialises an integer literal where retail
  references a **symbol**: find the real `D_<addr>` the address lands on and reference it, instead
  of a `.set` page base plus an offset.  The reverse (`addiu` yours, `ori` retail's) means retail
  really did compute a constant.  A base used repeatedly wants one function-scope pointer
  assigned once; a base used once wants the expression spelled at the use.
- **length-drift / dead-code-retention** — retail keeps a word gcc deletes (or the reverse).  This
  is the hardest class from C; spend few probes and move on.
- **delay-slot / slot-rotation** — retail fills a slot your build leaves as `nop`.  The filler is
  usually a value computed earlier than your C computes it.

## Commands (run from the repo root; never `cd` elsewhere)

- Score a candidate — **counts against your budget of {budget} verifies per row**:
  `python3 tools/verify.py <row_id> <candidate.c> --include-root include`
  `"exact": true` is success.  Otherwise read `total` (words off) and `class`.
- Free and unlimited, use before every verify:
  `python3 tools/verify.py <row_id> <candidate.c> --include-root include --regions`
  the aligned mismatch regions — the same view as `residue/`.  `--diff` gives the positional
  listing when you need instruction addresses.

## Rules

- **A candidate must contain no `ASM_` macro at all.** A row that only gets *fewer* pins is not a
  result for this lane; record it and move on.
- Start from `base/<container>/<file>.c` (pins already erased).  Keep the file's includes, externs,
  struct definitions, local names and the summary comment.  Change the C shape, not the identifiers.
- Never invent inline `__asm__` bodies, never add `volatile` to reach the bytes unless the value
  genuinely is hardware, and never edit anything outside your batch directory: `scratch/` for
  iterations, `out/<container>/<basename>.c` for exact candidates, `REPORT.md` at the end.
- IO discipline (one shared disk): no `grep -r`, `rg`, `find`, or any recursive search over the
  repo, `work/`, or `src/`.  Open the named files only.
- Never run `sweep.py`, `promote.py`, `apply_candidates.py`, `gate_all.py`, `mk_ovl_root.sh`, or
  any `git` command.  Do not launch background processes.
- Work `rows.tsv` in order (smallest residue first).  Stop a row at its budget; never re-submit an
  unchanged candidate.  Do every row in the batch.

## Report (`REPORT.md`)

A table `row | size | cfg | damage | class | exact | verifies | the C shape that did it (or the
best residue reached and what was tried)`, then a short list of patterns the brief does not
already name.  Final line exactly: `Exact: N/{count}`.
"""


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--band", type=int, default=8, help="max strip damage to include")
    ap.add_argument("--size", type=int, default=12, help="rows per batch")
    ap.add_argument("--batches", type=int, default=0, help="0 = all")
    ap.add_argument("--out", default="work/pin_lane")
    ap.add_argument("--only-class")
    ap.add_argument("--budget", type=int, default=12)
    ap.add_argument("--workers", type=int, default=8)
    a = ap.parse_args()

    by = {r["id"]: r for r in rows()}
    recs = {}
    for r in read_jsonl(LEDGER / "pins_strip.jsonl"):
        recs[r["id"]] = r
    live = []
    for rid, rec in recs.items():
        row = by.get(rid)
        if row is None or rec.get("exact"):
            continue
        t = rec.get("total")
        if t is None or t > a.band:
            continue
        if a.only_class and rec.get("class") != a.only_class:
            continue
        p = clean_path(row)
        if not p.exists():
            continue
        text = p.read_text(errors="replace")
        if sha_text(text) != rec.get("in_sha") or not sites_of(text):
            continue                      # the probe is stale for this text
        if "NON_MATCHING" in text:
            continue
        live.append((rec, row, text))
    # one mechanism per lane: group by class, then damage, then size
    live.sort(key=lambda x: (x[0].get("class") or "", x[0]["total"], x[1]["size"]))
    groups = collections.defaultdict(list)
    for rec, row, text in live:
        groups[rec.get("class")].append((rec, row, text))

    out = ROOT / a.out
    batches, n = [], 0
    for cls, items in sorted(groups.items(), key=lambda kv: -len(kv[1])):
        for i in range(0, len(items), a.size):
            batches.append((cls, items[i:i + a.size]))
    if a.batches:
        batches = batches[:a.batches]
    print(f"{len(live)} rows within {a.band} words of pin-free -> {len(batches)} batches")

    def residue(job):
        d, rec, row, text = job
        base = strip_pins(text)
        (d / "base" / row["container"]).mkdir(parents=True, exist_ok=True)
        (d / "base" / row["container"] / Path(row["c_path"]).name).write_text(base)
        with tempfile.TemporaryDirectory() as td:
            f = Path(td) / Path(row["c_path"]).name
            f.write_text(base)
            v = verify(row, f, include_root=INCLUDE, regions=True)
        (d / "residue" / (row["id"].replace("/", "__") + ".txt")).write_text(v.get("text", ""))
        return row["id"]

    jobs = []
    for bi, (cls, items) in enumerate(batches, 1):
        d = out / f"batch{bi}"
        if d.exists():
            shutil.rmtree(d)
        (d / "residue").mkdir(parents=True)
        (d / "scratch").mkdir()
        (d / "out").mkdir()
        lines = ["row_id\tcontainer\tfile\tsize\tcfg\tpins\tmacros\tdamage\tclass\twindow"]
        for rec, row, text in items:
            macros = ",".join(f"{k}x{v}" for k, v in sorted(rec.get("macros", {}).items()))
            lines.append("\t".join(str(x) for x in [
                row["id"], row["container"], f"src/{row['container']}/{Path(row['c_path']).name}",
                row["size"], row["cfg"], rec["pins"], macros, rec["total"], rec.get("class"),
                Path(row.get("gate_config") or "").stem]))
            jobs.append((d, rec, row, text))
        (d / "rows.tsv").write_text("\n".join(lines) + "\n")
        (d / "BRIEF.md").write_text(BRIEF.format(n=bi, cls=cls, budget=a.budget, count=len(items)))
        n += len(items)
    with ThreadPoolExecutor(max_workers=a.workers) as ex:
        list(ex.map(residue, jobs))
    print(f"wrote {n} rows into {out}")
    for bi, (cls, items) in enumerate(batches, 1):
        print(f"  batch{bi:<3} {cls:<22} {len(items):3d} rows  "
              f"{sum(r['size'] for _, r, _ in items):6,} B  "
              f"damage {min(x[0]['total'] for x in items)}-{max(x[0]['total'] for x in items)}")


if __name__ == "__main__":
    main()
