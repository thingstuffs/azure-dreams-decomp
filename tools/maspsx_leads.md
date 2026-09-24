# Measured assembler fidelity leads

## `_fold_selfinc_la` on real local small data (2026-09-24)

Status: queued for the toolchain-fidelity goal; no production change authorized
by this entry. Scope: `func_80049F68`, CDK `-fno-strength-reduce`, the real
four-byte table candidate and existing experimental generic small-data correction.

The post-pass folds an absolute `la` followed by a self-incrementing cursor loop.
Genuine ASPSX 2.79 retains the full base; the transformed output is one word
shorter. Tracing names this as the only fired pass, and disabling it alone makes
the 50-word object exactly equal to genuine ASPSX. The resumed RTL-guided source repair now reproduces all 50 retail words through
genuine ASPSX 2.79; disabling this pass alone also makes the generic-corrected
assembler exact on that source. Production integration remains pending.

Evidence, complete site map and exact ablation:
`docs/evidence/gp_order_bytes.md` and its adjacent receipt directory.
Original reproducer: `work/native_lane/gp_order_bytes/diagnose.py`, then `variants.py`.
Solved-source reproducer: `work/native_lane/gp_order_bytes/guard_verify.py`.
The diagnostic selects the private generic assembler in a copied trace harness;
the production assembler is unchanged.

Updated route: the [local-data guard](../docs/evidence/selfinc_local_guard.md)
now makes the same owner exact with every pass enabled. The private package
checks existing `.sdata`/`.sbss` metadata before folding, extending the existing
small-extern guard. Its full owner link is retail-exact, all 13 checked consumer
objects/traces are unchanged, and all 70 prior small-data probes stay exact.
Prepare this generic guard with the coordinated GP transition. Consumer repairs
and eventual pass retirement remain a separate queue. Regression
risk: existing sources may rely on the folded address and changed loop offsets;
the new local-data case alone does not establish that the pass is globally
unused. Preserve the goal's existing final sign-off for shared assembler changes.

The [fresh bounded consumer check](../docs/evidence/selfinc_consumers.md) verifies
12 current direct dependents plus the historical byte-neutral fired control.
Every direct consumer still fails retail with this pass removed; all disabled
outputs match genuine ASPSX 2.79. Removing only `-mno-split-addresses` from the
three flagged 81811E* rows does not repair them. This is a concrete consumer
queue, not permission to retire the pass or a complete whole-tree fired census.

## Repeated high-only base in 81811E30 (2026-09-24)

The [scoped compiler investigation](../docs/evidence/selfinc_81811E30.md)
retains this consumer and its current recipe. Measured index/goto and structured
loop forms, plus nine raw PsyQ compiler runs, do not reproduce retail's repeated
high-only base. The loop RTL creates a full-pointer induction variable; CSE2,
combine and allocation retain it. The tracked route is address-GIV analysis in
`loop.c` and actual record-layout evidence before another source trial. This
narrows the pass's inherited compiler claim; it does not prove a compiler-wide
impossibility or justify disabling the pass.
