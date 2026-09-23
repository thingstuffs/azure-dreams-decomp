# lanekit - the harness a lane gets, so no lane builds one again

Built 2026-09-21 from `docs/evidence/lane_log_mining_astra_20260921.md` and
`lane_log_mining_sol_20260921.md` (30 mined lanes). Every astra lane rebuilt the same
erase-compile-screen-verify-log loop; the cwd shim was invented twice and rewritten four more times;
five sol lanes hand-rolled subset erasure scans; and 13 of 16 astra lanes ended asking for a tool
that explains *why* a gcc pass decided what it did. That is what is here.

    cd work/native_lane/<lane>
    source <REPO>/tools/lanes/lanekit/env.sh     # optional; sets LANE/PYTHONPATH/TMPDIR
    python3 <REPO>/tools/lanes/lanekit/<tool>.py ...

Every tool writes **only inside the lane directory** (it refuses to run at the repository root), and
every compiler dump lands inside it by construction: `TMPDIR` and `tempfile.tempdir` point at
`<lane>/tmp`, so the `TemporaryDirectory` each shared tool compiles in is already there, and the
`sitecustomize.py` shim re-homes any compiler that would otherwise run at the repository root.

| tool | what it prints |
|---|---|
| `lab.py` | listing distance, pins left, byte score, and the REPORT table |
| `erase.py` | what each pin holds, and which pins fall together |
| `why.py` | the pass DECISION that changed: priorities, allocnos, loop verdicts, RTL |
| `diff.py` | the unified cc1-listing diff of one candidate vs pinned / erased / a file (+ `--score`) |
| `dump.py` | every `-da` pass dump of one text into a lane directory (`--cfg` for another cell) |
| `install.py` | `TOOLS.md` in a lane: the same table with that lane's rows |
| `sitecustomize.py`, `lane_shim.py`, `env.sh`, `kitlib.py` | plumbing; you never call these |

---

## lab.py - the harness

```
python3 .../lab.py baseline <row> --score          # STEP 1, always
python3 .../lab.py <row> v1.c v2.c --score         # variants as files
python3 .../lab.py <row> --subs shapes1.json --score [--score-top 3]
python3 .../lab.py <row> --grid grid1.json --score  # every combination of independent axes
python3 .../lab.py <row> v7.c --cfg "2.8.1-G0" --score          # measure at another cfg
python3 .../lab.py cellscore <row> v7.c --cfg "2.8.1-G0"        # trade check + hand-over lines
python3 .../lab.py report                          # the REPORT.md table, from lab_log.jsonl
```

* **Before writing a helper of your own, check this README - 26 lanes rebuilt the listing diff
  (`diff.py`), 23 the dump fetch (`dump.py`), ~21 an `itertools.product` grid (`--grid`) in round 73.**
* **`--grid`** takes `{"axis": {"label": [["old","new"],...], ...}, ...}`: one label per axis, every
  combination, named `label+label+...`, applied in axis order like `--subs` (nearest-line message,
  `pattern-missing` logged). `[]` is a valid label ("leave it"); `"@base": "pinned"` starts from the
  pinned text. The product counts against the cap.
* **`--cfg CFG`** compiles and scores as if the row were registered at CFG (the row-dict override
  `land_coherence.sh` uses). Distance stays against the pinned listing at the registered cfg, so it
  is information only: every variant that builds is scored and nothing is staged. **`cellscore`**
  also scores the pinned text at CFG (rule 2: byte-neutral switch or genuine coherence trade) and,
  when exact, prints the `cells.jsonl` line and the `land_coherence.sh` command for the
  orchestrator. The registered cfg is never changed; nothing under `ledger/` is written. `--cfg` variants and
  `cellscore` count toward the 60-variant cap; the report marks their scores `exact @<cfg>` and
  does not count them as solves.

* **`baseline` first.** It scores the row's own pinned text, which is byte-exact by definition: the
  scorer must say `exact=true, total=0`. One lane's custom adapter silently mis-scored every
  baseline (103/45/16/50/31 instead of 0) and it was caught only because that lane ran this check.
* **Two-tier screen.** The cc1 listing (~15 ms) is compared with the pinned text's listing, which is
  retail's instruction order on a byte-exact row. `--score` sends only the distance-0 variants to
  the byte scorer (5-20 s each); `--score-top N` also scores the N nearest of the run. Lanes that
  solved rows sent 1-6% of their variants to the scorer.
* **Guards, before anything is written:** a variant with more pin sites than the base, or more
  `volatile`, is refused and logged as `refused`.
* **Substitutions** are `variants.json` exactly as `tools/xform/variant_screen.py` reads it:
  `{"name": [["old","new"], ...]}` applied in order to the pin-erased base, first occurrence only;
  `"@name"` starts from the pinned text instead. A pattern that is not in the text prints the three
  nearest lines, not a bare `AssertionError`.
* **Staging.** A variant that is listing-exact AND scores exact AND passes the admission gate
  (strictly fewer pins, the rest a subset of the base's, no new `volatile`/`__asm__`/`ASM_*`, no new
  one-trip block) is copied to `out/<container>/<file>.c` with its `.base_sha`. `--no-stage` to
  measure without staging.
* **Everything** - refusals, failed builds, pattern misses - is appended to `lab_log.jsonl`, and
  `lab.py report` builds the table from that file. A row of the lane with **zero** measurements is
  printed as `ZERO MEASUREMENTS`: one sol lane left two of its five rows untried and the report read
  exactly like "measured and still open".
* **Cap:** more than 60 variants on one row needs `--more`. One lane wrote 209 probe files for two
  of its five rows.

Python API, if you are scripting a sweep of shapes:

