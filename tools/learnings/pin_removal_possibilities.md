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

## Same-register `bgez; nop; negu` = abs() (round 80, r80_opus_p2 on dungeon/func_800A8714)

Retail `bgez rX; nop; negu rX,rX` on ONE register is the mips.md `abssi2` template (ISA 1, source == destination):
the source was `v = abs(v)`, not an if-negate. With an if-negate, reorg fills the delay slot with an independent insn
and keeps are placed to stop that. Caveat measured: abs() makes v block-local, which can reorder allocation ($2/$3).

## Symbol argument on a reassigned local keeps retail's shared `lui` + per-call `%lo` (r80_opus_p2, town/func_8046C280)

At a splitting cell a symbol argument is HIGH + LO_SUM; cse folds `(lo_sum (high X) X)` to X, so a second use of the
same symbol reuses the full address. Retail keeps only the HIGH in a callee-saved register and re-adds `%lo` per call,
which happens when the local holding the address is REASSIGNED between the calls. A numeric page constant always
folds to `lui/ori`. APPEARS: ASM_KEEP(page) pairs around calls; RESOLVES: pass the typed symbol via a reassigned local.

## Constant-address call arguments: `lui a0; lui a1; addiu a0; addiu a1` vs retail's in-order pairs (r80_cell_c7, town/func_8032E720)

