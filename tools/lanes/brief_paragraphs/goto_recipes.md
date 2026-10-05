# goto_recipes.md - replacement "measured recipes" for tools/lanes/goto_lane_brief.md (r93 harvest: 14 Sonnet + 4 pinned + 8 Gemini goto lanes)

Source: 26 r93 hand lanes (Sonnet g1-g14, pg1-pg4; Gemini agy_goto1-8; cg1-cg7 and tptabc for the switch rows) plus s1,
t136. Counts are the lanes' own "tried / exact" tables merged; units differ (some lanes count per site, some per
row), so read them as strength of evidence, not as probabilities. Row ids are `dungeon/func_XXXX` unless noted.
Every line is APPEARS -> RESOLVES. A rewrite that is exact on one row can miss on the next because of a global-allocation
or block-order side effect: measure each; the NEVER column says which side effect.

Measurement protocol added by r93 (put in "How to measure"):
- A switch moves the jump table: export `LANEKIT_SCORE_NEAR=300` (listing distance 41-162 on exact switch rows; 200 for
  other structural rewrites). Exactness is the scorer's `status ok` incl. jtbl compare, not the listing distance.
- Several tail copies of DIFFERENT labels interact (crossjump keeps one copy): measure each label alone, then all, then
  the greedy union (t136 does this). "All three sites" was jtbl-mismatch while every proper subset was exact (g12
  81087818); two copy families together = 97 subs while each alone was exact (cg7 818B1664).
- Before declaring a backward goto "real", read `why.py <row> --pass loop --variant cand.c`: it prints the loop count
  retail vs candidate ("loops could not be aligned: loop_count_differs 5_vs_6") and the hoist/giv lines. That, not
  the distance, names the mechanism.

## 1. Deletions and returns

| shape APPEARS | RESOLVES | tried/exact | held on | NEVER / mechanism |
|---|---|---:|---|---|
| `goto L;` whose label is the next statement (incl. an `else { goto L; }` arm) | delete goto (+label, + empty else) | 8/7 | 809F33F8 (10 gotos), 800ADD2C, 818C8A70, town/800A02F0 next_entry | 80098378: plain delete = dist 6; the inner if/else must ALSO swap arm order (`!= 0` arm first). Try the swap once (t127 does not) |
| `goto end_of_function;` / `goto L` where `L: return;` | `return;` at each site, or fall out | 6/6 | 818C8A70 (remove_effect_done), 80092B48 | none for void |
| `goto L` where `L: return <variable/expr>;` | `return expr;` at each site | 9/7 | 80287C4C (3 of 4), 7FFED5BC (return entry_index) | the failing site: a side-call failure test right before a loop `break` (bltz delay slot, dist 20) |
| `goto L` where `L: return <CONSTANT>;` and retail keeps ONE shared return block | keep the goto, or fall through to the single final `return K;` | 8/1 | works only as fall-through into the last return: 8009B70C (`if/else` + one trailing `return 0`) | `return 0` at each site = dist 3 (extra `move $2,$0` per return, 8009B70C); `return 2` at the sites 339-347 (retail jumps to a shared return with the store in the delay slot, 8095563C). Constant returns are layout, not syntax |

## 2. Short shared tail -> copy at each goto (t136_stubtail covers <= 3 simple statements ending in return)

