# Round 39: investigate source and compiler decisions together

The owner reopened the research objective on 2026-09-17: zero pins, with no
impossibility verdict based on search exhaustion. Baseline: 6,103 pins in 1,284
rows at `bd28d6cf`. This round implements the four complementary investigations
in [PIN_RESEARCH_WORKFLOW.md](PIN_RESEARCH_WORKFLOW.md). Results below distinguish
exact candidates from gated removals.

## Allocator exemplar: `dungeon/func_81811388`

This 56-byte wrapper advances a menu selection using the count in
`D_800294F8[lookup_index]`. Retail calls `func_80049DE8(target, input_value, count)`
and returns its result. Three same-image callers (`8181140C`, `81811508`,
`818115B8`) consume that result as `s32`; the old definition incorrectly said
`void`. The helper's definition in `src/slus/code.c` confirms its integer result.

The old source had both an input binding to `$v0` and a volatile table pointer.
Under its recorded plain GCC 2.7.2 recipe, erasing the binding gives a five-word
register mismatch. The trusted existing allocator trace identifies the exact
cause: the short-lived table-address quantity (priority 10000) gets `$v0`
before the saved input quantity (priority 2000). The input's argument-register
suggestions fail because those registers are occupied. This is an observed
allocation decision, not proof that the input needs a pin.

Rubber-duck counterfactuals separated the problems. Reusing the input, target or
index variables left the same quantity graph. Actually advancing the table
pointer changed the graph and recovered the input's `$v0`, but retained the
address in `$v1` instead of `$a2`: two retail words still differ. That is useful
intermediate evidence, even without an exact result.

The decisive experiment reconsidered the inherited volatile qualifier together
with the recipe. Ordinary nonvolatile C is exact under stock 2.7.2-cdk, 2.8.0,
2.8.1 and 2.95.2. In plain 2.7.2, combining produces a symbolic indexed-load
macro and a 13-word function. CDK instead expands the address into `high` and
`lo_sum` RTL before allocation; the ordinary load and input then receive the
retail registers, and the complete function is 14/14 words exact. Adding the
semantically required return remains exact. The final candidate is simply:

```c
s32 func_80026388(s32 input_value, s32 target, s32 lookup_index)
{
    return func_80049DE8(target, input_value, D_800294F8[lookup_index]);
}
```

The existing pinned source is also exact at CDK. Thus this correction meets the
existing `apply_candidates.py --cells` rule, not just a new acceptance shortcut.
The portability landing check passes. The data symbol remains relocatable;
no literal address, pointer narrowing, fake dependency or replacement barrier
is introduced. The declaration already describes an ordinary byte array, and
there is one load before the helper call in both versions. The table refers to
normal RAM, not hardware registers. Caller declarations already match the new
return type and unchanged argument types.

Provenance remains qualified. The wrapper itself has no discriminating retail
lineage signature. Its nearby caller `8181140C` has a two-register split-address
sequence (`lui v0; addiu a0,v0,...`), and adjacent `81811294` has a compiler-split
global store. These corroborate the split-address family in this code region;
they do not prove a particular compiler release for the wrapper. The repair
uses the stock CDK cell, with this historical uncertainty explicitly retained.

Artifacts: `work/native_lane/r39_allocator/`: `SITE_MAP.md`,
`trace_summary.json`, observations for the original and CDK pipelines,
`cell_probes.jsonl`, `return_probes.jsonl`, `pinned_cell_controls.jsonl`, and
`out/dungeon/func_81811388.c`. Full raw GDB evidence is under `raw/`, which has
an ignore file. The candidate was independently verified and landed through
`apply_candidates.py --cells`. The affected `dungeon_deep_t8_1830` window is
MATCH (27 seconds); SLUS SHA-1 is MATCH and the row database check passes.
Current count: **6,102 pins in 1,283 rows**, one pin and one pinned row removed.
See [the compact evidence record](evidence/pin_research_allocator_20260917.json).

## Delay-slot provenance: `slus/w_80041CBC`

The inherited “assembler-side invisible keep” diagnosis is incorrect at the
investigated site. GCC's raw output already differs. The empty volatile asm
prevents delay-slot reorganization from moving the following address-high
instruction into the branch slot; the pinless compiler explicitly emits that
filled slot in noreorder mode. Both maspsx and a compatible genuine ASPSX
preserve this difference. The next repair must address the source/compiler
cause, rather than teaching the assembler to insert a function-specific nop.
This investigation remains active.

The [provenance checkpoint](evidence/pin_research_assembler_20260917.md)
includes the raw directives, final RTL, genuine-tool controls and 15 exact
functions whose filled address-high delay slots must remain valid. A literal
address experiment reproduces the retail bytes but is rejected as a repair:
it would replace a relocatable data symbol with another platform binding.

## Whole-function reconstruction: `dungeon/func_8180B064`

The complete 430-word retail map supports staged vertex-pointer/scalar reuse.
A four-pointer rewrite creates an incorrect larger frame. Erasing all six pins
from the current source retains the correct frame and 430 words but scores 55.
Selectively separating vertex 3's pointer and signed-y lifetimes improves this
to 33 with the same frame and instruction count. The remaining decisions are
the order of two global allocations, vertex-1 coloring and four scheduling
indels. This is a closer experimental source, not a landed removal or proof of
the unique original C. See the
[reconstruction checkpoint](evidence/pin_research_rebuild_20260917.md).

## Implemented tools and transfer boundary

`tools/alloc_explain.py` extends the existing allocator instruments with RTL
value origins and chronological allocation explanations. It rejects untrusted
traces, handles the suggestion pass before priority ordering, and never carries
pseudo numbers between compilations. `--baseline-cfg` plus a saved `--source`
allows a repair to be replayed after its row recipe changes. Global allocation
remains an explicit handoff to the existing `alloc_trace`/`alloc_probe` APIs.

`tools/pin_research.py` validates current source/candidate hashes, evidence
artifacts, required next experiments and the review/gate requirements for
resolution. Family transfer requires distinct independent controls; a failed
search cannot be promoted into an impossibility claim. The 42 allocator tests
and 10 workflow tests pass, and the seeded three-case ledger validates.

The [first transfer cohort](evidence/pin_research_transfer_20260917.md) has no
independent exact positive. Its closest ordinary-C candidate is
`town/func_800B51B8`, two instructions from retail under 2.95.2. Keeping its
existing volatile local array preserves required stack accesses, unlike the
exemplar's unnecessary volatile table read. The next probe targets the first
load's address form and placement relative to the return-address save. Other
controls expose arithmetic coloring and changed saved-register sets instead
of the exemplar's address-generation cause.

## What changes in the next phase

Investigate coadapted source and recipe choices, not only literal macro erasure.
A volatile qualification introduced during initial matching can obscure the
natural source and make an allocator trace explain an artificial problem. Test
small, semantically reviewed families with the same address-generation cause;
require independent transfer controls before promoting a general repair.
Whole-function reconstruction and the delay-slot investigation continue in
parallel. None of their unresolved cases establishes a nonzero minimum.
