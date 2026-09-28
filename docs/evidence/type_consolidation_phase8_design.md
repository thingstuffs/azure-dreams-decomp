# r78 type consolidation phase 8 - design

Model: claude-opus-5-5[1m].  Lane: work/native_lane/r78_types_p8.  Nothing under src/, include/, config/, tools/ or
ledger/ was edited; apply8.sh lands everything (payload8/: 3 header updates + 2 new headers + the respell tools;
cand8/MANIFEST.tsv: 757 rows).  draft8/ is regenerated from the current src/ by `bash build8.sh`
(respell8 -> hand8 -> variants8 -> preamble8); tools/manifest8.py then builds cand8/ (task-3 texts from cand8x/).

## 1. OPEN_ITEMS #2: GameWork embeds the +0x18 block (GameView view)
- **Layout** (tools/gen_header8.py writes inc/shared/game_work.h from the landed flat header, so every field keeps its
  retail width/sign and census comment): GameWork 0x000..0x017 unchanged, `/* 0x018 */ GameView view;`, 0x1DC..0x1FF
  unchanged.  GameView (0x1C4): header fields at gameWork offset - 0x18 (unk_000.., viewAngle keeps its name at 0x0B0),
  then `ViewSlot slot[4]` at 0x0B4 (gameWork 0xCC/0x110/0x154/0x198).  ViewSlot (0x44) takes slot 0's flat fields;
  +0x00 is `callback` (code2 func_8004D0C8/func_8004D110 store functions there; w_80040BB4 clears all four),
  +0x04 / +0x24 the record's data words (w_8004D294 passes &slot[0].unk_04 / &slot[2].unk_04 to func_8004D1EC).
  One record type: w_8004D7A8/w_8004D7E8 move whole 0x44-byte records slot 0<->1, 2<->3 via func_8004D75C.
  tools/offsets8.py proves the layout: every one of the 72 old field paths has the same offset and size under its new
  path (cc1-computed), sizeof(GameWork) 0x200, GameView 0x1C4 at 0x18, ViewSlot 0x44.
- **Names.** Owner rule: "view" is the less assertive reading of the evidence - 0x094..0x0B3 are four x,y,z,pad
  short vectors from which slus/w_8004D4AC builds the GTE view transform (RotMatrix / RotTrans / CompMatrix /
  SetRotMatrix / SetTransMatrix), w_8004D294 animates position/rotation targets through the slots, and viewAngle is
  vector 3's z; the rest of the header (0x000..0x093, incl. an r,g,b byte triple at 0x090) is not attributed, so
  "camera" would assert more than is proven.  viewAngle keeps its name (the brief: "becomes a member path").
  New names GameView / ViewSlot are unused anywhere in src/ and include/ (the apply preflight re-checks).
- **Respell** (tools/respell8.py, deterministic; respell_map8.json from gen_header8): `gameWork.F`, `P->F` for P
  declared `GameWork *`, and `((GameWork *)x)->F` for every flat field F in 0x018..0x1DB -> the member path;
  `&gameWork.unk_018` under a pointer cast -> `&gameWork.view` (the sub-object's own address).  637 rows / 1,374 sites
  (1,161 of them gameWork.viewAngle).  suspects() flags any moved name still spelled flat (0 in the tree).
- **The six `struct S_80083178 *` rows + D_80083178 users** (tools/hand8.py): func_800C6654, func_800C1E70,
  func_800B2614, func_8191696C, func_81984E94 -> `GameView *state = &gameWork.view;` with state_94.v[i].c -> the
  flat vector fields, callback/field_B8 -> slot[0].callback/unk_04; slus/w_80044724 -> `GameView *source` with an
  `*(struct S_80083178Vector *)&source->unk_0XX` view at the four 8-byte aggregate copies into D_80083CE8 (a genuine
  union site).  Retail forms 0x80083178 itself in three TUs, so they keep a LOCAL `extern GameView D_80083178;`:
  slus/w_8004D5D0 (as known), dungeon/func_800AFA68 (its camera base is D_80083178 - 0x18; as gameWork it misses)
  and slus/code2 (func_8004D0C8/func_8004D110: moving them onto gameWork changes the cc1 listing - offsets AND the
  delay-slot schedule).  game.h's struct S_80083178 is retired; S_80083178State / S_80083178Vector stay (D_80083CE8);
  globals.h drops `extern struct S_80083178 D_80083178;`.  game_work.h's stale "next step" comment is gone.
- **Readability folds** (tools/variants8.py, each kept only when the cc1 listing stays identical - all six kept):
  func_800C1E70's `*(s16 *)((char *)state + 0xNN)` -> state->unk_0NN; func_800B2614's
  `((S_800B7D74_4 *)game_state)->unk_B0` -> game_state->viewAngle (local view typedef dropped); func_809CA53C /
  func_80E0EF2C's `*(s16 *)((u8 *)((s16 *)(&gameWork.view.unk_090)) + 0x20)` -> gameWork.view.viewAngle;
  func_819112CC / func_81910EC0's `((u8 *)(&gameWork.unk_018)) - 0x18` -> `(u8 *)&gameWork`.
- **Proof in the lane** (verify.py cannot be pointed at a lane include tree: the scorer puts the live include/ first,
  see tools/match.py `-I ROOT/include` before the cfg flags):
  - tools/listing8.py: cc1 listing of (src, live include) vs (phase-8 text, lane inc_full/ = complete post-apply
    include tree, the only -I) at each row's cfg: 6,764 / 6,767 rows identical (the 3 others - slus w_8003E758,
    w_8003F368, w_8003F624 - do not compile standalone in either tree and name nothing touched); all 1,037 rows that
    name gameWork / GameWork / S_80083178 / D_80083178 / D_80083CE8 identical, incl. code2 (at 2.8.1).
  - tools/drive8.py (check.py: listing + verify.py byte score with the new shared header inlined): 678/681 exact;
    the 3 not scorable against the live globals.h are exactly the local-`extern GameView D_80083178` TUs (listing
    identity above covers them).
  - apply8 then runs tools/verify.py on EVERY row after the update (game.h/globals.h reach every common.h TU).
