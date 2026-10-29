#include "shared/sprite_frame_state.h"
#include "sdk/libc.h"
#include "dungeon/effect/particle.h"
/* One native TU; source order follows the complete ledger cohort. */
#include "dungeon/effect/particle/create_two_row_object_group.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/effect/particle.h"
#include "shared/object_node.h"
#include "common.h"
#include "engine/node/allocation.h"
#include "slus.h"
#include "dungeon/level.h"
#include "sdk/libgpu.h"
#include "engine/graphics.h"

extern s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */

typedef struct {
    u32 words[2];
} __attribute__((packed)) Copy8;

/* Creates up to sixteen objects in two rows with a shared payload. */
void create_two_row_object_group(void *payload, s16 value_scale) {
    s32 row = 1;
    s32 column;
    do {
        for (column = 7; column >= 0; column--) {
            ObjectNodeHeader *object = allocate_flagged_object_node(2);
            if (object != 0) {
                u8 *data = ((u8 *)object) + 0x20;
                *(s16 *)(((u8 *)object) + 0x20) = 0;
                *(s16 *)(data + 2) = 0x20;
                *(s16 *)(data + 8) = row;
                *(s16 *)(data + 0xA) = (column << 9) + (row == 0 ? 0x100 : 0);
                *(Copy8 *)(((u8 *)object) + 0x40) = *(Copy8 *)payload;
                *(s16 *)(data + 6) = GetClut(value_scale << 4, 0x1F8);
                object->update_callback = update_rotating_effect_vertices;
                register_node(object, draw_linked_textured_quads);
            }
        }
        row--;
    } while (row >= 0);
}
#include "common.h"
#include "shared/game_work.h"

typedef struct S_800DA93C_0 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_800DA93C_0;   /* base->unk0 in draw_linked_textured_quads */

typedef struct S_800DA93C_1_pre {
    s32 unk_00;
    u8 pad_04[0x4];
} S_800DA93C_1_pre;   /* the 0x8 bytes before walker in draw_linked_textured_quads, addressed as walker[-1] */

typedef struct S_800DA93C_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u16 unk_04;
    u16 unk_06;
} S_800DA93C_1;   /* walker in draw_linked_textured_quads */

typedef struct S_800DA93C_2 {
    u32 unk_00;
    s32 unk_04;
    u8 pad_08[0x4];
    s8 unk_0C;
    s8 unk_0D;
    u16 unk_0E;
    u8 pad_10[0x4];
    s8 unk_14;
    s8 unk_15;
    u16 unk_16;
    u8 pad_18[0x4];
    s8 unk_1C;
    s8 unk_1D;
    u8 pad_1E[0x6];
    s8 unk_24;
    s8 unk_25;
} S_800DA93C_2;   /* record in draw_linked_textured_quads */

typedef struct S_800DA93C_3 {
    u8 pad_00[0xB0];
    u32 unk_B0;
} S_800DA93C_3;   /* (u8 *)((u32)work + (u32)base->unk0) in draw_linked_textured_quads */

typedef struct S_800DA93C_4 {
    u8 pad_00[0xB0];
    u32 unk_B0;
} S_800DA93C_4;   /* (u8 *)work in draw_linked_textured_quads */

extern s32 RotTransPers();

