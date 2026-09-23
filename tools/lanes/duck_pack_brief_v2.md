## Start by restating the duck (round-62 rule; measured payoff below)

Every row in `rows.md` carries a **DUCK** brief: STATE (which pins are there, what each note claims,
what erasing each one alone does to the cc1 listing, what erasing them all does, and which pins fall
together), KNOWN (the mechanism hypothesis behind each pin, the generators that cover it and their
verdict on this row, and the distances earlier lanes reached) and NEEDED (what must change in the C,
whether the pins must fall together, and what is still unknown).

Before you compile anything for a row, **restate that row's duck in your own words**: the state, the
issue, and what has to happen for the pins to go. A row whose duck you cannot restate is a row you
are about to guess at.

Put every restatement in `rows.md` under one heading, spelled exactly:

    # Working DUCK restatements

with one `## <row id>` block under it, written before that row's first compile. The heading is fixed
so the restatements can be harvested later; three different spellings across nine lanes made the
last harvest mis-score three of them.

**Why bother:** across 37 early class-pack lanes with no duck, 70 of ~555 pack rows produced a
landed candidate (12.6%). Across 23 duck-briefed packs, 35 of 115 (30.4%) - 2.4x, on rows chosen
*because* they had already resisted the generators. The duck is the highest-paying instruction in
this brief.

---

## TOOLS - exact paths, verified. Do not guess a relative path.

`<KIT>` = `<REPO>/tools/lanes/lanekit`; `<REPO>` is the repository root (the pack builder writes the absolute path here and in `TOOLS.md`).
Work from your lane directory (`cd` into it first; `gcc -da` writes dumps into the current
directory). **There is no `RUNBOOK.md`** - `TOOLS.md` in your lane and `<KIT>/README.md` are the
index. Every cross-lane reference in this brief is an absolute path; a relative one will not resolve
from inside your lane.

    source <KIT>/env.sh          # from the lane: sets LANEKIT_LANE, PYTHONPATH, TMPDIR; lab/erase/why become commands

### The kit - use it before writing a harness of your own

Before writing a helper of your own, check this table - 26 lanes rebuilt the listing diff last night.

| what you want | command |
|---|---|
| **step 1**: prove the scorer on this row (the pinned text MUST come back `exact=true, total=0`) | `python3 <KIT>/lab.py baseline <row> --score` |
| what each pin holds alone, and which pins fall together | `python3 <KIT>/erase.py <row>` |
| screen candidate files | `python3 <KIT>/lab.py <row> v1.c v2.c --score` |
| screen named substitutions (`{"name": [["old","new"],...]}`) | `python3 <KIT>/lab.py <row> --subs shapes1.json --score` |
| screen every combination of independent axes (`{"axis": {"label": [["old","new"],...]}}`, names `label+label`) | `python3 <KIT>/lab.py <row> --grid grid1.json --score` |
| the cc1-listing diff of one candidate (vs pinned, erased or a file) | `python3 <KIT>/diff.py <row> cand.c [--vs erased] [--ctx 4] [--score]` |
| every `-da` pass dump of one text, into a lane directory | `python3 <KIT>/dump.py <row> cand.c\|pinned\|erased dumps/ [--cfg CFG] [--pass greg]` |
| score at another cfg (cell/flag trade), no ledger write; prints the hand-over when exact | `python3 <KIT>/lab.py cellscore <row> cand.c --cfg "2.8.1-G0"` (`--cfg` also works on any `lab.py` run) |
| the REPORT table, built from what was actually measured | `python3 <KIT>/lab.py report` |
| **why** the scheduler emitted that order | `python3 <KIT>/why.py <row> --pass sched --around <var>` |
| **why** that value got that register | `python3 <KIT>/why.py <row> --pass greg --around <var>` |
| **why** that constant stayed in / left the loop | `python3 <KIT>/why.py <row> --pass loop` |
| what changed at cse / combine / flow / jump | `python3 <KIT>/why.py <row> --pass combine --around <var>` |

`lab.py` logs every measurement to `lab_log.jsonl` and refuses more than 60 variants on one row
without `--more`. `why.py` compares `--vs` (default: the pinned text) with `--variant` (default: all
pins erased, or a path to your candidate). Read `<KIT>/README.md` once - it is one screen.

### The shared tools underneath

