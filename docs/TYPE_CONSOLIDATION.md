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
