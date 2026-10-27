/* Targeted ribbon motion, interpolated trail particles, and fading trail segments. */
#include "shared/object_node.h"
#include "dungeon/effect/particle.h"
#include "shared/sprite_frame_state.h"
/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "records/Rec_func_80167A98_arg0.h"
#include "records/Rec_func_80167A98_arg1.h"
#include "dungeon/system.h"

typedef struct S_80167C74_0_pre {
    u16 unk_00;
} S_80167C74_0_pre;   /* the 0x2 bytes before arg0 in update_targeted_ribbon_trail, addressed as arg0[-1] */

typedef struct S_80167C74_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80167C74_1;

typedef struct S_80167C74_4 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80167C74_4;

typedef struct S_80167C74_5 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80167C74_5;

typedef struct S_80167C74_6 {
    u8 pad_00[0x6];
    u16 unk_06;
} S_80167C74_6;

typedef struct S_80167C74_7 {
    u8 pad_00[0x8];
    u16 unk_08;
} S_80167C74_7;

typedef struct S_80167C74_8 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80167C74_8;

typedef struct S_80167C74_9 {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    u8 pad_0C[0xC];
    s16 unk_18;
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
    s16 unk_22;
} S_80167C74_9;

typedef struct S_80167C74_10 {
    u8 pad_00[0x18];
    s16 unk_18;
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
    s16 unk_22;
} S_80167C74_10;

typedef struct S_80167C74_11 {
    u8 pad_00[0xC];
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x1]; u8 v; } at01;
        struct { u8 pad[0x2]; u8 v; } at02;
    } unk_0C;   /* overlapping accesses */
} S_80167C74_11;   /* arg2 in update_targeted_ribbon_trail */

typedef struct S_80167C74_12 {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
} S_80167C74_12;

typedef struct S_80167C74_13 {
    u8 pad_00[0x18];
    s16 unk_18;
    s16 unk_1A;
} S_80167C74_13;

typedef struct S_80167C74_18 {
    s8 unk_00;
    s8 unk_01;
    s8 unk_02;
} S_80167C74_18;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u8 pad[0x5A];
} PositionTableEntry;

void select_record_entry_and_value(void *state_data, void *entry_data, short index);
void initialize_timed_motion_step(); /* Unprototyped: two or three arguments; retail reads only the first two. */
s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
struct EntityRec; void create_jittered_child_effect(struct EntityRec *, s32, s16, s16, s16, s16);
void create_ribbon_head_sprite();
extern u8 ribbon_sprite_entries[];
extern void D_80166D14();

extern PositionTableEntry ribbon_vertices[];

/* Narrows the input to a signed 16-bit result. */
static __inline__ s16 clamp_narrow(s32 value)
{
    return value;
}

