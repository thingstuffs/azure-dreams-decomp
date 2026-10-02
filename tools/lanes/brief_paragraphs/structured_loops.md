## m2c goto loops hide loop.c: write the STRUCTURED loop (r86_fable_mech, 2026-10-02; READ work/native_lane/r86_fable_mech/MECHANISM.md)
80DB9000 went 20 -> 0 with this. Retail's loops were real loops, so cdk loop.c ran on them; m2c's `label: ... goto label;`
removes every loop.c effect, and the pins imitate four loop.c decisions plus flow's loop-depth weighting:
1. loop.c 834-868 substitutes a single-use invariant `tmp = base + K` straight into its use (`addiu aN,$sX,K`). In a
   goto loop, combine sees `plus` on a known constant and emits `ori` instead.
2. move_movables (1730/1818) hoists a loop-invariant constant iff `(29 - 3*earlier_moves) * savings * lifetime >= real
   insns`. Lifetime is in luids, and every non-line NOTE has a luid, so a nested `{ }` scope can add the one luid that
   decides it (a load-bearing scope is a spelling trade to record). Retail values set BEFORE the loop = `moved`; values
   recomputed inside = `not desirable`.
3. strength_reduce + combine_givs fold all `walker + const` address givs of ONE walker into ONE new register whose offset
   is the LAST giv in insn order. Retail's "second walker" register (`addiu $s0,$s3,8`) is that reduced giv, not a C
   variable: use ONE walker struct with every access a field (a union for overlapping roles).
4. flow weights refs by loop depth, so callee-saved order comes out by itself; use parameters directly (an m2c copy of a
   parameter makes a short allocno that outranks the real one).
"Retail keeps the scratchpad base 0x1F800000 opaque" is REFUTED on all three rows: `move $17,$6` is reload_cse reusing the
RotTransPers argument's `lui`. Do not pin scratch bases for that.
APPEARS: an m2c label/goto loop (often with libgte calls), a lockstep second walker `p2 = p + K`, KEEP/REG pins on a page
or scratch base, hard-register argument carriers, KEEP_DEP on a mask. RESOLVES: `for (;;) { ... if (cond) break; p++; }`
with retail's single tail; one walker struct; parameters direct; scratch arguments as `base + K`; PsyQ `P_TAG` /
`setaddr` / `getaddr` for OT links; ONE exit statement (cse.c 8150 follows a one-use branch target and folds a duplicated
exit's load); no `volatile` on walker bytes (volatile bytes are not givs). A `(s8)` byte stored into a MULTI-SET s16 keeps
retail's `lbu; sll; sra` (combine merges a plain single-use load into `lb`). Then read the `.loop` dump (`why.py --pass
loop`): every `moved`, `not desirable` and `reduced to` line must match a retail register/position; adjust luid lifetimes
(statement order, scopes) until the thresholds match.
Also from r86_opus_oc1 (8187A9A8 13 -> 0, retiring a fitted 2.8.1 cell): read game state through `GameWork *gw = &gameWork;
gw->unk_000`, not through `*(S **)&gameWork` or a direct `gameWork.unk_000`. The struct-pointer read is a struct memory
access, so sched1 keeps it after an OT-link bitfield store (a dependence edge in the sched dump). The other spellings
let it float above the store.
