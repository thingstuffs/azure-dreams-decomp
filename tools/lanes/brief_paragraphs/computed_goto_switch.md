## Computed-goto dispatch -> real `switch` (r93: cg1-cg7 + tptabc; 41 of 45 cg rows exact, 10 of 10 tptabc rows exact)

Supersedes the "text-prefix tables are out of reach" line and the "label array order = table order" assumption in tools/lanes/switch_lane_brief.md.
Existing text still holds for: ladder-to-switch in source order, guard deletion, end values only on `default:`, no invented cases.

**1. READ THE RETAIL TABLE FIRST (`bin/rtab.py`, from tools/lanes or the r85 bin; `rdis.py` for the words' code addresses).** The m2c `&&label`
array is NOT retail's table when the table is an extern symbol: the labels were assigned by guessing. Old arrays were wrong on 5/5 12-entry rows (cg3: 8 and 9 swapped or
shifted), 4/6 (cg4), 4/7 (cg5), 2/2 town rows (cg6), at least 2/6 (cg7: missing or shifted entries). Build the case list from the table words, not from the label array, and write every
`case K:` at the code address word K holds. Old text sometimes ran the wrong block for some state and only matched because the table was extern; the real switch
fixes that (cg4 80E3A578, 80E8EC28; cg6 80956A00).

**2. Mid-body entries.** A table word that points INTO a block the old text had as one unit means: split the block there and put `case K:` at the split; the
previous case falls through (no `break`). Seen on at least 20 of the 55 rows: 81252D6C (entry 2 mid case 1, after `func_800A56E0(0x703)`), 80A4BA70/80A9EE48 (case 2 after
`unk_1C &= ...`, case 6 label sits BEFORE the `if (unk_9B != 6) return;` test so case 5 falls into it), 809A10A8/812A7C08 (case 4 mid old L4, after the `unk_A0` clamp;
old L1 is the continuation of case 0), 80E3A578, 80E8EC28 (case 1 mid case 0 after `unk_9B++`), 809A1D60 (case 1 = tail of state 0), 80D67FF8/80E63794 (case 4),
town 80956A00 (case 1 falls into `case 2:`) and 808141B8 (the address-taken `checked:` label IS table entry 1 - a real `case 1:`; it was load-bearing because the
CODE_LABEL splits the basic block, no kept label needed), 81887004/818B1664/8190B2D0 (case 1 mid case 0), 819A0DB8, 8188C800 (case 4 mid case 3), 80FDB6A8
(`case 9: unk_98 |= 0x8000; case 8: test` - the source had case 8 first = jtbl-mismatch). A local that was declared inside the old nested block must be hoisted to function scope.
A `do { x = ..; } while (0)` sitting at the split is dropped with it (exact on 80A4BA70, 80A9EE48).

**3. Holes and ends.** An entry that points at the switch END / default block needs no `case` when it is interior (gcc only needs the ends). An entry that points at
the JOIN label (not the default arm) IS a case: `case K: break;` (80D68D0C angle[0] = 0x2D4 = angle_store; without `case 0:` the table collapses, dist 255; stacked on
default: jtbl-mismatch word 6). An entry that points at a shared tail block inside the switch is a case (819A0DB8 `case 1: case 5: case 10:` on the shared +0x20 increments;
case 10 = table length 11). Symmetric tables prove every value (81971510: 20 entries -> `case 0: case 9: case 10: case 19:` ...).

**4. Nested second-table switches with `case -1`.** `goto *D_80170838[(s16)(f()+1)]` (5 entries, [0]ret [1]s0 [2]ret [3]s1 [4]s2) = `switch ((s16)f()) { case -1: case 1: break; case 0: ..;
case 2: ..; case 3: ..; }`. The minimum -1 and the holes at idx 0/2 are PROVEN by the retail table (80E0D894: 2/2 exact with -1 and 1; 0/3 with only 0,2,3, 0/3 with -1 only):
cc1 2.7.2-cdk emits a jump TABLE only at >= 5 case nodes after group_case_nodes (stmt.c CASE_VALUES_THRESHOLD 5); with 3-4 nodes it emits a compare chain, so the table's
existence is the evidence for the extra values. `case -1: case 1: return;` is the same bytes.

