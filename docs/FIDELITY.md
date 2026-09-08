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

## Next

- B1 (mid-row) rows: 362 rows carry only mid-row sites (186 with a single site), 207 mix kinds.
  The rewrite needs a reader; a Sonnet pilot over 15 single-site rows is measuring yield
  (`work/lac_lane/pilot/`); candidates land through `tools/apply_candidates.py` (verify, copy,
  journal) and the touched windows through the gate.
- A1 (epilogue) stays as spelled unless a per-row reader finds the fall-through form.
