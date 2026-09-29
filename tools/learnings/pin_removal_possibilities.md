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
| page `ASM_REG` over a symbol declared as a scalar; a load must stay after stores it cannot alias | access the symbol through an unsized array extern (`extern T SYM[]; SYM[0]`) - array MEMs are in-struct and keep the dependence | sched.c true_dependence struct/scalar exemption (round 78, dungeon/func_81887004) |
| SLUS page keep/barrier on a symbol of 16 bytes or less | declare it as an unsized array extern: not small data under -G16, so cc1 emits lui + offset and the store fills the delay slot | -G small-data choice by declared size (round 78, slus/w_80040CBC; land with land_slus_rebaseline.sh) |
| a data object's declared size differs between spellings (unsized `T x[]` vs `T x[N]`) on a stock (non-cdk) SLUS file | build the whole image, never discount it: the `.extern SYM, size` the compiler emits changes how the ASSEMBLER expands a `sh $r,SYM` store macro (sized: fills the jal/jr delay slot; unsized: goes through $at with a nop) as well as $gp small-data choice | round 78 phase 9: volumeScale[] shifted the SLUS image by 88,082 words; [8] matches |
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


## Proof checks (round 80, r80_fable_n1 retrospective) - run these before sweeping an axis

1. **Sole-ready-at-stall (sched2).** For residue insn R: t_r = max pick tick of R's successors; at the first tick
   >= t_r where R is ready and alone (or wins on priority) R is emitted. If retail has R EARLIER than that, no source
   reorder can move it: a successor of R must exist in retail's graph (the RTL must differ). -> NOT-REORDERABLE.
2. **Launched vs early group (sched1).** Retail "non-launched X after launched H" is reachable only if H has a
   non-launched consumer with LUID below X, or H's last consumer link costs > 1. Otherwise statement order is inert.
3. **Known-constant base (combine).** A single-set pseudo whose source is a CONST_INT, feeding an argument copy
   (plus B c) with (c & value) == 0, becomes `ori` (combine PLUS->IOR via nonzero_bits, reg_n_sets == 1). If retail
   has `addiu`, the original base was OPAQUE to combine (multi-set, a parameter, or a HIGH/LO_SUM symbol) - pins that
   make it opaque are imitating that, not scheduling.
4. **Barrier rule.** Any asm-volatile pin makes every earlier insn a predecessor of every later one: residue insns it
   governs are inert to order experiments while it stands - erase it first or reason about the graph without it.

All four run in one command: `tools/lanes/lanekit/checks.py <row> cand.c [--cfg CFG]` (a verdict and the evidence
line per residue insn); `why.py --trace --block/--insn` and `why.py --deps` show the trace each verdict reads.

## Three-pseudo copy shape: `andi aN / move sK,aN / ... move aN,sK` (round 80, r80_cell_c3b on dungeon/func_800C4A80)

Retail keeps a masked temp T, a callee-saved copy D and a later argument P that re-reads D (`move a0,s5`). Measured
mechanism at 2.7.2-cdk (expensive-optimizations ON): (1) P must have a DIFFERENT mode from D (e.g. a `u8` argument
local) - a same-mode P is merged into D by cse and the move vanishes (20+ same-mode spellings, totals 7-36); the
zero_extend is folded back to a copy by combine because D's nonzero_bits fit; (2) P's set must be T's FIRST use, so
combine never links the andi into D's copy; (3) `optimize_reg_copy_1` (local-alloc.c ~700, only with
-fexpensive-optimizations) then rewrites T -> D from D's copy to T's death, turning P's set into `move a0,s5`. A
cfg with -fno-expensive-optimizations cannot produce it - such rows pinned it as `ASM_KEEP_NV(direction)`.
Side effect: the extra reference optimize_reg_copy_1 adds raises D's allocation priority (prio.py), which can move
D to an earlier callee-saved register. Candidate shape: `s32 arg = (f >> 9) & 7; u8 check = arg; s32 dir = arg;`.

## Clone transplant + latch keep (round 80, r80_opus_p1: 6 dungeon TILE/DR_MODE clone rows, 57 -> 27 pins)

When several rows are one clone body, the cleanest sibling's body is the canonical text: transplant it (literal call
arguments such as GetTPage(0,1,0,0), the shared union), write the prologue as plain initialisers, and let the
schedulers order it (an unfenced prologue reached retail by sched1 birthing boost + LUID ties). A keep that only makes
a base register OPAQUE to combine (`checks.py` OPAQUE-BASE: without it, PLUS->IOR turns `scratch+4` into `ori`)
does its job from the loop LATCH as well as from the prologue - moving it there freed every prologue pin.
Colour/argument register pins: a dead read pinned to $6 next to an `a2 = 0` argument imitates a sched1 dependence
(the pin's output dep keeps the argument set after the read). Reusing the local as the zero argument
(`green = zero; f(zero, 1, green, 0)`) gives the true dependence and the a2 preference (func_80AE9000: pin gone,
retail `move $6,$4`). It does not stack: a second such local is merged by cse (`move $7,$6`).
