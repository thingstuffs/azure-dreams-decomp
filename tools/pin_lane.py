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
import argparse, collections, json, re, shutil, sys, tempfile
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

**Read this first: the residue is almost never a register *preference*.**  In most rows retail's
build holds two live pseudos carrying the same value, and gcc-2.7/2.8's cse collapses a plain
`b = a;` into one pseudo whenever both stay live - after which the allocator has no choice left.
That collapse is what `ASM_REG` and `ASM_KEEP_NV` were standing in for.  Reshaping the *variable
map* does not defeat it: 25+ shapes across five rows (split a local, merge two, drop it, move or
block-scope the declaration, copies in both arms, self round-trip, dead init, operand-order flips,
same-mode retyping) produced **byte-identical output every time**.  Two handles do defeat it:

1. **A value-preserving *mode* change on one side of the copy.**  `u16 x = <s32 expr>` is not a
   REG-REG set in RTL, so cse never enters the two into one quantity.  Choose a narrowing the code
   already pays for: `(u16)(angle + 0x100) & 0xE00` hides the re-widening inside a mask that was
   already there and costs zero words, where the `s16` spelling costs two because `sll/sra` cannot
   be folded.  The same trick stops `record_jump_equiv` merging the cse class of the two operands
   of an equality test - give them different modes and the later test reads the other register.
2. **The copy is an m2c artifact of a compiler-generated idiom.**
   `q = x; q >>= n; if (x < 0) q = (x + m) >> n; r = x - (q << n)` is `x % (1 << n)`.  Written back
   as `%`, gcc's own `expand_divmod` re-emits it with an internal copy that is immune to the
   collapse, and gcc picks the duplicated-shift or shared-shift form per site by itself.  **When a
   residue sits inside an arithmetic sequence, look for a hand-expanded compiler idiom before
   touching any variable.**

Then, by class:

- **length-drift** - retail keeps or drops a word.  A local declared wider than the load that fills
  it, with an explicit `& 0xFF`, is the commonest case: the mask folds away because `lbu` already
  zero-extends, so declare the local `u8` and drop the mask.  A "dead" store before a call is often
  a real argument to an under-declared callee - retype the extern, pass it, and retail's kept words
  return.  gcc's if-conversion fires on `x=1; if (c) x=0; f(x);`: writing the call out in both arms
  with literal arguments dodges it, and arm order sets branch polarity independently.
- **reorder-only / code-motion** - the C order is usually already right and the *scheduler* moved
  the instruction, so re-slotting the statement is a dead end (measured 0/3 mechanically).  Change
  the dependence instead: sink a value's computation into both arms of the `if` that produces it,
  or lift it into its own local assigned before the statement it must precede and read only through
  that local.  `do {{ stmt; }} while (0)` is a zero-byte scheduling barrier that pins a definition
  point (a bare block does **not** - only the loop note does); it works, it is counted as
  scaffolding by `census.py`, so reach for it only after a real shape has failed.
- **li-expansion / const-remat / addressing** - `lui;ori` yours against `lui;addiu` retail's means
  your C materialises an integer literal where retail references a **symbol**: find the real
  `D_<addr>` and reference it instead of a `.set` page base plus an offset.  The substitution alone
  often regresses, because a local set once from an address constant is a `reg_equiv_constant` that
  gets rematerialised at each use; a second, non-folding set fixes that, and whether it is free
  depends on the cell.  It also regresses when the value is later a **call argument**.
- **broad** - no single named signal; read the row's regions view.  Folding a load into the
  expression that consumes it, instead of pre-loading an accumulator, is what flips which pseudo
  becomes `rs` and which `rt`.
- **delay-slot / slot-rotation** - retail fills a slot your build leaves as `nop`; the filler is
  usually a value computed earlier than your C computes it.

Rows whose residue is branch-derived *constant* knowledge (`move $v0,$zero` against
`move $v0,$s0`) are cse choosing between a literal and a register it has proved holds the same
constant.  That is not register naming despite the class label - record it and move on.

