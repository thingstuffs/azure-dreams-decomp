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
