# Round 40 semantic evidence snapshot

Working candidate paths below are relative to `work/native_lane/r40_callback/`.

# Semantic review: `town/func_80878974`

## Verdict

The aggregate-copy repair is semantically admissible for the PSX decomp and is supported by
independent source evidence, not only by the byte match.  The retail function copies one complete
52-byte `ov_work` record, then makes three printf-like calls.  Its first call has three source-level
arguments; the fourth `dst` argument in the pinned source is a reconstruction artifact caused by a
still-live destination register.

Do not land `aggregate_alias_three.c` verbatim.  It still contains an unused `D_807030A0`
declaration, unused `Block` locals, a second callback type, and a duplicate include.  The cleaned
`aggregate_final.c` expresses the same recovered behavior, names the proven `kind` member, removes
the artificial volatile qualifier, and is the preferred landing source.  Its linked-strict receipt
is 56/56 words exact at `2.7.2` with ASPSX 2.40:

- candidate SHA-256: `a2f43febd8306933d2a0648013a17fb94b078c5442df816f5c04e5de35ab0db6`
- retail SHA-256: `66834386175298a800d09426671d4866c3c2a38534cc8c78f0650576f4dd13f8`
- zero source pins

This approval is for target behavior.  The remaining overlapping `D_` declarations and the
`D_807030AC - 0xC` expression are not portable ISO C object modeling; they are existing decomp type
debt described below.

## Address identity

The row name is synthetic.  TOWN file offset `0x7F8974` belongs to the image whose proven
file-to-VRAM delta is `0x7FF0A000`, so the runtime address is:

```
0x7F8974 + 0x7FF0A000 = 0x80702974
```

This agrees with `docs/evidence/konami_assertion_sites.csv`, which locates the three calls at true
addresses `0x807029EC`, `0x80702A10`, and `0x80702A38`.  The nominal symbol
`func_80878974` comes from the sweep's synthetic `0x80080000` base.  The source can retain that
nominal symbol for current row/build compatibility, but documentation must not describe
`0x80878974` as the runtime address.  `config/overlays/town.rowbase.jsonl` already identifies this
block as part of the same `0x80700000` image and calls the current identity wrong.

## Retail site map and the record copy

Retail words 0-21 do the following:

1. Preserve the input pointer in `$t0`.
2. Form destination `0x807030A0` in `$a3`.
3. Set source end to `p + 0x30`.
4. Copy three 16-byte chunks with four `lw` and four `sw` instructions per iteration.
5. Copy one final word at offset `0x30`.

The written interval is exactly `[0x807030A0, 0x807030D4)`, or 52 bytes.  GCC 2.7.2 lowers the
candidate's 13-word aggregate assignment to precisely this loop.  The nearby `sn_main.c:48` copy,
`func_808B3620`, also copies twelve words in three chunks plus a final word, independently
supporting a stable 52-byte record rather than a hand-written byte count.

The record interpretation is fixed by the embedded debug text and the code after the copy:

| record offset | destination | evidence |
|---:|---:|---|
| `+0x08` | `0x807030A8` | Printed first as `p->kind`, then as `ov_work.kind`; `%d` supports `s32 kind`. |
| `+0x0C` | `0x807030AC` | Used by the following module function as a `TownObject *`. |
| `+0x14` | `0x807030B4` | Used by the following module function as a pointer-remap table. |
| `+0x18` | `0x807030B8` | Used throughout the image as the runtime/service-table pointer. |

Earlier functions in the same image also use the word at `+0x04` as a flag-table base.  Thus the
real record contains mixed scalar and pointer fields; it is not literally thirteen logical signed
integers.  `SceneRecord` with opaque words is nevertheless a correct fixed-width copy type on the
32-bit PSX, and `aggregate_final.c` improves it by giving the proven `kind` field its real name.
The evidence calls the destination `ov_work`, so `OverlayWork` would be a more faithful eventual
type name than `SceneRecord`.

The function parameter is still written as `s32 *p`, but the disc's own string is `p->kind`.
The likely original type was a pointer to the same overlay-work record.  Changing the parameter to
`SceneRecord *p` would preserve the MIPS ABI and remove local casts if it remains exact; lack of that
cleanup does not change the candidate's runtime behavior.

## Logger interface and argument count

The bytes immediately before the function map to these runtime strings:

