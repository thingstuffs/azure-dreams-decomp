## Unboosted retail insn = a second set that leaves no code (r85_fable_birth, 2026-10-01)
sched1 (cdk sched.c 2513-2545/2583) gives max priority to a SET whose REG dest is live and has reg_n_sets == 1 - counted
after flow's dead-insn deletion and combine's folding (flow.c 1962-2120, combine.c 2368), SET or CLOBBER, pseudos and
hard registers alike - and emits it as late as its dependents allow. When `why.py --trace` tags the moved insn
`[launched: birthing boost]` and retail has it earlier, retail's destination was multi-set. Only four second sets cost
no instruction: (R) a RE-READ of the same field into the same variable after a store to the struct (`v = p->a;
... p->b = t; v = p->a;`): cse keeps it, sched1 hoists it next to the first load, reload_cse deletes it (reload1.c
8049) - same variable, no label between, the first value used before it, every store between through the same base
at another offset (818E6800 3->1); (P) the variable is the PARAMETER (its entry move counts but is never scheduled,
sched.c 3252) - keep two uses before the reassignment or combine folds the entry copy; (H) hard registers: $2 per
non-void callee declaration or `return`, $4-$7 per call; (S) a same-value re-copy of a REG-pinned hard register (a
crutch). A dead `= 0` init, a self copy, a pseudo re-copy or `x = y; x = x + k` never count. Both boosted = LUID tie.

**Owner ruling 2026-10-02:** form R is ACCEPTED (it leaves no code: reload_cse deletes it). Form S (a same-value re-copy of a REG-pinned hard register) stays FORBIDDEN as a fake dependency. Only the four no-code second sets listed above qualify; say in the report which form you used.
