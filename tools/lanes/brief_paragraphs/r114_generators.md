## Generators that paid in round 114 (try the matching one before inventing a shape)

Each line: where it APPEARS -> what RESOLVED it -> the deciding pass. Mechanisms and measurements:
work/native_lane/_r113/harvest_r114.md. All are pure C and landed (4381b0435); the union idiom is an owner-accepted
trade (10-12) - check the frame does not grow (a union that goes to the stack is a refusal).

- **Zero-init one-member union** `union { T v; } x = {0};` (use `x.v`): the initializer emits a CLOBBER + SET with no
  extra instruction, so the variable is TWO-SET. (a) Erasing a pin lets a single-set copy/constant be birthing-boosted
  past a load -> union on that copy (sched.c birthing_insn_p; 8028906C). (b) An entry KEEP on a parameter copied into a
  typed base pointer -> union on the pointer stops the cse adjacent-copy swap, so the entry insn survives combine
  (81844F2C). (c) A REG pin on a value retail colours GLOBAL but the text keeps block-local -> declare the union in a
  scope whose CLOBBER lands in an EARLIER compare-only block: flow counts it in another block, the pseudo goes global
  (818B6AFC; check prio.py; cdk only - at 2.6.3 `{0}` becomes a pool load and no CLOBBER is emitted).
- **Split sign extension**: a KEEP between a zero-extending HI load and a `<<16 >>16` that erasure folds into `lh` ->
  shift left into a fresh local and move the register's next REAL reassignment between the two shifts
  (combine.c use_crosses_set_p refuses the fold; 800AED64 4 -> 0).
- **Per-case tails**: an ASM_REG pointer flowing into a goto-shared tail reached after a page-constant load -> write the
  tail once per predecessor in the function's own idiom; the post-reload jump pass cross-jumps them back (80D68308).
- **Real narrow counter**: an m2c u32 counter used only through `(s16)` casts whose callee-saved register swaps with a
  hoisted `x<<16` pseudo -> declare it `s16` and write the plain `for` loop (HImode SUBREG increment is no SImode biv;
  80D68308). Also split 0/1 flags m2c merged into an unrelated variable.
- **Aggregate member access for a constant base**: a REG pin on a constant scratch base -> keep the pointer plain and
  set once, read through a real type's members (e.g. the 1 KB scratchpad `typedef union { u16 h[0x200]; u32 w[0x100]; }`)
  instead of `*(T *)(base + off)`: the set-once lui keeps its birthing boost and member accesses are MEM_IN_STRUCT_P,
  so true_dependence keeps retail's load order (819112CC).
- **Successor variable**: a pointer pinned to stop BIV/giv rebasing -> compute `next = p + sizeof(T)` before an
  intervening real insn and commit `p = next` at the loop end (loop.c basic_induction_var follows only the previous
  insn; 809A38E4).

Prove the target first when you can: `tools/lanes/lanekit/alloc_oracle.py` (and the oracle family when landed) forces one
compiler input and compares raw bytes with retail - "if X had priority P, is it exact?" before searching for C.
A byte-exact tidy at UNCHANGED pins is stageable: `lab.py stage-tidy <row> f.c --note "..."` (once the kit package
lands; until then `lab.stage_file(..., equal_pins=True)`). After a tidy that proves load-bearing, CONTINUE to the pins.
