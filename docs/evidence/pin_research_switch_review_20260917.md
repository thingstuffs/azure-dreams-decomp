# Round 48 switch dispatcher review

## Decision

`work/native_lane/r48_switch_address/candidate_final.c` is an ordinary-C,
zero-pin reconstruction of `dungeon/func_818B15F4`.  It replaces the inherited
computed-goto table, label-address keepalive array, `ASM_KEEP`, and false
external-noreturn epilogue calls with one natural `switch`.  It also passes all
three incoming arguments to each of the three real helper alternatives and
uses pointer types for the two callback context words.

The reviewed candidate SHA-256 is
`76ba8f1cfa4555cb902472961b34cf521c17a679c9277c8a6404067dcb818c5b`.
At stock `2.7.2-cdk-G0` it is linked-strict exact for all 28 words, with no
relocation masking, against target SHA-256
`0e6615288977cd29f588d47eea333d4569d7e96c1874b0d5cda20344cd7f2f03`.
The receipt is
`work/native_lane/r48_switch_address/final_strict.json`, SHA-256
`79a8e633dd7f07f9940a4524d19d859b601218bfdd058b79b7b8281ca7d1694e`.

The candidate contains no inline assembly, `ASM_*`, `NON_MATCHING`, volatile
object, register binding, computed goto, label address, explicit jump table,
literal code address, or fake use.  Candidate 4 from the pilot is therefore
not preferred even though it also recompiles exactly: it retains computed-goto
and label-keepalive scaffolding that the switch does not need.

The recipe evidence establishes a reproducible stock cell, not a unique
historical compiler lineage.  The current pinned source and the natural switch
are both exact at CDK; the current pinned source is also exact at its recorded
plain `2.7.2` cell.  The natural switch at plain `2.7.2` has five address-form
substitutions.  CDK emits the retail HIGH+LOW table address while the plain
family folds LOW into the indexed load.

## Complete retail control flow and generated table

The full row is `0x80024DF4..0x80024E64`, 112 bytes.  It reads a signed state
halfword at `arg0+0xA`, checks it as unsigned against eight, and sends any
out-of-range value to the common epilogue.  The eight table entries are:

| state | retail target | source action |
|---:|---:|---|
| 0 | `0x80024E54` | return zero |
| 1 | `0x80024E54` | return zero |
| 2 | `0x80024E54` | return zero |
| 3 | `0x80024E54` | return zero |
| 4 | `0x80024E2C` | call `0x800249B4`, then common return |
| 5 | `0x80024E3C` | call `0x80024B34`, then common return |
| 6 | `0x80024E4C` | call `0x80024C84`, then fall through |
| 7 | `0x80024E54` | return zero |

The epilogue at `0x80024E54` restores `ra`, clears `v0`, returns, and restores
`sp` in the delay slot.  It is inside this function.  The old declaration of
`func_80024E54` as an external noreturn function was therefore false.

The compiler assembly in `final.s` links the switch to its own `$L12` table.
Its generated entries are `$L2` four times, `$L9`, `$L10`, `$L11`, then `$L2`.
Those labels link to offsets `+0x60`, `+0x38`, `+0x48`, `+0x58`, and `+0x60`,
respectively, exactly matching the retail table above.  Linked-strict equality
also proves the code's `%hi/%lo` reference resolves to retail address
`0x80024008`; this is source-generated table data, not an external table kept
alive by a pin.

## Image identity

The existing rowbase record maps file row
`0x18D15F4..0x18D1664` to `0x80024DF4..0x80024E64` with delta
`0x7E753800`.  Its eight-entry table is at file offset `0x18D0808` and every
entry lands within this row.  The same delta is already proven immediately
after this row: `0x18D1664` maps to `0x80024E64`, so the regions abut exactly in
file and runtime space.  The earlier row `img_18d08ec_800240ec` is also proven
at the same delta.  The record remains `solved` only because the old
literal-call source could not discriminate load bases.  This honest local-C
candidate is the discriminating linked-strict recompile needed for normal
promotion; the review does not claim that promotion has already occurred.

## Helper and callback contracts

The three calls map under the same delta to the contiguous same-image helpers
`func_818B11B4`, `func_818B1334`, and `func_818B1484`.  Each helper accepts
three incoming words, returns `s32`, and forwards its third word unchanged as
the third argument of `func_80024610`.  The dispatcher ignores each helper's
result and itself always returns zero.