calls.c:1659 copies an "expensive" argument into a pseudo first only when preserve_subexpressions_p() is true:
always with -fexpensive-optimizations, otherwise only inside a loop (stmt.c:2435). With the copy, combine folds each
%lo into its a0/a1 move and cdk emits `lui a0; lui a1; addiu a0; addiu a1`; without it each argument loads straight
into its register in retail's order. A one-trip `do {} while (0)` COUNTS AS A LOOP here - pinned rows used such
blocks and keeps to imitate the missing flag. Fix: drop the one-trip blocks and record -fno-expensive-optimizations
as a recipe trade. (Same row: a single-set function-pointer load gets sched1's launch boost above the argument loads;
retail's plain source order needed -fno-schedule-insns.)
Allocation tie reading (same lane, dungeon/func_8195EF44): at 2.7.2-cdk the live lengths global.c weighs come from
sched1's recount (one unit per insn from block start to death in every block where the pseudo is live on entry), not
from flow's - compare the .flow and .lreg dumps before arguing from prio.py.

## Dead `lbu` reads of just-stored bytes = write-backs deleted by post-reload CSE (round 80, r80_opus_p3: xxx084 family, 60 pins -> 0 on 10 rows)

Retail loads packet r/g/b with `lbu` into scattered registers ($3/$6/$7) and never uses them; the pinned C spelled
that as volatile fields + ASM_REG/ASM_KEEP. The source STORED the values back (`r = p->r; ... p->r = r;`, a
setRGB0-style write): at allocation the three values are live together until those stores, so first-free allocation
gives $3/$6/$7; afterwards the cdk compiler's post-reload CSE (the pass that turns `li $6,0` into `move $6,$4`) deletes
the stores because memory already holds the value - insn in `.lreg`, gone in `.greg`, loads kept. This is recovered
source, not a fake dependency: retail's unconsumed loads REQUIRE a consumer that existed until after allocation.
Check before using it: the store must be in .lreg and absent in .greg. Literal constants for call arguments that the
base staged in pinned locals (GetTPage(0,1,0,0)) let sched1 hoist the a0/a1 sets as retail does.

## Round-80 Opus harvest, lanes p5/p6 (town/func_800AB37C, dungeon/func_819715D4, func_80AC55DC, func_800A2564, func_800A3D40)

- **Aggregate copy = movstrsi.** lw/sw triples off one base register with scratch $3/$4/$5 (+ KEEP_NV on a numeric
  page, + fake trailing call arguments keeping $5/$6 alive) is gcc's block-move pattern for `dst = SYMBOL;` of a
  struct: write the typed struct assignment and the call at its real arity.
- **Parameter width decides register vs stack.** An s16 parameter gets a conversion pseudo that lives in a register;
  an s32 stack parameter stays tied to its slot and is reloaded. With `p[i] = param` then `p[i] += src[k]`, cse
  replaces the read-back with the parameter (retail `lhu; move $2,$sN; addu`) - declare params at the element width.
- **Natural divisions.** Hand-expanded signed divisions with ASM_REG quotients: write `/8`, `/2`, `/4` inline with the
  divisor expression shared inline (cse keeps the sign-extended divisor canonical: `move $3,$4; bgez $4; addiu
  $3,$4,7`); a temp reused for a later quarter adds output/anti dependences that keep sched1 from hoisting it.
- **Set-once symbol pointer + ASM_USE, retail reloads via $8:** hoist its constant initialiser to the function top;
  it then lives across everything, spills, and reload rebuilds it through $8 as retail does.
- **Byte-loaded s16 re-extended at each use + KEEP_NV:** reassign it from the s16-returning call
  (`v = f(v)`): combine otherwise drops the re-extensions (nonzero_bits 0xFF).
- REG_EQUIV live doubling (local-alloc.c:1058) halves a symbol-set pseudo's priority - check prio.py before reading
  an allocation swap as a spelling problem.

## Round-80 Opus harvest, lanes p7/p9

- **KEEP_DEP_NV on a numeric page whose page+offset is a named symbol** imitates symbol opacity (combine folds an
  integer page to `ori`/absolute `lw`): use the typed symbol (dungeon/func_8194D354 12->9).
- **Sibling blocks loading the same fields while $4 is busy:** one shared local pair for both blocks makes them global
  allocnos that see the busy $4 and take $5/$6 - the $5/$6 pins imitated that (dungeon/func_81941338 8->3).
- **Fall-through `addiu +c` right after a back edge whose delay slot holds `addiu -c`** is reorg filling the slot with
  the loop-top decrement and emitting the inverse on the exit: write the decrement as the first do/while statement
  (town/func_800A4978 4->0).
- **Per-axis hand-expanded divisions with barriers between them:** write each stored field's full natural quotient
  (`(-(o << 16) / (duration / 8)) / 2`); every `duration / 8` leaves an empty sign-fix branch until jump2, which splits
  sched1 blocks exactly where the barriers stood; cse removes the repeated divides (dungeon/func_81339D2C 4->0).
- **A pinned pointer whose stores are duplicated in both arms of an if/else:** one conditional-expression store per
  field (fewer refs -> the allocation order flips; dungeon/func_81959E04).

## Round-80 Opus harvest, lanes p8/p10/p11/p12/q2 (short)

- A pinned register copy of a just-loaded field is often a SECOND READ of that field: sched1 hoists it and
  post-reload CSE turns the `lhu` into `move` (town/func_80820AF4: `obj->f += obj->g; obj->f += obj->g >> 2;`).
- A table base reused as a loop variable: give the base its own block-local variable, so local-alloc puts the
  split-address `lui` straight into $s0; pass literal 0 and zero the local after the call (town/func_8046BD98).
- Volatile field + CLOBBER/KEEP around an OR-ed copy -> non-volatile field with compound `|=` twice (cse keeps the
  two ORs apart: `move $3,$2; ori 0x80`) (dungeon/func_819411F0).
- `x <<= 16; x >>= 16;` on an s32 parameter behind KEEP_NV -> declare the parameter s16 (slus/w_8005A778; the
  caller's extern still says s32 - align it).
- Keeps around `(cur -= 0x20), cur` comma forms -> shift in the target statement and plain subtraction (combine
  rewrites `(t<<6) - (c-32)` as `+32 - c`) (dungeon/func_8180D0DC).
- KEEP_DEP_NV(x, call()>>k) -> one multi-set local for the block's shifts (sched1 birthing boost launches a
  single-set shift next to its mult) (dungeon/func_818B7264).
- Barrier + keep over staged fade locals -> field compound assignments (dungeon/func_8195A480).
- One temp reused for two axes across a barrier/$3 pin -> one fresh local per axis (dungeon/func_80F03000).
- 19-byte record walks spelled `(x*4+s)*4-s` in a goto loop + KEEP on a copied parameter -> natural `i*19` for loop
  (loop.c makes the biv copy itself) (dungeon/func_81811FA8, Sonnet).
- Scalar global RMW next to a struct-field RMW with a register pin between -> access the global through its shared
  struct type (objectFlagBlock.flags): MEM_IN_STRUCT_P keeps them ordered (dungeon/func_800BF6A0, Sonnet).
- **Goto-built loops are straight-line code to the allocator** (no loop-depth reference weighting): a keep on a value
  that lives across calls and loses its callee-saved register to a pointer may be imitating the weighting a REAL
  loop gives - rewrite as `while (1) { ... if (!c) break; }` (slus/konami_runtime_w_80033D54 3->0, q1). The opposite
  also holds (func_80ACB000: do/while swapped $s3/$s4) - measure both.
- Hand-rounded `r = s; if (s < 0) r = s + 2^k-1; C - (r >> k)` with ASM_REG on s -> `s = s / 2^k; return C - s;`.
