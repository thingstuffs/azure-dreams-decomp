## NEW (round 97, 2026-10-07): what paid on rows strong models had already failed - try these first

1. **Split a multi-role REG carrier ROLE BY ROLE with the pin kept** (town/func_809548E4 $2, r97_opus_a4): an
   all-or-nothing pin becomes one distance per role. Give each role a fresh variable while the pin stays on the rest;
   most roles are exact as plain block-locals; delete the pin once every role is exact. Keep two roles of ONE case
   together when splitting them removes a sched1 anti dependence (88-94 split vs 0 together).
2. **One store after an if/else-if chain** instead of a store + `goto` per arm (town/func_8095563C KEEP, r97_opus_a1):
   with one source store jump2 has no identical pair to cross-jump, and reorg fills the arm's j slot from the target
   thread like retail (check `dbr.py`).
3. **Make a hoisted invariant non-invariant naturally** (dungeon/func_81989558 KEEP_NV, r97_opus_a3): compare
   `lanekit/loopsum.py` on pinned vs erased - if the erasure HOISTS a value out of the loop, a value set twice in the
   loop (an accessor whose parameter is updated in place) is refused by consec_sets_invariant_p.
4. **Break a local-alloc priority tie by staging or moving** (800995D0, 809548E4 far_y, 8028BAA4): split pointer/flag
   roles into block-locals, stage a load into a block local so its chain outranks the competitor, move an independent
   struct store between a load and its use (sched2 restores retail's order); a two-set element address
   (`p = &a[i]; p--; x = *p;`) escapes the birthing boost.
5. **Copy through a variable whose last mention is this block** (800A8714 KEEP_NV): it never becomes the cse class
   head; update the source in place to stop optimize_reg_copy_1.
6. **Constants feeding a store run: try the ORIGINAL macro store order before fighting the boost** (dungeon/func_81976CB0
   KEEP + one-trip, r98_opus_birth): write the packet stores in libgpu macro order (setClut, setUV3 with literal u/v,
   setRGB0/1/2) with no staging locals - retail boosts the constants too; consecutive consumer stores make the boost tie
   fall to LUID order. Also: a REG pin whose role-split leaves no role exact is an allocation pin (one multi-role global).
REFUSED this round: negate-then-subtract (`b = -b; y = x - b;` for `x + b`) is cancelling arithmetic (decision 25).

## NEW TODAY (2026-09-24): what round 76's lanes found - try these first

1. **Set-exactly-once (25 of round 76's 43 removed pins).** An `ASM_KEEP(v)`/`ASM_REG` pin is itself a SECOND set of
   `v`. A pseudo with `REG_N_SETS == 1` gets sched1's `birthing_insn_p` priority boost and local-alloc's REG_EQUIV
   live-length doubling; the pin exists to cancel or fake that. So ask of every pinned variable: in the original, was
   it set exactly once, or more than once? Moves that paid: use a parameter directly instead of a `T x = x_in;` copy;
   fold an in-place update chain into one set (`v = E; v >>= k;` -> `v = (E) >> k`); route a call's result through
   the kept copy; drop a `volatile` access together with the register pin it propped up. Precedents:
   `docs/evidence/pin_research_round76_move_table.md` rows 1-10.
2. **Dead initializer is ordinary C (owner ruling 2026-09-23).** `T *p = 0;` / `= NULL` at a declaration that the
   next statement overwrites is allowed: it adds a set, which is sometimes exactly what retail's allocation needs.
3. **sched2-off signature.** When the remaining pins and one-trip blocks only stop a load-delay slot being filled
   (retail shows a `nop` where post-reload scheduling would move an independent insn), run
   `lab.py cellscore <row> <cand.c> --cfg "<row cfg> -fno-schedule-insns2"`. If the PINNED text is also exact there,
   a pin-free text at that recipe is a legitimate trade: report it with the hand-over line (two town rows paid this
   way, func_8032E364 and func_8032FD1C).
4. **Inline helpers (2026-09-21, still live).** Repeated expression shapes next to pins, or runs of `ASM_USE*`
   padding, may be a small `static __inline__` helper with narrow (`s16`/`u8`) parameters or return in the original;
   `cc1 -dL` shows the loop's "real insns".