/* Build textured quad packets from a linked list and insert them into the ordering table. */
s32 draw_linked_textured_quads(void *first_quad) {
    void *quad_data;
    void *packet;
    GameWork *render_state;
    s32 scratch;
    s32 depth;
    register s32 link_addr;
    s32 tile_index;
    s32 u_offset;
    s8 u_left;
    s8 u_right;
    s32 v_offset;
    s8 v_top;
    s8 v_bottom;
    u32 addr_mask;
    u32 tag_mask;

    quad_data = first_quad;
    render_state = &g_game_work;
    addr_mask = 0x00FFFFFF;
    tag_mask = 0xFF000000;

    do {
        packet = ((S_800DA93C_0 *)(render_state->draw_buffer))->unk_8D0;
        ((S_800DA93C_0 *)(render_state->draw_buffer))->unk_8D0 = (u8 *)packet + 0x28;

        depth = RotTransPers((u8 *)quad_data + 0x28,
                              (u8 *)packet + 8, &scratch, &scratch);
        depth += RotTransPers((u8 *)quad_data + 0x30,
                               (u8 *)packet + 0x10, &scratch, &scratch);
        depth += RotTransPers((u8 *)quad_data + 0x38,
                               (u8 *)packet + 0x18, &scratch, &scratch);
        depth += RotTransPers((u8 *)quad_data + 0x40,
                               (u8 *)packet + 0x20, &scratch, &scratch);
        depth = (depth >> 2) - 8;

        if ((u32)depth < 0x1E0U) {
            scratch = 0xFF - ((S_800DA93C_1 *)quad_data)->unk_02;
            ((S_800DA93C_2 *)packet)->unk_04 = (*(s32 *)((u8 *)quad_data + 0x10));
            SetPolyFT4(packet);
            SetSemiTrans(packet, 1);

            ((S_800DA93C_2 *)packet)->unk_16 = ((S_800DA93C_1 *)quad_data)->unk_04;
            ((S_800DA93C_2 *)packet)->unk_0E = ((S_800DA93C_1 *)quad_data)->unk_06;

            tile_index = (s16)(((S_800DA93C_1 *)quad_data)->unk_02 % 8);
            scratch = tile_index;

            u_offset = (tile_index % 4) << 5;
            u_left = u_offset - 0x80;
            u_right = u_offset - 0x61;
            ((S_800DA93C_2 *)packet)->unk_14 = u_left;
            ((S_800DA93C_2 *)packet)->unk_0C = u_left;
            ((S_800DA93C_2 *)packet)->unk_24 = u_right;
            ((S_800DA93C_2 *)packet)->unk_1C = u_right;

            v_offset = (scratch / 4) << 5;
            v_top = v_offset + 0x40;
            v_bottom = v_offset + 0x5F;
            ((S_800DA93C_2 *)packet)->unk_1D = v_top;
            ((S_800DA93C_2 *)packet)->unk_0D = v_top;
            ((S_800DA93C_2 *)packet)->unk_25 = v_bottom;
            ((S_800DA93C_2 *)packet)->unk_15 = v_bottom;

            link_addr = depth << 2;
            ((S_800DA93C_2 *)packet)->unk_00 =
                (((S_800DA93C_2 *)packet)->unk_00 & tag_mask) |
                (((S_800DA93C_3 *)((u8 *)((u32)link_addr + (unsigned long)render_state->draw_buffer)))->unk_B0 & addr_mask);
            link_addr += (s32)render_state->draw_buffer;
            ((S_800DA93C_4 *)((u8 *)link_addr))->unk_B0 =
                (((S_800DA93C_4 *)((u8 *)link_addr))->unk_B0 & tag_mask) |
                ((u32)packet & addr_mask);
        }

        link_addr = ((S_800DA93C_1_pre *)quad_data)[-1].unk_00;
        quad_data = (void *)(link_addr + 0x20);
    } while (link_addr != 0);

    return 0;
}
#include "common.h"
#include "shared/object_flags.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800DAB50_0_pre {
    u16 unk_00;
} S_800DAB50_0_pre;

typedef struct S_800DAB50_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    union { u16 s; u16 u; } unk_02;   /* accessed as both */
    s16 unk_04;
    u8 pad_06[0x2];
    s16 unk_08;
    union { u16 s; s16 u; } unk_0A;   /* accessed as both */
    s32 unk_0C;
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_10;   /* overlapping accesses */
    u8 pad_14[0xC];
    u16 unk_20;
    u16 unk_22;
    u16 unk_24;
    u8 pad_26[0x2];
    struct {
        u16 unk_00;
        u16 unk_02;
        u16 unk_04;
        u16 unk_06;
    } points[4];
} S_800DAB50_0;

typedef struct WorkBlock {
    s16 *unk0;
    s16 *unk4;
    s32 unk8;
    u16 unkC;
    s32 unk10;
    s32 unk14;
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    s16 unk1E;
    s16 unk20;
    s16 unk22;
    s16 unk24;
    s16 unk26;
    s16 unk28;
    s16 unk2A;
    s16 unk2C;
} WorkBlock;

s32 rsin(s32);

