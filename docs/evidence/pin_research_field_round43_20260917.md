Working paths in this review snapshot refer to `work/native_lane/r43_field_init`.

# Round 43 follow-up: `town/func_800BEA7C` / `func_800BC1DC`

## Outcome

No zero-pin exact source was found in the three-probe bound.  The existing
ordinary owner-recovery control remains the closest result: 45/45 words,
aligned total 1, with only `lw v1,-20(v1)` in place of retail
`lw v1,12(s0)`.  The follow-up explains both halves of that result from the
recovered GCC 2.8.1 implementation and rules out three natural source-level
ways of preserving the standalone payload base.

No candidate is retained for export.  Production source, configuration,
compiler, assembler, and shared tools were not changed.

## Fixed inputs

- Root state supplied for the wave: commit `1f808e00`, clean, 6,070 pins.
- Fixed row: `town/func_800BEA7C`, true symbol `func_800BC1DC`, 180 bytes /
  45 words, `2.8.1` with no extra flags.
- Exact two-pin base SHA-256:
  `52440b6983b0b608d7e2d93340fb7e12add706986c1c5a743fb50586ddb1afaf`.
- Existing owner control SHA-256:
  `58d77e7e05fe68f62c8b3c9e36e27202d35570e851d4c8da653921f44af74959`.
  Its prior full verifier result is 45/45, one substitution, no indels.
- The complete linked retail map and register roles are in `SITE_MAP.md`.

## Exact compiler-pass decision

The erased RTL reaches `flow` with three relevant instructions:

```text
insn 55: pseudo84 = object + 32
insn 58: value = 30
insn 60: mem:HI[pseudo84 + 2] = value   # pseudo84 has REG_DEAD here
```

`combine_instructions` walks each instruction's logical predecessor links and
tries both two- and three-insn combinations at
`toolchain/gcc-src/2.8.1/combine.c:584-599`.  `can_combine_p` accepts this
sequence under its SET/register, crossing-set, call, and volatility checks at
`combine.c:824-1048`.  The immediate does not alter `object`, so the
non-adjacent substitution is legal.

`try_combine` decides whether the earlier set must remain with:

```c
added_sets_2 = ! dead_or_set_p(i3, i2dest);
```

at `combine.c:1515-1544`.  In erased RTL, `pseudo84` dies in the store, so the
set need not remain.  `try_combine` substitutes the add into the store at
`combine.c:1648-1683`.  Recursive substitution then simplifies
`(object + 32) + 2` to `object + 34`: integer PLUS reassociation enters
`simplify_plus_minus` at `cse.c:3773-3783`; that routine flattens the operands,
folds constants, and rebuilds the nonconstant base first at
`cse.c:4333-4499`.  `plus_constant` implements the direct nested-constant
fold at `explow.c:108-128`.

The resulting combine dump deletes insn 55 and writes
`mem:HI[object + 34] = 30`.  This is the causal deletion.  Later scheduling and
allocation merely react to the shorter stream, swapping the subsequent local
roles of `v0` and `v1`.

## Why the one-word owner control chooses `v1 - 20`

The owner control gives `payload` a second semantic use:

```c
payload = &object->payload;
payload->lifetime = 30;
data = ((Object *)((u8 *)payload - 0x20))->data;
```

Its *initial* RTL already represents the final load as
`mem:SI[payload - 20]`; this form does not arise during combine.  Because the
payload pseudo remains live past the lifetime store, it has no `REG_DEAD` note
there.  `added_sets_2` therefore requires the `object + 32` set to survive.
The MIPS recognizer cannot encode a useful single parallel operation containing
both the retained add and store, so the original add remains and later becomes
retail's `addiu v1,s0,32`.

GCC has no pointer-provenance relation in this RTL saying that the payload
pseudo is permanently equal to `object + 32`.  Its arithmetic simplifier sees
`payload - 20`, with `payload` as the sole nonconstant operand.  It cannot
reverse that value into `object + 12`, so the linked result differs in exactly
that addressing word.

