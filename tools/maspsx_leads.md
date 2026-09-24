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

Route: refresh this pass's full consumer census, repair dependent C/recipes,
then prepare pass retirement with genuine and complete-image gates. Regression
risk: existing sources may rely on the folded address and changed loop offsets;
the new local-data case alone does not establish that the pass is globally
unused. Preserve the goal's existing final sign-off for shared assembler changes.

The [fresh bounded consumer check](../docs/evidence/selfinc_consumers.md) verifies
12 current direct dependents plus the historical byte-neutral fired control.
Every direct consumer still fails retail with this pass removed; all disabled
outputs match genuine ASPSX 2.79. Removing only `-mno-split-addresses` from the
three flagged 81811E* rows does not repair them. This is a concrete consumer
queue, not permission to retire the pass or a complete whole-tree fired census.