/* Update the effect vertices, animate their color, and advance the rotation. */
void update_rotating_effect_vertices(void *effect_data) {
    WorkBlock work;
    s32 index;
    s32 color_step;
    s32 color_value;
    s32 updated_value;
    s32 phase_value;
    s32 phase_value_2;
    s32 state;

    work.unk28 = 0;
    work.unk20 = 0;
    if (((S_800DAB50_0 *)effect_data)->unk_08 != 0) {
        work.unk22 = 0x30;
        work.unk2A = ((S_800DAB50_0 *)effect_data)->unk_02.s + 0x30;
    } else {
        phase_value_2 = ((S_800DAB50_0 *)effect_data)->unk_02.s;
        work.unk2A = 0x30;
        work.unk22 = (phase_value_2 * 2) + 0x40;
    }
    work.unk24 = (s16)(rsin(((s16)((S_800DAB50_0 *)effect_data)->unk_02.s - 0x20) << 6) >> 6);
    work.unk0 = &work.unk20;
    work.unk2C = 0;
    work.unk18 = 2;
    phase_value = ((S_800DAB50_0 *)effect_data)->unk_0A.s;
    work.unk8 = 0;
    work.unk14 = 0;
    work.unk10 = 0;
    work.unk1A = 0;
    work.unkC = phase_value;
    for (index = 0; index < 2; index++) {
        work.unk4 = (s16 *)&((S_800DAB50_0 *)effect_data)->points[index * 2];
        transform_rotated_vertices(&work);
        work.unkC += 0x200;
    }

    for (index = 3; index >= 0; index--) {
        ((S_800DAB50_0 *)effect_data)->points[index].unk_00 += ((S_800DAB50_0 *)effect_data)->unk_20;
        ((S_800DAB50_0 *)effect_data)->points[index].unk_02 += ((S_800DAB50_0 *)effect_data)->unk_22;
        ((S_800DAB50_0 *)effect_data)->points[index].unk_04 += ((S_800DAB50_0 *)effect_data)->unk_24;
    }

    state = ((S_800DAB50_0 *)effect_data)->unk_00.s;
    switch (state) {
    case 0:
        ((S_800DAB50_0 *)effect_data)->unk_10.at00.v = 0;
        ((S_800DAB50_0 *)effect_data)->unk_04 = GetTPage(0, 1, 0x2C0, 0x100);
        ((S_800DAB50_0 *)effect_data)->unk_0C = 0x242424;
        ((S_800DAB50_0 *)effect_data)->unk_00.s = (s16)((u16)((S_800DAB50_0 *)effect_data)->unk_00.s + 1);
    case 1:
        ((S_800DAB50_0 *)effect_data)->unk_10.at00.v = ((S_800DAB50_0 *)effect_data)->unk_10.at00.v
            + ((S_800DAB50_0 *)effect_data)->unk_0C;
        color_step = 0;
        if (((S_800DAB50_0 *)effect_data)->unk_10.at03.v != 0) {
            phase_value = GetTPage(0, 3, 0x2C0, 0x100);
            color_value = 0xFFFFFF;
            color_step = 0x101010;
            state = ((S_800DAB50_0 *)effect_data)->unk_00.u;
            ((S_800DAB50_0 *)effect_data)->unk_04 = phase_value;
            ((S_800DAB50_0 *)effect_data)->unk_10.at00.v = color_value;

            ((S_800DAB50_0 *)effect_data)->unk_0C = color_step;
            state += 1;
            ((S_800DAB50_0 *)effect_data)->unk_00.s = state;
        }
        break;
    case 2:
        ((S_800DAB50_0 *)effect_data)->unk_10.at00.v = ((S_800DAB50_0 *)effect_data)->unk_10.at00.v
            - ((S_800DAB50_0 *)effect_data)->unk_0C;
        color_step = 0;
        if ((u8)((S_800DAB50_0 *)effect_data)->unk_10.at00.v == 0x7F) {
            phase_value = GetTPage(0, 3, 0x2C0, 0x100);
            color_value = 0xA0A0A0;
            color_step = 0x101010;
            state = ((S_800DAB50_0 *)effect_data)->unk_00.u;
            ((S_800DAB50_0 *)effect_data)->unk_04 = phase_value;
            ((S_800DAB50_0 *)effect_data)->unk_10.at00.v = color_value;

            ((S_800DAB50_0 *)effect_data)->unk_0C = color_step;
            state += 1;
            ((S_800DAB50_0 *)effect_data)->unk_00.s = state;
        }
        break;
    case 3:
        color_step = ((S_800DAB50_0 *)effect_data)->unk_0C;
        updated_value = ((S_800DAB50_0 *)effect_data)->unk_10.at00.v - color_step;
        ((S_800DAB50_0 *)effect_data)->unk_10.at00.v = updated_value;
        color_value = ((S_800DAB50_0 *)effect_data)->unk_0C;
        if (color_value > 0x80808) {
            ((S_800DAB50_0 *)effect_data)->unk_0C = color_value + 0xFFFEFEFF;
        }
        if (((S_800DAB50_0 *)effect_data)->unk_10.at00.v < 0) {
            ((S_800DAB50_0 *)effect_data)->unk_10.at00.v = 0;
            ((S_800DAB50_0_pre *)effect_data)[-1].unk_00 = (u16)(((S_800DAB50_0_pre *)effect_data)[-1].unk_00 | 0x8000);
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
        break;
    }

    phase_value = ((S_800DAB50_0 *)effect_data)->unk_02.u;
    phase_value <<= 0x10;
    updated_value = phase_value >> 0xE;
    phase_value >>= 0x11;
    index = updated_value + phase_value;
    phase_value = ((S_800DAB50_0 *)effect_data)->unk_08;
    updated_value = ((S_800DAB50_0 *)effect_data)->unk_0A.u;
    if (phase_value == 0) {
        updated_value -= index;
    } else {
        updated_value += index;

    }
    ((S_800DAB50_0 *)effect_data)->unk_0A.s = updated_value;
    phase_value = ((S_800DAB50_0 *)effect_data)->unk_02.u;
    ((S_800DAB50_0 *)effect_data)->unk_02.s = phase_value - 1;
}
#include "common.h"
#include "shared/object_node.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "shared/dungeon_moving_views.h"

typedef struct S_800DAE44_2 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x36];
    s16 unk_48;
} S_800DAE44_2;

