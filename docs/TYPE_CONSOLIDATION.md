# Type consolidation (started 2026-09-28)

Owner rulings, 2026-09-28 (binding until revisited - "nothing is set in stone"):

1. **Consolidate.** The decompiler's per-function view structs (`S_800B0870_0 /* arg0 in func_800B0870 */`,
   `unk_XX` fields) and globals spelled as several `D_<addr>` symbols become shared, named game types.
2. **Naming.** Name a type or field when confidence is relatively high; a wrong name can be revisited. An unknown
   may stay `unk_XX` or get a descriptive name that makes the code easier to follow, never a name that asserts
   something it is not.
3. **Scope.** A type or global used by several binaries (SLUS, main, town and dungeon overlays) has one shared
   definition across all of them; the binaries are separate only for PS1 RAM/architecture reasons.
4. **Unions.** "Accessed as both" unions are resolved to the true field type where evidence allows.
5. **Pilot first**, then scale from measured cost and fallout.

Constraint: every touched row stays byte-exact through the normal gates. Types change codegen (signedness, alignment
and aggregate copies, alias/MEM_IN_STRUCT dependence, and shared `%hi` bases for fields of one object versus
separate symbols), so each row is verified individually; retail's own address-formation pattern is evidence of
how the original declared an object.

Baseline (2026-09-28): 276 local address-named typedefs in 223 files (259 distinct layouts), 102 shared
`include/records/Rec_*` headers, 3,140 rows referencing an address-named type; three opaque shared types in
include/game.h. Most-referenced globals: D_800814A0 (723 rows, all binaries), D_80083228 (578), D_80083460 block
(538 + 196 + 171 via separate symbols), D_80083160 (403, all binaries), direction step tables D_8006CCD8 /
D_8006CCE8 (231).

Pilot: `work/native_lane/r78_types_pilot/` (Opus) - the direction step tables (data-symbol naming mechanism) and
the 0x80083460 global block (struct consolidation). Results and the scaling recommendation go here when it lands.

Visual before/after (illustrative until the pilot lands; republished with verified code afterwards):
https://claude.ai/artifact/LA63o6jeL9Xc5hHTXuw6LZ - page source kept at docs/evidence/type_consolidation_preview.html

## Pilot result (2026-09-28): landed

243 rows consolidated (20-row sample first, then 223), every row verify-exact, 179 overlay windows + SLUS SHA-1
image MATCH, pins unchanged or lower (2,875 / 748 after). Design: evidence/type_consolidation_pilot_design.md;
per-row report: evidence/type_consolidation_pilot_report.md; apply script: work/native_lane/r78_types_pilot/apply.sh.

- **Mechanism:** readable DATA names are ordinary `config/names.tsv` rows (addr, D_ name, readable name):
  tools/build/ccproc.py (gates, SLUS) and tools/gate/match.py (scorer) spell them back to `D_<addr>` before the
  assembler, so every binary links the same address. `apply_names.py` refuses data rows today (no defining row);
  a `--data` mode is the tidy follow-up.
- **Headers:** `include/shared/<object>.h`, plain C types, no includes; only migrated rows include them (not
  common.h yet: local typedef names collide, e.g. `DungeonStatus` is already a local type in func_8028B110).
- **dirStepX / dirStepY** (`short[8]`, x/y grid step per direction 0..7): 225/229 rows exact (215 natural
  `dirStepX[i]`, 10 need a `(u16 *)` / byte view where retail reads unsigned or by byte).
- **DungeonGlobalStatus dungeonStatus** (0x80083460, 0x20 bytes): one object (527 rows form one lui/addiu base);
  `flags` (+0x02, bit tests only); the +0x0A union resolved to `short` (797 vs 786 rows exact); other fields
  stay `unk_XX` with access counts. Whole population: 797/857 rows exact automatically; every miss is a
  pointer-cast array view.
- **Codegen rule measured:** plain struct field access reproduces retail's %hi pattern everywhere; cast array
  views (`((T *)&g)[i]`) miss. Not "struct vs separate symbols".
- **Next:** a generator rewriting `D_base[i]` / `((T *)&g)[i]` into the field (clears most of the 60 view misses);
  next objects D_800814A0 (watch -G8 $gp), D_80083228, D_80083498, D_80083160. Two coherence repairs found
  (dungeon/func_800A065C ASM_KEEP, func_800A4DA8 do-while(0)): texts in the pilot lane's hand/pin/.

