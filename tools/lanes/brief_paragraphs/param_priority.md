## Register-priority swaps on parameters (round 85; READ work/native_lane/r85_fable_regequiv/MECHANISM.md)
cdk doubles the live length of every pointer/int register parameter that is set exactly once (REG_EQUIV to its home
slot), halving its global.c priority. KEEP_NV / ASM_SET / USE_NV / REG pins on parameters (or on m2c copies of them) are
usually a crutch for one allocation inequality. Run `alloc_need.py <row> <erased.c>` first; then:
- If the retail PROLOGUE shows the parameter moved directly (entry move at the top), the parameter is direct and doubled
  in retail too: do NOT add copies - change the COMPETITOR's side (its refs via a real second use, its live length via
  statement position, a narrower or merged local, a loop that weights refs), exactly as alloc_need's inequality says.
- A local copy of a parameter un-doubles it but sched1 treats the copy as a "birthing" single-set insn and sinks it
  (sched.c 2513/2583) - copies only work when retail's copy also sits late.
- Natural second sets that un-double in place: a live conditional set (`if (!p) p = &def;`), a walk (`p = p->next`), a
  narrowing store-back at a masked re-use (`flags = (s16)(flags & -4); if (flags == 0)`, 80BBB094 3->1) with any
  `copy = flags;` hoisted before the first `if`.
- A first-statement typed copy of the LAST hard-register parameter is folded into its entry move by cse (cse.c 7518):
  un-doubled with the prologue unchanged (one parameter per function).
Dead `= 0` inits, stores through the pointer, `p = p;`, call arguments do NOT count as second sets.
- **Proven generator (r85_opus_par1: 800914C4, 8132B8AC, 80819B14 to 0):** when alloc_need says a (doubled) parameter
  needs +k refs, write the statement at the head of a JOIN (after an if/else, at a goto label) that references it into
  EACH arm instead (add an `else` if needed). flow/global.c count every copy's refs; jump2 cross_jump merges the
  identical copies back after allocation, so the bytes do not change. Each copy must follow a barrier in its arm (a
  call, a loop exit, a branch) or sched1 interleaves it and cross-jumping only half-merges. Check (refs+k)/(live+d)
  against the competitor first. Owner ruling: the same statement in both arms is fine (copy-paste style).
- **Spawn clones (r85_opus_spawn, 4 rows to 0):** an s16 (narrow) PARAMETER makes combine merge the entry move into the
  conversion, which is then a scheduled insn (no REG_EQUIV doubling, no head-advance); stores in field order shorten a
  value's life by an insn or two (memory dependence fixes store order); duplicating a trailing store into both sub-arms
  LENGTHENS the competitor's life (cross_jump folds it back). Combine levers until prio.py shows the tie broken the
  retail way; a two-step `x = p; x += K;` leaves a (use x) that lengthens lives - write it as one statement.

Entry-move run (r86_opus_oc4, 800AC008): cdk sched.c 3248-3270 leaves the LEADING run of parameter copies from hard
registers unscheduled. When cse folds an earlier `x = earlier_param` copy, its deleted note ends that run; the next
parameter's entry move is then scheduled and, as a single-set pseudo, birthing-boosted and sunk. Use the earlier
parameter directly and the prologue order comes back.
