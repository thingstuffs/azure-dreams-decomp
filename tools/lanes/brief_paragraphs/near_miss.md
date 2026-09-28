## Near-miss conversion (round 78, r78_opus_c13)

These rows sit one or two instructions from exact at fewer pins. Start from the prior best text (evidence/),
re-measure it, then attack the ONE remaining difference. The round-78 conversion that worked: when an insn lands
one slot late because it TIES in sched1 priority with a neighbour (often after combine merged it into a call
argument, so no source order moves it), change the NEIGHBOUR instead - compute that value into a fresh local
assigned exactly once, so `birthing_insn_p` gives it launch priority (sched.c adjust_priority), then copy it
where the old variable was needed. Also consider: what the value IS (struct member, real parameter, second use)
rather than where the statement sits. Report the residue's deciding pass with the dump line that proves it.