| shape | RESOLVES | tried/exact | held on | NEVER |
|---|---|---:|---|---|
| `goto L` into `L: call(a); return;` / `L: x = f(v); y = x+1; return;` (1-3 lines, in a switch arm or mid-function) | the stub text at each site, label deleted | ~105/~70 pooled; clones 6/6 (809A58EC family, 4 sites each), 3/3 (g9), 3/3 (g10 80F34FB4/81875C70) | 80CE8CBC, 808110CC (set_state_8), 8099F8EC, 80D3C280 (4 of 6), 810332A4 cleanup, 81978140, 8105C45C, 818154FC | see "copy that raises a hot pseudo's refs" below |
| `goto` into another switch case's tail, tail <= 6 lines | copy the tail into the foreign case | 7/6 (g12), 6/6 (agy5 D3B284/81978140/…) | 81087818, 8132EAB8 (6 lines), 800BF7C0 (7 lines), 80D3F464 (8-line plus-angle exact, 9-line minus-angle NOT: the shared tail is real) | 10-line copy exact on 800AD540 (agy2): over the ~6-line owner limit, coordinator call |
| goto jumping into the tail of another arm where the copy raises allocation weight | `break;` + the tail ONCE after the switch (case that falls out) | 2/2 (EB7D2C, 800A72F8) | 80EB7D2C (copy = dist 151) | 81336754: break-to-tail moves case 0 to the epilogue in the jump table (dist 93) |
| goto into an `if (x) { copy: ... }` block from outside | the block's 3-4 lines copied into the other arm (`if (player) {copy} else if (kind==2) { if (t) {copy} } else {tail}`) | 14/9 | 80E0F7C0 (needs the `(s16)is_special != 0` cast), 80D3E260, 80E8D490, cg2/cg5/cg6 rows | the "copy-target trio" misses on 6 rows with a register swap: cg2 80D91070 (195), 810318E4 (387), 81252D6C (274), cg5 80F3575C (43 subs), cg1 5x3 gotos |

NEVER worked, with the mechanism (use it to stop early):
1. **Copy raises the refs of a hot pointer/state pseudo** -> global.c `4*refs/len` priority flips two callee-saved
   registers ($s0/$s1, $17/$18) over the whole function. Measured: 8102F83C monster refs 31->37 prio 5000->7283 (dist 68);
   800ACC98 work 11->13 refs 5593>6393 > obj 6315 (dist 42, 9 spellings); 81336754 (82 per site), 80EB7D2C (151), 8008DCFC (84),
   80D6671C (156), 818B7F38 (134), 80D3F464 stuck-flag (362). Check with `prio.py` BEFORE trying more spellings. A copy of a
   spilled variable's store (8009E0EC selected_action, 106-124) is the same class.
2. **Copy adds a second CALL site** that stays physically separate (falls into other code): 95984 (dist 56), 80BCDBA8/80BD9BA8
   12-line ground call (dist 50), 81005278 (69), 8133AD74 case 13 (31: extra site shifts $5->$7). A 1-2 line `call; return;`
   copy is fine because jump.c cross-jumping re-merges identical returning tails (hypothesis, consistent with 18 of 18).
3. **Retail lays the shared block out of source order**: the stub sits before the scan loops (800A1AD4, 54-134), between the
   5-7 test and the coords block (80D3C280 case 12: gcc keeps ONE copy of identical adjacent stubs, at the later position,
   dist 25), after the physical else block (810ADDF4 call block shared by two jump-ins, 6-31), before a block only a
   LATER backward goto enters (800C0848: 44-189), 81905FD0 (dist 30, no goto-free source order exists), 8009BEB8.
4. **Retail jump table has stubs `j case0; li` for other cases** (800BB3A0 words 0x38/0x3E): jtbl-mismatch dist 6/11.
5. **Whole-block hoist after a switch / duplicate into default**: 0/3 (809F5574 default-fallthrough 15-262; g2).

## 3. Skip guards, else wraps, merged conditions