| VRAM | file offset | string |
|---:|---:|---|
| `0x807028B0` | `0x7F88B0` | `%s = %d\n` |
| `0x807028BC` | `0x7F88BC` | `p->kind` |
| `0x807028C4` | `0x7F88C4` | `ov_work.kind` |
| `0x807028D4` | `0x7F88D4` | `mark: %s line %d\n` |
| `0x807028E8` | `0x7F88E8` | `sn_main.c` |

The three calls therefore reconstruct as:

```c
log("%s = %d\n", "p->kind", p->kind);
log("%s = %d\n", "ov_work.kind", ov_work.kind);
log("mark: %s line %d\n", "sn_main.c", 47);
```

Each format consumes exactly two arguments after the format string.  Retail explicitly prepares
`$a0`, `$a1`, and `$a2` for the first call and does not prepare a fourth source-level argument.
After the aggregate loop, `$a3` happens still to hold the destination cursor.  The old manual-loop
source used `ASM_USE(dst)` and passed `dst` as a fourth argument to reproduce this incidental live
register.  Aggregate assignment naturally leaves the same register value while permitting the C
call to state its actual three-argument meaning.

The variadic declaration is semantically justified by the format strings.  It is not codegen
scaffolding.  A future shared definition should preferably use a name such as `print` and a type
like `void (*)(const char *format, ...)`; the candidate's
`void (*func68)(void *, void *, ...)` has the correct calling convention but weak parameter types.
The return type cannot be recovered here because all callers discard it, so `void` is safe for this
function's behavior.

Nearby module evidence agrees:

- `func_80701FEC` uses the same service pointer and `+0x68` slot three times as
  `format, label, s32 value` for `kind`, `mode`, and `sno`.
- The following routine at true `0x80702A78` uses `+0x68` with a format string, a label/file
  string, and line `0xE2`, then invokes a separate service slot.
- The preceding routine at true `0x80702924` uses another slot (`+0x64`) for an opcode-style
  runtime operation, showing that `D_807030B8` is a multi-method service table rather than MMIO.
- The related `sn_main.c:48` build has the same `p->kind` and `ov_work.kind` prints.  Its recovered
  fourth argument reflects the same live-register ambiguity and is not evidence that the `%d`
  logger consumes an extra value.

## Volatile qualification

Removing `volatile` from the callback-table pointer is semantically sound.  `D_807030B8` is an
ordinary RAM field inside the copied work record, not a hardware register or synchronization
object.  The compiler still reloads it around calls because an unknown call may modify global
memory.  The adjacent source consistently treats the value as a runtime/service-table pointer.

## Caller and ABI audit

The repair does not alter the external ABI: one pointer arrives in `$a0`, no return value is used,
and the same three indirect calls occur in the same order.  No direct caller was found in the
recovered TOWN sources or among direct `j`/`jal` instructions in the local proven image span
`0x7F7800..0x7F8BA8`; this entry may be reached through a table or external tool runtime.  The lack
of a direct caller means the precise source-level parameter typedef remains unconfirmed, but the
disc strings prove it points to a record with `kind` at `+0x08`.

## Portability and layout risks

These are real type-modeling limitations, but none is introduced as new target behavior by the
aggregate repair:

1. `D_807030AC - 0xC` forms a pointer before the separately declared byte array.  ISO C does not
   define that pointer arithmetic.  It is used to name the known absolute base `0x807030A0` because
   the current label set has a field symbol at `0x807030AC`.
2. `D_807030A8`, `D_807030AC`, and `D_807030B8` are declared as separate extern objects even though
   they are fields inside the copied 52-byte `ov_work`.  Their declared extents overlap in the C
   model.  A host-native port should replace them with one shared `OverlayWork` definition and
   field accesses.
3. Dereferencing `(SceneRecord *)p` assumes four-byte alignment and at least 52 readable bytes.
   Retail performs `lw` loads across exactly that interval, so these are genuine target
   preconditions.  A modern strict-aliasing build would also need the real parameter type or a
   byte-copy boundary.
4. The opaque words preserve the 32-bit guest layout.  If pointer fields are later represented as
   native pointers on a 64-bit port, the structure needs an explicit guest-layout type rather than
   silent pointer widening.

For the current reconstruction, the candidate preserves the exact copy interval and ordering and
removes two artificial source devices: the explicit fourth logger argument and the volatile table
qualification.  The remaining layout debt should be tracked as a shared-record cleanup, not used
to retain the manual loop or source pins.
