#ifndef DUNGEON_EFFECT_SCREEN_H
#define DUNGEON_EFFECT_SCREEN_H

/* Function contracts owned by src/dungeon/effect/screen/ (decision 74; maintained by tools/headers). */
#include "common.h"
#include "shared/gpu_packets.h"
#include "shared/entity.h"
void add_random_quarter_value(void *source, void *target);
void create_wrapped_texture_scroll(s16 value);
void draw_content_or_rect(s32 *line_start, s32 *line_end, u8 *rect, s16 fill, s32 content_id);
s32 get_masked_record_flags(EntityRec *record, s32 mask, s32 mode);
void pack_and_submit_cell_height_levels(void);
void update_packed_map_levels(void);
s32 try_trigger_target_record_effect(void *entity, s32 flags, void *record);

/* Callback entry points. */
s32 queue_linked_visible_rectangle_copies(void *initial_state, void *input_values, s16 *initial_delta);

void apply_attack_power_and_element_effects(void *target, s16 base_power, s16 power_bonus, s16 elements, u16 hit_angle, void *source, u16 hit_kind);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void spawn_blinking_sprite_flash(s16 x, s16 y, s16 z);

struct S_Arg1;
struct S_Rect;
void create_type_212_object(s32 flag, s8 value);
void queue_visible_rectangle_copy(struct S_Rect *copy_rect, struct S_Arg1 *source);
void retire_tracked_effect_by_id(s32 targetId);

void *create_item_target_selector(u8 *selection_data);

void *resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);

/* Rectangle buffers contain packed x/y and width/height words. */
void draw_textured_ellipse(void *parameters, GpuRect *rectangle, u16 fill_rect, u16 draw_mode);

void *create_five_point_effect(s16 tile_x, s16 tile_y, s16 pos_z, void *transform_data, s16 scale, s32 setup_word_5c, s32 setup_word_60);
void *create_orbiting_color_particle(s16 x, s16 y, s16 z, s16 angle, s16 value_50, s16 value_58, s32 state_word, s16 value_48);

#include "shared/object_node.h"
struct FuncInput;
void create_attenuating_moving_effect(ObjectNodeHeader **alloc_arg, s32 child_x, s32 child_y, s32 child_z, struct FuncInput *input, s32 meta_value, s16 step_count, s32 range_value, s16 object_tag);

#endif
