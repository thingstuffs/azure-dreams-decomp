# cd_control.c: review for complete-TU placement

Reviewed by r99_astra_mod2 on 2026-10-07. This is a supported reconstructed
module grouping; the historical filename and original allocation boundaries
remain inferred. Scope: 3 contiguous functions / 160 bytes in
dungeon, region `xfer_dungeon_A3000`, at the recorded CDK-G0 recipe.

Membership follows the r98 strong module records, contiguous function boundaries,
one recipe, and shared calls/data references. The module manifest pins each
logical ID, source, runtime symbol, file offset and extent. The rowbase record
proves the load delta by DMA capture; the certifier validates all members against
that record and the registry. No per-function placement or sorting constructs
the match: the TU is linked once in emitted order.

## Control_CD ABI repair

The prior two-argument definition omitted the payload consumed in register a2
by func_8003E39C. The latter stores it for selector FF, treats 1 as a flag, and
otherwise copies through a nonzero address. The callers w_80048118 (callback
state) and w_80053CFC (saved payload) corroborate nonzero third-register values.
An ignored third parameter would not model this behavior.

The proposal gives Control_CD an explicit `s32 payload` word and passes it to
EVERY formerly two-argument helper call. It retains explicit zero arguments in
paths that retail clears. A shared header declares s32 return and these same
three parameters. func_8003F320 is void(void), matching its actual definition.
The header's payload word represents both small flags and pointer bits in the
32-bit ABI; it is not a host-pointer-width portability claim.

Fresh baseline and candidate builds of the EXISTING eight-function SLUS CD
physical TU have identical complete function tokens (1041 words), relocation
semantics, and every allocated payload section. Using the existing checked
small-data splitting, Control_CD resolves 528/528 bytes to retail, with zero
masks, in both builds. `overlay_control_cd_abi.json` records the proof. This is
an ABI repair proof, not a new SLUS placement certificate; the SLUS certificate
closure must be refreshed by the integrator. Other legacy caller declarations
outside these two overlay cohorts remain a separate API-cleanup queue.

## External storage ownership

This TU defines no storage. ALL allocated payload must be its enumerated text
sections; nonempty .data/.rodata/.bss/.sdata/.sbss and COMMON are rejected in both
assembler legs. The declarations are external views of the existing resident
retail asset `dungeon:xfer_dungeon_A3000`. The asset owns those bytes in this build;
these text-only modules do not claim to reconstruct the original data object.
No symbol-sized allocation, table endpoint, or original defining TU is inferred
from an unsized extern or a nearby label. In particular the indexed descriptor
array's view is a fingerprint sample, NOT an asserted full array bound.

The addresses below map through the proven region delta and are disjoint from
the module's code. The descriptor pairs are eight-byte input records: Control_CD
case 6 reads the second word. The one-byte state in dungeon has other readers
and writers, including func_800A40CC, outside this cohort. Town's map and test
arrays keep their existing s32/s16 views. The test array includes its -1 sentinel.

| symbol | file offset | fingerprint view bytes (not allocation size) | retail bytes |
|---|---:|---:|---|
| D_800DCF4D | 0xF77ED | 1 | ff |
| D_800DF3DC | 0xF9C7C | 8 | 00 50 82 02 69 60 00 00 |
| D_800DF3E4 | 0xF9C84 | 8 | 00 50 02 04 6e 60 00 00 |
| D_800DF3EC | 0xF9C8C | 16 | 00 60 0f 06 b3 3f 00 00 00 60 0f 01 98 42 00 00 |

The manifest binds these import views to the resident asset, and the certificate
fingerprints their bytes plus the load map. Changing the asset invalidates the
proof. Linking these imports as absolute addresses does not grant ownership of
any data to this module, and no storage is placed through NOLOAD. The complete
window gate retains ordinary fallback storage and neighbouring C compilation.
A later source-backed data owner must replace the asset intervals explicitly.

## Remaining source contracts

The module bodies and integer widths are preserved. Existing non-prototype
minigame handler declarations remain open-arity legacy imports; this review does
not invent prototypes or identify a banked handler solely by its RAM address.
No mutually incompatible declarations remain within either TU. The known shared
Control_CD/func_8003F320 contradiction is repaired at definition and caller.
Unknown historical names and broader API modernization are not placement claims.

## Acceptance

The executable certifier requires exact complete-TU genuine ASPSX 2.79 and linked
retail bytes, all affected production windows, one physical edge per cohort,
complete imports/functions/allocated sections, and unchanged input fingerprints
before and after the build. The levels reader only accepts those fresh proofs;
it leaves all lower-level, pin, tail-call and source-residue predicates intact.
