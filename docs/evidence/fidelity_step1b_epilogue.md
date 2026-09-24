# Toolchain fidelity STEP 1b: which compiler emitted the 2.8-era return epilogues?

Measurement only (brief `work/fidelity/STEP1B_BRIEF.md`; follows `docs/evidence/fidelity_step1_aspsx_diff.md`,
decision 1). Nothing under src/, include/, ledger/, config/, recipes, tools/maspsx, tools/build or toolchain/ was
touched; no gate, landing, sweep or git command was run.

- Tool: `tools/fidelity/epilogue_model.py` (+ `tools/tests/test_epilogue_model.py`, 7 tests: the text model, the
  census, the retail return-shape classifier).
- Data: `work/fidelity/step1b/epilogue_model.jsonl` (601 rows, every row at a 2.8.0 / 2.8.1 / 2.91.66 / 2.95.2 cell),
  `work/fidelity/step1b/rows_epilogue.tsv` (one line per row), `work/fidelity/step1b/control_272.jsonl` (105-row
  2.6.3 / 2.7.2 / 2.7.2-cdk control), run logs `run_2x.log`, `run_control272.log`; the SN egcs cc1 found in the
  archives is copied to `work/fidelity/step1b/genuine_cc1/egcs-2.91.66-psx/` (git-ignored).
- Re-run: `python3 tools/fidelity/epilogue_model.py --workers 8 --psyq` (5 min), `--report` for the first two tables.
  The tool keeps its scratch in `work/fidelity/step1b/tmp` (the first runs used aspsx_diff's shared
  `work/fidelity/tmp/rows` and removed it at the end, erroring 10 rows of the concurrent asv_trial run - fixed).

## Headline

**No compiler we hold, with any option, emits the epilogue retail has.** Every 2.8-era cc1 - our gcc 2.8.0 / 2.8.1 /
2.91.66 / 2.95.2 and every genuine SN build (psyq 4.3/4.4/4.5 `2.8.1 SN32 BUILD 4.0.0010`, the psyq 4.5 archive's
SN `egcs-2.91.66 (PSX)`, psyq 4.6 2.95.2), driven directly or through the genuine CCPSX driver - fills the return
slot with the stack teardown under `.set noreorder`. The only option that stops it, `-fno-delayed-branch`, un-fills
every other slot too (retail-exact on 8/601 rows; median 37 differing words on the 496 target rows).

**What retail has is gcc 2.7.2's TEXT epilogue on 2.8-era code.** Applying gcc 2.7.2's own epilogue decision
(`function_epilogue` + `mips_epilogue_delay_slots`, quoted below) to our 2.8-era cc1 output - a text model, rule
`t272` - makes **genuine ASPSX 2.79 (and 2.77) alone reproduce retail on 580 of the 601 rows**:

- **all 459 `_maybe_unfill_return_delay` rows and all 37 `_unfill_via_load_delay` rows (496/496)**;
- **all 84 rows that were already genuine-exact** (the control; the naive "rewrite every epilogue" probe breaks one
  of them, `town/func_8047EA14`, and the 2.7.2 rule keeps it - the rule is complete, not just permissive);
- the other 21 are the rows with a second maspsx behaviour (step 1's joint causes, `$gp` externs, `_fold_selfinc_la`,
  `_fold_lo_into_accesses`); `t272` shrinks the 15 epilogue-involved ones (e.g. 7 -> 4 words) and leaves them to that
  second behaviour.

The retail binary agrees in aggregate: in the cc1 output of the 601 rows there are 469 noreorder `j $31 / addu $sp`
blocks in functions that save any register besides `$31`, and retail has **469** `addiu sp / jr ra / nop` returns
(filled with the teardown: **0**); 48 blocks in `$31`-only functions directly after `lw $31`, retail has 49
`lw ra / addiu sp / jr ra / nop` returns; 1 block in a `$31`-only function with a real instruction before the jump,
retail has **1** `jr ra / addiu sp` return (filled).

