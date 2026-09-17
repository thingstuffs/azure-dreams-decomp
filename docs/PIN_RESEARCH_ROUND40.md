# Round 40: recover the record copy and its diagnostic interface

This investigation follows the owner's rubber-duck suggestion. The target is
`town/func_80878974`, a 224-byte function with two pins. The old C manually
copies three 16-byte blocks and one final word, keeps the destination alive with
`ASM_USE`, and binds an unsigned zero value to register zero for a diagnostic
line number. Erasing pins while retaining that source model had not matched.

## Reconstruct the operation before tuning its instructions

The embedded strings are `%s = %d\n`, `p->kind`, `ov_work.kind`,
`mark: %s line %d\n`, and `sn_main.c`. They identify a record copy followed by
three diagnostic calls. The first two print the input and copied record's kind
at offset 8; the third prints file and line 47. Each format takes two variadic
arguments. The inherited first-call declaration manufactured a fourth argument
from the finished copy pointer. The final source uses one consistent variadic
callback declaration and the actual three arguments for each call.

The copy becomes a single 52-byte aggregate assignment. GCC 2.7.2 expands it
into a 16-byte block-move loop and a four-byte block-move tail. RTL confirms
both remain `mem:BLK` parallel operations through scheduling and allocation;
the tail load/store is emitted together, so the assembler supplies the required
load-delay nop without a source asm barrier. This is a compiler-observed cause,
not merely a better score. The generated four-register block-move clobbers are
normal compiler RTL, not source bindings.

The final source keeps the existing relocatable destination expression
`D_807030AC - 12`, removes the unused block locals and the inherited volatile
callback-table qualifier, and names the known `kind` field. Directly declaring
a new aggregate at `D_807030A0` instead produces 55 words: GCC folds the low
address into stores and omits the initial address completion. That bounded
counterfactual explains why symbol/object identity matters. It does not prove
that another declaration model cannot work. Other field meanings remain unknown.

## Correct the assembler convention separately

Retail word 50 is `ori a2,zero,47`. This row lies in the already demonstrated
old-ASPSX constant-materialization island between `80878924` and `80878A78`.
The existing t45 rewrite missed its `u32` carrier because it recognized only
`s32`. Removing only this carrier is exact with `--aspsx-version=2.40`; default
2.56 differs only at word 50. The original two-pin source is exact with either
convention. This supports the pre-2.50 `li` expansion family, not a unique
historical assembler release. No function-specific assembler patch is added.

`tools/orzero_aspsx.py` now handles signed and unsigned 32-bit carriers,
preserves port/dead arms during scored-only rewriting, and checks all uses
before deleting conditional declarations. Twelve focused tests include unsafe
non-OR uses and mismatched fallback types. A registry-selected inventory found
only this remaining unsigned OR-zero candidate; that narrow fix alone is not
a new large removal population.

## Verification and remaining work

The final zero-pin candidate independently matches all 56 unmasked linked
retail words through both the direct comparator and production verifier.
The original source also passes the production verifier with the new assembler
convention. Source hash: `a2f43febd8306933d2a0648013a17fb94b078c5442df816f5c04e5de35ab0db6`.
Retail hash: `66834386175298a800d09426671d4866c3c2a38534cc8c78f0650576f4dd13f8`.
The semantic review approves the recovered copy/logger behavior and unchanged
external ABI; it records inherited overlapping-global/interior-label portability
debt explicitly. The candidate landed through `apply_candidates.py`; the full
564-byte `town_deep_t8b_7f8974` window is MATCH, SLUS SHA-1 is MATCH, and the
row database passes. Two pins and one pinned row are removed: **6,100 pins in
1,282 rows**, three removals from this research objective's 6,103-pin baseline.
See the [compact proof](evidence/pin_research_record_copy_20260917.json) and
[semantic review](evidence/pin_research_record_copy_review_20260917.md).

Working receipts: `work/native_lane/r40_callback/`, including `retail.txt`,
`aspsx_controls.jsonl`, `aggregate_results.jsonl`, the final source and strict
verifier JSON, and `aggregate_final_observe.json`. Two early diagnostic files
are explicitly named `invalid_*`: they used an incorrect symbol-injection
module. Their scores are excluded. All accepted controls resolve the named
symbols and use the TOWN container with the retail hash above.

Next phase: test complete aggregate assignments on a small independently
reviewed cohort of manual-copy functions with copy-end pins. Require known
copy extent and real object/callback contracts before any rewrite. Keep the
430-word allocator case and GCC delay-slot case open with their newly narrowed
questions; neither failed source probes nor this individual success establish
a general solution or an unavoidable minimum.