| shape | RESOLVES | tried/exact | held on | NEVER |
|---|---|---:|---|---|
| `if (c) goto L; BODY L:` (guard) | `if (!c) { BODY }` | ~50/~44 | 80CE8CBC (6/6), 80FF9000 (nested == `&&` chain), 809DB054, 80099EE4 (with the sequenced condition) | OR-merge of two skip tests 0/3 (pg2); merge of different bit tests into one `&&` (existing rule); flag-ifying (`stuck`, reuse `state` as flag) 0/2 |
| chain of guards to one label | one `||`/`&&` chain or nested ifs; both exact where tests are on different words | 5/5 | 800971DC, 80FF9000, 80087054 | `A && B && C` with redundant range tests (combine folds) |
| goto over a statement inside an arm | if-guard, or drop `else { goto }` when the skipped statement is an idempotent reload (cse folds it) | 4/4 | 800C2BFC (apply_drag), 818B7F38 | |
| two arms ending `goto M` / forward goto ladder to one tail | merge to one goto after if/else, or if / else-if chain falling into the tail | 14/11 | 810ADDF4 (13->2), 800B64A4, 80FDD1A0 empty_selection | else-if when retail's first block is the "neither" arm: write `a != X && a != Y` FIRST (8001A2B0; state==1-first dist 26) |
| `if (*p == 0) goto empty; MAIN; return; empty: ...` | `if (*p != 0) { MAIN; return; } empty...` | 8/8 | 80FDD1A0, cg2 x5 (even with labels left inside the block), cg4 x3 | empty-first / early-return-first (g2: dist 60) |
| `if (a) {if (b) goto L;} X; return; L: Y` | `if (a \|\| b) { X; return; } Y` | 5/1 | 8008B4B0 | `&&` form, nested with body first: dist 16 |
| two arms differing only in a prefix then identical | `if/else` with the shared tail once, but keep a prefix that carries a variable's use count | 3/1 | 818B7F38 | duplication that moves a `4*refs/len` priority |
| `if (x != A) { if (x != B) goto alt; } call(); ... ` | `if (x == A \|\| x == B) call(); if (x != B) { if (x == A) {...} }` | 4/2 | w_80042BDC | `x == B \|\| x == A` order: dist 10-108 |
| arm ORDER in the rewritten if/else | write the arm that retail lays out FIRST first | - | 8081E9A4 (up arm first exact, down-first 325), 8008B4B0, 80098378 (`!= 0` arm first), 8001A2B0, 810AF0B4 (kind==2 arm first; != 2 first = 38) | block order is the whole story: measure both orders once |

Arm-order / form notes that decided exactness: `if (c) A else B` vs `if (!c) B else A` (80D3FD8C both exact; 80098378 only one).
`kind == 0xE || (kind < 0xF ? kind == 0xD : kind == 0xF)` exact (813360FC, owner-approved odd condition).

### Skip-copy class (CONFLICT with the existing "do not rewrite" paragraph, see REPORT.md)
APPEARS `v = part_a; ... if (!(f & 1)) goto L; BODY; v = obj; L: call(v, ...)` (also `if (c1 || c2) goto init; ...; v = obj; init: func(v,..)`).
The existing paragraph says 0 of 12 goto-free spellings exact. r93 measured 6 of 6 exact by DROPPING the temp variable and
passing the base object directly: `if (f & 1) { BODY } call(obj, ...)` (agy_goto1: 80D65F80, 80F33094; agy_goto4: 809CF054, 809E1054,
809ED054, 80A9B07C, each with the dead locals deleted). The failing r93 case: 81809A0C check_other_side (first_slot hoist/merge
dist 90-112, left per brief). One compile decides: try "drop the temp, pass obj" before leaving the goto.

## 4. Ladders to `switch`

