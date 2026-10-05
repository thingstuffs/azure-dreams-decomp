# Fable r93 (dungeon/func_800C9858, 15 pins): compiler facts and drop-in guidance

Source: work/native_lane/r93_fable_c9858 (RETRO.md, REPORT.md; best pin-free text cand/best_k1b.c, total 29 - the
frontier for this row; r86 c6 was 74). Corrections to earlier briefs:
- **2.7.2 does not promote LOCALS**: `u16 x;` is a (reg/v:HI), `u8 b;` a (reg:QI) (stmt.c expand_decl uses DECL_MODE);
  only parameters/return values are promoted. Every 'narrow local behaves like a register' argument must account for it.
- **KEEP on a constant base has two effects**: the argument constants were already folded by cse (prologue shape), and
  the base becomes OPAQUE to sched1's alias analysis (stores alias everything -> block order). A pinned text can be exact
  partly BECAUSE of the second effect; a pin-free text needs a real dependence for those stores.
- gameWork page pins: the integer page 0x80080000(+0x3160) is HIGH(gameWork) - `GameWork *gw = &gameWork` (include/game_work.h).
- `lab.py --subs` applies each pair to the FIRST occurrence only; identical arms need the pair twice.

## 4. Guidance (drop-in text for briefs / learnings)
- "2.7.2 locals are not promoted: a `u16`/`u8` local is a HImode/QImode pseudo. Stored both narrow and as s32, the
  zero-extension survives as `andi 0xffff` unless combine can validate the load (hard-register base). Declare the local
  s32 (byte-neutral where retail has no andi)."
- "A stack parameter m2c types `s32` but tests as `(p << 16) == 0` / copies into an s16 is an `s16` parameter. Declare it
  s16: the test becomes `p == 0` (same bytes) and the REG_EQUIV-doubled parameter's allocation rank changes
  (dungeon/func_800C9858: ORDER verdict gone)."
- "cdk `extendqisi2`/`extendhisi2` expand a (s8)/(s16) of a MEM as lbu/lhu + sll + sra (mips.md force_not_mem); combine
  folds them to lb/lh unless a store/call sits between the load and the first shift (use_crosses_set_p), the MEM is
  volatile, or the destination is a paradoxical SUBREG of a multi-set HI variable with shortened arithmetic. A second use
  of the byte does NOT keep lbu (combine duplicates the load). Retail `lbu; sll 24; sra 24` with SI arithmetic and no store
  between is therefore an OPEN class: do not sweep spellings on it; measure which of the three blockers retail used."
- "A single-set constant pseudo's HIGH/LO_SUM pair cannot cross a CALL in sched1 (calls set every pseudo); its source
  position relative to the calls is the one that matters, not its distance from the use."
- "`x -= K` on a struct field creates a fresh single-set temp = birthing-boosted load placed late; m2c's shared temps are
  multi-set = unboosted loads placed early. When retail's loads interleave ahead of the previous chain's add (`lhu A; lhu
  B; add A; sh A`), B's temp was multi-set. Check with `why.py --pass sched --block bN --trace` before choosing the
  spelling; a shared temp also chains the F0->F2 priorities (anti-dependence) above independent stores."
- Brief paragraph for big m2c rows: "Do NOT rewrite the whole function from the listing; take the lane's frontier text,
  classify (diff.py --scorer --classify), alloc_need, and fix one verdict per variant. A 1-statement change that moves 40
  listing lines is normal; a 300-line rewrite is unmeasurable."

## 5. Mechanisms for this row's pins (learnings draft)
- pins 1,12 (REG $8 global_page + ASM_SET): the integer page 0x80080000 is HIGH(gameWork); `GameWork *gw = &gameWork`
  with `gw->unk_000` for the first word -> cse keeps `lui $8,%hi; lw $3,%lo($8); addiu $23,$8,%lo` (c6/k1b exact there).
- pins 5,6 (REG $20 part, $21 sprite_data) + 7,10,13 (REG $17 sort_bias, KEEP_NV(sort_bias), KEEP(bias_copy)): the
  parameters used directly + the structured `for (;;)` loop (loop.c reduced giv `addiu $17,$20,1` = part+1 is the walker's
  field accesses; `addiu $16,$19,4` = the POLY_FT4 x0 giv) -> callee-saved order comes from flow's loop-depth refs
  (r86 mechanism, holds in k1b: 29/29 allocnos right).
- pins 8,9 (KEEP_MEM_NV(screen_out), KEEP_DEP_NV(depth_out)) + 3,4 (REG $4/$6 scratch args): constant scratch arguments
  folded by cse; `move $18,$4` is reload_cse (r86). k1b exact in the prologue/setup blocks.
- pin 2 (KEEP_NV(orient_mode)): the fifth parameter is `s16`; as s32 it is REG_EQUIV-doubled and loses its $s4 rank
  to the camera-matrix pointer (global.c floor_log2(refs)*refs/live).
- pin 11 (KEEP_MEMDEP(sprite_data, state_dep, gameWork)) and pin 15 (KEEP_NV(scratch), the opaque base): the one that
  still stands for something - the block-1 RMW interleave: retail's BA load is unboosted (multi-set temp) and the `sw vec`
  stores need a dependent (opaque base gives it). Deciding pass sched1 (birthing boost + LUID ties), then local-alloc
  colours, then sched2 hoists. Open.
- pin 14 (KEEP(bias_copy)) and pin 0 (REG $2 segment_angle): fall with the parameter-direct spellings (k1b exact there).
- the base's 2 volatile part bytes (counted like pins): combine's lbu->lb fold; the only non-volatile blockers are a
  store/call between or a multi-set HI destination with shortened arithmetic (recolours). Open.

## 6. Late notes
- Admission gate detail worth stating in briefs: a candidate that KEEPS some of the base's volatiles but removes ASM pins
  is admissible (volatiles are a subset). Here it is refuted by evidence (retail's giv addressing of the volatile-candidate
  bytes), but on other rows a base volatile may be retail-real and should not be dropped reflexively.
- Two levers I would hand an Opus lane for this row, in order: (1) find the block-1 spelling: a known-constant scratch
  base, the BA (y0) load unboosted and placed at pos 2, `sh F2` above the `sw vec` stores (needs a dependent for those
  stores or a LUID tie they win) - trace with `why.py --pass sched --block b1 --trace` after each try, do not sweep;
  (2) the `lbu; sll 24; sra 24` class: measure retail siblings (other dungeon rows with `lbu; sll 24; sra 24` on
  non-volatile bytes, e.g. the 800AFA68 world loop) for the C shape that keeps it with SImode arithmetic; the mechanism
  table in REPORT.md narrows it to a store/call between the load and the shift or a multi-set HImode subreg destination.

## Birthing boost: what "live" means (r93_sonnet_kit1, measured on 800C9858 block 1)
sched.c schedules each block BACKWARDS, so at a pick `bb_live_regs` = the block's live-out set PLUS the sources of insns
already scheduled (i.e. later in forward order). birthing_insn_p's "dest live" therefore means "used later in the block
or live out of it", not "live at block end": plain live-out disagreed with the observed boost on 17 of 27 insns, the
corrected rule agreed on all 27. `why.py --pass sched --block bN --deps-table` prints both (birth = static test,
boost = observed) and flags disagreements.