**When the compiler changed, from gcc's own ChangeLog** (gcc-2.8.0 `ChangeLog`, in
`toolchain/gcc-src/tarballs/2.8.0-gcc-2.8.0.tar.gz`):

```
Fri Jul 11 09:49:15 1997  Jeffrey A Law  (law@cygnus.com)
	* mips.c (epilogue_reg_mentioned_p): Delete unused function.
	(mips_epilogue_delay_slots): Likewise.
	(function_epilogue): Greatly simplify.
	(mips_expand_epilogue): If we have a null prologue/epilogue, then use a normal return insn.  Emit blockage
	insns before stack pointer adjustments.
	...
	* mips.h (DELAY_SLOTS_FOR_EPILOGUE): Delete.
	(ELIGIBLE_FOR_EPILOGUE_DELAY): Likewise.
	* mips.md (return): Remove expander and change the pattern to look like a standard "return" insn.
	(return_internal): Show use of $31 explictly.
	(epilogue expander): Enable.
```

So the compiler that built these ~580 rows is **a gcc2-lineage cc1 from before 11 July 1997 that already had the
2.8-era code generation our 2.8.x cells reproduce** - a 2.8 development snapshot (the cdk cell, psyq 4.1's
`cygnus-2.7.2-970404`, is the same lineage three months earlier and has the text epilogue too). No PsyQ release we
hold ships it (inventory below). All four 2.8-era cells (2.8.0, 2.8.1, 2.91.66, 2.95.2) are therefore codegen
proxies for that one unheld compiler, not the historical toolchain - and their split is thin: the SN 2.8.1 binary
already produces our 2.8.0 output on 179 of the 191 rows registered at 2.8.0. The two maspsx helpers are therefore not assembler models and not arbitrary:
they are exact models of that compiler's epilogue decision followed by genuine ASPSX's reorder-mode filler.

## gcc source: the epilogue forms and their conditions

gcc 2.8.1 (`toolchain/gcc-src/2.8.1/config/mips/`; 2.8.0, 2.91.66, 2.95.2 have the same structure):

- `mips.md:6514` `define_expand "epilogue"` - unconditional, calls `mips_expand_epilogue` (`mips.c:5613`):
  `save_restore_insns` (the restores as RTL), `gen_blockage`, `addsi3 $sp,$sp,tsize`, then
  `emit_jump_insn (gen_return_internal ())` - or `gen_return` when `mips_can_use_return_insn` (`mips.c:5670`: no
  frame, `$31` not live).
- `mips.md:6537` `return_internal` = `[(use (reg:SI 31)) (return)]`, template `"%*j\t$31"`, type `jump`;
  `mips.md:124` `define_delay (eq_attr "type" "jump")` gives it one slot any single-word non-dslot insn may fill.
- `mips.c:3917` / `3960`: `%*` prints `.set noreorder` + `.set nomacro` **only if `final_sequence`** (the slot was
  filled by reorg). reorg (`reorg.c` `dbr_schedule`, run from `toplev.c:3572` iff `optimize > 0 &&
  flag_delayed_branch`) fills the return slot with the `addu $sp` directly before it: the return references only
  `$31`, so the teardown is always eligible. Hence the filled noreorder block on every non-leaf function, at every
  option that keeps reorg on.
- `mips.c:5526` `function_epilogue` prints only `.end` and statistics - there is no text-epilogue path left.

gcc 2.7.2 (`toolchain/gcc-src/2.7.2/config/mips/`; 2.6.3 alike): the epilogue expander is commented out
(`mips.md:6056`); `function_epilogue` (`mips.c:5072`) prints the epilogue as text:

- `mips.c:5080-5081`: `epilogue_delay = current_function_epilogue_delay_list; noreorder = (epilogue_delay != 0);`
- `mips.h:2041` `DELAY_SLOTS_FOR_EPILOGUE` = `mips_epilogue_delay_slots ()` (`mips.c:5378`): **1 only when the frame
  is empty or saves nothing but `$31`** (`mask == RA_MASK && fmask == 0`), else 0 - reorg may hand the epilogue a
  delay insn only in those cases.