| shape | RESOLVES | tried/exact | held on | NEVER |
|---|---|---:|---|---|
| state/phase ladder `if (s==1) goto a; if (s<2) {if (s==0) goto b; return;} if (s==2) goto c; return;` | `switch (s)` with the cases in the labelled blocks' SOURCE order, `default: return;` (or none), tail `break`; case 0 falling into case 1 where the source falls | ~40/~34 | 80CE8CBC, 80D150D0, 80FB4E68, 8197D468, 81339F68, 80EB7D2C, 813231FC, 81934928, town/800BE540, 818154FC, 80D3FD8C restore_phase | the SAME ladder as if / else-if: 0/4 (8197D468 dist 48, 8182D698 dist 24, 80CE8CBC 20); test-order switch 0/2 (80D150D0 1,0,2,3 dist 82); retail case tree flat vs gcc's (80956260: retail root 0x100/left 3, dist 14, 20 variants) |
| `case n: goto L_n;` dispatch with labels in source order | `case n:` at each label, bodies in place, indentation fixed | 2/2 | 80DBD3EC | |
| compare ladder over a state var with constant-holding locals (`x = 0x31; if (state == x)`) | switch; DROP the locals (literals): variables kept = dist 6 (li hoist) | 4/4 | town/func_800BF718 | |
| binary dispatch with shared bodies (`s` in 0..3, 0/2 and 1/3 share) | grouped `case 0: case 2:` / `case 1: case 3:` | 2/1 | town/func_800C217C | sequential 0,1,2,3 dist 3; reversed groups 29; booleans 39-49 |
| ladder of range tests jumping over a default block | `switch (x) { default: DEFAULT; case 1: case 2: case 3: ...; case 37 ... 41: }` DEFAULT FIRST | 2/2 | town/func_800BB264 | default last 26; small-arm-first if/else 26; merged range tests 37-40. The GNU range here is OK only if it means something; 37-41 are table-proven |
| sparse `if (state != 0) { if (state == 1) goto fade; return; } body0; return; fade:` | `switch (state) { case 0: ...; case 1: ... }` | 3/3 | 8182D698, 8008D69C | `if/else if` (24; emits `bne` on 0 first) |
| switch hides a constant held in a register | re-materialised in the target block (li hoisted into a delay slot): 1 row stays at 1 | - | (round 80 note) | |
| `goto L` out of a switch-case to code AFTER the switch | `break;` (inner switches need their own `break;`) | ~14/14 | 80D3F464 (5/5), 8186F0C4 (4/4) | |
| cases entering mid-body of a sibling (goto into fall-through case) | reorder so the case that tested it falls into the target | 1/1 | 80CE8CBC `case 12:` before `case 5/6/7` | |
| a case label inside an `if` block (goto into a block) | early `break` guard before the label, case 2 falls into case 3 | 1/1 | 8195E81C | copying the case-3 test into the if-block: 13 words off |

NEVER worked: inlining the case bodies where retail has the cases jump to labels in a LATER block (80A9D4E8 item_e/b/8; 80FDD1A0 jtbl word 0
0x80172DFC vs 0x80172E0C, dist 96); a label inside the switch body that holds a block after the jump table (8095563C zone_found, `break` = dist 8-11);
case order other than the labelled blocks' source order (24 orders, 80956260-style 32-51).

## 5. Slot-web: m2c `goto` web into slot / kind assignments (the largest single family: ~25 rows incl. the cg dispatch rows)

APPEARS `switch (kind - 1)` or `(unk_46 & 0x3FFF)` cases that `goto kindN`/`goto slotN` into assignments `slot = actor + 0xE; goto ready;`,
with a "special" flag set on some paths (`use_player = 1;`).
RESOLVES two switches:
```
switch (id - 1)  /* flagged */ { case 6: use_player = 1; case 2: slot = 0xE; break;   /* fallthrough PAIRS */
                                 case 5: use_player = 1; case 1: ...; case 7: ...; case 3: ...; default: ... }
else  switch (unk_46 & 0x3FFF) { case 3: ...; case 2: ...; case 1: ...; default: ...; }   /* DESCENDING, default last */
```
Measured: ~16 rows exact, 2 failed: 80A1F0C4, 810AF0B4, 80BC3AC4, 80C412B4, 80D13E4C, 80E0F7C0, 80E8D490 (1 goto left: UpdateFlags case 3/4 shared store),
80F5F040, 80D3E260, plus cg4 80C6B878/80AC7A30/80E639C8, cg5 809A1D60/80DBBFC8. Failed: 809F5574 (item_slot has 11 refs vs retail 9, priority
4074 > actor 3915, prio.py; 12+12 order variants, 9 init placements 11-98 - the flagged and non-flag switches are byte-identical except $s0/$s1 swap) and
80977248 (dist 102 swap; per-case copies 31-39 = block order only: retail lays the flag-switch stubs, then the else switch, then THREE shared tails AFTER it).
Case ORDER: only 3,2,1 exact in the else arm (all 12 orders measured on 810AF0B4: others jtbl-mismatch or dist 6-16); the flagged pairs in order 3,2,1;
ascending else-arm 0/3 (jtbl). Per-case duplicated assignments: 0/14 on the g-lanes (dist 7-119), yet exact 3/3 on cg4 where the bodies are ONE-line
stores (`item_slot = actor + 0xE`): the duplicate is exact when it adds no use of a hot pseudo; multi-line motion bodies (cg1/cg2/cg5) never (0/5, 71).
Residual kept gotos on the cg dispatch rows: ONE `goto body_N` per case body (3 per row) into the other switch's labelled bodies - retail holds the bodies once,
after the compare chain; 5 + 5 + 3 rows keep these 3 (cg1, cg2, cg5, cg3 81007034 has 10).

