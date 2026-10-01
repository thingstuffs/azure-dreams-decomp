## Rows registered with a per-row CRUTCH FLAG on the main compiler (rounds 81-85)
The module's real build is plain `2.7.2-cdk-G0` (src/<container>/INDEX.md module column; STATUS.md "Likely incorrect
compiler"). A per-row -f flag was fitted, usually hiding a SOURCE SHAPE. TARGET = plain `2.7.2-cdk-G0` (drop the flag),
erase all pins there first, then fix the shape the flag stood for (tools/learnings/pin_removal_possibilities.md):
- `-fno-strength-reduce` -> index loops (`base[i]`, counter as loop variable), derived cursors deleted, s16 counters
  (Round 83); a hand cursor `q = p + c` beside a walker resets the giv group (Round 84).
- `-fno-cse-follow-jumps` / `-fno-cse-skip-blocks` -> re-reads after struct stores, integer pages as split symbols,
  parameters used directly; ASM_REG pins joining a parameter's cse class are the real issue (Round 84 cse).
- `-fno-expensive-optimizations` -> local-alloc optimize_reg_copy_1 retargets copies: multi-set result carriers / u8
  locals (Round 81); cdk has reload_cse_regs (zero accumulators' width, Round 85).
- `-fno-schedule-insns` -> sched1 order: single-set locals for loads (birthing boost), struct-field spellings for
  MEM_IN_STRUCT dependences, statement order (sched1 ties break by source order) (Round 84 class C).
- `-fno-rerun-cse-after-loop` -> loop.c structure (loops with calls, Round 85 loop_call paragraph).
- `-O1` on a resident-image row -> not the -O1 debug family (that is only the town 0x8032E2BC run): a crutch.
Stage with `lab.py stage-cell <row> cand.c --cfg "2.7.2-cdk-G0" --note "..."` (`--equal-pins` for pin-free or equal-pin
rows - a flag retired is a landing). Never stage at a cfg that ADDS a flag.