- noreorder branch (`mips.c:5182-5225`): restores; for a `$31`-only frame the delay insn (or a `nop`); `j $31`;
  `addu $sp` in the slot. Reorder branch (`mips.c:5226-5239`): restores; `addu $sp,$sp,N`; `j $31` - the slot left
  to the assembler.

The `t272` model (`epilogue_model.rewrite(src, "t272")`) applies exactly that decision to a 2.8-era listing: a
noreorder `j $31 / addu $sp` block becomes `addu $sp / j $31` (reorder) unless the function saves only `$31` and a real
instruction already sits between `lw $31` and the jump (2.7.2's epilogue-delay form, also printed under noreorder).
On 2.7.2-family output it is a no-op by construction - measured: unchanged on 105/105 control rows (below).

What genuine ASPSX then does with the reorder-mode return is what the maspsx helpers hard-code: after a restore
sequence of 2+ registers it leaves `addiu sp / jr ra / nop` (`_maybe_unfill_return_delay`); after a lone `lw $31` it
puts the teardown in the load-delay slot, `lw ra / addiu sp / jr ra / nop` (`_unfill_via_load_delay`). The helpers'
trigger (`callee_restores >= 2`, i.e. `$31` plus any other register) is `mips_epilogue_delay_slots () == 0`.

## Option table (compilers and options tried)

Epilogue form on a 2+-register frame (`dungeon/func_7FFE7BE8` and a 3-register test function), our cc1 and genuine
CC1PSX; "filled" = `.set noreorder / j $31 / addu $sp`.

| compiler | options | return |
|---|---|---|
| our gcc 2.6.3 / 2.7.2 / 2.7.2-cdk | -O2 | `addu $sp / j $31` (reorder) - text epilogue |
| our gcc 2.8.0 / 2.8.1 / 2.91.66 / 2.95.2 | -O2 | filled |
| our gcc 2.8.1 | -g, -gcoff, -ggdb, -O1, -mabicalls, -membedded-pic, -mlong-calls, -fno-omit-frame-pointer, -p | filled |
| our gcc 2.8.1 | -fno-delayed-branch | reorder - but every other slot un-filled too |
| genuine CC1PSX psyq4.4 (= 4.3 = 4.5, `2.8.1 SN32 BUILD 4.0.0010`) | -O2, -O1, -O3, -G0, -g, -gcoff, -gstabs, -ggdb, -fno-schedule-insns(2), -mno-gpopt, -mmips-as, -msoft-float, -mno-split-addresses, -fno-omit-frame-pointer, -mdebuga..i | filled |
| genuine CC1PSX psyq4.4 | -fno-delayed-branch | reorder, every slot un-filled |
| genuine CCPSX psyq4.4 (`CCPSX 3.06.0015`) driver | -O2 [-g] | runs `cc1psx -quiet [-version] -O2 in -o out` - no hidden defaults; filled |
| genuine SN `egcs-2.91.66 (PSX)` (psyq 4.5 archive, BIN/WIN) | -O2 -G0 | filled |
| genuine CC1PSX psyq4.6 (2.95.2) | row recipes | filled |

`strings` of the psyq4.4 CC1PSX against our 2.8.1 cc1 show no option name the SN build adds. The CCPSX driver's
option handling (psyq4.4 `SN.INI` / `SN_PATH`) passes the user's flags through; `SN.INI` holds only paths and
libraries.

## Results on the 601 rows at 2.8-era cells (genuine ASPSX 2.79, all of aspsx_diff's modes, `-0` as the row needs)

Variants (each compared with the row's retail-exact maspsx object by aspsx_diff's comparator): `base` = our cc1 as
the pipeline runs it; `all` = every noreorder return block rewritten (step 1's probe); `t272` = gcc 2.7.2's rule;
`fndb` = our cc1 with `-fno-delayed-branch`; `psyq` = the genuine SN cc1 of the cell's generation through a cc1
wrapper (2.8.0 rows use the 2.8.1 SN binary: cross-generation); `psyq_t272` = the rule on its output.

| group (step 1 cause) | rows | base | all | t272 | fndb | psyq | psyq_t272 |
|---|---|---|---|---|---|---|---|
| `_maybe_unfill_return_delay` | 459 | 0 | 459 | **459** | 0 | 0 | 442 |
| genuine-exact (control) | 84 | 84 | 83 | **84** | 5 | 84 | 84 |
| `_unfill_via_load_delay` | 37 | 0 | 37 | **37** | 3 | 0 | 37 |
| epilogue + a second behaviour (step 1 joint causes) | 15 | 0 | 0 | 0 | 0 | 0 | 0 |
| other maspsx-dependent (not epilogue) | 6 | 0 | 0 | 0 | 0 | 0 | 0 |
| **all** | 601 | 84 | 579 | **580** | 8 | 84 | 563 |

`t272` at ASPSX 2.77 gives the same 580. By container and cell:

| container | cell | rows | base | t272 | not t272-exact |
|---|---|---|---|---|---|
| dungeon | 2.8.0 | 175 | 5 | 171 | 4 |
| dungeon | 2.8.1 | 207 | 10 | 204 | 3 |
| dungeon | 2.91.66 | 2 | 0 | 2 | 0 |
| dungeon | 2.95.2 | 8 | 0 | 8 | 0 |
| main | 2.8.0 | 3 | 2 | 3 | 0 |
| main | 2.8.1 | 9 | 2 | 9 | 0 |
| main | 2.95.2 | 1 | 0 | 1 | 0 |
| ovmovie | 2.8.1 | 5 | 2 | 4 | 1 |
| slus | 2.8.1 | 119 | 31 | 108 | 11 |
| slus | 2.91.66 | 1 | 1 | 1 | 0 |
| slus | 2.95.2 | 4 | 3 | 3 | 1 |
| town | 2.8.0 | 13 | 8 | 12 | 1 |
| town | 2.8.1 | 39 | 13 | 39 | 0 |
| town | 2.91.66 | 6 | 2 | 6 | 0 |
| town | 2.95.2 | 9 | 5 | 9 | 0 |

**Genuine cc1 vs ours on these rows.** The genuine SN cc1's `.ent`..`.end` bodies equal ours on 589/601 rows (all
2.8.1, 2.91.66 and 2.95.2 rows - the twin result of `work/tailslot_aspsx/CC1_DIFFERENTIAL.md` now on 589 rows and
three binaries, including the SN egcs build); the 12 that differ are 2.8.0 rows compiled by the 2.8.1 binary
(cross-generation). `psyq_t272` = `t272` except those 12 and 5 dungeon bank rows (`func_80E91000`, `_80E9D000`,
`_80EA3000`, `_80EAF000`, `_80FA5000`) whose bodies are identical to ours but where the genuine cc1 emits one extra
`.text` before the composite body, which the comparator's composite-unit rule does not model (a harness limit, not a
code difference). So "genuine SN cc1 + the 2.7.2 epilogue decision + genuine ASPSX" = retail on the same rows.

