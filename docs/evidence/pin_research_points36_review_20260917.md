Publication update: the accepted candidate has landed and passed all affected
windows and SLUS; see [the round-43 receipt](pin_research_round43_20260917.json).
The review below records its pre-publication state.

Working paths in this review snapshot refer to `work/native_lane/r43_points36`.

# `dungeon/func_819C0000` clean aggregate-copy review

## Decision

`aggregate_clean.c` is an admissible exact candidate for the copy cleanup. It replaces the hand-written, pinned 36-byte copy with an ordinary `LocalPoints` aggregate assignment, removes all eight pins that existed only to reproduce that copy, preserves the pre-existing `NON_MATCHING` arm's assignment text, and changes neither the function API nor the later state-machine logic.

Candidate SHA-256: `24fe10483994f2a6d2efae72cb66923dd4af581e8250809d6347bd87f45284d7`.

The two earlier scratch prototypes, `aggregate_direct.c` and `aggregate.c`, are not candidates: they retain the old pinned copy under a newly introduced conditional. Only `aggregate_clean.c` has the clean source shape reviewed here.

## Inputs and provenance

- Ledger row: `dungeon/func_819C0000`, runtime entry `func_80025800`, file offset `0x19E0000`, 1,256 bytes / 314 words.
- Recorded stock recipe: `2.7.2-cdk-G0 -fno-expensive-optimizations`; assembler flags `--fill-shadowed-return-delay`.
- Checked-in source captured as `base.c`: SHA-256 `faf687e357bd74feecece863f0b65331af2718e610bdcd54480f16c15dca8134`.
- Retail slice `retail.bin`: SHA-256 `4d0c0e0373e9bc87a1e7f8131aec2bd229e908b5173ae83b6961c3eb6f2f6b46`.
- The row links at the proven runtime base `0x80025800` in `img_19deb98_80024398` (delta `0x7E645800`), rather than at its synthetic overlay name.

The unchanged baseline was first compiled and compared linked-strict: exact 314/314 words, 1,256/1,256 bytes, zero substitutions and zero indels. Receipt: `base_verify.json`, SHA-256 `a8728f5f91cd00475298bcb7c44404822c254ade73dd0cc979339dbe1f3a711d`.

## Candidate and exactness

The replacement is:

```c
LocalPoints offsets;
u8 *copy_src;

#ifdef NON_MATCHING
    copy_src = (u8 *)&D_80024004;
#else
    copy_src = (u8 *)&D_80024004;
#endif
offsets = *(LocalPoints *)copy_src;
```

The original `NON_MATCHING` assignment is retained verbatim. The matching arm now names the ordinary symbol rather than constructing `0x80020000 + 0x4004`. The manual copy loop, copy-only temporaries, literal-page construction, and its register/keep/scheduling directives are removed from both arms.

Direct linked-strict verification is exact 314/314 words and 1,256/1,256 bytes, with zero substitutions, zero indels, zero positional differences, and no relocation suspicion. Receipt: `aggregate_clean_verify.json`, SHA-256 `caa6cabef010865bbfa6b677680c73f2e60638b10b669af9ebc77a2f454ad1fb`. Compiler assembly is `aggregate_clean.s` (SHA-256 `049a65d6b1db7738b56ba55e9579ff42e5e0825895d1c3dc4ae0d244232560d7`); translated assembly is `aggregate_clean.maspsx.s` (SHA-256 `5608fe9823a7ebb981e4cd65286b130c31eebaa819e3c747d6afd2fbdf81a37e`). The compiler binary SHA is `7a571911a97cef0c6b7b5d4174e89ac54f9806ce3d4b233c0f8620e3503c672b` and comparator SHA is `54b4b6488120f2e418f3083080b814a52f7e64be57ef5b07b3fd341343af83ce`.

Pin census changes from 11 live sites to 3. The removed copy-only sites are three `ASM_REG`s (`copy_src/$6`, `source_page/$2`, `copy_dst/$7`), two `ASM_KEEP_NV`s, and three `ASM_SCHED_BARRIER`s. The three remaining sites belong to later coordinate-loop allocation (`biased_x`, `tile_x`, and `point`) and are outside this bounded change. Independent cascade testing found no additional removable pin. `landing_refusal` returns `None`; the unscored-text comparison is equal (both hashes `de26f7c533f228f20fb2de24fc13bca8f27002ac08c44e7b673fa0381ff4144e`).

## Why the ordinary assignment emits the retail copy

`LocalPoint` is two `u16` fields, so it is 4 bytes with 2-byte alignment. `LocalPoints` contains exactly nine `LocalPoint`s and is therefore 36 bytes. The destination is the local `offsets` object at `sp+0x18`; the source is the separately declared global `LocalPoints D_80024004`, so the ranges cannot overlap.

At this CDK compiler and recipe, the aggregate assignment lowers to the retail block-copy form. It puts the destination in `$a3`, forms `D_80024004` in `$a2` with a split `lui`/`addiu`, and tests `$a2 & 3`. The unaligned branch performs two 16-byte `lwl/lwr` plus `swl/swr` iterations; the aligned branch performs two 16-byte `lw`/`sw` iterations; both share a final 4-byte unaligned load/store. This is the complete 32+4-byte retail site. The compiler also naturally reproduces the prologue-save interleaving and all downstream instructions. Thus the removed source was a manual transcription of the compiler's normal aggregate-copy expansion.

The dynamic alignment test is meaningful even though this instance's linked address `0x80024004` is 4-byte aligned: the declaration only promises `LocalPoints`' 2-byte alignment. The aggregate keeps that true type and does not falsely raise its alignment.

## Semantics and port review

The old code copied precisely bytes `[0, 36)` from `D_80024004` to the stack object before any call. The new aggregate assignment copies the same complete object at the same point. There is no padding in the nested array layout: each element is two adjacent `u16`s, and the array has nine elements. The subsequent state-two loop indexes the local copy as a 3-by-3 table, reads each entry's `x` and `y`, adds them to base tile coordinates for `func_80025710`, and scales them into effect positions for `func_80025648`. Copying to the stack preserves the original snapshot behavior across those calls.

`D_80024004` is ordinary overlay data, not MMIO or synchronization state, and its declaration is non-volatile. The cast does not create a strict-aliasing mismatch: `copy_src` is derived from the address of the actual `LocalPoints` object and is cast back to `LocalPoints *` before dereference. The destination is a distinct automatic object. These properties also make the assignment valid in the port build.

The public definition remains `void func_80025800(void *effect_in, void *position_in, void *visual_in)`. A bounded source search found no textual caller, and a complete DUNGEON-container scan found no direct `jal` or `j` encoding for `0x80025800`. The sole raw `0x80025800` word is at file offset `0x18A2060`, in a different overlay image: the neighboring row's delta maps that file location to runtime `0x80025860`, amid a sequence of data pointers spaced by 12 bytes. It is therefore an overlay-address alias, not a caller or callback-table reference to this row. The entry is consequently reached through an indirect/fixed-entry overlay mechanism that this static scan does not expose. This limits caller-type corroboration, but the candidate does not alter the established API or any use of its three inputs; the body consistently treats them as effect, position, and visual records.

## Scope

All candidate, assembly, retail, and receipt files are confined to `work/native_lane/r43_points36/`. No production source, recipe, configuration, ledger, export, or build-root file was changed for this review.
