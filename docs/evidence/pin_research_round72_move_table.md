# Round 72 harvest: MOVE TABLE from the second KIT wave (2026-09-21)

Source: the 46 `base/out` pairs with fewer pin sites in `out/` across
`work/native_lane/r71_kit_astra1 .. r71_kit_astra12` (five rows per lane came back with a byte-exact
candidate; the lanes' other rows produced no `out` text).  Total **118 pin sites removed**.
Pin counts are `pin_census.sites_of(base) - sites_of(out)`; the removed sites were listed macro by
macro (`ASM_REG` declarations, keeps, barriers) so each pin is attributed to the edit it sat on.
Where one row mixes two moves the pins are SPLIT between them and both entries say so; the split
rounds 118 down to 117 in the table below.

The astra lanes' own rule sentences are quoted from `work/native_lane/r71_kit_astra<N>/REPORT.md`
(`**Generator rule:**` under each `### <row>` heading).

Ranked by pins freed in THIS wave; the last column is the combined rank over rounds 67 + 71 + 72.

| # | move | pins | rows | owner today | verdict | recurs |
|---|---|---|---|---|---|---|
| 1 | a dead local's storage reused for a later value (the merge) | 36 | 21 | t93_scopemerge, t87/t90, t81_reuselocal | detector gap (cross-type donor, function-level donee) -> **t93 extension** | r67 B (20/10), r71 B (8/8) - **all three rounds** |
| 2 | the declared PARAMETER width changed in every declaration, the entry copies and their keeps erased jointly | 24 | 5 | t36_paramwidth, t84_narrowparams | pin-plan + menu gap -> **BUILT t98_paramcell** | new as a wave family (t84's four hand rows, round 59) |
| 3 | a staged page value spelled as the named symbol | 12 | 5 | t92_pagerun, t97_pagesym | spelling/shape gap, measured at listing distance 2 - NOT closed here | r67 A (10/5), r71 C (8/4) - **all three rounds** |
| 4 | de-register AT THE SAME WIDTH paired with an unpinned local's retype | 9 | 5 | t37_localwidth | menu gap -> **t37 extension with a listing screen** | r71 F (4/3) |
| 5 | scalarised load / or / store written as one field expression | 7 | 2 | t94_castsplit (inverse), none | new detector -> **BUILT t100_rmwfold** | r67 D / r71 D+E in the SPLIT direction (21/11) |
| 6 | one-offs (see H) | 7 | 4 | - | NOT BUILT | - |
| 7 | the aggregate copy widened, with an invented byte-array typedef | 4 | 1 | t78_aggcopy | detector gap; `unscored_text` gate OK -> NOT BUILT here | r71 G (7/2) |
| 8 | the abs() idiom folded into the difference | 4 | 1 | t96_absplace, t16_absidiom | joint-plan gap (t96 reaches distance 2) | r71 A (9/4) - t96 built there |
| 9 | the join/tail statement duplicated into every arm | 4 | 3 | t82_armsink | detector gap -> **t82 extension** | r67 F (6/2), r71 #12 (1/1) - **all three rounds** |
| 10 | the symbol read as an ABSOLUTE memory operand (`*(u16 *)0x80013714`) | 4 | 3 | t29_addrsym (inverse), none | new move -> **BUILT t99_absmem** | new |
| 11 | a statement written after the call instead of before it | 3 | 2 | t71_updateaftercall | detector gap, unchanged from r67 E | r67 E (4/4) |
| 12 | a `static __inline__` helper recovered | 2 | 2 | none | NOT BUILT (search space) | r67 G (6/4), r71 (1/1) - **all three rounds** |
| 13 | a struct field retyped so two reads share one word | 1 | 1 | none | NOT BUILT (1 row, type invention) | new |

## Combined three-round ranking (the one the build set follows)

| rank | move | r67 | r71 | r72 | total | state |
|---|---|---|---|---|---|---|
| 1 | local merge / storage reuse | 20/10 | 8/8 | 36/21 | 64 pins / 39 rows | t93 built; cross-type donor NOT built -> **built this round** |
| 2 | page value -> symbol | 10/5 | 8/4 | 12/5 | 30/14 | t92 + t97 built; the r72 forms still miss (see C) |
| 3 | statement granularity (split r67 D / r71 D+E, merge r72 #5) | 9/4 | 12/7 | 7/2 | 28/13 | t94 splits; the MERGE direction **built this round (t100_rmwfold)** |
| 4 | parameter width interface | - | - | 24/5 | 24/5 | **built this round (t98_paramcell)** |
| 5 | de-register at the same width + an unpinned retype | - | 4/3 | 9/5 | 13/8 | **built this round (t37 extension)** |
| 6 | abs idiom | - | 9/4 | 4/1 | 13/5 | t96 built; the joint two-site plan not |
| 7 | aggregate copy widened | - | 7/2 | 4/1 | 11/3 | NOT BUILT (see G) |
| 8 | join/tail duplicated into the arms | 6/2 | 1/1 | 4/3 | 11/6 | **built this round (t82 extension)** - recurs in all three |
| 9 | `static __inline__` helper | 6/4 | 1/1 | 2/2 | 9/7 | NOT BUILT - recurs in all three |
| 10 | statement moved across a call | 4/4 | - | 3/2 | 7/6 | t71 detector gap, unchanged |
| 11 | absolute memory operand | - | - | 4/3 | 4/3 | **built this round (t99_absmem)** |
| 12 | value staged through a fresh/other local | 2/1 | 4/4 | (inside #1) | 6/5+ | folded into the merge family |

---

## A. A dead local's storage reused for a later value -- 36 pins / 21 rows

  Pins by row: `dungeon/func_80CBD2E0` 4 (of 7), `func_818B0E10` 4, `func_80BC1BA8` 3 (of 5),
  `func_80BD9BA8` 3 (of 5), `func_80C153B8` 3, `func_8009CCC4` 3, `func_8180A990` 2 (of 3),
  `func_813238E8` 1 (of 2), and one pin each on `func_81334230`, `func_81989558`, `func_81984754`,
  `func_80A1FBBC`, `func_80BECDA4`, `func_80B97C10`, `func_80ADD000`, `func_80084084`,
  `func_800B8F90`, `func_800A3D40`, `func_800D1A48`, `func_800C1C20`, `func_80CE83EC`.

  The lanes state one rule in eleven spellings, e.g. `func_8008F228`: "a pinned early pointer is
  dead before an ordinary scalar which already receives the same saved register becomes live.
  RESOLVES: merge those disjoint roles into a pointer-sized scalar with explicit casts, remove only
  the pointer pin"; `func_800D1A48`: "share the real count/pointer lifetime, preserving the count's
  signed narrow interface"; `func_800C1C20`: "share that real scalar's storage with the pointer,
  then check that the reference-count increase raises its allocator rank".

  Three textual sub-forms:
    A1 the pinned local is dropped and an existing local of the SAME type takes its uses
       (`func_80084084`: the arm-local `register Entry *entry ASM_REG("$17")` renamed to the
       enclosing `entry_m`).
    A2 the donor has ANOTHER type, so every use is cast and often the donor is retyped as well
       (`func_80A1FBBC` `void *projectile_callback` -> `u16 frames_left` retyped `u32`;
       `func_800B8F90` `s32 selected_entity` -> `u8 spawn_type` retyped `s32`; `func_8008F228`
       `S_800E3E48 *entries` -> `s16 var_s1` retyped `u32`; `func_800D1A48` `s32 count_or_x` ->
       `u8 *quad`; `func_81984754` `u8 *allocation_data` -> `Object *prev_object`).
    A3 the two roles share one storage through an invented union (`func_800C1C20`:
       `union { u32 word; DungeonCoord *coord; } center;`).

  MEASURED (`T.eligible` + `donees()` on the base texts):
    - `t93_scopemerge` is ELIGIBLE on `func_80A1FBBC`, `func_80BC7BA8`, `func_80084084`,
      `func_8009CCC4`, `func_80BC1BA8` and lists the right donee, but every donor it offers has the
      donee's exact type and pointer depth, so the A2 rows have an EMPTY candidate menu.  Run
      through `gen_drive` on `func_80084084` (the pure A1 row!) the menu is empty too: the donor
      `entry_m` is a FUNCTION-level declaration and `donors()` only offers locals declared in an
      enclosing BLOCK of the donee, never the function's own top-level declarations
      (lane `work/native_lane/r72_h_t93_probe`, `nearest: []`).
    - On `func_800B8F90`, `func_8008F228` and `func_800D1A48` t93 refuses outright with
      "no pinned register declaration in a nested block": the pinned declaration is at FUNCTION
      level, which `donees()` does not collect.
    - On `func_81984754` it refuses "no enclosing local free over the block" - the only free
      enclosing local is `u8 *allocation_data`, a different type from `Object *prev_object`.
    - `func_80BC1BA8` reaches listing distance 6 with `state_compare->height_accum@101:erase`,
      i.e. the merge alone is not the whole row: it also needs move D below.
  -> t93 extension: function-level donees, function-level donors, and an integer/pointer donor of
     another type with a cast at every use and at the donor's declaration.

## B. The declared parameter width -- 24 pins / 5 rows

  `dungeon/func_80CBD000` 8 (`s8 _arg1, s8 arg2` -> `s16, s16`; ALL eight pins go),
  `func_8009612C` 5 (`s32 target_x, s32 target_y` -> `s16, s16`, five `ASM_USE2` sites),
  `func_80FB7000` 4 (`s8 pos_y` -> `s16`), `func_80FC3000` 4 (`s8 arg2` -> `s16`),
  `func_80E07054` 3 of 4 (`s32 arg2` -> `s16`, and the CALLEE prototype `func_800A48F0`'s third
  parameter with it).

  The lanes' rule (`func_80FB7000`): "APPEARS in the allocation-call twin family when jointly
  erasing argument colours/uses leaves only the saved third/fourth argument order.  RESOLVES by
  testing the stored-byte third parameter as a halfword interface and jointly removing that
  four-pin call group; update every declaration in the translation unit."  `func_80CBD000` adds
  "vary the actual incoming narrow modes separately from local/storage modes"; the mechanism is
  gcc 2.x `assign_parms` + PROMOTE_PROTOTYPES - a formal narrower than the mode it arrives in gets
  a real pseudo with an entry conversion, and the entry copies retail has stop needing a pin.

  MEASURED: `t36_paramwidth` is ELIGIBLE on `func_80CBD000`, `func_80FB7000` and `func_80FC3000`
  and refuses `func_80E07054` / `func_8009612C` with "no pinned copy of a narrow parameter"
  (their formals are all `s32`, and `NARROW` has no s32 entry - t36 only ever WIDENS).  On the
  three eligible rows the miss is the PIN PLAN and the parameter CHOICE:
    - `pairs()` on `func_80FB7000` returns `(saved_part_value, part_a_value)` and
      `(saved_x, pos_x)`; the parameter the lane changed is `pos_y`, which has no pinned copy, so
      no single-parameter candidate touches it and the group candidates (`narrow+1`) widen `pos_x`
      as well.
    - `build()` erases only the pins that NAME the copies, so the two `ASM_REG` declarations
      (`object_type`, `object_pool`) and the `ASM_USE_NV` group survive every candidate.
    - t36 has no listing screen: it sorts 24 candidates by remaining pin count and calls `vf` on
      each until one is exact.
  -> BUILT as `tools/xform/t98_paramcell.py` (every formal x every other integer width, in BOTH
     directions, x a joint whole-function pin plan, screened by the cc1 listing).

## C. The staged page value spelled as its symbol -- 12 pins / 5 rows

  `dungeon/func_80977E0C` 7 (six `effect_table = (u8 *)0x80170000; ASM_KEEP(...); effect_table +=
  0x40F8;` runs in six switch states, plus the `phase_flag` keep that falls with them),
  `func_800C40F0` 2 (of 6), `func_80285A70` 1, `func_8180A990` 1, `func_80285E80` 1.

  Lane rule (`func_80977E0C`): "Repeated pinned page constants feed one shared table local across a
  state dispatch, and named symbols alone allocate the high and low halves differently.  RESOLVES:
  use named symbols with separate per-state table lifetimes; where necessary duplicate an existing
  common tail into its existing predecessor arms."

  MEASURED (`work/native_lane/r72_h_t97_probe`):
    - `t92_pagerun.runs()` finds ALL SIX runs of `func_80977E0C` and t97 is eligible; its best
      candidate is at listing distance 2 (`run@8096:file+8:core`) after 108 listings.  The gap is
      not the spelling: states 1, 2 and 4 share one `effect_common` tail that READS `effect_table`,
      so three different symbols cannot flow into one tail - the lane duplicated that tail into
      each state and gave each state its own block-local.  Neither t92 nor t97 can duplicate a tail.
    - `func_80285A70` is refused by both ("no staged page run"): the seed
      `xor_page = (u8 *)0x80080000;` and the bias `xor_base = xor_page + 0x3160;` are separated by
      an unrelated statement (`entry_flags = state->flags;`), and `runs()`/`tails()` stop at the
      first statement that reads neither.
    - `func_8180A990` is refused for the same reason (the keep sits on ANOTHER variable between the
      seed and the bias, and the bias is 18 lines later, after a branch).
    - `func_80285E80` and `func_8008F228` ARE seen by `t97.tails()` but land at distance 48 and 24:
      their page local is a STRUCT pointer whose "bias" is a field access (`final_page->floor_146C`
      -> `D_8008146C[0]`), so respelling the seed alone leaves every use wrong.
  -> not closed this round; the honest next step is a tail-duplication plan, which is move #9's
     machinery applied to a page run.

## D. De-register at the same width, paired with an unpinned local's retype -- 9 pins / 5 rows

  `dungeon/func_80CBD2E0` 3 (of 7): `register s32 direction_copy ASM_REG("$21")` -> `s16
  direction_copy` and the unpinned `s32 direction_index` -> `s16`, with two keeps;
  `func_80BC1BA8` and `func_80BD9BA8` 2 each (of 5): `register s16 old_state ASM_REG("$16")` and
  `register u8 old_state_byte ASM_REG("$2")` de-registered AT THEIR OWN WIDTH while the unpinned
  `u32 height_bits` becomes `u16`; `func_80BC7BA8` 1 (`register u32 height_bits ASM_REG("$3")` ->
  plain, with the unpinned `s32 height_offset` -> `s16`); `func_8008F228` 1 (`s16 var_s1` -> `u32`).

  This is round 71's move F, which that round measured but did not build ("t37 verifies up to 40
  candidates per row with `vf` and has no listing screen").

  MEASURED: `t37_localwidth.candidates()` on `func_80CBD2E0` offers 20 single-local retypes
  (`direction:s32>s16`, `direction_copy:s32>u16`, ...) - every other width of every PINNED local,
  and nothing else: the same-width de-register is skipped by `continue` on `new == cur`, and the
  unpinned `direction_index` is not on `pinned_locals()`'s list at all, so the PAIR the row needs
  is not expressible.
  -> t37 extension: a `keep`/same-width plan, a second unpinned integer local retyped with the
     first, and a cc1 listing screen in front of `vf` so the bigger menu costs listings, not scores.

## E. Scalarised load/or/store written as one field expression -- 7 pins / 2 rows  (BUILT: t100_rmwfold)

  `dungeon/func_800C5028` 6: `actor_flags_14 = p->unk_14; actor_flags_1c = p->unk_1C;
  ASM_SCHED_BARRIER(); actor_flags_14 |= 0x2000; ... p->unk_14 = actor_flags_14;` ->
  `p->unk_14 |= 0x2000; p->unk_1C |= 0x2000;`, which drops two locals, the barrier, two
  `ASM_REG` declarations and two keeps together.  `func_80E07054` 1 (the same shape, two fields).
  Lane rule: "RESOLVES by writing direct field updates with fresh expression results and combining
  them with independently justified context/argument-role erasures."
  This is the INVERSE of the family t94_castsplit owns (r67 D, r71 D+E): there the row wanted one
  assignment split into two, here it wants three statements folded into one.  Built as a NEW
  generator rather than a t94 shape (`tools/xform/t100_rmwfold.py`): the detector is "N sibling
  load/op/store triples over distinct lvalues with a pin in or just above the run", the two forms
  are the full fold and the birth form (`V = LV op K;`, which is what func_80E07054 kept its store
  for), and the pin plans are the run's window, the pins naming the locals, and the whole function
  when it has at most eight.  Refused when a CALL sits between a load and its store - the generator
  cannot prove the callee does not touch that memory.

## F. The rest of the ranked table

  - **abs()** (4 pins, `func_80D6A4D8`): `tile_dx = tx; tile_dx -= sx; if (tile_dx < 0) tile_dx =
    -tile_dx;` twice -> `tile_dx = __builtin_abs(tx - sx);`.  `t96_absplace` IS eligible and its
    `plainif@161:fold` candidate reaches listing distance 2 (lane `work/native_lane/r72_h_t96_probe`)
    - it folds ONE site with the pins in that site's window, and this row needs BOTH sites plus two
    keeps (`target_tile`, `effect_flags`) and two `ASM_REG` declarations in one joint plan.
  - **join/tail duplicated into the arms** (4 pins, 3 rows): `func_80BBB094` 2 - the tail
    `partB->unk2C = (void *)slot2; ASM_KEEP(partB);` after a three-arm `if / else if / else` chain
    written into all three arms ("place that real store in each existing predecessor, allow late
    tail sharing to recover the join"); `func_80097F94` 1 (an assignment given to both arms, the
    `do { } while (0)` scope dropped); `func_81893474` 1 ("put each real result store in its arm").
    MEASURED: `t82_armsink` is eligible on both rows and produces an EMPTY candidate list - it only
    hoists a statement that already appears in every arm, or sinks a join LOCAL; the tail-copy
    direction is not on its menu (`work/native_lane/r72_h_t82_probe`).
  - **absolute memory operand** (4 pins, 3 rows): `func_81332EC0` 1, `func_80088FA0` 1,
    `func_8008557C` 2 - `ASM_SCHED_BARRIER(); if (D_80013714 & 8)` -> `if ((*(u16 *)0x80013714) & 8)`
    with the barrier erased.  Lane rule (`func_80088FA0`): "a listing-invisible scheduling barrier
    sits immediately before a known global load and its erasure changes a branch delay slot.
    RESOLVES: use the matching-width absolute memory operand so address expansion occurs after
    delay-slot selection".  Mechanism: as a `SYMBOL_REF` the address is a HIGH/LO_SUM pair the
    scheduler may split across the branch; as an integer constant address it is one `lw`-with-offset
    operand expanded after delay-slot selection.  NEW move, nothing in `tools/xform` spells an
    address that way (t29/t86/t77 all go the other way, address -> symbol).
  - **statement written after the call** (3 pins, 2 rows): `func_80A20A28` 2 (five setup statements
    sunk BELOW `func_800DBA90`), `func_813284E4` 1 (the initialisation moved to the join the two arms
    share).  `t71_updateaftercall` refuses both with "no movable update before a call" - the exact
    r67 gap: `UPDATE` matches `v++`, `v +/-= k` and `v = (T *)v +/- k` only.  t71 is not in this
    harvest's writable set.
  - **`static __inline__` helper** (2 pins, 2 rows): `func_819112CC` (`radial_coordinate(center,
    trig, radius)`), `func_813238E8` (`clamp_level(level)`), and one inside `func_8009612C`
    (`offset_tile`).  Unlike round 67's helpers these are used ONCE: the helper is not
    de-duplication but a narrow RETURN interface ("recover the clamp's narrow return interface").
  - **struct field retyped** (1 pin, `func_800C5448`): `s16 unk_96` replaced by a
    `union { struct { u16 pad; s16 ticks; } half; s32 word; }` so that one of the reads can be
    written `timer.word >> 16`.  Type invention inside a recovered struct; no generator edits
    struct definitions.

## G. Not built, with the measured reason

  - **Aggregate copy widened** (4 pins, `func_800C40F0`; 7 pins / 2 rows in round 71).  Four field
    loads and stores off a typed symbol become
    `*(ResultCopy *)((u8 *)entity + 0x54) = *(ResultCopy *)&D_80089430;` with an invented
    `typedef struct { u8 bytes[11]; } ResultCopy __attribute__((aligned(4)));`.  `t78_aggcopy`
    refuses "no scalarized copy run": its run detector needs loads and stores at EQUAL offsets of
    two objects, and here the source offsets are 0/4/8/0xA and the destination 0x54/0x58/0x5C/0x5E.
    The `#ifdef NON_MATCHING` arm the lane deleted is NOT a blocker - `unscored_text(base) ==
    unscored_text(out)` holds for this pair, so a generator could reproduce it.  Left unbuilt: the
    typedef name, the byte extent and the alignment attribute are three free parameters and the
    round's build budget went to the four moves above.
  - **The `static __inline__` helper** and **the struct-field union**: type/function invention,
    one or two rows each.
  - **The page-run tail duplication** (move C): needs move #9's machinery; the honest next step.

## H. One-offs (7 pins / 4 rows)

  - `func_8008557C` 3 (of 5): a constant recomputed in two stages instead of staged in a local
    (`requested_angle = ((u32)direction << 10) >> 1;`), and a nested call argument recovered
    (the staged `slot_target = f(...)` written back inside the call it feeds).
  - `func_81893474` 2 (of 4): the CALLEE prototype given back its third argument
    (`func_800A45D8(u16, u16)` -> `(s32, s32, s32)`, the call passing `target_z`) - the arity lever
    `t76_arity` owns, refused here because the call site has two arguments, not three.
  - `func_800971DC` 1: the sign test rewritten as a bit-mask test with explicit early-exit `goto`s.
  - `func_800D74DC` 1: `a = b + c` written `a = (u32)b - -(u32)c` so that `combine` recreates the
    PLUS operand order ("expressing unsigned addition as subtraction of the negated second input").

---

# BUILT (round 72 harvest, 2026-09-21)

| generator | move | exemplars reproduced (base text -> pins) | sweep: eligible / exact rows / pins |
|---|---|---|---|
| `tools/xform/t98_paramcell.py` (new) | B | 3/5 - `func_80CBD000` 8->0 (`all=s16:all`), `func_80FB7000` 7->3 and `func_80FC3000` 7->3 (`arg2=s16:callargs`); `func_80E07054` and `func_8009612C` also need moves E and #12 | 125 / **19** / **40** (lane `work/native_lane/r72_h_t98_paramcell`); the continuous lander took all 19 within the hour, and a re-sweep of the 106 rows left found nothing more - the shape's remaining population is spent |
| `tools/xform/t37_localwidth.py` (extended: a same-width de-register, a joint de-register of every pinned integer local, a paired UNPINNED local retyped with it, and the cc1 listing screen round 71 said it needed) | D | 1/3 - `func_80CBD2E0` 7->2 (`pair:all>keep+direction_index:s32>u16`, five of the lane's seven); `func_80BC1BA8` and `func_80BC7BA8` stay at listing distance 6 (their other pins need move A's callback merge) | 766 / 1 / 1 - `slus/w_80042900` 2->1, and that one through the BASE menu (`localwidth:saved_id:s32>s16`), not a KIT candidate (lane `work/native_lane/r72_h_t37_localwidth`) |
| `tools/xform/t93_scopemerge.py` (extended: the MIRROR direction - an unpinned nested declaration merged into a PINNED enclosing local - and an `erase-fn` plan over the donor's pins anywhere in the function) | A1 | 1/5 - `func_80084084` 7->6 (`entry->entry_m@89:erase-fn`); the four cross-type rows are still refused (see below) | 432 / 5 / 5, all five through the new `erase-fn` plan (lane `work/native_lane/r72_h_t93_scopemerge`) |
| `tools/xform/t82_armsink.py` (extended: the `dup` site - the statement after an exhaustive braced chain written into every arm) | #9 | 1/1 - `func_80BBB094` 9->7 | 282 / 4 / 4, all four `dup` (lane `work/native_lane/r72_h_t82_armsink`) |
| `tools/xform/t100_rmwfold.py` (new) | E | 2/2 - `func_800C5028` 7->6 and `func_80E07054` 7->6, both `rmw2@...:full:win` at listing distance 0.  The lane got 6 pins on `func_800C5028`; this generator's whole-function plan (`rmw2@108:full:fn`, all 7 pins) IS generated and sits at listing distance 21, because the other five pins need move A's role merges as well | 52 / 0 / 0 (lane `work/native_lane/r72_h_t100_rmwfold`) |
| `tools/xform/t99_absmem.py` (new) | #10 | 3/3 - `func_81332EC0` 7->6, `func_80088FA0` 7->6, `func_8008557C` (each read respelled with its own barrier) | 201 / 9 / 9 (lane `work/native_lane/r72_h_t99_absmem`) |

Tests: `tools/tests/test_t98_paramcell.py`, `test_t99_absmem.py`, `test_t100_rmwfold.py`,
`test_t37_kit_pairs.py`, `test_t82_kit_dup.py`; `test_t93_scopemerge.py` / `test_t93_kit_donees.py` unchanged and green.

Three measurements worth keeping:

  - `t37`'s sweep is the round's honest negative: 766 rows, 110 listings each, ONE exact, and that
    one from the menu t37 already had.  The move is real - it pays 5 pins on its own exemplar
    (`func_80CBD2E0` 7->2) - but the population left in the tree after eighty rounds does not carry
    it.  The screen also caps `vf` at 5 per row where the old t37 spent up to 40, so a candidate
    byte-exact at a listing distance above the two nearest is no longer reached: that is the trade
    that buys the bigger menu, and it is written into the generator's docstring.


  - every t82 win and every t93 win came from the NEW plan, not from a re-sweep of the old menu -
    `dup@...` on four rows and `erase-fn` on five.  The t93 mirror direction also fixed a latent
    `_decl` bug: `fall_duration = 0x10;` matched the declaration regex as type `fall_duratio` plus
    name `n`, which was harmless while only pinned declarations were donees.
  - t99's nine wins are all at cc1 listing distance 3, never 0: an absolute-address load is an
    assembler MACRO, so the listing differs textually from the `%hi`/`%lo` pair it assembles to.
    The generator therefore verifies the two nearest candidates as well as the listing-exact ones -
    on this move the screen ranks, it never proves.

Superseded lanes, do NOT land (their `out/` is emptied): `r72_h_t93_probe`, `r72_h_t96_probe`,
`r72_h_t97_probe`, `r72_h_t82_probe`, `r72_h_t98_check`, `r72_h_t93_check`, `r72_h_t82_check`,
`r72_h_t99_check`, `r72_h_t37_check`, `r72_h_t100_check`.

## What the six leave on the table

- `t98_paramcell` changes only the function's OWN declarations.  `func_80E07054` also needs the
  CALLEE prototype `func_800A48F0(void *, s32, s32)` narrowed to `s16` in its third parameter (the
  call passes the retyped formal), which is t76_arity's side of the call and not on this menu.
- `t93_scopemerge` still refuses every CROSS-TYPE donor (move A2, six rows this wave): an integer
  donee accepts an integer donor of another width, but an int<->pointer pair needs a cast at every
  use and at the donor's declaration, and a pointer donee still needs its donor's exact type.  The
  measured menu on those rows is EMPTY, not merely mis-ranked.  It also has no function-level
  donee: `func_800B8F90`, `func_8008F228` and `func_800D1A48` pin a declaration at the function's
  own top block, which is t87/t90 territory and needs a liveness test, not a block test.
- `t37_localwidth` pairs ONE unpinned local with the de-register; rows whose second local is itself
  pinned (`func_800D1A48`) or which need a third change are out of reach.
- `t82_armsink`'s `dup` refuses a call after the chain, a multi-line join statement and a chain
  without a final `else` - `func_81893474`'s arm-store form has a call, so it is not taken.
- `t100_rmwfold` refuses a CALL between a load and its store: it cannot prove the callee leaves
  that memory alone, so the folded form would not be the same program.  Its whole-function plan is
  capped at eight pins.
- `t99_absmem` respells one read per pin; `func_8008557C` needs both of its reads AND the two
  one-off moves of section H.
