# r78 type consolidation phase 8 - report

Model: claude-opus-5-5[1m].  Deliverable: apply8.sh + payload8/ (UPDATES.tsv: game_work.h, game.h, globals.h updated;
object_index_slots.h, def_table.h NEW; tools/respell8.py for run-time re-derivation) + cand8/MANIFEST.tsv (757 rows:
640 `hdr`, 117 `opt`) + sample8_rows.txt (38 opt rows: dungeon 15, town 16, slus 6, main 1).
`bash work/native_lane/r78_types_p8/apply8.sh --dry-run` -> 757 to land, 0 skipped, 0 busy.

Run order (from the repo root; the script takes build_ovl/work/land.lock itself):
1. `bash work/native_lane/r78_types_p8/apply8.sh --no-hdr --rows work/native_lane/r78_types_p8/sample8_rows.txt`
   (sample: the 2 NEW headers + 38 opt rows; no existing header changes; verifies the landed rows, gate_all, SLUS).
2. `bash work/native_lane/r78_types_p8/apply8.sh` (full: the 3 header updates + ALL 640 hdr rows in one go + the other
   opt rows; verify.py on EVERY row (~10-15 min, VERIFY_WORKERS=12), gate_all, SLUS SHA-1).  Resumable.
The task-1 header update cannot be sampled: once GameWork's flat fields move, every unlanded `gameWork.viewAngle`
row stops compiling, so hdr rows ignore --rows.  Stale hdr rows are re-derived at run time with respell8 (mechanical);
a stale hand/variant row (15 rows) refuses the run (then in the lane: `bash build8.sh && python3 tools/manifest8.py`).
A busy hdr row refuses the run unless --busy-ok; after landing, any in-flight lane candidate that spells a flat
gameWork field must be re-derived: `python3 work/native_lane/r78_types_p8/payload8/tools/respell8.py FILE`.

| task | result |
|---|---|
| 1 OPEN_ITEMS #2 | Done in the payload. GameWork embeds `GameView view` (gameWork+0x018..0x1DB: header + `ViewSlot slot[4]`, 0x44 each). 637 rows / 1,374 sites respelled mechanically (gameWork.viewAngle -> gameWork.view.viewAngle: 1,161 sites; gameWork.unk_154 -> gameWork.view.slot[2].callback, ...). The six `struct S_80083178 *` rows are now `GameView *state = &gameWork.view;`, plus w_80044724. game.h's struct S_80083178 is retired (State/Vector stay for D_80083CE8). globals.h's D_80083178 extern is removed; three TUs where retail forms 0x80083178 keep a local `extern GameView D_80083178;`: slus/w_8004D5D0, dungeon/func_800AFA68 and slus/code2 (code2 newly measured: on gameWork its cc1 listing changes). Six readability folds kept (listing identical). Proof: offsets8 (72 field paths, same offset and size); listing8 identical on 6,764/6,767 rows against the complete post-apply include tree (the other 3 do not compile standalone in either tree); check/verify byte score 678/681 (the 3 are the local-extern TUs, covered by listing identity). |
| 2 nine-object cluster | Not a clone family: 51 self-contained rows carry a dead, m2c-flattened copy of old game.h + globals.h, and the nine symbols are only declared there. Real users: 16 SLUS rows + 1 main row. D_80081550/54/58 are already SLUS module state (message_mode_81550.h, command_slots_81554.h). Done: dead preamble copies dropped from 42 rows (preamble8.py, listing identical); this removes the last textual copies of struct S_80083178. Open: the D_80084808/0A/0C/10 stats group (8 SLUS rows, declared size differs per TU). |
| 3a D_80082660 | include/shared/object_index_slots.h `ObjectIndexSlot D_80082660[]` (8-byte slots). `object` (+4) is named: rows register `object - 0x20` and ms_mot_accpt_ow returns `object + 0x20`. 65/72 exact (26 via natural field stores replacing `*((i * 8) + &D_80082660) = 0`). Misses: town/func_800C6228 (7), func_800C8448 (2), func_800D15C4 (17). Refused: 4 (no common.h / no local decl). |
| 3b D_8006DE24 | include/shared/def_table.h `DefEntry D_8006DE24[]` (0x14-byte read-only records). `kind` (+0x12) is named: nearly every user tests `== 2`. What the index means differs between rows, so the type keeps a neutral name. 49/61 exact. 11 misses form one base-forming class (retail %hi(D_8006DE24) + offset vs ours %hi(D_8006DE24+18)); 1 is a sign-extension order (func_800A3D40, 4). |
| pins | None freed. pins8: 115 pinned draft8 rows, every pin alone and all together, old vs new listing identical. pins2: 28 pinned task-3 rows. No cell-only result to check. |

Pre-flight of apply8's verify step: tools/verify.py over ALL 6,767 rows of the current tree (live src + include, exactly
as apply8 calls it, incl. slus/code2 and every module/partition row): 0 not exact (results/verify_baseline.jsonl; ~11 min
at 16 workers - run the full apply with VERIFY_WORKERS=16).  No hdr row is a comment-only respell (checked: 0).

Other findings:
- verify.py's `include_root` cannot test a changed header from a lane: tools/match.py (the scorer) passes
  `-I ROOT/include` BEFORE the cfg flags, so the live include wins (verify8.py reproduces it).  Lane proof for header
  edits = cc1 listing identity against a complete include copy (listing8.py).  Candidate OPEN_ITEMS line.
- OPEN_ITEMS after landing: #2 -> Closed (phase 8).  New: D_80084808 stats group; D_8006DE24's 11 base-forming rows.
- Totals after landing: 757 row migrations (637 respell [6 also hand-edited] + 3 hand-only, 114 task-3 [38 overlap with respell],
  42 dead-preamble), 2 new shared headers (15 overall), 3 header updates.
- Tools (lane tools/, worth syncing to tools/consolidate/): gen_header8.py, offsets8.py, respell8.py
  (+respell_map8.json), hand8.py, variants8.py, preamble8.py, listing8.py, verify8.py, pins8.py, records8.py,
  drive8.py, drive8x.py, manifest8.py; build8.sh regenerates draft8/.
