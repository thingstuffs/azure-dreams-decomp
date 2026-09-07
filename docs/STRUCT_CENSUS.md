# Cross-function struct census (Layer 3 groundwork, 2026-09-07)

`tools/struct_census.py` reads every per-function struct T4 produced, ties its base to a
provenance (a global `D_XXXXXXXX`, or a parameter followed through call edges when the caller
passes its own parameter or a global), merges classes only when their layouts are compatible
(no width or pointer-kind disagreement on more than 10 % of shared offsets), and reports each
class's merged layout with per-offset type votes.

structs 10791 from 2745 rows; provenance keys 8683 ({'param': 1740, 'local': 6852, 'global': 91}); groups with >=2 structs: 246

Hard conflicts = width or pointer-vs-integer disagreement at an offset (union-of-views or an
evidence decision). Soft = signedness / qualifier only (a union view or a cast).

| provenance | structs | rows | members | hard conflicts | soft (sign/qualifier) | span |
|---|---:|---:|---:|---:|---:|---:|
| global:D_80083780 | 818 | 596 | 103 | 36 | 11 | 0x12C |
| global:D_800848F8 | 438 | 436 | 22 | 9 | 7 | 0x30 |
| global:D_80126000 | 135 | 128 | 16 | 4 | 2 | 0x44 |
| global:D_800814A8 | 105 | 105 | 18 | 2 | 2 | 0x110 |
| global:D_80082D58 | 95 | 91 | 45 | 3 | 10 | 0xB0 |
| param:dungeon:func_80094268:arg0 | 49 | 45 | 13 | 1 | 5 | 0x48 |
| param:dungeon:func_800AAA54:arg0 | 44 | 44 | 9 | 2 | 1 | 0xAC |
| param:dungeon:func_8008ACDC:arg0 | 27 | 27 | 25 | 1 | 4 | 0x128 |
| param:dungeon:func_800A9E70:arg0 | 17 | 17 | 14 | 1 | 2 | 0xB2 |
| param:dungeon:func_8008B9FC:arg3 | 16 | 16 | 10 | 2 | 1 | 0x8E |
| global:D_800814A0 | 15 | 15 | 1 | 0 | 0 | 0x4 |
| global:D_800CFCB4 | 13 | 13 | 17 | 0 | 0 | 0xAC |
| param:town:func_80020DF0:arg0 | 11 | 11 | 15 | 1 | 1 | 0xB0 |
| global:D_8001E950 | 10 | 10 | 5 | 0 | 0 | 0x9 |
| param:town:func_800AF254:arg1 | 10 | 7 | 5 | 1 | 0 | 0xAC |
| global:D_80083160 | 8 | 8 | 3 | 1 | 1 | 0x8D4 |
| param:dungeon:BODY_NAME:arg1 | 8 | 8 | 9 | 4 | 2 | 0x1A |
| param:dungeon:func_800AC82C:arg0 | 7 | 7 | 8 | 1 | 1 | 0xB0 |
| param:dungeon:func_801237A4:arg0 | 6 | 6 | 19 | 0 | 1 | 0x5C |
| param:dungeon:func_8008D024:arg0 | 6 | 6 | 14 | 0 | 1 | 0x124 |
| param:town:func_800B683C:arg0 | 5 | 4 | 12 | 0 | 0 | 0xE0 |
| param:town:func_800165F4:arg0 | 5 | 5 | 2 | 0 | 0 | 0x1C |
| param:town:func_800B0C68:arg0 | 5 | 3 | 2 | 1 | 0 | 0xD0 |
| global:D_800CFCEF | 5 | 5 | 1 | 0 | 0 | 0x4 |
| param:town:func_80090A74:arg0 | 5 | 5 | 5 | 2 | 0 | 0x42 |

## Reading it

- The five largest classes are global-rooted records used by 91–596 functions each. Their
  merged layouts have few hard conflicts (2–36), and the type votes are lopsided: for
  `D_800848F8` offset 0x14 is read as `u16` by 317 functions, offset 0x4 as `s8` by 59. Those
  are the first shared headers: majority type per member, union of views where a hard
  conflict has real support on both sides, explicit padding elsewhere, `unk_XX` names until
  evidence names them.
- Parameter-rooted classes (`func_80094268:arg0`, `func_8008ACDC:arg0`, `func_8008B9FC:arg3`)
  are the dungeon object-handler ABI: the same record reaches dozens of handlers through the
  dispatcher. The census keeps them separate from the globals unless a call edge links them
  compatibly.
- 6,852 structs stay `local:` (base is a temporary or an expression): they get merged only when
  a Layer-2 pass or a human names the value they hold.

## Next: T7 shared headers