## 6. Backward gotos (loops)

Rule (supported by ~40 rows, both directions): **a structured spelling is neutral exactly when retail's loop is a NOTED loop; it breaks the row when
retail's loop had no LOOP_BEG/END notes (m2c goto loop = the source's own goto, or a do/while with a one-trip body) because loop.c, flow's loop-depth
weighting and jump.c's exit-test duplication then start acting.** `why.py --pass loop` loop-count mismatch is the test.

| shape | RESOLVES | tried/exact | held on | NEVER |
|---|---|---:|---|---|
| `if (C) { L: BODY; if (C) goto L; }` / `L: BODY; if (c) goto L;` with counted or pointer-walk body | `for (i = 0, p = base; i < N; i++, p++)`, `do {} while (c)`, `while (1) {..; if (!c) break; ..}` - try all four, the exact one varies | ~45/~22 | 8186F0C4 (2 rotated init+test loops -> for, 6 variants exact), 81832800, 8009F33C, 80093850, 8028BC54, 807AF5FC, 8009C470/C4B4, 8081B82C (4/4), 8032EC84, 800C2BFC (for(;;)+continue/break; two whiles 24, merged while 21), 80FC3000 (while(1)+break; while(cond)+trailer and for(;;) 0/2, dist 17), cg7 3 of 5 loops, cg4/cg5 loops | |
| loop whose exit test needs an invariant recomputed | recompute `p_y = p + K` INSIDE the body (stops loop.c making a third biv) | 1/1 | 800ABBC0 `while (1)` | the form with the hoisted `p_y` (BB728 dist 22-24, 10 variants) |
| `if (x != k) goto after;` as first statement of a do/while | `while (x == k && ...)` / for with x == k in the test | 5/4 | 80098378 | `break` out of the do-while keeps the loop-exit note: loop.c strength-reduces (dist 34) |
| goto exit from a FOR/WHILE body to code right after the loop | `break` (loop already structured) | 4/3 | 81978428, 818D4800 (do/while(1)) | 8009B70C BD8C break dist 47 (exit moves sra/slt tests); s1 80286AF8 goto->break dist 161 (jump.c rotates the exit test) - **conflict, see REPORT.md** |
| goto retry/loop-top with a parameterless function body | `return func_X();` (self tail call compiles to the branch to entry, no loop notes) | 3/3 | 8009399C, 8009A108 (while(1)/for/do-while: 17, loop.c hoists &gameWork into $16, frame 24->32) | exactness holds; whether a human wrote it is an owner call (flagged) |

