# Round 40: independent aggregate-copy transfer

Snapshot of `work/native_lane/r40_copy_transfer/candidates/REPORT.md`. Relative
experiment paths below refer to that directory. The exact candidate has since
landed through `ledger/sweeps/r40_record_copy_transfer.jsonl`.

# Whole-aggregate probes: `800B0994` and `800A23CC`

This was a bounded two-row probe at each row's recorded recipe. Both current base files first verified byte-exact against retail. No source, configuration, or build-root file was changed. Each row received four explained variants, and only an exact pin-reducing candidate was promoted to `out/`.

## `town/func_800B0994` / `func_800AE0F4`

- Recipe: `2.8.1-G0`.
- Current base SHA-256: `3bf86be542490cf9eda15fb9dbc48c09b551869ee85257aca3dc2433255aff35`.
- Base control: exact, 21/21 words.
- Base pins: one `ASM_KEEP(src)` in the copy loop.

### Retail extent and semantic boundary

Retail loads the separate state word at `D_80082A38[0x20]` and stores it to `record[0xC]`. It then copies four 16-byte groups from words `[0x32, 0x42)`, followed by the word at index `0x42`. The definite aggregate extent is therefore words `[0x32, 0x43)`: 17 words / 68 bytes, copied to `record + 0xD`. The sole visible caller, `open_shop` in `src/town/func_800B0A4C.c`, passes `shop + 0x20` from a newly allocated shop object. That destination cannot overlap the static source object, so a non-volatile C aggregate assignment has the same copy semantics.

### Variants and result

1. `func_800B0994_v1.c`: a flat `Record68 { s32 words[17]; }` assignment through direct casts. Result: 21/21 words, 13 substitutions plus 4 indels, total 17.
2. `func_800B0994_v2.c`: the same assignment through named `Record68 *src` and `*dst`, preserving the base source's initialization order. Result: the same total 17.
3. `func_800B0994_v3.c`: a record expressed as four `Words` blocks and one tail word, matching the manual loop's visible grouping. Result: the same total 17.
4. `func_800B0994_v4.c`: enclosing typed source and destination records, with the state and copied record accessed as fields rather than cast slices. Result: the same total 17.

All four aggregate spellings lower to the correct 21-instruction copy shape, but the same wrong allocation: destination/source/end are `$6/$5/$2` rather than retail's `$7/$6/$8`; the four copy temporaries shift accordingly. This is not a scheduling or copy-extent mismatch.

The causal dumps make the distinction precise. In the exact pinned manual form, the three global pointer pseudos have allocator use/live figures `11/17`, `8/21`, and `2/28`, and are assigned `$6`, `$7`, and `$8`. In the aggregate form, GCC creates pointer pseudos with use/live figures `5/12`, `6/9`, and `2/12`, and assigns destination/source/end `$6`, `$5`, and `$2`. The empty keep increased the manual source pseudo's references; aggregate lowering removes that pressure rather than recreating it. Dumps are retained under `evidence/b0994_base_dumps/` and `evidence/b0994_v1_dumps/`.

Result: informative negative, with no output candidate. Whole-record typing is semantically supported and reproduces the emitted loop, but it does not recover retail allocation at this compiler. The unresolved owner is the authentic source idiom or lifetime that gave the source and destination pointers the retail priority order; more aggregate layout spelling is not indicated by these four identical emissions.

## `town/func_800A23CC` / `func_8009FB2C`

- Recipe: `2.7.2-cdk-G0`.
- Current base SHA-256: `f1d878c504858fe9c462ab50c7e36c22a1c4d52a8c032943dbed293a4986d15c`.
- Base control: exact, 113/113 words.
- Base pins: four: `stored_entry ASM_REG("$2")`, `record_buffer ASM_REG("$17")`, `ASM_MEM_BARRIER()`, and `ASM_KEEP(entry)`.

### Retail extent and semantic boundary

Retail copies five 16-byte groups from `D_80100AF8`, followed by one word at source offset `0x50`: exactly 84 bytes / `0x54`. The destination is `0x800102F0 + record_index * 0x54`, whose stride independently confirms the extent. `D_80100AF8` is already declared as `Record84`, and `func_800422DC` fills that record before the copy. Source and destination lie in distinct fixed regions (`0x80100AF8` versus the table at `0x800102F0`), so they do not overlap. The later ten-byte detail copy deliberately overwrites destination offsets `0x34..0x3d` after the record copy and remains in the same order.

### Variants and result

1. `func_800A23CC_v1.c`: replace the manual loop, tail, and memory barrier with `*(Record84 *)copy_dst = *(Record84 *)copy_src`, retaining the other three pins. Exact, 113/113 words.
2. `func_800A23CC_v2.c`: additionally remove `ASM_KEEP(entry)` while retaining the hard register on `record_buffer`. Non-exact, 112/113 words, total distance 9. This keep is independent of the copy mechanism.
3. `func_800A23CC_v3.c`: start from variant 1 and make `record_buffer` an ordinary pointer, removing its `ASM_REG("$17")`. Exact, 113/113 words.
4. `func_800A23CC_v4.c`: remove `ASM_KEEP(entry)` from variant 3 as a combined check. Non-exact, 112/113 words, total distance 9, confirming the same independent owner.

