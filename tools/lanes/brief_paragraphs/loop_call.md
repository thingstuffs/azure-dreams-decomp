## Goto / walker loops that contain a call (round 85; READ work/native_lane/r85_opus_loopA/REPORT.md)
r85_opus_loopA solved town/func_809542B8 3->0 and dungeon/func_80084084 4->0 with this rule (cdk loop.c 631, 834-868,
1316-1322, 1730, 1818):
- A symbol address used in a loop is a HIGH + LO_SUM pair: the LO_SUM is substituted into its single use (call
  argument / address), the HIGH is an ordinary movable. loop.c hoists a movable only if
  `(29 - 3*moves_so_far) * savings * life >= real insns` (29 = 1 + n_non_fixed_regs in a loop WITH a call; measured: a
  29-insn loop moves the HIGH, a 30-insn loop keeps it). So whether retail's `lui` stays IN the loop depends on how
  many movables came before it and how long the loop is.
- m2c's hand-stepped walkers make the loop smaller and leave that budget unspent; retail's steppers are reduced givs
  of INDEXED loops whose array bases spend the budget (round 83 index rule). Retail's in-loop `lui` = the HIGH shows
  `not desirable` in the `.loop` dump.
- A loop-invariant pointer that retail keeps in a callee-saved register was ASSIGNED INSIDE the loop body (hoisted
  later -> shorter live range -> wins the register; cse1 then addresses loads through its HIGH). Spelling trade OK.
APPEARS: a goto or walker loop with a call + KEEP/REG pins on a page local, a page+K copy source or a symbol pointer.
RESOLVES: index form (`base[i]`, `i*K+C`), integer pages named as the symbols they split, the invariant pointer assigned
in the body, then erase the pins. Count movables/insns from `.loop` when the HIGH lands on the wrong side. Pin-free goto
loops whose structuring makes loop.c hoist a HIGH retail recomputes are retail-shaped: leave them as they are.
More from r85_opus_lp1 (81331C88 5->0, 808216B0 5->0): retail's "goto" interpolation loops were REAL index loops whose
walkers are loop.c's reduced givs - write the table symbol directly in the innermost body so its address pair is hoisted
first and spends the no-call budget (a /7 magic constant then stays in the loop: `not desirable`); a retail register
repeated across two loops = ONE C variable (merge m2c-split variables); drop m2c parameter copies; an address local
assigned before a call is not folded into its later use (combine stops at calls). Add-operand order in the listing
follows how the statement is written (`x = a + x` prints `addu x,x,a`).
