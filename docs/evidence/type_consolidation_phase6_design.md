# r78 type consolidation phase 6 - design

Model: claude-opus-5-5[1m]. Lane: work/native_lane/r78_types_p6. Nothing under src/, include/, config/, tools/ or
ledger/ was edited; apply6.sh lands everything under build_ovl/work/land.lock (payload6/, cand6/).

## 1. SLUS link definitions for data symbols only C names (tools/build/configure.py C_SYMS)
Measured: build_slus.sh reconfigures only with --fresh; the SLUS link takes LDSCRIPTS = undefined_funcs +
undefined_syms.modules (splat's undefined_syms filtered of module-owned data).  splat writes only symbols its
disassembly names, so an address that only C names (a shared include/shared/ header) has no definition.
- New checked-in linker script config/slus_006.14.c_syms.txt: one `D_<ADDR> = 0x<ADDR>;` per symbol, /* */
  comments only (no splat parsing, so no `key:value` hazard).  Contents: D_8006CCD8 / D_8006CCE8 (dirStepX/Y),
  D_80082E80 (TileObject), D_80083498 (ObjectNodeHeader) - every shared-header object the SLUS link lacked.
- configure.py (+26 lines after the MODULES block): when the file exists, validate each line (name spells its own
  address; a module-owned symbol is refused - an absolute assignment would override the module's real object) and
  append it to LDSCRIPTS.  os.path.exists is False on a dangling link, so without the file the recipe is byte-
  identical (measured: unpatched and patched-without-file configure both reproduce ledger/splits/slus.build.ninja).
- mk_slus_root.sh: the file joins the config symlink loop (SlusView copies with symlinks=True, so verify.py's
  partition/module gates see it).
- Recipe effect (measured in a scratch copy of build_slus): exactly 4 changed lines - the link rule command gains
  `-T config/slus_006.14.c_syms.txt` and the .elf link edge gains it as an implicit dep; row_db.slus_edges
  identical (no cc edge changes); ninja relinks; image SHA-1 OK; nm shows the four absolutes.  A same-value
  duplicate with undefined_syms (a later split naming the address) links (tested with D_80083160); a malformed
  line stops configure with the line number.
- apply6 regenerates build_slus/build.ninja (configure.py in the view root, as land_recipe_move.py does), refuses
  any diff outside those two lines or any cc-edge change, then re-pins ledger/splits/slus.build.ninja; the SLUS
  gate must then record MATCH with recipe_vs_pinned identical (verify.py rebaseline and the module-evidence tools
  key on that).  Future C-only symbols are one line in the config file: no recipe change.

## 2. The phase-5 open item dissolves: D_80082EC0 is its own object, TileObject ends at 0x40
The three excluded SLUS rows failed because their phase-5 candidates respelled D_80082EC0 (already in the SLUS
undefined_syms, links today) as `(int *)&D_80082E80.unk_040`.  Evidence that 0x80082EC0 is a separate object:
slus code2 func_8003F7E4 clears all 128 words of D_80082EC0; w_8003D8B0 passes it with count 0x80; w_8003F80C
stores `(addr & 0xFFFFFF) | (width << 24)` into it (a 0x200-byte table, 0x80082EC0..0x800830C0).  The census's
only +0x40 / +0x140 "TileObject" accesses were exactly w_8003F80C's two stores into that table (address-range
regex); no TileObject row reaches past 0x38.  So:
- tile_object.h: unk_040 / pad_044 / unk_140 / pad_144 removed; TileObject ends at 0x40 (the table bounds it).
  The size change 0x144 -> 0x40 only moves `.extern D_80082E80,<size>` (above every -G in use): 8 rows show it,
  all verify-exact.
- w_8003D8B0 / w_8003F80C are NOT landed (they keep `extern int D_80082EC0[128]`, correct as they are).  Do not
  re-run apply5 for them: after phase 6 their phase-5 candidates no longer compile (unk_040 is gone).
- w_8004D614 (D_80083780 only) was collateral of the whole-image partition link: landed here, verify.py exact.

## 3. record_ptrs.h onto EntityRec; retire Rec_D_800814A8.h
record_ptrs.h: `struct EntityRec; extern struct EntityRec *D_800814A8, *D_800E3D7C;` (D_80016000 keeps its
generated record).  The 159 rows still including Rec_D_800E3D7C.h / Rec_D_800814A8.h used the names only in the
#include and comments (phase 5 had already rewritten the code), except three: func_80E11860 (a parameter typed
`Rec_D_800E3D7C *` with no member access -> EntityRec *), func_81334954 (entity.rewrite + one
`*(unsigned char *)&...->unk_84 = 0x80` cast at the use: EntityRec's unk_84 is signed char, retail loads li 128),
func_8133AD74 (reads D_80083780 through the generated volatile view `at00_vs32`: exposing it would grow the
row's scaffolding, so it keeps the include).  Hence Rec_D_800814A8.h is retired (apply6 deletes it and its
ledger/records.json entry only when nothing includes it after landing); Rec_D_800E3D7C.h stays for func_8133AD74.
Header-update gate: apply6 verifies every landed row AND every row including tile_object.h / record_ptrs.h /
object_node.h (1,068 rows at dry run).  In the lane all of them were checked against the lane headers: 829
header includers (cc1 listing identical to the current src's; the 8 whose `.extern D_80082E80` size moved and the
hand rows also verify.py exact), the 277 D_80083498 rows by verify.py (drive3).

## 4. D_80083498 = ObjectNodeHeader (include/shared/object_node.h)
- slus/w_8003FD64 func_8003FD64(flags, head) is the node allocator: clears 0x49 words, links the node at *head
  (node->next = *head; *head = node; node->pprev = head), +0x1E = flags | 0x4000, +0x0C/+0x08 payload cursors.
- 265 dungeon/town rows pass D_80083498 as that head (its word 0 is a node's next slot); town/func_800C438C clears
  bit 0x2000 at +0x1E and hands &D_80083498 to func_8004EE50 (object task).  So 0x80083498 is a node header:
  next / pprev / flags named from func_8003FD64, the rest unk_.
- D_800834B8 (= +0x20, the record half) stays separate: town rows form the base AT 0x800834B8 and reach the header
  at -0x18/-0x14/-0x10, i.e. retail declared the record separately there.  (0x20 + sizeof(EntityRec) = 0x14C lands
  exactly on D_800835E4, but pool nodes are 0x124 bytes, so "header + EntityRec" is not claimed.)
- Not named from docs/SYMBOLS.md's script slot 26 V_item_type_data -> 0x80083498: an item-type table does not fit
  a list-head node; the address stays D_.
- drive3 with objects/D_80083498.json: 277 rows exact (257 natural, 20 with the typed local-pointer fold), 4 miss
  (3 town build errors on local TownState views, dungeon/func_800ACC98 at 2.6.3 by 8), 51 refused (48 census rows
  that only name the neighbours D_800834B8 etc., 2 without a local declaration, 1 reaching +0x20).
- Pins: pins2 over the 73 pinned migrated rows: no pin freed.  Tasks 1-2 change no cc1 listing, so they cannot
  free a pin.