Backward gotos that STAY (loop.c / loop notes act; rows and the pass that decided it; ~25 rows, 0 structured spellings exact in ~110 tries):
- loop.c hoists an invariant: 800D3B60 (D_8006CCD8 base in $23, frame 56->64), 80FC9000 (move $5,$0, 16-17), 8081E9A4 (lui 992 hoisted, 8), 81809A0C (li 512, 58), 802835B8 (andi 0xff, 13), 818B1664 create_loop (lui 0x190000, total 4), 80098144 (loop depth multiplies config refs 7->9).
- loop.c strength-reduces a giv / adds a counter register: 800A02F0 (addiu $16,$4,12), 8028AE2C outer (area spilled, frame 64->72, dist 98), 800997A4 (frame 40->48, dist 32-41), 800BB728 (hoists p+8, new $3), 818B1664 first angle loop (211), 819B3414 (5 -> 6 loops, $16/$17 swap, dist 38 for every spelling), 8009E0EC inner/outer (94/178).
- greg loop-depth weighting of refs (an added NOTE raises refs 11->16, prio 1078->2091): 8028AE2C inner (32), 98144 (22: $9/$10 swap).
- jump.c rotation / exit-test duplication: w_800407C0 (21-60), 80286AF8 (161), w_80059F8C and w_80059E94 (found: stub physically before loop_start; 35-74).
- 3 cases with NO loop at all in retail: 800C4CE4 (six gotos all part of allocation: map_state/heading_offsets/scan_tile ref+live), 800C6540 (roll/divisor two-pseudo merge via the goto pair: single-var forms 10-21), 8028484C (retry loop 124).

## 7. Labels into blocks (owner rule: still rejected) - where r93 lanes hit it

- 8009E0EC (pg1) staged 9->6 with `set_slot:` inside `if (line_valid != 0) {` and a `goto set_slot` from outside; the lane flagged it; a 7-goto variant with the label in a plain block is in experiments/func_8009E0EC_r1_7gotos.c. Land the 7-goto text, not the 6.
- agy_goto5 (80BCDBA8, 80BD9BA8) and agy_goto4 (80BC1BA8, 80BC7BA8): the kept `goto test_ground/ground_check` jumps INTO the else arm of an if/else (label placed before `if (height_offset == 0)` in arm 2). The 2->1 is a goto-into-block; check the coordinator rule before landing.
- 80095160 (p2) routes returns through `goto move_failed` whose label sits inside an `if` block (base text already had it; the final goto is new). Spelling trade, flagged by the lane.
- cg2 810318E4: `goto empty_selection` -> `if (*sel != 0) {...}` with labels inside the block that still jump within the block (fine: goto and label in the same block).

## 8. Scaffolding removal found in goto rows (volatile / one-trip)

| what | tried/exact | removed together with a goto rewrite (exact) | held (dist) |
|---|---:|---|---|
| `*(volatile T *)&x` reads and volatile struct fields in goto rows | ~70/~8 | 80099EE4 (2/2, with the sequenced `||`), 81844F2C unk_2C, 8032EC84 (signature `volatile u8 *src` + barrier); tptabc dropped 3 volatile casts on 2 rows; cg3 dropped a `static void *volatile` label array | actor+0x60 object store (80BC3AC4 16, 80D13E4C 16, 80D3E260 20, 80CBEF98 22, 810318E4 131, 80DBBFC8 27), 810332A4 display reads 56/66, 818D4800 (2: lhu/lw swap), 8008D69C (14) |
| `do { v = w; } while (0)` / empty one-trip | s1 16/0 alone; ~14/~8 jointly | 80087054, 8009C470/C4B4 (`do { slot = 0; } while (0)` -> `slot = 0;`), 80A4BA70/80A9EE48 (dropped at the split case), tptabc 81988800 (5 `if (0) {}`), 8183E800 (2 `register`) | 80091258 (2), 800914C4 (8: hoists &dungeonStatus into $16), 809F7320 (3: jal slot), 800988D8 (39), 819A0DB8 (45 jtbl), 80C953CC (25), 8102FCB8 (292) |

Pattern: scaffolding comes out in the same edit that restructures the goto next to it (the removed barrier was standing in for the structure the goto had), and almost never alone
(s1: 0 of ~120 respellings, mechanisms: NOTE_INSN_LOOP_BEG/END = sched1 barrier + loop-depth ref weight + cse block end; goto->break dist 161; goto loop -> do/while 32-144).

