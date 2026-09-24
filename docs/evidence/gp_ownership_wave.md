# SLUS data ownership wave, 2026-09-24

Eighteen more GP-dependent rows now have ordinary C definitions for their small
shared data. The complete SLUS image remains retail-exact. Fresh verification
covers 781 function words and 24 newly owned data symbols, with zero masked
relocations and no compatibility passes firing in these rows. The dependency
ledger falls from 223 to 205 records; the original GP cohort falls from 56 to 38
remaining rows. The assembler's global extern model is still unchanged.

The authoritative result is [gp_ownership_wave_receipt.json](gp_ownership_wave_receipt.json).
It records a fresh complete-image gate, the pinned recipe hash, per-module source
fingerprints, exact object section bytes, object symbol offsets, linked non-ABS
addresses, and genuine ASPSX 2.79 plus retail equality for every member. Symbols
emitted as NOTYPE have no object-level size metadata; their extent is checked by
the typed definitions, exact section length/bytes and adjacent symbol offsets.

## Current ownership, not recovered original files

| Ownership unit | Rows | C-owned data |
|---|---:|---|
| `entry_words` | `w_800508F0` | `D_80080B80`, `D_80080B84`: two initialized `s32` words |
| `render_words` | `konami_runtime_w_80035888` | `D_800809B8`, `D_800809BC`: two initialized `s32` words |
| `owned_80035484` | `konami_runtime_w_80035484` | `D_80081440`: null pointer |
| `owned_80038A10` | `konami_runtime_w_80038A10` | `D_80081448`: typed null pointer |
| `owned_80044698` | `w_80044698` | `D_80080B00`: zero `u16` |
| `owned_800448BC` | `w_800448BC` | `D_80081508`: typed null pointer |
| `owned_8004713C` | `w_8004713C` | `D_80080B08`, `D_80080B0A`: zero `s16` values |
| `owned_80047338` | `w_80047338` | four zero `u16` values at `D_80081518` through `D_8008151E` |
| `owned_80047468` | `w_80047468` | four zero `u16` values at `D_80081520` through `D_80081526` |
| `state_defaults` | `w_8004D614` | four `s32` values at `D_80080B58` through `D_80080B64`: 0xFD80, 0, 0, 0x400 |
| `slot_transition` | `w_80041AE4`, `w_80041B98`, `w_80041BE4`, `w_80041C64` | `D_800814E8`: zero `s16` slot index |
| `slot_transition_secondary` | `w_80043D04`, `w_80043DB8`, `w_80043E04`, `w_80043E60` | `D_80081500`: zero `s16` slot index |

The manifest describes present ownership reconstructions. It does not establish
original source filenames or historical translation-unit boundaries. Single-row
aggregators own data while retaining the canonical row fragments and their IDs.
Pointer definitions follow their fragment where the existing row-local type must
be in scope. No duplicate tentative definition, section attribute, new pin, or
artificial source dependency supplies storage.

The two four-function groups have direct callback transitions and a shared slot
index within each group. Their existing common layouts and declarations now live
once in `include/slus/slot_transition.h`; the header is shared by both groups.
`func_8003F794`'s two `s16` parameters follow its current definition, replacing
conflicting per-row prototypes. Its backward scan from slot 7 supports the
existing eight-element slot-table bound. `D_80082E6E` becomes an incomplete byte
array, replacing declarations explicitly padded to force an addressing mode.
The shared state declaration preserves the existing larger observed prefix in
place of one row's short artificial padding. Unproved field meanings remain
address/offset names; existing volatile declarations are retained.

These changes prove data ownership and code fidelity. **They do not grant L4
placement** to the twelve new units. Broader source-map and type review remains
separate; no new module-placement certificate has been written for them. The
previous `runtime_directory` pilot is recertified against the changed build and
keeps its independently reviewed placement. All 884 logical rows remain; the
two additional four-function groups reduce physical C compile inputs to 876.

## Compiler and link evidence

Explicit zero initializers are supported by the held compilers: the measured
`= 0` pointer/halfword/word definitions occupy initialized `.sdata`. The earlier
inventory's possible `.sbss` obstacle is superseded by these actual compilations.
There is no need to manufacture nonzero padding or add a section attribute.

