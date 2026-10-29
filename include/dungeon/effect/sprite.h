#ifndef DUNGEON_EFFECT_SPRITE_H
#define DUNGEON_EFFECT_SPRITE_H
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
struct S_800244BC_2;
s32 ground_items_lack_special_pair(void);
void advance_target_chasing_emitter(void *object, struct S_800244BC_2 *position, s32 context);
void *create_an_copies_three_source_fields_child_runs_n_16_child_setup(s32 value, void *source, s32 unused, s32 context);
void *draw_sprite_effect_quads(u8 *sprite_list, s32 count_hint, s32 render_state_addr, u8 *placement, u8 *packet_buf);
void process_effect_block_entries(void *block);
void add_hex_200_s_field_64_runs_callbacks_mode_n_2_check_returns_zero(EntityRec *object, s32 unused, void *record);







void advance_damped_animated_sprite(void *entry, ObjectPosition *motion, SpriteFrameState *object);
void update_spiral_effect(void *effect, ObjectPosition *motion, SpriteFrameState *sprite);

/* Callback entry points. */
void update_linked_monster_effect(void *effect_in, void *motion_in, void *sprite_in);

struct S_func_800D7FB8_0;
void update_effect_controller(struct S_func_800D7FB8_0 *controller);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
#include "shared/dungeon_moving_views.h"
s32 draw_shaded_textured_cylinder(void *unused_data, MovingPosition *center, s32 unused_value, s16 rotation, s32 height, s16 radius, u8 blend_mode, u8 brightness);

struct EffectColor;
struct S_func_81886800_1;
struct S_func_81886800_11;
struct S_func_81886800_3;
void check_the_target_using_scaled_low_byte_conditionally_applies_global_800_e_1_d_01(void *target, s32 value, void *record);
void create_a_sprite_effect_position_randomized_rotation(s16 x, s16 y, s16 z);
void create_quad_fragments_vertex_grid_randomized_motion_rotation(void);
void handle_retail_n_81887570_callee_80024_d_70_fade_colour_n_1_n_8_per_call_mark(void *effect, s32 unused, struct EffectColor *color);
void run_jittered_point_sequence(void *sequence, void *out_position);
void run_radial_sprite_sequence(struct S_func_81886800_1 *effect, struct S_func_81886800_11 *motion, struct S_func_81886800_3 *sprite);
void update_jittered_effect_points(void *effect);
void update_pulsing_actor_color(void *state_data, s32 unused, void *actor_data);
void update_randomized_intermediate_points(void *self);

s32 build_and_enqueue_interpolated_depth_sorted_shaded_lines_linked_list(void *first_owner, void *first_vertices, void *first_line);

#endif
