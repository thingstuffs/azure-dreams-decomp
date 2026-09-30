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
- **Fake call arguments:** check the callee's definition (`s32 f(void)`): pinned (dst, src) arguments to a void-arity
  callee forced constants to be rebuilt; call it at its real arity (dungeon/func_8008D990, with a struct copy for the
  lwl/lwr run).
- **Barrier before a join guarding `if (c) x = K1; else { x = K2; ... }`:** jump.c:699 turns it into `x = K2; if (c) x = K1`,
  creating an insn that sched1 sinks and reorg copies into delay slots; an else-if chain stops the transform
  (dungeon/func_8197CEC0).

## `branch; nop; lui` vs retail `branch; lui` is a DECLARATION SIZE question, not an assembler gap (r80_opus_lafill)

Genuine SN ASPSX 2.56-2.86 never fills a branch delay slot from the fall-through (aspsx_diff --one on the candidate,
synthetic probes, and a 125-site / 79-row retail census: 0 fall-through fills). Retail's `lui` in the slot comes from
cc1: it splits the address into HIGH + LO_SUM and reorg steals the HIGH into the slot - which cc1 does only for symbols
that are NOT small data. A 4-byte `extern u8 *SYM;` is small data at -G8, so cc1 emits an unsplittable `la`. Before
blaming the assembler, check the symbol's `.extern SYM, n` size (n <= 8 -> small) and whether retail's other uses
prove a larger object (dungeon/func_807B0B3C: `extern u8 *D_80083160[]` gives the split and the filled slot). Second
"assembler fills a slot" idea disproved with genuine ASPSX (after the 655-record tail-jump one) - test with
aspsx_diff before any maspsx change. Kit gap: listing distance treats `la SYM` as equal to `lui/addiu`.

## dirStep terrain walks: `next_x ASM_REG("$4")` = optimize_reg_copy_1 on an s32 latch (r80_opus_o10, 3 clone rows 1 -> 0)

