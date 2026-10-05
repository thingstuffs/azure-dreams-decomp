# Pin / alignment mechanisms found in round 92-93 (one entry = APPEARS -> RESOLVES, rows, what failed)

Sources: r92_agyO_p1, p2, al1 (Opus 5.5 on the agy rails), r93_sonnet_ot1/ot2 (PsyQ idiom), al3/al4 + r92_agyS_al2 (cell alignment),
r93_sonnet_s1 (scaffolding). Only mechanisms that are new relative to tools/learnings/*.md and the brief paragraphs are listed;
cross-references are to the existing paragraph they extend.

## L1. dbr marker from ANOTHER loop's backward fill (solved dungeon/func_81810198, 1 -> 0)  [extends dslot.md "Delay-slot residues"]
APPEARS dbr.py DECIDING on an erased arg-register pin: `li $4,8 -> REJECTED: sets $a0, LIVE at the opposite thread ... ADDED by find_dead_or_set_registers at
(use (insn 234))` where insn 234 is `addu $4,$4,1` that fill_simple moved into the slot of a LATER loop's `bne` (m2c do-while with the counter increment
BEFORE the exit test, filled BACKWARD). update_block leaves that USE marker, so $a0 is live at the earlier jal and the beq's fill_eager copy of the target head is refused.
RESOLVES restructure THAT later loop as increment-after-test: `for (i = 0, p = state; i < 3; i++, p += 4)`; its `bne` is then filled from the TARGET thread (INSN_FROM_TARGET_P,
no marker), $a0 is dead at the jal, and the earlier beq takes `li $4,8`. Then drop the ARG-register pin and pass the literal `8` (func_800DBF38 is void(void): the 8 was never its argument).
Measured: literal alone dist 7 / total 2; for-loop with the cursor stepped in the BODY 12/6; the do-while with `i += 1` moved after the test is also exact.
Brief change: dslot.md says that with a `(use (insn N))` marker "only an argument set placed before the branch helps" (800C379C). Add the second remedy: change the form of the loop whose slot created the marker. Look at which branch owns insn N in `dbr.py`.

## L2. abs() priority flip (solved dungeon/func_81820800, 1 -> 0)  [extends t16 abs, r83 rules]
APPEARS a register-colour pin (USE/REG) on a multi-role variable `x` that also feeds a hand-written abs whose TEST is on x but whose NEGATED variable is another: `d = (s16)x; if (x < 0) d = 0 - d;`
(the y side of the same row already spelled `abs_y = abs(abs_y)`). The t16 detector misses it because the test and the negate name different variables.
RESOLVES `d = abs(x)` - same bytes (abssi2 = `bgez; move; negu`) but ONE pre-combine ref instead of two: x 16 -> 15 refs, floor_log2 4 -> 3, priority 10322 -> 7377 (prio.py), so `effect` (9230) ranks first and takes $s1, x takes $s2 = retail.
Needs the r91 spelling trade (the masked tile x hosted in the pointer variable `effect` of the case-1/2 loop; record the trade) and the `effect->unk_20 = state_obj` store at its retail position (moving it early cost 2 words).
Failed (store at retail position): host without abs 42; abs without the host 284; other hosts with abs: start_y 4/2, velocity_x/y 18/9, abs_y 16/21, phase 288, end_x 287, duration 343; `abs((s16)x)` 8/5; two-step narrowing 42; goto loop 74.
GENERATOR: extend t16 to the test-on-x / negate-d form (candidates: any row with a USE/REG pin whose erased residue is a pure $s swap and a `if (x < 0)` followed by `= 0 - d`; run prio.py after).

## L3. PsyQ setaddr/getaddr OT idiom (3 landed, 1 refused, ~9 rows where it did not apply)  [extends structured_loops.md "P_TAG / setaddr / getaddr"]
APPEARS an ASM_REG (or ASM_KEEP_NV) on a loop-invariant 0x00FFFFFF OT mask (`addr_mask`) in an m2c-expanded link `(*p & 0xFF000000) | (ot & 0xFFFFFF)`; erasing the pin = pure $s recolour against a call-crossing local (mask pseudo ranks just below the competitor in prio.py).
RESOLVES the PRIM-TAG stage written as the bitfield pair `setaddr(prim, getaddr(OT slot))` via a local `P_TAG` typedef (same as landed 80DB9000 / exemplar 81845068; no P_TAG in include/): the double mask adds +2..+4 flow refs to the 0xFFFFFF pseudo (combine folds them later),
lifting it above the competitor (81845068: 13 refs / live 209 = 1866 > depth_bucket 1616; ASM_REG gone). The OT UPDATE stage keeps the multi-set `tag_mask` variable; read the OT base through the GameWork struct.
Landed: dungeon/func_81845068 1 -> 0 (p2), town/func_8080DAB8 2 -> 1 (ot1; all FOUR stages setaddr/getaddr, no tag_mask/addr_mask left; mixing bitfield and old stages: 29-52), dungeon/func_819112CC 4 -> 3 (ot1; prim tag <- OT word sites as setaddr/getaddr, link store keeps the multi-set 0xFF000000 var and a literal `& 0xFFFFFF`).
DID NOT APPLY (do not retry): (a) the link-STORE stage `*link = (*link & mask) | (prim & 0xFFFFFF)` as setaddr (double mask, dist 86 on 819112CC, 107 on 81904990); (b) full `addPrim` on both halves hoists 0xFF000000 too (64-88, frame grows; 81845068); (c) sites that use TWO mask registers through m2c work_bits/work_value temps
(town/800AED64: even the PINNED control breaks, 26/43 - the bitfield form changes the insn count); (d) pins that are not mask pins: 81976CB0 (ASM_KEEP transform_flags, one-word MOVED residue), 80B467DC (KEEP effect/next_node, 16 lines), 807B0B3C (ASM_REG $4 draw_value, 110, identical RTL), 81989558 (KEEP_NV ring: +12 weighted refs, prio 21306 -> 24146), 818F2800 (4 independent pins; code-neutral);
(e) 81904990 got the mask pins to fall mechanically (addr_mask lands in $19) but length_mask/sprite_base ($23/$22) are reversed and packet_tag $2/$3 swap: best dist 54 with 1 pin, not stageable.
REFUSED: dungeon/func_81910A9C 2 -> 1 (ledger/refused_trades.jsonl round 93): dropping `ASM_REG($23) angle` and writing the first link stage as `(word & addr_mask & addr_mask)` was exact (prio 1421 vs 1436 -> mask above angle) but it is an idempotent re-mask written only to steer global.c = fake dependency (same class as form S / 09-12 revert); the natural PsyQ spelling with the extra mask ref was not exact (all-bitfield 47 pinned / 323 erased; mask var + bitfield stores 101-107; multi-set mask at loop top/bottom 4-10, ORDER 2 words).

## L4. cse-follow-jumps via a local pointer read (solved main/func_8001F368, `-fno-cse-follow-jumps` crutch retired at equal pins)  [r83 rules / crutch_flags.md]
APPEARS a row registered with -fno-cse-follow-jumps whose retail RELOADS a scalar global after a store through a struct pointer (here a `menu->unk_30` timer store between two button-global tests).
RESOLVES read the global through a local pointer to it: `s32 *held_p = &D_801379A8; s32 *press_p = &D_801379B0;` and test `*press_p & ...`. Mechanism (stock 2.7.2 cse.c note_mem_written): a non-struct `(mem (reg))` read is a "varying address" entry that invalidate_memory drops after any varying store,
while a plain `(mem (symbol_ref))` scalar survives; so follow-jumps no longer carries the earlier read across the store. A struct/array global (astra's spelling) gave 16/31 and a single Pad struct 14/25; the scalar pointer pair gave 0.
GENERATOR: sweep rows on `-fno-cse-follow-jumps` for "retail reloads a scalar global across a struct store" (the diff shows an extra `lw` of the same global); one local-pointer rewrite per global read, verify at the recipe without the flag.

## L5. sched1 birthing boost and single-set copies (3 rows: one solved, two leads)  [extends narrow_copy.md / near_miss.md birthing notes]
Rule (birthing_insn_p): an insn whose destination is live at block end with `REG_N_SETS == 1` gets a priority boost, so backwards scheduling issues it EARLY = late forward. A copy that must come FIRST in retail needs the pseudo to have >= 2 real sets.
- main/func_8001A0F0 solved (crutch `-fno-schedule-insns` -> 2.6.3-G0 retired, 0 -> 0 pins): the state-three arm's `return status;` copy was picked T-5 in sched1 (stores win equal priority on potential hazard, the constant on birthing boost); v0 then lived over the constant. RESOLVES route the arm to the existing common return (`goto done`; the state-one body inlined into the `state < 3U` branch so the goto count stays 4): the return copy sits in the join block, constant in v0, pointer in v1, reorg copies `move v0,s0` into the jump slots. Goto-free structured rewrites 29/19 (retail block order follows the goto layout).
- dungeon/func_80095160 (p2, 3 -> 1): `tile_coord = target_x >> 6` loses the boost when `tile_coord` keeps two REAL sets: re-set the shift's source (`coord_or_height`) between the shift and the call with a value the call needs (use_crosses_set_p blocks combine folding the shift into the a1 copy). A no-op second set is folded by cse (23 unchanged) - the second set must be real.
  Also there: a duplicate trailing `return -1` next to `label: return -1` lets cross_jump move the label onto the trailing copy, so fill_eager steals `li v0,-1` into the EQ branch slot (barrier residue): fold the duplicate through the existing `goto move_failed` and order `if (!(A||B||C||D)) return result; BODY` first (a spelling trade: the final goto jumps into the label block already present in the base).
- dungeon/func_80289BD4 (al4, open): origin_x/origin_y copies (uid 24/27) get the boost; retail has them first. Needs a source shape where the saved x/y pseudos are set at least twice; natural params-untouched rewrite 51-80; no-op re-set folded.

## L6. Spill/frame lead on dungeon/func_80DE48EC (open, 5 pins)  [extends spill_register.md]
APPEARS `register void *output ASM_REG("$8")` passed as an argument and re-read at a later call, plus a padded one-word struct local `struct { void *saved_ptr; u8 pad[20]; } state` reloaded at the tail.
LEAD: evidence/80DE48EC_spill_pinfree.c has 0 pins: `output` as a plain local used at both calls. All nine callee-saved s0-s8 are taken, prio.py ranks it 13/15 priority 329, global.c spills it to 16(sp), and reload produces what both pins imitated: reload register $t0 (first never-live call-used, greg "Spilling reg 8"), retail's `addiu t0,s1,-32; move a0,t0; jal; sw t0,16(sp)`, and the tail's `lw a0,16(sp)` order (the sched2 residue r91c could not move).
BLOCKER: frame 64 vs retail 80 - retail has 20 unreferenced bytes at 20..39 after the spill slot at 16. A local array cannot make them (MIPS frames grow upward; expand-time locals sit below reload's slots), so it is a reload-time `assign_stack_local` that stays unreferenced; the only orphan-slot mechanism found is the caller-save area (cdk caller-save.c setup_save_areas 250-300, after alter_reg), but CALLER_SAVE_PROFITABLE (refs > 4*calls) is reachable by no allocno here (actor 16 refs / 9 calls; spilled values 2-4 refs / 7-9 calls). Also an s7/s8 tie (sprite 515 vs result 512: +2 luids flips it) and one sched1 `move a0,s1` placement.
Totals at 2.7.2-cdk-G0: inherited 1-pin text 6; spill text 35 (frame shift dominates); output-reuse 33. NEXT (falsifiable): gdb on cc1 breaking on `assign_stack_local` during reload, on the pinned base and on the spill text; find what population of call-crossing values makes the 20 bytes.

## L7. Other measured mechanisms (open rows; no generator)
- dungeon/func_813274E4 (1 pin, pin-free total 3): retail's `lbu v0,13841(v0)` sits after all six prologue saves because in sched2 an sp-based store conflicts with `(plus REG const)` (memrefs_conflict_p 629-830) but never with a CONSTANT_P or LO_SUM address; unpinned, combine folds the single-use page constant into `(mem (const_int ..))` -> floats above the saves. flow.c 2145 LOG_LINKs the page constant only to its FIRST use: a probe with two loads (page[0x3610], then page[0x3611]) keeps `lbu $2,13841($4)`. Need: a natural earlier use of the 0x8001 page that survives combine but leaves no instruction in retail. Failed: page pointer/cast/absolute 9, mode-first 5, raw-first 6.
- dungeon/func_8008F228 (2 pins): reload_cse_simplify_set (reload1.c 8142) rewrites each walker's constant load into a copy from the LOWEST-numbered register already holding K, so retail's `move t3,s0; move t4,t3` needs src_ptr's load first AND src_ptr to outrank rec_src; both 7 refs, the earlier-loaded lives longer (52 vs 51) and loses (49 init permutations, best 4). probe_i: a hard-register `+= 1` expands through a temporary, a pseudo's does not, so the slot loop drops 139 -> 138 real insns and D_800DCED4's HIGH flips from `not desirable` to `moved` (spilled, rematerialised in $t8).
- dungeon/func_81876014 (7 pins): lockstep vertex writers under -fno-schedule-insns; one multi-set x plus a saved copy reused for z2 reproduces retail's `x0+16` twice (0 pins, total 24); the y copies need three surviving SI class heads that outlive the cse block (cse.c 856-870).
- slus/w_80048B8C: sched2 block 5, store 76 and add 81 tie at priority 2; schedule_select takes the store on potential hazard; priority() only grows through load-fed chains, so only an add writing v1/a1 or a loop/EH note between them orders store-then-add.
- town/func_800AE09C: reload_cse_regno_equal_p reuses a constant only into an equal/narrower mode; mode choice keeps four `li`; residue is sched1 (the combined a0 argument insn sits at the call LUID).
- town/func_808B2B04 (al2): fill_simple_delay_slots' epilogue-slot scan takes the return `move v0,a1` (mask == RA_MASK, call-used regs) so v0 is live at the exit and the loop slot cannot take `addu v0,a0,a1`; retail keeps the move before `lw ra`. Need a legal return shape whose final move is ineligible without a new saved register.
- town/func_806D30B4 (al2 side lead, EXACT at plain 2.6.3-G0 with the r91c loop rewrite: `entry = &entries[entry_index]` at the loop head, no `entry++`, test `entries[entry_index].flags != 0`): retires the registered `-fno-strength-reduce` (pins 0 -> 0). Single counter biv -> loop.c derives the address as a giv; the separate walker biv was the reason for the flag. Not staged (assigned target was 2.7.2-G0); orchestrator decision. File: r92_agyS_al2/side/func_806D30B4_exact_at_2.6.3-G0.c.
- main/func_8001C4D8 (al3, open 29 -> best 20): pure global.c colouring; menu 14 refs/live 82 prio 5121 must drop below offset_cursor 4090 (refs <= 11); a tail role that takes ~3 menu refs without being copy-propagated. Tail reuse of primitive_cursor 20, offset_cursor 23, offset_slot 32.
- Recipe retirements (alignment lanes, equal pins): town/func_8080BCD4 (2.7.2-G0 -fno-schedule-insns -> 2.6.3-G0), dungeon/func_81893024 (2.7.2-cdk -> 2.7.2-cdk-G0), town/func_80813E14 (2.8.1-G0 -mno-split-addresses -> 2.6.3-G0), dungeon/func_80E8D490 (2.8.1-G0 -> 2.7.2-cdk-G0), main/func_8001F368 (L4) and main/func_8001A0F0 (L5): 6 of 10 alignment rows retired at the target cell (4 were pure recipe switches; 8080BCD4, 81893024, 80813E14, 80E8D490 bases were already exact there): ALWAYS re-score a registered-crutch row's CURRENT text at the target cell before writing C.

## L8. Scaffolding (s1: 6 rows, 0 of ~120 respellings removed one barrier alone)  [confirms one_trip.md]
Per barrier, what it holds (do not retry the natural spellings): town/8096D944 five `do { entry_index++; } while (0)`: ++ barrier = global.c loop-depth weight on the counter ($a0/$a1 swap dist 12); `entry = *slot` blocks dist 2 with a jtbl word. dungeon/80286AF8: `goto tally -> break` dist 161 (jump.c rotates the exit test and renumbers regs); empty `do {} while (0)` after `rh = jr;` dist 2 (cse copy-propagates jr->rh: `sll $2,$21,16` vs `$2,$2,16`; respellings if/else, test on rh, `rh = jr = f()+5`: all 2). town/80953900: two EMPTY barriers after `entity->quantity` +/- 1: dist 11/16 (sched hoists `timer = 0x10` and `lhu state` above the D_80012D5C load; the barrier orders store(quantity) -> load -> rest). main/func_80402A1C (8001BA1C): `loop: do { body } while (0); if (id_ptr < stack_end) goto loop;` -> do/while(cond) 135-144 (loop.c): this goto-loop is how the row avoids loop.c; `opcode = 0x48` wrapper dist 6 (the note splits the basic block, retail `li $14` sits before `lui $13`). slus/w_8003931C: the one-trips raise the ref weight of variables inside (index_byte/entry_index $s2/$s3 swap, 16-20). town/808B3620: 4-word copy loop avoiding loop.c; the 13-word struct assignment gives the identical loop (MIPS block-move expander, dist 7 with the right 4th arg) - retail wrote an explicit pointer copy loop. See goto_recipes.md section 8 for the joint-removal cases that DID work.

## r93_opus_ca184 (dungeon/func_800CA184 11 -> 10, gotos 32 -> 24) - base-pointer facts
- A REG-pinned (ASM_REG) constant base blocks loop.c's giv reduction (`li $5,K; addu` instead of `addiu $4,$16,K`):
  walkers at base+K*stride are reduced givs of index loops over a PSEUDO base - type the scratchpad as a struct, index
  loops, then erase the base pin (207 listing lines -> 10).
- sched1 alias: a single-set constant base carries REG_EQUAL, so its stores are disjoint from symbol loads; retail
  order (loads after scratch stores) = an unknown base. A COPY of the base made after a join label has no REG_EQUAL,
  is free when global.c coalesces it, and must stay live while competing pointers are (owner review: ledger trade).
- Keep a goto loop where retail does not strength-reduce (two bivs in one for(;;) split a register).
- Exemplar with the same scratch layout, pin-free: src/town/func_800AF9D8.c.

## r93_opus_vb5 (dungeon/func_81904990 4 -> 0; town/func_800AED64 volatiles 6 -> 2)
- Second confirmation of the vb4 recipe: s16 per-block byte arithmetic + ONE walker per pointer in a real loop. A REG
  pin on a walker stands in for the loop.c offset folding it itself blocks (`frame_header+8` -> retail's $16, 27
  packet offsets -> retail's $8 that m2c named `quad_end`); KEEP_NV on mask constants falls with it.
- A variable shared by two blocks that pins to $2 = it became global; retail has one per block.
- OPEN: halfword `lhu; sll 16; sra 16` (800AED64 unk_16A) is NOT the byte family - HI/u16 hosts 36, only a store
  between load and extension keeps it (cdk combine.c ~10506); next: combine.py --insn on the pinned text with VOL#5 erased.

## r93_opus_p16 (800A1AD4 7 -> 0, 8009E0EC 8 -> 0; 14 gotos -> 0)
- m2c `goto scan; found:` stub BEFORE goto loops = real loops with the exit INLINE in each: loop.c
  find_and_verify_loops moves both exits to the first block's return barrier and jump2 merges them (retail layout).
- Narrow (s16) parameters used directly: cse never makes the narrow copy the head of the full value; s32 base copies
  are what needed KEEP_NV(x). An s16 loop `dir` shares the call-argument/index extension (`move $16,$17`).
- loop.c hoisting threshold: count real insns in the loop (11*2*2 = 44 >= 44 hoists the table address); a
  natural spelling that adds one insn (u16 read as (s16)) keeps retail's in-loop `lui`.
- Multi-role m2c temps: split where alloc_need shows a priority inversion; a block-local chain hosted in a temp a
  second block also uses becomes a global allocno like retail's (spelling trade, owner review).

## r93_opus_p17 (8009F018 7 -> 0; 819613A8 open)
- Copy V = W where retail still reads W after the copy: cse make_regs_eqv keeps the register with the LATER last use
  as class head - put the copy before the branch (optimize_reg_copy_1 stops at it) and give W a real later use that
  combine folds (return through W). Trade recorded.
- 819613A8: local-alloc assigns lowest-free registers BEFORE global; short high-priority locals take $v0/$v1, and a
  global is invisible to it (row took $a0, retail $a1 -> retail had a block-local value there). combine refuses to
  fold a copy of a call's return value (combine.c:943). Next: a re-read of one height after a store (reload deletes
  it) to lower its local priority below ~1100. Prototypes from sibling 8195FB34 are exact (cleanup only).