/* Create an object at the source position and initialize its data. */
void create_source_positioned_object(ObjectPosition *source_pos, s16 initial_value) {
    S_800DAE44_2 *object_data;
    ObjectNodeHeader *object;

    object = allocate_list_node(0x312, &scene_object_list_anchor.next);
    if (object != NULL) {
        object->update_callback = spawn_scattered_timed_objects;
        ((MovingPosition *)(object->position))->x = (u16) ((u16)source_pos->x.w.i);
        ((MovingPosition *)(object->position))->y = (u16) ((u16)source_pos->y.w.i);
        object_data = ((void *)object) + 0x20;
        ((MovingPosition *)(object->position))->z = (u16) ((u16)source_pos->z.w.i);
        object_data->unk_10 = sample_terrain_surface_height(((u16)source_pos->x.w.i), ((u16)source_pos->y.w.i),
            (s16) (((u16)source_pos->z.w.i) - 0x80));
        object_data->unk_48 = initial_value;
    }
}
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"

typedef struct S_800DAEF4_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} S_800DAEF4_2;   /* params in spawn_scattered_timed_objects */

typedef struct S_800DAEF4_3_pre {
    u16 unk_00;
} S_800DAEF4_3_pre;   /* the 0x2 bytes before owner in spawn_scattered_timed_objects, addressed as owner[-1] */

typedef struct S_800DAEF4_3 {
    u8 pad_00[0x10];
    union { u16 s; s16 u; } unk_10;   /* accessed as both */
    u8 pad_12[0x36];
    u16 unk_48;
} S_800DAEF4_3;   /* owner in spawn_scattered_timed_objects */

typedef struct S_800DAEF4_4 {
    u8 pad_00[0x10];
    u16 unk_10;
    u8 pad_12[0x36];
    u16 unk_48;
} S_800DAEF4_4;   /* work in spawn_scattered_timed_objects */

typedef struct S_800DAEF4_6 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_800DAEF4_6;   /* link in spawn_scattered_timed_objects */

extern s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */

extern s32 secondary_sprite;

/* Spawns up to 13 scattered objects and marks the owner finished when its timer expires. */
void spawn_scattered_timed_objects(void *source_owner, void *spawn_params)
{
    s32 remaining;
    u8 *link;
    ObjectNodeHeader *object;
    SpriteFrameState *node;
    u8 *work;
    s32 offset_roll_a;
    s32 spread_roll_b;
    s32 spread_roll_a;
    s32 divisor;
    s32 height_delta;
    s32 link_value;
    u16 timer;
    u16 target_height;
    ObjectPosition *part;

    remaining = 12;
    link = (u8 *)&secondary_sprite;
    do {
        object = allocate_list_node(0x312, &scene_object_list_anchor.next);
        if (object != 0) {
            object->update_callback = update_timed_effect_animation;
            register_node(object, project_sprite_chain);
            node = object->sprite;
            work = (u8 *)object;
            work += 0x20;

            offset_roll_a = rand();
            {
                const s32 offset_roll_b = rand();
                s32 offset_sum;
                part = object->position;
                offset_sum = offset_roll_a % 64 + offset_roll_b % 64 - 64;
                part->x.w.i =
                    ((S_800DAEF4_2 *)spawn_params)->unk_02 + offset_sum / 2;
            }

            spread_roll_a = rand();
            spread_roll_b = rand();
            object->position->y.w.i =
                ((S_800DAEF4_2 *)spawn_params)->unk_06 + (spread_roll_a % 64 + spread_roll_b % 64 - 64) / 2;

            object->position->z.w.i = ((S_800DAEF4_3 *)source_owner)->unk_10.s;
            ((S_800DAEF4_4 *)work)->unk_10 = ((S_800DAEF4_2 *)spawn_params)->unk_08.at02.v;

            divisor = (rand() & 3) + 4;
            height_delta = ((S_800DAEF4_2 *)spawn_params)->unk_08.at00.v;
            height_delta -= ((S_800DAEF4_3 *)source_owner)->unk_10.u << 16;
            object->position->velocity_z = height_delta / divisor;

            node->flags |= 0xC;
            node->scale_x = 0x1000;
            node->scale_y = 0x200;
            if (rand() & 1) {
                node->flags |= 1;
            }
            node->tpage_abr = 0x60;
            node->color.word = 0xC06060;
            node->unk_00 = link;
            link_value = ((S_800DAEF4_6 *)link)->unk_04;
            node->unk_04 = 0;
            node->frame_ticks = 0;
            node->source = link_value;
            target_height = ((S_800DAEF4_2 *)spawn_params)->unk_08.at02.v;
            ((S_800DAEF4_4 *)work)->unk_48 = 4;
            ((S_800DAEF4_4 *)work)->unk_10 = target_height;
        }
        remaining--;
    } while (remaining >= 0);

    timer = ((S_800DAEF4_3 *)source_owner)->unk_48 - 1;
    ((S_800DAEF4_3 *)source_owner)->unk_48 = timer;
    if ((timer << 16) <= 0) {
        ((S_800DAEF4_3_pre *)source_owner)[-1].unk_00 |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }

}
#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_800DB164_0_pre {
    u16 unk_00;
} S_800DB164_0_pre;   /* the 0x2 bytes before arg0 in update_timed_effect_animation, addressed as arg0[-1] */