`func_80024610` returns `s32`.  It dereferences its second argument as the
origin pointer but does not read its first or third arguments.  Consequently,
the root callee body does not prove the semantic type of the third word.  The
pointer conclusion comes from the callback path instead: the adjacent
same-image `func_80024E64(State *, Motion *, DrawInfo *)` registers
`func_80024DF4`; the active-node allocator types fields at offsets 8 and 12 as
pointers; and the alternate callback walker calls negative callbacks as
`(void *, void *, void *)`.  `func_818B1334` already names its third formal
`void *context`.  The generic positive callback walker currently spells the
same two target words as `s32`; that target-ABI reconstruction is compatible
at the machine level but does not justify narrowing the recovered pointer
contexts in the function-specific source.

There is no direct C call to `func_80024DF4` in the inspected sources.  The
same-image source registers it indirectly in `func_818B1664`.  That file's
current `extern void func_80024DF4(void)` is pre-existing callback declaration
debt; its registration call does not supply the eventual callback arguments.
The final dispatcher declaration is `s32 (Func818B15F4Arg *, void *, void *)`,
which preserves all three incoming target words and the observed return value.

Three narrow forwarding-chain corrections were independently compiled without
changing bytes:

| helper scratch source | correction | recorded stock recipe | result | SHA-256 |
|---|---|---|---|---|
| `helper_818B11B4_void_context.c` | third formal to `void *`; prototype `func_80024610` as returning `s32` with pointer contexts | `2.7.2-cdk` | 96/96 exact | `7758a99fc3337744f89acd11042e8d02d2d59f0c8ec6a6bd907508393a15556b` |
| `helper_818B1334_return_contract.c` | correct only `func_80024610` return from `void` to `s32` | `2.8.1-G0` | 84/84 exact | `105e7f1071cd020f87fad95586779b8e1d8d37ffe6347687558068e0ae26800b` |
| `helper_818B1484_void_context.c` | third formal to `void *`; prototype `func_80024610` as returning `s32` with pointer contexts | `2.7.2-cdk` | 92/92 exact | `0c7c53b8acb60b0571649a9a4ca89e9349d4463cf0f2058034442601a7a377cd` |

Their verification receipts are in
`work/native_lane/r48_switch_review/`; SHA-256 values are
`3b60bc67285ebcf2aacbd3766b8dc8efe5cd39e54f0c823b09820606fe20d406`,
`24596c6ce68c20339b5db17c2495f6f388447cb6604b61ade90ff44b57a45343`,
and `ea9e8bb124d3373f42436e2c02b2f9a04283f49626871dafacf35efee933a03`
in table order.  These tests cover only the necessary forwarding declarations
and third-formal corrections; they do not infer meaning for the unused root
callee parameter from register coincidence.  The current `func_818B0E10`
definition still spells its unused first and third formals as `s32`; making its
definition and the pointer-context helper declarations ISO-C compatible is a
declaration cleanup, even though the target ABI and emitted calls are
unchanged.  The final contract addendum below verifies and closes that cleanup.

## Provenance and limits

This review used the complete retail disassembly
`work/native_lane/r48_switch_address/retail.dis` (SHA-256
`ac42de8a46b930489cd6089e71be4f0a51740dd5c06c0be34b810e4a7b3d1c18`),
the decoded table receipt `table.json` (SHA-256
`949d5592e61b9c582d739e7f48bfc2b004a44774619a27e1a22a93149c05110c`),
the CDK controls (SHA-256
`2a24df03e0617cc855aa9614b905c82dbc9612da487a88f63fb743e8fa1115f6`),
the rowbase ledger, and the recovered caller/helper bodies named above.
No production source, configuration, export, build root, or pin was changed by
the review.

## Final six-file contract addendum

The landing set now closes the declaration debt across the actual callee,
three forwarding helpers, dispatcher, and registration source.  I inspected
the final diffs; they change only the types and declarations needed for this
chain.

The actual `func_818B0E10` definition now accepts pointer-typed unused first
and third arguments, matching what all three helpers pass.  Its points input
and local base are `s32 *`, which expresses the existing word-vector accesses
without an integer-to-pointer conversion or loss of bits.  The eighth formal
remains a full `s32` target word.  The function retains its existing explicit
`s16 phase = (s16)color_phase` conversion at the point where the value is
actually consumed, so the truncation is local and visible.

All three helper declarations are consequently identical in contract:

```c
s32 func_80024610(void *, void *, void *, s32, s32, s32 *, u8, s32);
```

The `818B1334` spelling uses `M2C_UNK *` for the sixth formal; in
`m2c_compat.h`, `M2C_UNK` is an alias of `s32`, so it is the same type.

