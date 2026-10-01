## Pins on constant page / scratchpad base locals (round 84 class C; read work/native_lane/r84_opus_opqC/REPORT.md)
A KEEP/REG/USE pin on a local set from a constant page (`(T *)0x80xx0000`) or the scratchpad (`0x1F800000`) usually
does NOT stand for an opaque base - it imitates SCHEDULING PRIORITY and MEM_IN_STRUCT dependences:
1. cdk sched.c (835-911) drops a dependence between an in_struct varying access and a NON-in_struct fixed-address
   access. Raw-cast scratch/page accesses (`*(T *)(base + K)`) are exempt from struct-pointer accesses and hoist;
   spelled as STRUCT FIELDS (a named struct for the scratch/page layout, or a struct member through the base) the
   retail `load; nop; store` dependences come back. (r84_opus_opqC used an anonymous pad-struct field macro
   `((struct { u8 _pad_[K]; T v; } *)(base))->v` - prefer a NAMED struct with the fields at the offsets.)
2. The birthing boost (sched.c birthing_insn_p needs reg_n_sets == 1): a load into a variable assigned more than once
   gets priority 1 and floats to the top (or is blocked behind store chains); give each such load its own SINGLE-SET
   local and it lands next to its use.
3. Name split symbols: a bare `lui` page + %lo offsets feeding one symbol = that symbol (D_xxxx direct).
4. A dying single-use page folded by combine into `(mem (const_int ...))` is a different question (813274E4: open).
5. cse folds `x |= K` on a known constant into a fresh constant (a second `lui/ori` build): keep the variable's value
   unknown to cse only through natural data flow (800A406C KEEP(color) open).
Erase the base pins at the row's recipe first, then use `why.py --trace --block` on the first differing block to
see whether each residue is a priority tie or a dependence before you spell anything.
