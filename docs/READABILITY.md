# Readability census

Baseline: `ee0067601`; schema: `readability-v2`. 6,257 physical `.c`/`.h` files under `src/`, 8,252 definitions, 16,741,477 bytes; 0 delimiter warnings.

Scores describe visible source debt and review candidates. They do not establish correctness, shared layout equivalence, removable casts, or safe matching-C rewrites. No source files are changed. Function identity remains relative path, symbol, occurrence, and a token-normalized SHA-256 anchor. Comments, directives (including macro definitions), and quoted contents never create detector hits. Both conditional branches are counted textually. Includes are not expanded.

## Legacy measurements

The five v1 category scores, definitions and weights are unchanged in v2. `v1_score` is their original sum on the same function. `--schema v1` uses the frozen implementation and ignores the registry, emitting the original columns, queues, trend and methodology.

| Measure | Definition | Score |
| --- | --- | ---: |
| Byte offsets | Spelled byte-pointer cast (`u8 *`, `s8 *`, `char *`, `int8_t *`, `uint8_t *`) followed by one operand and addition/subtraction of a numeric literal; includes `(u8 *)p + 0x24` and `((u8 *)p) - 0x20` | 8 each |
| Pointer casts | Explicit pointer casts in bodies, including initializers and abstract function-pointer casts; declarations and `sizeof(type *)` excluded | 3 each |
| M2C macros | Identifier occurrences beginning `M2C_`, in signature/body | 12 each |
| Gotos | `goto` keyword occurrences | 8 each |
| Address names | Self named `func_`, `D_`, `unk_`; signature/body identifier uses with those prefixes, including unknown offset fields | 5 self; 2 per use |
| Temporary names | Exact `arg` + digits, `var_...`, `temp_...`, or `sp` + hex digits; occurrences, including declarations/parameters; unique count also exported | 1 per use |
| Magic literals | Numeric occurrences in assignment RHS or comparison operands, including nested expressions; overlaps counted once; 0 and +/-1 (including suffixes/floats) excluded | 2 each |
| Nesting | Maximum brace depth inside the function, outer body excluded | 4 per level above 2 |
| Length | Physical lines, token-bearing lines, token count; only token-bearing lines scored | 2 per started block of 40 lines after the first 40 |

The v1 score is the sum of these five category scores. `offsets` and `casts` use their own weights; `names` combines address and temporary names; `magic` counts magic literals; `structure` combines M2C, gotos, nesting and length. Overlap between categories is intentional: an offset cast with a literal can contribute to three categories. Brace nesting includes local structs and initializer lists, and does not measure unbraced control nesting. Magic detection is syntactic: constants in local named initializers are included, standalone return values, case labels, array bounds on the left of assignments and standalone call arguments are excluded. No semantic naming recommendation follows from these counts.


## Added measurements

