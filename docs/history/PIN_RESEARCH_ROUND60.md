# Round 60 (2026-09-20): the sol misses read, six generators from the wave's exact rows, a clone family solved by one type

Start: 5,682 pins / 1,175 rows (after round 59's class packs, [round 57-59 note](PIN_RESEARCH_ROUND57.md)).
Charter: [PIN_CAMPAIGN_CHARTER.md](PIN_CAMPAIGN_CHARTER.md).  Receipt: `docs/evidence/pin_research_round60_20260920.json`.

## Chain F: the last 1-3-pin sol slices (self-feeding, 04:00Z-08:30Z)

| slice | rows | landed | pins | note |
|---|---:|---:|---:|---|
| large5 | 15 | 1 | 1 | |
| mid4 | 15 | 3 | 3 | |
| large6 | 15 | 2 | 4 | a third row byte-exact but refused (below) |
| mid5 | 15 | 2 | 4 | |
| large7 | 15 | 4 | 5 | three of the four kept one pin (2 -> 1) |
| mid6 | 10 | 4 | 4 | the mid pool's last rows |
| large8 | 15 | 2 | 4 | |
| large9 | 14 | 3 | 3 | the large pool's last rows |

5,682 -> 5,653 / 1,163 over the nine slices (19 rows, 29 pins), every landing gated (covering windows + SLUS MATCH), committed by the
ten-minute snapshot loop.  Two-pin rows paid better than one-pin rows (large7: 4 of 15).

## Why the misses miss (the five lane reports, ~60 rows)

1. **Function-wide register role swaps** (about half): two long-lived values take each other's callee-saved or argument
   registers from prologue to epilogue; every spelling coalesces to the same RTL.  Includes the four-row sprite-spawn
   family (solved below, by a type, not a spelling), the three-row item-target family and the raw-height pair.
2. **Named residues at listing distance 1-5**: a literal zero copy-propagated where retail copies a register (two rows);
   two initial `lui` in the other order; a page constant folded lui/ori where retail has lui/addiu (a symbol address
   spelled as an integer); `move; addiu` combined into one addiu; a prologue `sw/move` pair one slot early (three rows,
   the known prologue copy-order class).
3. **Fence pins between repeated loads and later stores**: cse drops a reload retail keeps; solved once by moving an
   existing store next to its producer (t83 below), unsolved twice where no such store exists.
4. **Partial repairs**: disjoint-local reuse, u16 narrowing or folding assign-then-add gets the listing halfway and
   leaves a group-1 swap.

**Calibration of a residue screen** (every served sol row of rounds 59-60, 235 rows / 40 solved, `served_calib.json`):
RECOLOURED residues whose erase distance is at least 0.3 of the row's instruction count: 18 served, 0 solved;
RECOLOURED under 0.15: 26 served, 8 solved.  Rows of at most 60 instructions paid worst (4 of 44); rows over 250
paid 11 of 44.  The pack builder now screens the first group (`build_pack2.py`); nothing else separated cleanly.

**One byte-exact candidate refused**: `town/func_8032D6E4`, the model rewrote a three-way dispatch with labels and dropped
the `#ifdef NON_MATCHING` split; the arm-restore twin did not compile (nested `#ifndef` blocks).  Rewritten by hand with
the port arm intact: exact, landing rule satisfied, lane `r60_dispatch`.  A labelled dispatch outside a loop is a
spelling the owner has not ruled on (t48_gotoreturn is the precedent); flagged.

## The sprite-spawn family, solved: `s16` parameters (t84_narrowparams)

`dungeon/func_8132DED0`, `8132E6F8`, `8132E018`, `8132ED0C` (CHANGED|17-32, two `ASM_REG` copies of the 5th/6th
parameters each): retail loads the stack-passed offsets into $19/$20 in the prologue and holds them across the
allocation call; the erased build reloads them at each use.  gcc 2.7.2 `function.c assign_parms`: a parameter
narrower than the mode it is passed in gets a real pseudo with an entry conversion copy, not a REG_EQUIV memory it can
be reloaded from, so it crosses the call and `global.c` gives it a callee-saved register.  `offset_y, offset_z` as
`s16`: listing 44 -> 16 (prologue loads back, allocation order still wrong); all three offsets `s16` (or `u16`):
byte-exact, no scaffolding, all four rows, 8 pins.  The sol pack had measured every placement variant at 26-30 and never
a type.  Generator `tools/xform/t84_narrowparams.py` (parameter groups narrowed jointly, copies dropped, listing
screen): 4 of 4 family rows and `slus/w_8004A330` (4 pins); 32 eligible rows in the tree.  None of the five functions
has a textual caller in `src/` (table-called), so the signature change has nothing to reconcile.

Bounded the same way (`family_notes.md`): the item-target family (volatile byte loads fix order and registers but 2.8.0
expands a volatile QImode load as lbu+sll/sra: distance 8) and the raw-height pair (u16: 20; volatile signed load: worse).

## Six generators from the wave's exact rows (Opus agents, one family each; `tools/lanes/gen_drive.py` validates on the lanes' pre-landing texts)

| generator | what it restores | exemplars (byte-exact) | tree sweep: eligible / exact rows / pins |
|---|---|---|---|
| t78_aggcopy | a scalarized whole-object copy as one aggregate assignment (`*(CopyN *)dst = *src`) | 81087524, 818B7E14 (818C2FAC stops at 6: its pins are on other variables) | 9 / 2 / 2 (siblings of 81087524); the family is nearly spent |
| t80_derivecall | a pure derived assignment (`p = base + 0x20`, `p = &sym`) moved from after a call to before it, so the pseudo crosses the call; plus the split-shift merge | 8133A5D0, 818ED25C | 218 / 6 / 6; misses' median listing distance 9 |
| t81_reuselocal | an arm-confined local hosted on a dead same-typed function-scope local, initialiser merged; generalises natural.host_candidates to any pin kind | 8081DED0 (8081791C reaches 8, as the lane did) | 294 / 5 / 5; 418 rows have no braced window (unbraced `case` regions: the next increment) |
| t82_armsink | a join local's consumer sunk into the arms, or a statement repeated in every arm hoisted out | 8008D084, 8008BCD0, 80EDF8B8 | 151 / 3 / 3 (two leave an empty `if` arm; spelling-trade rule) |
| t83_storeafterproducer | an existing store moved next to its producer (invalidates cse before scheduling) | 80D1170C (both stores jointly) | 131 / 6 / 6; misses at distance 1-4 want a joint move of a store run |
| t84_narrowparams | pinned `s32` copies of `s32` parameters dropped by declaring the parameter group `s16`/`u16` | the four spawn rows | 32 / 5 / 17 (the slus row carried 9 pins) |
| t19_modpow2 (extended) | the remainder tree with a named rounded quotient, folded into its reader | 800D5794 | 19 / 0 new (one other row of the spelling, no fold) |

Model spend: four Opus agents, 160k-196k tokens each, one generator family per agent, validated on the lanes'
pre-landing texts through `tools/lanes/gen_drive.py` (`--base-from <lane>`; stages into `work/native_lane/r60_<gen>/out`,
never writes `src/`).  All seven are in the landing cascade (`land_lanes.sh`, `coherence_sweep.py`).

Landed (`land_r60*.log`): the dispatch row (2 pins, 5,653 -> 5,651), the t84 lane (5 rows, 17 pins, 5,651 -> 5,634 / 1,157), then the
five generator lanes in one transaction between chain G's codex lanes (t83 6 rows, t80 6, t81 5, t82 3, t78 2; one row shared by t80 and t82 landed once and the cascade took the second pin): **5,634 -> 5,612 / 1,157**, 21 windows + SLUS MATCH.

**Round total so far: 5,682 -> 5,612, 70 pins** (chain F 29, the dispatch row 2, t84 17, the five generators 22), with chain G's first 4-8-pin slice landing 4 rows (4 pins, 5,608) as this note is written; the receipt's `after` count includes that slice.

Debt named, not fixed: of the two other PORT_COMPILE refusals of 09-19, `dungeon/func_800C96AC` has since landed pin-free by the Opus symbol lane, and `dungeon/func_800A21EC` (3 -> 1 pins, byte-exact) is a port-arm question for the owner, not a tool gap: the current port arm stores the page base `0x800A0000` where the scored arm stores `0x800A0000 + 0x77AC`, the candidate writes `&D_800A77AC` for both, and the landing rule refuses any change to the port build's code (clause: port codegen identity); a human review of that port arm lands it; rows whose fences t83 removed keep a stale `/* MECHANISM: ... barriers ... */` comment (readability-later rule).  The pack builder now lives in `tools/lanes/build_class_pack.py` with its inputs in `ledger/pack_inputs/` (chain G still runs the scratchpad copy).  Next lever for the swap class: read `global.c`'s allocno ordering (`allocno_compare`: refs, live length, size) against the inputs `tools/alloc_trace.py` / `alloc_probe.py` already dump under gdb - the way `sched.c` paid in round 57.

## Chain G: sol on 4-8-pin rows (untested there; luna and Gemini paid nothing)

Ran 08:30Z-14:16Z behind chain F: 15-row slices by residue class with the screen, a kind stopping after a slice
that lands nothing.  Sol pays on 4-8-pin rows, thinly: large 4 of 15 then 0 of 15 (stopped, 35 rows left in that
pool); mid 1 + 1 rows (7 pins; the pool of 17 is spent); far 1, 2, 2, 3, 1, 1 rows over six slices then 0 of the
last 5.  Eleven slices, 16 rows, 25 pins: **5,608 -> 5,586 / 1,156**, committed by the snapshot loop (df289cd4).
Chain G ended itself (`CODEX59G_END`).  The far band on 4-8 pins paid one row in eight, better than far on 1-3 pins
(2 of 30): multi-pin rows carry more of the same mechanism, so one found move pays twice.

Round 60 close: **5,682 -> 5,586 / 1,156, 96 pins** (chain F 29, dispatch 2, t84 17, five generators 22, chain G 25).

## Round 61 openers (the night of 2026-09-20/21, three Opus agents on the named levers)

**The allocation-order rule** (`work/native_lane/r61_alloc_study/NOTE.md`): a function-wide register role swap is a
one-position error in `global.c`'s allocno sort, not a colouring mystery.  A pin is a missing allocno (a `register x
ASM_REG` decl is a hard register, not a pseudo); erasing it adds one allocno and everything below slides one register
down.  The sort key is `allocno_compare` (2.7.2 `global.c:586-608`): `floor_log2(n_refs)*n_refs/live_length*10000*size`,
descending, ties by allocno number = declaration order; `find_reg` (`:904-985`) hands call-crossing values `$s0, $s1, ...`
strictly in rank order (no `REG_ALLOC_ORDER` on MIPS).  Why the packs' 10-20 variants all coalesced: `reg_live_length`
is measured after scheduling, and reordering independent statements changes nothing (60 legal permutations of one
prologue give two live-length vectors).  Levers that move the key: delete a redundant copy of a formal (the live range
then starts at entry), split an over-used local (refs fall, life lengthens), dependency-crossing moves, type
narrowing.  A simulator (`sim.py`) reproduces the real register dispositions on all 14 studied builds, so it is a free
gate ahead of the listing screen.  Two rows byte-exact by the levers (`town/func_800AC3CC`, `dungeon/func_8009AB4C`, 4
pins); two more have the colouring solved with an emission residue (6, 18); two are the preference family
(`set_preference`), not order.  The generator on this rule, `t85_allocorder` (levers a/b/d, each candidate compiled once with `-dl -dg`, the
disposition simulator `tools/alloc_sim.py` as a population and candidate gate, listing from the same dump), finds both study
rows by itself and sweeps the tree in 32 s: 453 rows with a callee-saved `ASM_REG`, 350 textually eligible, 78 genuine
order sites (272 rows fail the APPEARS test: dispositions not a permutation, or the preference family), 0 new exact rows.
On fresh rows every best candidate is a type change and the redundant-copy / split-meaning shapes are rare; 11 rows have
the colouring right with a residue elsewhere (the study's d=6/d=18 class).  Not in the cascade (nothing to add there yet).

**t80's near band** (77 rows at listing distance <= 4): 45 are one instruction moved where the up-move is
listing-neutral (those pins hold scheduler tie-breaks and delay-slot fills), 10 are one `lui`/`li` fewer (the
candidate CSEs two identical page constants retail materialises twice: a SYMBOL_REF-vs-CONST_INT spelling, t29
territory, the clearest lead), the rest small.  A down-move step (0-4 statements) added one row
(`dungeon/func_800C9858`); deeper up-slots and joint moves paid nothing.

**t83 joint store runs and t81 run/case windows**: both increments built and regression-checked on the recovered r60
inputs (6 of 6, 5 of 5), 0 new rows over 219 and 356 eligible; the "unbraced case" class is 7 rows in practice (pins in
the function body are the real remainder, now covered by a statement-run window).  Widening the scorer fallback to four
runs at listing distance <= 2 also found nothing: the screen's near band hides no byte-exact texts here.

**Chain H** (sol, from 23:05Z): retry slices on the rows only Gemini has served (mid classes 53 rows, MOVED/CHANGED-small
46) and the never-served far band at 1-3 pins (105), built by `tools/lanes/build_class_pack.py --only-served-by r58_order`.  First result: the mid-class retry landed 0 of 15
(sol does not recover what Gemini missed in those classes; the kind stopped itself).
