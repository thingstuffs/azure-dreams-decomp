Working paths in this review snapshot refer to `work/native_lane/r41_pair/`.

# `town/func_800AB37C` 24-byte Pair reconstruction

This bounded continuation tested six C reconstructions at the registered `2.7.2` recipe. It changed no production source, configuration, or build root. Every probe removed all seven `ASM_*` sites and used only real copy/call dataflow. The current source was first verified exact.

## Provenance and retail map

- Row: `town/func_800AB37C`; true name `func_800A8ADC`.
- Current base SHA-256: `8a20ccbd54212b560f465add7c004a2f82b66d3b458b009ee8c923ca566ad5e6`.
- Base control: exact, 47/47 words at `2.7.2`.
- Base pins: seven (`second_y ASM_REG("$4")`, three keeps, one scheduling barrier, and two use sites).
- Saved normalized retail map: `evidence/base_screen.s`.

Retail reserves a 72-byte frame and copies six consecutive words from address `0x80089128` to stack offsets `16..36`: two adjacent three-word vectors, exactly 24 bytes and exactly one `Pair`. The copy is followed by a three-word position copy to stack offsets `40..48`, with `0x100000` added to its z coordinate. The local `Pair` is then passed to `func_800A895C` and `func_80097AD0`, so the local aggregate is genuine live data rather than an allocation device.

The retail copy uses a two-stage address:

1. `$v0 = 0x80090000` before the `$ra` save.
2. `$a2 = $v0 - 0x6ed8` after that save.
3. `$v1/$a0/$a1` load the two vectors through `$a2` and store them to the local `Pair`.

From instruction 18 onward, the clean whole-aggregate probe reproduces every retail instruction. The remaining problem is therefore confined to address construction and allocation for the 24-byte source.

## Callee contract and semantic correction

The actual implementation at `src/slus/konami_runtime_w_800374F4.c` is:

```c
u32 func_800374F4(s32 limit)
```

It consumes only the limit. The base's first call `func_800374F4(2, second_z, pair_source)` therefore carries two decompiler-added phantom arguments. Retail happens to leave the last copied word in `$a1` and the source address in `$a2` at the call, but the callee does not read either register. All six probes use the real one-argument contract. They retain the same two later calls, the same raised-position values, and the same 24 bytes passed in the local `Pair`.

## Six source probes

1. `scratch/func_800AB37C_v1.c`: direct whole assignment `pair = D_80089128`. Result: 47/47 words, 13 substitutions plus 2 indels, global total 15. It matches retail exactly at instructions 18 through 46. GCC expands the 24-byte assignment correctly but uses one direct-symbol source pseudo in `$a1`; retail uses page `$v0` plus source `$a2`.
2. `scratch/func_800AB37C_v2.c`: whole assignment through a literal `0x80090000` page and derived pointer. Result: total 15. Constant folding turns the address into `lui 0x8008; ori 0x9128`, so it loses retail's split page/negative-offset form.
3. `scratch/func_800AB37C_v3.c`: two named `Vec3` field assignments through a `Pair *`. Result: 47/47 words, total 19. GCC rematerializes the source address for the second vector, adding instructions absent from retail.
4. `scratch/func_800AB37C_v4.c`: one 24-byte `memcpy` with the corrected one-argument random call. Result: total 15 and the same allocation as probe 1. This confirms aggregate-assignment versus builtin-copy spelling is not the owner.
5. `scratch/func_800AB37C_v5.c`: two staged `Vec3` assignments through an advancing source pointer. Result: 47/47 words, 6 substitutions plus 2 indels, total 8. It recovers retail's copy-value registers and all six stores. It still forms the source entirely in `$v0` and schedules the low-half addition before the `$ra` save; retail has a distinct derived `$a2`. This was the closest diagnostic, not a promotion candidate.
6. `scratch/func_800AB37C_v6.c`: whole assignment through a typed enclosing town-data record whose `Pair` is at offset `0x9128`. Result: total 15. GCC folds the field access to the same direct symbol form as probe 1, refuting enclosing-layout spelling as a way to preserve the two address pseudos.

A qualified `2.7.2-cdk` compiler control on probe 5 is worse: 47/47 words, total 13, with an additional split/rematerialized source and shifted schedule. There is no evidence for recipe reattribution.

## Causal RTL

The retained dumps are under `evidence/rtl_base/`, `evidence/rtl_v1/`, and `evidence/rtl_v5/`.

The exact pinned base has page pseudo 74 (five uses across eight instructions) assigned `$v0`, then a distinct derived source pseudo 75 (eight uses across ten instructions) assigned `$a2`. The clean whole-Pair form reaches RTL as one `mem:BLK(symbol_ref D_80089128)`; aggregate expansion consequently owns a single source address and colors it `$a1`. Probe 5 materializes one explicit source pseudo 74 (five uses across three instructions) and colors it `$v0`; its two `movstrsi_internal` operations use that same pseudo. Thus the closest clean sources do not present the allocator with retail's two-pseudo page/source graph.

The base obtains that graph from `data_page`, `pair_source`, and empty-asm constraints. None of the six ordinary-C forms supplies a genuine second lifetime for the page value: constant and field forms fold, while separate vector accesses either share one source or rematerialize it. Adding a dummy later use would manufacture the missing graph and was deliberately excluded.

## Result

UNRESOLVED; no file was placed in `out/`. The aggregate-copy mechanism removes the scalar copy temporaries and phantom callee arguments while preserving the entire suffix, but ordinary source tried here does not reproduce the retail page-base/source split. This is a bounded allocator/address-lifetime negative, not evidence that exact C is impossible. A next investigation should identify a real surrounding data-page owner or declaration shared with another access, rather than add another copy spelling or a liveness-only use.
