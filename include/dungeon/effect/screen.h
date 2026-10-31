#ifndef DUNGEON_EFFECT_SCREEN_H
#define DUNGEON_EFFECT_SCREEN_H

/* Function contracts owned by src/dungeon/effect/screen/ (decision 74; maintained by tools/headers). */
#include "common.h"
#include "shared/gpu_packets.h"
#include "shared/entity.h"

typedef struct AdvanceScreenTransitionBody {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x18];
    u16 unk_24;
    u16 unk_26;
    union { s16 s; u16 u; } unk_28;
    u8 pad_2A[0x2];
    union { s16 s; u16 u; } unk_2C;
    s16 unk_2E;
    u8 pad_30[0x9A];
    u16 unk_CA;
    u8 pad_CC[0x2];
    u16 unk_CE;
    u8 pad_D0[0x2];
    u16 unk_D2;
    u8 pad_D4[0x12];
    u16 unk_E6;
    u32 unk_E8;
    union { u32 word; u8 bytes[4]; } unk_EC;
    u16 unk_F0;
    u16 unk_F2;
    u16 unk_F4;
    u16 unk_F6;
    u16 unk_F8;
    u16 unk_FA;
    u16 unk_FC;
    u16 unk_FE;
    u16 unk_100;
    u16 unk_102;
} AdvanceScreenTransitionBody;

void add_random_quarter_value(ActorRecord *body, void *target);
void create_wrapped_texture_scroll(s16 value);
void draw_content_or_rect(s32 *line_start, s32 *line_end, u8 *rect, s16 fill, s32 content_id);
s32 get_masked_record_flags(EntityRec *record, s32 mask, s32 mode);
void pack_and_submit_cell_height_levels(void);
void update_packed_map_levels(void);
s32 try_trigger_target_record_effect(void *entity_in, s32 flags, void *record_in);

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
