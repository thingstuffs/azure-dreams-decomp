# Round 71 harvest: MOVE TABLE from the first KIT wave (2026-09-21)

Source: the 38 base/out pairs with fewer pin sites in `out/` across
`work/native_lane/r70_kit_astra1 .. r70_kit_astra8` (40 rows; `dungeon/func_800C4A80` and
`dungeon/func_800CA184` of astra7 produced no out text).  Total **78 pin sites removed**.
Pin counts are `pin_census.sites_of(base) - sites_of(out)`.

Ranked by occurrences x pins (= total pins freed by the move; rows as the tie-break).

| # | move | pins | rows | owner today | verdict |
|---|---|---|---|---|---|
| 1 | ABS idiom in the goto / if-else spelling, rewritten IN PLACE | 9 | 4 | t16_absidiom, t91_absfresh | detector gap -> BUILT t96_absplace |
| 2 | a local merged into an existing local of the function | 8 | 8 | t93_scopemerge, t87/t90 | mixed (see B) -> t93 detector extension |
| 3 | staged page run collapsed to a NEIGHBOUR symbol +/- offset | 8 | 4 | t92_pagerun | spelling gap -> BUILT t97_pagesym |
| 4 | `v = (s16)e;` expanded to the shift pair (inverse of t94's collapse) | 7 | 2 | t94_castsplit | detector gap -> t94 extension |
| 5 | an aggregate copy widened to swallow the trailing scalar copy | 7 | 2 | t78_aggcopy | NOT BUILT (2 rows, needs a wider Copy typedef / a typed symbol) |
| 6 | one assignment split into two statements (`v = A op B;`) | 5 | 5 | t94_castsplit | menu gap (constant-operand only) -> t94 extension |
| 7 | de-register AT THE SAME WIDTH, paired with an unpinned local's retype | 4 | 3 | t37_localwidth | menu gap -> t37 extension |
| 8 | the value staged through a fresh / another local instead of in place | 4 | 4 | t89_lifetimesplit, t91 | NOT BUILT (see H) |
| 9 | `register s32 zero ASM_REG("$0")` replaced by the literal | 3 | 3 | none | NOT BUILT (recurs from round 67 move I) |
| 10 | a run of UNRELATED keeps erased jointly, no C change at all | 2 | 1 | t2_pins / joint_scan | NOT BUILT (recurs from round 67 move I) |
| 11 | a staged register copy feeding two stores dropped | 2 | 1 | t42_sinkcopy | NOT BUILT (1 row) |
| 12 | the statements AFTER an if/else duplicated into BOTH arms | 1 | 1 | t82_armsink | NOT BUILT (1 row; round 67 move F recurs, without goto retargeting) |

Below the line: the redundant second `ASM_CLOBBER("hi")` of m2c's implicit-hi read group deleted
(3 sites, `dungeon/func_818B6AFC`); two declaration initialisers of one block swapped
(`dungeon/func_8008EE88`, 1 pin); a local retype paired with a statement reorder
(`dungeon/func_818F2800`, 1 pin); a `static __inline__` helper recovered
(`dungeon/func_81978428`, 1 pin - round 67 move G recurs).

---

## A. The abs idiom in the spellings t16 does not see -- 9 pins / 4 rows

  astra2 `dungeon/func_81912154` 2, astra5 `dungeon/func_818AAE60` 4 (five sites),
  astra5 `dungeon/func_818B1664` 2, astra6 `dungeon/func_818E6800` 1.

  Three spellings, all rewritten IN PLACE to `axis_dist = abs(axis_dist);`:

      (goto)     if (axis_delta >= 0) { goto store_end; }      astra2, astra5
                 axis_delta = 0 - axis_delta;
      store_end: ...
      (if/else)  if (delta_x < 0) { distance = delta_x;        astra6
                     ASM_KEEP_NV(distance); distance = -distance;
                 } else { distance = delta_x; }
      (fold)     target_x -= source_coord;                     astra5 818B1664
                 if (target_x < 0) { target_x = -target_x; }
                 work.distance[0] = target_x;
              -> work.distance[0] = abs(target_x - source_coord);

  The astra lanes' generator rule: "an m2c conditional negate - whatever branch spelling it wears -
  is gcc's `abssi2` insn; write it `abs()` and the barrier or keep that was holding the branch
  around the negate has nothing left to hold."

  MEASURED on the four base texts:
    - `t16_absidiom.idioms()` returns **0** on 81912154, 818AAE60 and 818E6800 (`eligible` refuses
      "no conditional-negate idiom"): its `IF_RE` only matches `if (t < 0) { d = -x; }` and it
      explicitly `continue`s on an `else` arm.  On 818B1664 it finds 1 idiom and is eligible - that
      row is a spelling miss (t16's in-place `target_x = abs(target_x);` leaves the subtraction as
      its own statement; the lane folded the producer into the call).
    - `t91_absfresh` DOES detect the goto spelling (`negates()`: 5 on 81912154, 6 on 818AAE60) but
      `sites()` keeps only the ones with a single producing assignment (1 of 5, 4 of 6) and its
      rewrite is by definition into a FRESH local; the lanes' exact texts are in place.  On 818B1664
      and 818E6800 it refuses "no conditional negate with a single producing assignment".
  The pins are POSITIONAL (`ASM_SCHED_BARRIER` above the idiom on 818AAE60/818B1664), not named on
  the negated variable, so t16's `names_var` pin plan would not reach them either.
  -> BUILT as `tools/xform/t96_absplace.py`

## B. A local merged into an existing local -- 8 pins / 8 rows

  B1 a NESTED-block declaration merged into an enclosing local:
     `dungeon/func_81905FD0` (`register S_func_81905FD0_2 *target_motion ASM_REG("$7")` ->
     `target_motion_m`), `dungeon/func_81008664` (`s32 fall_duration = 0x10;` + `ASM_KEEP_NV` ->
     the outer `fall_anim`), `dungeon/func_818D4E68` (`u8 *copy_dest` + `ASM_KEEP` -> the outer
     `s32 direction`, casts at the two uses), `dungeon/func_8180C3C0` (`u8 *scene_rgb` + `ASM_KEEP`
     -> the outer `s32 message_text`, casts at three uses).
  B2 two FUNCTION-level locals merged: `dungeon/func_80F36D0C` (`register u32 angle_bits
     ASM_REG("$6")` -> `zero_arg`), `dungeon/func_80D150D0` (`void *effect` and `register s32
     height_delta ASM_REG("$16")` -> one `s32 object_or_height`, `(void *)` at every use),
     `dungeon/func_81904990` (`u16 sprite_flags` -> `tpage_offset`),
     `dungeon/func_81850800` (`register s32 facing ASM_REG("$4")` -> `base_y`, SAME register).

  Generator rule from the lanes: "when two locals are never live at once, retail had one pseudo;
  give the second one the first one's name and the register pin it was carrying disappears."

  MEASURED:
    - 81905FD0 IS on `t93_scopemerge`'s menu: `donees()` lists `target_motion` (line 770) and
      `donors()` offers `['target_motion_m', 'owner_motion']`, so the pair
      `target_motion->target_motion_m@770` is offered.  With 8 donees and `MAX_VERIFY = 6` this is a
      RANKING miss, not a detector one.
    - B1's other three rows are NOT on t93's menu: `donees()` keeps only declarations carrying an
      `ASM_REG(...)` IN the declaration, so a plain `u8 *copy_dest;` / `s32 fall_duration = 0x10;`
      whose pin is a SEPARATE `ASM_KEEP`/`ASM_KEEP_NV` statement in the same block is never a donee;
      and `donors()` requires the donor's type and pointer depth to match exactly, which rules out
      the two rows that cast at the uses.
    - B2 is t87/t90 territory (function-level), and the two cross-type merges (80D150D0,
      818D4E68's outer form) are outside both: they rename by name at one type.
  -> t93 detector extension (plain declaration + a keep statement as the pin; donor tried at the
     donee's type, with the uses cast when the donor is wider).  The cross-type function-level
     merge (80D150D0) is left for t87.

## C. A staged page run collapsed to a NEIGHBOUR symbol +/- offset -- 8 pins / 4 rows

  astra4 `dungeon/func_800AFA68` 2 (two runs), astra7 `dungeon/func_818BDEBC` 2 (two runs),
  astra8 `dungeon/func_80A170DC` and `dungeon/func_80C1509C` 2 each (the cross-variable form).

      camera_state = (u8 *) 0x80070000;  ASM_KEEP_NV(camera_state);  camera_state -= 13008;
   -> camera_state = (u8 *)&D_8006CD10 + (32);            + `extern u8 D_8006CD10[];`

      (table_base) = 0x80070000; ASM_KEEP(table_base); (table_base) -= 0x3328;
   -> table_base = (s32)D_8006CCE8 - 0x10;                /* NOT (s32)D_8006CCD8 */
      (table_base) = 0x80070000; ASM_KEEP(table_base); (table_base) -= 0x3318;
   -> table_base = (s32)D_8006CCD8 + 0x10;                /* the two symbols SWAPPED */

      table_page = (u8 *)0x80150000; ASM_KEEP(table_page); table = table_page + 0x1168;
   -> table = D_80151168;                                 /* the tail assigns ANOTHER local */

  Generator rule: "the `%hi`/`%lo` pair names a symbol, not an address: spell the page value with
  the symbol whose relocation retail used, even when that is a neighbour of the address plus or
  minus a constant."

  MEASURED: `t92_pagerun` is ELIGIBLE on 800AFA68 and 818BDEBC and finds both runs on each
  (`runs()` -> two `camera_state` / two `table_base` runs); its candidate menu is
  `run@...:win / wide / wide+1 / var`, i.e. four PIN plans over ONE spelling.  That spelling comes
  from `t29_addrsym.sym_expr(text, addr, ...)`, which always names `D_%08X % addr` exactly - so a
  neighbour symbol plus an offset is not on the menu at all, and for 800AFA68 the invented
  `extern u8 D_8006CD30[];` names an address the symbol table has no symbol at.
  On 80A170DC/80C1509C t92 refuses "no staged page run": the bias step assigns a DIFFERENT local
  (`table = table_page + 0x1168;`), and `runs()` stops at the first statement that reads V without
  stepping it.
  -> BUILT as `tools/xform/t97_pagesym.py` (t92 is not in this harvest's writable set; the new
     generator imports `t92_pagerun.runs` and respells the seed).

## D. `v = (s16)e;` expanded to the shift pair -- 7 pins / 2 rows

  astra8 `dungeon/func_800AA49C` 6 (six sites, plus three de-registers that fall with them),
  astra7 `dungeon/func_80F90E88` 1.

      angle = (s16)angle;        ->  angle = (u32)angle << 16;  angle >>= 16;
      angle = (s16)next_angle;   ->  angle = (u32)next_angle << 16;  angle >>= 16;
      right_x = (s16) max_xy;    ->  half_width = (u32)max_xy << 16;  half_width >>= 16;   (80F90E88,
                                     into an EXISTING other local, whose later uses take over)

  Generator rule: "a narrowing cast is one gcc insn and coalesces with its source; written as the
  shift pair the intermediate is a second set of the pseudo, which is what retail's register
  colouring shows."  This is the EXPANSION direction of the shape round 67 built as t94's
  `merges()` (`v <<= 24; w = (s32)v >> 24;` -> `(u8)(v + 0)`), which the round-67 table listed as
  built - the inverse was not.

  MEASURED: `t94_castsplit.sites()` on 800AA49C returns exactly ONE site (`insource@180`); none of
  its four `splits()` shapes matches an assignment whose whole right-hand side is a cast of a NAME.
  -> t94 extension (`expand`), with a joint plan over every expansion site of the function and a
     pin plan that reaches the `register` declarations at the function top.

## E. One assignment split into two statements -- 5 pins / 5 rows

  astra1 `dungeon/func_807B0B3C` 1: `bucket_tag = (p->unk_B0 & tag_mask) | ((u32)prim & addr_mask);`
        -> `bucket_tag = p->unk_B0 & tag_mask; bucket_tag |= (u32)prim & addr_mask;`
  astra1 `dungeon/func_818CFB74` 1: the `<< 16` hoisted out of the store's right-hand side into the
        producer (`offset_x <<= 16; d->x4C = offset_x;`)
  astra4 `dungeon/func_818EC800` 2: `s32 packet_link = A | B; ASM_KEEP_NV(packet_link); *p =
        packet_link;` -> the two halves named separately, the high half through an existing local
  astra6 `dungeon/func_800969CC` 1: `step_distance = y_step * step_distance;`
        -> `y_step *= step_distance; step_distance = y_step;`
  astra3 `dungeon/func_818B6AFC` (part of 10): one `(s32)((u32)(a - b*2) << 16)` written as four
        statements over the same local.

  This is round 67's move D family, which t94 was built for; the menu gap is exact: `splits()`
  requires the second operand to be a CONSTANT (`_const(k)`), so `A | B` and `y_step * step_distance`
  over two locals are not offered.
  -> t94 extension (allow a call-free non-constant operand in the `insource` and two-op shapes).

## F. De-register at the same width, paired with an unpinned local's retype -- 4 pins / 3 rows

  astra2 `dungeon/func_800CDFD8` 1 (`register u16 height ASM_REG("$4")` -> `u16 height`, with the
     UNPINNED `s32 edge_y` -> `s16 edge_y`), astra6 `dungeon/func_8180E7F4` 2 (`register s32
     ability_id ASM_REG("$2") = ...; ASM_KEEP_NV(ability_id);` -> `s32 ability_id = ...;`, with the
     inner `s32 ability` -> `u8 ability`), astra5 `dungeon/func_818FF710` 1 (`register s32
     origin_tile ASM_REG("$3")` -> plain, with `s32 parent_tile` -> `s8 parent_tile`).

  MEASURED: `t37_localwidth.candidates()` on 800CDFD8 offers `height:u16>s32|s16|u8|s8` - every
  OTHER width - but never `height` at its own width (the loop `continue`s on `new == cur`), so
  "erase the register pin and change nothing else" is not a candidate; and `pinned_locals()` only
  ever considers locals a pin NAMES, so the second, unpinned local is never retyped.
  -> t37 extension (same-width de-register; a second unpinned integer local paired with it;
     a cc1 listing screen, which t37 has none of today).

## G. Not built, with the reason

  - **Aggregate copy widened** (7 pins / 2 rows).  `dungeon/func_802835B8`: `*(Copy12 *)(e+0x34) =
    *(Copy12 *)src; tail = *(s8 *)(src+12); e->unk_40 = tail;` -> `*(Copy13 *)(e+0x34) =
    *(Copy13 *)src;` needs a `Copy13` typedef that the row does not have until the lane writes one.
    `dungeon/func_8187C45C`: three `memcpy` calls off a page pointer -> `direction_steps =
    D_80024074;` needs the symbol declared at the struct's type.  Both are type INVENTION, which no
    bounded generator does; `t78_aggcopy` merges runs at equal offsets of two objects and is not
    close enough to extend.
  - **The zero register** (3 pins / 3 rows, round 67 move I recurs): `register s32 zero
    ASM_REG("$0")` used as a literal (`dx = zero;`, `state = zero + 1;`, `return (void *)zero;`).
    Only `dungeon/func_81850800` is the move alone; `dungeon/func_800969CC` pairs it with move E and
    `dungeon/func_81978428` replaces it with a recovered `static __inline__ u16 initial_count(u16)`
    (round 67 move G).  Cheap to build, ranked below the five that were.
  - **A run of unrelated keeps erased jointly** (2 pins, `dungeon/func_819B3414`): two
    `ASM_KEEP_NV` on two DIFFERENT variables in one straight-line run, no C change at all - the same
    pure joint-erasure miss round 67 recorded on `dungeon/func_81008664`.  t2/joint_scan group per
    variable, so a run-local group of unrelated keeps is still never offered.  RECURS: worth a
    joint-erasure pass keyed on the RUN, not the variable.
  - **The statements after an if/else duplicated into both arms** (1 pin,
    `dungeon/func_80DB9000`): round 67's move F without the goto retargeting, so it IS buildable as
    a `t82_armsink` extension (t82 hoists a statement present in every arm OUT; this is the inverse).
    One row here.
  - **A staged copy feeding two stores dropped** (2 pins, `dungeon/func_8009AE44`), **two
    declaration initialisers of a block swapped** (1 pin, `dungeon/func_8008EE88`), **the redundant
    second `ASM_CLOBBER("hi")`** (3 sites, `dungeon/func_818B6AFC`) and **the helper invention**
    (1 pin, `dungeon/func_81978428`): one row each.

## H. Which round-67 "unbuilt" moves recur here

  | round 67 | recurs? | where |
  |---|---|---|
  | A page run -> symbol (BUILT t92) | YES, in two new spellings | C above, 4 rows |
  | B local merge (BUILT t93) | YES | B above, 8 rows |
  | C field copy elided | no | - |
  | D3 sign-extension idiom | YES, in the EXPANSION direction | D above, 2 rows |
  | E statement moved across a call (t71 second pattern list) | no | no row moved a plain `v = expr;` across a call |
  | F join block duplicated into the arm | YES, in the easy form (both arms, no goto) | `dungeon/func_80DB9000` |
  | G `static __inline__` helper invention | YES | `dungeon/func_81978428` |
  | H single-arm hoist (t82 extension) | no | - |
  | I `zero` register as a literal | YES, x3 | G above |
  | I run of unrelated keeps erased jointly | YES | `dungeon/func_819B3414` |

  So of the round-67 "what remains unbuilt" list, **E and H did not recur** in this wave, while
  **F, G and both move-I one-offs did** - each still at one or two rows, which is why they stay
  unbuilt here too.

---

# BUILT (round 71 harvest, 2026-09-21)

| generator | move | exemplars reproduced (base text -> pins) | sweep: eligible / exact rows / pins |
|---|---|---|---|
| `tools/xform/t96_absplace.py` (new) | A | 4/4 - func_818AAE60 21->18, func_818B1664 21->19, func_81912154 30->26 (two MORE pins than the lane), func_818E6800 19->18 | 57 / 5 / 11 (lane `work/native_lane/r71_h_t96_absplace`) |
| `tools/xform/t97_pagesym.py` (new) | C | 2/4 - func_800AFA68 24->22 and func_818BDEBC 18->16 exact; func_80A170DC / func_80C1509C stay at listing distance 4 (their other four pins are three de-registers and an `ASM_KEEP` this generator does not touch) | first sweep 85 / 5 / 9; re-swept after a liveness fix and after the lander took those rows: 73 / 4 / 7 (lane `work/native_lane/r71_h_t97_pagesym`) |
| `tools/xform/t94_castsplit.py` (extended: shapes `expand` and `opsplit`, a per-LABEL joint group over the whole function, and the function-wide `allvar` / `regvar` pin plans) | D + E | 1/4 - func_800AA49C 17->15 (two of the lane's six); func_80F90E88 and func_800969CC reach listing distance 2 (each needs the paired de-register as well); func_807B0B3C is a MULTI-LINE assignment, which `ASSIGN` does not match | 520 / 8 / 11 (lane `work/native_lane/r71_h_t94_castsplit`) |
| `tools/xform/t93_scopemerge.py` (extended: a plain declaration pinned by a keep STATEMENT is a donee; an integer donee accepts an integer donor of another width) | B1 | 2/2 - func_81008664 24->23 (donor `world_coord`, not the lane's `fall_anim` - both byte-exact), func_81905FD0 24->23 (`target_motion->target_motion_m`, which the round-67 table called a ranking miss: it is exact on re-sweep) | 316 / 6 / 7 (lane `work/native_lane/r71_h_t93_scopemerge`) |

Totals: 23 exact rows, 36 pins, over 966 eligible rows (t97 counted at its re-sweep).  The
`t93`/`t94` counts are NOT a regression against round 67's 227/26/26 and 228/9/12: those rows are
landed, so this sweep is over what is left.  (`dungeon/func_818B1664`,
`dungeon/func_818C3B90` and `dungeon/func_81912154` are each staged by two of the four lanes; the
second landing of such a row sees a changed `base_sha` and skips it.)

Tests: `tools/tests/test_t96_absplace.py`, `test_t97_pagesym.py`, `test_t94_kit_shapes.py`,
`test_t93_kit_donees.py`; the existing `test_t94_castsplit.py` / `test_t93_scopemerge.py` are
unchanged and green (886 tests).

Superseded lanes, do NOT land (their `out/` is emptied): `r71_h_t92_probe`, `r71_h_t93_check`,
`r71_h_t93_probe`, `r71_h_t94_check`, `r71_h_t96_check`, `r71_h_t96_check2`, `r71_h_t96_check3`,
`r71_h_t97_check`, `r71_h_t97_check2`, `r71_h_t97_check3`.

## What the four generators still leave on the table

- `t96_absplace` deliberately takes only the IN-PLACE goto negate (`d == t == x`): m2c's
  `if (a >= 0) goto L; b = 0 - a; L:` into a DIFFERENT destination is not an absolute value unless a
  copy `b = a;` precedes it, and the round-71 rule is strict rather than clever.
- `t97_pagesym` invents the neighbour symbol at `addr - K` for K in {4, 8, 0x10, 0x20, 0x40, 0x100}
  and takes the file's own symbols within 0x400.  The winning K is not predictable from the text -
  on `dungeon/func_800AFA68` K = 0x10 was exact and on `func_818BDEBC` the file's OWN neighbour
  (-0x10) was, so the menu is a small search, not a rule.  Its cross-variable tail refuses a seed
  local that is READ again before it is next assigned (the edit deletes the seed store, so such a
  rewrite would leave a use of an uninitialised value even where the bytes matched).
- `t94_castsplit`'s `ASSIGN` is a single-LINE regex, so m2c's wrapped right-hand sides
  (`dungeon/func_807B0B3C`) are invisible to every shape it has.  Its function-wide pin plans reach
  the `register` declarations but not the keeps on a local that the rewritten lines never name
  (`angle_step` in `dungeon/func_800AA49C`), which is why that row pays 2 of 6.
- `t93_scopemerge` still refuses an int<->pointer donor pair (`dungeon/func_818D4E68`,
  `func_8180C3C0`): those need a cast at every use and an assignment-side cast, which is a different
  rewrite from the rename this generator does.
- MOVE F (`t37_localwidth`: de-register at the same width paired with an unpinned local's retype)
  was measured but NOT built: t37 verifies up to 40 candidates per row with `vf` and has no listing
  screen, so multiplying its menu by a second local would put the sweep far outside a round's
  budget.  It needs the screen first.