| tool | path | one line |
|---|---|---|
| byte scorer, the only authority | `<REPO>/tools/verify.py` | `python3 <REPO>/tools/verify.py <row> <ABSOLUTE path to .c>`; `--diff` prints generated \| retail |
| cc1-listing screen (CLI and `Screen` class) | `<REPO>/tools/xform/variant_screen.py` | `python3 <REPO>/tools/xform/variant_screen.py <row> variants.json [--verify] [--context 4]` — `--context N` already prints the diff; do not write a wrapper for it (five lanes did) |
| the listing normalisation the screen uses | `<REPO>/tools/xform/screen.py` | `from screen import compile_s, sdiff` |
| the pins of a text | `<REPO>/tools/pin_census.py` | `from pin_census import sites_of` — note: `tools/`, **not** `tools/xform/` |
| erase pins, site facts | `<REPO>/tools/pin_sites.py` | `from pin_sites import erase_many` — `tools/`, **not** `tools/xform/` |
| rows, recipes, paths | `<REPO>/tools/common.py` | `from common import rows, clean_path, parse_cfg` |
| scheduler dumps, ready lists, insn pairs | `<REPO>/tools/xform/sched_trace.py` | `compile_text(row, text, dumps=True)`, `decisions()`, `diagnose(before, after)` |
| per-pass RTL features, the first differing pass | `<REPO>/tools/xform/reg_state.py` | `observe(row, text)`, `comparison(a, b)` — `cls` names it: ops / order / wiring / late |
| the gcc 2.x allocator model | `<REPO>/tools/alloc_sim.py` | `read(row, text)`, `simulate(rd)`, `decl_pseudos(text, first)` |
| the allocator's real reason, under gdb | `<REPO>/tools/alloc_trace.py` | `python3 <REPO>/tools/alloc_trace.py <row> [--source cand.c] [--site N]` |
| loop-pass decisions | `<REPO>/tools/lanes/loop_census.py` | `dump_loop`, `split_functions`, `compare` |
| joint erasure subsets | `<REPO>/tools/lanes/joint_scan.py` | `subsets_of(...)` — the lane-safe wrapper is `erase.py`; do not run the repo-scale scan |
| gcc sources for every cell | `<REPO>/toolchain/gcc-src/<version>/` | one version directory at a time, `rg --max-filesize 4M` |

`0 of 9` duck lanes ever ran `sched_trace.py` or `reg_state.py`, while 14 of ~24 of their row
paragraphs ended by asking for exactly what those two print. `why.py` is the front door to both.

Never run `tools/sweep.py`, `tools/pin_search.py` or `tools/apply_candidates.py` from a lane. Never
edit `src/`. Never run git or a gate.

---

## THE WORKING METHOD (the sequence the three biggest wins used)

1. **Read first, compile later.** BRIEF.md, `rows.md` with every duck, `exemplars.md`, any
   `evidence/` bundle, and the named worked examples in `src/`. The lane that took one row from 37
   pins to 2 spent its first 20% of commands reading and nothing else. If a supplied evidence script
   hardcodes another lane's path, throw it away rather than run it - one lane nearly wrote into a
   different directory that way.
2. **Calibrate.** `lab.py baseline <row> --score` for every row in the pack, before any candidate.
   If the pinned control is not exact, stop and fix that; every later number is noise.
3. **Census the erasures.** `erase.py <row>` - what each pin holds alone, what they hold together,
   which fall together. Now every later trial has a reference point, and you know whether you are
   looking for one move or a coupled group.
4. **Replay the exemplars.** Every diff in `exemplars.md`, on every row, before inventing anything.
   That gives each row a residual distance you can rank against.
5. **Screen cheap, score rare.** Listing distance on everything; the byte scorer only on
   distance 0 (and at most a couple of near ones). In the lanes that solved rows, 1-6% of variants
   reached the scorer. Scoring everything is how a lane runs out of time.
6. **Generate by family, not by guess.** One script per shape FAMILY that loops over the rows and
   over the family's parameters (operand width, host local, reuse strategy), not one file per idea.
   The 5/5 lane wrote three such scripts; the 209-file lane wrote one file per idea and left three of
   its five rows nearly untouched.
7. **When the black-box search stalls, ask the compiler.** `why.py --pass sched|greg|loop|combine`
   on the pinned text versus the erased text, then versus your best candidate. The winning shape in
   the 5/5 lane came from reading the actual `REG_DEP_OUTPUT`/`REG_DEP_ANTI` edges, not from another
   guess. Both complete failures in the mined set were lanes that reached this point with no tool.
8. **Escalate in a ladder.** Mechanical exemplar moves, then hand-designed shapes, then *combinations
   of independently-exact single moves*. Not combinations first.
9. **On a hit, confirm the mechanism.** Re-run the winner under `why.py` and state which decision
   flipped. That turns "found by trial" into a generator rule.
10. **Generalise inside the pack.** If two rows look alike, apply the winning family to both in the
    same loop. The 5/5 lane won 5 rows with 3 shape families.
11. **Keep the negatives**, including confounded ones you re-ran. An honest "distance 10 and here is
    the word that resists" is worth more than a story.

## EFFORT RULE

**Breadth before depth, then depth, then keep going.**

* Every row gets its duck restated and at least its baseline + erasure census + exemplar replay
  before *any* row gets deep work. A row with no measurement is not an open row, it is an unworked
  row - `lab.py report` prints `ZERO MEASUREMENTS` for it, and that is a lane failure, not a result.
  (One sol lane in fourteen spent its session on infrastructure for three rows and left two of five
  with no attempt at all.)
* Then go deep on the rows that moved - the ones whose distance fell when you touched them.
* **Keep going.** The mined lanes did 13-29 minutes of real work each. A lane that stops with open
  rows still at listing distance <= 4 has stopped early: at that distance the answer is a word or an
  order, and `why.py` will name it. Before you stop, for every open row you must be able to say
  which pass decides it and what you measured that failed.