- **Pins**: tools/pins8.py erases every pin alone and all together in the old and the new text of the 115 pinned
  draft8 rows and compares the listings: identical everywhere - the respell frees nothing (none expected: identical
  RTL).
- **Why hdr rows must travel together**: after the update the flat spelling no longer compiles, so the 640 `hdr`
  rows land with the header in one run (apply8 re-derives any row whose src moved since the lane with respell8, and
  also any new src user of a flat field; a stale hand/variant row refuses the run; busy hdr rows refuse unless
  --busy-ok, because the busy lane's out/ candidate would still spell gameWork.viewAngle).

## 2. The "nine-object cluster" (D_80081550/54/58, D_80084808, D_80084130, D_800814C8, D_800712B4/98/50)
Not a clone family.  51 self-contained rows (dungeon/town/main, no common.h) carry a flattened copy of the old
game.h + globals.h (struct S_80083178*, MonsterInitialStats/Trap/StatGrowth, the globals.h externs) that m2c
inlined; in those rows the nine symbols are DECLARED, never used.  Real users (census/c9.jsonl): 16 SLUS rows + 1
main row, and the objects are already single declarations: D_80081550 / D_80081554 / D_80081558 are SLUS module
state (include/slus/message_mode_81550.h, command_slots_81554.h; their rows are module members), D_800814C8 is used by
slus/c8_accessors_owned and slus/code.c, D_80084130 by main/func_8000DEA0 ([0] lw/sw) and slus/code.c,
D_800712B4/98/50 only by slus/code.c (a plural partition).
- Done: tools/preamble8.py drops the DEAD copies (a name is removed only when nothing else in the text uses it;
  fixpoint so S_80083178State goes only with its last user) from 42 rows - which also removes the last textual copies
  of the retired struct S_80083178.  Declarations only: listing8 identical on all 42; they are `opt` rows.
- Open (next step): D_80084808 / D_8008480A / D_8008480C / D_80084810 (8 SLUS rows: w_80053DF0, w_80053E20,
  w_80053E90, w_80054D64, w_800550E8, w_800552C8, w_8005560C, w_800559B4) - three s16 stats + an array at +8,
  spelled as separate symbols; w_80053E90 (2.7.2 -G8) reads them with the bare macro form (declared size <= 8 in that
  TU) while w_800552C8 uses D_80084808+2 -> the per-TU declared sizes differ; needs an A/B per row and SLUS
  rebaseline handling.  Not done.

## 3. Task 3 objects (tools/records8.py = room.py generalised; drive8x.py)
### D_80082660 -> include/shared/object_index_slots.h: `ObjectIndexSlot D_80082660[]` (8-byte slots)
- Census (census/c2660.jsonl, 71 rows): indexed (68 rows) by an object's slot number (town objects +0x60/+0x40;
  Konami runtime script byte operand); +0 sb only (clear), +1 lb/sb, +2 lbu 3 / lb 2 / sb 2, +4 lw/sw.
  D_80082668/69/74/7C/80/88/B8 are slot 1..11 fields spelled as their own addresses.