typedef struct S_800DB164_0 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x36];
    u16 unk_48;
    u8 pad_4A[0x2];
    union { s16 s; u16 u; } unk_4C;   /* accessed as both */
} S_800DB164_0;   /* arg0 in update_timed_effect_animation */



/* Updates a timed effect's animation and motion, marking it for removal when finished. */
void update_timed_effect_animation(void *effect, ObjectPosition *motion, SpriteFrameState *visual) {
    s32 phase;
    s32 ticks_left;
    s32 next_phase;

    phase = ((S_800DB164_0 *)effect)->unk_4C.s;
    ticks_left = ((S_800DB164_0 *)effect)->unk_48 - 1;
    ((S_800DB164_0 *)effect)->unk_48 = ticks_left;
    switch (phase) {
    case 0:
        visual->scale_x = (u16) (visual->scale_x
            - ((rand() & 0xFF) + 0x300));
        visual->scale_y = (u16) (visual->scale_y
            + ((rand() & 0xFF) + 0x200));
        if ((s16) ((S_800DB164_0 *)effect)->unk_48 > 0) {
            break;
        }
        next_phase = ((S_800DB164_0 *)effect)->unk_4C.u + 1;
        ((S_800DB164_0 *)effect)->unk_4C.u = next_phase;
        break;

    case 1:
        visual->color.word = (s32) (visual->color.word
            + 0xFFF3F3F4);
        motion->velocity_z = (s32) (motion->velocity_z - ((rand() & 0xFF)
            << 0xA));
        if (motion->z.w.i < ((S_800DB164_0 *)effect)->unk_10) {
            phase = 4;
            ((S_800DB164_0 *)effect)->unk_48 = phase;
            next_phase = ((S_800DB164_0 *)effect)->unk_4C.u + 1;
            ((S_800DB164_0 *)effect)->unk_4C.u = next_phase;
        }
        break;

    case 2:
        if ((ticks_left << 0x10) <= 0) {
            (*(u16 *)((u8 *)effect + -2)) = (u16) (((S_800DB164_0_pre *)effect)[-1].unk_00 | NODE_REMOVE);
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
        break;
    }

    if (((S_800DB164_0 *)effect)->unk_4C.s != 0) {
        motion->z.v = (s32) (motion->z.v
            + motion->velocity_z);
        advance_sprite_animation_and_textures(visual);
    }
}
#include "common.h"
#include "m2c_compat.h"
#include "shared/object_node.h"
#include "shared/dungeon_moving_views.h"

struct D_800DB420_Obj;
struct D_800DB420_RngOut;
struct D_800DB420_Effect;

typedef struct S_800DB2DC_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
    u8 pad_24[0x26];
    u16 unk_4A;
} S_800DB2DC_0;

typedef struct S_800DB2DC_1 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_800DB2DC_1;   /* held_arg2 in create_two_effect_groups */

typedef struct S_800DB2DC_2 {
    u8 pad_00[0x12];
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x12];
    s32 unk_28;
    s32 unk_2C;
} S_800DB2DC_2;   /* held_arg1 in create_two_effect_groups */

   /* held_arg0 in create_two_effect_groups */

typedef struct S_800DB2DC_5 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
} S_800DB2DC_5;

/* Creates two groups of four effects using the source position and visual state. */
void create_two_effect_groups(MovingPosition *position, S_800DB2DC_2 *source_visual, S_800DB2DC_1 *source_arg, s16 effect_param) {
    register M2C_UNK *callback;
    s32 scale;
    s16 saved_param;
    s32 effects_left;
    s32 group_step;
    u16 visual_flags;
    u16 source_offset;
    s32 visual_word;
    SpriteFrameState *visual;
    S_800DB2DC_5 *effect_state;
    ObjectNodeHeader *effect;

    saved_param = effect_param;
    group_step = 3;
    callback = advance_jittered_effect_modes;
    scale = 0x1000;
    do {
        effects_left = 3;
        do {
            effect = allocate_list_node(0x312, &scene_object_list_anchor.next);
            if (effect != 0) {
                effect->update_callback = callback;
                visual = effect->sprite;
                ((S_800DB2DC_0 *)effect)->unk_4A =
                    (u16)source_arg->unk_2A;
                visual_word = source_visual->unk_28;
                visual->scale_y = scale;
                visual->scale_x = scale;
                visual->animation_resource = visual_word;
                visual_flags = source_visual->unk_14;
                visual->flags = visual_flags;
                source_offset = source_visual->unk_12;
                visual->color.word = 0x808080;
                visual->flags = (u16)(visual_flags | 0xC);
                visual->clut =
                    (s16)(source_offset - 0x80);
                ((S_800DB2DC_0 *)effect)->unk_20 = position;
                ((MovingPosition *)(effect->position))->x =
                    (u16)position->x;
                ((MovingPosition *)(effect->position))->y =
                    (u16)position->y;
                ((MovingPosition *)(effect->position))->z =
                    (u16)position->z;
                effect_state = ((void *)effect) + 0x20;
                effect_state->unk_06 = saved_param;
                effect_state->unk_04 = (s16)(group_step != 0);
                visual->frameTable =
                    (s32)source_visual->unk_2C;
            }
        } while (--effects_left >= 0);
        group_step -= 3;
    } while (group_step >= 0);
}
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"

