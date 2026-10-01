## Argument-register setups and copies held at their statement position (rounds 80 + 85)
READ tools/learnings/pin_removal_possibilities.md "The early constant argument - SOLVED as a rule" and the MOVED-class
triage after it. A pin that keeps `li/move $a0-$a3` (or a copy feeding a store) at its statement position stands for a
sched1 priority fact: `birthing_insn_p` boosts a producer whose register is set ONCE in the function. Rule A: the arg
register is set once -> retail had a second set (a call below the callee's DEFINED arity - pass the parameters
through; jump2 deletes the moves). Rule B: a competitor lost its boost because m2c reused one variable for several
roles -> give each role a FRESH single-set local of the field's width. Also: a pointer local assigned BEFORE an
intervening call keeps its `addiu` unfolded (combine never crosses a CALL_INSN); a constant written at its store plus
per-role compound assignments parks a late `li` (sched2 LUID tie). Run `why.py --pass sched --trace --block <b>` and
name which insn is boosted before spelling anything.