At `w_8004D614`'s former 2.8.1 recipe, real data ownership removes the GP mismatch
but leaves a two-word genuine/retail epilogue difference. CDK emits all 31 retail
words exactly. The two shared-slot groups likewise use one verified
`2.7.2-cdk -G16` recipe each. Nine recipe changes passed the existing lander and
SLUS gate: eight were byte-neutral at the target recipe; `w_80043E60` required
its corrected shared-state declaration under the authorized coherence rule.
The matrix receipts under [gp_ownership_wave/](gp_ownership_wave/) preserve the
trial-cell comparisons. The lander recorded trades and refreshed raw object
baselines before the physical module regrouping.

The original linker output uses `SUBALIGN(4)`. Splitting one raw asset around a
two-byte C datum created a new boundary, and this directive inserted two bytes
before the suffix. The code and owned symbol address were exact but the rest of
the image shifted. `rewrite_ordered_linker_script` now changes only the containing
output section to `SUBALIGN(1)` when a new internal boundary violates the old
alignment. Existing word-aligned carves and unrelated output sections retain
their directives. A real MIPS assembler/linker regression fixture proves exact
4-byte prefix + 2-byte datum + 14-byte suffix reconstruction; both complete
shared-slot builds and the integrated image then match retail.

## Repeat the proof

```sh
flock build_ovl/work/land.lock \
  python3 tools/fidelity/prove_slus_ownership.py \
    entry_words render_words owned_80035484 owned_80038A10 \
    owned_80044698 owned_800448BC owned_8004713C owned_80047338 \
    owned_80047468 state_defaults slot_transition slot_transition_secondary \
    --output work/native_lane/gp_ownership_wave/recheck.json
```

This builds a fresh private SLUS view and checks the live manifest/recipe/source.
It refuses any mismatched section bytes, symbol placement, member comparison,
masked relocation or input change. Its receipt deliberately supplies no L4
placement. `tools/fidelity/probe_slus_module_build.py` also preserves all other
active modules while replaying the original pilot's positive, sibling-negative
and recipe-conflict checks.

## Remaining investigations

Two additional zero-data candidates were withheld: `w_80047E78` and `w_80053CFC`.
Their expected `.sdata` bytes were present, but address-of emission changed,
shortening each function by four bytes and failing the full image gate. The
[47E78](gp_ownership_wave/address_of_80047E78.json) and
[53CFC](gp_ownership_wave/address_of_80053CFC.json) receipts retain the failures.
Those full-image word counts include layout shifts; they are not independent
source-instruction mismatch counts. A follow-up using the **unchanged retail-exact ELF** for relocation anchors
corrects the 47E78 diagnosis: genuine ASPSX emits all 29 retail words exactly,
whether the C definition precedes or follows the function. Stock maspsx/GNU as
instead makes the address load GP-relative and emits 28 words. Thus this case is
assembler-owned, not a C reconstruction failure. The existing experimental
correction (GNU as `-G0`, with maspsx selecting actual small-data operations)
restores all 29 retail words with zero masks. See the
[retail-anchor comparison](gp_ownership_wave/address_of_80047E78_retail_anchor.json),
[generic-correction comparison](gp_ownership_wave/address_of_80047E78_generic_correction.json)
and [ordinary candidate C](gp_ownership_wave/address_of_80047E78_candidate.c).
The earlier failing-build receipt used that shifted ELF's addresses, so its
per-function genuine/retail distance is not the authoritative retail comparison;
its failed full-image gate remains valid. The
[follow-up ownership proof](gp_next_ownership.md) supplies the 53CFC retail-anchor
check and fixes its conflicting padded asm alias in private C. Both address-taking
owners now pass genuine and full-image checks with the experimental correction.
Neither candidate is activated: the global correction and
full linked proof must be prepared together before the remaining sign-off.

The remaining shared GP cohorts still include mixed recipes, overlapping data
views and noncontiguous storage. Their graph is an investigation aid, not proof
that all consumers belong in one original translation unit. No global GP switch
or compatibility-pass deletion has been made by this wave.
