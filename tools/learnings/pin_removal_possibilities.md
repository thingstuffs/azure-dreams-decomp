# Pin-removal source-shape possibilities

This is a hypothesis catalogue for pin-removal lanes. Every proposed shape must
compile under the row's recorded recipe and pass the full byte scorer. A local
instruction resemblance can suggest an ordinary C idiom, but the target function's
address formation, live ranges, allocation, and scheduling determine whether the
result is exact.

## How to use the catalogue

1. Classify the erased-pin residue and identify the exact local instruction window.
2. Pick a plausible source family from the table below.
3. Build the smallest target-local candidate under the row's recorded compiler recipe.
4. If the local core appears but the function still misses, stop permuting that core.
   Inspect address materialization, variable live ranges and set counts,
   saved-register membership, and scheduling or block order with `why.py`.
5. Accept only a full byte-exact result with fewer pins. Record a close miss as a
   bounded negative and describe the residual it exposed.

Repeated instruction shapes increase confidence in a C family, not in a complete
source reconstruction.

## Source-shape catalogue

| Retail or residue clue | Ordinary C shapes to test | Compiler effect to inspect |
|---|---|---|
| `lwl/lwr` + `swl/swr` run, often with aligned/unaligned arms | typed aggregate assignment; assignment from a typed global symbol; `memcpy` only as a control | alignment knowledge, copy expansion, base-address lifetime, post-copy cursor lifetime |
| extra `andi`, `sll/sra`, `lh` versus `lhu` | actual narrow parameter/return type; explicit local conversion; signed/unsigned lvalue cast | `assign_parms`, extension pseudos, pseudo count, allocation order |
| repeated `lui` for nearby data versus one shared high base | separate globals versus fields of one struct/array; named symbol versus numeric address | address CSE, shared HIGH lifetime, relocation/address splitting |
| same address expressed as `base + offset` versus a field/index | typed field/index versus raw byte offset | GCC 2.x `MEM_IN_STRUCT_P`, alias/dependence edges, scheduling freedom |
| typed indexing fixes a memory operation but perturbs later address formation | inspect natural local reuse, split or merged roles, and the lifetime of index/address temporaries | allocno count, address-before-scale scheduling, equal-priority source order |
| a pin changes several later saved-register roles | split one variable into consecutive roles; merge adjacent roles; move a conversion into a fresh local | set count, `birthing_insn_p`, allocno creation/order, live range |
| load/store remains around a call or pointer write | direct object/field access versus store through an aliasing pointer | CSE invalidation, reload, dependence edges |
| loop constant/count moves or refuses to move | cache `obj->count` before the loop; recover a narrow inline helper; change true loop-body shape | loop insn-count threshold, lifetime/savings decision |
| branch body is right but jump/delay-slot order is wrong | `if (x) continue; break;` versus `if (!x) break;`; sink/hoist/duplicate an existing statement across arms | jump canonicalization, basic-block order, sched/delay-slot candidates |
| switch cases contain the right blocks in the wrong emitted order | change lexical order of switch bodies while preserving labels and fallthrough | initial RTL chain order and later scheduling |
| prologue copies an argument before other setup | use the argument directly versus make an explicit local copy/conversion at its real lifetime boundary | parameter pseudo, local allocno order, saved-register set |
| a store/load will not cross a fallthrough edge | an original volatile access may explain retail, but **never add volatile as a repair** | treat as diagnosis only; seek the larger correct object/control-flow shape |
| `ASM_REG("$8"/"$9"/"$10"/"$12")` + keeps where retail shows `lui/addiu $8`, `lhu $8,N($sp)`, `mflo $12` next to ordinary code, all callee-saved registers taken | reload, not a user variable: use the real parameter/table/symbol, make fake frame fields plain locals, declare `T *p = SYM;` once at function scope, and drop ALL spill-register bindings together (one left pushes reload to the next register) | global.c spills, reload spill register, REG_EQUIV rematerialisation (round 78: 9 rows, see `tools/lanes/brief_paragraphs/spill_register.md`) |
| a callee-saved swap on a loop counter written as `label: ... if (i < n) goto label;` | a real `for`/`do-while` loop (loop notes weight the counter's refs by loop depth) | global.c allocno priority (round 78, dungeon/func_818BDEBC) |
| a callee-saved role pinned while a local is initialised from a parameter | use the parameter itself; its longer live length lowers its priority | global.c priority (round 78, dungeon/func_800C3928) |
| a pinned constant call argument that retail keeps in the `jal` delay slot, after a store to a volatile global | do the store through the plain typed pointer already being passed | reorg `fill_simple_delay_slots` stops at a volatile store (round 78, slus/w_80053CFC) |
| `goto` into another case's tail on a row with a callee-saved near-tie | write the tail out in each arm (jump2 cross-jumps it back after allocation) | global.c ref counts before jump2 (round 78, dungeon/func_818E6800) |
| a fence whose only job is to stop two identical blocks merging | diagnosis: jump2 `find_cross_jump`; no C spelling found yet | treat as an open toolchain question, not a spelling search |
| lw/sw runs beside a fake extra call argument in `$7` | one aggregate assignment of the real typed record; the call has its real arity | block-move scratch registers (round 78, town/func_8080E59C) |
| frame size/stack slots are right only with apparently unused declarations | recover real locals, types, scopes, or aggregate objects from surrounding semantics | frame layout and slot order; do not add fake unused locals merely to shape code |

## Aggregate-copy decision rule

Aggregate copies are a common source family and easy to overclaim.

- Preserve the record's real alignment and dimensions. A halfword-aligned object can
  legitimately produce runtime aligned/unaligned paths.
- Establish the real source object, destination object, and callee arity. Artificial
  copy-end cursors or extra arguments make false live ranges survive the rewrite.
- Try the complete typed relationship, not only `*dst = *src`. The result may need
  the correct struct dimensions, symbol, alias role, helper prototype, or typed table
  access around the copy.
- When the copy instructions match but the whole function does not, inspect address
  form and the surrounding register lifetimes before trying more spellings of the
  same copy.

## Additional compiler clues

- Casting the lvalue, not merely the value after loading, selects signed versus unsigned
  memory operations.
- Widening a prototype can remove extensions; narrowing one can create them. Review real
  callers and callees together rather than optimizing one isolated body.
- Two source-level bit tests can combine into one machine test, so a surprising mask need
  not imply a hand-written combined condition.
- A store through a pointer can intentionally block CSE of otherwise identical loads.
- Source lexical order matters for switch bodies and for equal-priority scheduler ties.
- `-O1` and `-O2` can differ in absolute-store/address behavior; use recipe experiments
  only as diagnosis unless the pinned control is also exact at the alternate recipe.

These possibilities may explain legacy `volatile`, hard-register, or keep scaffolding.
They do not relax lane legitimacy: do not add `volatile`, inline assembly, fake
dependencies, one-trip blocks, or unused declarations with no credible source role.
