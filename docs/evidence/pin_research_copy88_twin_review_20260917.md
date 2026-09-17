Working paths in this review snapshot refer to `work/native_lane/r41_copy88_twin/`.

# Independent semantic review: `town/func_8081DD70` / runtime `func_80020570`

## Decision

Use `scratch/natural_reviewed.c`, not `natural_v2.c`.  It is the zero-pin
aggregate reconstruction from `natural_v1.c` with one evidence-backed type
correction: the callback field and canonical `func_800206D0` declaration are
`void (*)(void *, void *, void *)`, matching the actual definition in
`src/town/func_8081DED0.c`.  It deliberately retains v1's established pointer
declarations for the three helper calls.  It adds no pointer-to-`s32` casts and
does not assume that the allocator returns this row's private `Object` type.

The reviewed file independently verifies `MATCH`, 88/88 words, at
`2.7.2-cdk-G0`.  It has no pin sites, and `pin_census.landing_refusal` returns
`None` against the current source.

| Artifact | SHA-256 |
|---|---|
| Baseline production source before landing | `9c369347519663478a166ae5b520c615934ead681ddc8f1beff0dd8c88a25e21` |
| `scratch/natural_v1.c` | `3db020fdf1ae33d819e5af61a127abfea55b1656b13ff34803c69f2477125a04` |
| Rejected `scratch/natural_v2.c` | `37c63ce0a37709efb1ca02eff30dc358596e3a0b222324ff0fbf59241f5ee05f` |
| Reviewed candidate | `00e5f850c3d20827125c648ccaf1ddf225c7e5a990f668701235fdf927dea3b3` |

The verification receipt is
`natural_reviewed_2.7.2-cdk-G0_verify.json`.  The complete retail map remains
`../r40_copy_transfer/return_probe/maps/func_8081DD70.retail.dis` (352 bytes,
88 words; SHA-256
`a6036b99fcbc051ea6bc838eb948376f1251ac5c7263f9990b31381732fc59c0`).

## Runtime identity and definite callers

The catalog row's synthetic label is `func_8081DD70` and its `true_name` field
is null.  The code image places this routine at runtime address `0x80020570`:
it is the 0x160-byte routine immediately preceding the handler at
`0x800206D0`.  The review therefore uses `func_80020570` only for same-image
caller analysis; it does not claim that the catalog label itself is a source
symbol mapping suitable for a global rename.

`src/town/func_8081E9A4.c` declares `func_80020570(void *, void *)` and has two
definite call sites.  Both pass an `EffectMessage` followed by an
`EffectScratch`:

- `EffectMessage` is exactly 0x58 bytes on the target ABI: `kind` at +0,
  `owner` at +4, padding through +0x53, and `x/y` at +0x54/+0x56.  This is the
  complete 88-byte `Payload88` copied by the candidate.
- `EffectScratch` is exactly six `s32` values, 0x18 bytes.  This is the
  complete `Initial24` copied through `object->initial`.
- The first loop sets `message.x` to 2, 1, then 0.  The second call path sets
  it to `func_80069EF8() % 3`.  Thus the signed halfword at source +0x54 used
  to index `D_8002445C` is in 0..2 at both definite callers.
- The two inputs are distinct adjacent/local objects, while the destinations
  belong to a node newly returned by the allocator.  The aggregate copies do
  not introduce an overlap change.  Allocation failure still skips every
  copy, field write, and helper call.

This caller evidence also explains why copying all 0x58 bytes is required:
the callback later reads the copied `x` value at payload +0x54 as the pickup
denomination/resource kind.

## Layout and resource semantics

On the 32-bit target ABI, the private `Object` view places the initial record,
render record, and callback at +8, +0x0c, and +0x10.  `RenderPart` maps the
retail accesses exactly: x/y +4/+5, image/resource word +8, color +0x0c,
flags +0x14, and scales +0x1c/+0x1e.  `Payload88` and `Initial24` use only
fixed-width `s32` storage, so their sizes are 0x58 and 0x18 independently of
host pointer width.

`D_8002445C` is correctly an `s32[]`, not an address table.  The actual
`func_800206D0` handler declares the same symbol as `s32[]`, indexes it with
the copied denomination at pickup +0x54, and stores the selected word into the
sprite image field.  The candidate's `RenderPart.image` is correspondingly
`s32`.  The definite callers establish the 0..2 index domain.

`D_80020014`, `D_80024420`, and `D_80045340` are used here as addresses.  The
array declarations in v1/the reviewed candidate preserve that intent.
`D_80024420` is also declared `u8[]` in the actual callback TU.

The callback store now uses the canonical executable symbol
`func_800206D0`, whose definition is exactly
`void func_800206D0(void *, void *, void *)`.  The typed callback therefore
has a verified implementation contract; the copied `State`, `Motion`, and
`Actor` tags in v1/v2 were unproved and have been removed.

## Helper prototype boundary

- `func_8003FC64` actually returns `void *`.  Keeping that declaration and
  assigning it locally to `Object *` is correct.  V2's `Object *` return type
  invents a cross-translation-unit type promise.
- The reconstructed `func_8004491C` definition returns `s32` and receives a
  word-valued registration ID.  This row ignores the result and passes the
  address `D_80045340`; many town callers preserve that second argument as a
  pointer.  V1's `void (void *, void *)` declaration preserves the established
  call-site model and target ABI.  Aligning the declaration globally is
  separate prototype debt.
- The reconstructed `func_8008F074` definition has two `s32` setup words, but
  this row passes `object->initial` and `D_80024420`, both guest addresses.
  They are stored/forwarded as 32-bit target words.  V2's explicit `(s32)`
  casts make host-pointer truncation part of this source without resolving
  the guest-address representation.  The reviewed candidate keeps the prior
  pointer declaration.  A future coherent repair needs a project-wide
  guest-address type or matching callee model, not per-call narrowing casts.

These local declarations are ABI-equivalent for the 32-bit PS1 build and the
exact receipt proves the emitted call registers.  They are not offered as a
global prototype cleanup.

## Portability boundary and landing recommendation

Like the existing object reconstruction, the private `Object` contains target
pointers and assumes the PS1 32-bit layout.  On an LP64 native host its pointer
members would not remain at +8/+0x0c/+0x10, and the payload +0x50 store through
`void **` would be eight bytes.  This is existing target-memory-model debt.
The reviewed source avoids worsening it with explicit narrowing; a native
port must represent stored guest addresses with a 32-bit guest-address type
and translate before dereference.

The source and recipe form one reconstruction: the current six-pin source is
exact at `2.95.2-G0 -fno-expensive-optimizations`, while this ordinary
two-aggregate source is exact at `2.7.2-cdk-G0`.  The exact endpoint supports
that recovered compiler cell but does not by itself establish the historical
release.  Export `scratch/natural_reviewed.c` with the recipe change as one
hash-bound transition, then use the live-row verifier and affected town window
gate as publication authority.
