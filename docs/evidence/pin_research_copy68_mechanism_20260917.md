Working paths in this review snapshot refer to `work/native_lane/r42_copy68/`.

# Record68 retail roles and compiler ownership

Baseline source at recorded 2.8.1-G0 is independently exact: 21 words, no frame,
no calls or saved registers. Full source-equivalent retail assembly is retained
in round 40's `b0994_base.s`; the new CDK assembly independently matches it.

Words 0..6 prepare destination a3 = record + 52, materialize D_80082A38 in v0,
source a2 = base + 200, load the state word v1 = base[32], end t0 = base + 264,
and store state at record + 48. Words 7..17 load v0/v1/a0/a1 from source offsets
0/4/8/12, store those words, advance both pointers by 16, and loop until source
reaches end. Words 18..20 copy the one-word tail across the return delay slot.
The fixed extent is four 16-byte blocks plus four bytes: 68 bytes. The scalar
state copy is separate and precedes the aggregate operation.

No special store signature attributes a unique compiler release: the fingerprint
reports insufficient evidence. The 2.7 block-copy family is a hypothesis supported
by the previously recovered initializer register partition, not by config ranking.
Plain 2.7.2 recovers all loop registers but uses a separate symbolic scalar load,
yielding 22 words; CDK keeps that load relative to the already materialized base
and yields 21 exact words. The pinned source is also exact at CDK, satisfying the
normal cell-switch rule.

## Allocation evidence

`raw/cdk_dumps/aggregate.c.lreg` and the retained round-40 2.8.1 lreg dump show
identical pointer pseudo lifetimes: destination 84 has refs 5/live 12, source 85
has refs 6/live 9, end 86 has refs 2/live 12. Both prioritize 85, 84, 86 for
global allocation.

Yet CDK local allocation has already assigned each block-move scratch to
v0/v1/a0/a1. All three global pointers conflict with those registers; source,
destination and end consequently become a2/a3/t0. In 2.8.1 the four scratch
operands remain SCRATCH through lreg; global pointers take a1/a2/v0 and reload
later chooses a3/t0/t1/t2 for the scratch registers. Pointer reference counts
alone cannot explain this family difference: scratch allocation happens at a
different stage. No invented extra use is needed at CDK.

A subsequent trusted 2.8.1 debugger run ruled out both memory-constraint
rejection and scratch-list exhaustion: both operands pass, the selected
alternative succeeds, and all eight loop/tail scratch quantities are created.
The source difference is how successful local assignments are recorded. CDK
mutates instruction scratch nodes in place; 2.8.1 adds replacement registers to
an allocator side table while leaving the instruction's scratch nodes for the
later path. See [the causal trace](pin_research_copy68_causal_20260917.md).
No compiler or assembler patch is proposed.
