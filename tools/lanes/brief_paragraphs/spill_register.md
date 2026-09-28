## Family: pins that fake reload's spill register ($8 / $12)

Two lanes this round removed pins by recognising that an `ASM_REG("$8")` (or `$12`) binding was imitating
RELOAD, not a user variable: in a function whose callee-saved registers are all taken, global.c spills some
pseudos to the frame and reload rebuilds them in the first free spill register ($8 on these rows, $12 on
another), so retail shows `lui/addiu $8`, `lhu $8,N($sp)` or `mflo $12` next to ordinary code. Exemplar diffs
are in `evidence/` (r78_opus_c3 dungeon/func_81912154 15->11, r78_opus_c5 dungeon/func_800969CC 16->8).

The move that worked: use the real parameters/tables directly (index tables by symbol, make stack fields plain
locals), let the compiler spill them, and drop ALL the $8/$12 bindings together - any remaining hard-register
variable on the spill register pushes reload to the next one ($9: distance 26 on 81912154). Then fix the
remaining allocation near-ties (loop counter initialisation placement, a narrower/wider local).
First check with `why.py --pass greg` / `--pass lreg` whether the pinned pseudo is actually spilled on your row;
if it is not, say so - that is a useful negative for this family.
