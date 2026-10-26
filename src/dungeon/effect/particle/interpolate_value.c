/* Coordinate interpolation and creation of seven colored ribbon segments. */
#include "shared/object_node.h"
#include "shared/entity.h"
#include "common.h"
#include "shared/object_flags.h"
#include "engine/node.h"

/* Sparse views for fields not covered by the existing record types. */
typedef struct { u16 flags; } EffectFieldView_81331C88Prefix;

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80168C88_0 {
    u8 unk_00;
    u8 unk_01;
    u8 pad_02[0x10];
    union { s16 s; u16 u; } unk_12;   /* accessed as both */
    u8 pad_14[0x4];
    union { s16 s; u16 u; } unk_18;   /* accessed as both */
    u8 pad_1A[0x2];
    s16 unk_1C;
    u16 unk_1E;
} S_80168C88_0;   /* arg0 in update_animated_textured_ribbon */

typedef struct S_80168C88_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_80168C88_1;   /* arg2 in update_animated_textured_ribbon */

typedef struct S_80168C88_2 {
    u8 pad_00[0x54];
    s16 unk_54;
} S_80168C88_2;

typedef struct S_80168C88_3 {
    s16 unk_00;
} S_80168C88_3;

typedef struct S_80168C88_4 {
    s8 unk_00;
    s8 unk_01;
    s8 unk_02;
    u8 pad_03[0x1];
    s8 unk_04;
    s8 unk_05;
    s8 unk_06;
    u8 pad_07[0x1];
    s8 unk_08;
    s8 unk_09;
    s8 unk_0A;
    u8 pad_0B[0x1];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x9];
    s16 unk_18;
    s16 unk_1A;
} S_80168C88_4;

typedef struct S_80168C88_6 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} S_80168C88_6;

typedef struct S_80168C88_8 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80168C88_8;   /* arg1 in update_animated_textured_ribbon */

typedef struct S_80168C88_9 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    s16 unk_1C;
    s16 unk_1E;
} S_80168C88_9;

typedef struct S_80168C88_10 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
} S_80168C88_10;

typedef struct S_80168C88_11 {
    u8 pad_00[0x8];
    u8 unk_08;
} S_80168C88_11;

typedef struct S_80168C88_12 {
    u8 pad_00[0x9];
    u8 unk_09;
} S_80168C88_12;

extern u8 D_80166914[];
extern u8 ribbon_particle_update_address[];
extern u8 D_80173B4C[];
extern u8 ribbon_vertices[];

/* Returns the signed 16-bit value at step/7 along the supplied delta from the start value. */
static __inline__ s16 interpolate_value(s32 delta, s32 step, u16 start)
{
    s16 value = start + delta * step / 7;
    return value;
}