---

## KNOWN MECHANISMS (current; each is a family that has paid)

* **Single-assignment pseudos and birthing priority** - a value written once has a different
  scheduling priority and lifetime than one written twice: **merge** two locals' lifetimes into one,
  **split** one into two, or compute into a **fresh local** (`abs()` into a new variable is the
  common case).
* **Allocation order = a missing allocno.** A `register x ASM_REG("$s2")` pin is one extra allocno;
  erasing it slides every lower-priority allocno one register down the callee-saved sequence. Fix
  the ORDER (declaration order, reference count, live length), not the register.
  `why.py --pass greg` prints the table; `alloc_trace.py` prints the allocator's own reason.
* **Narrow parameters / `assign_parms`** - a parameter declared `s16`/`u8` arrives with a conversion
  pseudo; the wrong width changes both the insn count and the allocation.
* **Symbol-named addresses at a splitting cell, and aggregate copies from typed symbols** - a pinned
  integer page constant is usually a symbol address (`t86_symaddr`), and a run of word-by-word
  stores is usually one aggregate copy from a typed symbol (`t78_aggcopy`).
* **Recovered inline helpers with narrow interfaces** - a repeated expression was a
  `static __inline__ s16 helper(s32, s32, u16)`; its parameter/return conversions are real insns
  while `loop.c` runs and vanish later, which keeps a loop above the hoisting threshold
  (`loop.c:1631`, `threshold * savings * lifetime >= insn_count`). `why.py --pass loop`.
* **Loop insn-count thresholds** - anything that changes a loop's real insn count can move a
  constant in or out of the loop. A changed count with no changed decision is not evidence.
* **Updates after a call** - a pseudo that already crosses a call takes no dependence on it, so a
  statement written after the call is hoisted above it (`t71_updateaftercall`).
* **Arm sink / hoist** - a statement moved into or out of an `if` arm, or duplicated into both arms
  (a duplicated statement in both arms is a legitimate original shape, not scaffolding).
* **Store next to its producer** (`t83`), **scope merge** (`t93`), **cast split** (`t94`),
  **statement permutation** inside a dependence-preserving run (`t72`).

A kind that matches none of these is written "unknown" in the duck - say so in the report rather
than forcing it into a family.

---

## REPORT.md - the required shape

`lab.py report` writes the measurement table; paste it and add the prose. One block per row:

    ### <row id>

    **Result:** solved (N pins removed) | partial (N of M) | open
    **The change:** one or two sentences, and the diff.
    **Mechanism:** which pass decided it, with the evidence from `why.py` quoted -
      "greg: near_dy was allocno rank 16 -> 21, $s2 -> $s4; the pin is the missing allocno".
      Not "the scheduler moved it": say which decision, in which block, with which priority.
    **Generator rule:** APPEARS (how to recognise the population), RESOLVES (the move), in one
      sentence each - so the move can be swept over the tree tomorrow.
    **What failed, with distances:** every direction measured, named, with its listing distance and
      its scorer total. The table from `lab.py report` is this.
    **What I would need to know:** for an open row only - the specific, falsifiable next
      measurement. "Another shape" is not an answer; "the live range of X across block 12 under the
      candidate" is.

A partial result is a success: land the group you can make byte-exact and leave the other pins.
"Impossible in C" is not an accepted verdict and has been wrong every time in this project; report
what you measured instead.

---

## LEGITIMACY - a candidate that breaks any of these removes nothing

The census counts these exactly like pins:

* No new `ASM_*`, `__asm__`, `volatile`, fences or fake dependencies (`x = e + a; x -= a;`,
  `f(a + v - v)`, a dead store).
* No one-trip block: `do { } while (0)`, `while (0) { }`, `for (;0;)`, or any block that runs once
  only to change what the compiler sees.
* No new branch whose two arms hold the same code. Moving an existing keep elsewhere removes nothing.
* Never edit an unscored arm (`NON_MATCHING`, `port`, `dead`): the scored arm is the whole subject.
* The compiler recipe is fixed per row (`cell` in `rows.md`); do not change it.
* An output goes to `out/<container>/<name>.c` (with its `.base_sha`) only when `verify.py` said
  `"exact": true` for that exact file, it has strictly fewer pin sites than the base, and it adds
  none of the forms above. `lab.py` checks all of this before it stages anything. No comment about
  the erased pin is left in the output file.
* A byte-exact but rule-breaking candidate is a hard no, even under time pressure. Record it as a
  rejected result with the reason - one lane rejected four that way and its report is better for it.

IO discipline (the disk is shared): never `grep`/`rg`/`find` recursively over `work/`, the repo root
or the home directory. Search narrow directories only (`tools/`, `include/`, `docs/`, one
`toolchain/gcc-src/<version>/`, your own lane), always with `--max-filesize 4M`. When waiting on a
process, wait on its PID, never on a `pgrep -f` pattern your own command line contains. At most 4
compiles in parallel.