**Read the `internal_jumps` column of `rows.tsv` before you diagnose anything.**  m2c spells
retail's plain `j` to a label *inside the same function* as a call to a symbol declared
`__attribute__((noreturn))`.  When that column is non-empty, the named symbol is NOT a callee: it
is a label at the given word of this very function, and **the value stored just before the "call"
is live, not dead** - control continues at the label.  Three separate lanes reasoned from the
declaration instead, concluded gcc's liveness analysis provably deletes the store and that the
class was unreachable from C, and closed 0/28 rows between them on that basis.  The real shape is
the LABEL_AS_CALL rewrite: `if (c) {{ A; target(); return; }} B; T` becomes
`if (c) {{ A' }} else {{ B' }} T`, where T is the code the landing word points at; a backward
target is a loop, not a tail; when the tail is already spelled out after the call, just delete the
call.  That rewrite closed 67 of 75 rows in this project's earlier reader lanes.

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


NORETURN_RE = re.compile(
    r"extern[^;\n]*\b(func_[0-9A-Fa-f]{8})\s*\([^;\n]*\)\s*__attribute__\s*\(\s*\(\s*noreturn")


def internal_jumps(row, text):
    """`func_X@word N` for every "noreturn callee" that is really a label inside this row.

    m2c spells retail's plain `j` to an internal label as a call to a symbol declared noreturn.
    Three separate lanes then reasoned that the value stored before such a "call" is provably dead
    (the call never returns, so nothing can read it) and concluded the class was unreachable from
    C.  It is not dead: control continues at the label, inside this same function.  27 pinned rows
    are in this state and the fidelity census already flags 25 of them; the packs simply never
    passed the fact on.  The landing word is counted from the row's true name, which is what a
    LABEL_AS_CALL rewrite needs.
    """
    tn = row.get("true_name")
    if not tn:
        return ""
    base = int(tn.replace("func_", ""), 16)
    out = []
    for m in NORETURN_RE.finditer(text):
        tgt = int(m.group(1).replace("func_", ""), 16)
        if base <= tgt < base + row["size"]:
            out.append(f"{m.group(1)}@word{(tgt - base) // 4}")
    return ",".join(out)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--band", type=int, default=8, help="max strip damage to include")
    ap.add_argument("--size", type=int, default=12, help="rows per batch")
    ap.add_argument("--batches", type=int, default=0, help="0 = all")
    ap.add_argument("--out", default="work/pin_lane")
    ap.add_argument("--only-class")
    ap.add_argument("--only-rows", help="path to a file of row ids, one per line")
    ap.add_argument("--budget", type=int, default=12)
    ap.add_argument("--workers", type=int, default=8)
    a = ap.parse_args()

    only_rows = set(Path(a.only_rows).read_text().split()) if a.only_rows else None
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
        if only_rows is not None and rid not in only_rows:
            continue
        p = clean_path(row)
        if not p.exists():
            continue
        text = p.read_text(errors="replace")
        if sha_text(text) != rec.get("in_sha") or not sites_of(text):
            continue                      # the probe is stale for this text
        if "NON_MATCHING" in text:
            continue
        if re.search(r'__asm__\s*(__volatile__\s*)?\(\s*"[a-z]', text):
            # a raw asm BODY is not an ASM_* pin: `strip_pins` leaves it, so the "pin-free" base a
            # lane would start from still carries hand-written instructions and can never be a
            # clean result.  A reorder-only lane hit exactly this (4 asm blocks, rows.tsv said 1 pin).
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
        from pin_facts import facts
        body = v.get("text", "")
        (d / "residue" / (row["id"].replace("/", "__") + ".txt")).write_text(
            "FACTS (mechanical - do not re-derive these):\n"
            + facts(row, text, body) + "\n\nRESIDUE of the pin-free text against retail:\n" + body)
        return row["id"]

    jobs = []
    for bi, (cls, items) in enumerate(batches, 1):
        d = out / f"batch{bi}"
        if d.exists():
            shutil.rmtree(d)
        (d / "residue").mkdir(parents=True)
        (d / "scratch").mkdir()
        (d / "out").mkdir()
        lines = ["row_id\tcontainer\tfile\tsize\tcfg\tpins\tmacros\tdamage\tclass\twindow\tinternal_jumps"]
        for rec, row, text in items:
            macros = ",".join(f"{k}x{v}" for k, v in sorted(rec.get("macros", {}).items()))
            lines.append("\t".join(str(x) for x in [
                row["id"], row["container"], f"src/{row['container']}/{Path(row['c_path']).name}",
                row["size"], row["cfg"], rec["pins"], macros, rec["total"], rec.get("class"),
                Path(row.get("gate_config") or "").stem, internal_jumps(row, text) or "-"]))
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
