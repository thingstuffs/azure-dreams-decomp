# AF3 pair: declaration repair and private full-image proof

Status: **prepared, not integrated**. Both adjacent state-transition functions
now have a coherent default CDK recipe and actual AF3/AFC storage in a private
module. All **153 words** match genuine ASPSX 2.79 and retail without masks,
and the complete private SLUS image equals retail. This removes the previously
unresolved source/recipe obstacle; production integration still depends on the
coordinated generic assembler correction.

## Why the earlier recipe trials failed

The [earlier trials](gp_af3_recipe.md) used unchanged 4450C declarations:
12-byte external structs at 81480 and 8148C, explicitly padded past the small-data
threshold, plus an asm alias for a repeated 8148C read. At default CDK those
large declarations force compiler address expansion with allocated scratch
registers. Retail's store instead uses the assembler's `$at` macro expansion.
Switching both functions to `-mmips-as` preserves the old 4450C stock result but
breaks 4437C's held table-base accesses; explicit pointer locals did not change
that output. Those negative receipts remain valid for their original inputs.

The fix is the declaration model in 4450C. Its actual accesses only read or write
the leading 32-bit word. Using plain `extern s32` declarations for 81480/8148C
allows default CDK to emit the store macro; genuine ASPSX correctly expands
external symbols absolutely. Removing the redundant asm alias also reproduces
the later fresh load after calls. No 4437C body rewrite or dialect flag is needed.
The [scalar control](gp_af3_declarations/scalar_receipt.json) yields 53 exact
words with genuine/private generic assembly, while the stock external-GP model
emits 51 wrong words. Its aligned distance eight uses `SequenceMatcher`, not
an optimal-LCS claim. This is a measured reachable recipe, not unique historical
compiler attribution.

## Declaration and storage evidence

The [complete 53-word map](gp_af3_declarations/retail_4450c_53.dis) shows reads of
8148C at `80044560`–`80044564` and `80044584`–`80044588`, and an `$at`-based store
to 81480 at `80044568`–`8004456c`. No access here needs either padded extent.
A scoped source audit found other scalar/pointer views at both addresses, a
separately accessed byte at 81485, and separate words at 81490/81494. Existing
neighbor casts and three-word rebuild types do not prove original object extents.
The new declarations are four-byte access views; this module does **not** own
81480/8148C or claim their complete historical types. Detailed audit:
`work/native_lane/gp_af3_8148c_audit/REPORT.md`.

The pair defines `s8 D_80080AF3 = -1` and a private `static s16 D_80080AFC` in
4437C. AF3 is the shared state index. AFC is the halfword selector used by 4437C;
the [separate AFE cache](gp_cache_afe.md) has already landed independently.
Their actual retail bytes are `ff` and `0000`, at offsets `0xb3` and `0xbc` of
`assets/54240.bin`. They occupy separate `.sdata` and `.sbss` sections. No padding,
duplicate tentative definitions, new pins or source-specific assembler rule is
part of the proposed repair. Possible indexed access through AF0 remains subject
to the bounds limitation documented in the cache audit; retail addresses/bytes
are preserved. The adjacent pair is an inferred present ownership unit, not a
recovered historical file or an L4/L5 placement claim.

## Full-link proof and remaining integration

The [full-link receipt](gp_af3_declarations/private_link_receipt.json) starts from
the 19 active production modules and preserves all of them. The private build
has 20 modules, 872 physical inputs and the same 884 logical IDs. Its only logical
recipe difference is 4450C from plain 2.7.2 to default CDK. The pair owns exactly
one initialized byte and two zero bytes, linked non-absolutely at `80080AF3` and
`80080AFC`; AFC is local. Their obsolete absolute assignments are filtered by
existing tooling. Fresh generic and genuine objects use the actual linked symbol
map and match all 100 + 53 retail words, with zero masked references.

The complete 524288-byte image has retail SHA-256
`ae19d8d4bdd2db9a933b1e44d70dd61be670781e441d7cb37da85250a7aed31f`.
The comparison also found all 903 pre-existing source object files unchanged;
that number includes inactive cached objects, not 903 active compilation units.
The temporary manifest evidence/header fields reflect the private experiment.

This measurement selects the generic assembler only for the pair in an isolated
wrapper. That is diagnostic containment and **must not become a production
exception**. The assembler is the all-passes-enabled candidate from
[the local-data guard proof](selfinc_local_guard.md), package hash
`28e45bbcf00fc90dc0645250f233b73f96ad11d06a2f8230ce533fc2fafbbfbe`.
Prepared [4437C](gp_af3_declarations/w_8004437C.c),
[4450C](gp_af3_declarations/w_8004450C.c) and
[aggregator](gp_af3_declarations/w_8004437C_pair.c) are retained with receipts.
Reproduce with `python3 work/native_lane/gp_af3_pair_link/probe.py`;
[script hashes](gp_af3_declarations/reproducers.json) identify this run.

Next integrate this candidate into the combined private rehearsal, repair the
remaining 20-row component, then rerun global correction and dependency gates
before the required final assembler sign-off. No production source, recipe,
assembler default or dependency record changes follow from this private proof.
Production remains 197 total dependencies, 29 GP rows and 19 ownership units.