/* Update trail motion, emit interpolated particles, and build fading trail segments. */
void update_targeted_ribbon_trail(void *effect_data, Rec_func_80167A98_arg1 *origin, S_80167C74_11 *color) {
    u8 *motion_table;
    u8 *table_join;
    u8 *clamp_base;
    s16 *clamp_coord;
    s16 life_left;
    s32 trail_index;
    s32 scaled_z;
    s32 velocity_y;
    s32 copy_axis_offset;
    s32 object_axis_offset;
    void *effect_object;
    s32 color_weight;
    s16 particle_life;
    s32 step_y;
    s32 delta_x;
    s32 delta_z;
    s32 delta_y;
    s32 object_limit;
    s32 step_z;
    s32 step_x;
    s32 move_x0;
    s32 move_y0;
    s32 move_z0;
    s32 move_x1;
    s32 move_y1;
    s32 move_z1;
    s32 clamp_axis;
    s32 copy_axis;
    s32 object_axis;
    s32 phase_threshold;
    s32 copy_pair_offset;
    s32 copy_pair_stride;
    s32 particle_count;
    s32 history_index;
    s32 sum_x;
    s32 sum_y;
    s32 object_index;
    s32 sum_z;
    s32 history_offset;
    s32 limit_offset;
    s32 table_offset;
    u8 *copy_row_offset;
    s32 clamp_pair;
    s32 copy_pair;
    s32 object_pair;
    s32 scaled_red;
    s32 scaled_green;
    s32 scaled_blue;
    u16 *pos_x0;
    u16 *object_pos;
    u16 *object_prev_pos;
    u16 copy_value;
    s16 phase_tick;
    SpriteFrameState *object_flags;
    SpriteFrameState *object_render;
    S_80167C74_4 *pos_y0;
    S_80167C74_5 *pos_z0;
    S_80167C74_6 *pos_x1;
    S_80167C74_7 *pos_y1;
    S_80167C74_8 *pos_z1;
    u8 *object_data;
    S_80167C74_1 *target_pos;
    u8 *copy_row;
    S_80167C74_9 *trail_row;
    ObjectNodeHeader *object;
    u8 *interp_row;
    u8 *head_pos;
    s32 table_base;
    u8 *case_base;
    u8 *interp_base;
    u8 *copy_dst;
    u8 *copy_src;
    u8 *object_table_base;
    u8 *object_base;
    ObjectPosition *object_origin;
    s32 object_offset;
    s32 object_copy_index;

    target_pos = ((Rec_func_80167A98_arg0 *)effect_data)->unk_24;
    switch (((s16)(((Rec_func_80167A98_arg0 *)effect_data)->unk_12))) {
    case 0:
        velocity_y = ((Rec_func_80167A98_arg0 *)effect_data)->unk_60;
        phase_threshold = 0;
        ((Rec_func_80167A98_arg0 *)effect_data)->unk_5C =
            (s32) ((((Rec_func_80167A98_arg0 *)effect_data)->unk_5C * 4) / 5);
        trail_index = ((Rec_func_80167A98_arg0 *)effect_data)->unk_1C;
        ((Rec_func_80167A98_arg0 *)effect_data)->unk_60 = (s32) ((velocity_y * 4) / 5);
        ((Rec_func_80167A98_arg0 *)effect_data)->unk_64 =
            (s32) ((((Rec_func_80167A98_arg0 *)effect_data)->unk_64 * 4) / 5);
        if (trail_index == 0)
            phase_threshold = 0x46;
        if (trail_index == 1)
            phase_threshold = 0x32;
        if (trail_index == 2)
            phase_threshold = 0x1E;
        motion_table = (u8 *)0x80170000;
        if (phase_threshold >= ((Rec_func_80167A98_arg0 *)effect_data)->unk_18) {
            ((Rec_func_80167A98_arg0 *)effect_data)->unk_12 =
                (s16) ((u16) ((Rec_func_80167A98_arg0 *)effect_data)->unk_12 + 1);
            case_base = (u8 *)ribbon_vertices;
            ((Rec_func_80167A98_arg0 *)effect_data)->unk_68 = (s32) ((s32) ((target_pos->unk_00
                - (((Rec_func_80167A98_arg0 *)effect_data)->unk_5C * 0x14))
                - (origin->unk_00 + (*(s16 *)(case_base + (((Rec_func_80167A98_arg0 *)effect_data)->unk_1C * 0x60))
                << 0x11))) >> 7);
            ((Rec_func_80167A98_arg0 *)effect_data)->unk_6C = (s32) ((s32) ((target_pos->unk_04
                - (((Rec_func_80167A98_arg0 *)effect_data)->unk_60 * 0x14))
                - (origin->unk_04 + (*(s16 *)((((Rec_func_80167A98_arg0 *)effect_data)->unk_1C * 0x60) + case_base + 2)
                << 0x11))) >> 7);
            scaled_z = (((Rec_func_80167A98_arg0 *)effect_data)->unk_64 * 0x14) + 0x200000;
            ((Rec_func_80167A98_arg0 *)effect_data)->unk_70 = (s32) ((s32) ((target_pos->unk_08 - scaled_z)
                - (origin->unk_08 + (*(s16 *)((((Rec_func_80167A98_arg0 *)effect_data)->unk_1C * 0x60) + case_base + 4)
                << 0x11))) >> 7);
            ((Rec_func_80167A98_arg0 *)effect_data)->unk_1E = 0U;
            break;
        }
        break;
    case 1:
        phase_tick = ((Rec_func_80167A98_arg0 *)effect_data)->unk_1E + 1;
        ((Rec_func_80167A98_arg0 *)effect_data)->unk_1E = phase_tick;
        if (phase_tick == 0xC) {
            create_ribbon_head_sprite(effect_data, origin, color);
            ((PlayerRecord *)primary_actor_record)->unk_10C = (u16) (((PlayerRecord *)primary_actor_record)->unk_10C | 1);
            primary_actor_record->movement_facing = (s16) (((u16)primary_actor_record->facing) + 0x800);
            initialize_timed_motion_step(6, 0xC);
            play_sound_if_enabled(0x601);
        }
        if ((s16) ((Rec_func_80167A98_arg0 *)effect_data)->unk_1E >= 0x10) {
            ((Rec_func_80167A98_arg0 *)effect_data)->unk_18 = 0;
        }
        ((Rec_func_80167A98_arg0 *)effect_data)->unk_5C = (s32) (((Rec_func_80167A98_arg0 *)effect_data)->unk_5C
            + ((Rec_func_80167A98_arg0 *)effect_data)->unk_68);
        ((Rec_func_80167A98_arg0 *)effect_data)->unk_60 = (s32) (((Rec_func_80167A98_arg0 *)effect_data)->unk_60
            + ((Rec_func_80167A98_arg0 *)effect_data)->unk_6C);
        ((Rec_func_80167A98_arg0 *)effect_data)->unk_64 = (s32) (((Rec_func_80167A98_arg0 *)effect_data)->unk_64
            + ((Rec_func_80167A98_arg0 *)effect_data)->unk_70);
        break;
    default:
        motion_table = (u8 *)ribbon_vertices;
        goto update_positions;
    }

    motion_table = (u8 *)ribbon_vertices;
update_positions:
    table_join = motion_table;
    move_x0 = ((Rec_func_80167A98_arg0 *)effect_data)->unk_5C;
    pos_x0 = (u16 *)((((Rec_func_80167A98_arg0 *)effect_data)->unk_1C * 0x60) + (s32)table_join);
    if (move_x0 < 0)
        move_x0 += 0xFFFF;
    *pos_x0 += move_x0 >> 0x10;
    move_y0 = ((Rec_func_80167A98_arg0 *)effect_data)->unk_60;
    pos_y0 = (void *)((((Rec_func_80167A98_arg0 *)effect_data)->unk_1C * 0x60) + (s32)table_join);
    if (move_y0 < 0)
        move_y0 += 0xFFFF;
    pos_y0->unk_02 = (u16) (pos_y0->unk_02 + (move_y0 >> 0x10));
    move_z0 = ((Rec_func_80167A98_arg0 *)effect_data)->unk_64;
    pos_z0 = (void *)((((Rec_func_80167A98_arg0 *)effect_data)->unk_1C * 0x60) + (s32)table_join);
    if (move_z0 < 0)
        move_z0 += 0xFFFF;
    pos_z0->unk_04 = (u16) (pos_z0->unk_04 + (move_z0 >> 0x10));
    move_x1 = ((Rec_func_80167A98_arg0 *)effect_data)->unk_5C;
    pos_x1 = (void *)((((Rec_func_80167A98_arg0 *)effect_data)->unk_1C * 0x60) + (s32)table_join);
    if (move_x1 < 0)
        move_x1 += 0xFFFF;
    pos_x1->unk_06 = (u16) (pos_x1->unk_06 + (move_x1 >> 0x10));
    move_y1 = ((Rec_func_80167A98_arg0 *)effect_data)->unk_60;
    pos_y1 = (void *)((((Rec_func_80167A98_arg0 *)effect_data)->unk_1C * 0x60) + (s32)table_join);
    if (move_y1 < 0)
        move_y1 += 0xFFFF;
    pos_y1->unk_08 = (u16) (pos_y1->unk_08 + (move_y1 >> 0x10));
    move_z1 = ((Rec_func_80167A98_arg0 *)effect_data)->unk_64;
    pos_z1 = (void *)((((Rec_func_80167A98_arg0 *)effect_data)->unk_1C * 0x60) + (s32)table_join);
    if (move_z1 < 0)
        move_z1 += 0xFFFF;
    clamp_pair = 0;
    clamp_base = table_join;
    limit_offset = 0x190;
    pos_z1->unk_0A = (u16) (pos_z1->unk_0A + (move_z1 >> 0x10));
    do {
        clamp_axis = 0;
        do {
            clamp_coord = (s16 *)(clamp_axis * 2 + (clamp_pair * 6 + (((Rec_func_80167A98_arg0 *)effect_data)->unk_1C * 0x60 + (s32)clamp_base)));
            if (*clamp_coord >= 0x191)
                *clamp_coord = limit_offset;
            clamp_coord = (s16 *)(clamp_axis * 2 + (clamp_pair * 6 + (((Rec_func_80167A98_arg0 *)effect_data)->unk_1C * 0x60 + (s32)clamp_base)));
            if (*clamp_coord < -0x190)
                *clamp_coord = clamp_narrow(-0x190);
            clamp_axis += 1;
        } while (clamp_axis < 3);
        clamp_pair += 1;
    } while (clamp_pair < 2);
    history_index = 7;
    table_base = (s32)((u8 *)ribbon_vertices);
    limit_offset = 0x54;
loop_2:
    {
        copy_pair = 0;
        copy_row_offset = (u8 *)limit_offset;
        copy_pair_stride = copy_pair;
copy_pairs:
        copy_axis = 0;
        copy_pair_offset = copy_pair_stride;
        do {
            copy_axis_offset = copy_axis * 2;
            copy_axis += 1;
            copy_row = (u8 *)(((s32)copy_row_offset) + ((((Rec_func_80167A98_arg0 *)effect_data)->unk_1C * 0x60)
                + (s32)((u8 *)table_base)));
            copy_dst = (u8 *)(copy_pair_offset + (s32)copy_row);
            copy_row -= 0xC;
            copy_src = (u8 *)(copy_pair_offset + (s32)copy_row);
            copy_value = *(u16 *)(copy_axis_offset + (s32)copy_src);
            copy_axis_offset += (s32)copy_dst;
            *(u16 *)copy_axis_offset = copy_value;
        } while (copy_axis < 3);
        copy_pair += 1;
        copy_pair_stride += 6;
        if (copy_pair < 2)
            goto copy_pairs;
        history_index -= 1;
        limit_offset -= 0xC;
    }
    if (history_index > 0)
        goto loop_2;
    particle_count = 0xA;
    interp_base = (u8 *)ribbon_vertices;
    trail_row = (((Rec_func_80167A98_arg0 *)effect_data)->unk_1C * 0x60) + interp_base;
    delta_x = (trail_row->unk_00 + trail_row->unk_06) - (trail_row->unk_18 + trail_row->unk_1E);
    delta_y = (trail_row->unk_02 + trail_row->unk_08) - (trail_row->unk_1A + trail_row->unk_20);
    delta_z = (trail_row->unk_04 + trail_row->unk_0A) - (trail_row->unk_1C + trail_row->unk_22);
    if (((Rec_func_80167A98_arg0 *)effect_data)->unk_12 == 0)
        particle_count = 3;
    history_index = 1;
    if (history_index < (particle_count + 1)) {
        sum_z = delta_z;
        sum_y = delta_y;
        sum_x = delta_x;
        do {
            s32 interp_y0;
            s32 interp_y1;
            s32 interp_x1;
            s32 interp_z0;
            s32 interp_x0;
            s32 interp_z1;
            step_y = sum_y / particle_count;
            step_z = sum_z / particle_count;
            step_x = sum_x / particle_count;
            effect_object = effect_data - 0x20;
            particle_life = 0xA;
            interp_row = (((Rec_func_80167A98_arg0 *)effect_data)->unk_1C * 0x60) + (u8 *)ribbon_vertices;
            interp_y0 = ((S_80167C74_10 *)interp_row)->unk_1A;
            interp_y1 = ((S_80167C74_10 *)interp_row)->unk_20;
            interp_x1 = ((S_80167C74_10 *)interp_row)->unk_1E;
            interp_z0 = ((S_80167C74_10 *)interp_row)->unk_1C;
            interp_x0 = ((S_80167C74_10 *)interp_row)->unk_18;
            interp_z1 = ((S_80167C74_10 *)interp_row)->unk_22;
            create_jittered_child_effect(effect_object, color->unk_0C.at00.v, particle_life, (s16) (interp_x0 + interp_x1 + step_x),
                (s32) (s16) (interp_y0 + interp_y1 + step_y), (s32) (s16) (interp_z0 + interp_z1 + step_z));
            sum_z += delta_z;
            sum_y += delta_y;
            sum_x += delta_x;
            history_index += 1;
        } while (history_index < (particle_count + 1));
    }
    object_table_base = (u8 *)&ribbon_vertices;
    head_pos = (u8 *)((((Rec_func_80167A98_arg0 *)effect_data)->unk_1C * 0x60) + (s32)object_table_base);
    if ((((S_80167C74_12 *)head_pos)->unk_00 != 0x190) && (((S_80167C74_12 *)head_pos)->unk_02 != 0x190)
        && (((S_80167C74_12 *)head_pos)->unk_04 != 0x190)) {
        object_index = 0;
        object_limit = 8;
        object_base = object_table_base;
        history_offset = 0;
        do {
            object = allocate_flagged_object_node(0x212);
            if (object != NULL) {
                object_data = ((void *)object) + 0x20;
                ((S_80167C74_13 *)object_data)->unk_18 = 1;
                ((S_80167C74_13 *)object_data)->unk_1A = 1;
                object->update_callback = expire_ribbon_segment;
                register_node(object, &D_80166D14);
                object_flags = object->sprite;
                object_flags->tpage_abr = 0x20;
                object_flags->flags = (u16) (object_flags->flags | 0xC);
                object_origin = object->position;
                history_index = 0;
                object_origin->x.v = (s32) origin->unk_00;
                color_weight = object_limit - object_index;
                object_origin->y.v = (s32) origin->unk_04;
                object_origin->z.v = (s32) origin->unk_08;
                object_render = object->sprite;
                object_render->scale_y = 0x1000;
                object_render->scale_x = 0x1000;
                object_render->color.c.b = 0x80;
                object_render->color.c.g = 0x80;
                object_render->color.c.r = 0x80;
                do {
                    scaled_red = (u8) color->unk_0C.at00.v * color_weight;
                    ((S_80167C74_18 *)(object_data + history_index * 4))->unk_00 = (s8) (scaled_red / 8);
                    scaled_green = color->unk_0C.at01.v * color_weight;
                    ((S_80167C74_18 *)(object_data + history_index * 4))->unk_01 = (s8) (scaled_green / 8);
                    scaled_blue = color->unk_0C.at02.v * color_weight;
                    ((S_80167C74_18 *)(object_data + history_index * 4))->unk_02 = (s8) (scaled_blue / 8);
                    history_index += 1;
                } while (history_index < 4);
                object_render->depth_bias = 0;
                select_record_entry_and_value(object_render, ribbon_sprite_entries, 0);
                object_pair = 0;
                object_offset = history_offset;
                copy_row_offset = object_data;
                table_base = object_pair;
                do {
                    object_axis = 0;
                    table_offset = table_base;
                    object_prev_pos = copy_row_offset + 0x80;
                    object_pos = copy_row_offset + 0x74;
                    for (;;) {
                        object_axis_offset = object_axis * 2;
                        *object_pos = *(u16 *)(object_axis_offset + (table_offset + (object_offset
                            + ((((Rec_func_80167A98_arg0 *)effect_data)->unk_1C * 0x60) + (s32)object_base))));
                        object_axis += 1;
                        object_pos += 1;
                        object_copy_index = object_offset + ((((Rec_func_80167A98_arg0 *)effect_data)->unk_1C * 0x60)
                            + (s32)object_base);
                        object_copy_index += 0xC;
                        object_axis_offset += table_offset + object_copy_index;
                        *object_prev_pos = *(u16 *)object_axis_offset;
                        object_prev_pos += 1;
                        if (object_axis < 3)
                        continue;
                        copy_row_offset += 6;
                        object_pair += 1;
                        table_base += 6;

                        break;
                    }
                } while (object_pair < 2);
            }
            object_index += 1;
            history_offset += 0xC;
        } while (object_index < 7);
    }
    life_left = (u16) ((Rec_func_80167A98_arg0 *)effect_data)->unk_18 - 1;
    ((Rec_func_80167A98_arg0 *)effect_data)->unk_18 = life_left;
    if ((life_left << 0x10) <= 0) {
        ((S_80167C74_0_pre *)effect_data)[-1].unk_00 = (u16) (((S_80167C74_0_pre *)effect_data)[-1].unk_00 | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}