**Round 93 correction (r93_opus_vb4, dungeon/func_800D1A48 4 pins + 12 volatiles + 2 one-trips + 2 gotos -> 0):**
a goto loop that measures 'retail-faithful' by `why.py --pass loop` loop count when structured may only look that way
because m2c's text keeps TWO lockstep walkers per object (`p` and `p2 = p + K`). Rewrite with ONE walker per pointer
(`quad[k+1]`, `packet + K` as expressions) before concluding: loop.c then combines every giv into retail's single
register (`addiu $18,$20,1`), substitutes single-use invariants into call arguments, and loop-depth ref weighting fixes
colours. Same lesson: r93_opus_p9 (800A02F0 one struct walker), r93_opus_p5.

**r93_sonnet_ct1 (labels-into-block clones 80BC1BA8 x4):** copying the ground-check tail into both arms removes both
gotos and jump2 re-merges the copies, but the extra refs raise entity_base's global.c priority (2424 -> 2735) past a
temp (2727) and swap $s2/$s3 (dist 50). Reading unk_88 through `entity` in both copies = dist 2 (one base register).
Needs an allocation-level fix (Opus): one fewer entity_base ref that still loads through $19, or retail's store order
kept with one more live unit. 80095160: retail keeps its `li -1; j` failure stub MID-function (jump2 merge target);
a plain final `return -1` falls into the epilogue (dist 9).

**Solved (r93_opus_ct2, 5/5 rows, 10 gotos):** (a) the copy-tail clones: after writing the shared tail in both arms, a
callee-saved swap where the pointer's floor_log2(refs)*refs/live sits just above a competitor is fixed by a REF-FREE
duplicate statement in both arms at a barrier-led join inside the pointer's live range (here the motion update
`motion->x.v += ..; motion->y.v += ..;`): it adds live length, no refs, and jump2 deletes it after allocation. Ties
break by allocno number. (b) goto to a mid-function `li -1; j` stub + a trailing goto: put the shared tail after the
nested range checks, give each check `else { return -1; }`, and write the one inline `if (f(..) != 0) return -1;`
right after its test - jump.c cross-jump needs 2 matching insns for a stub right after a conditional branch (survives)
but 1 for a label-headed stub (merges), so every else-stub merges into the surviving mid-function one.

**r93_sonnet_fp2 (pinned rows at equal pins):** a goto directly before its own label: delete it (3/3); a skip-guard goto
-> `if (!c) {...}` wrap (4/4); two gotos onto one label -> invert the test so the label falls through (2/2); 2-4 line
store tails copied at each goto - measure the WHOLE set of copies, single copies were off (3 of 6). A backward goto
into a loop retail does NOT note (`why.py --pass loop` count goes up when structured) never became a structured loop
(0/12 across 5 loops) - leave it. Volatile accessor macros: try per SITE, not per macro (15 of 22 sites came off).

**r93_sonnet_fp1 (dungeon/func_800A8714, 109 -> 7 gotos at equal pins):** `goto L` where L follows a switch whose
`default:` is L -> `break;` + `default: break; }` before L (73/73); a goto ladder over a state variable -> `switch (v)`
in source order, shared-tail gotos -> `break` (1/1); a label with ONE goto -> inline the block there; shared 2-line
`store; return K;` stubs -> copy per site, measure each alone then the union (6 of 10 exact; the union of the exact
six stayed exact); a goto over a statement into an if chain -> invert the first test into a guard.

**Correction (r93_opus_p22):** dungeon/func_800C4CE4 HAS a real loop in retail (the m2c goto web hid it): `for (; i < 8; i++)` with
`break` on accept solved it 3 -> 0 pins + 6 gotos. Do not trust an earlier 'no loop in retail' note without `why.py --pass loop`
on a structured candidate. A computed goto through a D_800240xx text-prefix table can become a compiler-owned switch
(8185CFD4, table read from the retail bytes; the per-row scorer compares table words - window gate confirms ownership).
