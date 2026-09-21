# Round 67 harvest: MOVE TABLE from the duck-briefed big-row lanes (2026-09-21)

Source: 34 base/out pairs with fewer pin sites in out/ across
work/native_lane/r63_astra_big{2,3,5,6,7,8,10} and r66_sol_big{1,2,3,4,5,6,7,9,10,11}.
Total 89 pin sites removed.  (r63_astra_big4/big9, r66_sol_big8/big12 produced no out text.)
Ranked by occurrences x pins.

## A. Staged page-address run collapsed to the symbol at the final address  -- 10 pins / 8 runs / 5 rows
   `V = 0x80070000; ASM_KEEP(V); V -= 0x3328;`  ->  `V = (s32)D_8006CCD8;`
   rows: 818C3B90 (2 runs/3 pins, incl. a joint ASM_KEEP on the consumer), 818BDEBC (2/2),
         81912154 (2/2, in a `#else` arm), 8180E7F4 (1/3, `u32 dead_base = 0x800E0000;` decl-init,
         non-contiguous run, third pin on the intervening `dead_index`), 819ADDB8 (1/1, `#else` arm).
   SHOULD HAVE BEEN FOUND BY t29_addrsym / t54_pagebase.  Measured refusals:
     - t29 `candidates()` returns {'table_work': 'modified'} on 818C3B90: V is re-staged to a SECOND
       symbol later in the function, and t29 substitutes every use with ONE symbol, so it bails.
     - t54's only move that drops the offset step is `cursor_candidates`, which refuses (a) any
       function containing `goto` or a label - all five rows are m2c goto soup, (b) ptr!=1 (integer
       page locals `s32 table_work`, `u32 dead_base`), (c) more than one definition of V.
       t54's `anchor:` candidates keep the page value and only respell it, leaving the `-= 0x3328`.
     - t29 additionally refuses the two `#ifdef NON_MATCHING / #else <staged>` rows with `port-arm`
       (and the lanes' own out texts delete the `#ifdef`, which gen_drive's vf rejects because
       `unscored_text` changes).  The repair: rewrite the `#else` arm only.
   -> BUILT as tools/xform/t92_pagerun.py

## B. Register-pinned local merged into an existing local of the function  -- ~20 pins / 10 rows
   B1 inner block-scoped `register T v ASM_REG("$n")` replaced by an existing ENCLOSING local:
      8180C3C0 7 pins (four same-named `register s32 object_index ASM_REG("$17") = 0` blocks ->
      the outer `object_index_m`, three `register void *object ASM_REG("$16")` -> `object_m`),
      80DB9000 1 (`register u32 uv_adjusted ASM_REG("$2")` -> `coord_value`),
      81850800 1 (`register s32 pixel_offset ASM_REG("$3")` -> `state`),
      80AEF12C 1 (inner `register u32 pixel_ot_tag ASM_REG("$3")` hoisted over the outer `u32 color`),
      8197192C 3 (`outer_point`->`position`, `init_obj_m` dropped, `light_copy_m` dropped),
      800AFA68 2 (`shadow_rotation`->`transform_dst`, `shadow_matrix_arg`->`world_matrix_arg`).
   B2 two function-level locals merged: 80084340 1 (`actor_or_result`($17) -> `linked_actor`),
      800AFA68 1 (`initial_pitch`($3) -> `sprite_yaw`).
   B3 bare de-register, nothing else: 8009AE44 1 (`register volatile s32 y_result ASM_REG("$3")`
      -> `s32 y_result` - the `volatile` goes too), 800AFA68 1 (`sprite_corner_y`),
      8191CD78 1 (`floor_limit` $6, with an unrelated ASM_CLOBBER("$6") left standing),
      80A473B8 1 (`height_limit` $2, with move D below).
   SHOULD HAVE BEEN FOUND BY t87_lifetimemerge / t90_lifetimemerge_far.  Measured:
     - B2 IS on t90's menu (`far-rename:actor_or_result->linked_actor@358` for 80084340) - a
       ranking/MAX_VERIFY miss, not a detector miss.
     - B1 is NOT on either menu on any of the four rows checked: t87/t90 pair declarations found by
       natural._functions, and an inner-block decl with an initialiser (`register s32 object_index
       ASM_REG("$17") = 0;`) repeated under the SAME NAME in four sibling blocks is not offered;
       any rename-by-name rewrite would also corrupt the other three blocks.
   -> BUILT as tools/xform/t93_scopemerge.py (keys the donor by DECLARATION SPAN, not name)

## C. A staged copy of a value that is already in a struct field, elided  -- 12 pins / 3 runs / 1 row
   8197192C: `light_saved = light_color; ASM_KEEP(light_saved); ... d->unk_0C = light_saved;` and
   `dark_left = d->unk_24; d->unk_14 = dark_left;` -> `d->unk_0C = d->unk_1C;` etc.  Three identical
   blocks in one function, 4 pins each.  No generator covers "read the field back instead of keeping
   a local copy"; t78_aggcopy is the nearest (it merges a load/store RUN into one aggregate
   assignment) but it requires the loads and stores to be at the SAME offsets of two objects; here
   source and destination are different offsets of the SAME object.  NOT BUILT (one row).

