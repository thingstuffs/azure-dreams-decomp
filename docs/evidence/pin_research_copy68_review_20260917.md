Working paths in this review snapshot refer to `work/native_lane/r42_copy68/`.

# Independent review: `town/func_800B0994` / `func_800AE0F4`

## Decision

Approve `aggregate.c` as a one-pin removal paired with stock
`2.7.2-cdk-G0`.  The aggregate assignment is a more faithful representation
of a complete 68-byte record field than the current manual loop, and the sole
recovered caller proves that source and destination cannot overlap.  A direct
linked-strict comparison independently reproduces all 21 retail words.

This is a source-and-cell repair.  The current pinned source is exact under
both its recorded `2.8.1-G0` cell and the proposed CDK cell, so the ordinary
cell-change landing route has a safe baseline control.  The natural aggregate
source distinguishes the tested cells: it is exact only at CDK in the bounded
stock cohort.  That supports CDK as the best recovered recipe, but it is not
standalone historical proof that the original object was compiled by this
precise compiler release.

The candidate has no `ASM_*` sites.  `tools/pin_census.py` reports one live
site in the baseline (`ASM_KEEP(src)` at line 41), none in the candidate, and
`landing_refusal(...) == None`.

## Independent exact receipt

The independent run invoked `work/g3/overlay_func_compare.py` directly with
the exact row identity (`foff 0x30994`, size 84), true-base-aware linking, and
`--summary-json`.  It did not use a relocation-masked comparison.

| Item | SHA-256 |
|---|---|
| Current/baseline source, `base.c` | `3bf86be542490cf9eda15fb9dbc48c09b551869ee85257aca3dc2433255aff35` |
| Candidate, `aggregate.c` | `feb688e460fab8599bb9779a498ab5c6670a2bb0d97cefdfcd291c1e3223074f` |
| Retail 84-byte slice | `87bd937eb90c188eed7733752bcdc49e1b57ddb62f9928e3a15d5e2003557c60` |
| CDK compiler executable | `7a571911a97cef0c6b7b5d4174e89ac54f9806ce3d4b233c0f8620e3503c672b` |
| Comparator | `54b4b6488120f2e418f3083080b814a52f7e64be57ef5b07b3fd341343af83ce` |
| Candidate receipt file | `90fa8d1578cdba85761cd1e38613936a0a9af1fc603d9ee1e9fabc8eb95c6c75` |
| CDK baseline-control receipt file | `60dae391061cf5bb4500ea0dfd8400d3e67527d0bab648bf7aa93a145e46eb09` |
| Recorded-cell baseline receipt file | `e1b8db0a90fd89b3d04930bc25b20bea823fc14e2c0d955d08aa755a11153a7b` |

Candidate result:

- comparison mode: `linked-strict`
- rowbase link address: `0x800AE0F4` (`xfer_town_B000`, delta `0x8007D760`)
- generated/target: 21/21 words, 84/84 bytes
- substitutions: 0
- indels: 0
- positional words off: 0
- relocation suspicion: false

Receipts:

- `independent_aggregate_2.7.2-cdk-G0_verify.json`
- `independent_base_2.7.2-cdk-G0_verify.json`
- `independent_base_2_8_1_G0_verify.json`

## Complete retail map

The retail slice is retained as `retail.bin`; `retail_disasm.txt` is an
objdump view adjusted to the proven runtime address.

| word | address | instruction | role |
|---:|---:|---|---|
| 0 | `0x800AE0F4` | `addiu a3,a0,52` | Destination = `record + 0x34`, or word `0xD`. |
| 1 | `0x800AE0F8` | `lui v0,0x8008` | Begin materializing `D_80082A38`. |
| 2 | `0x800AE0FC` | `addiu v0,v0,0x2A38` | `v0 = D_80082A38`. |
| 3 | `0x800AE100` | `addiu a2,v0,200` | Source = global offset `0xC8`, word `0x32`. |
| 4 | `0x800AE104` | `lw v1,128(v0)` | Load the separate scalar at global word `0x20`. |
| 5 | `0x800AE108` | `addiu t0,v0,264` | Loop end = global offset `0x108`, word `0x42`. |
| 6 | `0x800AE10C` | `sw v1,48(a0)` | Store scalar to `record[0xC]`. |
| 7 | `0x800AE110` | `lw v0,0(a2)` | Load chunk word 0. |
| 8 | `0x800AE114` | `lw v1,4(a2)` | Load chunk word 1. |
| 9 | `0x800AE118` | `lw a0,8(a2)` | Load chunk word 2. |
| 10 | `0x800AE11C` | `lw a1,12(a2)` | Load chunk word 3. |
| 11 | `0x800AE120` | `sw v0,0(a3)` | Store chunk word 0. |
| 12 | `0x800AE124` | `sw v1,4(a3)` | Store chunk word 1. |
| 13 | `0x800AE128` | `sw a0,8(a3)` | Store chunk word 2. |
| 14 | `0x800AE12C` | `sw a1,12(a3)` | Store chunk word 3. |
| 15 | `0x800AE130` | `addiu a2,a2,16` | Advance the source one four-word chunk. |
| 16 | `0x800AE134` | `bne a2,t0,0x800AE110` | Repeat until four chunks / 64 bytes are copied. |
| 17 | `0x800AE138` | `addiu a3,a3,16` | Delay slot: advance destination. |
| 18 | `0x800AE13C` | `lw v0,0(a2)` | Load the seventeenth word at global offset `0x108`. |
| 19 | `0x800AE140` | `jr ra` | Return. |
| 20 | `0x800AE144` | `sw v0,0(a3)` | Delay slot: store the seventeenth word. |

