Working paths in this snapshot refer to `work/native_lane/r41_entry_join/`.

# `town/func_800A23CC`: recover the entry-store join

## Result

The exact candidate is `out/town/func_800A23CC.c`, based on source SHA-256
`78d6d82f634b6f75b0781fbc071b68ff9aa0e51ff5110a6b88d110addcd8f0de` at the
already proven row recipe `2.7.2-cdk-G0`. It removes both remaining pins:
`stored_entry ASM_REG("$2")` and `ASM_KEEP(entry)`. The per-row verifier reports
113/113 words, zero substitutions, and zero indels.

The repair is one source fact: `func_8009FB2C` returns the entry it allocates.
The source now declares a `void *` return, stores `entry` directly in
the slot, and returns `entry`. The paired `out/town/func_800A2590.c` keeps the
value pointer-typed through `set_item_w0`; the VM transports the same 32-bit
return word. No volatile qualifier, fake dependency, literal
address addition, or replacement register pin was introduced.

## Exact base and attribution

- Base verification: `python3 tools/verify.py town/func_800A23CC
  src/town/func_800A23CC.c --regions` -> `MATCH`, total 0.
- Base size: 113 words / 452 bytes.
- Recipe: `2.7.2-cdk-G0`, already proven by the landed Round 40 record-copy
  receipt and complete `town_scene` gate.
- The `az-c-rebuild` workflow's `tools/lineage_fingerprint.py` is absent from
  this checkout. No new lineage claim was inferred from a config sweep.

## Actual allocator evidence

Two diagnostic executions used the same single-site erasure of the
`stored_entry` register binding; no `ASM_KEEP`-only erasure was repeated.

1. `alloc_explain_site0.json` independently rebound the erased value but
   classified it as global, so its local-only causal layer returned
   `unsupported-global` rather than inventing a diagnosis.
2. `trace_site0.json` retained the underlying trusted global trace. The erased
   value is function-scoped pseudo 90, defined on both predecessor paths as a
   copy of entry pseudo 86 and used once by the slot pointer store. It has
   3 refs, live length 7, allocation order position 4, no preference or copy
   preference, and hard conflicts with `$v0`, `$v1`, and `$sp`; `find_reg`
   consequently assigns `$a0`. The trace labels this a preexisting hard/local
   conflict, not earlier global competition.

The erased compile exposes the bad join shape directly: each predecessor moves
the same entry value to `$a0`, one path jumps over the other move, and the slot
store consumes `$a0`. In the exact base/retail stream there is one
`move $v0,$s3` before the join, the slot store consumes `$v0`, and `$v0`
remains live to function exit.

## Whole-join semantics and callers

Both sides of the source conditional assign `stored_entry = entry`, so the
synthetic phi has no semantic distinction. The function allocates `entry`,
optionally creates and copies the type-0x13 record, always installs that same
entry pointer in the selected slot, and clears the adjacent word.

A registry-selected source scan found only the definition and one direct
caller, `town/func_800A2590` (`set_item_w0`). That caller assigns the result
and returns it. The former `void` definition was inconsistent with that
observed use. The helper prototypes inherited from m2c are not used as
evidence for this conclusion.

### Return-type review

The script dispatcher supplies the external ABI evidence. `func_80039DBC`
calls table entries through a reconstructed four-argument function-pointer
type and saves the return word; `func_80038690` likewise saves the word and
branches on nonzero. `set_item_w0` is developer symbol `FNO_set_item_w0`,
call-table number 135. Those consumers prove a single 32-bit return value and
zero/nonzero behavior, but not a signed C semantic type: a pointer has the same
return-register ABI on this target. Its one ordinary C caller,
`mam_bita_give`, ignores the result. The same readable name in dungeon belongs
to unrelated overlay-local functions and supplies no TOWN prototype.

Inside that boundary the recovered value is an allocated entry pointer: it is
installed in the slot, success returns it, failure returns zero, and retail
leaves that same pointer in `$v0`. The chosen types therefore make
`func_8009FB2C` and `set_item_w0` both return `void *`.
This preserves the native port pointer and the target's 32-bit guest-address
bits without an unnecessary pointer-to-`s32` narrowing. The VM's reconstructed
signed field/function-pointer types remain uncertain and are existing
reconstruction debt: target ABI word compatibility does not by itself prove
ISO C function-type compatibility. Its byte-level word transport and zero test
are compatible with this pointer-or-null contract.

The only ordinary TOWN caller of `set_item_w0`, `mam_bita_give`, now declares
the same `void *set_item_w0(s8, s8, s8, s8)` interface. It ignores the return.
That declaration-only candidate is independently exact at 11/11 words, total
0, from base SHA-256
`11de632e0cd9334259ad9cfaaa1442605d38a14995ddb9553023d16149b86e9f`.

This was the single allowed pointer-return counterfactual. Both halves are
independently exact:

- `town/func_800A23CC`: pointer return, 113/113 words, total 0.
- `town/func_800A2590`: pointer-or-null wrapper return, 30/30 words, total 0.
  Base SHA-256
  `d64bf5d52bd64ffeef3082d23708d6af8ff367f838e7108a0218b7a35a229860`.
- `town/func_800CA9C0`: consistent ordinary-caller declaration, 11/11 words,
  total 0.

## Bounded reconstruction

- Diagnostic erasures used: 2/2 (same register site, explanation then raw
  global trace).
- Predicted reconstructions used: 1/4.
- Reconstruction 1: remove the redundant join local and keep; store `entry`;
  return the entry value. Result: exact 113/113, total 0.
- Semantic type counterfactual: pointer-returning helper and pointer-or-null
  script wrapper. Both rows exact; selected for output.

No production source, configuration, or build-root file was changed here.
