## Copies that re-head a cse class (round 85; READ work/native_lane/r85_fable_cshead/MECHANISM.md)
cdk cse.c make_regs_eqv (856-870): for a copy `y = x`, y becomes the class head (every later use of x reads y) when y's
last mention is later than x's AND y lives beyond the extended cse block (which runs to the next LABEL, not the next
jump) - or always when x is a hard register (parameter copies). Pins (KEEP/USE/REG) on such copies hold retail's
choice. Natural spellings that keep retail's head: NARROW the copy (`u16/s16/u8 y = x`) when y's uses are masks /
compares / narrow stores - a subreg copy gets its own qty and combine folds the extension (800AF51C, w_80052A90,
800B50B0); use the parameter itself instead of a copy; a later real read of the original keeps it head. Check the .lreg
dump too: local-alloc optimize_reg_copy_1 (704-869) rewrites the original's remaining reads to the copy when the
original dies in the copy's block - same visible effect.