## Three bounded probes

All probes preserve the two definite callers' object contract: an embedded
payload begins at object +0x20, its lifetime is the halfword at +2, and the
render/data pointer is stored in the owning object at +0x0c.  They introduce no
asm, volatile access, pointer narrowing, new pin, or unused lifetime operation.

| Probe | SHA-256 | Prediction and result |
|---|---|---|
| `probe1_register.c` | `87ff8afc612c5e85fe3531a3bff076ebde6f446cf9f1f7c560025a9fa80718b4` | An ordinary C `register` storage class might mark the shared pointer as a user variable. GCC still gives the first value a death at the store and emits the erased 44-word body (`sh ...,34(s0)`); screen difference from exact base is 19 normalized lines. |
| `probe2_union.c` | `1a0848e24cb7e5cd2c4f7beafd5c30e60717464d7b2f3257bcbf562e7e3f2ec5` | A real union view reuses one source object for embedded payload and render pointers. Scalarization removes the union before combine; the payload add folds, and the typed alias sets let `lw ...,12(s0)` move before the lifetime store. Screen difference is 5 lines. |
| `probe3_named_owner.c` | `e2ab1a4b29f92699ca1f130b18e67ee316a271a46c553091d706e31984aea0c1` | A named `owner` supplies both `&owner->payload` and `owner->data`. GCC coalesces it with `object`; raw assembly is byte-for-byte identical to probe 2 and has the same 5-line screen difference. |

The screen negatives were not sent to the full verifier because each raw
stream lacks the required `addiu` and has additional ordering/register
differences.  The existing owner control is the only promising shape and
already has a full byte-verifier receipt.

## Semantic and caller evidence

`src/town/func_8081FA90.c` and `src/town/func_800BECFC.c` are the definite
callers.  Each supplies a two-halfword position record, an object setup address,
and a resource/setup word.  The sibling display construction in
`func_800BECFC.c` independently treats object +0x20 as embedded display data and
writes 30 at its +2 halfword, confirming the modeled payload and lifetime.

No caller or sibling reveals another observable use of this routine's payload
base.  Retail itself shows one use, then overwrites `v1` with the render pointer.
A source repair therefore cannot simply add a second lifetime use: it must find
an authentic relationship that survives long enough to defeat combine and is
then represented by an already-existing retail operation.

## Bounded causal conclusion

| Feature | Owner | Status |
|---|---|---|
| Deletion of `object + 32` | GCC 2.8.1 `combine`, gated by death of the payload pseudo at the store | Proven from dump transition and source predicate. |
| `object + 34` base choice | `simplify_plus_minus` / `plus_constant` on the substituted MEM address | Proven from compiler source and resulting RTL. |
| Owner-control `payload - 20` base | Front-end/expand RTL from the explicit container recovery | Present before combine; not recoverable to `object + 12` without provenance absent from RTL. |
| Downstream `v0/v1` swap | Allocation after the deleted add | Consequence; disappears when the add survives. |

The useful next experiment is compiler instrumentation, not another spelling
of the same object types.  Add temporary logging around the insn-55/60
`try_combine` call in a private compiler build to record `dead_or_set_p`,
`added_sets_2`, the recognized substituted MEM, and rejection of the two-SET
parallel in the owner control.  Compare that receipt with any independently
recovered, historically compatible 2.8.1 compiler only if such a binary is
available.  The fixed C-side oracle is the owner control: any future authentic
source shape must retain its first 29 retail words while changing only the
owner-recovery load from `-20(v1)` to `12(s0)`.

Root next-phase decision: the predicates above already explain the observed
fold. Logging them again alone would not distinguish a new repair. First seek
an independent ordinary exact sibling that retains a one-use payload base, or
new compiler-provenance evidence, then compare its operation and lowering with
this case. Further instrumentation should answer that specific difference.