- `object` (+4) named: every store registers `(u8 *)object - 0x20` (the node header), ms_mot_accpt_ow
  (konami_runtime_w_800392A4) returns object + 0x20 after checking the header's type word.  Others unk_.
- records8.pre(): m2c's `extern u8 D_80082660;` + `*((i * 8) + &D_80082660) = 0` becomes `D_80082660[i].unk_00 = 0`
  (natural(), tried first) or keeps the byte view `((u8 *)D_80082660)` (plain) - whichever is exact.
- 65/72 exact (39 plain, 26 natural).  Misses: town/func_800C6228 (7), func_800C8448 (2: retail bases at
  D_80082660 for a +1 access), func_800D15C4 (17); refused: func_8009CE94 / func_800C6A74 (no common.h:
  self-contained), func_800C8810 / dungeon/func_8002DBE8 (no local declaration).
### D_8006DE24 -> include/shared/def_table.h: `DefEntry D_8006DE24[]` (0x14-byte read-only records)
- Census (census/cde24.jsonl, 60 rows): indexed only, lw +0/+8, lbu +0x10..+0x13; `kind` (+0x12, lbu 49) compared
  with 2 almost everywhere.  Rows disagree on what the index is (item_defs / action_table / ability_table /
  MotionEntry), so the type name is the neutral DefEntry and the variable stays D_.
- 49/61 exact.  The 11 misses are one class: the row reads `D_8006DE24[i].kind`-like bytes where retail forms the
  base of D_8006DE24 and adds the offset (%hi(D_8006DE24) vs %hi(D_8006DE24+18)) - those rows' original spelling
  was byte arithmetic on the table base; plus func_800A3D40 (4, a sign-extension order).  They keep their local
  declarations.
- Pins: tools/pins2.py over the 28 pinned task-3 rows: none freed.

# HOW TO CONTINUE (cold start; supersedes phase 7's where they differ)
Start from docs/evidence/type_consolidation_pilot_design.md "HOW TO CONTINUE" and docs/TYPE_CONSOLIDATION.md.
Additions from phase 8:
- **Changing a landed shared type's member paths** (a field moves under a sub-struct): generate the new header from
  the old one (gen_header8.py pattern), prove offsets/sizes with a cc1 `offsetof` table (offsets8.py), write a
  deterministic respell (respell8.py) and let the apply re-derive stale rows at run time; every respelled row
  travels with the header (flag hdr).  Prove the whole tree with listing identity against a COMPLETE lane include
  copy (listing8.py; `cp -r include inc_full`, edit there) - verify.py/kitlib cannot use a lane include tree.
- **Global headers (game.h, globals.h, common.h)**: an edit reaches every row; listing8 over all 6,767 rows takes
  ~10 s (cc1 only), verify.py over all rows ~10-15 min (apply8 does it).
- **Flattened self-contained rows** (no common.h; m2c inlined old common.h content): symbol counts over src/ are
  inflated by their dead declarations - census real USES (census.py) before ranking an object.  preamble8.py is the
  template for dropping dead copies.
- **Arrays of records**: records8.py (room.py with OBJ specs; pointer fields accept pointer views without a cast;
  pre() turns a scalar byte declaration + `&D` arithmetic into the array form; natural() turns byte stores into
  field stores - tried first, kept only if exact).  Driver: drive8x.py KEY.
- **Base-forming misses** (%hi(D) + off vs %hi(D+off)): a row whose retail forms the table's base and adds a field
  offset was written against a byte pointer; keep its local declaration (phase-8 D_8006DE24: 11 rows).
Ranked next objects (rows that USE the symbol; flattened preamble copies excluded):
| rank | object(s) | rows | note |
|---|---|---|---|
| 1 | D_80084808 / 0A / 0C / 10 | 8 SLUS | stats shorts + array; per-TU declared sizes differ (-G8 macro form); SLUS rebaseline |
| 2 | D_800DDE84, D_8006CCF8 | 53, 51 | dungeon (D_8006CCF8 sits after dirStepY: a third step table?) - census uses first |
| 3 | D_8001E950, D_800CFCB4, D_800FE488 | 43, 32, 36 | town |
| 4 | D_80170838 / D_80170808, D_800E3548, D_800DDC40, D_8008ACDC | 42/37, 38, 36, 34 | dungeon |
| - | the task-3 misses above; the D_8006DE24 base-forming class | - | by hand |
| - | gameWork.view header fields (0x000..0x093) and the four view vectors | - | name once evidence allows (func_8004D4AC suggests translation / rotation / target / view rotation) |