The loop copies global words `[0x32, 0x42)`, four 16-byte iterations.  The
tail copies word `0x42`, so the complete source interval is
`[0x32, 0x43)`: 17 words / 68 bytes.  The destination is record words
`[0xD, 0x1E)`.  The separate scalar at source word `0x20` is stored to
destination word `0xC` immediately before that block.

The tail is identical in plain 2.7.2 and CDK.  It is not the owner of the
plain-2.7.2 length difference.

## Aggregate semantics and layout evidence

The aggregate boundary has evidence outside this candidate.  The immediately
following `func_800AE148` models the global as a `TownState` whose last field
is a 17-word `CopyBlock` at offset `0xC8`.  It assigns that entire field from
another `CopyBlock`.  The generated record census gives `D_80082A38` a span of
exactly `0x10C` bytes.  The reviewed copy starts at `+0xC8` and ends at
`+0x10C`, exactly the last field and the end of the known global record.

`Record68 { s32 words[17]; }` contains no padding on the target ABI.  Its
assignment therefore copies every byte in the retail interval and no adjacent
state.  The candidate preserves the scalar-before-block order and does not
introduce volatile reads, a barrier, an artificial dependency, or a live
unused cursor.  GCC lowers the assignment to retail's four 16-byte `BLK`
iterations and four-byte tail.

The generic `Record68` name is admissible locally.  A future shared layout
cleanup could reuse the neighboring `CopyBlock`/`TownState` definitions and
give the corresponding destination field a real name; that is type cleanup,
not a condition for this behavior repair.

## Caller and destination audit

The sole recovered caller is `open_shop` (`src/town/func_800B0A4C.c`, runtime
`0x800AE1AC`).  It:

1. obtains `shop` from `func_8003FC64(0)`;
2. sets `shop_state = shop + 0x20`;
3. passes `shop_state` to `func_800AE0F4`.

The resident allocator's recovered definition shows that this allocation is
a `0x124`-byte node.  Relative to the node, the reviewed function writes:

- scalar: `shop + 0x50`;
- aggregate: `[shop + 0x54, shop + 0x98)`.

The entire destination is therefore inside the allocated node.  The source is
the static interval `[D_80082A38 + 0xC8, D_80082A38 + 0x10C)`, so it cannot
overlap the fresh heap/freelist node.  This makes ordinary C aggregate
assignment equivalent to retail's forward loop.  Both source and destination
are four-byte aligned, matching retail's `lw`/`sw` precondition.

The caller currently has an old-style `M2C_UNK func_800AE0F4()` declaration,
but it passes exactly one pointer and ignores the result.  The candidate keeps
the target ABI and the established `void` definition.  Retail incidentally
returns with the final copied word still in `v0`; neither the current source
nor the caller treats that register residue as a return contract.

On the caller's resource-failure path, `shop` is set to null after cleanup but
the saved `shop_state` pointer is still passed to this routine.  The candidate
does not change that existing ordering or lifetime assumption.

## Compiler-cell evidence

The same candidate was scored under a bounded stock lineage cohort:

| cell | words | aligned result |
|---|---:|---:|
| `2.6.3-G0` | 22/21 | total 2: 1 substitution, 1 indel |
| `2.7.2-G0` | 22/21 | total 2: 1 substitution, 1 indel |
| `2.7.2-cdk-G0` | 21/21 | **exact** |
| `2.8.0-G0` | 21/21 | total 17: 13 substitutions, 4 indels |
| `2.8.1-G0` | 21/21 | total 17: 13 substitutions, 4 indels |
| `2.95.2-G0` | 21/21 | total 13: 13 substitutions |

CDK represents the global address as `high` plus `lo_sum` RTL, retains the
materialized base in `v0`, and emits `lw v1,128(v0)`.  Plain 2.7.2 starts from
a symbol reference, then schedules the scalar as a separate constant-symbol
load `lw v1,D_80082A38+128`; ASPSX expands that macro through another address
materialization, producing the extra word.  The subsequent loop and tail are
the same.

CDK also assigns aggregate destination/source/end to `a3/a2/t0` and the four
copy values to `v0/v1/a0/a1`, exactly retail's partition.  The 2.8.x cells
retain the 21-word broad shape but color the copy differently, which accounts
for their larger aligned distance.

The current pinned manual source independently matches both `2.8.1-G0` and
`2.7.2-cdk-G0`.  That is an important negative control: the old source cannot
identify the compiler.  The candidate's natural aggregate boundary, the CDK
exact result, and the CDK recipes already recorded for the immediately
following initializer and caller form positive but reconstruction-dependent
lineage evidence.  Nearby rows still carry mixed cells, so this review does
not claim a uniform compiler for the whole address run.

The recommended recipe is an unmodified stock compiler with only `-G0`; no
new optimization flag or patched toolchain behavior is involved.

## Portability boundary

The target semantics are sound, with two ordinary decomp portability debts:

1. Casting the `s32 *` source and destination slices to `Record68 *` relies on
   their established four-byte alignment and object extent.  Those conditions
   are proven above.  A modern strict-aliasing host build would be better served
   by shared typed fields or a `memcpy` boundary.
2. The record uses fixed-width scalar words and contains no pointers, so it
   remains 68 bytes on LP64 hosts.  This candidate does not introduce the
   pointer-width problems seen in target structs containing native pointers.

These limitations do not justify retaining `ASM_KEEP(src)`: the keep has no
runtime meaning, and the aggregate form expresses the actual record operation
while reproducing retail exactly at the supported stock cell.