With an s32 sum, `cell_x = next_x` is a reg-reg copy and local-alloc's optimize_reg_copy_1 (local-alloc.c:700) rewrites
the later `target_x = next_x` to read cell_x, raising its refs (8 -> 10) and recolouring the function; a hard-register
pin is exempt, which is all the `$4` pin did. u16 cells make the copies SUBREGs (also exempt): write
`u16 cell_x, cell_y; ... cell_x += dirStepX[dir]; cell_y += dirStepY[dir]; target_x = cell_x; target_y = cell_y;`
and load the x cell FIRST (y-first lets cse swap the copy so target_x becomes the load's destination, refs 8 -> 7).
Related: a volatile local whose latch delay slot needs an earlier insn is a NON-volatile memory local (reorg will not
move insns past a volatile store); never name `$8` in C when reload rebuilds a loop-hoisted table HIGH there (o6).
- **`a = b + a` operand order** (r80_opus_ds1, dungeon/func_80289BD4): expand_binop (optabs.c:399-415) swaps the operands
  when the target is the second operand; a FRESH single-assignment target gives retail's `addu $4,$13,$4`. local-alloc
  ties a register only between a dying block-local temp and its result, never with a multi-role variable.
- **dirStep offset locals**: `*(u8*)((u8*)dirStepX + ((f>>8)&0xE))` through a pinned/reused offset local ->
  `dirStepX[(f>>9)&7]` inline (fresh temp created first takes $2; dungeon/func_800A5544).
- **CORRECTION (r80_opus_r1, dungeon/func_818B1664 10 -> 0):** retail's `lhu $8,48($sp)` for saved_y is RELOAD, not a
  memory object: a plain `u16 saved_y` scalar that global.c leaves unallocated (low priority, spilled) is reloaded into
  spill register $8. Memory spellings (arrays, addressed scalars) create a load local-alloc ties into another value's
  register - which is what o6/o10/a7 kept hitting. Also: abs + store written in BOTH arms of a test replaced a
  barrier (jump2 merges the identical arm tails after reload); a reused multi-block local gets $3 once a block-local
  takes the value that overlapped it. And for pinned rows with a pin-free SIBLING on the same table/callee
  (8028516C <- func_80017F88): transplant the sibling's natural body first; nested ifs where retail branches twice
  (`&&` merges the two tests into one andi).
- **Switch-scope `ASM_REG($s*)` pins on case-locals** (r80_opus_r4, dungeon/func_8180C3C0 11 -> 7): where retail keeps
  per-case locals in the SAME callee-saved register across cases, the source had ONE function-wide variable per register
  role (merged pseudo crosses calls and ranks high: message_id 288 -> 1862). Share a child pointer that is live beside the
  merged object so it conflicts and does not inherit the object's $6/$7 argument preferences (expand_preferences).
- **Shared join label fed by a KEEP_NV'd local** (r80_opus_r3, dungeon/func_8187C45C 9 -> 7): a label whose only statement
  is `F = local + 1;`, reached by gotos that each set `local = K` + `ASM_KEEP_NV(local)`, was per-path tails in the source:
  write `F_store = K; F += 1; return;` in every path and let jump2 cross-jumping re-merge the identical tails after reload
  (retail's shared `addiu; sh` join). The multi-block local was a global pseudo that lost $2 to a neighbouring literal.
- **Residue class: a compared constant held in an ASM_REG variable** (r80_opus_r3, 8187C45C/818D4E68): where retail copies
  a register (`move a1,v0`) that plain C gets as `li a1,255`, cse folded the constant the pinned text kept in a hard
  register; and an `lbu; sll 24; sra 24` vs `lb` word is combine refusing across a store (use_crosses_set_p). Both open.
- **Argument-register pins on multi-role setup variables** (r80_opus_r5, dungeon/func_8180E534 9 -> 0): ASM_REG($4)/($5)
  on setup variables fall when ONE variable carries each argument role across calls (the sprite passed first to one call
  is the effect's sprite later; `data` is the second argument of both calls and later the colour): the global pseudo
  inherits the $4/$5 argument preference. Assign the late role AFTER the call statement, or it crosses the call ($16).
  Values retail keeps in $8 are reloads of unallocated scalars; goto loops stop loop.c hoisting the invariants.
- **Odd-cell row with a pin-free clone in the same overlay** (r80_opus_r5, dungeon/func_80BEE104 11 -> 0 as a cell move
  2.95.2 -> 2.7.2-cdk): transplant the clone's body, score it at the CLONE's cell (lab.py cellscore); the odd recipe only
  fitted the m2c text. Land through land_coherence.sh (a recorded trade).
- **Callee-saved pin on a copy of a parameter** (r80_opus_r6, dungeon/func_819613A8 9 -> 8): reassign the parameter in
  place with a compound op (`tile_y = row; tile_y <<= 4;`) instead of copying it; an s32 copy joins the parameter's cse
  class and becomes canonical, an s16 (subreg) copy stays out. The copy placed before a NULL test fills the beq delay slot.
- **ASM_REG on a constant used only inside a loop** (r80_opus_r7, dungeon/func_81337998 7 -> 0): when erasing the pin makes
  loop.c hoist the constant, hold it in a USER variable with a declaration initialiser (`s32 k = 0x40;`): loop.c
  (loop.c:691-703) does not move a set after the loop's first conditional branch for a user variable first referenced
  outside the loop. A tail that re-reads a byte it just stored becomes retail's `move` by post-reload CSE.
- **ASM_REG $8/$9 on a `lui; addiu %lo(SYM)` pair recomputed after calls** (r80_opus_r7, dungeon/func_80E3B96C 8 -> 4):
  not a colour choice - a set-once pointer local to SYM with the lowest priority gets no register and reload rebuilds
  the address into the spill register at every use. Write `T *p = &SYM;` once and use it across the calls.
- **Pinned parameter whose register is an argument slot of an earlier call** (r80_opus_r10, town/func_8009CC44 5 -> 0):
  check the callee's DEFINED arity - the m2c text passed fewer arguments. Calling it at its real arity adds the `$6 =`
  set (jump2 later deletes it as redundant) and reorders local-alloc; prior lanes all assumed the short call.
- **Spawner rows with pinned attribute parameters** (r80_opus_r10, dungeon/func_80DE9000 5 -> 1): copy the parameter
  handling of pin-free sibling spawners - s16 parameters, narrow saved copies at the top in the siblings' order, literal
  allocator arguments; sched1's birthing boost then orders the prologue by statement position.
- **Goto loop with callee-saved pins where a real loop hoists a table address** (town/func_800AEA50 5 -> 0): real do/while
  (loop-depth weighting) plus the address assigned INSIDE the loop to a user pointer declared `= 0` (loop.c:686-692).

## Scaffolding (volatile / one-trip) on pin-free rows - round 80 (r80_sonnet_vol1/vol2)
- **Volatile scalars whose address is passed as a rect/vector** (town/func_800B83C0, dungeon/func_80EDFC98): the separate
  volatile locals imitated a contiguous struct - declare `struct { s16 x, y, w, h; } rect;` and pass `&rect`.
- **Volatile u16 load masked by a small constant** (dungeon/func_8180E164): plain `& 3` lets combine narrow the load to
  `lbu`; write `% 4` (unsigned) - it expands to the AND on the full-width `lhu`.
- **Volatile cast load that must stay after struct stores** (town/func_800AB788): read it through the typed struct field;
  a `*(T **)p` cast load is hoisted above the stores by sched, a member load is not.
- **Volatile on u8 loads in a sum** (dungeon/func_800B2D84): it only fixed the commutative `addu` operand order - write
  the load first. Scratchpad (0x1F800000) casts need no volatile.
- **Volatile stores that only stop a loop.c DEST_ADDR giv** (dungeon/func_80283EC0) and **one-trip blocks on a fully
  unscheduled function** (town/func_8032FE78: load-delay nops, source order): recipe facts (`-fno-strength-reduce`,
  `-fno-schedule-insns -fno-schedule-insns2`), landed as byte-neutral cell moves.
- Open residue: `lbu; sll 24; sra 24` vs `lb` (combine folds without the volatile) - 800D1A48, 800CB068, 8187C45C.

## The early constant argument - SOLVED as a rule (r80_opus_earlyconst, 2026-09-30; trace in its REPORT.md)
Retail loads a call's CONST_INT argument (`li $4..$7,K`) early; plain C gets it late. sched1 works backwards and
`birthing_insn_p` gives max priority to a producer whose register is live and set ONCE in the function. The constant's
move is emitted last (calls.c), so its place depends on who is boosted:
- **A - the li itself is boosted** (its arg register is set exactly once in the function): retail had a second set of
  that register - usually a call written BELOW its callee's defined arity; pass the parameters through (jump2 deletes
  the moves later). dungeon/func_800A6018 2 -> 0.
- **B - a competitor lost its boost**: m2c reused one variable for several roles, so the insns between li and call are
  multi-set and drop to priority 1. Give each role a FRESH single-set local, of the field's width (s16/s8) where cse
  would otherwise merge the copy back into the parameter. dungeon/func_800ACC98 2 -> 0; p3's xxx084 family was B too.
Untried B candidates: 800B4204 (closest), 80CE8564, 81850800, 80EB751C, 8187C45C, 8187A9A8, 807B0B3C, 819ADDB8, 800BE8D0.
- **Unfolded `addiu $t,$base,K` right before a store `off($t)`** (r80_opus_earlyconst2, 800B4204 3 -> 0, 80EB751C 4 -> 0):
  the pointer local was assigned BEFORE an intervening call - combine.c:924 (2.7.2) never combines across a CALL_INSN,
  so the add is not folded into the store offset, and sched1's birthing boost puts it back right before the store.
  Pins/asm barriers on `obj + 0x20` "work" pointers fall when the assignment moves above the preceding call.
- **Late `li` held below address setup by a CLOBBER/KEEP** (r80_opus_cl_li, dungeon/func_818C3A3C 1 -> 0): the constant was
  written at its store (`s->f = 0x7DCF;`), and the neighbouring m2c read-modify-write chain was per-role field compound
  assignments (`|= 0xC; |= 0x20; ...`) - both halves needed (constant alone: 38). sched2's LUID tie then parks the li
  after the address pairs, before the stores. EXCEPTION (town/func_80470F3C): when retail keeps all of a variable's roles
  in ONE register, the m2c reuse is faithful - its anti-dependences order same-base byte stores; do not split it.
- **MOVED|1-2 census class = four mechanisms; triage** (r80_opus_cl_move; checks are mechanical):
  1. *dbr delay-slot fill* - `why.py --pass sched2` identical between pinned and erased, only the slot differs:
     fill_slots_from_thread (reorg.c:3257) skips a fall-through insn that sets a register live at the target. A
     `lui $2` skipped at an exit branch = the function returns a value ($2 live at exit): make it non-void
     (dungeon/func_800AC914 1 -> 0; no return statement needed).
  2. *sched1 rule A* - the moved insn sets `$4..$7` and that register is set once in the function: call at the
     callee's defined arity (fake m2c arguments add the second set) (dungeon/func_81339700).
  3. *sched1 rule B* - the moved insn copies a call result into a variable reassigned later: single-set carrier plus a
     separate variable for the later role (dungeon/func_80976B7C, with `s32 result = 0;`).
  4. *loop-note barrier* - the insn after a `do{}while(0)` has ~90 refs in the sched trace: the pin and the block hold
     the same fact; solve them together.
- **MOVED `lui` class = four mechanisms** (r80_opus_cl_lui; at 2.7.2-cdk a symbol argument is HIGH + LO_SUM and the
  $4-$7 moves are never boosted): (1) *a variable's second role* - a KEEP right after a single-set pointer sum imitates
  a real second set: host the later same-register table base in the same variable (town/func_800A9E84 2 -> 1);
  (2) *argument copy kept at its statement* - `x = y; KEEP(x); call(x)` with x in $4: in plain C cse keeps y canonical
  and deletes the copy (cse.c:840-857: x becomes canonical only if it lives outside the extended block and dies after
  y) - OPEN, the largest family; (3) *loop notes* - a `do{}while(0)` makes the next insn a full sched barrier and is a
  cse1-only boundary; (4) *sched1 alias knowledge* - two constant bases never alias, so a KEEP on the base imitates an
  opaque base's anti-dependence. The kit cannot compile some slus rows (PartitionError) - measure with verify.py.
- **Argument copy kept at its statement - SOLVED rule** (r80_opus_argcopy, dungeon/func_80088FA0 3 -> 2): cse.c
  make_regs_eqv (840-857) keeps the COPY x canonical for `x = y` only if (A) x is referenced before the cse block
  starts or after it ends, and (B) x's last reference is later in the insn stream than y's. Natural shape: ONE
  function-scope alias, set from the parameter in every section that uses it, INCLUDING the textually last section that
  reads the parameter - and read there (combine folds that last single-use copy into its load, costing nothing). Then
  the copy survives, takes $4, and the early `move $4,$sN` falls out without ASM_REG/KEEP. Predicted fit:
  dungeon/func_819B3414 (next_effect). Not this rule: a constant argument (cse costs CONST_INT 0 < reg 1), no call
  (local-alloc), or a symbol address (cl_lui mechanism 1).
- **`move $2,$sN; beq $2,$0` kept by a KEEP on `x = flag`** (r80_opus_cl_copy, dungeon/func_80BC3AC4 1 -> 0): combine CREATES
  that copy when the source copies a 0/1 flag into a NARROW local (`s16 t = flag; if (t != 0)`): cse feeds the flag into
  the sign-extension shifts and combine, knowing the flag's sign bits (combine.c:724-731: set more than once, not live at
  entry, small constants only), reduces them to a register copy left before the branch. So: declare the copy s16/u8,
  give every other role m2c merged into the flag its own local, and drop pins that read the flag before its first set.
  An s32 copy is folded by cse. Pin-free siblings are written this way (80CBEF98, 80A9D4E8, 80B9913C).
- **Page fold `lui R; addiu R,R` (same register) held by page+KEEP** (r80_opus_cl_ori, 80AC5F28 2 -> 0, 809A1A8C/812A85D4
  2 -> 1): at a splitting cell `movsi` puts (high SYM) into a new pseudo TEM and writes (lo_sum TEM SYM) into DEST;
  local-alloc combine_regs ties TEM to DEST only when DEST is a pseudo used in ONE basic block (or a hard arg register).
  A function-scope multi-block variable gives the untied `lui $2; addiu $5,$2`. So: (a) use the typed symbol directly /
  via a block-scoped pointer when its uses stay in one block; (b) when the block ends in `goto join`, write the shared
  tail out in place with the symbol and `return` - jump2 cross-jumps it back into retail's `lui $5; j tail; addiu`.
  If retail shows two registers, the symbol belongs in the function-scope variable. t54/t97 miss this because they put
  the symbol into the same function-scope variable the integer lived in.
- **MOVED `lw` class** (r80_opus_cl_lw): always a sched1 decision; the pin buys a barrier, a second set (a KEEP's output
  makes the variable multi-set, so birthing_insn_p stops boosting its load), or a combine refusal. Source facts:
  (a) a real second set - an in-place register-width update (`s32 t = f; ...; t--; f = t;`, 81988800); (b) bookkeeping
  written AFTER the call - sched1 lifts pure-pseudo updates above it (t71; 81984754 1 -> 0); (c) an ASM_REG on $4-$7
  makes that register multi-set so its load loses the boost - solve that pin and its USE falls too (818B6AFC);
  (d) a barrier standing in for a one-instruction struct copy (80E65598, cdk cell); (e) a copy of a spilled variable
  floating above calls (w_8004B954, open).
- **Callee-saved order pins in goto loops = missing loop-depth weight** (r81_opus_alloc1, dungeon/func_80097F94 6 -> 0 with
  4 gotos gone; 80F90E88 15 -> 13): global.c weights refs by loop depth only for real loops; m2c's `label: ... goto
  label;` gets none, so ASM_REG pins stood in for the weighting. Write the loop as do/while and check with
  tools/lanes/lanekit/alloc_need.py; check `diff.py --classify` for OPCODE/COUNT changes (= loop.c moved something
  retail did not - then the goto loop is original). A uniform "every mis-coloured variable one register late" pattern
  = a missing preference, e.g. a call argument m2c dropped (LoadImage called with 1 arg where every caller passes 2).
- **`x = y | x` with retail's operand order y-first** (80F90E88): gcc 2.8.1 optabs.c:423 swaps a commutative op when the
  target is also the second operand - compute into a temporary, then assign (combine folds the copy).

## Round 81 (2026-09-30): the cell and the flags come first - pins fitted to the wrong build
Before hunting a source shape, ask whether the row's registered cell/flags are its module's build. Tools:
`tools/lanes/row_census.py` (all pins erased, scored at registered vs module census recipe),
work/native_lane/r81_sonnet_cellcmp/cellcmp.py (D0: erased text at two cells line for line; D1 `--carriers`: which pin
carries the cell dependence), work/native_lane/r81_sonnet_flagcrutch/flag_crutch.py (pin-free module neighbours scored
under the row's cfg; a neighbour exact at the census recipe that breaks proves the row's flag is a crutch).
- **Class P (r81_fable_late, cellcmp census 69+4 of 138 non-cdk rows):** with every pin erased the late (2.8.x) or old
  cell and cdk emit the SAME body; the cell dependence is carried by a KEEP/USE/JALDELAY pin on an integer-page local
  (never the ASM_REG pins) - the 1997 combine force_to_mode ASM_OPERANDS change (r14287) seen from the row side. The
  registered cell is where the pins happened to work: work those rows at the module census cell.
- **Flag crutches (r81_fable_eqv, flag_crutch census 118 rows / 511 pins strict):** 813231FC's
  -fno-expensive-optimizations broke 7 of beldo.c's 28 pin-free rows; it disabled local-alloc optimize_reg_copy_1
  (local-alloc.c:1084), which retargets `(set a1 r); (set fr r)` into retail's `move $16,$5`; the three pins imitated
  it. At the module recipe: multi-set result carrier + u8 local, 3 -> 0.
- **reload_cse_simplify_operands is not in the retail (cdk 970404) compiler** (`strings` on cc1): a 2.8.0 row whose lone
  erasure turns an immediate into a callee-saved register (`sll $18,$2,$20`) is at the wrong cell (800AC3B0 1 -> 0 at cdk).
- **Unaligned aggregate copy = cdk marker** (818FF5B8 3 -> 0): cdk's output_block_move copies words 0,4,8 (retail),
  FSF 2.8.1 0,8,4 - a `packed` pointer + word copies + lwl/lwr in retail -> `*(T *)dst = SYM;` at cdk.
- **Parameter REG_EQUIV halves priority** (r81_opus_lc2, 81934928 5 -> 0, 818E6800 4 -> 3): a never-reassigned
  parameter carries REG_EQUIV to its stack slot; local-alloc.c:1064 doubles its live length, halving its global.c
  priority. A local copy / reassigned parameter ranks twice as high. APPEARS `T *x = (T *)param;` + callee-saved
  ASM_REG swaps; RESOLVES use the parameter directly (or the inverse: 80819B14 needs both parameters without REG_EQUIV).
  Generator: t132_paramequiv (r81_sonnet_t132).
- **Reload right after a store = an intervening store** (r81_fable_eqv, 81876014): cse invalidates every varying-address
  MEM on a store to a varying address (note_mem_written -> invalidate_memory); `e->z0 = 0; e->x1 = ...; e->z1 = e->z0;`
  gives retail's `sh $0; lhu` pair. Replaces a volatile read. A register copy survives cse/combine only if its source
  is reassigned before the copy's use.
- **s16 argument locals + ternary argument** (r81_opus_lc1, 800A4C0C 3 -> 0): calls.c converts s16 arguments before
  expanding a ternary argument's branch - retail's early `move a0,s2` + `move a1,s3` in the beqz slot.
- **Loop counter zeroed in every branch** (813284E4 1 -> 0): one `i = 0;` before the loop drops its priority below the
  competitor that should get the callee-saved register.
- **Round 82 (r82_fable_resid) - the second assumption under the cell, decided on 6 served-but-open crutch rows:**
  real on 3 (cell-carried pins: lone erasure `OP rd,rs,IMM -> OP rd,rs,$sN` = 2.8.x reload_cse_simplify_operands,
  absent at cdk; a flag masking a source shape: retail's "unscheduled" tail is sched1 output once one variable is reused
  for the preceding store - anti-edge; and **cdk's front end marks every sibling field of a struct with a `volatile`
  member volatile** (`mem/s/v`), FSF 2.7.2/2.8.1 do not - 80F90E88 48 -> 17 by dropping `void *volatile p50`), and
  ordinary source shape on 3 (8187A9A8, 81876014, 8009F018: stop cell/flag work). Egcs-proxy rows: cdk cse COMMONS
  page constants like retail, egcs recomputes them - an egcs row with page-constant pins belongs at cdk (8081822C).
  Opaque integer base `ori` vs `addiu` (combine nonzero_bits, 2.7.2 combine.c:6887-6890/726-731): a single-set base
  is known everywhere; retail's mixed `ori`/`addiu` needs a multi-set base or one live at entry - symbol spelling refuted.
- **Round 82 (fc12): 2.6.3 `mem & mask_var` puts the mask first** (expand_binop orders a MEM behind a REG); a literal
  mask gives value-first and lets loop.c hoist the constant into retail's register. m2c `goto` back edges without a
  LOOP_BEG note are not loops to loop.c (nothing hoisted); a goto-free do/while is.

## Round 83 (09-30 afternoon): what `-fno-strength-reduce` stood for; loop.c movable order; preference inheritance

- **`-fno-strength-reduce` rows are pointer-walk spellings of INDEXED loops** (r83_fable_nosr/MECHANISM.md, cdk loop.c line
  refs from the genuine source toolchain/gcc-src/2.7.2-cdk/). cdk reduces any pointer-walk biv with >= 2 constant-offset
  accesses into 0-offset registers (20-98 words off retail); a lone access is never reduced. Retail's stepping registers
  WITH offsets kept are what loop.c emits for `base[i].f`: T = base + i*s is a DEST_REG giv with a register add_val,
  reduced and replaced by one stepping register (`move R,base` / `la R,sym`). Rewrite: counter as the loop variable,
  walkers -> `base[i]`, increments dropped, parameters direct. `.loop` tells: `giv reg N ... mult S add (reg)` reduced =
  indexed source; `combined with` on DEST_ADDR givs = a pointer walk. CLASS.tsv: 67 of 71 flag rows are this class.
  Natural routes by which cdk IGNORES a loop (rare): `do { if (c) goto found; ... } while (t)` (multiple entry points)
  and `while (A || B)` (duplicated exit test before LOOP_BEG). An oversize `[N]` declaration view makes a scalar load
  MEM_IN_STRUCT_P - not byte-neutral inside loops that store through pointers (w_8005914C, w_800599B0 open on this).
- **loop.c movable order (r83_opus_b1, 819B3414 32 -> 0):** an array access `grid[column][row]` makes the index shift a
  movable hoisted to the END of the preheader; statements retail has after it must be later movables (a user-variable
  limit assigned IN the body through a named local: a literal is a compiler temporary the outer loops hoist further) or
  givs (a pointer computed from the counter inside the loop). PsyQ `P_TAG` `addr:24` bitfield assignments give the
  0xFFFFFF mask its extract+store references (flow counts refs before combine) - replaces a pinned link mask.
- **global.c expand_preferences is one in-order pass (r83_opus_b2, 818D4E68 1 -> 0):** a pointer written
  `if ((p = q->f) != 0) p = *(p - K)` where q is argument N of a call: test/dereference `q->f` directly so the load temp
  (q's last use) inherits q's argument-register preference and p inherits it from the temp.
- **A VAR_DECL array read `table[i]` expands base-first** (lui/addiu before the index shift); a `&table[i]` pointer local
  gives the shift first (800C4A80: 7 -> 3 off).
- A function whose call arguments are printf-style literals repeated per call (a debug print macro) may be an -O1
  object: town/func_8046C280's 0-pin natural text is exact only at `2.7.2-cdk-G0 -O1` (held: module is -O2).