Variant 3 is the promoted candidate. The aggregate assignment makes the source pointer's lifetime through `func_800422DC` and the copy real C dataflow; it is no longer fixed to `$17` by a register pin. GCC's aggregate expansion emits retail's five-block loop and tail, and it supplies the ordering formerly forced by the empty memory barrier. No volatile access, fake dependency, copy barrier, or otherwise unused live pointer was introduced. The two remaining pins, `stored_entry ASM_REG("$2")` and `ASM_KEEP(entry)`, are textually unchanged from the exact base and govern the later entry-store join; variants 2 and 4 explicitly showed that the keep does not transfer with this copy rewrite.

The promoted file also removes the now-unused `Copy16` typedef and `unused_value` declaration. That cleanup was rescored after promotion and remains an exact 113/113-word match.

### Output

- Exact candidate: `out/town/func_800A23CC.c`
- Base hash: `out/town/func_800A23CC.c.base_sha`
- Exact verification: `2.7.2-cdk-G0`, 113/113 words, zero substitutions and zero indels.

`town/func_800B0994`: UNRESOLVED after four aggregate forms; the 68-byte assignment reproduces the loop but changes global pointer priority and register coloring. `town/func_800A23CC`: EXACT with two pins removed; the 84-byte `Record84` assignment replaces the manual loop/barrier and makes the source register lifetime arise from ordinary dataflow.

## Independent 88-byte controls

Two additional fixed-recipe controls were investigated in
`work/native_lane/r40_copy_transfer/return_probe/`. Both original sources are
exact. The 88-byte aggregate in `town/func_8080E838` (2.95.2-G0,
`-mno-split-addresses`) retains all 87 instructions and differs in exactly 18
copy-region register operands. The same reconstruction in `town/func_8081DD70`
(2.95.2-G0, `-fno-expensive-optimizations`) has aligned total 28 and perturbs
the following record copy as well.

RTL retains the 16-byte loop and eight-byte tail as opaque BLK operations.
Aggregate destination/source/end are v1/v0/a0, with data in a1/a2/a3/t0;
retail uses a3/a2/t0 pointers and v0/v1/a0/a1 data. Named pointer staging
produces identical raw assembly. A memcpy spelling loses known alignment and
adds runtime alignment branches, unaligned copy paths, and a larger frame;
that variant was rejected before full scoring. Four full verifier calls cover
two exact baselines and two aggregate candidates. No negative candidate lands.

These controls separate two compiler questions: recovering aggregate operation
grouping can remove a copy barrier, but its address and scratch allocation need
not reproduce retail. The next useful experiment reads actual allocation order
and authentic surrounding lifetimes; it should not repeat equivalent aggregate
spelling. These bounded results do not exclude another source form or compiler
attribution. The fifth inventory candidate, `town/func_800AB37C`, has an existing
24-byte Pair split between memcpy and scalar stores and remains untested.

The independently landed 84-byte candidate was also observed with the existing
RTL tool. Its 16-byte chunks and four-byte tail persist as `mem/s:BLK` through
scheduling; the later ten-byte detail copy remains a separate operation.
Artifact: `work/native_lane/r40_copy_transfer/candidates/evidence/final_observe.json`.

## Gated outcome and lineage follow-up

The 84-byte candidate independently landed and the complete `town_scene`
window is MATCH: 335,872 bytes, 243.5 seconds. Row database OK. Final candidate
SHA-256: `78d6d82f634b6f75b0781fbc071b68ff9aa0e51ff5110a6b88d110addcd8f0de`.
Current count: **6,098 pins in 1,282 rows**, five removals from the new research
baseline. Existing SLUS SHA-1 proof remains current; this changes only TOWN C.

A four-verifier follow-up tested the unchanged `8080E838` aggregate and pinned
base under stock 2.7.2-G0 and 2.7.2-cdk-G0. Both older aggregate compiles recover
the exact retail copy register partition. Plain 2.7.2 differs in only two words:
loop-end calculation uses a2 instead of its equal saved source s1, and an
unrelated address add reverses equivalent operands. CDK has the same loop-end
choice plus a final-call argument/delay-slot ordering difference (aligned total
5). The pinned manual controls score 30 and 29 respectively.

This is a source-model and compiler-family interaction, not evidence that
aggregate assignment inherently cannot reproduce the 88-byte copy. It also
means the current pinned-source-exact recipe-switch control does not pass.
The next phase must investigate actual source lifetimes and lineage evidence;
it must not silently treat a close alternative compiler as established history
or bypass the recipe review. All four receipts and full diff maps are in
`work/native_lane/r40_copy_transfer/return_probe/maps/lineage_272_runs.json`
and its named verifier files. No candidate from this follow-up landed.
