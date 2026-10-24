#include "shared/object_node_flags.h"
#include "shared/audio_commands.h"
/* Level reduction attempts, terrain-seeking particles, randomized drawing, and target effects. */
#include "modules/dungeon_ovl_192a800.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/dungeon_effect_views.h"
#include "shared/gpu_packets.h"
#include "shared/game_work.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"
#include "modules/dungeon_native_abi.h"
#include "shared/entity_height_offsets.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "dungeon/player/object.h"

void (*const dungeon_192a800_entry)(struct S_func_8190B2D0_0 *,void *,void *) = update_a_moving_effect_target_animation_cleanup_state;
const u8 level_not_decreased_suffix[52] = {0x81,0x66,0x82,0x93,0x81,0x40,0x82,0x8c,0x82,0x85,0x82,0x96,0x82,0x85,0x82,0x8c,0x81,0x40,0x82,0x84,0x82,0x89,0x82,0x84,0x82,0x8e,0x81,0x66,0x82,0x94,0x81,0x40,0x82,0x84,0x82,0x85,0x82,0x83,0x82,0x92,0x82,0x85,0x82,0x81,0x82,0x93,0x82,0x85,0x81,0x44,0x0,0x0};
const Rect D_80024038 = {832,256,96,88};
const Rect rising_effect_texture_rect = {832,256,2,2};

#include "dungeon/effect/screen.h"
extern s32 random_dungeon_range_16(s32 bound_a, s32 bound_b);
extern void adjust_source_value_and_finalize(void *context, void *source);
extern void create_actor_value_popup(s32 flags, u8 *source_data, s16 value, u16 callback_mode);
extern const u8 level_not_decreased_suffix[];