## D. A compound assignment split into two statements over the same local  -- 9 pins / 10 sites / 4 rows
   D1 cast after arithmetic: `v = f() & 0xF; ASM_KEEP(v); v = (s16)(v - 8);`
      -> `v -= 8; v = (s16)v;`  -- 8181B3E8, 5 sites / 5 pins.
   D2 bias-then-shift: `t = (t + 0x100) >> 8;` -> `t += 0x100; t >>= 8;` -- 8180C3C0 (1 pin),
      810332A4 (`coord_base = collision_coord + 0x20;` -> `collision_coord += 0x20;
      coord_base = collision_coord;`, 2 pins), 80A473B8 (`height_limit = height_offset <
      ground_offset - 0x20;` -> three statements, 1 pin).
   D3 sign-extension idiom collapsed (the shape earlier harvests named unbuilt - IT RECURS):
      80A473B8 `global_flags <<= 24; ASM_KEEP(actor_context); state_index = (s32)global_flags >> 24;`
      -> `state_index = (s8)(global_flags + 0);` (1 pin).
   D4 signed `/2` written back OUT as gcc's expansion (the inverse of t17_divpow2):
      80097C50 `map_index = tile / 2;` -> `map_index = tile + ((u32)tile >> 31); map_index >>= 1;`
      2 sites / 2 pins.
   No generator does statement splitting: t35_shiftspell flips one scale spelling in place, t17
   folds the idiom INTO a `/`, t39 is the sign-bit test.  The whole family is "one assignment ->
   two, so the intermediate gets its own pseudo".
   -> BUILT as tools/xform/t94_castsplit.py

## E. A statement moved across a call  -- 4 pins / 4 rows
   800BFE94 `ASM_KEEP(packet_code); packet_code += 0xC;` before a call -> the update sunk BELOW the
   call; 80FB5398 `vertex_bytes = ((u8 *)vertex_base) + 24;` sunk below `func_800DBA90`
   (ASM_KEEP_MEM_NV); 8191CD78 `index = 1;` sunk below `func_800BCB04`; 818CFB74
   `coord_or_variant = (s16)state->variant7E;` HOISTED above a staged-address run.
   t71_updateaftercall is the owner.  Measured: t71 is `eligible` on 800BFE94 but its candidate menu
   never produces the sink (see the t71 note below); on 80FB5398 it refuses outright with
   `no movable update before a call` because the statement is a plain assignment from another local
   (`v = expr;`), not `v += k / v++ / v = (T *)v + k`.
   -> t71 detector extension (widen the movable-statement form to a single-assignment
      `v = <expr>;` whose RHS the call does not name, and accept ASM_KEEP_MEM/ASM_KEEP_MEM_NV pins)

## F. A join block duplicated into the arm so the goto join disappears  -- 6 pins / 2 rows
   800C9858 (5 ASM_SCHED_BARRIER), 800CDFD8 (1): `... goto y_join;` ... `y_join: A; B;` ->
   the arm gets its own copy of `A; B;` and jumps past them.  In 800C9858 the two block-locals
   `s16 edge_coord` are also widened to `s32` (t37_localwidth's move, but t37 only retypes; it never
   duplicates the join).  t82_armsink is the nearest owner: it hoists a statement written in EVERY
   arm out of the branch, and sinks a join local into the arms - it has no "duplicate the join tail
   into one arm and retarget the goto" candidate.  NOT BUILT (2 rows, needs goto retargeting).

## G. A recovered `static __inline__` helper  -- 6 pins / 4 rows
   8197C800 (2 pins, `jitter_coordinate_64`), 8188C800 (2, `align_effect_coord`, applied twice),
   81941338 (1, `particle_alpha_from_random`), 819ADDB8 (1, `read_y_offset`).
   Each helper is a 1-3 statement body used two or more times in the row; inlining it gives the
   callee-side pseudo structure retail has.  No generator invents a helper.  NOT BUILT: the search
   space is the set of repeated statement runs in a function; worth a lane, not a bounded generator.
   Note 8197C800's helper body is just the `%` idiom (`random % 64`), which t19_modpow2 should be
   able to fold; t19 was not the miss here because the pins freed were on `position`, not on the
   modulo temporaries.

## H. A declaration or assignment hoisted out of an if arm to before the branch  -- 5 pins / 4 rows
   8197192C x2 (`u8 *effect_data = (u8 *)effect_obj + 0x20;` hoisted above `if (effect_obj != 0)`),
   80CE8564 (`kind_or_position = (s32)position;` hoisted above the `if`), 800AA49C (two sibling
   blocks each declaring `s16 coord;` -> one declaration at function top), 8188C800 (`s32 height =
   ...` folded into its declaration).  t82_armsink hoists only a statement present in EVERY arm of a
   chain; a single-arm hoist is not on its menu.  NOT BUILT (would be a t82 extension).

