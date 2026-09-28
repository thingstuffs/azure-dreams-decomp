# r78 type consolidation phase 7 - report

Model: claude-opus-5-5[1m].  Deliverable: apply7.sh (+ payload7/: 3 new shared headers + include/slus/slot_transition.h
update, UPDATES.tsv; cand7/MANIFEST.tsv 206 rows; sample7_rows.txt 40 rows: dungeon 28, slus 11, town 1 - no main
row references these objects).  `bash work/native_lane/r78_types_p7/apply7.sh --dry-run` -> 205 to land, 1 skipped
as busy (dungeon/func_81324774: r78_astra_b4 out/ within the hour, free after ~12:40; func_810AFA04's window has passed).
Run order: `bash work/native_lane/r78_types_p7/apply7.sh --rows work/native_lane/r78_types_p7/sample7_rows.txt`,
then the full run (resumable).  The 5 slot_transition module rows always travel with the header update (also in
a --rows run); apply7 refuses to run if any of them is busy or stale.  No SLUS recipe / c_syms change.

| task | result |
|---|---|
| 1 game.h S_80083178 | BLOCKED, kept. All six local-pointer rows A/B'd onto flat gameWork fields: 19-118 words each - retail holds gameWork+0x18 in a register (callee-saved across calls, or passed to func_800997FC / func_80042900). The +0x18..+0x1DB block (0x1C4 bytes: header + four 0x44-byte dispatch slots ending at 0x1DC) is a real sub-type; removing the overlap = GameWork embeds it, which respells gameWork.viewAngle in 634 rows (no anonymous structs in gcc 2.7.2, tested). Owner decision. |
| 2 Rec headers | func_810AFA04 / func_81324774 drop the dead Rec_D_800814A8.h include (exact); apply7 retires the header + records.json entry once no includer is left. func_8133AD74: without volatile misses by 2; volatile at the use is exact but grows the row's scaffolding count -> Rec_D_800E3D7C.h kept. |
| 3a D_800E296C / D_800E2970 | include/shared/dungeon_floor.h: `int D_800E296C` (floor flag word) + `DungeonRoom D_800E2970[]` (0x14-byte room table; x/y/w/h/flags named). 140 rows exact (58 + 85); misses func_800AFA68, func_812A524C (-G8), func_80286AF8; 4 refused (no local decl / unmapped member / no common.h). |
| 3b D_80083120 | include/shared/transition_slots.h `TransitionSlot D_80083120[8]` (type/unk_2/param/unk_6 from the allocator func_8003F794); slot_transition.h now includes it. 11 rows (6 verify exact in the lane, 5 module rows proven by module listing identity: tools/module_check.py). |
| 3c D_80013714 | include/shared/sys_flags.h `unsigned short D_80013714` (name stays D_). 72 rows exact; misses: slus/w_80042560, konami_runtime_w_8003BAF8 (-G8 declared size), dungeon/func_800A665C, func_812A524C, func_81325730, func_81337D98. |
| pins | none freed (pins2 over 64 pinned migrated rows; module rows carry none). |

Totals: 206 row migrations onto 3 new shared headers (13 shared headers overall), 1 header update, 1 generated
record header retired (on landing).

Tooling (lane tools/, worth syncing to tools/consolidate/): room.py (array-of-records rewrite), slots.py,
drive7.py, combine7.py (all transforms per row, one verify, writes the manifest), tidy137.py, module_check.py,
try.py (check one text), fold18.py (the task-1 A/B helper); check.py also inlines slus/slot_transition.h from the
lane inc/.

Caveats:
- apply7's verify set = landed rows + every includer of the new/updated headers (slot_transition.h pulls in the
  whole slot_transition module family); plural partitions slot_transition.c / _secondary.c are covered by the SLUS
  image gate.
- If r78_opus_w7 / r78_astra_b4 land func_810AFA04 / func_81324774 first, those rows go stale: the change is one
  dropped `#include "records/Rec_D_800814A8.h"` line; Rec_D_800814A8.h stays until then.
- game_work.h's comment still says folding S_80083178 is "the next step"; fix it at the next GameWork header update.
- OPEN_ITEMS: #2 stays open with the new evidence (sub-type is real; owner decision on embedding); #3 closes for
  Rec_D_800814A8.h once the two rows land, stays open for Rec_D_800E3D7C.h (func_8133AD74 hidden volatile).