/* Runs action 0x53 on the target after state and threshold checks. */
extern u32 RotTransPers(void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void SetDrawMode(void *, s32, s32, s32, s32);
extern s32 rand(void);
extern s32 rand(void);
extern s32 rand(void);
extern s32 D_80025638[4];
extern u8 D_80025648[48];
extern u8 D_80025678[44];
extern s32 get_a_random_in_n_0_limit_zero_limit_zero_rejection_sampling(s32);
extern void LoadImage(Rect *, s32 *);
extern void *jtbl_80024088[9];
extern Packed12 D_80025618;
extern Packed12 D_80025624;
extern u8 current_spell_effect_variant[];
extern s32 get_sprite_attachment_vector(void *, void *, void *, s32);
extern s32 rand(void);
extern s32 check_adjacent_tile_height_clearance(u16 x, u16 y, s32 z, void *skip_check);
extern u16 GetTPage(s32, s32, s32, s32);

/* Attempts to lower the target's level after a random threshold check and displays the fallback result
   on failure. */
void try_lower_actor_level(void *target, s32 threshold_arg, void *owner_context) {
    s32 value_index;
    s32 threshold;

    if (try_trigger_target_record_effect(target, 4, owner_context) != 0) {
        return;
    }

    value_index = (s16)(random_dungeon_range_16(0, ((u8 *)target)[3]) - 16);
    threshold = threshold_arg & 0xFF;
    if (value_index < threshold) {
        if (lower_entity_level(target, 1) != 0) {
            return;
        }
    } else if (threshold == 0xFF) {
        if (lower_entity_level(target, 1) != 0) {
            return;
        }
    }

    adjust_source_value_and_finalize(target, level_not_decreased_suffix);
    create_actor_value_popup(0x53, target, -1, 1);
}

/* GPU scratchpad (0x1F800000) workspace used while projecting. */
typedef struct Scratch80024154 {
    u16 x;
    u16 y;
    u16 z;
    u8 pad06[0x12];
    u8 *cursor;
    u8 pad1C[4];
    u32 *ot;
    u8 pad24[0x6C];
    u32 xy;
    u32 depth;
    u8 pad98[0x28];
    u32 index;
} Scratch80024154;

/* Retail 8190A954 (func_80024154): projects each linked point and queues a brightness-scaled shaded tile
 * followed by a draw-mode packet for it. */
s32 draw_dimmed_height_effect_points(PointRecord *first_point, ObjectPosition *first_position)
{
    PointRecord *point = first_point;
    ObjectPosition *position = first_position;
    GameWork *render_state = &g_game_work;
    u32 addr_mask = 0x00FFFFFF;
    GpuContext *render_ctx = g_game_work.draw_buffer;
    u8 *packet_start;
    u32 tag_mask = 0xFF000000;
    Scratch80024154 *scratch =
        (Scratch80024154 *)0x1F800000;
    PointPacket *tile;
    PointPacket *draw_mode;
    GpuContext *final_render_ctx;
    s32 color_value;
    s32 draw_page;
    ObjectNodeHeader *next_node;

    packet_start = render_ctx->packetCursor;
    scratch->ot = (u32 *)&render_ctx->orderTag;
    scratch->cursor = packet_start;

    for (;;) {
        tile = (PointPacket *)scratch->cursor;
        scratch->x = position->x.w.i;
        scratch->y = position->y.w.i;
        scratch->z = (u16)position->z.w.i;
        scratch->cursor = (u8 *)tile + 0xC;
        scratch->index = RotTransPers(scratch, &tile->data,
                                       &scratch->xy, &scratch->depth);

        if (scratch->index < 0x1E0U) {
            *(u32 *)&tile->r = point->color;

            color_value = tile->r * point->brightness;
            if (color_value < 0) {
                color_value += 0xFF;
            }
            tile->r = color_value >> 8;

            color_value = tile->g * point->brightness;
            if (color_value < 0) {
                color_value += 0xFF;
            }
            tile->g = color_value >> 8;

            color_value = tile->b * point->brightness;
            if (color_value < 0) {
                color_value += 0xFF;
            }
            tile->b = color_value >> 8;

            ((GpuLinkTag *)&tile->tag)->len = 2;
            tile->code = 0x6A;
            ((GpuLinkTag *)&tile->tag)->addr = ((GpuLinkTag *)&scratch->ot[scratch->index])->addr;
            ((GpuLinkTag *)&scratch->ot[scratch->index])->addr = (u32)tile;

            draw_mode = (PointPacket *)scratch->cursor;
            scratch->cursor = (u8 *)draw_mode + 0xC;
            draw_page = func_80066460(0, 1, 0, 0);
            SetDrawMode(draw_mode, 0, 0, (u16)draw_page, 0);

            ((GpuLinkTag *)&draw_mode->tag)->addr = ((GpuLinkTag *)&scratch->ot[scratch->index])->addr;
            ((GpuLinkTag *)&scratch->ot[scratch->index])->addr = (u32)draw_mode;
        }

        next_node = ((ObjectNodeHeader *)point - 1)->chain_next;
        if (next_node != 0) {
            point = (PointRecord *)(next_node + 1);
            position = next_node->position;
            continue;
        }

        break;
    }

    final_render_ctx = render_state->draw_buffer;
    final_render_ctx->packetCursor = scratch->cursor;
    return 0;
}

/* Position slots: three 4-byte slots with only the second halfword used (x +2, y +6, z +0xA);
 * the z slot's word is also bumped as one s32 (+0x20000 raises z by 2). */

/* Effect record: the object header precedes it. */
typedef struct EffectRecord {
    u8 pad_00[0x32];
    u16 timer;
} EffectRecord;

/*
 * Raises Z by 0x20000 plus 12-bit jitter while below sampled terrain height, subtracts eight from
 * the timer, and flags removal when its signed value is zero or negative.
 */
void handle_raise_position_toward_queried_height_set_flags_countdown_expires(EffectRecord *state, ObjectPosition *position)
{
    u16 countdown;

    D_80025630 = 1;
    if ((s16)(u16)position->z.w.i <
        (s16)sample_terrain_surface_height((u16)position->x.w.i, (u16)position->y.w.i,
                      (s16)((u16)position->z.w.i + 2))) {
        position->z.v += 0x20000 + (rand() & 0xFFF);
    }

    countdown = state->timer - 8;
    state->timer = countdown;
    if ((s32)(countdown << 16) <= 0) {
        ((ObjectNodeHeader *)state - 1)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

/* Retail 8190AC70 (handle_retail_n_8190_ac_70_callee_80024470_spawn_effect_under_parent_node_placed_parent): spawn an effect object under the parent node, placed at the parent's
 * position plus a random jitter (0..31 per axis) and the given offsets (minus half the jitter range). */
void handle_retail_n_8190_ac_70_callee_80024470_spawn_effect_under_parent_node_placed_parent(ObjectNodeHeader *parent, s16 field_34, s32 field_28, s16 field_52, s16 offset_x,
                   s16 offset_y, s16 offset_z) {
    ObjectNodeHeader *source_obj = parent;
    u32 saved_field_28 = field_28;
    s16 saved_field_52 = field_52;
    ObjectNodeHeader *spawned;
    PointRecord *fields;
    s32 jitter_x;
    s32 jitter_y;
    s32 jitter_z;
    s16 bias_x;
    s16 bias_y;
    s16 bias_z;
    s16 position_x;
    s16 position_y;
    s16 position_z;
    ObjectPosition *dest_x;
    ObjectPosition *dest_y;
    ObjectPosition *dest_z;

    /* the parent's next slot is the list head the new node links behind */
    spawned = allocate_list_node(0x211, (ObjectNodeHeader **)source_obj);
    if (spawned != 0) {
        spawned->update_callback = (void *)handle_raise_position_toward_queried_height_set_flags_countdown_expires;
        jitter_x = rand() & 0x1F;
        position_x = source_obj->position->x.w.i;
        dest_x = spawned->position;
        position_x += jitter_x;
        bias_x = offset_x - 0x10;
        position_x += bias_x;
        dest_x->x.w.i = position_x;

        jitter_y = rand() & 0x1F;
        position_y = source_obj->position->y.w.i;
        dest_y = spawned->position;
        position_y += jitter_y;
        bias_y = offset_y - 0x10;
        position_y += bias_y;
        dest_y->y.w.i = position_y;

        jitter_z = rand();
        jitter_z &= 0x1F;
        position_z = source_obj->position->z.w.i;
        fields = (PointRecord *)(spawned + 1);
        dest_z = spawned->position;
        position_z += jitter_z;
        bias_z = offset_z - 0x10;
        position_z += bias_z;
        dest_z->z.w.i = position_z;
        fields->unk_14 = field_34;
        fields->brightness = saved_field_52;
        register_node(spawned, draw_dimmed_height_effect_points);
        fields->color = saved_field_28;
    }
}

/* Returns a random value in [0, limit), or zero when limit is zero. Rejection sampling: the rand() bits are masked
 * to the smallest bit range that covers limit (2, 4, 6, 8, 12 or 16 bits) and redrawn until below limit. */
s32 get_a_random_in_n_0_limit_zero_limit_zero_rejection_sampling(s32 limit) {
    s32 sample;

    sample = 0;
    if (limit != 0) {
        if (limit < 5) {
            do {
                sample = (rand() & 0xC) >> 2;
            } while (sample >= limit);
            return sample;
        }
        if (limit < 0x11) {
            do {
                sample = (rand() & 0xF0) >> 4;
            } while (sample >= limit);
            return sample;
        }
        if (limit < 0x41) {
            do {
                sample = (rand() & 0xFC) >> 2;
            } while (sample >= limit);
            return sample;
        }
        if (limit < 0x101) {
            do {
                sample = (rand() & 0xFF0) >> 4;
            } while (sample >= limit);
            return sample;
        }
        if (limit < 0x1001) {
            do {
                sample = rand() & 0xFFF;
            } while (sample >= limit);
            return sample;
        }
        do {
            sample = rand() & 0xFFFF;
        } while (sample >= limit);
    }

    return sample;
}

typedef struct S_8190AEB4_0 {
    union { s16 s; u16 u; u16 p; } unk_00;   /* accessed as both */
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2C];
    union { void * s; u8 * u; } unk_30;   /* accessed as both */
    void * unk_34;
} S_8190AEB4_0;   /* arg0 in advance_the_animation_draws_rectangles_in_randomized_order */

typedef struct S_8190AEB4_1 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
} S_8190AEB4_1;   /* arg2 in advance_the_animation_draws_rectangles_in_randomized_order */

typedef struct S_8190AEB4_2 {
    u8 pad_00[0x90];
    s16 unk_90;
} S_8190AEB4_2;   /* ((S_8190AEB4_0 *)arg0)->unk_34 in advance_the_animation_draws_rectangles_in_randomized_order */

/*
 * Moves and rescales the captured sprite through staged motion, then shuffles 48 column indices
 * and 44 row indices to clear its VRAM area over 44 updates. Signals the linked state and flags
 * removal when the clearing sequence finishes.
 */
void advance_the_animation_draws_rectangles_in_randomized_order(void *effect, s32 *position, void *transform)
{
    Rect rect;
    Rect draw_rect;
    Point center;
    s32 *source_position;
    u8 *model;
    s16 timer;
    u16 next_x;
    u16 next_y;
    s32 entry;
    u8 *shuffle_order;
    u8 *slot;
    u8 *slot_2;
    u8 saved_entry;
    s32 order_index;
    s32 state;
    u16 next_state;

    rect = D_80024038;
    draw_rect = rising_effect_texture_rect;
    state = ((S_8190AEB4_0 *)effect)->unk_00.s;
    D_80025630 = 1;

    switch (state) {
    case 0:
        center.x = rect.x + ((s16)rect.w >> 1);
        center.y = rect.y + 0x48;
        draw_transformed_sprite_with_clip_rect(((S_8190AEB4_0 *)effect)->unk_30.s, &rect, &center, 1, 1);

        model = ((S_8190AEB4_0 *)effect)->unk_30.u;
        source_position = *(s32 **)(model - 0x18);
        position[0] = source_position[0];
        position[1] = source_position[1];
        position[2] = source_position[2];

        ((S_8190AEB4_1 *)transform)->unk_1C -= 0x20;
        ((S_8190AEB4_1 *)transform)->unk_1E += 0x80;
        timer = ((S_8190AEB4_0 *)effect)->unk_02.s + 1;
        ((S_8190AEB4_0 *)effect)->unk_02.s = timer;
        if (timer < 0x28) {
            return;
        }
        next_state = ((S_8190AEB4_0 *)effect)->unk_00.u;
        ((S_8190AEB4_0 *)effect)->unk_02.s = 0;
        next_state++;
        ((S_8190AEB4_0 *)effect)->unk_00.p = next_state;
        return;

    case 1:
        ((S_8190AEB4_1 *)transform)->unk_1C += 0x140;
        position[2] -= 0x140000;
        ((S_8190AEB4_1 *)transform)->unk_1E -= 0x500;
        timer = ((S_8190AEB4_0 *)effect)->unk_02.s + 1;
        ((S_8190AEB4_0 *)effect)->unk_02.s = timer;
        if (timer < 4) {
            return;
        }
        next_state = ((S_8190AEB4_0 *)effect)->unk_00.u;
        ((S_8190AEB4_0 *)effect)->unk_02.s = 0;
        next_state++;
        ((S_8190AEB4_0 *)effect)->unk_00.p = next_state;
        return;

    case 2:
        position[2] -= 0x100000;
        next_y = ((S_8190AEB4_1 *)transform)->unk_1E - 0x200;
        next_x = ((S_8190AEB4_1 *)transform)->unk_1C + 0x200;
        ((S_8190AEB4_1 *)transform)->unk_1E = next_y;
        ((S_8190AEB4_1 *)transform)->unk_1C = next_x;
        next_state = ((S_8190AEB4_0 *)effect)->unk_00.u;
        next_state++;
        ((S_8190AEB4_0 *)effect)->unk_00.p = next_state;
        return;

    case 3:
        position[2] += 0x180000;
        next_y = ((S_8190AEB4_1 *)transform)->unk_1E + 0x300;
        next_x = ((S_8190AEB4_1 *)transform)->unk_1C - 0x300;
        ((S_8190AEB4_1 *)transform)->unk_1E = next_y;
        ((S_8190AEB4_1 *)transform)->unk_1C = next_x;
        next_state = ((S_8190AEB4_0 *)effect)->unk_00.u;
        next_state++;
        ((S_8190AEB4_0 *)effect)->unk_00.p = next_state;
        return;

    case 4:
        position[2] -= 0x80000;
        next_y = ((S_8190AEB4_1 *)transform)->unk_1E - 0x100;
        next_x = ((S_8190AEB4_1 *)transform)->unk_1C + 0x100;
        ((S_8190AEB4_1 *)transform)->unk_1E = next_y;
        ((S_8190AEB4_1 *)transform)->unk_1C = next_x;
        next_state = ((S_8190AEB4_0 *)effect)->unk_00.u;
        next_state++;
        ((S_8190AEB4_0 *)effect)->unk_00.p = next_state;
        return;

    case 5:
    {
        u8 *cursor;

        entry = 0x2F;
        cursor = D_80025648;
        cursor += 0x2F;
        do {
            *cursor = entry;
            entry--;
            cursor--;
        } while (entry >= 0);
    }
        {
            u8 *cursor;

            entry = 0x2B;
            cursor = D_80025678;
            cursor += 0x2B;
            do {
                *cursor = entry;
                entry--;
                cursor--;
            } while (entry >= 0);
        }

        for (entry = 0; entry < 0x30; entry++) {
            shuffle_order = D_80025648;
            slot_2 = shuffle_order + entry;
            saved_entry = *slot_2;
            order_index = get_a_random_in_n_0_limit_zero_limit_zero_rejection_sampling(0x30);
            *slot_2 = shuffle_order[order_index];
            shuffle_order[order_index] = saved_entry;
        }
        for (entry = 0; entry < 0x2C; entry++) {
            shuffle_order = D_80025678;
            slot = shuffle_order + entry;
            saved_entry = *slot;
            order_index = get_a_random_in_n_0_limit_zero_limit_zero_rejection_sampling(0x2C);
            *slot = shuffle_order[order_index];
            shuffle_order[order_index] = saved_entry;
        }

        D_80025638[0] = 0;
        D_80025638[1] = 0;
        D_80025638[2] = 0;
        D_80025638[3] = 0;
        ((S_8190AEB4_0 *)effect)->unk_02.s = 0;
        ((S_8190AEB4_0 *)effect)->unk_00.p++;
                        /* fallthrough */

    case 6:
    {
        s32 *draw_data;

        entry = 0;
        do {
            draw_rect.x = D_80025648[entry] * 2 + 0x340;
            order_index = entry + ((S_8190AEB4_0 *)effect)->unk_02.u;
            if (order_index >= 0x2C) {
                order_index -= 0x2C;
            }
            draw_data = D_80025638;
            draw_rect.y = D_80025678[order_index] * 2 + 0x100;
            LoadImage(&draw_rect, draw_data);
            entry++;
        } while (entry < 0x30);

        timer = ((S_8190AEB4_0 *)effect)->unk_02.s + 1;
        ((S_8190AEB4_0 *)effect)->unk_02.s = timer;
        if (timer < 0x2C) {
            return;
        }
        ((S_8190AEB4_2 *)(((S_8190AEB4_0 *)effect)->unk_34))->unk_90 = 1;
        (*(u16 *)((u8 *)effect + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        break;
    }
    }
}

const CoordTable rising_effect_octant_offsets = {{{32,0},{32,32},{0,32},{-32,32},{-32,0},{-32,65504},{0,65504},{32,65504}}};

typedef struct S_func_8190B2D0_0 {
    void * unk_0;
    void * unk_4;
    u8 pad_8[0x1];
    u8 unk_9;
    union {
        s16 s16;
        u16 u16;
    } unk_A;
    u8 pad_C[0x6C];
    union {
        s16 s16;
        u16 u16;
    } unk_78;
    u8 unk_7A;
    union {
        s8 s8;
        u8 u8;
    } unk_7B;
    u8 pad_7C[0x2];
    union {
        s16 s16;
        u16 u16;
    } unk_7E;
    u8 pad_80[0x2];
    union {
        s16 s16;
        u16 u16;
    } unk_82;
    u8 pad_84[0x4];
    s16 unk_88;
    s16 unk_8A;
    u8 pad_8C[0x4];
    union {
        s16 s16;
        u16 u16;
    } unk_90;
    u8 pad_92[0x4];
    Packed12 unk_96;
    u8 unk_A2;
    u8 unk_A3;
} S_func_8190B2D0_0;

typedef struct S_func_8190B2D0_1 {
    u8 pad_0[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0xE];
    s8 unk_72;
    s8 unk_73;
    u8 pad_74[0x14];
    u16 unk_88;
} S_func_8190B2D0_1;

typedef struct S_func_8190B2D0_2 {
    u8 pad_0[0x8];
    void * unk_8;
    void * unk_C;
    u8 pad_10[0xE];
    u16 unk_1E;
} S_func_8190B2D0_2;

typedef struct S_func_8190B2D0_3 {
    union {
        u32 u32;
        struct {
            u8 pad_0[0x2];
            u16 unk_2;
        } at_2_u16;
    } unk_0;
    union {
        u32 u32;
        struct {
            u8 pad_4[0x2];
            u16 unk_6;
        } at_6_u16;
    } unk_4;
    union {
        u32 u32;
        struct {
            u8 pad_8[0x2];
            u16 unk_A;
        } at_A_u16;
    } unk_8;
} S_func_8190B2D0_3;

typedef struct S_func_8190B2D0_4 {
    union {
        s32 s32;
        struct {
            u8 pad_0[0x2];
            u16 unk_2;
        } at_2_u16;
    } unk_0;
    union {
        s32 s32;
        struct {
            u8 pad_4[0x2];
            u16 unk_6;
        } at_6_u16;
    } unk_4;
    union {
        s32 s32;
        void * ptr;
        struct {
            u8 pad_8[0x2];
            s16 unk_A;
        } at_A_s16;
        struct {
            u8 pad_8[0x2];
            u16 unk_A;
        } at_A_u16;
    } unk_8;
    union {
        s32 s32;
        void * ptr;
    } unk_C;
    union {
        s32 s32;
        void * ptr;
    } unk_10;
    s32 unk_14;
    u8 pad_18[0x28];
    Packed12 unk_40;
} S_func_8190B2D0_4;

typedef struct S_func_8190B2D0_5 {
    u8 pad_0[0x6];
    u16 unk_6;
    void * unk_8;
    union {
        u32 u32;
        u8 u8;
        struct {
            u8 pad_C[0x1];
            u8 unk_D;
        } at_D_u8;
        struct {
            u8 pad_C[0x2];
            u8 unk_E;
        } at_E_u8;
    } unk_C;
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x4];
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
} S_func_8190B2D0_5;

typedef struct S_func_8190B2D0_6 {
    u8 pad_0[0x13];
    u8 unk_13;
    u32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
} S_func_8190B2D0_6;

typedef struct S_func_8190B2D0_7 {
    u8 pad_0[0xA];
    u16 unk_A;
    u16 unk_C;
    u8 pad_E[0x1E];
    void * unk_2C;
    void * unk_30;
    void * unk_34;
} S_func_8190B2D0_7;

typedef struct S_func_8190B2D0_9 {
    u8 pad_0[0x4];
    u16 unk_4;
} S_func_8190B2D0_9;

/* Updates a moving effect, its target animation, and cleanup state. */
void update_a_moving_effect_target_animation_cleanup_state(S_func_8190B2D0_0 *effect, void *motion_arg, void *sprite_arg)
{
    s16 start_offset[3];
    Rect capture_rect;
    Point capture_point;
    CoordTable directions;
    S_func_8190B2D0_1 *owner;
    u8 * owner_base;
    register u32 source_pos;
    s32 state;
    S_func_8190B2D0_3 *target_pos;
    S_func_8190B2D0_4 *motion_or_child = motion_arg;
    SpriteFrameState *sprite = sprite_arg;

    owner = effect->unk_0;
    capture_rect = D_80024038;
    directions = rising_effect_octant_offsets;
    owner_base = ((u8 *)owner - 32);
    source_pos = (u32)((S_func_8190B2D0_2 *)owner_base)->unk_8;
    state = effect->unk_A.s16;

    switch (state) {
    case 0:
    {
        s16 owner_flags;
        u16 next_state;
        sprite->color.word = 0x00808080;
        effect->unk_96 = D_80025624;
        sprite->source = (u8 *)effect + 0x96;
        owner_flags = owner->unk_2A;
        D_80025630 = 1;
        next_state = effect->unk_A.u16;
        effect->unk_7E.u16 = (u16)(owner_flags >> 9) & 7;
        next_state++;
        effect->unk_A.u16 = next_state;
    }

    case 1:
    {
        s32 offset_ready;
        u16 next_state;
        u16 base_z;
        u16 base_height;
        S_func_8190B2D0_6 *target;
        S_func_8190B2D0_5 *owner_sprite;
        s32 target_z;
        s32 height_or_steps;
        s32 coordinate_steps;
        s32 target_coord;
        offset_ready = get_sprite_attachment_vector(((S_func_8190B2D0_5 *)((S_func_8190B2D0_2 *)owner_base)->unk_C)->unk_8,
                           ((S_func_8190B2D0_2 *)owner_base)->unk_C, start_offset, 0);
        if (offset_ready == 0 &&
            !(((S_func_8190B2D0_5 *)((S_func_8190B2D0_2 *)owner_base)->unk_C)->unk_14 & 0x8000)) {
            return;
        }
        motion_or_child->unk_0.at_2_u16.unk_2 = ((S_func_8190B2D0_3 *)source_pos)->unk_0.at_2_u16.unk_2;
        motion_or_child->unk_4.at_6_u16.unk_6 = ((S_func_8190B2D0_3 *)source_pos)->unk_4.at_6_u16.unk_6;
        base_z = ((S_func_8190B2D0_3 *)source_pos)->unk_8.at_A_u16.unk_A;
        motion_or_child->unk_8.at_A_u16.unk_A = base_z;
        if (!(((S_func_8190B2D0_5 *)((S_func_8190B2D0_2 *)owner_base)->unk_C)->unk_14 & 0x8000)) {
            motion_or_child->unk_0.at_2_u16.unk_2 += start_offset[0];
            motion_or_child->unk_4.at_6_u16.unk_6 += start_offset[1];
            motion_or_child->unk_8.at_A_u16.unk_A += start_offset[2];
        } else {
            motion_or_child->unk_8.at_A_u16.unk_A =
                (u16)(base_z - 64);
        }

        if (((u16 *)effect->unk_4)[0] & 0x80) {
            if (!(effect->unk_7A & 4)) {
                register_node((u8 *)effect - 32, project_sprite_chain);
                sprite->color.c.b = 20;
                sprite->color.c.g = 20;
                sprite->color.c.r = 20;
                sprite->flags |= 0xC;
                sprite->tpage_abr = 0;
                sprite->scale_y = 0x800;
                sprite->scale_x = 0x800;
                effect->unk_7A |= 4;
            }
        } else {
            return;
        }

        target = owner->unk_60;
        if (target != 0) {
            target_pos = ((S_func_8190B2D0_2 *)((u8 *)target - 32))->unk_8;
            height_or_steps = entity_height_offsets[target->unk_13] + 32;
            target_z = target_pos->unk_8.at_A_u16.unk_A - height_or_steps;
            effect->unk_78.u16 = (u16)target_z;
            owner_sprite = ((S_func_8190B2D0_2 *)((u8 *)owner - 32))->unk_C;
            effect->unk_A2 =
                owner_sprite->unk_24 +
                ((u8 *)dir_step_x)[(s16)effect->unk_7E.s16 * 2];
            effect->unk_A3 =
                owner_sprite->unk_25 +
                ((u8 *)dir_step_y)[(s16)effect->unk_7E.s16 * 2];

            coordinate_steps = owner->unk_72;
            target_coord = owner_sprite->unk_24;
            if (coordinate_steps != target_coord) {
                coordinate_steps -= target_coord;
            } else {
                coordinate_steps = owner->unk_73;
                target_coord = owner_sprite->unk_25;
                coordinate_steps -= target_coord;
            }
            coordinate_steps = __builtin_abs(coordinate_steps);
            effect->unk_7B.u8 = (u8)((coordinate_steps << 1) - 1);
        } else {
            base_height = owner->unk_88;
            effect->unk_7B.u8 = 32;
            effect->unk_78.u16 = (u16)(base_height - 80);
        }

        motion_or_child->unk_C.s32 =
            (s32)directions.value[effect->unk_7E.s16].x << 16;
        motion_or_child->unk_10.s32 =
            (s32)directions.value[effect->unk_7E.s16].y << 16;
        motion_or_child->unk_14 =
            (((s32)effect->unk_78.s16 << 16) - motion_or_child->unk_8.s32) /
            (s8)effect->unk_7B.u8;
        effect->unk_82.u16 = 0;
        next_state = effect->unk_A.u16 + 1;
        effect->unk_A.u16 = next_state;
        effect->unk_88 = (s16)(s8)effect->unk_7B.u8;
        effect->unk_8A =
            (s16)((s8)effect->unk_7B.u8 *
                  (s8)effect->unk_7B.u8);
        return;
    }

    case 2:
    {
        u32 particle_index;
        u8 frames_left;
        s32 elapsed_frames;
        s32 elapsed_frames_2;
        s32 elapsed_frames_3;
        s32 collision;
        particle_index = 0;
        do {
            s32 particle_shade;
            s32 random_bits = rand();
            particle_shade = (random_bits & 0xFF) | 0x80;
            handle_retail_n_8190_ac_70_callee_80024470_spawn_effect_under_parent_node_placed_parent((u8 *)effect - 32, effect->unk_7E.s16,
                          0x00202020, particle_shade, 0, 0, 0);
            particle_index++;
        } while ((s32)particle_index < 4);
        {
            u16 angle = sprite->angle_z + 400;
            sprite->angle_z = angle;
            if ((u16)angle >= 0x1001) {
                sprite->angle_z =
                    (u16)(angle - 4096);
            }
        }
        elapsed_frames = effect->unk_88 - effect->unk_7B.s8 + 1;
        sprite->color.c.r = (u8)((elapsed_frames * elapsed_frames * 108) /
                                effect->unk_8A + 20);
        elapsed_frames_2 = effect->unk_88 - effect->unk_7B.s8 + 1;
        sprite->color.c.g = (u8)((elapsed_frames_2 * elapsed_frames_2 * 108) /
                                    effect->unk_8A + 20);
        elapsed_frames_3 = effect->unk_88 - effect->unk_7B.s8 + 1;
        sprite->color.c.b = (u8)((elapsed_frames_3 * elapsed_frames_3 * 108) /
                                    effect->unk_8A + 20);
        collision = check_adjacent_tile_height_clearance(motion_or_child->unk_0.at_2_u16.unk_2, motion_or_child->unk_4.at_6_u16.unk_6,
                                  motion_or_child->unk_8.at_A_s16.unk_A, owner->unk_60);
        if ((collision << 16) != 0) {
            effect->unk_A.u16 = 8;
            effect->unk_82.u16 = 0;
            sprite->color.c.b = 0;
            sprite->color.c.g = 0;
            sprite->color.c.r = 0;
            sprite->scale_y = 0;
            sprite->scale_x = 0;
            return;
        }
        frames_left = effect->unk_7B.u8 - 1;
        effect->unk_7B.u8 = frames_left;
        if ((s8)frames_left <= 0) {
            if (owner->unk_60 != 0) {
                effect->unk_A.u16 = 3;
                effect->unk_82.u16 = 0;
                play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
                ((S_func_8190B2D0_6 *)owner->unk_60)->unk_14 |= 0x100000;
                target_pos = ((S_func_8190B2D0_2 *)((u8 *)owner->unk_60 - 32))->unk_8;
                motion_or_child->unk_0.at_2_u16.unk_2 = target_pos->unk_0.at_2_u16.unk_2;
                motion_or_child->unk_4.at_6_u16.unk_6 = target_pos->unk_4.at_6_u16.unk_6;
                motion_or_child->unk_8.at_A_u16.unk_A = effect->unk_78.u16;
                return;
            }
            effect->unk_A.u16 = 8;
            effect->unk_82.u16 = 0;
            sprite->color.c.b = 0;
            sprite->color.c.g = 0;
            sprite->color.c.r = 0;
            sprite->scale_y = 0;
            sprite->scale_x = 0;
            return;
        }
        motion_or_child->unk_0.s32 += motion_or_child->unk_C.s32;
        motion_or_child->unk_4.s32 += motion_or_child->unk_10.s32;
        motion_or_child->unk_8.s32 += motion_or_child->unk_14;
        return;
    }

    case 3:
    {
        ObjectPosition *child_pos;
        u8 * child_data;
        s32 frame;
        void *child_object;
        S_func_8190B2D0_6 *target;
        s32 current_frame;
        u32 spawn_frame;
        {
            u16 angle = sprite->angle_z + 400;
            sprite->angle_z = angle;
            if ((u16)angle >= 0x1001) {
                sprite->angle_z =
                    (u16)(angle - 4096);
            }
        }
        effect->unk_82.u16++;
        frame = effect->unk_82.s16;
        if (frame == 1) {
            capture_point.x = capture_rect.x + ((s16)capture_rect.w >> 1);
            capture_point.y = capture_rect.y + 72;
            draw_transformed_sprite_with_clip_rect(owner->unk_60, &capture_rect, &capture_point, 1,
                          frame);
        }
        spawn_frame = effect->unk_82.s16;
        if ((s16)spawn_frame != 4) {
            return;
        }
        {
            motion_or_child = allocate_flagged_object_node(0x212);
            if (motion_or_child != 0) {
                child_object = motion_or_child;
                child_data = ((u8 *)motion_or_child + 32);
                ((S_func_8190B2D0_7 *)child_data)->unk_2C = owner;
                ((S_func_8190B2D0_7 *)child_data)->unk_30 = owner->unk_60;
                ((S_func_8190B2D0_7 *)child_data)->unk_34 = effect;
                motion_or_child->unk_10.ptr = advance_the_animation_draws_rectangles_in_randomized_order;
                register_node(child_object, project_sprite_chain);
                sprite = motion_or_child->unk_C.ptr;
                sprite->tpage_abr = 32;
                sprite->depth_bias = 6;
                sprite->flags |= 0xC;
                child_pos = motion_or_child->unk_8.ptr;
                ((S_func_8190B2D0_7 *)child_data)->unk_A = 0;
                ((S_func_8190B2D0_7 *)child_data)->unk_C = 0;
                target = owner->unk_60;
                target_pos = ((S_func_8190B2D0_2 *)((u8 *)target - 32))->unk_8;
                child_pos->x.v = target_pos->unk_0.u32;
                child_pos->y.v = target_pos->unk_4.u32;
                child_pos->z.v = target_pos->unk_8.u32;
                sprite = motion_or_child->unk_C.ptr;
                sprite->scale_y = 0x1000;
                sprite->scale_x = 0x1000;
                sprite->color.c.b = 0x80;
                sprite->color.c.g = 0x80;
                sprite->color.c.r = 0x80;
                motion_or_child->unk_40 = D_80025618;
                sprite->source = (u8 *)motion_or_child + 64;
                ((S_func_8190B2D0_9 *)sprite->source)->unk_4 =
                    GetTPage(2, 1, 0x340, 0x100);
            }
        }
        current_frame = effect->unk_82.s16;
        if (current_frame != (s16)spawn_frame) {
            return;
        }
        effect->unk_A.u16 = current_frame;
        effect->unk_82.u16 = 0;
        effect->unk_90.u16 = 0;
        return;
    }

    case 4:
    {
        s32 fade_frame;
        s32 green_frame;
        S_func_8190B2D0_6 *target;
        S_func_8190B2D0_5 *target_sprite;
        effect->unk_82.u16 = effect->unk_82.u16 + 1;
        {
            u16 angle = sprite->angle_z + 400;
            sprite->angle_z = angle;
            if ((u16)angle >= 0x1001) {
                sprite->angle_z =
                    (u16)(angle - 4096);
            }
        }
        if (effect->unk_82.s16 < 42) {
            motion_or_child->unk_8.s32 -= 0x20000;
        }
        if (effect->unk_82.s16 == 81) {
            sprite->tpage_abr = 32;
            sprite->color.c.r = 54;
            sprite->color.c.g = 54;
            sprite->color.c.b = 54;
        }
        if (effect->unk_82.s16 >= 81) {
            fade_frame = effect->unk_82.s16;
            sprite->color.c.r = (u8)(((100 - fade_frame) * 54) / 20);
            green_frame = effect->unk_82.s16;
            sprite->color.c.g = (u8)(((100 - green_frame) * 54) / 20);
            fade_frame = effect->unk_82.s16;
            sprite->color.c.b = (u8)(((100 - fade_frame) * 54) / 20);
        }
        if (effect->unk_82.s16 >= 0) {
            target = owner->unk_60;
            target->unk_1C |= 0x10000000;
            target_sprite = ((S_func_8190B2D0_2 *)((u8 *)target - 32))->unk_C;
            if (effect->unk_82.s16 >= 43) {
                if (effect->unk_82.s16 < 64) {
                    target_sprite->unk_C.at_E_u8.unk_E += 3;
                    target_sprite->unk_C.at_D_u8.unk_D += 3;
                    target_sprite->unk_C.u8 += 3;
                }
            } else {
                if (effect->unk_82.s16 == 41) {
                    target_sprite->unk_C.at_E_u8.unk_E -= 60;
                    target_sprite->unk_C.at_D_u8.unk_D -= 60;
                    target_sprite->unk_C.u8 -= 60;
                }
            }
        }
        if (effect->unk_82.s16 >= 100) {
            S_func_8190B2D0_6 *finished_target;
            u32 clear_tint_mask;
            clear_tint_mask = 0xEFFFFFFF;
            finished_target = owner->unk_60;
            finished_target->unk_1C &= clear_tint_mask;
            target_sprite = ((S_func_8190B2D0_2 *)((u8 *)finished_target - 32))->unk_C;
            target_sprite->unk_C.at_E_u8.unk_E = 128;
            target_sprite->unk_C.at_D_u8.unk_D = 128;
            target_sprite->unk_C.u8 = 128;
            effect->unk_A.u16++;
        }
        return;
    }

    case 5:
    {
        S_func_8190B2D0_6 *target;
        u8 target_mode;
        u32 clear_effect_mask;
        s32 effect_kind;
        if (effect->unk_90.s16 != 0) {
            clear_effect_mask = 0xFFEFFFFF;
            effect_kind = 255;
            target = owner->unk_60;
            target_mode = current_spell_effect_variant[0];
            target->unk_14 &= clear_effect_mask;
            if (target_mode != effect_kind) {
                effect_kind = effect->unk_9;
            }
            try_lower_actor_level(owner->unk_60, effect_kind, owner);
            effect->unk_A.u16 = 8;
            effect->unk_82.u16 = 30;
        }
        return;
    }

    case 8:
    {
        s16 old_frame;
        s16 frame;
        s32 cleanup_pending;
        old_frame = effect->unk_82.u16;
        frame = old_frame + 1;
        effect->unk_82.u16 = frame;
        if ((s16)frame < 31) {
            break;
        }
        cleanup_pending = D_80025630;
        effect->unk_82.u16 = old_frame;
        switch (cleanup_pending) {
        case 0:
        {
            g_dungeon_status.active_actor = 0;
            ((ObjectNodeHeader *)((u8 *)effect - 0x20) )->flags|= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            break;
        }
        default:
            D_80025630 = 0;
            break;
        }
    }
    }
}
