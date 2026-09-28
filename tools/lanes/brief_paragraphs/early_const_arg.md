## Research task: the early constant argument (r78_opus_c19)

This is a MECHANISM lane (research credit: a demonstrated mechanism, its population, a reusable artifact, a next
step). On these rows retail loads a constant argument register BEFORE the other argument computations
(80921B2C `li $4,530`, 800A6018 case 3 `li $7,2`, 80DE48EC `li $6,8`); the pinned texts fake it with ASM_REG/KEEP.
Measured (c19): gcc 2.7.2 calls.c:1615 loads register parameters in order after all argument values are expanded
(no PUSH_ARGS_REVERSED on MIPS), so the constant load gets the block's highest LUID; sched1 rank_for_schedule
breaks the priority-1 tie by LUID; cse propagates every pseudo spelling; the address cannot move above it
(anti-dependence on the last call, sched.c:1732).

1. Find the C construct that gives a constant argument load an early LUID or a higher sched1 priority. Read
   calls.c (expand_call: precompute_register_parameters, the order args are computed, when an argument is
   evaluated into a pseudo before the call sequence), cse.c and sched.c for the row's cell. Candidate ideas to
   test, not assume: an argument whose value is a real join of two paths; a K&R-defined or unprototyped callee
   (default promotions change expand order); the constant passed through a variable also used after the call; the
   call written as the operand of an expression; argument order / evaluation of a nested call argument.
2. Size the population: how many pinned rows show this pattern (pin comments "rematerialises a constant retail
   keeps in a register" = 128 pins in 75 rows is a candidate superset - check a sample of 10 with erase.py).
3. Deliver: the mechanism with dump evidence, the construct (or a measured negative with the passes that rule
   each idea out), the population estimate, and any row made exact (staged normally).
