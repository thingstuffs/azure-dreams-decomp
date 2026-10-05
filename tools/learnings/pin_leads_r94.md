# Round 94 pin levers (2026-10-05) - what paid repeatedly, with lane and row
Read with pin_leads_r93.md and fable_r94_de48ec.md. Every item measured byte-exact on the named row.

## Allocation (global.c / local-alloc)
- MERGE two C variables when alloc_need's mover lives in another pinned variable's retail register: one C variable
  per retail register across disjoint roles (r94_opus_p28 8180C3C0 saved_text into message_text; p30 8182C800
  burst_count into distance_x = four $s1 roles; p33 80084340 sentinel variable also hosts the loop page base).
- HOST a value alloc_need calls "NOT A LOCAL QTY IN RETAIL" in the loop variable that owns the same retail register
  over a disjoint life (p35 800CA184 setup values in $t0/$t1/$t3 holders; check alloc_need on every PAIR of hosts -
  two merged allocnos can swap). If a remaining pin names the value, the host takes the pinned name (rename later).
- SPLIT a two-role $v0/$v1 pin variable into per-block locals (p28, p30 tile_origin_x -> + start_x).
- An extra NATURAL reference re-ranks global.c without code: `return result;` at a fall-through return
  (fable_r94_de48ec), a derived argument `(world + C) >> k` where the call takes `world >> k` (p32 800C4A80), a copy
  duplicated into both arms that cross_jump re-merges (p34 800B2D84).
- A set-once pointer the allocator leaves unallocated is rematerialised by reload into a spill register (p34 800B2D84:
  retail's tail `lui/addiu $8; lw 0($8)` = REG_EQUIV rematerialisation; the REG $8 + KEEP pins faked it).
- Compute a value in place into an existing global temp when a LOCAL qty blocks a global (p31 OT address
  `e = otz; e *= 4; e += base;`); load a masked value in place (`w = f; w &= 0xC000;`, p38 800AED64).

## Scheduling / combine
- In-place narrowing keeps the unfolded form and drops sched1's birthing boost (multi-set):
  `x <<= 16; x >>= 16;` on a shared s32 (p31), `x = (s8)x;` on an s16 local = subreg set combine cannot fold to `lb`
  (p36 818F2800), s16 target for an unfolded lbu;sll;sra byte (r94_sonnet_vb28 800CDFD8).
- An arithmetic chain retail leaves unboosted goes in its own MULTI-SET s32 local (p36; 1 of 19 orders exact).
- A store through a `T **` pointer local instead of an array subscript keeps a sched1 order the subscript
  (MEM_IN_STRUCT) loses - replaced a one-trip block (p29 80092824).
- Re-read into a clobbered accumulator defeats reload_cse deleting a reload (p31 800CA184 volatiles 7 -> 0).
- A memory read between two stores keeps the first store (cdk flow.c last_mem_set; p31).

## Structure / evidence
- READ THE RETAIL WORD OPCODE where a noreturn call is involved: a noreturn tail call compiles to `j`, so an m2c
  "call" to a phantom label can hide a `j` into the function's own join (p34 town/func_808B8184 2 -> 0 at its TRUE base
  0x80003984; diff.py --scorer now tags op2 jump / op3 call).
- Backward goto loops where retail has NO loop notes (why.py --pass loop count differs when structured) are the
  source's own: 17+ spellings 0 exact across r94_sonnet_fp9/fp10 - stop serving them.
- Revive OLD fewer-pin near-miss texts after fidelity cleanups (tools/lanes/old_nearmiss.py): p32 800C4A80 16 -> 0
  from r86_opus_up's forgotten 0-pin text; p34 2 rows.
- Definition prototypes are not always right: MEASURE one at a time; a K&R/implicit-int TU regresses
  (fable_r94_de48ec; fidelity_first.md updated).
- m2c's signed `/` and `%` by 2^k expansions are byte-neutral as operators on most rows: t144_divmod (CPU, ~70 rows).

## Open mechanism questions (better than row retries)
- Opaque scratch base: what C makes `scratch` (0x1F800000) unknown to sched1's alias check while combine still sees its
  low bits (800AED64 frontier cand/a2.c 0 pins dist 32; r84 opaque-base class).
- 80DE48EC: can an honest shape make reg_n_deaths != 1 for a block-local REG_EQUIV pseudo (needs a gdb probe at
  local_alloc entry; frame_gdb.py plumbing).
- 8180C3C0 object_slot: keep two identical address givs from combine_givs; 800CA184 column+row priority swap
  (one refs 29 vs address_mask 23).
