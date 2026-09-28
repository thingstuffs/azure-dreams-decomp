# r78 type consolidation phase 9 - report

Model: claude-opus-5-5[1m].  Deliverable: apply9.sh + payload9/ (UPDATES.tsv: include/globals.h updated,
include/shared/sound_volume.h NEW; names_add9.tsv: volumeScale -> D_80084808) + cand9/MANIFEST.tsv (207 rows: 202
`opt`, 4 `opt,rebaseline`, 1 `hdr`) + sample9_rows.txt (40 opt rows: dungeon 22, slus 11, town 5, main 2 - includes
every task-1 SLUS row, so the 4 rebaseline rows are exercised by the sample).
`bash work/native_lane/r78_types_p9/apply9.sh --dry-run` -> 207 to land, 0 skipped; with `--no-hdr --rows
work/native_lane/r78_types_p9/sample9_rows.txt` -> 40, 0 skipped.

Run order (from the repo root; the script takes build_ovl/work/land.lock itself):
1. `bash work/native_lane/r78_types_p9/apply9.sh --no-hdr --rows work/native_lane/r78_types_p9/sample9_rows.txt`
   (NEW header + names row + 40 opt rows; verifies the landed rows, gate_all, SLUS SHA-1, --rebaseline-slus x4).
2. `VERIFY_WORKERS=16 bash work/native_lane/r78_types_p9/apply9.sh` (globals.h update + slus/code + the other opt
   rows; verify.py on EVERY row ~11 min, gate_all, SLUS SHA-1).  Resumable (landed rows are skipped).
A stale or busy opt row is skipped (re-derive: `cd work/native_lane/r78_types_p9 && python3 tools/build9.py &&
python3 tools/check9.py && python3 tools/manifest9.py`); a stale/busy slus/code, or any src row that still uses
D_80084808 through globals.h, refuses the full run.

| task | result |
|---|---|
| 1 OPEN_ITEMS #17 | Done. 0x80084808/0A/0C are ONE object: `extern short volumeScale[];` (include/shared/sound_volume.h; names.tsv alias to D_80084808). Three Q15 volume scales (sound init sets 0x7FFF; the option words 0x80080A9C/98/94 set them; each multiplies a level / 32767 before func_8005B4D0 / func_8005B27C / func_8005A56C). Declared UNSIZED: measured, a 6/8-byte declaration drops into $gp at -G8 (w_80053E20 37, w_8005560C 74 words off); `[8]` would overlap the separate table D_80084810 (reached only from its own base by w_800550E8 - not a member). 7 SLUS rows + slus/code migrated; globals.h's `short D_80084808[8]` removed (whole tree: listing identical on 6,757/6,767, the rest = the migrated rows modulo symbol names + 3 rows that never compile standalone); 6 dead overlay copies dropped. 4 rows need `--rebaseline-slus` (relocation names D_80084808+2/+4 vs D_8008480A/C, same bytes). Wrong "player stat"/"pitch bend"/"gauge" comments corrected. |
| 2 OPEN_ITEMS #18 | Done, 12/12 (the 11 + func_800A3D40). Phase 8's misses were a generator artifact: under `DefEntry D_8006DE24[]` the BYTE view `((u8 *)D_8006DE24)[i*0x14+0x12]` folds +18 into %hi (exactly phase 8's diff), while `D_8006DE24[i].kind` keeps retail's base form and is exact. func_8009E0C0 needs `DefEntry *entry = &D_8006DE24[i]; entry->unk_13`; func_800A3D40's local S_8006DE24_Entry maps straight onto DefEntry. |
| 3 views onto shared types | 182 rows folded, all exact (per driver, rows overlap): EntityRec pointer globals 120 (15 local views -> EntityRec fields, 105 redundant `(EntityRec *)` casts), local view pointers -> typed shared pointers gameWork 45 (dungeon 25, town 11, slus 7, main 2), dungeonStatus 21, TileObject D_80082E80 7, EntityRec D_80083780 3 (35 view typedefs dropped). Census of what remains: census/views9.jsonl (458 rows with a local view on a shared object; ranked in DESIGN HOW TO CONTINUE). |
| pins | None freed: pins2 over 58 pinned migrated rows (162 pins, each alone and all together). No cell-only result. |

Pre-flight: verify.py over all 6,767 rows of the current tree = 0 not exact (results/verify_baseline9.jsonl).
Totals after landing: 207 row migrations (task 1: 8 incl. slus/code; task 2: 12; task 3: 182; dead-copy drops: 6; one row in both task 2 and 3) - dungeon 175, slus 16, town 14, main 2;
1 new shared header (16 overall), 1 header update (globals.h), 1 names row.
OPEN_ITEMS after landing: #17 and #18 -> Closed (phase 9).  Candidate new line: lane tools/consolidate.py typed-mode
fix (maps local-view members) and objects/gameWork.json (still the flat pre-phase-8 layout) to sync into tools/consolidate/.
Tools (lane tools/): t1.py / t1v.py (declared-size A/B), spell.py (spelling A/B), drive9e.py, drive9g.py, tidy9.py,
viewcensus.py, build9.py (composition), check9.py, listing9.py (whole-tree listing identity), manifest9.py, vbase.py.

## Fix after the full run reverted (2026-09-28)
Root cause: the unsized `volumeScale[]` (landed with the sample) mis-assembles slus/code (stock 2.7.2 store macros: no
`.extern` size -> `$at` expansion + nop instead of the delay-slot fill) -> every module/partition gate calibration NO MATCH
(88,082 words).  Not a verify.py or resync problem.  apply9.sh now also updates include/shared/sound_volume.h to
`short volumeScale[8]` in the full run (retail: any size > 8 bytes; [5]/[8] MATCH, [4]/[] do not).  Proven in scratch
SlusView copies: complete post-apply SLUS state calibrates MATCH (words_diff 0); the 7 landed w_ rows stay verify-exact.
Dry run: 167 to land, 40 already landed, 0 skipped.  Run: `VERIFY_WORKERS=16 bash work/native_lane/r78_types_p9/apply9.sh`.