| Category | Units and boundary | Weight |
| --- | --- | ---: |
| offset_macros | Literal offset argument in F(owner,type,offset), U8/S8/S16/U16/U32/S32(owner,offset), U8/S8/S16/U16/U32/S32_AT(owner,offset), PTR(owner,offset). Exact macro spellings/arity live in the registry. Nested owner expressions and signed/grouped integer offsets allowed; dynamic offsets excluded. | 8/access |
| byte_views | Spelled byte-pointer cast of an address-of member expression, including `(u8 *)&x->unk_10 + 1`. Count once per cast even without arithmetic. | 8/view |
| fixed_addresses | Spelled pointer cast whose operand is an integer other than 0 or +/-1. `0x1F800000..0x1F8003FF` is labeled scratchpad in evidence; other integers are fixed-address candidates (may include sentinels). Dereference is not required. | 8/cast |
| local_types | Placeholder struct typedef candidates named Entity, Actor, Rec or Rec_*, S_[func_]8hex_suffix with a pad*/unk* member. Forward typedef + tag definitions included. One unit per definition per function spelling its type in signature/body, including block-local types. Declarations/fields only, never quoted text, trigger membership. | 12/type user |
| sign_extension | `(... << 16) >> 16` or adjacent `x = expr << 16; x >>= 16;` (also <<=), decimal/hex/suffixed shifts accepted. Counts spelling, not inferred signedness. | 3/idiom |
| wrappers | Body-spelled `do { ... } while (0)` with a constant integer zero condition. Macro definitions are excluded by the lexer. | 3/wrapper |
| double_casts | Adjacent signed 32-bit then signed 16-bit scalar casts: `(s32)(s16)`, int32_t/int16_t and built-in signed int/short equivalents. Other scalar cast chains excluded. | 3/chain |
| duplicates | Exact token-normalized sequences of >=8 substantive physical body lines, within or across functions/files. Brace-only/comment/blank lines excluded; declarations/control lines included; literal values and identifiers retained. Earliest (function key, line index) copy is canonical. Same-function seed windows must not overlap. Score the union of later-copy lines once, including overlapping seeds. Adjacent covered lines merge into evidence ranges; a range may have several references in duplicates.tsv. This detects copy candidates, including conditional/overlay copies, without asserting that extraction is safe or runtime code is duplicated. Formatting across physical lines or renamed locals can prevent detection. | 2/redundant code line |
| hex_states | Direct hex integer assignment/comparison with an identifier segment state, timer or countdown (snake_case/camelCase, case insensitive). State and timer units exported separately; 0/1 included here. Arithmetic expressions, bitmask operations, decimal values, case labels, unnamed fields, and semantic aliases excluded. A hex literal is not judged wrong. | 2/literal |

Total v2 debt is the sum of all category scores. Cross-category overlap is intentional: a member byte view can already be a v1 byte offset, and a hex state can already be a magic literal. Added debt is `score - v1_score`, not a v1 trend delta. Each detector hit carries pattern id, source line span, units and a diagnostic in `oddities.tsv`. `local_types.tsv` inventories candidates including those without direct function users; unreferenced types contribute no function score. A lexical candidate does not prove it duplicates a shared type; an owner must check include/ layouts. This snapshot has 5,174 type definitions, 129 without direct function users.

## Oddities registry

`ledger/readability_oddities.jsonl` is loaded automatically in v2. One JSON object per pattern requires id, category, metric, positive integer weight, example, why, owner_decision (string or null), and exactly one detector or regex. Built-in detector names are an allowlist; invalid/duplicate ids, reserved v1 names, unknown options, inconsistent metric weights and empty-match regexes fail the run. A regex is applied to space-separated body tokens with quoted literals replaced by `<literal>`. Append a regex entry to add a category/metric and queue without editing Python; structural patterns use a tested allowlisted detector. There is no eval or dynamic import from registry data. Review regexes for runtime cost. Changing the registry changes the metric: retain its SHA-256 with every trend and compare only identical schema/registry/weights.

| Pattern | Detector | Category / metric | Owner decision |
| --- | --- | --- | --- |
| offset_f | `offset_macro` | offset_macros / macro_offsets | pending |
| offset_integer | `offset_macro` | offset_macros / macro_offsets | pending |
| offset_at | `offset_macro` | offset_macros / macro_offsets | pending |
| offset_ptr | `offset_macro` | offset_macros / macro_offsets | pending |
| member_byte_view | `member_byte_view` | byte_views / member_byte_views | pending |
| fixed_address | `fixed_address_cast` | fixed_addresses / fixed_address_casts | pending |
| local_placeholder | `local_placeholder_type` | local_types / local_type_users | 61, 73, 74, 75: inspect shared ownership and ActorRecord/PlayerRecord before naming or merging. |
| shift_narrowing | `sign_extension` | sign_extension / sign_extension_idioms | pending |
| one_trip_wrapper | `do_while_zero` | wrappers / do_while_wrappers | pending |
| wide_narrow_cast | `double_scalar_cast` | double_casts / double_scalar_casts | pending |
| copied_sequence | `repeated_lines` | duplicates / duplicate_lines | pending |
| hex_state | `hex_named_literal` | hex_states / hex_state_literals | pending |
| hex_timer | `hex_named_literal` | hex_states / hex_timer_literals | pending |

