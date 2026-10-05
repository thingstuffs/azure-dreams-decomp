## Copies that re-head a cse class (round 85; READ work/native_lane/r85_fable_cshead/MECHANISM.md)
cdk cse.c make_regs_eqv (856-870): for a copy `y = x`, y becomes the class head (every later use of x reads y) when y's
last mention is later than x's AND y lives beyond the extended cse block (which runs to the next LABEL, not the next
jump) - or always when x is a hard register (parameter copies). Pins (KEEP/USE/REG) on such copies hold retail's
choice. Natural spellings that keep retail's head: NARROW the copy (`u16/s16/u8 y = x`) when y's uses are masks /
compares / narrow stores - a subreg copy gets its own qty and combine folds the extension (800AF51C, w_80052A90,
800B50B0); use the parameter itself instead of a copy; a later real read of the original keeps it head. Check the .lreg
dump too: local-alloc optimize_reg_copy_1 (704-869) rewrites the original's remaining reads to the copy when the
original dies in the copy's block - same visible effect.

Loop-tail shadow copies (r85_opus_q3): local-alloc optimize_reg_copy_1 (cdk local-alloc.c 704-869) rewrites `e = n` to read another copy of n only when the REG_DEAD note's mode equals the source's mode. If a pinned loop tail `t = n; ...; e = n;` (KEEP between the copies) needs retail's `move e, n`, declare the shadow `e` 16-bit and put its copy last. This works only when n is a hard register (818BDEBC 6->4).

Field-width locals escape the boost (r85_opus_bg20): a single-set s32 local that is only stored to an s16 field gets sched1's birthing boost. Declared at the field's width (s16/u16/u8), combine turns the store into a subreg-destination set, which is never boosted, so the value follows source order. Try this before reaching for a KEEP/REG pair that fakes the order (8028A5D8 5->1).

**Round 93 correction (Fable, tools/learnings/fable_r93_c9858.md):** 2.7.2 does not promote LOCALS - a `u16`/`u8` local
is a HImode/QImode pseudo; stored both narrow and as s32 the zero-extension survives as `andi 0xffff` unless combine
validates the load. Declare such a local s32 where retail has no andi. A stack PARAMETER m2c types s32 but tests as
`(p << 16) == 0` is an s16 parameter: declare it s16 (same bytes for the test; changes its REG_EQUIV-doubled rank).
