# 800C7F80: plain-C follow-up, 2026-10-14

Final review outcome and scoped blocker account:
`docs/evidence/c7f80_plain_c_blockers_20261014.md`. No exact plain-C landing
proposal resulted; the full record below preserves the causal investigation.

## Result

No exact pin-free candidate and no production edit for this function.
The best valid source remains
`work/native_lane/plain_callarg_c7f80_20261014/candidates/base.c`: zero pins,
aligned byte distance 2 (0 substitutions, 2 indels), solely the exchanged order
of `sll a1,s1,2` and `li a0,1293`. This reproduces an inherited frontier rather
than claiming a new improvement. The registered recipe is `2.7.2-cdk-G0`.

All references to early producer UID154 concern the **pinned reconstruction's
compiler output**. Retail bytes establish final order, not original compiler
RTL or the necessity of an early CSE survivor. The C508 solution in
`callarg_plain_c_20261014.md` demonstrates why that distinction matters.

## Bounded source investigations

- Real index/count continuations, alternative loop forms, ordinary pointer and
  table indexing, scalar widths, and genuine pointer-lifetime changes did not
  improve the two-instruction residual.
- A cardinal-direction induction variable changed the register/instruction
  shape; duplicating the existing sound call into genuine final-iteration and
  continue paths left extra control flow and call sites in the output.
- Splitting the X delta, Y delta, Y-table base and sprite setup roles on o17's
  single-set-scale source restored retail's scale/position/color registers.
  However, loop-invariant motion hoisted the Y-table and texture addresses into
  two additional saved registers, growing the frame from 48 to 56 bytes.
  This candidate's aligned score is 29; it fails the prologue gate.
- Reusing a real address scratch for the two address calculations restored the
  frame but kept the addresses in a long-lived t0 and moved instructions to the
  top of the loop block (aligned score 13). Further measured role partitions
  and a genuine goto-form loop did not reach exactness.

The last two experiments isolate a coupled problem: making the scale single-set
changes scheduling, while separating its neighboring value roles changes
allocation and loop-invariant motion. None of these results establishes that all
plain C is impossible.

## Excluded diagnostics

The sound callee in `src/dungeon/func_8009FF80.c` forwards one masked argument to
SD_Call. Extra sound-call arguments have no independent retail evidence and are
not source proposals. The `y_typed_carrier` experiment incorrectly shifted a
table load by -2 bytes and is not a valid near-match. The allocator oracle's
attempt to force the repeatedly reused scratch into a local allocation was
rejected because it has multiple deaths; that run is not a scored result.

## Tracked continuation

### Allocation-only causal result

The downstream-difference hypothesis is confirmed for `d_fresh.c`.
Holding its C and sched1 output fixed, changing only the scale/address
allocation from v0 to unused t0 restores adjacent `li a0,1293; sll t0,s1,2`.
Its normalized listing distance barely changes (53 to 52), despite fixing
the root ordering mechanism.

An independently reviewed, nonoverlapping mapping of position to a2,
color to a3, scale/address to a1, and reused scratch to v0 recovers the
entire function assembly. A stronger control changes only the four local
pseudos **before global allocation**; GCC then chooses v0 for the global
scratch without intervention. All dumps through sched1 and local allocation
are identical between that control and the ordinary run. The scratch's
eight deaths remain unchanged; forcing it local is unnecessary.

The pinned source's byte calibration is exact, and the diagnostic output
equals its complete function assembly including directives, after internal
label-name normalization. This is a compiler diagnostic, not exact plain C.
No production source was modified. Reproducible scripts, mappings and limits:
`work/native_lane/c7f80_allocation_probe_20261014/RESULTS.md`.

### Plain-C allocation follow-up

`work/native_lane/c7f80_causal_rebuild_20261014/candidates/v_hybrid_x.c`
changes only the X-coordinate scratch into a separate `x_delta` relative to
`d_fresh.c`. It naturally produces all the desired register roles, retains
the 48-byte frame and 140-word length, and scores total 7 (1 substitution,
6 indels; the full diff is reorder-only). It has zero pins. However, the
Y-table address setup and addition move ahead of the X calculations, and
the scale still precedes the sound constant. Thus it solves allocation but
does **not** preserve the diagnostic source's corrected root ordering.
The two-score near-match remains the best valid source by total distance.

Two partial X-role splits intended to retain the scratch's real dependency
on the X calculation lose the desired allocation again (totals 28 and 30).
Initializing the address from `dirStepY` and then adding the separate scale
also remains nonexact (total 8 in the single-set and hybrid forms).
No exact plain-C proposal emerged from this bounded investigation.

### Scheduler/overlap follow-up

The exact diagnostic is now reduced to **one sched1 input**, with completely
ordinary allocation: forcing only the Y-address low instruction UID181's
birth result produces all **560 retail bytes, zero mismatches**. The source
and pre-schedule RTL are unchanged, and there is no allocator override.

The local replay reproduces 40/40 local pseudos. In ordinary `d_fresh`, the
scale/address lifetime begins at index 42, just after the Y-high temporary
dies at 40, so both take v0. An earlier scale birth creates the needed overlap
and naturally produces a1/a2/a3 for scale/position/color. The ordinary global
allocator then chooses v0 for the reused scratch. The inverse local model
finds no priority-only route under the original geometry.

The X split removes compiler output/anti dependencies into the Y-address
overwrite, explaining why its successful allocation has different scheduling.
The forced birth bit is not a C solution: the existing carrier has multiple
sets. Another genuine source graph must reproduce the overlap and order;
making that same reused carrier single set cannot simply be asserted.

New sample-width, direct-coordinate, split-arithmetic and assignment-expression
checks did not improve the source frontier. The shared X/Y index reconstruction
also hoisted the Y base during loop optimization and grew the frame. Full
measurements, rejected hypotheses and the exact scheduler control are recorded
in `work/native_lane/c7f80_shape_bridge_20261014/REPORT.md`. No exact plain C
or production edit resulted from this follow-up.

Route: **az-c-rebuild**, `C7F80-SCHED1-OVERLAP`.

The two causal handoff sources are `v_hybrid_x.c` above (natural allocation)
and the single-set source (corrected scheduling under the allocation control):
`work/native_lane/_r118/root7/work/native_lane/r118_opus_o17/c/d_fresh.c`.
The allocation discriminator above is now satisfied. The source target is
a meaningful value relationship that preserves the 48-byte frame, scale=a1,
position=a2, color=a3, and transient address calculations in v0, while producing
retail's root ordering. The single-set source is a justified rebuild starting
point even though its ordinary total score is worse. More statement permutations
or direct constant-carrier spellings do not test that hypothesis.

The full-function byte gate remains mandatory. A proposed source change must
be reviewed by the owner before production application.

## Receipts

- `work/native_lane/plain_callarg_c7f80_20261014/REPORT.md`, `lab_log.jsonl`
- `work/native_lane/plain_callarg_boundary_20261014/c7f80/COMPILER_AUDIT.md`
- `work/native_lane/plain_callarg_c7f80_fresh_20261014/EVIDENCE.md`
- `work/native_lane/plain_callarg_review_20261014/lab_log.jsonl`
- `work/native_lane/plain_callarg_review_20261014/dumps/c7f_single_scale/`
- `work/native_lane/plain_callarg_review_20261014/c7f_single_scale_prio.txt`
