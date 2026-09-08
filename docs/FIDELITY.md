# Fidelity debt: what is mechanical, measured (2026-09-08)

The baseline audit (`config/decomp_audit_baseline.json`, byte-derived at the pin) lists 3,018
LABEL_AS_CALL and 809 PASSTHRU_NO_ARGS sites, the two classes the plan calls blocking (L1 requires
none). Both were measured on this tree through the window gate before anything was built:
`work/exp_lac/REPORT.md`, `work/exp_passthru/REPORT.md`.

## What the classes are

- **LABEL_AS_CALL**: the C "calls" a pseudo-function that is a label, almost always the function's
  own tail (with true-space names 1,390 epilogue sites and 1,554 mid-row sites lie inside their
  row; only 88 target another row). m2c spelled the retail `j` as a call declared noreturn.
- **PASSTHRU_NO_ARGS**: `f()` written with no arguments where retail's callee reads argument
  registers the caller left in place (the audit's `need`). Byte-exact, semantically silent.

## Measured (20 rows each, window gate)

| class / shape | pass | mechanism |
|---|---:|---|
| PASSTHRU_NO_ARGS, caller's own parameters | 13/20 (65 %) | `f(arg0..argK)` + prototype; predictor = filler positions the callee never reads (≤1: 11/12; ≥2: 2/8); the per-row scorer agreed with the gate 20/20 |
| LABEL_AS_CALL mid-row (B1) | 8/10 | `if (c) { A; tail(); return; } B; T` → `if (c) { A' } else { B' } T`, rejoining at the shared tail; needs a reader for the data flow (merged locals), one row needed a local widened; scorer agreed with the gate 24/24 (`linked-target` class catches the wrong-target case) |
| LABEL_AS_CALL epilogue (A1) | 2/10 | `return;` fails three ways: retail's `j` carries a filled delay slot gcc's own epilogue jump does not get (row grows a word), frameless rows get an inline `jr ra`, and one row's honest fix is deleting the statement (fall into the tail). Not mechanical. |

## Built and landed

- `tools/xform/t8_passthru.py` (sweep `t8_passthru`): the local rule exactly as measured, plus one
  relocation rule (a prototype naming a type typedef'd below it moves before the definition).
  Eligibility: one audited site per file, the caller declares the needed parameters and does not
  reassign them. Dry run 109 exact of 129 eligible; the sweep landed **109 rows**, every touched
  window re-gated byte-identical (46/46), SLUS gate MATCH. The other 680 sites need argument
  values the caller does not hold in its own parameters (174 rows), share a file with other
  sites (341), or are ordinal-ambiguous (162): reader work.
- The fidelity census is now **live**: `tools/census.py::live_audit` keeps a baseline site only
  while the current text still spells it (a `target(` call, an asm-aliased call, an empty-paren
  call for PASSTHRU_NO_ARGS); `levels.py` and STATUS use it, so a removed site stops blocking
  the row. Twenty rows turned out to have been structured already at the pin (the byte-derived
  audit still lists their `j`); they are no longer counted.

## Classification through the shipped toolchain (2026-09-08, `work/exp_psyq/REPORT.md`)

The genuine Psy-Q levels 4.0–4.6 (CC1PSX.EXE + ASPSX.EXE under wibo) are on this box, so the
question "what does a pin stand for" was measured instead of argued:

- **gcc-facing pins → source shape.** 15/15 rows with load-bearing pins: the shipped SN cc1 and
  the decompals rebuild are byte-identical with the pins and byte-identical without them (same
  words wrong at the same positions). No compiler difference hides under any pin.
- **maspsx markers → source shape too.** Genuine ASPSX (2.56/2.67/2.79/2.86) never fills a
  branch or jump delay slot from a neighbouring instruction (always `nop`), on hand-written
  assembly and on genuine cc1 output alike; the fills the markers encode can only come from
  cc1's delay-branch pass on a different source shape. 0/12 marker rows match through the genuine
  pipeline with the markers no-op'd.
- **The noreturn tail-call spelling has no producer in the shipped toolchain.** Genuine cc1
  emits `jal` for a `__attribute__((noreturn))` call and genuine ASPSX leaves it; maspsx's
  `jal`→`j` conversion and frame elision are ours. 9/12 rows diverge by up to six words for that
  reason alone. This is the same population as the intra-row label-as-call sites, and the reason
  the mid-row `if/else` rewrite works (the real source jumped to a shared block inside the
  function and gcc filled the slot itself).

Consequence (in `docs/PLAN.md`): pins, markers and the tail-call spelling are one class of
scaffolding debt with one remedy — find the shape, prove it through the window gate, delete the
scaffolding — attempted at L1 (mechanical sweeps), by every L3 lane (`tools/agent_task.py`
journals pins/sites before and after) and in a dedicated L5 pass; `STATUS.md` carries the two
new shape lines (tail-call spelling, marker pins). The end state retires maspsx's tail-jump and
frame-elision passes.

## Pins: what a shape search finds (2026-09-08, `work/exp_pins/REPORT.md`)

20 rows, 29 load-bearing sites, 205 scorer probes, window-gated: **4 rows (5 sites) pin-free,
0 pin-reduced, 16 unchanged**. The census class predicts tractability: `reg-rename` 3/4 rows,
`length-drift` 1/4, `addressing` / `block-order` / `code-motion` / `reorder-only` 0/3 each. The
four shapes that worked: a reassigned parameter used as a loop counter moved into a fresh local;
one reused local split into two; an inner-block declaration hoisted to function scope; a loop
increment sunk to the end of the loop body (a barrier). What never worked, and is dropped from
any menu: declaration-order permutation (0/9), explicit temporaries (0/9), statement reorder
other than the increment sink (0/13), polarity flips (0/8). Three mechanisms explain 14 of the
16 failures — cse deleting a copy retail keeps, a dead value retail parks in a delay slot, a
fence position no statement boundary reproduces — none reached from C within the budget. A
transform for the tractable class, `tools/xform/t9_regpins.py`, is built from those four shapes.
Astra's lanes now attempt removal on every refined row and journal the counts (first 16 rows:
10 pins removed).

## Lanes and transforms landed (2026-09-08, later)

- **Epilogue (A1) pilot, 15/15** (`work/lac_lane/epi_pilot/`, Opus): the mechanism behind the earlier
  2/10 is gcc ≥ 2.8.0 collapsing a jump-to-return into an inline `jr ra` when the function is
  frameless (frame 0, no ra save); the 2.7.2 family keeps the jump in every shape. Framed rows and
  2.7.2-family rows take `return;` / `return N;` / `return call(...)` or the deleted statement; a
  frameless row pinned to a 2.8.x cell is byte-exact from pin-free C at a 2.7.2-family cell — its
  pinned cell was an artefact of the label-as-call spelling (our assembler front end elided the
  frame, so the config search never saw the contradiction). 15 rows landed (13 as-is, 2 with the
  cell corrected: `common.set_row_cfg`, recorded in the split table as `config_was`); the sweep
  now accepts a stock-cell correction from a plugin (`verify_fn(cand, cfg=...)`, `info["cfg"]`).
  The audit's `v0=imm:N` is unreliable (two rows are void).
- **`tools/xform/t10_epilogue.py`** (sweep `t10_epilogue`), built from that recipe: menu per site
  drop-before-return → `return;` → `return N;` → `return <preceding expression>;` → fall into the
  tail → the same C at a 2.7.2-family cell for frameless 2.8.x rows. Dry run and sweep agree:
  **453 rows applied, 979 of 1,418 epilogue sites removed, 13 rows with the cell corrected (all to
  2.7.2-cdk / 2.7.2-cdk-G0)**, 342 touched windows byte-identical, SLUS gate MATCH. Refusals: 133
  rows with no exact candidate (large rows whose residue is other scaffolding — re-run after pin
  work), 36 whose target is no longer spelled, 12 with the target outside the row, 12 inside
  `#ifndef NON_MATCHING`. The old `t3_epilogue` plugin is retired (its in-row test used the wrong
  address space and matched no row).
- **Mid-row (B1) pilot, 10/15** (`work/lac_lane/pilot/`, Sonnet): the if/else rejoin, with the
  split point found from the target address minus the row's true address. Failures: two rows
  without a rowbase record (the gate links the new jump at the synthetic base — a data fix under
  `config/overlays/*.rowbase.jsonl`), two where retail keeps a redundant `j` to the next
  instruction that gcc eliminates, one delay-slot dead value. 10 rows landed through
  `tools/apply_candidates.py` (journal `t11_midrow`).
- **Register pins, `tools/xform/t9_regpins.py`** (sweep `t9_regpins`): the four shapes from the
  experiment, gated on the T2 journal (the live text is what T2 left, not the census's original).
  Live tractable class: 91 rows (every live pin colouring-only); 8 rows changed (7 pin-free, 1
  reduced), 11 pins removed. The tractable seam is small; the bulk of the 13,600 load-bearing
  pins needs a reader per row (the lanes now attempt it).

## Next

- B1 (mid-row) rows: 362 rows carry only mid-row sites (186 with a single site), 207 mix kinds.
  The rewrite needs a reader; a Sonnet pilot over 15 single-site rows is measuring yield
  (`work/lac_lane/pilot/`); candidates land through `tools/apply_candidates.py` (verify, copy,
  journal) and the touched windows through the gate.
- A1 (epilogue) stays as spelled unless a per-row reader finds the fall-through form.
