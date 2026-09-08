# adrando (Azure Dreams De-Randomizer) — value for the decomp

Repo copied to `ref/adrando/` (`github.com/ProGrammar-R/ProGrammar-R.github.io`, JS browser patcher).
Only `constants.js` + the entity data files matter for us; the rest is UI/patching glue.

## Spot-check: VERIFIED against our own `baserom/slus_006.14`

adrando's offset scheme: numeric = **raw disc-image** offset; `//RAM` comment = **load address**.
Resident EXE loads at `0x8002D000`, 0x800-byte header, so `file = RAM - 0x8002D000 + 0x800`.
Every probe below matched real bytes — the map is trustworthy, and it is **our exact disc**
(SHA-1 `fab68454…`), so no version drift.

| adrando entry | RAM | Check result |
|---|---|---|
| `anUpperFloorText` | 0x80031353 | Shift-JIS fullwidth decodes to `"an upper flo…"` ✅ |
| `balloonDescription` | 0x8002f220 | decodes to `"It absorbs damage to…"` ✅ |
| `initialStatsTable` | 0x8006d168 | 24-byte records; sane stats; `spell1Id=0x2e` == `spells.darkWave`; `level`byte=1 ✅ |
| `trapTable` | 0x80072cd0 | 12-byte records; embedded valid `0x8003xxxx` text pointers ✅ |
| `itemCategoryTable` | 0x80073414 | embedded valid `0x80081434` pointer ✅ |

**Text is stored Shift-JIS fullwidth even in the USA build** — relevant for any string work.

## The killer demonstration (data map → function identity)

`D_8006D168` (= `initialStatsTable`) is referenced by exactly two split functions:
`func_800429E4` and `func_80042640`. Disassembly of `func_80042640` builds `index<<4 + index<<3`
= **×24 stride** into `%hi/%lo(D_8006D168)` — matching `rowLength.initialStats = 24`.
=> Both are **monster initial-stat lookups**. Two previously-anonymous functions named with zero
guesswork, straight from adrando's table map. This generalizes to every table it lists.

## Where it's valuable in the chain (findings only)

1. **Data-symbol naming (biggest win).** `romAddresses` gives real names + both offsets for ~90
   tables/routines. Harvest into `config/*.symbols.txt` → turn `D_8006D168` into
   `g_MonsterInitialStats`, etc. Data naming is the hardest thing a decomp recovers unaided; it's done.
2. **Struct typing.** `monsterStats` (24B: attack/def/agi/luck/mp/hp/xp/3×spell/level/id/element/
   pushable/flying), `trap` (12B), `statGrowth` (8B), item-category layouts → drop straight into an
   `include/game.h`. Replaces `field_4`/`pad8` with real fields in decompiled accessors.
3. **Function identification / target selection.** For each un-decompiled function, the table its
   `%hi/%lo` touches names its purpose *before reading asm* (demonstrated above). Directly fixes the
   earlier "no game-logic sense yet" gap and lets us pick high-value targets instead of address-order grind.
4. **Named constants / enums.** `TYPE` (item categories), `TRAP_TYPES` (20), `spells`, elements,
   `paletteTypes` → named constants once logic switches on them.
5. **Overlay roadmap.** The `0x800Axxxx–0x8017xxxx` RAM entries are **overlay** code we haven't split
   yet (DUNGEON/TOWN.BIN). They name exactly where the meaty logic lives: `placeMonsterRollGamma`,
   `initMonsterSpawnRate`, `turnMonsterSpawnRate`, trap-roll routines, `resetElementAfterMix` (fusion),
   `eggBombLevelUp`, `monsterDenLeveledUp`, `floorMonsterTable`, `statGrowthTable`, and the Beldo boss
   AI cluster. A ready-made priority map for future overlay work.
6. **RNG ground truth.** `lcgConstants` (glibc-style LCG: mult `0x5DEECE66D`, incr 11) is the game's
   PRNG — lets us *verify* any decompiled RNG-consuming routine behaves bit-exactly.
7. **Asset/palette math.** `paletteInfo` (monster sprite/palette sector layout) aids the 1:1 asset
   preservation side, not the C.

## What it does NOT give / caveats

- **No source, no algorithms.** It knows data *layout/location*, not the code that consumes it. It
  re-implements floor gen via its own seeding; it does not document the game's routines in C.
- **No effect on byte-matching.** Matching is codegen/compiler; these names only help readability,
  typing, and target-selection.
- **Trust: high** (validated above) but its offsets are hand-RE'd — spot-check before bulk import
  (done for 5; do a couple more per table family before trusting a whole region).
- **License: MPL-2.0** (file-level copyleft). Facts about the binary (addresses, record sizes, field
  names) are not copyrightable, so re-deriving them into our own `symbols.txt`/`game.h` is clean. Do
  **not** copy adrando's `.js` files into tracked source. The `ref/adrando/` clone is a local reference
  only — keep it untracked.