```python
import sys; sys.path.insert(0, "<REPO>/tools/lanes/lanekit")
from lab import Lab
lab = Lab("dungeon/func_8009612C")
lab.baseline(score=True)
lab.test("narrow_param", text, note="s16 parameter", score=True)
```

## diff.py, dump.py

```
python3 .../diff.py <row> <cand.c|erased|pinned> [--vs pinned|erased|FILE] [--ctx N] [--score]
python3 .../dump.py <row> <cand.c|pinned|erased> <outdir> [--cfg CFG] [--pass sched|greg|lreg|loop|combine|cse|jump|all]
```

`diff.py` prints the listing diff `lab.py` stores as `experiments/<func>/<name>.diff`, for one file,
then the distance line; without `--score` it writes nothing. `dump.py` is `kitlib.dumps` (the compile
`why.py` uses) writing `<outdir>/<stem>.<pass>` and `<stem>.s`; `sched`/`cse`/`jump` include their
second pass; `outdir` must be inside the lane.

## erase.py - what each pin holds

```
python3 .../erase.py <row>                       # lone + all + every pair (<= 8 pins)
python3 .../erase.py <row> --mode subset --budget 60
python3 .../erase.py <row> --variant experiments/func_X/v7.c
```

Prints, and writes `erase_<func>.md`: every site with its line, its pin, its statement and the
listing distance of erasing it **alone**; the distance with **all** pins erased; and the subsets -
every pair on small rows, plus the same-macro and same-variable groups (`joint_scan.subsets_of`,
reused rather than re-derived). A pair **FALLS TOGETHER** when erasing both leaves a residue no
larger than either alone (`duck_brief.fall_together`): those pins are one mechanism and one
candidate has to move all of them. `--variant` runs the same scan on a candidate you have already
written - which of the remaining pins is still holding it.

Listing distances only; the byte scorer is never called here; the ledger is never touched.

## why.py - the pass-decision explainer

```
python3 .../why.py <row> --pass sched|sched2|greg|lreg|loop|cse|cse2|combine|flow|jump|jump2|rtl|dbr
                        [--variant FILE|erased] [--vs pinned|erased|FILE] [--around TOKEN] [--top N]
```

Two `-da` compiles (one per text; every pass comes out of each), then the decisions that differ:

* **`sched` / `sched2`** - per basic block: each insn's `priority` and `ref_count`, the scheduler's
  ready lists, the **source** order (`INSN_LUID`) beside the **emitted** order, and each insn's
  dependence links. `src` is read from the dump of the pass BEFORE the scheduler (`.combine` for
  sched1, `.greg` for sched2), because `sched.c` numbers LUIDs by walking that chain and the chain
  is *not* UID order - combine creates high-UID insns and splices them where the combined insn was
  (two such splices on the smoke row alone). gcc 2.x `sched.c` fills a block from the end, priority is the
  longest dependence path, and ties are broken by `INSN_LUID`: equal priorities with a different
  order means a **tie broken by statement order** (move the statement in the C); different
  priorities means a **dependence edge appeared or vanished** (the `deps on` column says which).
* **`greg`** - the allocno table: pseudo, variable name, `n_refs`, `live_length`, calls crossed,
  `global.c allocno_compare` priority, the allocno **order**, and the hard register each one got.
  Allocnos present in one text and not the other are printed first as **MISSING ALLOCNO** - a
  `register x ASM_REG("$19")` pin is exactly that, and every lower-priority allocno slides one
  register down the callee-saved sequence. The dump's own `Register dispositions` is the truth; the
  `alloc_sim` model's agreement is printed as a flag, not as an answer.
* **`lreg`** - refs / live length / calls crossed per named pseudo, and the **flow vector**: when it
  is identical, the two texts pose the same allocation problem and any register difference is
  allocno ORDER, not lifetimes.
* **`loop`** - each loop's real insn count and every movable's verdict (`moved` / `not desirable` /
  `not safe`) plus the biv/giv/unrolling diagnostics, aligned by position. A changed insn count with
  no changed decision is not evidence.
* **everything else** - a filtered insn-pattern diff of that pass's dump, pseudos anonymised by
  first appearance (raw UIDs and regnos shift the moment a pin is erased, so neither ever aligns).

`--around` takes a C variable name (resolved to its pseudo through `alloc_sim.decl_pseudos`), a hard
register (`$19`, `a0`), a bare pseudo number, `L<n>` for a source line (its variables are used, its
comment is not), or an RTL substring. Mapping an assembly line back to RTL is **not** supported:
name the register or the variable.

## Honest limits

* `--score` runs `tools/verify.py`, which scores inside `build_ovl/`. That is the one sanctioned
  write outside the lane, and the kit cannot and does not prevent it.
* The shim re-homes a compiler only when it would run at the repository root. It deliberately leaves
  the scorer's own compiles (which run in `build_ovl/` and in the candidate's directory) alone: a
  shim that forced every compiler into the lane would break scoring, including in grandchildren that
  inherit `PYTHONPATH`.
* `why.py --pass sched` needs the two texts to have the same block count; when they do not, it says
  so and points at `--pass jump` / `--pass flow`, because the scheduler is then not the first
  difference.
* `alloc_sim`'s `find_reg` model does not reproduce every disposition (30 of 38 on one smoke row).
  Read the `got` column, which is the dump.
* `--pass greg` / `--pass lreg` need `alloc_sim.FIRST`'s FIRST_PSEUDO_REGISTER for the cell, which
  covers 2.6.3, 2.7.2, 2.7.2-cdk, 2.8.0 and 2.8.1 - 1,098 of the ~1,117 pinned rows. The 19 rows on
  2.91.66 / 2.95.2 get a message saying so rather than a wrong table. `--pass sched` works on all of
  them (2.95.2 still prints `;; insn[N]: priority`), and falls back to the filtered RTL diff if a
  future cell does not.