### Does consolidation remove pins? (measured 2026-09-28)
Directly, barely: t2_pins / t63_memdep / t86_symaddr over the 94 consolidated rows that still carry pins (633)
applied nothing (noop/refused); of the pilot's two reported pin repairs, dungeon/func_800A065C is retail-exact at
2.7.2-cdk (cell_retail_check: maspsx and genuine ASPSX, 0 words) and landed as a coherence trade (1 pin), while
dungeon/func_800A4DA8 is NOT (8 words vs retail at cdk: genuine == maspsx != retail) and was not landed.
Indirectly, yes: many round-78 pin removals were typed spellings (symbol arrays, real struct fields, shared
bases, unsized array externs); shared types give future pin lanes those spellings ready-made. Pin lane briefs
should point at include/shared/ once more objects are consolidated.

## Phase 2 (2026-09-28): landed

1,382 rows (44-row cross-binary sample first), every row verify-exact, 734 overlay windows + SLUS SHA-1 MATCH,
pin-neutral (256 migrated pinned rows re-tested: no pin became removable).
- **dungeonStatus** finished: 845 rows total (669 pure field accesses, 26 keep a cast at the use, 130 keep m2c's
  local-pointer idiom - the next generator step). Not migrated: func_8008629C, func_80CEAF2C (miss), and five rows
  without a local declaration. New evidence: func_800CCA6C masks unk_10 with 0x7FFFFFFF (bit 31 is a tag).
- **ObjectFlagBlock objectFlagBlock** at 0x800814A0 (include/shared/object_flags.h), 681/724 rows: `flags`
  is ORed with 0x8000 whenever an object header gets its 0x8000 mark. Declared size bound to 9..16 bytes by
  per-row evidence (-G8 rows need > 8, -G16 SLUS rows need <= 16). 0x800814A8 stays its own symbol (retail
  declared it separately: 23 of 38 functions using both miss as a field).
- **Decision taken (owner away, revisitable):** 22 rows (SLUS stock 2.7.2 -G0, MAIN, TOWN) only match against a
  SCALAR `int` at 0x800814A0 - the original declared that address two ways. They keep `extern int D_800814A0;`
  rather than a second readable name for one address (list: work/native_lane/r78_types_pilot/scalar_rows.txt).