/* cfail-repair: tf7-phase1-cache-v3 */
typedef struct D_800DB420_Obj {
    u16 *random_data;
    s16 mode;
    u16 count;
    u8 unk8[0x22];
    s16 value2a;
} D_800DB420_Obj;

typedef struct D_800DB420_RngOut {
    u8 unk0[2];
    s16 x;
    u8 unk4[2];
    s16 y;
    u8 unk8[2];
    s16 z;
} D_800DB420_RngOut;

typedef struct D_800DB420_Effect {
    u8 unk0[0xC];
    u32 wordC;
    s16 half10;
    u8 unk12[0x1A];
    u8 *data2c;
} D_800DB420_Effect;

/* Jitter the position and advance the effect through its modes and countdown. */
void advance_jittered_effect_modes(D_800DB420_Obj *state, D_800DB420_RngOut *position, SpriteFrameState *effect) {
    position->x = state->random_data[1] + (rand() % 11) - 5;
    position->y = state->random_data[3] + (rand() % 11) - 5;
    position->z = state->random_data[5] + (rand() % 11) - 5;

    switch (state->mode) {
    case 0:
        effect->tpage_abr = 0x60;
        effect->color.word = 0x00303030;
        *(u16 *)((u8 *)state + 4) += 1;
        return;
    case 1:
        register_node((u8 *)state - 0x20, project_sprite_chain);
        select_sprite_entry(effect, (*(u8 **)&effect->frameTable)[((g_game_work.view.camera_rotation.parts.viewAngle + state->value2a + 0x100) >> 9) & 7], 0);
        *(u16 *)((u8 *)state + 4) += 1;
        return;
    case 2:
        advance_sprite_animation_and_textures(effect);
        {
            u16 remaining = state->count - 1;
            state->count = remaining;
            if ((remaining << 0x10) <= 0) {
                *(u16 *)((u8 *)state - 2) |= NODE_REMOVE;
                object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
            }
        }
    default:
        return;
    }

    return;
}
#include "common.h"
#include "shared/object_flags.h"

/* Subtracts the limit when available, otherwise marks the record and global flags. */
void subtract_limit_or_flag_record(void *record) {
    s32 current = *(s32 *)((s8 *)record + 0x18);
    s32 limit = *(s32 *)((s8 *)record + 0x1C);

    if (current >= limit) {
        *(s32 *)((s8 *)record + 0x18) = current - limit;
        return;
    }
    *(u16 *)((s8 *)record - 2) |= NODE_REMOVE;
    object_flag_block.flags |= OBJECT_REMOVE_PENDING;
}
#include "common.h"
#include "shared/game_work.h"

