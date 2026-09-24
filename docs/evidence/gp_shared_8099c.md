# 8099C ownership and the retained compiler epilogue model

Status: **integrated; accepted compiler epilogue dependency retained**. The two adjacent functions
33D44 and 33D54 can share an ordinary `s32 D_8008099C = 0`. Their production
recipes differ; an unchanged standalone 33D44 is byte-neutral at 2.8.1, which is
33D54's current recipe. The opposite CDK trial for 33D54 failed. The group therefore uses 2.8.1 for both, preserving their source bodies.
The private experiments below preceded the production landing recorded at the end.

The [routing receipt](gp_shared_8099c/receipt.json) proves the complete 524,288-byte
image equals retail, SHA-1 `e6bfbb95ff6676899e077481221d73ddd4d3bf52`. Both
functions retain their addresses and extents: 33D44 is 16 bytes and 33D54 is
2,148 bytes. The owner contributes four zero `.sdata` bytes at `0x8008099C`,
asset 3E018 offset `0x16184`. The outside 3C0C8 object stays byte-identical and
retains its references to the word. All 17 production modules are preserved;
the private trial has 873 physical inputs and 884 logical rows.

The original private aggregator lacked the `konami_runtime` prefix and linked
in the later general-code slot. Renaming it to
`konami_runtime_gp_shared_8099c.c` makes the existing runtime wildcard place it
correctly. This is a current linker-routing requirement, not evidence of the
original translation-unit name. No production linker rule was changed.

Direct genuine ASPSX 2.79 matches 33D44's four words. For 33D54 it emits 536
words versus retail's 537: the stack restoration remains in the return delay
slot, whereas retail restores the stack before the return and leaves a nop.
This result is **not** direct genuine equality and must not be recorded as such.

The [separate attribution receipt](gp_shared_8099c/epilogue_receipt.json) applies
the existing `epilogue_model.rewrite(..., 't272')` to the fresh corrected-routing
assembly. Genuine ASPSX 2.79 then reproduces both functions, all 541 words, with
zero masks and exact retail bytes. This isolates the remaining discrepancy to
the already accepted missing-compiler epilogue model; it introduces no new
compiler hypothesis or assembler exception. See the
[model-of-record decision](fidelity_lost_compiler_case.md).

Reproduce the grouped link with
`python3 work/native_lane/gp_shared_8099c_routing/probe.py`. The trial's fresh
`genuine/a.s` is the compiler stream used in the attribution receipt. Those private receipts retain their original pre-integration snapshots.
The production continuation below supersedes their pending-integration status.
No L4/L5 placement claim is made.

## Production continuation

The unchanged standalone setter moved from 2.7.2 to 2.8.1 through
`land_recipe_move.py`, tag `gp_8099c`: rule 2 holds, its object hash is unchanged,
and the full image passes. The active module uses
`src/slus/konami_runtime_gp_shared_8099c.c`, shared declarations in
`include/slus/gp_shared_8099c.h`, and one ordinary zero-initialized signed word.
Duplicate common includes and the setter's unused accessor macros were removed.
Both function bodies and the renderer's existing pins are unchanged.

This is an inferred present ownership unit: adjacent display-cancellation setter
and renderer, a common word with matching signed declarations, and a coherent
measured recipe. It does not identify a historical source file. The outside
3C0C8 consumer remains separate, with its object bytes and external references
unchanged. The two functions stay at their retail addresses and extents.

The [production ownership receipt](gp_shared_8099c/ownership_receipt.json)
records the fresh complete retail image, exact four-byte object/linked storage,
and separate direct and modeled comparisons. The setter is direct genuine-exact
at four words. The renderer's direct genuine output is still 536 words against
537 retail words, with aligned difference three and no masked relocations.
Rewriting only that member's return through the already accepted `t272` model,
then assembling with genuine ASPSX 2.79, gives all 537 retail words exactly.
Neither member has an external-data GP dependency. Whole-module traces still
fire `_maybe_unfill_return_delay`; that trace is not attributed to the setter.

The ownership verifier now requires an explicit `--compiler-model-row` opt-in
for this separate schema-3 evidence; its default schema-2 direct-genuine checks
remain strict. The raw discrepancy is retained, the model code is fingerprinted,
and both the fresh pipeline and modeled genuine object must independently match
retail without masks. This does not relax the placement certificate or remove
compiler-model residue. Reproduce under the landing lock:

```sh
python3 tools/fidelity/prove_slus_ownership.py gp_shared_8099c \
  --compiler-model-row slus/konami_runtime_w_80033D54 \
  --output docs/evidence/gp_shared_8099c/ownership_receipt.json
```

Production now has **18 ownership units, 873 physical / 884 logical rows,
198 dependency records and 30 remaining GP rows**. Only the setter's dependency
record is removed; the renderer's combined cause becomes the retained epilogue
model. The runtime-directory pilot has a fresh direct-genuine certificate.
No production assembler rule or global default changed.

Validation of the verifier change: all 15 focused ownership tests pass, including
rejection of implicit/unselected model use, missing or unknown direct evidence,
masked comparisons, nonretail results, and incorrect modeled output. The fresh
production proof and direct runtime-pilot recertification cover the real tools
and current module build in addition to those negative tests.