**Controls.**
- The 84 genuine-exact 2.8-era rows stay exact under `t272` (84/84 at 2.79 and 2.77). The model changes their
  epilogues too (every multi-register frame, every `$31`-only `lw $31 / #nop / j` return) and ASPSX still gives
  retail; the one `$31`-only function with a delay insn (`town/func_8047EA14`, retail `jr ra / addiu sp`) is kept
  filled by the rule and broken by the naive rewrite.
- 105 rows at 2.6.3 / 2.7.2 / 2.7.2-cdk (8 per container x cell, `work/fidelity/step1b/control_272_sample.txt`):
  `t272` changes nothing on 105/105; verdicts unchanged (98 genuine-exact, 7 not, as in step 1). Their retail return
  shapes are the same families as the 2.8-era rows' (`addiu sp / jr ra / nop` 53, ld-shadow 20, filled teardown 2).

## Rows that still need maspsx under `t272`, and why

| rows | step 1 cause | after `t272` |
|---|---|---|
| dungeon/func_800C3928, func_80CC2828, func_81912154, func_819611CC | `_rotate_marked_store_into_jal_delay` + unfill | 7 -> 4 words: the store rotation remains |
| ovmovie/func_800413C0 | `_unfill_via_load_delay` + `_rewrite_arg_sibcall_jal_to_j` | 10 -> 6: the jal->j rewrite remains |
| town/func_8047E0D8 | `_unfill_via_load_delay` + `_rewrite_tail_call_jal_to_j` | 5 -> 1: the jal->j rewrite remains |
| slus/code2, konami_runtime_w_80033D54, w_80041AE4, w_80041C64, w_80043D04, w_80043E04, w_80043E60, w_80045340, w_8004D614 | `$gp` extern model + fired passes (2.8.1) | 35->12, 13->10, 6->3, 6->2, 6->3, 8->4, 6->2, 9->6, 11->8: decision 3 (`$gp` externs) remains |
| slus/w_80041134, w_8004DCA8 | `$gp` extern model | unchanged (8, 4): not an epilogue row |
| dungeon/func_81811E30, func_81811E70, func_81811EC0 | `_fold_selfinc_la` | unchanged: not an epilogue row |
| slus/w_8003E188 | `_fold_lo_into_accesses` | unchanged: not an epilogue row |

