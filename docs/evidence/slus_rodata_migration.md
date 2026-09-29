# SLUS rodata migration: switch rows own their jump tables

Lane `r80_opus_slusrodata` (2026-09-29). Seven SLUS rows whose computed-goto dispatches became honest
`switch` statements now own their compiler-emitted jump tables. The complete SLUS links to the retail
SHA-1 `e6bfbb95ff6676899e077481221d73ddd4d3bf52`, both for each row alone and for all seven together.

## Problem

The retail executable has the PsyQ layout, with `.rdata` placed first. Splat's `[0x800, bin]` segment
covers VMA 0x8002D000-0x80033360 and holds every TU's read-only data, jump tables included. It is linked
as one `build/assets/800.o(.data)`.

A computed-goto row reached its table through an absolute `jtbl_<ADDR>` symbol from splat's
`undefined_syms`. A `switch` instead emits the table into the TU's own `.rodata`. The ordered linker
script had no slot for that section, so the sw23 landing (2026-09-29 08:53Z) failed to link the SLUS.
Until now, `tools/verify.py` passed these rows only through its text-identical fallback.

## Mechanism

1. **Ownership.** Each row gets an owner module in `config/slus_modules.json`: `jtbl_<row>`, whose
   source is `src/slus/<row>_jtbl_owned.c` (a wrapper, `#include "<row>.c"`). Its single member keeps its
   row ID, canonical source and recipe. Its data records have `section: ".rodata"`, `asset:
   assets/800.bin`, and the retail offset, size, VMA and bytes. Multiple records must be contiguous, as
   in w_8005F134's two tables.
   - `tools/build/slus_modules.py` now accepts exactly `.rodata`. Named `.rodata.*`, `.rdata` and `.data`
     are still refused.
   - The existing carve (`plan_asset_carves`, `rewrite_ordered_linker_script`) splits `800.o` around each
     table and places `build/src/<row>_jtbl_owned.o(.rodata)` there. The `_800` output section is already
     `SUBALIGN(1)`, so no padding is inserted.
   - `filter_owned_symbols` removes the absolute `jtbl_` assignment. Nothing else referenced it.
2. **Section-end padding.** `mipsel-linux-gnu-as` rounds each section's size up to its alignment
   (`md_section_align` does this for a non-"elf" TARGET_OS). ASPSX/psylink did not, and retail shows it
   twice:
   - w_8005F134's 60-byte span is followed at 0x800332B8 by LIBETC VSYNC's `"VSync: timeout"`.
   - w_80052144's 20-byte table at 8002EFDC is followed directly by 8002EFF0.

   Retail does apply `.align 3` relative to the section start: w_8005F134's second table is at +32,
   after a zero pad word.

   `tools/build/slus_rodata_trim.py` runs as a post-assembly step through the cc rule's existing
   `$data_piece_step` hook, which `configure.py` wires for each `.rodata` owner. It rewrites only
   `sh_size`, cutting back to the manifest span. It is fail-closed: the cut must be all zero, shorter
   than the section alignment, and hold no relocation or symbol. `configure.py` refuses a module that has
   both `data_pieces` and `.rodata`.
3. **Retail scoring.** `aspsx_diff.resolve_tokens` and `retail_compare` take `section_anchors`.
   `rodata_anchors(module)` supplies the owner's manifest VMA for its symbol-less `.rodata`. A
   named-symbol anchor that disagrees with it keeps the word masked. Member HI16/LO16 references to the
   table therefore resolve against retail words with zero masks.
4. **Ownership proof.** `prove_slus_ownership.prove_data` has a `.rodata` branch, `prove_rodata`. The
   initialized-data proof cannot apply: the table is a compiler-local label and its object bytes are
   unrelocated. The branch requires:
   - the object `.rodata` equals the owned span exactly and defines no symbol;
   - every relocation is `R_MIPS_32` into a member function, within its extent;
   - every other word is `.align 3` zero padding;
   - the `ld -Map` placement, taken from a relink of the gated view whose ELF must be identical, equals
     the first record's VMA and the span;
   - each linked table word equals the member function's linked address plus the relocation addend;
   - the member's HI16/LO16 reference, resolved from the linked image, addresses the table's VMA;
   - the linked bytes equal the retail record bytes;
   - no absolute or linked `jtbl_` symbol survives.

   `certify_slus_module` grants L4 placement and checks no data bytes, so it needs no branch. It refuses
   these owners because they have no shared header of their own. They carry data ownership only.