For each class with ≥ 10 rows: emit `include/records/<class>.h` with the merged layout, and a
verified transform that rewrites every member function's `S_<addr>_<n>` uses to the shared
type (member names by offset stay `unk_XX`, so the rewrite is mechanical); a row that
mismatches keeps its local struct and is journalled. Globals get `extern <Record> D_XXXXXXXX;`
declarations so `((S *)D_x)->unk_08` becomes `D_x.unk_08`.

## T7 shared headers — mechanics (2026-09-07 late)

- `tools/struct_census.py` now also writes `ledger/struct_census_structs.json`: every local struct
  with its row, function, base, layout and provenance class (the census re-run after the campaign:
  11,026 structs from 2,783 rows, 240 classes with ≥ 2 structs).
- `tools/gen_records.py` emits `include/records/Rec_<root>.h` for every global- or
  parameter-rooted class with ≥ 10 member functions (13 headers). The layout is the union of every
  view the member functions use: one type at an offset → `T unk_XX;`; several types of one width →
  `union { s16 as_s16; u16 as_u16; } unk_XX;` (a view per type); overlapping spans →
  `union { struct { s32 v; } at00_s32; struct { u8 pad[0x2]; s16 v; } at02_s16; } unk_00;`; gaps →
  `u8 pad_XX[0xN]`. A class is named after the global most of its member structs are rooted at
  (stable across census re-runs; the header comment lists every root and the parameter routes).
  Structs with an in-row union or an unknown-width type are `unmapped` and keep their local
  struct. `ledger/records.json` carries, per class, the header sha and per local struct the access
  path of each member. View names derive from the type alone, so a regenerated header (more rows
  joining a class) adds views but never renames one; structs are keyed by row and name because the
  same `S_<fn>_<n>` name exists in several rows (true-name collisions; the first pass tripped on
  this and was redone). Structs already converted are carried forward from the previous census so
  a class never loses votes.
- `tools/xform/t7_headers.py` (sweep `t7_headers`): drops the local typedef, adds
  `#include "records/<Rec>.h"`, renames the struct, and rewrites each member access whose type sits
  in a union view to that view (`arg2->unk_0C` → `arg2->unk_0C.as_s32`, `->unk_00` → `->unk_00.at00_s32.v`),
  attributing every site to its struct through the cast `((S *)expr)->` or an identifier declared
  `S *ident`; anything it cannot attribute, `sizeof(S)`, and `_pre` records are refused. The
  function reads every offset with exactly the type it read before, so the bytes cannot move;
  each row is still verified (all structs at once, then one at a time on a mismatch) and the
  touched windows are re-gated afterwards. Verified exact on the first three rows tried, one per
  class kind (global scalar, the big dungeon record via union views, a parameter class).

### T7 result (2026-09-08 00:xx UTC)

Four passes, the first three thrown away (source reverted, journal deleted) as each found a
defect in the machinery, never in a row:

1. struct names collide across rows (`S_<fn>_<n>` is keyed on the true name, and several rows
   carry the same true name), so the census kept one layout per name and the transform refused
   the others ("member not in the record mapping") — the census is now keyed by row and name;
2. union-view names came from vote order (`s`/`u`/`n`, `at00`/`at00u`), so a regenerated header
   could rename a view under an already-converted row — names now derive from the type alone
   (`as_s16`, `as_pv`, `as_pps32`, `at02_u16`, `as_x<hash>` for function pointers) and every
   header is compiled standalone by the 2.7.2 cell before it is used;
3. the census parsed a function-pointer member as its return type (`M2C_UNK (*unk_50)(...)` →
   `M2C_UNK`), so the shared view was not callable — fixed in the member parser; rows with a
   hand-trimmed prelude (a lone `typedef s32 M2C_UNK;`) clashed with the compat include the
   headers pull in — the duplicate typedef lines are dropped (byte-neutral), any other definition
   of those names is refused.

Pass 4 (`ledger/sweeps/t7_headers.jsonl`): **1,014 rows applied, 1,563 local structs replaced by
12 shared records, 7,791 access sites routed through union views, 0 mismatches, 0 build failures,
0 partial refusals**; the only refusals are rows with no struct of a record class. 611,680 bytes
of matched C (23.9 % of the registry) now compile against `include/records/` (dungeon 674 rows,
town 337, SLUS 3). Every class converted every mapped member (e.g. `Rec_D_800E3D7C` 537/537).
Proof of record: the SLUS SHA-1 gate rebuilt the three executable TUs (MATCH) and the window gate
re-ran every touched window: **562 windows, 562 byte-identical** (369 s; journal 2,172 / 2,172 MATCH).

What the headers are not yet: named. Members are offsets, classes are addresses, and the
overlap unions in the big dungeon record (`unk_0C` with eight views, `unk_14` with four) are
honest but ugly — they record that different functions read the same bytes with different
widths. Naming (L4) starts from these files, and a name change in a header reaches every user at
once, verified through the same gate.
