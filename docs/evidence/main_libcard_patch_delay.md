# MAIN private Sony LIBCARD/PATCH delay

Reviewer: **pending**. Identity: `main/func_800219C4`, MAIN file
`[0x2719c4,0x2719dc)`, exactly 24 bytes. This is the unnamed private routine
at `LIBCARD/PATCH.OBJ +0x17c`, not the `_patch_card2` export at `+0x110`.
The existing synthetic symbol names an extent. This conversion makes no new
runtime-placement claim and changes no rowbase or window geometry.

The whole PATCH linked text is MAIN `[0x271848,0x2719e8)`, 416 bytes,
SHA-256 `da6667239d5da39af0582721d7ca40011ec5d51becdb020d3b1c155a8e856634`.
The private extent SHA-256 is
`3ab55a0f1f41698287658ae2491979e94fd9a912f084c47d498560a0ec7e445f`.
Its little-endian instruction words are `3c0e0032 25ceffff 15c0ffff
25ceffff 03e00008 00000000`. The branch at row `+8` targets itself;
row `+12` is its decrement delay slot. The return delay slot is zero.
There are no calls, stack accesses, arguments, or relocations in this extent.

The [original member receipt](main_libcard_patch_original.json) records the
871-byte original LNK v2 member, SHA-256
`db12f78375df9446125b3347b8a353d1b106e7ebfcd689a5052dbebd9e43cbab`.
It contributes 416 `.text` bytes and 16 uninitialized `.sbss` bytes, exports
`_patch_card` and `_patch_card2`, imports `EnterCriticalSection` and `FlushCache`,
and carries 28 relocations. All 60 changed original-vs-linked bytes are in those
fields. A diagnostic relocation replay reproduces 416/416 retail bytes using
`.text=0x80408848`, `.sbss=0x8040923c`, `EnterCriticalSection=0x8007ca38`,
`FlushCache=0x8007c938`. The bindings include retail-derived values; this is
object-provenance consistency, not an independently recovered original link map.
The independently evidenced front-end map places this routine at `0x804089c4`;
this package keeps the established naming/gating map unchanged.

The [catalogue receipt](main_libcard_patch_versions.json) identifies the
whole text in held PsyQ 3.6.10 / 3.6.11 / 3.7 catalogues. PATCH alone cannot
select between those identical versions. Adjacent CARD/INIT/END/PATCH members
have 3.7 as their common tested catalogue. The 4.0 whole PATCH pattern fails
at 162 specified bytes despite containing the same short delay. No source-file
record establishes original assembly authorship; it remains an inference.

The original member was retrieved from the archived Programmer Tools 3.6 disc.
Only bounded sectors were retained, and the entire remote archive checksum was
not verified. The exact library/member hashes, LNK records, catalogue match and
relocation replay are retained by `work/native_lane/r112_sol61_sdk`. See its
`REPORT.md`, `PROOF.md`, and the reproduction in
`work/native_lane/r113_sol61_sdk2/PROOF.md`. No SDK binary is installed by this
package; the generator reads the user's existing MAIN disc container.

`tools/build/main_sdk_asm.py` checks the complete object hash and the private
extent before generating `build_slus/asm/psyq/libcard/main_patch_delay.s`.
It emits mnemonics in retail order under `.set noreorder`, using the existing
SDK `macro.inc`. Both overlay-view creation and SLUS builds regenerate the
twin, including after a fresh SLUS split. The unchanged overlay gate assembles
it through the existing wrapper and proves the complete production
`config/overlays/main_boot.overlay.yaml` window. Whole-object hash validation
also refuses corruption outside the short routine.

The split record now carries `config: platform-asm`, `source_kind: platform_asm`,
and `asm_path: asm/psyq/libcard/main_patch_delay.s`. Its fitted GCC 2.8.0 recipe,
`src/main/func_800219C4.c`, `raw/main/func_800219C4.c`, and live register pin are
retired. The repository registry deliberately excludes assembly from the C
row denominator. This is a one-row / 24-byte reduction in C accounting,
not a C cleanliness promotion. The historical baseline and weak module-group
assignment remain intact for provenance.

The containing object, copied templates, two CFAIL public exports, 16-byte SBSS
and relocation ownership are outside this narrowly bounded conversion. The
new generator is not a whole-object native module integration.
