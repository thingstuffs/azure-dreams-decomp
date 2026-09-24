# Runtime count and shared display slots: C data ownership

Two additional ownership units recover real C storage for three GP-dependent
SLUS rows. `konami_runtime_gp_count` owns `D_80081460` for `func_8003C6F8`;
`gp_shared_slots` owns six globals used by `func_8003CB08` and
`func_8003CCB0`. The latter functions have a direct call relationship and share
the animation/display state. This establishes present ownership and an exact
reconstruction, not historical translation-unit boundaries or L4 placement.

The canonical function fragments and their existing pins are unchanged. Both
units retain their registered `2.7.2-cdk` recipe. Ordinary initialized C
definitions follow the included fragments; no assembler exceptions, section
attributes, artificial padding globals or duplicate storage are introduced.

| Symbol | C type | C bytes | Asset carve bytes |
|---|---|---:|---:|
| `D_80081460` | `void *` | 4 | 4 |
| `D_80080AA4` | `s16` | 2 | 2 |
| `D_80080AA6` | `u16` | 2 | 2 |
| `D_80080AA8` | `u16` | 2 | 2 |
| `D_80080AAA` | `u8` | 1 | 2 |
| `D_80080AAC` | `s16` | 2 | 4 |
| `D_80080AB0` | `void *` | 4 | 4 |

All initial bytes are zero. The shared unit emits a 16-byte `.sdata` section:
13 bytes of typed storage and three bytes of normal compiler alignment padding.
The manifest's `size` describes each carved span, including trailing alignment
before the next symbol; it is not a claim that the byte at AAA has type `u16`
or that the halfword at AAC has type `s32`. Exact section bytes, total length,
symbol offsets and linked addresses are checked together. No other named
storage in those three alignment bytes is claimed by this reconstruction.

`D_80080A6C` remains owned solely by the existing `runtime_directory` pilot.
The count function continues to access that external symbol. Its new count
pointer has separate C storage at the retail address. The private experiment
also rechecked the pilot's three functions and four GP-relative accesses.

The production proof is [gp_count_and_slots_receipt.json](gp_count_and_slots_receipt.json).
It checks a fresh complete image, the pinned build recipe, genuine ASPSX 2.79
and all 402 retail function words with zero masked relocations, exact owned
data bytes and non-absolute linked symbol addresses. The full image SHA-1 is
`e6bfbb95ff6676899e077481221d73ddd4d3bf52`. The build preserves all 884 logical
rows with 875 physical C inputs. This removes three dependency records:
205 to 202 overall, and 38 to 35 in the remaining GP cohort.

```sh
flock build_ovl/work/land.lock \
  python3 tools/fidelity/prove_slus_ownership.py \
    konami_runtime_gp_count gp_shared_slots \
    --output work/native_lane/gp_count_and_slots/recheck.json
```

The private candidate and additional pilot checks are reproducible with
`work/native_lane/gp_count_and_slots/probe.py` against its original 13-module
snapshot; its retained receipt records that pre-landing state. Current-state
rechecks should use the production command above. No global assembler semantic
switch, pass removal or new module-placement certificate is part of this change.