(The remainder after `t272` is attributed by step 1's ablations; this step did not re-ablate the maspsx leg
against the `t272` genuine object.)

## Genuine binaries searched (inventory)

| where | file | sha256 (12) | identity |
|---|---|---|---|
| toolchain/genuine psyq4.0 | CC1PSX.EXE | ddaa03030d1b | 2.7.2.SN32.3.7.0002 (text epilogue) |
| psyq4.1; 4.1 CD image (`RuntimeLibrary_4.1…rar`) GNU/ | CC1PSX.EXE | 17b0d9dc6a80 | cygnus-2.7.2-970404 SN32.3.7.0004 = cdk (text epilogue) |
| psyq4.3/4.4/4.5; 4.3 CD ISO GNU/; 4.5 MFD BIN/ | CC1PSX.EXE | 26eb8259fa3e | 2.8.1 SN32 BUILD 4.0.0010 (RTL epilogue) |
| 4.5 MFD archive (`_archives/rar45`) BIN/WIN/ | CC1PSX.EXE | a24ed21b8d37 | **new**: SN egcs-2.91.66 (PSX) (RTL epilogue) |
| psyq4.6; PSYQ_SDK.zip psyq/bin; Psy-Q_46.zip | CC1PSX.EXE | 0755e509f148 | 2.95.2 (RTL epilogue) |
| 4.1 / 4.3 CDs GNU/DOS; 4.5 MFD BIN/DOS | CC1PSX.EXE (go32) | 6801fea8e761 | 2.7.2.SN16.3.7.0003, DOS (not runnable under wibo; pre-2.8) |
| PSYQ_SDK.zip psyq/psyq (1995-12-20) | CC1PSX.EXE (go32) | d383902b6ed1 | 2.7.2.SN.1, DOS (pre-2.8) |

Psy-Q_47.zip and psyq-4.7-converted-full.7z carry no cc1. No held archive has a PsyQ 4.2-era (late 1997) cc1 - the
generation that would sit between `cygnus-2.7.2-970404` and the July-1997 epilogue change.

## Recommended recipe change and blast radius

The evidenced recipe for these rows is "2.8-era cc1 with the pre-11-July-1997 text epilogue + genuine ASPSX 2.77-2.81".
We do not hold that binary, so there are two routes (owner decision):

