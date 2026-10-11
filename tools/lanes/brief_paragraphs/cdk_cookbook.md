# CDK cookbook: decide from the pass, then check the bytes

Recipe: copied `toolchain/compilers/gcc-2.7.2-cdk/cc1`, `-O2 -G0 -msoft-float`,
`-da -dp`; maspsx 2.56 and GNU MIPS assembler. These are synthetic mechanism
proofs, not retail matches or production gates. Reproducers below live in
`tools/lanes/cdk_cookbook/reproducers/`; run the installed kit's
`tools/reproduce.py` for dump assertions, read-only GDB observations and linked
byte hashes. The kit pins compiler/source hashes and refuses drift.

BFM's map and cookbook supplied questions, not admissible fixes. CDK source
citations below are under `toolchain/gcc-src/2.7.2-cdk/`. No probe uses register
pins, volatile, asm, one-trip wrappers, dead reads, decoy quantities or fake
dependences. Statement placement, genuine variable reuse and ordinary arithmetic
are the admissible dials. Keep types and callee declarations supported by retail.

## A load or constant moves unexpectedly: sched1 birthing

**Pass:** `sched.c:2513` tests a plain REG destination, the evolving backward
live set and `reg_n_sets == 1`; `:2554` adjusts priority only when `schedule_insn`
releases a dependency. Counts are those remaining after CSE/combine, not source
assignment counts. Hard registers qualify too. Initial-ready instructions never
receive this release-time boost.

**Lever:** reuse a variable for two real, consumed values, or place a real
constant store before the counter initialization that could supply it.
**Proof:** `sched_birth_live_a.c` reuses the raw/masked tag: pseudo 82 has two
sets. In `sched_birth_live_b.c` the two roles are separate single-set pseudos;
insn 19 changes from priority 2 to `7f000001`. Final 64-byte images are equal:
a boost change alone does not guarantee a byte change. The simpler
`sched_birth_a.c` / `sched_birth_b.c` mask pair is erased by combine and is
also byte-identical. `sched_const_a.c` / `sched_const_b.c` show the constant-store
placement dial surviving into different bytes; the latter emits a separate
`li $v1,1` for the store. Check all later passes before claiming an order fix.

## Two independent stores exchange places: sched1 LUID

**Pass:** `sched.c:2419` ranks priority, then dependence class, then original
LUID. Scheduling is backward; full ties choose the higher LUID first, preserving
ascending order in the forward stream. `schedule_select` can still intervene
for hazards; equality of priority alone is insufficient.

**Lever:** move independent, semantically reorderable statements or their real
initializations. **Proof:** `sched_luid_a.c` / `sched_luid_b.c` reverse two disjoint
stores. Both initial ready lists tie at priority 1 and choose insn 21 before 16;
the stores exchange identities in that stream. Their 32-byte linked images
differ. Do not move possibly aliasing operations on this evidence.

## Saved registers swap at a reference threshold: global priority

**Pass:** `global.c:587` uses truncated
`floor_log2(refs) * refs / live_length * 10000 * size`, then allocno order for
exact ties. The denominator is live length. `flow.c:2566` weights real uses by
loop depth; it is not a count of source mentions.

**Lever:** change real loop/use placement or a competitor's live range, then
solve the measured inequality. **Proof:** `global_refs6.c` gives a 7-reference
value priority 7777 versus the pointer's 7800; `global_refs7.c` crosses to 8
references and priority 12000 versus 7777. Allocation order changes
`80,81,82` to `81,80,82`, swapping `$s0`/`$s1`. Those controls contain different
real writes; they are not a byte-neutral rewrite. `global_loop_depth.c` observes
reference increments of exactly 1, 2 and 3 outside/inside real nested loops.
Never buy references using dead reads or one-trip loops. CDK's
`config/mips/mips.h:1355` sets FIRST_PSEUDO_REGISTER to 76; do not import BFM's
stock-compiler register-number constants.

## Local density predicts the wrong winner: quantity order

**Pass:** `local-alloc.c:1598` uses fixed quantity numbers in the three-quantity
compare network while swapping order slots. With quantity 1 highest, the two
`compare(0,1)` exchanges undo each other. Two quantities sort correctly;
`:1621` uses qsort for four or more. Quantities are born during the forward
scan, not necessarily in declaration/pseudo order. Suggestions allocate first.

**Proof:** `local_fixed2.c`, `local_fixed3.c`, `local_fixed4.c` have exactly
2/3/4 local quantities and no suggestions. Measured allocation orders are
`1,0`; `0,1,2` (density says `1,0,2`); and `1,0,2,3`. Three puts the base in
`$v0` and the accumulator in `$v1`; four reverses them. Each extra quantity has
a real load/store role. These are controls of different computations, not a
license to add a decoy. **Lever:** move actual births/deaths and verify the real
quantity census before trying declaration permutations. BFM's blanket
“<=3 means creation order” overstates this bug.

## An explicit parameter copy disappears: CSE canonicalization

**Pass:** `cse.c:838` promotes a new pseudo to equivalence-class head only when
it escapes the current CSE block and outlives the old head (with additional
hard-register rules). **Proof:** `cse_copy_a.c` observes pseudo 82 promoted over
80 when last-use CUID 12 exceeds block end 10 and old last-use 9. A later CSE
pass restores head 80; final bytes equal the direct-parameter `cse_copy_b.c`.
**Lever:** place a genuine body-local copy at its actual lifetime boundary and
check CSE1, CSE2, flow and allocation. A textual copy does not establish a new
allocno or a surviving entry preference.

## A field re-read becomes a move: CDK post-reload CSE

**Pass:** CDK calls `reload_cse_regs` at `reload1.c:2140`; `:8142` can replace a
load with a hard-register copy of a recorded equal value. Calls, labels and
clobbers constrain the available records. This pass is present in OUR CDK;
BFM's statement about stock FSF 2.7.2 having no reload CSE does not apply.

**Lever:** spell genuine field dataflow as field re-reads where justified.
**Proof:** `reload_live.c` stores a value, updates another field and returns the
first field plus the still-live value. UID 22 is a MEM through `.lreg`, then a
copy from hard register 5 in `.greg`; GDB observes that exact mutation inside
`simplify_set`. `reload_reread.c` clobbers the only recorded register and retains
the load. Do not introduce a self-assignment or a dead re-read to manufacture it.

## A temporary vanishes or changes role: combine i2dest reuse

**Pass:** `combine.c:1767` first requires a three-insn candidate. The fallback
at `:1872` checks split-point mode/eligibility, adjacency or a crossing check,
and that `i2dest` is absent from the substituted pattern; both resulting
instructions must then recognize. This is a split of three instructions into
two, not the ordinary two-insn copy fold.

**Proof:** `combine_split_a.c`, `((x+5)<<2)+4`, combines UIDs 10/11/13. Adjacent
UIDs 11/13 have matching SI mode, and the referenced test returns false. The
split reuses pseudo 83 for `x<<2`, deletes the old `x+5` pseudo and adds 24.
It matches `combine_split_b.c`, `(x<<2)+24`, byte-for-byte (16 bytes).
`combine_split_or.c` changes the final addend to 3: PLUS becomes IOR and the
compound still fails recognition even though the referenced test passes.
**Lever:** use the real arithmetic decomposition and original lifetime. This
unsigned identity is legal; it is not a general signed-overflow identity or
permission to change ABI widths without retail evidence.
