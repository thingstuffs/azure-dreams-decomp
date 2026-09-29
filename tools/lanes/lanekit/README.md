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
| `lab.py` | listing distance, pins left, byte score, and the REPORT table; `--base FILE`, `--cfg`, `cellscore`, `stage-cell` |
| `erase.py` | what each pin holds, and which pins fall together (`--cfg`: byte totals at another cell) |
| `why.py` | the pass DECISION that changed: priorities, allocnos, loop verdicts, RTL (`--cfg` for another cell); `--trace --block`: one block tick by tick; `--deps UID`: one insn's LOG_LINKS and dependents |
| `diff.py` | the unified cc1-listing diff of one candidate vs pinned / erased / a file (+ `--score`, `--cfg`, `--scorer [--norm-regs]`: the byte scorer's retail-vs-generated diff; `--scorer --classify`: ORDER / COLOUR / OPCODE / COUNT per region) |
| `checks.py` | the four proof checks (sole-ready, launched group, known-constant base, barrier): a verdict per residue insn |
| `dump.py` | every `-da` pass dump of one text into a lane directory (`--cfg` for another cell) |
| `prio.py` | the global-allocation priority table of one text at a cfg (refs, live, floor_log2, priority, got) |
| `regcmp.py` | how many NAMED variables sit in a different register than in a reference text (`--subsets`: every pin-removal subset ranked) |
| `install.py` | `TOOLS.md` in a lane: the same table with that lane's rows |
| `sitecustomize.py`, `lane_shim.py`, `env.sh`, `kitlib.py`, `retailmap.py` | plumbing; you never call these |

## Pin-removal source-shape possibilities

Read `../../learnings/pin_removal_possibilities.md` before inventing a new source family. It
catalogues aggregate-copy forms, lvalue signedness, prototype widths, struct fields versus raw
offsets, address-base sharing, variable split/merge and set-count effects, pointer-store CSE
effects, loop hoisting, and lexical control-flow order. Use these possibilities to rank hypotheses
for a target-local rebuild. The row's recorded recipe and full byte scorer remain the authority.

---

## lab.py - the harness

```
python3 .../lab.py baseline <row> --score          # STEP 1, always
python3 .../lab.py <row> v1.c v2.c --score         # variants as files
python3 .../lab.py <row> --subs shapes1.json --score [--score-top 3]
python3 .../lab.py <row> --grid grid1.json --score  # every combination of independent axes
python3 .../lab.py <row> v7.c --cfg "2.8.1-G0" --score          # measure at another cfg
python3 .../lab.py cellscore <row> v7.c --cfg "2.8.1-G0"        # trade check + hand-over lines
python3 .../lab.py stage-cell <row> v7.c --cfg "2.8.1-G0" --note "mechanism"   # exact there -> out/ + cells.jsonl
python3 .../lab.py <row> --base cand/best.c --subs s.json --score   # substitute on YOUR file, not the erased text
python3 .../lab.py report                          # the REPORT.md table, from lab_log.jsonl
```

* **Before writing a helper of your own, check this README - 26 lanes rebuilt the listing diff
  (`diff.py`), 23 the dump fetch (`dump.py`), ~21 an `itertools.product` grid (`--grid`) in round 73.**
* **`--base FILE`** (with `--subs` / `--grid`) starts every substitution set from FILE instead of the
  pin-erased text - round 80: three lanes wrote `gen.py base.c subs.json outdir` for exactly this. `@name`
  and `"@base": "pinned"` still mean the pinned text; the guards, the misses log and the staging gate
  (admissible vs the lane's `base/` copy) are unchanged. Variant files given on the command line are
  measured as they are (`--base` does not touch them).
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

* **`stage-cell <row> cand.c --cfg CFG --note "..."`** is the hand-over `cellscore` describes, done: when
  `cand.c` scores exact at CFG (`kitlib.score_at`, no ledger write) AND passes `kitlib.admissible` vs the
  lane's `base/` copy, it is copied to `out/<container>/<file>.c` with the base's `.base_sha` and
  `cells.jsonl` gets `{"id","to","coherence","pins_before","pins_after"}` (the format
  `tools/fidelity/land_recipe_move.py` reads; a re-stage of the same id + cfg replaces its line). Not exact
  or not admissible: refused, exit 1, nothing staged (the attempt is still journalled in `lab_log.jsonl`).
  `--note` (the coherence argument) is required. Rule 2 is not scored - use `cellscore` for that.

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
                    [--cfg CFG] [--scorer [--norm-regs]]
python3 .../diff.py <row> cand.c --scorer --classify [--cfg CFG]
python3 .../prio.py <row> <cand.c|pinned|erased> [--cfg CFG] [--top N] [--all]
python3 .../dump.py <row> <cand.c|pinned|erased> <outdir> [--cfg CFG] [--pass sched|greg|lreg|loop|combine|cse|jump|all]
```

`diff.py --cfg CFG` lists/scores both texts at that cell (no ledger write). **`--scorer`** prints the byte
scorer's retail-vs-generated disassembly diff (`-` retail, `+` generated; what `cdkdiff.py` / `sd.py` did)
at the row's cfg or `--cfg`; **`--norm-regs`** first renames each side's registers by first appearance and
masks branch targets, so a pure register renaming disappears and only real differences remain (`adiff.py`).

**`--scorer --classify`** labels every differing region of the scorer's listing, with counts: **ORDER** (the
same instruction, moved - identical text outside the LCS, paired nearest first), **COLOUR** (equal once the
allocatable registers v/a/t/s/fp are renamed), **OPCODE** (a different instruction or constant) and
**COUNT** (an insertion or deletion). It names the residue's pass before anything is swept: ORDER = a
scheduler (`why.py --trace`), COLOUR = allocation (`why.py --pass greg`, `prio.py`), OPCODE = cse / combine /
loop. An exact text prints "nothing to classify".

**`prio.py`** prints, for ONE text at a cfg, the `global.c` allocation table in allocno order: pseudo,
variable, refs, live length, calls crossed, `floor_log2(refs)`, the priority
(`floor_log2(refs) * refs / live * 10000`, `alloc_sim.priority`), the rank that priority alone gives
(`!` where the dump's own order differs) and the hard register got (`--all` adds the local-allocation
pseudos). It is `r80_cell_c1b/prio.py`; `why.py --pass greg` is the two-text comparison.

**`regcmp.py <row> cand.c [--ref ref.c] [--cfg CFG]`** is a progress measure for big register rows, where the
listing distance moves in dozens of lines per allocno: it compiles the candidate and the reference (default the
row's src text), takes `prio.py`'s table and prints every C variable that got a different hard register
(`name: was -> now (refs/live=priority)`) and the count; unnamed temporaries are ignored. **`--subsets`** erases
every subset of the candidate's live pins (`kitlib.sites` / `kitlib.erase`, as `erase.py`; refuses above
`--max-pins`, default 8) and ranks them by that count, writing the texts to `regcmp/`. It is
`r80_opus_r2`'s `pcmp.py` + `combo.py`.

`diff.py` prints the listing diff `lab.py` stores as `experiments/<func>/<name>.diff`, for one file,
then the distance line; without `--score` it writes nothing. `dump.py` is `kitlib.dumps` (the compile
`why.py` uses) writing `<outdir>/<stem>.<pass>` and `<stem>.s`; `sched`/`cse`/`jump` include their
second pass; `outdir` must be inside the lane.

## erase.py - what each pin holds

```
python3 .../erase.py <row>                       # lone + all + every pair (<= 8 pins)
python3 .../erase.py <row> --mode subset --budget 60
python3 .../erase.py <row> --variant experiments/func_X/v7.c
python3 .../erase.py <row> --variant cand.c --cfg "2.7.2-cdk-G0"   # byte totals at another cell
```

Prints, and writes `erase_<func>.md`: every site with its line, its pin, its statement and the
listing distance of erasing it **alone**; the distance with **all** pins erased; and the subsets -
every pair on small rows, plus the same-macro and same-variable groups (`joint_scan.subsets_of`,
reused rather than re-derived). A pair **FALLS TOGETHER** when erasing both leaves a residue no
larger than either alone (`duck_brief.fall_together`): those pins are one mechanism and one
candidate has to move all of them. `--variant` runs the same scan on a candidate you have already
written - which of the remaining pins is still holding it.

Listing distances only; the byte scorer is never called here; the ledger is never touched. With `--cfg CFG`
the pinned listing is not retail's, so each erasure is byte-scored at CFG instead (`r80_cell_c2`'s
`erase_cfg.py`; 4 threads, 5-20 s each, mode defaults to `all`).

## why.py - the pass-decision explainer

```
python3 .../why.py <row> --pass sched|sched2|greg|lreg|loop|cse|cse2|combine|flow|jump|jump2|rtl|dbr
                        [--variant FILE|erased] [--vs pinned|erased|FILE] [--around TOKEN] [--top N]
```

`--cfg CFG` compiles both texts at that cell (the round-80 `why_cfg.py` wrapper).

**One text, one block, tick by tick** (round 80, `r80_fable_n1` read these by hand from the raw dump):

```
python3 .../why.py <row> --pass sched2 --block <N|bN|uN|rN> --trace [--variant F] [--cfg X] [--retail]
python3 .../why.py <row> --pass sched2 --trace --insn 781 --variant cand.c [--block ...]
python3 .../why.py <row> --deps 781 [--pass sched2] [--variant cand.c] [--cfg X]
```

* **`--trace`** compiles ONE text (`--variant`, default the erased text; `pinned` or a file) with `-dap` and
  prints, for the block `--block` names, the table in emitted order - `pos` (forward position), uid, `src`
  (INSN_LUID rank, from the previous pass's chain; `?` = not in that dump, e.g. prologue insns or sched1's
  split insns), static `prio`/`refs`, the tick it became `ready`, the tick it was `picked` and `why` - then
  every tick: the pick, its reason and the full ready list with dynamic priorities (`[launch U]` = a queue
  release). Reasons: `sole` (the only ready insn: always issued), `priority` (tagged `[launched: birthing
  boost]` in sched1 for `adjust_priority`'s 0x7f000001, `[tail: ...]` for the jump/call kept at the end),
  `hazard` (`schedule_select`'s `greater potential hazard`, with what the sort had first), `LUID tie`
  (equal priority, the higher LUID goes first: the statement-order lever), `class/stale-sort` (equal
  priority but the LOWER LUID won: `rank_for_schedule`'s dependence class, whose cost is not in the dump, or
  a list SCHED_SORT did not re-sort - the one checkable fact, whether the loser is a LOG_LINK of the
  last-scheduled insn, is printed), `tie` (a LUID is unknown), `stall` (every ready insn blocked).
* **`--block`**: plain `N` = an insn uid when some block holds it, else the basic block number (the header
  says which reading it took); `bN` block number, `uN` uid, `rN` retail word index (scores the text).
* **`--retail`** byte-scores the text and adds `gen` / `retail` columns: uid -> generated word (the `-dap`
  `# <uid> <pattern>` annotations, aligned to the scorer's disassembly on mnemonic with li/la/symbolic
  loads expanded - a model of the assembler whose coverage is printed; `-` = not placed) -> retail word (LCS,
  moved instructions paired by identical text). On an exact text the scorer prints no listing and it says so.
* **`--insn N`** narrows to one insn: its dependents (it becomes ready when the last of them is issued),
  the tick it became ready, what it lost at each tick and why, and the tick it was picked.
* **`--deps UID`** prints the insn's LOG_LINKS with their kind (true / anti / output) and the insns whose
  LOG_LINKS name it (its `ref_count` owners), at `--pass` (default `sched2`; any pass dump works).

Smoke (r80_fable_n1's 819B3414 `g_seed` at 2.7.2-cdk-G0): uid 781 -> gen [180] -> retail [172], ready from
T-19 after 528, loses T-19 on priority, T-20 on `potential hazard` to 521, T-21..T-23 on priority, and at
T-24 is `sole` - the report's whole mechanism, in one command.

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

## checks.py - the four proof checks, per residue insn

```
python3 .../checks.py <row> cand.c [--cfg CFG]
```

One `-dap` compile and one byte score of `cand.c` (at `--cfg`: nothing written), the residue classified as
`diff.py --classify` does, and for every residue insn one verdict with the evidence line of each check that
applies (`tools/learnings/pin_removal_possibilities.md`, "Proof checks"):

| verdict | check | meaning |
|---|---|---|
| `OPAQUE-BASE` | (iii) | `ori` where retail has `addiu`, made by combine's PLUS->IOR on a pseudo with ONE set from a CONST_INT: the base must be opaque (multi-set, parameter, HIGH/load); order is irrelevant |
| `BARRIER-GOVERNED` | (iv) | a volatile asm (`ASM_KEEP`, ...) shares the insn's sched2/sched1 block: order experiments are inert while it stands |
| `NOT-REORDERABLE` | (i) / (ii) | sched2: retail has it earlier but it was issued as the lone ready insn or on priority; sched1: retail's "non-launched N after launched H" with no non-launched consumer of H below N and H not a load |
| `REORDERABLE` | (i) / (ii) | the deciding pick was a LUID tie (or H has the consumer the rule needs) |
| `UNKNOWN` | - | the dumps cannot decide: no uid (an assembler `nop`), COUNT/COLOUR residue, an unknown LUID, a hazard or class pick |

The precedence is the table's order; every check's evidence is printed, so a `BARRIER-GOVERNED` insn also
shows what (i)/(ii) would say once the barrier is gone. Directions use the drift of the nearest unmoved
word, so an indel earlier in the function does not flip "earlier" and "later". Smoke: both r80_fable_n1 rows
reproduce the report (819B3414 g_seed: 780/781 BARRIER-GOVERNED by ASM_KEEP uid 483, 781's (i) line = sole at
T-24; 800AFA68 a_t2: (ii) NOT-REORDERABLE, consumers 30*/41* launched, 49 above 44; c_nokeep_noreg: 19
OPAQUE-BASE `ori`s on pseudo 95 = 0x1f800000).

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
* The uid -> generated-word map (`--retail`, `checks.py`) is a mnemonic alignment of gcc's `-dap` assembly
  against the scorer's disassembly with a small table of assembler macro expansions, not the assembler
  itself; a word it cannot place prints `-` and a check without a retail position says `UNKNOWN`.
* `--trace` reads gcc 2.6-2.8 `sched.c` commentary; the haifa scheduler of 2.91.66 / 2.95.2 prints another
  format and the trace refuses rather than guesses.
* `alloc_sim`'s `find_reg` model does not reproduce every disposition (30 of 38 on one smoke row).
  Read the `got` column, which is the dump.
* `--pass greg` / `--pass lreg` need `alloc_sim.FIRST`'s FIRST_PSEUDO_REGISTER for the cell, which
  covers 2.6.3, 2.7.2, 2.7.2-cdk, 2.8.0 and 2.8.1 - 1,098 of the ~1,117 pinned rows. The 19 rows on
  2.91.66 / 2.95.2 get a message saying so rather than a wrong table. `--pass sched` works on all of
  them (2.95.2 still prints `;; insn[N]: priority`), and falls back to the filtered RTL diff if a
  future cell does not.