The module fingerprint includes the trim implementation for `.rodata` owners, as it already includes
the data-piece splitter. `aspsx_diff.tool_fingerprint` lists `slus_rodata_trim.py`.

## Rows

| row | owner module | table VMA(s) | owned span | table words | pads | retail compare: maspsx diff/masked; genuine 2.79 |
|---|---|---|---|---|---|---|
| w_80042BDC | jtbl_80042BDC | 8002D67C | 128 | 32 | - | 0/0; exact [0,0] |
| w_8004CECC | jtbl_8004CECC | 8002E5F8 | 24 | 6 | - | 0/0; exact [0,0] |
| w_800517CC | jtbl_800517CC | 8002E964 | 32 | 8 | - | 0/0; exact [0,0] |
| w_80052CE0 | jtbl_80052CE0 | 8002EFF0 | 32 | 8 | - | 0/0; exact [0,0] |
| w_80054F9C | jtbl_80054F9C | 80032E14 | 144 | 36 | - | 0/0; exact [0,0] |
| w_80057A94 | jtbl_80057A94 | 80032EA4 | 92 (as: 96) | 23 | - | 0/0; exact [0,0] |
| w_8005F134 | jtbl_8005F134 | 8003327C, 8003329C | 60 (as: 64) | 14 | +28 | 0/0; exact [0,0] |

- **w_8005F134.** Its four pins fell with the switch. The single scorer word the lane saw (`lw v0,32(at)`
  against retail `0(at)`) was only relocation spelling. Once the table is placed, `.rodata+32` is
  0x8003329C.
- **w_80057A94.** It owns 92 bytes, and the retail zero word at 0x80032F00 stays in the shared blob.
  That word is consistent with w_80057A94 and w_80057D20 having been one retail TU (relative
  `.align 3`). The same pattern holds for w_8005EDA0 and w_8005F134. This is a TU-boundary hint and is
  not claimed here.

## Receipts

The production ownership receipt is written at landing to
`docs/evidence/slus_rodata_migration/ownership_receipt.json` (see LANDING.md in the lane). The lane
measurements it reproduces are in `work/native_lane/r80_opus_slusrodata/results/`:

- **Isolated gates.** `gate_<row>.json` for each of the 7 rows and `gate_joint7.json` are SHA-1 MATCH.
  Each is a fresh copy of build_slus with only that row migrated, and records the map placement.
- **Ownership.** `receipt_joint7.json` and `dry_ownership_receipt.json` hold the production prover's
  output (`prove_slus_ownership.py` on all seven owners) after a `--fresh` build of the patched tree.
  All seven rows are "direct genuine and retail exact". The `.rodata` proofs record the placements,
  table words, pads and text references.
- **Negative controls.**
  - w_80054F9C with `case 16:` changed to `case 17:` has the same code and a different table. The SHA-1
    gives NO MATCH at 2 image words, 0 function words. `prove_rodata` on those real objects refuses with
    "linked table bytes differ: jtbl_80032E14".
  - w_8005F134 without the trim gives NO MATCH: 4 bytes at 0x800332B8.
- **Unit tests.**
  - `tools/tests/test_slus_rodata_owner.py` (8): trim positive and negatives; carve, bytes and section
    refusals.
  - `tools/tests/test_slus_ownership_rodata.py` (10): prover acceptance; case-17-style table refused;
    link context required; surviving symbol refused; object-shape, placement, resolution and
    text-reference refusals; map parser; retail anchor; certifier boundary.
- **Split ledger.** `ledger/splits/slus.jsonl` is unchanged. The logical edges project back to the same
  884 rows, so only `ledger/splits/slus.build.ninja` is repinned. Its diff is limited to the seven moved
  TUs, the `800.bin` carve chunks and the link input list.
- **Row verification.** After landing, `tools/verify.py slus/<row> src/slus/<row>.c` routes each member to
  the whole-image module gate: exact for all seven. The case-17 candidate reads `exact=False` ("2 image
  words differ"). Note that its function residue `total` is 0, because the difference lies in the
  table, not the text.
- **Ledger effect.** After `tools/levels.py`, `computed_goto` leaves the L5 residue of all seven rows,
  and w_8005F134 goes from 4 pins to 0. Pin sites go from 2,493 in 696 rows to 2,489 in 695 rows.
  `not_in_module` stays, because this is data ownership without a placement grant.