1. **Reconstructed cells** (toolchain change, needs sign-off): our gcc 2.8.0 and 2.8.1 rebuilt with Law's 1997-07-11
   change reverted, and - separately, each has its own egcs-lineage `mips.c` - 2.91.66 and 2.95.2 (or those 31 rows
   deferred): four patched compilers. A single pre-July-1997 snapshot cannot natively reproduce the body differences
   the four cells encode, so this is a model of the unheld compiler, not the compiler. The revert: `mips.md` epilogue expander disabled, `mips_epilogue_delay_slots` / `DELAY_SLOTS_FOR_EPILOGUE` /
   `ELIGIBLE_FOR_EPILOGUE_DELAY` and the 2.7.2 `function_epilogue` text path restored. Build and measure it outside
   toolchain/ first; the text model predicts: all 601 rows at 2.8.0/2.8.1/2.91.66/2.95.2 are affected; 580
   genuine-exact (84 unchanged + 496 new), `_maybe_unfill_return_delay` and `_unfill_via_load_delay` then fire on
   zero landed rows and retire (step 5 of the plan); 15 rows keep a second maspsx behaviour; 6 unrelated rows
   unchanged. Caveat the model cannot settle: with the RTL epilogue gone, sched2 can no longer interleave body
   insns with the restores and reorg's `$31`-only epilogue-delay choice becomes 2.7.2's `ELIGIBLE_FOR_EPILOGUE_DELAY`
   - in the cc1 output of a 150-row sample the restore tail was contiguous in every block except the one `$31`-only
   delay-insn case the rule already keeps. The other place a real build can diverge: the 48 `$31`-only
   `lw $31 / #nop / j $31` sites, where 2.7.2's reorg may hand the epilogue a body insn if
   `ELIGIBLE_FOR_EPILOGUE_DELAY` (2.7.2 `mips.h:2047`: `dslot == no && length == 1 &&
   !epilogue_reg_mentioned_p (PATTERN (INSN))`) accepts one; the model assumes none is taken and retail agrees
   (48/48 exact), which says the candidates were refused - but only a real build and gate can prove it.
2. **Keep the helpers, re-label them** as a model of that compiler (a `cell_imitation`-class construct in the
   ladder sense, not an ASPSX model): their docstrings' "Replicate ASPSX/retail" is wrong on the mechanism -
   genuine ASPSX passes a noreorder block through; the decision is cc1's. By this measurement they are byte-equivalent
   to "`t272` + genuine ASPSX" on all 496 rows they carry.

Also: of the 31 rows at 2.91.66 / 2.95.2 cells, 19 are exact only with the pre-July-1997 epilogue (11 are exact as they are, 1 has
a non-epilogue cause), which no egcs / 2.95 build has - evidence that those cells are proxies
(codegen-compatible on these functions) for the same snapshot compiler, not the historical toolchain.

## Decisions for the owner / orchestrator

0. Housekeeping (orchestrator): this step's first runs removed the shared scratch `work/fidelity/tmp/rows` under
   the concurrent asv_trial run; 10 of its rows are `status: error` for that reason (dungeon/func_800C7A44,
   func_800C7B34, func_800C7C24, func_809A32D4, func_809A35A0, func_809A38E4, func_809A4014, func_809A457C,
   func_81977E0C, func_81977FB8). A plain re-run of `tools/fidelity/asv_trial.py` recomputes exactly the non-ok rows.
   asv_trial (like aspsx_diff) also removes that shared directory at the end of its own run.
1. Accept the finding: the 2.8-era epilogue is a **compiler** property (pre-11-July-1997 gcc text epilogue on
   2.8-era codegen), not an ASPSX one and not any option of any held compiler.
2. Choose route 1 (build reverted-epilogue cells - four compilers: 2.8.0, 2.8.1, 2.91.66, 2.95.2 - then gate the 601 rows; retires two maspsx helpers,
   496 dependents) or route 2 (keep the helpers, re-label them as a cc1-epilogue model on the ladder).
3. Optionally, a search for a PsyQ 4.2-era SN cc1 (late 1997), the only binary that could make route 1 unnecessary.
4. The 2.91.66 / 2.95.2 cell assignments (31 rows, 19 of them epilogue-dependent) are suspect as history; a module-census check against the 2.8.x
   cells under the reverted epilogue would settle whether they collapse into one cell.
