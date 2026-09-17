# Round 47 constructor identity and source review

## Decision

The two ordinary-C candidates are semantically preferable to the landed
sources and are independently reviewable for landing.  Each constructor now
returns the allocated object on success and null on allocation failure.  The
old declarations of `func_80024210` and `func_80024320` as external noreturn
functions were false: in the retail image those `j` instructions target the
calling function's own common epilogue.

Both final candidates are zero-pin, contain no `NON_MATCHING` arm, and are
byte-exact under their recorded stock recipe, `2.8.1-G0`:

| row | true start used by scorer | candidate | source SHA-256 | strict result |
|---|---:|---|---|---|
| `dungeon/func_818A4948` | `0x80024148` | `work/native_lane/r47_constructor_rebuild/sibling_positive_return.c` | `bf671e430ec20abe02425aa1649fbff609b7c5f2290d7d4625f3a2c18651bb88` | 58/58 words, linked-strict exact |
| `dungeon/func_818A4A64` | `0x80024264` | `work/native_lane/r47_constructor_rebuild/positive_return.c` | `b673c83118b2f3aca66cd32d0b581cd53c6983bc48e99658cf19d5806320d12b` | 55/55 words, linked-strict exact |

The linked-strict receipts are
`work/native_lane/r47_constructor_rebuild/sibling_positive_return_strict.json`
(SHA-256 `2b0dad13de01a1509341f72edf66944bfd30df76190901b9d2d31f276f6f2919`)
and `positive_return_strict.json` (SHA-256
`231bee87826f5fcdbd5688201a60af0a6db26fba1c62b946b8c6ae697241b958`).
They compare against retail SHA-256
`415c22c02fd3ccca71fa1de2d1baebc9153a3a67ab089e52b2bd8eb51bb83901`
and `e8b3bd1749fa656a4c1e3d78eba90120b163ee861b904413a2a76eac7f954b7b`
respectively.  Relocations were not masked.

## Retail control flow

The complete 58- and 55-word maps in
`work/native_lane/r47_direct_table/retail_818A4948.dis` and
`retail_818A4A64.dis` were read for this review.  In each body, the allocator
result is copied to `s1`, followed by `bnez s1, success`.  Failure executes an
unconditional local jump with `move v0,zero` in its delay slot:

- At true start `0x80024148`, retail word 13 jumps to `0x80024210`, offset
  `+0xC8`.  Words 50--57 at that address restore the frame and return.
- At true start `0x80024264`, retail word 13 jumps to `0x80024320`, offset
  `+0xBC`.  Words 47--54 at that address restore the frame and return.

Success moves `s1` to `v0` immediately before the same epilogue.  Thus the
machine contract is a nullable allocated-object return.  The positive-form C
is also the source shape that reproduces retail's branch polarity and split
static-address materialization.  The earlier `if (object == NULL)` ordinary C
control had the right value semantics but missed by distance 5 because it
inverted that control-flow shape.

The old sources represented the local jumps as calls to absolute externs marked
`__attribute__((noreturn))`.  That spelling made a relink at any base
non-discriminating and made the native-port failure path falsely fatal.  The
new source returns null directly.  The final-hash `port_review.json` records
that both files compile for the port and have no portability-lint findings.
The generic
arm-identity lander is expected to refuse because the repair intentionally
removes a semantically wrong conditional arm; this is a whole-C semantic
review, not an arm-collapse claim.

## Independent load-region identity

The proposed image relation is:

```
file 0x18C0800 -> VRAM 0x80020000
delta          =      0x7E75F800
```

Three independent observations agree with that relation.

First, it turns both constructor callbacks into exact registered row starts,
and the registered extents form a contiguous chain:

| file row | mapped start | mapped end | role |
|---:|---:|---:|---|
| `0x18C4828` | `0x80024028` | `0x800240C4` | preceding row |
| `0x18C48C4` | `0x800240C4` | `0x80024148` | callback stored by the `4948` constructor |
| `0x18C4948` | `0x80024148` | `0x80024230` | first constructor |
| `0x18C4A30` | `0x80024230` | `0x80024264` | callback stored by the `4A64` constructor |
| `0x18C4A64` | `0x80024264` | `0x80024340` | second constructor |

The recovered `func_818A48C4` body accepts three callback-style arguments.
The `func_818A4A30` machine body reads `a0`, uses `a2` as the target passed to
`func_800478B8`, and ignores the middle word.  Its current `long long` source
spelling is therefore ABI-shaped reconstruction debt; it does not contradict
the ordinary three-word callback role established by the constructor store.

