# Readability census

Baseline: `dc234586b`; metric schema: `readability-v1`. 6,260 physical source files (.c/.h), 8,252 function definitions, 16,817,017 source bytes.

This is a lexical source census for choosing future work. Scores describe visible debt; they do not prove that a literal is unexplained, a cast removable, or a rewrite safe for matching. Every physical `.c`/`.h` file under `src/` is read once, including merged translation units, auxiliary C and local headers. A function is keyed by relative path, symbol and occurrence, so duplicate overlay names and conditional definitions remain separate. Declarations, function-pointer variables and data initializers are excluded. Comments, string/character contents and preprocessor directive bodies do not contribute.

## Measurements and weights

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

Total score is the sum of five category scores. `offsets` and `casts` use their own weights; `names` combines address and temporary names; `magic` counts magic literals; `structure` combines M2C, gotos, nesting and length. Overlap between categories is intentional: an offset cast with a literal can contribute to three categories. Brace nesting includes local structs and initializer lists, and does not measure unbraced control nesting. Magic detection is syntactic: constants in local named initializers are included, standalone return values, case labels, array bounds on the left of assignments and standalone call arguments are excluded. No semantic naming recommendation follows from these counts.

## Subsystems

| Subsystem | Files | Definitions | Offsets | Casts | Names | Magic | Structure | Total |
| --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: |
| dungeon | 2,170 | 3,391 | 79,416 | 213,228 | 139,372 | 106,932 | 20,798 | 559,746 |
| engine | 816 | 881 | 2,904 | 6,555 | 2,586 | 8,474 | 1,674 | 22,193 |
| frontend | 368 | 404 | 4,280 | 6,483 | 3,739 | 3,098 | 440 | 18,040 |
| main | 41 | 40 | 24 | 264 | 106 | 150 | 42 | 586 |
| movie | 1 | 17 | 0 | 93 | 31 | 84 | 10 | 218 |
| ovmovie | 4 | 12 | 64 | 120 | 96 | 140 | 22 | 442 |
| slus | 44 | 221 | 192 | 282 | 282 | 700 | 204 | 1,660 |
| town | 2,816 | 3,286 | 17,456 | 35,931 | 34,456 | 22,590 | 3,690 | 114,123 |

Subsystem values are weighted debt totals. `files.tsv` and `folders.tsv` give the same aggregation at file and immediate parent-folder level; all files, including those without definitions, appear in coverage/file summaries. Maximum nesting aggregates with max; other numeric measures sum (temporary unique counts are per-function sums).

## Fifty hardest functions

Ranked by total weighted score, ties by function key. Locations are for navigation; replay/queue identity uses the symbol and occurrence.