## I. One-offs (1-2 pins each, all single rows)
   - 81008664: three `ASM_KEEP_NV` on three DIFFERENT variables in one straight-line run erased
     together, no C change at all (3 pins) - a pure joint-erasure miss; joint_scan/t2's groups are
     per-variable, so a run-local group of unrelated keeps is never offered.
   - 809548E4: `transition_timer = phase_value; ASM_KEEP(...)` -> re-read the field
     (`transition_timer = ((S *)game)->unk_2E.s;`) instead of copying the local (1 pin).
   - 818CF0E8 x2: `p->unk_1A = f() & 0xFFF; ASM_SCHED_BARRIER();` -> route the call result through
     an existing local first (`hi = f() & 0xFFF; p->unk_1A = hi;`) (2 pins).
   - 800969CC: `register s32 zero ASM_REG("$0")` used as a literal zero -> `return NULL;` (1 pin).
   - 819611CC: `__attribute__((noreturn))` dropped from an extern prototype -> ASM_SET(zero) freed
     (1 pin).  A declaration ATTRIBUTE as a pin lever; nothing looks at attributes today.
   - 8182C800: a loop accumulator staged through a second local (`step_sum = distance_sum +
     step_index; do { step_index++; step_sum += step_index; } while(...); distance_sum = step_sum -
     step_index;`) written as the direct accumulation (2 pins).
   - 80AEF12C: a copy feeding a call argument dropped (`green = zero_arg; ASM_KEEP(green);` ->
     pass `zero_arg` at the call) (1 pin).

# BUILT (round 67 harvest, 2026-09-21)

| generator | move | exemplars reproduced | sweep (eligible / exact rows / pins) |
|---|---|---|---|
| tools/xform/t92_pagerun.py    | A | 4/5 (818C3B90 18->15, 818BDEBC 21->18, 81912154 34->32, 8180E7F4 24->21; 819ADDB8 misses - that row also needs the inline helper of move G) | 28 / 1 / 2 (lane r67_h_t92_pagerun2) |
| tools/xform/t93_scopemerge.py | B1 | 2/2 (8180C3C0 30->28 via the joint x2 merge, 80DB9000 30->29) | 227 / 26 / 26 (lane r67_h_t93_scopemerge2) |
| tools/xform/t94_castsplit.py  | D | 4/4 (8181B3E8 20->15 all five sites, 80097C50 13->11 jointly, 810332A4 15->13, 80A473B8 17->16 sign-extension) | 228 / 9 / 12 (LAND FROM lane r67_h_t94_castsplit2) |

Lanes: work/native_lane/r67_h_t92_check, r67_h_t92_pagerun, r67_h_t93_check, r67_h_t93_scopemerge,
r67_h_t94_check, r67_h_t94_check2, r67_h_t94_castsplit, r67_h_t94_castsplit2.
Tests: tools/tests/test_t92_pagerun.py, test_t93_scopemerge.py, test_t94_castsplit.py (800 tests green).

# NOT BUILT, with the reason

- MOVE E (statement across a call, 4 rows/4 pins) - t71_updateaftercall's detector gap is exact and
  small: `UPDATE` only matches `v++`, `v +/-= k` and `v = (T *)v +/- k`, so a plain `v = <expr>;`
  (`vertex_bytes = ((u8 *)vertex_base) + 24;`, `index = 1;`) is not a movable statement and the row
  refuses `no movable update before a call` (measured on func_80FB5398 and func_8191CD78).  On
  func_800BFE94 t71 DOES see the site and the right update (`sites_in` returns the call at line 358
  with `packet_code += 0xC`), so that row is a vf/erasure-group miss, not a detector one.  NOT DONE
  because adding patterns to `UPDATE` changes the site list of EVERY row (`sites_in(text)[-8:]`),
  which can displace sites that already pay; the safe shape is a SECOND pattern list used only for
  calls that have no classic update, with its own site budget.
- MOVE C (12 pins in one row), F (join duplication + goto retargeting), G (inline helper), H
  (single-arm hoist) and the one-offs: see the table above - each is one or two rows, or needs a
  search space a bounded generator does not have.

# Sweep ceilings measured after two plan additions (2026-09-21)

- t92 `wide+1` (window pins plus the nearest pin outside it) added NOTHING: 28 eligible / 1 exact
  both before and after.  The 27 misses sit at listing distance 1-4 from the pinned listing, so they
  need another C change beside the symbol, not another pin erasure.  28 rows is the whole remaining
  population of the shape in the tree - t29/t54 have already taken the rest over earlier rounds.
- t93 cross-name joint per donor (`all->object_m@x3`) added NOTHING on func_8180C3C0: the further
  merges in that row (`source_object`/`object`/`child` -> `object_m`) are not listing-exact on their
  own, because the lane paired them with other moves.  t93 stays at 227 / 26 / 26.
- Superseded lanes (do NOT land): r67_h_t92_pagerun, r67_h_t93_scopemerge, r67_h_t94_castsplit,
  r67_h_t94_check, r67_h_t92_check, r67_h_t93_check.