## Per-category totals

| Category | Units | Weighted debt | Functions |
| --- | ---: | ---: | ---: |
| offsets | mixed v1 measures | 96,368 | 2,553 |
| casts | mixed v1 measures | 236,382 | 4,927 |
| names | mixed v1 measures | 161,720 | 5,766 |
| magic | mixed v1 measures | 138,214 | 5,592 |
| structure | mixed v1 measures | 26,606 | 2,439 |
| byte_views | 499 | 3,992 | 230 |
| double_casts | 66 | 198 | 34 |
| duplicates | 17398 | 34,796 | 602 |
| fixed_addresses | 1044 | 8,352 | 574 |
| hex_states | 252 | 504 | 135 |
| local_types | 5049 | 60,588 | 2,017 |
| offset_macros | 4221 | 33,768 | 72 |
| sign_extension | 125 | 375 | 67 |
| wrappers | 132 | 396 | 107 |

Total: **802,259**; original v1 debt: **659,290**; added categories: **142,969**. `pattern_totals.tsv` separates individual registry patterns and units.

## Per-subsystem totals

| Subsystem | Files | Definitions | offsets | casts | names | magic | structure | byte_views | double_casts | duplicates | fixed_addresses | hex_states | local_types | offset_macros | sign_extension | wrappers | Total |
| --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: |
| dungeon | 2,170 | 3,391 | 72,104 | 188,049 | 123,671 | 103,650 | 20,614 | 3,832 | 135 | 31,662 | 4,872 | 288 | 40,080 | 25,512 | 327 | 183 | 614,979 |
| engine | 816 | 881 | 2,728 | 6,504 | 2,465 | 8,342 | 1,658 | 64 | 12 | 466 | 768 | 26 | 3,996 | 4,832 | 21 | 63 | 31,945 |
| frontend | 368 | 404 | 4,248 | 6,345 | 3,365 | 3,042 | 440 | 0 | 0 | 0 | 776 | 0 | 3,228 | 0 | 0 | 18 | 21,462 |
| main | 41 | 40 | 24 | 264 | 104 | 150 | 42 | 0 | 0 | 0 | 8 | 0 | 12 | 0 | 0 | 0 | 604 |
| movie | 1 | 17 | 0 | 93 | 26 | 84 | 10 | 0 | 0 | 16 | 0 | 6 | 96 | 0 | 0 | 0 | 331 |
| ovmovie | 4 | 12 | 64 | 120 | 68 | 140 | 22 | 0 | 0 | 34 | 16 | 0 | 0 | 0 | 0 | 0 | 464 |
| slus | 44 | 221 | 176 | 270 | 190 | 712 | 166 | 0 | 0 | 156 | 48 | 4 | 84 | 0 | 0 | 3 | 1,809 |
| town | 2,813 | 3,286 | 17,024 | 34,737 | 31,831 | 22,094 | 3,654 | 96 | 51 | 2,462 | 1,864 | 180 | 13,092 | 3,424 | 27 | 129 | 130,665 |

Subsystems/files/folders sum every metric except max_nesting (maximum). Local type counts sum type users; duplicate lines sum redundant-copy coverage.

## Thirty worst functions v1 rated tidy

Operational definition: v1 score <= 100, >= 80 code lines, positive added debt; rank by v2 score, then added debt, then function key. These absolute cutoffs and the eligible count are explicit; the score is not divided by length. Override with --tidy-max-score and --tidy-min-lines. `tidy_misses.tsv` exports the same list.