| Rank | Function | Source | Score | What makes it hard |
| ---: | --- | --- | ---: | --- |
| 1 | `func_8002405C` (#1) | [src/dungeon/effect/mesh/wave.c:58](../src/dungeon/effect/mesh/wave.c#L58) | 3,759 | 231 byte offsets; 494 pointer casts; 1 address name; 20 func_ uses; 1 D_ uses; 173 magic literals; nesting 7; 359 code lines |
| 2 | `render_rotated_effect_quads` (#1) | [src/dungeon/effect/sprite/render_rotated_effect_quads.c:4](../src/dungeon/effect/sprite/render_rotated_effect_quads.c#L4) | 3,439 | 216 byte offsets; 455 pointer casts; 14 func_ uses; 1 D_ uses; 144 magic literals; nesting 5; 354 code lines |
| 3 | `update_effect_particles_and_cleanup` (#1) | [src/dungeon/effect/particle/update_effect_particles_and_cleanup.c:318](../src/dungeon/effect/particle/update_effect_particles_and_cleanup.c#L318) | 2,834 | 103 byte offsets; 374 pointer casts; 4 func_ uses; 12 D_ uses; 213 unk_ uses; 199 magic literals; nesting 4; 498 code lines |
| 4 | `update_player_and_actor_turns` (#1) | [src/dungeon/player/update_player_and_actor_turns.c:235](../src/dungeon/player/update_player_and_actor_turns.c#L235) | 2,701 | 112 byte offsets; 343 pointer casts; 4 gotos; 2 func_ uses; 14 D_ uses; 140 unk_ uses; 189 magic literals; nesting 8; 624 code lines |
| 5 | `update_actor_scripts_and_motion` (#1) | [src/dungeon/monster/kewne_uncached/create_entity_at_tile_center.c:45](../src/dungeon/monster/kewne_uncached/create_entity_at_tile_center.c#L45) | 2,686 | 436 pointer casts; 4 func_ uses; 45 D_ uses; 373 unk_ uses; 205 magic literals; nesting 24; 738 code lines |
| 6 | `render_active_sprite_parts_and_shadows` (#1) | [src/dungeon/level/render_active_sprite_parts_and_shadows.c:122](../src/dungeon/level/render_active_sprite_parts_and_shadows.c#L122) | 2,672 | 123 byte offsets; 280 pointer casts; 28 func_ uses; 1 D_ uses; 215 unk_ uses; 153 magic literals; nesting 10; 467 code lines |
| 7 | `advance_linked_actor_motion_script` (#1) | [src/dungeon/monster/beldo_large/advance_linked_actor_motion_script.c:175](../src/dungeon/monster/beldo_large/advance_linked_actor_motion_script.c#L175) | 2,173 | 337 pointer casts; 1 gotos; 1 func_ uses; 13 D_ uses; 372 unk_ uses; 4 temporary names; 169 magic literals; nesting 4; 647 code lines |
| 8 | `advance_effect_sequence` (#1) | [src/dungeon/effect/particle/project_and_queue_visible_shaded_quad.c:1117](../src/dungeon/effect/particle/project_and_queue_visible_shaded_quad.c#L1117) | 2,091 | 16 byte offsets; 349 pointer casts; 4 func_ uses; 7 D_ uses; 306 unk_ uses; 118 magic literals; nesting 8; 448 code lines |
| 9 | `render_actor_sprite_parts` (#1) | [src/dungeon/actor/effect/render_actor_sprite_parts.c:188](../src/dungeon/actor/effect/render_actor_sprite_parts.c#L188) | 1,857 | 77 byte offsets; 171 pointer casts; 9 func_ uses; 240 unk_ uses; 102 magic literals; nesting 5; 299 code lines |
| 10 | `update_traveling` (#1) | [src/dungeon/effect/mesh/build_textured_sprite_strips.c:978](../src/dungeon/effect/mesh/build_textured_sprite_strips.c#L978) | 1,724 | 30 byte offsets; 100 pointer casts; 1 gotos; 4 func_ uses; 10 D_ uses; 397 unk_ uses; 155 magic literals; nesting 6; 567 code lines |
| 11 | `create_anchored_directional_object` (#1) | [src/dungeon/monster/flame/flame_actions.c:141](../src/dungeon/monster/flame/flame_actions.c#L141) | 1,665 | 67 byte offsets; 247 pointer casts; 4 func_ uses; 4 D_ uses; 83 unk_ uses; 86 magic literals; nesting 7; 291 code lines |
| 12 | `update_homing_effect_and_attached_copies` (#1) | [src/dungeon/effect/motion/initialize_entity_position_and_motion.c:435](../src/dungeon/effect/motion/initialize_entity_position_and_motion.c#L435) | 1,638 | 14 byte offsets; 60 pointer casts; 1 gotos; 21 func_ uses; 9 D_ uses; 480 unk_ uses; 134 magic literals; nesting 6; 689 code lines |
| 13 | `update_animated_effect_sprite` (#1) | [src/dungeon/effect/particle/project_textured_quad_or_callback.c:1384](../src/dungeon/effect/particle/project_textured_quad_or_callback.c#L1384) | 1,632 | 11 byte offsets; 250 pointer casts; 1 gotos; 8 func_ uses; 7 D_ uses; 257 unk_ uses; 107 magic literals; nesting 4; 403 code lines |
| 14 | `update_actor_callbacks_and_ground` (#1) | [src/dungeon/monster/kewne/update_actor_callbacks_and_ground.c:19](../src/dungeon/monster/kewne/update_actor_callbacks_and_ground.c#L19) | 1,606 | 101 byte offsets; 198 pointer casts; 4 func_ uses; 3 D_ uses; 87 magic literals; nesting 4; 183 code lines |
| 15 | `select_creature_action_and_target` (#1) | [src/dungeon/actor/select_creature_action_and_target.c:64](../src/dungeon/actor/select_creature_action_and_target.c#L64) | 1,593 | 289 pointer casts; 5 gotos; 29 unk_ uses; 272 magic literals; nesting 10; 1063 code lines |
| 16 | `advance_projectile_burst_and_impact` (#1) | [src/dungeon/effect/particle/render_textured_effect_parts.c:424](../src/dungeon/effect/particle/render_textured_effect_parts.c#L424) | 1,534 | 7 byte offsets; 226 pointer casts; 28 func_ uses; 9 D_ uses; 206 unk_ uses; 140 magic literals; nesting 5; 464 code lines |
| 17 | `advance_paired_object_sequence` (#1) | [src/dungeon/effect/motion/advance_paired_object_sequence.c:165](../src/dungeon/effect/motion/advance_paired_object_sequence.c#L165) | 1,522 | 13 byte offsets; 240 pointer casts; 1 gotos; 10 D_ uses; 197 unk_ uses; 116 magic literals; nesting 6; 600 code lines |
| 18 | `create_anchored_directional_object` (#1) | [src/dungeon/monster/univern/create_anchored_directional_object.c:169](../src/dungeon/monster/univern/create_anchored_directional_object.c#L169) | 1,509 | 65 byte offsets; 215 pointer casts; 2 func_ uses; 15 D_ uses; 68 unk_ uses; 76 magic literals; nesting 5; 226 code lines |
| 19 | `render_shaded_map_tiles` (#1) | [src/town/map/shaded_tile_rendering_g00594.c:25](../src/town/map/shaded_tile_rendering_g00594.c#L25) | 1,430 | 23 byte offsets; 110 pointer casts; 3 func_ uses; 297 unk_ uses; 126 magic literals; nesting 11; 573 code lines |
| 20 | `update_directional_actor_effect` (#1) | [src/dungeon/effect/particle/fade_effect_sprite_to_black.c:46](../src/dungeon/effect/particle/fade_effect_sprite_to_black.c#L46) | 1,389 | 2 byte offsets; 219 pointer casts; 1 gotos; 12 func_ uses; 5 D_ uses; 201 unk_ uses; 14 temporary names; 113 magic literals; nesting 5; 420 code lines |
| 21 | `update_actor_movement_history` (#1) | [src/dungeon/monster/u_boat/update_actor_movement_history.c:51](../src/dungeon/monster/u_boat/update_actor_movement_history.c#L51) | 1,359 | 59 byte offsets; 121 pointer casts; 7 gotos; 111 unk_ uses; 100 magic literals; nesting 9; 384 code lines |
| 22 | `update_actor_movement_and_ground_height` (#1) | [src/dungeon/monster/hikewne/update_actor_movement_and_ground_height.c:57](../src/dungeon/monster/hikewne/update_actor_movement_and_ground_height.c#L57) | 1,350 | 59 byte offsets; 180 pointer casts; 4 func_ uses; 14 D_ uses; 61 unk_ uses; 77 magic literals; nesting 6; 226 code lines |
| 23 | `update_actor_movement_facing` (#1) | [src/dungeon/monster/hikewne/update_actor_movement_facing.c:57](../src/dungeon/monster/hikewne/update_actor_movement_facing.c#L57) | 1,350 | 59 byte offsets; 180 pointer casts; 4 func_ uses; 14 D_ uses; 61 unk_ uses; 77 magic literals; nesting 6; 226 code lines |
| 24 | `update_entity_behavior_movement_and_ground` (#1) | [src/dungeon/monster/hikewne/update_entity_behavior_movement_and_ground.c:56](../src/dungeon/monster/hikewne/update_entity_behavior_movement_and_ground.c#L56) | 1,350 | 59 byte offsets; 180 pointer casts; 4 func_ uses; 14 D_ uses; 61 unk_ uses; 77 magic literals; nesting 6; 226 code lines |
| 25 | `update_entity_behavior_movement_and_grounding` (#1) | [src/dungeon/monster/hikewne/update_entity_behavior_movement_and_grounding.c:57](../src/dungeon/monster/hikewne/update_entity_behavior_movement_and_grounding.c#L57) | 1,350 | 59 byte offsets; 180 pointer casts; 4 func_ uses; 14 D_ uses; 61 unk_ uses; 77 magic literals; nesting 6; 226 code lines |
| 26 | `update_entity_behavior_movement_and_height` (#1) | [src/dungeon/monster/hikewne/update_entity_behavior_movement_and_height.c:56](../src/dungeon/monster/hikewne/update_entity_behavior_movement_and_height.c#L56) | 1,350 | 59 byte offsets; 180 pointer casts; 4 func_ uses; 14 D_ uses; 61 unk_ uses; 77 magic literals; nesting 6; 226 code lines |
| 27 | `update_entity_ground_animation` (#1) | [src/dungeon/monster/hikewne/update_entity_ground_animation.c:57](../src/dungeon/monster/hikewne/update_entity_ground_animation.c#L57) | 1,350 | 59 byte offsets; 180 pointer casts; 4 func_ uses; 14 D_ uses; 61 unk_ uses; 77 magic literals; nesting 6; 226 code lines |
| 28 | `update_entity_movement_and_ground` (#1) | [src/dungeon/monster/hikewne/update_entity_movement_and_ground.c:57](../src/dungeon/monster/hikewne/update_entity_movement_and_ground.c#L57) | 1,350 | 59 byte offsets; 180 pointer casts; 4 func_ uses; 14 D_ uses; 61 unk_ uses; 77 magic literals; nesting 6; 226 code lines |
| 29 | `update_chasing_star_effect` (#1) | [src/dungeon/effect/sprite/route.c:447](../src/dungeon/effect/sprite/route.c#L447) | 1,318 | 7 byte offsets; 182 pointer casts; 1 gotos; 11 func_ uses; 4 D_ uses; 211 unk_ uses; 111 magic literals; nesting 6; 391 code lines |
| 30 | `run_actor_callbacks_and_update_grounding` (#1) | [src/dungeon/monster/death/run_actor_callbacks_and_update_grounding.c:37](../src/dungeon/monster/death/run_actor_callbacks_and_update_grounding.c#L37) | 1,269 | 65 byte offsets; 171 pointer casts; 14 D_ uses; 24 unk_ uses; 69 magic literals; nesting 5; 230 code lines |
| 31 | `update_entity_movement_and_ground_height` (#1) | [src/dungeon/monster/death/update_entity_movement_and_ground_height.c:37](../src/dungeon/monster/death/update_entity_movement_and_ground_height.c#L37) | 1,269 | 65 byte offsets; 171 pointer casts; 14 D_ uses; 24 unk_ uses; 69 magic literals; nesting 5; 230 code lines |
| 32 | `update_entity_movement_animation_and_height` (#1) | [src/dungeon/monster/death/update_entity_movement_animation_and_height.c:37](../src/dungeon/monster/death/update_entity_movement_animation_and_height.c#L37) | 1,269 | 65 byte offsets; 171 pointer casts; 14 D_ uses; 24 unk_ uses; 69 magic literals; nesting 5; 231 code lines |
| 33 | `run_entity_callbacks_and_update_ground` (#1) | [src/dungeon/monster/death/run_entity_callbacks_and_update_ground.c:37](../src/dungeon/monster/death/run_entity_callbacks_and_update_ground.c#L37) | 1,266 | 65 byte offsets; 170 pointer casts; 14 D_ uses; 24 unk_ uses; 69 magic literals; nesting 5; 224 code lines |
| 34 | `update_actor_animation_movement` (#1) | [src/dungeon/monster/death/update_actor_animation_movement.c:37](../src/dungeon/monster/death/update_actor_animation_movement.c#L37) | 1,255 | 64 byte offsets; 169 pointer casts; 14 D_ uses; 24 unk_ uses; 69 magic literals; nesting 5; 228 code lines |
| 35 | `update_entity_movement_animation_and_ground` (#1) | [src/dungeon/monster/death/update_entity_movement_animation_and_ground.c:37](../src/dungeon/monster/death/update_entity_movement_animation_and_ground.c#L37) | 1,255 | 64 byte offsets; 169 pointer casts; 14 D_ uses; 24 unk_ uses; 69 magic literals; nesting 5; 228 code lines |
| 36 | `update_entity_motion_facing_and_ground` (#1) | [src/dungeon/monster/death/update_entity_motion_facing_and_ground.c:37](../src/dungeon/monster/death/update_entity_motion_facing_and_ground.c#L37) | 1,226 | 63 byte offsets; 166 pointer casts; 14 D_ uses; 24 unk_ uses; 63 magic literals; nesting 5; 220 code lines |
| 37 | `run_collection_round_sequence` (#1) | [src/town/scene/run_collection_round_sequence.c:124](../src/town/scene/run_collection_round_sequence.c#L124) | 1,221 | 14 byte offsets; 167 pointer casts; 16 func_ uses; 14 D_ uses; 149 unk_ uses; 109 magic literals; nesting 6; 327 code lines |
| 38 | `build_and_depth_sorts_five_radial_line_segments_effect` (#1) | [src/dungeon/effect/mesh/create_an_effect_position_randomized_sprite_angle.c:92](../src/dungeon/effect/mesh/create_an_effect_position_randomized_sprite_angle.c#L92) | 1,201 | 75 byte offsets; 155 pointer casts; 6 func_ uses; 60 magic literals; 115 code lines |
| 39 | `animate_falling_timed_object` (#1) | [src/town/scene/animation/animate_falling_timed_object.c:69](../src/town/scene/animation/animate_falling_timed_object.c#L69) | 1,192 | 29 byte offsets; 162 pointer casts; 3 gotos; 15 func_ uses; 16 D_ uses; 97 unk_ uses; 85 magic literals; nesting 5; 263 code lines |
| 40 | `update_sequenced_object` (#1) | [src/town/scene/object/update_sequenced_object.c:101](../src/town/scene/object/update_sequenced_object.c#L101) | 1,192 | 1 byte offsets; 170 pointer casts; 22 func_ uses; 39 D_ uses; 166 unk_ uses; 93 magic literals; nesting 6; 382 code lines |
| 41 | `update_actor_object_motion` (#1) | [src/dungeon/monster/baloon/update_actor_object_motion.c:54](../src/dungeon/monster/baloon/update_actor_object_motion.c#L54) | 1,185 | 55 byte offsets; 163 pointer casts; 2 func_ uses; 1 D_ uses; 52 unk_ uses; 62 magic literals; nesting 5; 206 code lines |
| 42 | `func_80024758` (#1) | [src/dungeon/effect/particle/project_textured_quad_or_callback.c:376](../src/dungeon/effect/particle/project_textured_quad_or_callback.c#L376) | 1,176 | 34 byte offsets; 171 pointer casts; 1 address name; 24 func_ uses; 154 magic literals; nesting 7; 221 code lines |
| 43 | `update_dropped_object_motion` (#1) | [src/dungeon/actor/effect/effect.c:1157](../src/dungeon/actor/effect/effect.c#L1157) | 1,168 | 18 byte offsets; 192 pointer casts; 1 gotos; 1 D_ uses; 137 unk_ uses; 71 magic literals; nesting 5; 239 code lines |
| 44 | `update_bank_actor_movement` (#1) | [src/dungeon/monster/zu/update_bank_actor_movement.c:175](../src/dungeon/monster/zu/update_bank_actor_movement.c#L175) | 1,165 | 54 byte offsets; 139 pointer casts; 2 func_ uses; 73 unk_ uses; 73 magic literals; nesting 5; 182 code lines |
| 45 | `advance_item_use_and_cleanup` (#1) | [src/dungeon/monster/hikewne/advance_item_use_and_cleanup.c:56](../src/dungeon/monster/hikewne/advance_item_use_and_cleanup.c#L56) | 1,158 | 39 byte offsets; 170 pointer casts; 10 D_ uses; 94 unk_ uses; 48 magic literals; nesting 6; 348 code lines |
| 46 | `update_actor_visual_motion` (#1) | [src/dungeon/monster/u_boat/update_actor_visual_motion.c:45](../src/dungeon/monster/u_boat/update_actor_visual_motion.c#L45) | 1,156 | 53 byte offsets; 158 pointer casts; 2 func_ uses; 1 D_ uses; 50 unk_ uses; 66 magic literals; nesting 5; 196 code lines |
| 47 | `build_textured_sprite_strips` (#1) | [src/dungeon/effect/mesh/build_textured_sprite_strips.c:74](../src/dungeon/effect/mesh/build_textured_sprite_strips.c#L74) | 1,133 | 28 byte offsets; 75 pointer casts; 10 func_ uses; 1 D_ uses; 257 unk_ uses; 59 magic literals; nesting 5; 390 code lines |
| 48 | `update_actor_callbacks_animation_and_ground` (#1) | [src/dungeon/monster/snowman/move_and_shrink_fading_effect.c:257](../src/dungeon/monster/snowman/move_and_shrink_fading_effect.c#L257) | 1,126 | 45 byte offsets; 166 pointer casts; 1 func_ uses; 19 D_ uses; 56 unk_ uses; 50 magic literals; nesting 4; 186 code lines |
| 49 | `update_actor_approach_descent_return` (#1) | [src/dungeon/monster/baloon/update_actor_approach_descent_return.c:102](../src/dungeon/monster/baloon/update_actor_approach_descent_return.c#L102) | 1,116 | 8 byte offsets; 178 pointer casts; 9 D_ uses; 147 unk_ uses; 88 magic literals; nesting 6; 310 code lines |
| 50 | `update_gym_minigame` (#1) | [src/town/minigame/update_gym_minigame.c:115](../src/town/minigame/update_gym_minigame.c#L115) | 1,116 | 10 byte offsets; 158 pointer casts; 1 gotos; 32 D_ uses; 130 unk_ uses; 99 magic literals; nesting 6; 340 code lines |

## Work queues and caller limits

Each `queue/{offsets,casts,names,magic,structure}.tsv` contains all definitions with debt in that category. Payoff is `category_score * max(1, known_callers)`, an optimistic score reduction times distinct source callers. It is a prioritization estimate, not a prediction of achievable reduction. Ties use category score then function key. Repeated calls from one definition count once; recursion does not boost its own count. A unique same-file target wins, otherwise only a unique non-static global definition resolves. Duplicate overlay symbols and conditional variants remain ambiguous. Function-pointer/address-taking edges, alias expansion, assembly calls and preprocessor macro expansion are not resolved. Local callbacks whose spelling coincides with a global function can be overcounted. `calls.tsv` exposes the edges and `unresolved_calls.tsv` exposes 6,394 unresolved spellings; 17,071 edges resolve. A token-normalized definition hash anchors each queue entry. Before editing, inspect the current symbol, callers, owning header and proof requirements. Names need evidence; offset/cast fixes should retype declarations rather than add use-site casts.

## Trend per landing

Track the five **total weighted category debts** from `trend.tsv`, in this order: `offsets`, `casts`, `names`, `magic`, `structure`. Lower is better; also retain metadata coverage, source digest and schema so deleted/missed functions cannot masquerade as readability improvements. Do not divide by source length: adding code must not dilute debt. Use the same schema and weights on both sides of a landing, report five signed deltas, and inspect changed-function rows when coverage changes. This metric is not a build gate.

| Category | Baseline weighted debt |
| --- | ---: |
| offsets | 104,336 |
| casts | 262,956 |
| names | 180,668 |
| magic | 142,168 |
| structure | 26,880 |

## Reproduce and limitations

Run from the repository root (Python 3 standard library only):

```sh
nice -n 10 python3 -m unittest discover -s tools/readability -p "test_*.py"
nice -n 10 python3 tools/readability/score.py --root . --revision dc234586b --out out/readability --docs docs/READABILITY.md
```

The CLI uses at most four workers (override with `--workers 1` for serial use). Outputs have stable ordering and contain no timestamps or absolute paths. The source digest hashes sorted relative paths and file hashes; metadata and coverage make the snapshot auditable without a build. The scanner handles ANSI/K&R definitions, implicit int returns and GNU attributes. It does not expand macro-generated function definitions. Source symlinks are refused. Includes are not expanded; definitions in headers outside `src/` are outside this source census. Both sides of conditional compilation are textually counted; there is no claim that all are linked together. Branch-dependent unmatched delimiters are reported in `parse_warnings.tsv` and require review. Pointer casts through typedefs without a spelled `*`, variable byte offsets, scalar casts, field names without the listed prefixes and numeric literals outside assignments/comparisons are outside the metric. This deliberately conservative lexer is not a C type checker.