extern int sound_payload_buffer;
extern int message_handler_mode;
extern int message_command_start_index;
extern int message_command_write_index;
extern unsigned char D_80071298[];
extern int D_800712B4[];
extern int card_server_initialized[3];
extern struct S_80083178State saved_view_vectors;
typedef struct
{
    s16 x;
    s16 y;
    s16 z;
    s16 pad;
}
Vec16;
typedef struct
{
    u8 u0;
    u8 pad01;
    u8 v0;
    u8 pad03;
    u8 du;
    u8 pad05;
    u8 dv;
    u8 pad07;
    s16 x0;
    s16 y0;
    s16 z0;
    s16 pad0e;
    s16 x1;
    s16 y1;
    s16 z1;
    s16 pad16;
    u32 color;
    s16 pad18;
    s16 pad1a;
    s16 angle;
    s16 depth;
    s16 depth_step;
    s16 scale;
    s16 base_angle;
    s16 angle_step;
    u16 tpage;
    s16 width;
    s16 height;
    u16 clut;
    u16 tex;
    s16 count;
}
Item;
typedef struct
{
    s16 x;
    s16 y;
    s16 z;
    s16 pad;
    Vec16 *p0;
    Vec16 *p1;
    s32 pad10;
    s16 sx;
    s16 pad16;
    s16 sy;
    s16 sz;
    s16 value;
    s16 pad1e;
    s16 one;
    s16 zero;
    s32 pad24;
}
Transform;
typedef struct
{
    u32 tag;
    u32 color;
    u8 data[0x2c];
}
Primitive;
typedef struct
{
    u8 pad00[0xB0];
    u32 ordering[0x1E0];
    u8 pad830[0xA0];
    Primitive *next_primitive;
}
Dungeon;
extern s32 rsin(s32);
extern s32 RotTransPers4(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
/* Draw linked items as fading textured quads along interpolated, oscillating paths. */
s32 draw_fading_linked_quads(Item *item)
{
    Vec16 local_vertices[4];
    Vec16 quad_vertices[4];
    Transform transform;
    s32 projection_scratch;
    Dungeon *dungeon_copy;
    s32 quad_index;
    s32 accum_x;
    s32 accum_y;
    s32 accum_z;
    s32 delta_x;
    s32 delta_y;
    s32 delta_z;
    s32 z_phase;
    s32 address_mask;
    Dungeon **dungeon_ptr;
    dungeon_ptr = (Dungeon **) ((u8 *)(&g_game_work));
    address_mask = 0x00FFFFFF;
    for (;;) {
        s32 left_x = (-item->width) >> 1;
        s32 near_z;
        s32 right_x;
        s32 far_z;
        s32 color;
        s32 offset_phase;
        Item *current_item;
        Item *next_node;
        local_vertices[1].x = left_x;
        local_vertices[0].x = left_x;
        near_z = (-item->height) >> 1;
        local_vertices[2].z = near_z;
        local_vertices[0].z = near_z;
        right_x = left_x + ((u16) item->width);
        local_vertices[3].x = right_x;
        local_vertices[2].x = right_x;
        far_z = near_z + ((u16) item->height);
        local_vertices[3].z = far_z;
        local_vertices[1].z = far_z;
        local_vertices[3].y = 0;
        local_vertices[2].y = 0;
        local_vertices[1].y = 0;
        local_vertices[0].y = 0;
        quad_index = 0;
        current_item = item;
        z_phase = item->depth;
        offset_phase = item->base_angle;
        color = item->color;
        delta_x = item->x1 - item->x0;
        delta_y = item->y1 - item->y0;
        delta_z = item->z1 - item->z0;
        if (item->count >= 0) {
            accum_z = 0;
            accum_y = accum_z;
            accum_x = accum_y;
            do {
                Primitive *primitive;
                u8 *vertex_bytes;
                u32 *ordering_entry;
                void *vertex_0;
                void *vertex_2;
                void *vertex_3;
                void *vertex_1;
                s32 ordering_index;
                s32 wave_value;
                u8 u_start;
                u8 u_end;
                u8 v_start;
                u8 v_end;
                wave_value = rsin(offset_phase);
                transform.x = (wave_value * current_item->scale) >> 12;
                transform.z = 0;
                transform.y = 0;
                transform.p0 = &transform.x;
                transform.p1 = &transform.x;
                transform.sx = current_item->tpage;
                transform.sy = current_item->x0 + (accum_x / current_item->count);
                transform.sz = current_item->y0 + (accum_y / current_item->count);
                wave_value = rsin(z_phase);
                transform.value = (current_item->z0 + (accum_z / current_item->count))
                    + ((wave_value * current_item->angle) >> 12);
                transform.one = 1;
                transform.zero = 0;
                transform_rotated_vertices((Transform *) (&transform.p0));
                vertex_bytes = (u8 *) quad_vertices;
                vertex_0 = vertex_bytes;
                vertex_2 = vertex_bytes + 16;
                vertex_3 = vertex_bytes + 24;
                quad_vertices[1].x = transform.x - (((s16) current_item->width) >> 1);
                quad_vertices[0].x = quad_vertices[1].x;
                quad_vertices[3].x = quad_vertices[0].x + current_item->width;
                quad_vertices[2].x = quad_vertices[3].x;
                quad_vertices[2].z = transform.z - (((s16) current_item->height) >> 1);
                quad_vertices[0].z = quad_vertices[2].z;
                quad_vertices[3].z = quad_vertices[2].z + current_item->height;
                quad_vertices[1].z = quad_vertices[3].z;
                quad_vertices[3].y = transform.y;
                quad_vertices[2].y = quad_vertices[3].y;
                quad_vertices[1].y = quad_vertices[2].y;
                quad_vertices[0].y = quad_vertices[1].y;
                z_phase += current_item->depth_step;
                vertex_1 = vertex_bytes + 8;
                {
                    Dungeon *dungeon = *dungeon_ptr;
                    primitive = dungeon->next_primitive;
                    offset_phase += current_item->angle_step;
                    dungeon->next_primitive = (Primitive *) (((u8 *) primitive) + 0x34);
                }
                ordering_index = RotTransPers4(vertex_0, vertex_1, vertex_2, vertex_3, ((u8 *) primitive) + 8,
                    ((u8 *) primitive) + 0x10, ((u8 *) primitive) + 0x18, ((u8 *) primitive) + 0x20,
                    &projection_scratch, &projection_scratch) - 8;
                if (((u32) ordering_index) < 0x1E0) {
                    primitive->color = color;
                    SetPolyFT4(primitive);
                    SetSemiTrans(primitive, 1);
                    *((u16 *) (((u8 *) primitive) + 0x16)) = current_item->clut;
                    *((u16 *) (((u8 *) primitive) + 0x0E)) = current_item->tex;
                    u_start = current_item->u0;
                    *(((u8 *) primitive) + 0x14) = u_start;
                    *(((u8 *) primitive) + 0x0C) = u_start;
                    u_end = current_item->u0 + current_item->du;
                    *(((u8 *) primitive) + 0x24) = u_end;
                    *(((u8 *) primitive) + 0x1C) = u_end;
                    v_start = current_item->v0;
                    *(((u8 *) primitive) + 0x1D) = v_start;
                    *(((u8 *) primitive) + 0x0D) = v_start;
                    v_end = current_item->v0 + current_item->dv;
                    *(((u8 *) primitive) + 0x25) = v_end;
                    *(((u8 *) primitive) + 0x15) = v_end;
                    {
                        Dungeon *dungeon = *dungeon_ptr;
                        Dungeon *ordering_dungeon;
                        u32 chain_tag;
                        chain_tag = (primitive->tag & 0xFF000000) | (dungeon->ordering[ordering_index] & address_mask);
                        (*(u32 *)((u8 *)primitive + 0)) = chain_tag;
                        dungeon_copy = *dungeon_ptr;
                        ordering_dungeon = dungeon_copy;
                        ordering_dungeon->ordering[ordering_index] =
                            (ordering_dungeon->ordering[ordering_index] & 0xFF000000)
                            | (((u32) primitive) & address_mask);
                    }
                }
                if (color > 0x80807) {
                    color -= 0x80808;
                }
                accum_z += delta_z;
                accum_y += delta_y;
                accum_x += delta_x;
                quad_index++;
            }
            while (quad_index <= current_item->count);
        }
        next_node = *((Item **) (((u8 *) item) - 8));
        if (next_node == 0) {
            break;
        }
        item = (Item *) (((u8 *) next_node) + 0x20);
    }

    return 0;
}
#include "common.h"

extern void PushMatrix(void);
extern void PopMatrix(void);
extern void SetRotMatrix(void *matrix);
extern void SetTransMatrix(void *values);
extern void RotTrans(void *vertex, void *coordinates, s32 *result);
extern void RotMatrix(void *transform_fields, void *matrix);
extern void RotMatrixX(s16 value, void *matrix, s32 diagonal_value, s32 last_column_index_index);
extern void RotMatrixY(s16 value, void *matrix);
extern void RotMatrixZ(s16 value, void *matrix);

typedef struct Struct_800D6330 {
    /* 0x00 */ s32 *unk00;
    /* 0x04 */ s16 *unk04;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ s16 unk0C;
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ u16 unk1A;
} Struct_800D6330;

/* Transforms source_vertices using the selected rotation matrix and stores their coordinates. */
void transform_rotated_vertices(void *transform_data) {
    Struct_800D6330 *transform = transform_data;
    union {
        s16 rotation_matrix[9];
        struct {
            s8 pad1[0x14];
            s32 input_0;
            s32 input_1;
            s32 input_2;
            s32 output_x;
            s32 output_y;
            s32 output_z;
        } s;
    } scratch;
    s32 column_index;
    s16 *matrix_row;
    s16 *row_start;
    s16 *matrix_cell;
    s32 index;
    s32 last_column_index;
    s32 diagonal_value;
    s32 vertex_byte_offset = 0;
    s32 *source_vertices;
    void *output_coordinates;

    PushMatrix();
    scratch.s.input_0 = transform->unk10;
    scratch.s.input_1 = transform->unk12;
    scratch.s.input_2 = transform->unk14;
    SetTransMatrix(scratch.rotation_matrix);
    if (transform->unk1A == 0) {
        RotMatrix(&transform->unk08, scratch.rotation_matrix);
    } else {
        index = 2;
        if (transform->unk1A != 0x8000) {
            last_column_index = index;
            diagonal_value = 0x1000;
            matrix_row = scratch.rotation_matrix + 6;
            do {
                column_index = last_column_index;
                row_start = matrix_row;
                do {
                    matrix_cell = (s16 *) ((column_index << 1) + (unsigned long)row_start);
                    if (index == column_index) {
                        *matrix_cell = diagonal_value;
                    } else {
                        *matrix_cell = 0;
                    }
                    column_index--;
                } while (column_index >= 0);
                index--;
                matrix_row -= 3;
            } while (index >= 0);
            if (transform->unk1A == 1) {
                RotMatrixX(transform->unk08, scratch.rotation_matrix, diagonal_value, last_column_index);
                RotMatrixY(transform->unk0A, scratch.rotation_matrix);
                RotMatrixZ(transform->unk0C, scratch.rotation_matrix);
            }
        }
    }
    SetRotMatrix(scratch.rotation_matrix);
    index = 0;
    if (transform->unk18 > 0) {
        output_coordinates = &scratch.s.output_x;
        do {
            vertex_byte_offset = index * 8;
            source_vertices = transform->unk00;
            RotTrans((s8 *) source_vertices + vertex_byte_offset, output_coordinates, &column_index);
            *(u16 *) ((s8 *) transform->unk04 + index * 8) = *(u16 *) &scratch.s.output_x;
            *(u16 *) ((s8 *) transform->unk04 + index * 8 + 2) = *(u16 *) &scratch.s.output_y;
            vertex_byte_offset = (s32)transform->unk04 + vertex_byte_offset;
            *(u16 *) (vertex_byte_offset + 4) = *(u16 *) &scratch.s.output_z;
            index++;
            if (index >= transform->unk18) {
                break;
            }
            output_coordinates = &scratch.s.output_x;
        } while (1);
    }
    PopMatrix();
}
