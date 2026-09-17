Final cleanup: root removed the now-unused copy-end assignment/declaration and
four scalar scratch declarations. Final source SHA-256: `28948b23db5fb310f79bc40107deed00b19013f0663ad9e0cd4ff651a0da984a`.
The final source independently verifies exact at 114 words and the affected
5,084-byte window was rebuilt again with MATCH. Interfaces, memory accesses
and pin count are unchanged; the receipt retains this final hash and gate.

Publication update: the accepted candidate has landed and passed all affected
windows and SLUS; see [the round-43 receipt](pin_research_round43_20260917.json).
The review below records its pre-publication state.

Working paths in this review snapshot refer to `work/native_lane/r43_dungeon_copy`.

# Independent review: `dungeon/func_8132B300`

Review date: 2026-09-17

## Verdict

**PASS for a gated landing candidate.** The candidate is a zero-pin, full-row
byte match at stock `2.7.2-cdk-G0`, and the two source changes preserve the
observable behavior supported by the current caller, allocator, and real
helper implementation. The function interface is unchanged.

- Current source SHA-256:
  `132d02176aab823864fa24c45ec8b12d0073bbae42e8d550d6cdc91eefb27377`
- Independently compiled candidate:
  `raw/8132B300/aggregate_real_call.c`
- Independently compiled candidate SHA-256:
  `b13086ad354fa609fa8532e112a0685298958ac21696d3b109f426c03837dadf`
- Final staged output:
  `out/dungeon/func_8132B300.c`
- Final staged output SHA-256:
  `4c2e98b3ab10551a7b789261d6c565d9848717cdd0f50dd227d3b69b0afecf2e`
- Final candidate pin census: `0` sites; current source has one `ASM_KEEP`
  site.

The final staged output differs from the independently compiled candidate only
by deletion of the stale trailing four-line `MECHANISM` comment (including its
blank line). No token presented to the C preprocessor/compiler changed, so the
linked-strict proof below applies unchanged to the final staged hash. This was
confirmed with a direct unified diff; no second compile was needed for the
comment-only normalization.

## Independent exactness check

I ran the candidate through the row scorer at the row's true linked address:

```text
python3 tools/aligned_score.py \
  --func func_8132B300 --overlay dungeon \
  --configs 2.7.2-cdk-G0 --summary-json \
  work/native_lane/r43_dungeon_copy/raw/8132B300/aggregate_real_call.c
```

The oracle reported:

- `status: MATCH`, `exact: true`, `byte_exact: true`
- `comparison_mode: linked-strict`
- `mask_relocations: false`
- generated/target length: `456/456` bytes, `114/114` words
- substitutions/indels/positional words off: `0/0/0`
- scorer source SHA:
  `b13086ad354fa609fa8532e112a0685298958ac21696d3b109f426c03837dadf`
- target SHA: `5654cd37674e2b0d98907dddad405bb219b19f2d63492681143d555daee97a23`
- compiler SHA:
  `7a571911a97cef0c6b7b5d4174e89ac54f9806ce3d4b233c0f8620e3503c672b`

The current pinned source independently remains linked-strict exact at both
its recorded `2.8.1-G0` cell and `2.7.2-cdk-G0`. This is a valid normal-cell
control: the match is not obtained by accepting relocation-masked words or an
already-broken baseline.

The candidate is recipe-specific. At `2.8.1-G0` it has the same 114-word
length but 14 strict substitutions, classified as register renames. That does
not weaken the CDK result, but it means the row recipe must change with the
source if this candidate lands.

## Forty-eight-byte copy

The old loop copies three `CopyBlock` values. Each block is four 32-bit words,
so the source interval is exactly `[sprite_template, sprite_template + 0x30)`
and the destination interval is `[sprite, sprite + 0x30)`. The replacement
`Copy48` contains twelve `u32` words and covers those same 48 bytes without a
tail, prefix, or widened access.

The only caller is `func_801730AC` in `src/dungeon/func_8132B8AC.c`. It passes
its existing `sprite` argument as `sprite_template`. The caller's
`S_func_8132B8AC_2` layout reaches exactly 0x30 bytes: its final pointer is at
offset 0x2C and occupies bytes 0x2C--0x2F. The callee also reads template
fields at 0x1C and 0x1E after the copy, consistent with that same record.

The destination is the child object returned by
`func_8003FD64(0x112, parent_object)`, not the caller's sprite. The real
allocator in `src/slus/w_8003FD64.c` clears and returns a newly removed free
node (or delegates to its allocation fallback). Because `0x112` contains the
`0x100` flag, it sets `field_0xC` to `node + 0xF4`. The node ends at `+0x124`,
leaving exactly 0x30 bytes for the destination sprite. The callee's
`S_80172B00_3` likewise has its final pointer at 0x2C and size 0x30. The source
is the active parent's sprite while the destination belongs to the newly
allocated child, so the audited call path supplies disjoint storage.

Both old and new copy forms use 32-bit aggregate members through the existing
`CopyBlock *` cursors. The new cast neither narrows a pointer nor raises its
alignment beyond four bytes. The allocator offset `0xF4` is four-byte aligned,
and the old word loop already depended on the same alignment for both ranges.
There are no volatile accesses in either range.

## Helper call and discarded values

`src/slus/w_8004491C.c` defines the real helper with two parameters:

```c
s32 func_8004491C(RegistrationNode *entry, s32 registration_id)
```

Its body reads only those parameters. I independently reran:

```text
python3 tools/verify.py slus/w_8004491C src/slus/w_8004491C.c
```

It returned `status: ok`, `exact: true`, with object SHA-256
`3a4e53898ac90709a7330e6a4bcd827b4ff4e348b2d75264d727b9d404f5de7b`,
matching `work/native_lane/r43_helper_abi/helper_verify.json`.

The candidate preserves `effect_object` and `&D_80045340` as the first two
arguments. The deleted third and fourth arguments were the local values
`copy_dst` and `copy_src` after their loop increments. Evaluating those plain
local pointer expressions had no side effects; the real callee cannot consume
them, and neither cursor is used after the call. Removing the loop increments
therefore does not remove observable state once the artificial extra arguments
are removed.

The definition and all three parameters of `func_80172B00` are unchanged. The
candidate also leaves the old-style local declaration of `func_8004491C`
unchanged, so it introduces no exported prototype, calling-convention, or
cross-translation-unit ABI change. The new two-argument call agrees with the
verified helper ABI.

## Limits and landing gate

This review establishes the one observed caller and current allocator/helper
contracts. It does not claim compiler lineage from the recipe-specific match.
The aggregate cast continues the project's existing word-aliasing model; it is
not a general strict-ISO effective-type proof for arbitrary storage.

Before production landing, run the normal affected dungeon window gate for
`dungeon_deep_t8b_134b.overlay.yaml` and the row/database checks with the source
and recipe changed together. No production source, configuration, export, or
build file was modified by this review.