Second, the retail table at file `0x18C4800`, which maps to runtime
`0x80024000`, contains a zero word plus runtime entries `0x800247D4`,
`0x8002488C`, `0x800248D4`, `0x80024DF0`, `0x80024F30`, `0x80024FB0`,
`0x80024FD8`, `0x800250E0`, and `0x80025118`.  Subtracting the same delta maps
all nine entries back into the same file image at `0x18C4FD4` through
`0x18C5918`.  This header/table evidence is independent of interpreting either
constructor's local jump.

Third, two later rows in the same file neighborhood already have byte-exact
true-base promotions under this delta: `0x18C4CA0 -> 0x800244A0` and
`0x18C4ED0 -> 0x800246D0`.  Their promoted candidate hashes are
`f256b619b17274975fa72cdfe5d1dd82f495d11ae1dd6949c58b529422330638`
and `40c98eae76e92b6ecef5af6ccb5083900704f9d5bf67237ccda4f8e994a92ed4`.

The older `dungeon_deep_18c4.overlay.yaml` gate maps a broad synthetic window
and records no row `true_name`; its synthetic `818A` namespace is not identity
evidence.  The two constructor rowbase records were previously only `solved`
because their original pseudo-call sources could not discriminate bases.  The
ordinary local-return candidates supply the missing discriminating recompiles.

## Callee contracts

The final declarations were checked against the recovered resident definitions:

- `src/slus/w_8003FC64.c` defines `void *func_8003FC64(s32 flags)`.  It returns
  an initialized node or null, including explicit null paths for allocation
  policy and exhaustion.  The constructors' positive branch and null return
  preserve that contract.
- `src/slus/code.c` defines
  `void func_8003DB94(struct Dst *, struct Elem *, short)`.  The candidates use
  a `void` return and `s16` third parameter, and pass constant zero.
- `src/slus/w_8004491C.c` defines
  `s32 func_8004491C(RegistrationNode *, s32 registration_id)`.  The candidates
  use `extern s32 func_8004491C(void *, s32)` and explicitly convert the
  address `D_80045340` to the target's 32-bit registration ID.  Its result is
  intentionally ignored.  This replaces the initially exact but incompatible
  `void (void *, void *)` declaration without changing bytes.

The candidates store the two verified same-image callback entry addresses and
the same table/registration addresses as retail.  They add no volatile object,
fake use, inline assembly, register binding, literal-address arithmetic, or
other allocation constraint.

## Caller scope and address collisions

A bounded decode of the mapped local image, file `0x18C4800..0x18C6000`
(runtime `0x80024000..0x80025800`), found one direct call to the first
constructor: `jal 0x80024148` at runtime `0x80024DE0`.  It supplies `a0=s2` and
`a1=s6`, then stores returned `v0` at `0x1C(s2)`, consistent with the
two-argument, pointer-return constructor.  The containing bytes after
`0x800247D4` have no registered source row, so this audit does not invent a
higher-level caller identity or parameter names for them.

The same bounded decode found no direct `j`/`jal` or literal pointer word for
`0x80024264`, and no literal pointer word for `0x80024148`.  That excludes a
plain local function table reference in the inspected image, but it does not
prove absence of dynamically constructed or out-of-image indirect callers.

Bare addresses cannot be treated as family-wide identities: other independently
loaded dungeon regions also contain a `func_80024264`, and the family noreturn
list contains that bare spelling for a different region.  These constructors
must be interpreted with their file row and rowbase region.  No noreturn fact
from another load region applies here.

## Review provenance

- Final candidate hashes and the zero-finding port checks are recorded in
  `work/native_lane/r47_constructor_identity/port_review.json` (SHA-256
  `0f02d4bc7eeeb9b9b0486c4d7dd6689fc4f3d3bd1e58ce521873a8ab4ba39e23`).
  The earlier
  `source_review.json` binds the pre-contract candidate and is not used as the
  final source-hash receipt.
- Full retail site map SHA-256:
  `retail_818A4948.dis`
  `2daa543eecbd85be1ae149a37440cba487d4c532dd4bef341548b24b49e624c4`;
  `retail_818A4A64.dis`
  `491e0ec7a0ca708b0572a86a8e9ef975178008f47afcbd781c18e4fb75eca378`.
- Identity sources were the retail table/header bytes, registered row extents,
  `config/overlays/dungeon.rowbase.jsonl`, and the two already promoted
  neighboring rows.  No source probe, compiler patch, production edit, recipe
  change, or new pin was used by this review.
