# 8099C ownership and the retained compiler epilogue model

Status: **private full-image proof; not integrated**. The two adjacent functions
33D44 and 33D54 can share an ordinary `s32 D_8008099C = 0`. Their production
recipes differ; an unchanged standalone 33D44 is byte-neutral at 2.8.1, which is
33D54's current recipe. The opposite CDK trial for 33D54 failed. The successful
private group therefore uses 2.8.1 for both, preserving their source bodies.

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
`genuine/a.s` is the compiler stream used in the attribution receipt. Production
sources, recipes, module configuration and dependency records remain unchanged.
Integration must retain the epilogue residue explicitly, land the standalone
recipe through the existing gate, and verify the new ownership in production;
the current direct-genuine ownership helper cannot certify this mixed result.
No L4/L5 placement claim is made.