/* Builds seven colored effect segments from interpolated coordinates and decrements their source effect lifetime. */
void update_animated_textured_ribbon(u8 *effect, void *origin, void *color_in)
{
    s16 phase;
    s32 red_scaled;
    s32 green_scaled;
    s32 step;
    s32 edge;
    s32 sample_offset;
    s32 edge_offset;
    s32 axis;
    s32 dest_coord;
    u8 *shape_row;
    u8 *endpoint;
    s16 *start_coord;
    s32 scaled_delta;
    s32 segment;
    s32 segment_offset;
    ObjectNodeHeader *task;
    u8 *segment_data;
    ObjectPosition *position;
    void *render_data;
    u8 *vertex_base;
    u8 *texture_data;
    void *texture;
    s32 coord;
    u8 *far_coord;
    s16 ticks_left;
    u8 *coord_table;
    s32 one;

    phase = ((S_80168C88_0 *)effect)->unk_12.s;
    switch (phase) {
    case 0:
        if (((S_80168C88_0 *)effect)->unk_18.s < 6) {
            ((S_80168C88_0 *)effect)->unk_12.u++;
        }
        break;
    case 1:
        red_scaled = ((S_80168C88_0 *)effect)->unk_00 * ((S_80168C88_0 *)effect)->unk_18.s;
        ((S_80168C88_1 *)color_in)->unk_0C = (red_scaled / 4);
        green_scaled = ((S_80168C88_0 *)effect)->unk_01 * ((S_80168C88_0 *)effect)->unk_18.s;
        ((S_80168C88_1 *)color_in)->unk_0D = (green_scaled / 4);
        break;
    }
    step = 1;
    do {
        edge = 0;
        do {
            axis = 0;
            do {
                dest_coord = axis * 2;
                shape_row = (u8 *)(((S_80168C88_0 *)effect)->unk_1C * 0x60 + (s32)ribbon_vertices);
                endpoint = (u8 *)(edge * 6 + (long)shape_row);
                start_coord = (s16 *)dest_coord;
                start_coord = (s16 *)((u8 *)start_coord + (s32)endpoint);
                endpoint += dest_coord;
                scaled_delta = ((S_80168C88_2 *)endpoint)->unk_54;
                scaled_delta -= *start_coord;
                axis += 1;
                dest_coord += edge * 6 + (step * 0xC + (s32)shape_row);
                ((S_80168C88_3 *)((void *)dest_coord))->unk_00 = interpolate_value(scaled_delta, step, *start_coord);
            } while (axis < 3);
            edge += 1;
        } while (edge < 2);
        step += 1;
    } while (step < 7);

    segment = 0;
    coord_table = ribbon_vertices;
    one = 1;
    ((S_80168C88_0 *)effect)->unk_1E = ((S_80168C88_0 *)effect)->unk_1E - 1;
    segment_offset = segment;
    do {
        task = allocate_flagged_object_node(0x12);
        if (task != NULL) {
            void *init_fn = 0;
            void *callback;

            scaled_delta = (s32)(task);
            segment_data = (u8 *)task + 0x20;
            callback = D_80166914;
            init_fn = ribbon_particle_update_address;
            ((S_80168C88_4 *)segment_data)->unk_18 = one;
            ((S_80168C88_4 *)segment_data)->unk_1A = one;
            task->update_callback = init_fn;
            register_node((void *)scaled_delta, callback);

            render_data = task->sprite;
            ((S_80168C88_6 *)render_data)->unk_10 = 0x20;
            ((S_80168C88_6 *)render_data)->unk_14 |= 0xC;

            position = task->position;
            position->x.v = ((S_80168C88_8 *)origin)->unk_00;
            step = 0;
            position->y.v = ((S_80168C88_8 *)origin)->unk_04;
            position->z.v = ((S_80168C88_8 *)origin)->unk_08;

            render_data = task->sprite;
            ((S_80168C88_9 *)render_data)->unk_1E = 0x1000;
            ((S_80168C88_9 *)render_data)->unk_1C = 0x1000;
            ((S_80168C88_9 *)render_data)->unk_0E = 0x80;
            ((S_80168C88_9 *)render_data)->unk_0D = 0x80;
            ((S_80168C88_9 *)render_data)->unk_0C = 0x80;

            do {
                ((S_80168C88_10 *)(segment_data + step * 4))->unk_00 = ((S_80168C88_1 *)color_in)->unk_0C;
                ((S_80168C88_10 *)(segment_data + step * 4))->unk_01 = ((S_80168C88_1 *)color_in)->unk_0D;
                ((S_80168C88_10 *)(segment_data + step * 4))->unk_02 = ((S_80168C88_1 *)color_in)->unk_0E;
                step += 1;
            } while (step < 4);

            if (segment == 0) {
                ((S_80168C88_4 *)segment_data)->unk_06 = 0;
                ((S_80168C88_4 *)segment_data)->unk_05 = 0;
                ((S_80168C88_4 *)segment_data)->unk_04 = 0;
                ((S_80168C88_4 *)segment_data)->unk_02 = 0;
                ((S_80168C88_4 *)segment_data)->unk_01 = 0;
                ((S_80168C88_4 *)segment_data)->unk_00 = 0;
            }
            if (segment == 6) {
                ((S_80168C88_4 *)segment_data)->unk_0E = 0;
                ((S_80168C88_4 *)segment_data)->unk_0D = 0;
                ((S_80168C88_4 *)segment_data)->unk_0C = 0;
                ((S_80168C88_4 *)segment_data)->unk_0A = 0;
                ((S_80168C88_4 *)segment_data)->unk_09 = 0;
                ((S_80168C88_4 *)segment_data)->unk_08 = 0;
            }

            ((S_80168C88_9 *)render_data)->unk_06 = 0;
            __builtin_memcpy(segment_data + 0x28, D_80173B4C, 0xC);

            edge = 0;
            sample_offset = segment_offset;
            vertex_base = segment_data;
            texture_data = vertex_base + 0x28;
            ((S_80168C88_9 *)render_data)->unk_08 = texture_data;
            ((S_80168C88_11 *)texture_data)->unk_08 += ((S_80168C88_0 *)effect)->unk_1C * 4;
            texture = ((S_80168C88_9 *)render_data)->unk_08;
            ((S_80168C88_12 *)texture)->unk_09 += (((S_80168C88_0 *)effect)->unk_1E & 3) * 8;

            do {
                coord = 0;
                edge_offset = (one - edge) * 6;
                start_coord = (s16 *)(vertex_base + 0x80);
                dest_coord = (s32)(vertex_base + 0x74);
                do {
                    *(u16 *)dest_coord = *(u16 *)(coord * 2 + (edge_offset + (sample_offset + (((S_80168C88_0 *)effect)->unk_1C * 0x60 + (s32)coord_table))));
                    dest_coord += 2;
                    far_coord = (u8 *)(sample_offset + (((S_80168C88_0 *)effect)->unk_1C * 0x60 + (s32)coord_table)) + 0xC;
                    *start_coord = *(u16 *)(coord * 2 + (edge_offset + (s32)far_coord));
                    start_coord += 1;
                    coord += 1;
                } while (coord < 3);
                edge += 1;
                vertex_base += 6;
            } while (edge < 2);
        }
        segment += 1;
        segment_offset += 0xC;
    } while (segment < 7);

    ticks_left = ((S_80168C88_0 *)effect)->unk_18.u - 1;
    ((S_80168C88_0 *)effect)->unk_18.s = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        (((EffectFieldView_81331C88Prefix *)effect)[-1].flags) |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