- **Tools:** tools/consolidate/consolidate.py (one spec per object in tools/consolidate/objects/*.json: maps
  S[k], scalar S, *S, &S and local view-typedef members onto fields; casts only where sign/int-pointer disagree)
  and drive3.py (several objects in one verified text). Apply scripts: the pilot lane's apply.sh / apply2.sh.
- **Next objects:** D_80083228 (578 rows), D_80045340 (442), D_80083160 (403, all binaries), D_80016000 (313),
  D_80082E80 (290), D_80083498 (284, passed by address), D_800814A8 (236), D_800E3D7C (199), D_80083780 (177).

## Phase 3 (2026-09-28): landed

1,487 rows (40-row sample across all five binaries first), every row verify-exact, 834 overlay windows + SLUS
SHA-1 MATCH, pin-neutral (350 migrated pinned rows re-tested; one pin, dungeon/func_80DE9000's
`arg3_part ASM_REG("17")`, is byte-exact erased on the tree text anyway - landed separately).
- **Local-pointer fold** (`consolidate.rewrite_pointers`): m2c's `u8 *s = &var; ((V *)s)->m` becomes `var.field`
  (direct) or `Type *s = &var; s->field` (typed); refused for register-pinned, address-taken or reassigned pointers.
- **GameWork gameWork** at 0x80083160 (include/shared/game_work.h), 0x200 bytes, one object used by every binary:
  967 rows. It absorbs D_80083228 as `gameWork.viewAngle` (0x0C8): read-only, added to an object's angle to pick its
  8-way directional sprite (the view's rotation); as a stand-alone scalar 60 rows miss, as the aggregate 575/576
  are exact. Other fields stay unk_ with access counts. game.h's S_80083178 is gameWork + 0x18 (D_80083178, 69
  rows) - folding it in is the next step.
- **D_80045340 was code, not data**: a function passed as a callback to func_8004491C by 442 rows; they now name
  `func_80045340` with one shared prototype (include/shared/slus_callbacks.h). 434/442 exact.
- Not migrated: 36 non-exact rows (mostly SLUS 2.7.2-cdk rows declaring `void *D_80083160[3]`), 147 rows keep a
  `(u8 *)&gameWork` view pointer the fold could not take.
- **Next objects:** D_80083178 (69, fold into GameWork), D_80016000 (313), D_80082E80 (290), D_80083498 (284),
  D_800814A8 (236), D_800E3D7C (199), D_80083780 (177), D_800E2970 (91), D_80013714 (81).
- Totals after phase 3: 3,112 row migrations onto 5 shared headers (dir_step, dungeon_status, object_flags,
  game_work, slus_callbacks).

## Phase 4 (2026-09-28): landed

763 rows (40-row sample first; 11 SLUS rows that differ from their pinned object only in relocation symbol names -
e.g. `D_80083160+24` for `D_80083178` - landed via the image gate + per-row rebaseline, as land_slus_rebaseline.sh).
- **S_80083178 folded into GameWork** (gameWork + 0x18): 66/69 rows. state_94's four s16 xyz vectors are gameWork
  0x0AC..0x0CB and v[3].z is viewAngle. game.h's S_80083178 stays for now: blocked by dungeon/func_800AFA68 (misses
  by 9), slus/w_8004D5D0 (retail forms its base at 0x80083178 itself - a second declaration, keeps D_80083178),
  slus/code2 (plural partition) and six rows that type a local pointer as `struct S_80083178 *`.
- **Pointer globals typed onto the existing records** (include/shared/record_ptrs.h, forward-declared structs):
  D_800814A8 (230 rows), D_800E3D7C (188), D_80016000 (294) are each ONE pointer (word lw/sw, element 0 only)
  and are now `struct Rec_X *` onto include/records/Rec_*.h. Names stay D_ (D_800E3D7C looks like the player
  entity - unproven).
- **Pins freed by the type change** (m2c had declared these pointer globals as arrays, which moved gcc's
  schedule; the pins compensated): slus/w_8004FAA4 (2 SCHED_BARRIER), slus/w_800492B0 (KEEP), slus/w_80042BDC
  (KEEP_NV) - landed right after phase 4.
- **Tooling fix found by phase 4:** verify.py compiled current SLUS texts against the frozen raw/include; 182 of
  884 SLUS rows could not compile at all through the CLI (commit e8874f3b). The lander already passed the live
  include, so no landing had been lost.
- **Next:** a hand-recovered entity type superseding the union-heavy Rec_D_800E3D7C, then D_80082E80 (290),
  D_80083498 (284), D_80083780 (177) and Rec_D_800814A8 onto it; D_80083120 (the 0x40 bytes before gameWork),
  D_800E2970 (91), D_80013714 (81). Totals: 3,875 row migrations onto 6 shared headers.

## Phase 5 (2026-09-28): landed - the entity type

785 rows (sample first), every row verify-exact (2 SLUS rows via image gate + rebaseline), 475 windows + SLUS
SHA-1 MATCH, pin-neutral (155 migrated pinned rows re-tested).
- **EntityRec** (include/shared/entity.h): the actor/entity record, hand-recovered; supersedes the generated
  Rec_D_800E3D7C.h and Rec_D_800814A8.h (the second turned out to be another view of the same 0x12C-byte record).
  Positions are 16.16 fixed point (`Fixed1616`: whole word and integer half; world coords are tile*64+32). Named
  where every use agrees: x/y/z, tileX/tileY (+0x24/+0x25, paired with dirStepX/Y), facing (+0x2A, with viewAngle
  picks the 8-way sprite), target (+0x60), flags14, flags1C; the rest unk_. Objects carry a 0x20-byte header
  before the record (callers pass `record - 0x20`). 577/580 rows exact.
- **D_80083780** is an EntityRec instance (include/shared/entity_objects.h), 178/184 rows.
- **D_80082E80 is not an entity** (4-byte words where EntityRec has bytes): its own TileObject type
  (include/shared/tile_object.h), 312 rows; name stays D_ (possibly the player's record - unproven).
- **Open item:** three SLUS rows (w_8003D8B0, w_8003F80C, w_8004D614) were excluded: their candidates name
  D_80082E80, which has no entry in the SLUS symbol file (no SLUS source named it before), so the SLUS link
  failed; apply5 reverted cleanly both times. Fix: define it for the SLUS link, gate, re-run apply5 for them
  (details: work/native_lane/r78_types_pilot/PHASE5_OPEN.md).
- **How to continue:** docs/evidence/type_consolidation_pilot_design.md ends with a cold-start "HOW TO CONTINUE"
  section (workflow, tool entry points in tools/consolidate/, every measured hazard, ranked next objects:
  retype record_ptrs.h onto EntityRec and retire the generated Rec headers; D_80083498 (284); remove game.h's
  S_80083178; D_80083120; D_800E2970/D_800E296C; D_80013714).
- Totals: **4,660 row migrations onto 9 shared headers.**

## Phase 6 (2026-09-28): landed (fresh agent, cold start from HOW TO CONTINUE)

425 rows (40-row sample first), every row verify-exact plus every row including an updated shared header
(1,068 verified), 352 windows + SLUS SHA-1 MATCH, pin-neutral. Design/report: evidence/type_consolidation_phase6_*.md.
- **SLUS C-only data symbols:** tools/build/configure.py `C_SYMS` + config/slus_006.14.c_syms.txt define data
  symbols that only C names (D_8006CCD8, D_8006CCE8, D_80082E80, D_80083498) for the SLUS link; strict
  `D_<ADDR> = 0x<ADDR>;` lines, module-owned symbols refused, inert without the file; only the link edge changes
  (no cc edge); recipe re-pinned in ledger/splits/slus.build.ninja with the image MATCH.
- **The phase-5 open item was a candidate error:** those SLUS candidates had folded the separate 128-word table
  D_80082EC0 into TileObject. TileObject now ends at 0x40; w_8003D8B0 / w_8003F80C keep their current (correct)
  text; w_8004D614 landed.
- **record_ptrs.h retyped onto EntityRec *:** 158 dungeon rows dropped the generated record includes.
  Rec_D_800E3D7C.h stays for func_8133AD74 (volatile view); Rec_D_800814A8.h stays until func_810AFA04 and
  func_81324774 (pin-lane rows skipped as busy) migrate.
- **ObjectNodeHeader** (include/shared/object_node.h) at D_80083498: the 0x20-byte node header the SLUS
  allocator func_8003FD64 links into a list (next, pprev, flags named from the allocator); 277 rows. The name stays
  D_ (a script-slot label calls it item type data, which does not fit a list node). D_800834B8 stays separate
  (town rows form their base there).
  *2026-09-28:* that label was a symbol-dump parse error (every name carried the previous record's value). The
  true script variable slot of D_80083498 is `V_pobj` (26), which fits a list node; `V_item_type_data` (27) is
  `itemCategoryTable` 0x80073414 and `V_sys` (28) is `gameWork` (docs/evidence/script_call_table_20260908.md, correction note).
- Totals: **5,085 row migrations onto 10 shared headers.**

## Phase 7 (2026-09-28): landed

205 rows (40-row sample first), 131 windows + SLUS SHA-1 MATCH, pin-neutral; no SLUS recipe change.
- **DungeonRoom D_800E2970[]** + `int D_800E296C` (include/shared/dungeon_floor.h): a table of 0x14-byte room
  records (x, y, w, h, flags named) and a floor flag word - two separate objects; 140 rows.
- **TransitionSlot D_80083120[8]** (include/shared/transition_slots.h; include/slus/slot_transition.h now
  includes it): fields named from the allocator func_8003F794; 11 rows incl. the slot_transition module.
- **`unsigned short D_80013714`** (include/shared/sys_flags.h): 72 rows.
- game.h S_80083178: measured blocked (the six rows miss by 19-118 words) because retail holds gameWork+0x18 as a
  real pointer - the original had a sub-structure there. Decision (OPEN_ITEMS #2): GameWork gets that member;
  phase 8. Rec_D_800814A8.h: its last user func_81324774 was busy; retires on the next pass.
- Totals: **5,290 row migrations onto 13 shared headers.**