| Rank | Function | Source | Lines | v1 | v2 | Added |
| ---: | --- | --- | ---: | ---: | ---: | ---: |
| 1 | `slide_actor_along_facing` (#1) | [src/dungeon/actor/slide_actor_along_facing.c:48](../src/dungeon/actor/slide_actor_along_facing.c#L48) | 82 | 78 | 208 | 130 |
| 2 | `slide_actor_along_facing_second` (#1) | [src/dungeon/actor/slide_actor_along_facing_second.c:48](../src/dungeon/actor/slide_actor_along_facing_second.c#L48) | 82 | 78 | 208 | 130 |
| 3 | `slide_actor_along_facing_third` (#1) | [src/dungeon/actor/slide_actor_along_facing_third.c:48](../src/dungeon/actor/slide_actor_along_facing_third.c#L48) | 82 | 78 | 208 | 130 |
| 4 | `finish_timed_actor_movement` (#1) | [src/dungeon/monster/metal/finish_timed_actor_movement.c:66](../src/dungeon/monster/metal/finish_timed_actor_movement.c#L66) | 94 | 82 | 208 | 126 |
| 5 | `handle_catalog_detail_input` (#1) | [src/town/menu/input/handle_catalog_detail_input.c:40](../src/town/menu/input/handle_catalog_detail_input.c#L40) | 167 | 94 | 196 | 102 |
| 6 | `flatten_floor_terrain` (#1) | [src/dungeon/item/flatten_floor_terrain.c:35](../src/dungeon/item/flatten_floor_terrain.c#L35) | 85 | 100 | 196 | 96 |
| 7 | `CheckBuildBuildingLand` (#1) | [src/town/map/check_build_building_land.c:32](../src/town/map/check_build_building_land.c#L32) | 110 | 88 | 164 | 76 |
| 8 | `update_encounter_camera_focus` (#1) | [src/dungeon/monster/beldo_large/update_encounter_camera_focus.c:41](../src/dungeon/monster/beldo_large/update_encounter_camera_focus.c#L41) | 147 | 76 | 162 | 86 |
| 9 | `carve_corridor_toward_destination` (#1) | [src/dungeon/level/generate.c:2276](../src/dungeon/level/generate.c#L2276) | 159 | 78 | 156 | 78 |
| 10 | `move_toward_actor_tile_center` (#1) | [src/dungeon/monster/killer/move_toward_actor_tile_center.c:66](../src/dungeon/monster/killer/move_toward_actor_tile_center.c#L66) | 94 | 82 | 156 | 74 |
| 11 | `update_actor_directional_animation` (#1) | [src/dungeon/monster/saber/update_actor_directional_animation.c:31](../src/dungeon/monster/saber/update_actor_directional_animation.c#L31) | 94 | 80 | 150 | 70 |
| 12 | `build_shaded_textured_quad` (#1) | [src/dungeon/effect/particle/update_brightening_fading_effect.c:1435](../src/dungeon/effect/particle/update_brightening_fading_effect.c#L1435) | 109 | 97 | 145 | 48 |
| 13 | `animate_catalog_previous_detail` (#1) | [src/town/menu/animation/animate_catalog_previous_detail.c:41](../src/town/menu/animation/animate_catalog_previous_detail.c#L41) | 98 | 84 | 142 | 58 |
| 14 | `update_scene_effect_controller` (#1) | [src/engine/effect/update_scene_effect_controller.c:12](../src/engine/effect/update_scene_effect_controller.c#L12) | 136 | 92 | 140 | 48 |
| 15 | `update_fade_in_out_effect` (#1) | [src/engine/effect/update_fade_in_out_effect.c:40](../src/engine/effect/update_fade_in_out_effect.c#L40) | 82 | 74 | 130 | 56 |
| 16 | `start_voice_on_channel` (#1) | [src/engine/audio/sequence/start_channel_voice.c:97](../src/engine/audio/sequence/start_channel_voice.c#L97) | 165 | 94 | 118 | 24 |
| 17 | `find_highest_valid_cell_height` (#1) | [src/town/map/forward_surface_query_with_argument_g01117.c:893](../src/town/map/forward_surface_query_with_argument_g01117.c#L893) | 128 | 99 | 118 | 19 |
| 18 | `CheckBuildBuildingLandNo` (#1) | [src/town/map/building.c:19](../src/town/map/building.c#L19) | 126 | 91 | 115 | 24 |
| 19 | `refresh_catalog_entry_grid` (#1) | [src/town/menu/menu_row_index.c:53](../src/town/menu/menu_row_index.c#L53) | 93 | 72 | 114 | 42 |
| 20 | `SpuSetCommonAttr` (#1) | [src/engine/audio/spu/spu_attr.c:44](../src/engine/audio/spu/spu_attr.c#L44) | 169 | 66 | 110 | 44 |
| 21 | `refresh_packed_grid_nibbles` (#1) | [src/dungeon/effect/screen/change.c:1219](../src/dungeon/effect/screen/change.c#L1219) | 89 | 86 | 110 | 24 |
| 22 | `choose_next_step_toward_destination` (#1) | [src/dungeon/level/generate.c:2143](../src/dungeon/level/generate.c#L2143) | 121 | 85 | 108 | 23 |
| 23 | `initialize_building_scene_objects` (#1) | [src/town/map/initialize_building_scene_objects.c:31](../src/town/map/initialize_building_scene_objects.c#L31) | 80 | 82 | 106 | 24 |
| 24 | `advance_actor_action_controller` (#1) | [src/dungeon/actor/advance_actor_action_controller.c:37](../src/dungeon/actor/advance_actor_action_controller.c#L37) | 107 | 85 | 105 | 20 |
| 25 | `update_gym_score_object` (#1) | [src/town/minigame/object/update_gym_score_object.c:46](../src/town/minigame/object/update_gym_score_object.c#L46) | 162 | 91 | 105 | 14 |
| 26 | `create_nine_linked_effects` (#1) | [src/dungeon/effect/motion/initialize_entity_position_and_motion.c:1157](../src/dungeon/effect/motion/initialize_entity_position_and_motion.c#L1157) | 121 | 93 | 101 | 8 |
| 27 | `decode_or_copy_resource_pixels` (#1) | [src/engine/resource/decode_or_copy_resource_pixels.c:5](../src/engine/resource/decode_or_copy_resource_pixels.c#L5) | 158 | 84 | 100 | 16 |
| 28 | `process_circular_segments` (#1) | [src/dungeon/actor/depth_strip_projection_g00337.c:6](../src/dungeon/actor/depth_strip_projection_g00337.c#L6) | 169 | 92 | 100 | 8 |
| 29 | `update_timed_tile_approach` (#1) | [src/dungeon/monster/blume/update_timed_tile_approach.c:66](../src/dungeon/monster/blume/update_timed_tile_approach.c#L66) | 95 | 84 | 96 | 12 |
| 30 | `run_warp_cutscene` (#1) | [src/dungeon/effect/travel/warp.c:378](../src/dungeon/effect/travel/warp.c#L378) | 100 | 82 | 94 | 12 |

Eligible definitions: 47; showing up to 30.

## Queues, proof and reproduction

`queue/<category>.tsv` retains the v1 columns, including symbol/occurrence, normalized anchor, evidence, category score and payoff = category score * max(1, distinct known callers). Each registry category gets a queue automatically, even if empty. Same-file/global unique resolution and ambiguity limits are unchanged from v1; callback, assembly and macro-expanded edges are not inferred. 17,061 resolved edges; 6,392 unresolved spellings. Keep all trend categories, coverage and source digest; never compare v1 totals directly with v2 totals. Evidence spans describe the snapshot, not replay offsets. Inspect current symbols, anchors, shared headers and matching proof before source changes. This census is not a build gate.

Run from the repository root (Python standard library, <=4 workers):

```sh
nice -n 10 python3 -m unittest discover -s tools/readability -p "test_*.py"
nice -n 10 python3 tools/readability/score.py --schema v2 --root . --revision ee0067601 --out out/readability-v2 --docs docs/READABILITY.md
nice -n 10 python3 tools/readability/score.py --schema v1 --root . --revision ee0067601 --out out/readability-v1
```

Outputs use sorted relative identities, no timestamps, and no absolute paths. --revision labels a snapshot; it does not check out that Git revision. Source symlinks are refused. Definitions in include/ are outside coverage. Unmatched conditional delimiters are reported and cause exit 1; invalid registry/input causes exit 2. Exit 0 requires no delimiter warnings. Worker count does not change output. Macro-generated functions, typedef-only pointer casts, type flow and semantic states/timers require further detectors and owner review.