**5. The 7-entry "kind" dispatch** (`goto *T[(v & 0x3FFF) - 1]`, `if (idx >= 7) goto none;`; table: v1,v2,v3 -> the three non-player bodies, v4 -> default, v5,v6,v7 -> stubs `use = 1; goto body_N`)
is one scripted shape on ~25 rows (D_80170838/50/58/60/78/80/98 family; cg1, cg2, cg3 81007034, cg4, cg5, cg3 table D_80170808 12-entry variant: v1,2,3 aaf call; v4,10,11 default;
v5,6,7 facing body falling into v12; v8, v9 own bodies):
```
if (flags & 0x2000) switch (v & 0x3FFF) { case 7: use = 1; /*fallthrough*/ case 3: goto body_3; case 6: use = 1; case 2: goto body_2; case 5: use = 1; case 1: goto body_1; default: sel = 0; break; }
else               switch (v & 0x3FFF) { case 3: body_3: ..; break; case 2: body_2: ..; case 1: body_1: ..; default: ..; }
```
Orders: 7,6,5 first for the flagged switch; the else arm 3,2,1 (1,2,3 first in the flagged h-form = jtbl-mismatch). 7/7 exact (cg2), 6/6 (cg1, 5 keep 3 gotos), 3/3 (cg4, bodies
duplicated into the first switch because they are ONE line: `item_slot = actor + 0xE`), 2/2 (cg5). When there is no second compare switch sharing the bodies the stubs are a pure
fallthrough PREFIX with no goto (809A1D60: `case 7: base = 1; case 3: addr = +0xE; break;`). The 3 remaining gotos per row (`goto body_N` into the other switch's bodies) stay: full duplicates
0/10 (text off 71: $s0/$s1 swap of actor/motion, bodies placed inline after the stubs while retail has stubs jumping to the later copies). cg4 duplicated the one-line bodies exact: duplicate only
when the body adds no hot-pseudo reference. When the index temp is a separate local (`special_slot`, `slot`, `kind`) keep it as the switch variable (`switch (special_slot)`): plain expressions gave 4 subs (80EB6FC8, 81252D6C).
Other fixes on these rows that were exact 5/5: `if (*sel == 0) goto empty; ...; empty:` -> `if (*sel != 0) {...; return;} <empty>`; hi/lo split `anim_table = (u8 *)0x80170000; ... += 0x41B4;` -> `anim_table = &D_801741B4;` after the chain.

**6. Score with `LANEKIT_SCORE_NEAR=300`** (the switch moves the table; listing distance 41-162 on exact rows) and read `status ok` / "not jtbl-mismatch". `lab.py` prints `jtbl-mismatch` when only a table word is wrong: that is
a case-label placement error (the table words are the oracle), not a codegen mystery. Fixing the split point by table word is a 1-compile loop.

**7. Ownership classes - decide before writing C (`bin/composites.py`, tools/lanes r85):**
- **Works today** (cg1-cg7: 41 rows): the table symbol is extern data OUTSIDE the row (module data `D_801708xx`, `D_80024008/28/50/88` in the prefix before the row's link range, town `0x800201A0`, `0x805267C8`).
  The switch's own `.rdata` table lands in the TU; jtbl check passes; no record, no cell change. Land with the normal lander + gate_all for the windows.
- **OWNER** (tptab step C, 10 composite dungeon rows 81838800 8183E800 81844800 81856800 8188C800 81988800 8199A800 819A6800 819AC800 819B2800): retail stores the table in `.text` right before
  the function (entry pointer `D_80024000`, `.align 3` pad, N-entry table at 0x80024008, function at 0x8002401C/20/50). The row OWNS its `.rodata`: text shape = forward decl +
  `void (*const module_entry)(...) __asm__("func_80024000") = func_800240xx;` + the function renamed to its code address + the real `switch`. Needs a record in
  `config/overlays/dungeon.rodata_owners.jsonl` (`azure-clean.rodata_owner.v1`: id, foff, rodata_size, function, rodata text) - 10 records + 10 texts land TOGETHER (without the records:
  "`.rodata' referenced in section `.text.func_8002401C' ... defined in discarded section `.rodata'"). `switch_land_lanes.sh` does NOT append records; follow LANDING.md. A 5-entry table pads `.rodata` to 32:
  record `rodata_size` 28 ("4 B cut", 8199A800, 81988800, 819B2800 - all MATCH). All 10 exact in an isolated gate root, 7 windows MATCH; plain gotos 61 -> 3, computed 10 -> 0, volatile 3 -> 0.
- **MULTI** (a window with several tables / rows that need a re-carve): none met in r93 (composites.py classified all 10 tptabc rows OWNER; cg7's 6 rows have no `.text` prefix array in the source, composites.py printed "?"). Treat as a separate owner/carve job, do not hand-write.
- **cg7 8195281C and 8195E81C**: text exact except ONE word (table address `addiu`, 16392 vs table orphaned after `.text`): the 5-entry table sits at 0x80024008..0x8002401C directly before the row at 0x8002401C,
  gcc pads the placed `.rdata` to 8 and the placed table overlaps the row's .text by 4 B -> placement refused. These look like the same 5-entry-pad OWNER case tptabc solved (rodata_size 28). composites.py printed "?" because
  the SOURCE has no `.text` prefix array; build the prefix (entry pointer + pad + table) and the owner record, then re-score (HYPOTHESIS, not run). Texts: r93_sonnet_cg7/out_pending/dungeon/.

**8. Town blockers (cg6) - two rows stay at computed gotos:**
- town/func_806D835C (func_80016B5C): text and jump table right (read retail idx0..7 = +A8 +B0 +E0(default) +B8 +C0 +C8 +D0 +D8; the old array had the wrong order) but the table's address shares the 0x8001xxxx PAGE with a `D_80010000`
  load: retail CSEs the `lui` between the two symbols (both numeric 0x8001 after the symbol rewrite); a switch's local `%hi(L0)` cannot share, so loop.c hoists `lo_sum(high D_80010000)` into $19 (frame 32->40). Six switch spellings, same difference. Needs the table symbol (page lui sharing), not a spelling.
- town/func_808119EC: one `slot`/table pointer was live across TWO loops in the original; the switch makes it live only in loop 1 (priority 11666 rank 1), so $s1/$s2 swap (dist 56, 59 declaration permutations); pin ASM_REG $3 kept. Lead: a way to keep loop 1's pointer live across loop 2.
- Rule: a table address in the same page as another symbol the loop reads, or a pointer shared across loops: leave the computed goto, report.

**9. Residual kept gotos (cg7: 46 plain -> 4 over 6 rows; 3 per row on the kind-dispatch rows):** backward loops that loop.c would hoist (818B1664 loop_0 and create_loop: do/while, while, for(;;) all inexact), tails whose copy shifts crossjump
(818B1664 reset_state jtbl-mismatch; increment_reset vs increment_state families: either copy exact alone, together 97 subs), `goto copy_active_coords` into an `if (target)` block (80C6B878 268, 80AC7A30 jtbl, 80E639C8 25: the copy adds refs to actor/sprite).

**Never worked here:** full duplicate bodies in both switches (0/10); `case 0..4` cases dropped from a state table where retail's table has them (collapses the table); stacking an interior hole on `default:` when
retail points it at the join (jtbl word wrong); state switch with `case 1:` where retail's mid-body entry is elsewhere (jtbl-mismatch); removing the volatile actor+0x60 store (0/6: 16-131); guessed case ranges
(8185CFD4 pg3: 0-5/6/7-13 gives dist 446 - own table + different prologue; read the retail table or leave it).