`func_818B11B4` and `func_818B1484` also change their third formals to
`void *`; `func_818B1334` already had that type.  A negative control typed the
last callee formal as `u16`.  That introduced one substitution in each helper,
because the prototype imposed a caller-side narrowing operation.  Keeping the
formal `s32` makes all three callers exact and preserves the full incoming
word; the callee's existing local cast supplies the supported low-halfword
semantics.  This avoids inferring a narrow calling convention merely from how
the callee later uses the value.

The adjacent registration source now declares the callback as
`s32 func_80024DF4(void *, void *, void *)`, matching the final switch
definition rather than the old no-argument `void` declaration.  This is a
declaration-only change at the registration call and remains 650/650 words
exact.

The final source identities and checks are:

| role | final scratch source | SHA-256 | verification |
|---|---|---|---|
| dispatcher | `candidate_final.c` | `76ba8f1cfa4555cb902472961b34cf521c17a679c9277c8a6404067dcb818c5b` | 28/28 linked-strict exact at `2.7.2-cdk-G0` |
| actual callee | `root_final_contract.c` | `f5739a77409408104a670e67c1640e4780c98493b72647150c5209ef393f2ca1` | 233/233 exact at recorded recipe |
| helper `818B11B4` | `func_818B11B4_final_contract.c` | `5450c97b200e816bfa587f9447c3e4b7cd2b2ab868981e1691ee5b0c1d10f317` | 96/96 exact at recorded recipe |
| helper `818B1334` | `func_818B1334_final_contract.c` | `2605c28ab019c8f3b271fcef2cc6baf1751b6bf4cb49fc112a772e47b2a2bba2` | 84/84 exact at recorded recipe |
| helper `818B1484` | `func_818B1484_final_contract.c` | `4b950eeca3ff9425eded1dd45c01bb6edeab93a958805e0b0ccdd1e66b05a84f` | 92/92 exact at recorded recipe |
| registration source | `registration_contract.c` | `166853dcb155437ba9e65f5853104ed0d9a8f25135bf8c9f1be2b96887cfaaea` | 650/650 exact at recorded recipe |

The four callee/helper results are recorded in
`work/native_lane/r48_switch_address/final_contract_controls.json`, SHA-256
`60220d993c2504d5651dbbcdd20295a9d62b4f4391287d86b559ac6266973b82`.
The registration result, callee compatibility control, and three
narrow-formal negative controls are in `complete_contract_controls.json`,
SHA-256
`2f872950550ad7beca2a897c63ea599b68196c2156082940736e27e9344d29de`.
The dispatcher linked-strict receipt remains `final_strict.json`, SHA-256
`79a8e633dd7f07f9940a4524d19d859b601218bfdd058b79b7b8281ca7d1694e`.

Across the six files, this removes the dispatcher's single `ASM_KEEP` and its
computed-goto/false-noreturn scaffold.  It introduces no new pin or register
constraint.  Existing helper and root-callee pins remain outside this bounded
repair.

## Publication addendum (primary agent)

The hashes above describe the independently reviewed intermediate. The final dispatcher
uses three `void *` formals and casts only its first argument to the local state
view, making its definition exactly compatible with the registration prototype.
It defines `func_80024DF4`, the registered proven runtime symbol; this lets the
existing generic table-placement machinery find the correct object section.
No compiler or linker implementation change was needed. Its final SHA-256 is
`b6b1c3ec3d3512e0a96c0804bdbdf88c4e8c1fdbce2f59032792e542ce4f527d`.

The registration source also contained two pre-existing, unused malformed macros
that redefined the keyword `do` under NON_MATCHING. The entire unused table-macro
block was removed. No invocation existed; target bytes remain 650/650 exact and
host syntax now passes. Its final SHA-256 is
`9be2b3ea87698ab5859dc14707985f18b54ef2cc8724973748f9b7a53e0979e9`.

Final evidence: [round 48 receipt](pin_research_round48_20260917.json). The dispatcher
is 28/28 linked-strict exact; all six host NON_MATCHING syntax checks pass; the
173,608-byte covering window and SLUS match; row database passes. The table at
file 0x18D0808 is before the window start, so a separate emitted-section comparison
proves all eight table entries (32 bytes) against retail rather than relying on
the window's NOLOAD address resolution. Ten isolated existing-pin erasures in the
three forwarding helpers and drawing callee all fail; no cascade gain is claimed.

The dispatcher also forward-declares the actual helper struct tags, so all
three helper prototypes agree with their typed definitions; ordinary C converts
the incoming void pointers at each call. This changes no instructions.
