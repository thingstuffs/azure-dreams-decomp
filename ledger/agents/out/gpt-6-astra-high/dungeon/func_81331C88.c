#include "common.h"

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
} S_80168C88_0;   /* arg0 in func_80168C88 */

typedef struct S_80168C88_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_80168C88_1;   /* arg2 in func_80168C88 */

typedef struct S_80168C88_2 {
    u8 pad_00[0x54];
    s16 unk_54;
} S_80168C88_2;   /* temp_v0 in func_80168C88 */

typedef struct S_80168C88_3 {
    s16 unk_00;
} S_80168C88_3;   /* (void *)temp_a1 in func_80168C88 */

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
} S_80168C88_4;   /* temp_s0 in func_80168C88 */

typedef struct S_80168C88_5 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80168C88_5;   /* temp_v0_2 in func_80168C88 */

typedef struct S_80168C88_6 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} S_80168C88_6;   /* temp_a3 in func_80168C88 */

typedef struct S_80168C88_7 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80168C88_7;   /* temp_v1_3 in func_80168C88 */

typedef struct S_80168C88_8 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80168C88_8;   /* arg1 in func_80168C88 */

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
} S_80168C88_9;   /* temp_a3_2 in func_80168C88 */

typedef struct S_80168C88_10 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
} S_80168C88_10;   /* var_a0 in func_80168C88 */

typedef struct S_80168C88_11 {
    u8 pad_00[0x8];
    u8 unk_08;
} S_80168C88_11;   /* temp_a0_3 in func_80168C88 */

typedef struct S_80168C88_12 {
    u8 pad_00[0x9];
    u8 unk_09;
} S_80168C88_12;   /* temp_a0_4 in func_80168C88 */

typedef struct S_80168C88_13 {
    u16 unk_00;
} S_80168C88_13;   /* lookup in func_80168C88 */

typedef struct S_80168C88_14 {
    u16 unk_00;
} S_80168C88_14;   /* lookup_final in func_80168C88 */



extern void *func_8003FC64();
extern void func_8004491C();
extern s32 D_800814A0;
extern u8 D_80166914[];
extern u8 D_80167C30[];
extern u8 D_80173B4C[];
extern u8 D_80175DD8[];

/* Builds seven colored effect segments from interpolated coordinates and decrements their source effect lifetime. */
void func_80168C88(u8 *effect, void *origin, void *color_in)
{
    register void *color ASM_REG("$23");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s16 phase;
    u16 phase_bits;
    s32 red_scaled;
    s32 green_scaled;
    s32 step;
    s32 step_offset;
    s32 dest_offset;
    s32 edge;
    s32 sample_offset;
    register s32 edge_offset ASM_REG("$9");   /* MATCH pin: retail register colouring depends on it */
    s32 axis;
    s32 dest_coord;
    register u8 *shape_row ASM_REG("$3");   /* MATCH pin: keeps a constant in a register as retail does */
    register u8 *endpoint ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    s16 *start_coord;
    register s32 scaled_delta ASM_REG("$4");   /* MATCH pin: keeps a constant in a register as retail does */
    u8 *table_base;
    s32 segment;
    s32 segment_offset;
    void *task;
    u8 *segment_data;
    register void *render_flags ASM_REG("$7");   /* MATCH pin: retail register colouring depends on it */
    void *position;
    register s32 vertex ASM_REG("$8");   /* MATCH pin: retail register colouring depends on it */
    register u8 *vertex_color ASM_REG("$4");   /* MATCH pin: keeps a constant in a register as retail does */
    void *render_data;
    s32 side;
    u8 *vertex_base;
    u8 *texture_data;
    void *texture;
    s32 coord;
    s32 source_offset;
    u16 *near_vertex;
    register u16 *far_vertex ASM_REG("$6");   /* MATCH pin: retail register colouring depends on it */
    s32 coord_offset;
    s32 source_side;
    s32 source_index;
    register u8 *coord_lookup ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    u8 *far_coord;
    s16 ticks_left;
    u8 *coord_table;
    register s32 one ASM_REG("$22");   /* MATCH pin: keeps a constant in a register as retail does */

    phase = ((S_80168C88_0 *)effect)->unk_12.s;
    phase_bits = *(volatile u16 *)(effect + 0x12);
    color = color_in;
    if (phase == 0) {
        goto status_zero;
    }
    if (phase == 1) {
        goto status_one;
    }
    step = 1;
    goto table_setup;

status_zero:
    if (((S_80168C88_0 *)effect)->unk_18.s < 6) {
        ((S_80168C88_0 *)effect)->unk_12.u = phase_bits + 1;
    }
    goto table_start;

status_one:
    red_scaled = ((S_80168C88_0 *)effect)->unk_00 * ((S_80168C88_0 *)effect)->unk_18.s;
    if (red_scaled < 0) {
        red_scaled += 3;
    }
    ((S_80168C88_1 *)color)->unk_0C = red_scaled >> 2;
    green_scaled = ((S_80168C88_0 *)effect)->unk_01 * ((S_80168C88_0 *)effect)->unk_18.s;
    if (green_scaled < 0) {
        green_scaled += 3;
    }
    ((S_80168C88_1 *)color)->unk_0D = green_scaled >> 2;

table_start:
    step = 1;
table_setup:
    table_base = D_80175DD8;
    step_offset = 0xC;
    do {
        edge = 0;
        dest_offset = step_offset;
        sample_offset = edge;
interpolate_edge:
        axis = 0;
        edge_offset = sample_offset;
interpolate_axis:
        dest_coord = axis * 2;
        shape_row = (u8 *)(((S_80168C88_0 *)effect)->unk_1C * 0x60);
        ASM_KEEP_NV(shape_row);   /* MATCH pin: keeps a constant in a register as retail does */
        shape_row += (s32)table_base;
        endpoint = (u8 *)((s32)edge_offset + (s32)shape_row);
        start_coord = (s16 *)dest_coord;
        start_coord = (s16 *)((u8 *)start_coord + (s32)endpoint);
        ASM_KEEP_DEP_NV(start_coord, endpoint);   /* MATCH pin: keeps a constant in a register as retail does */
        endpoint += dest_coord;
        ASM_KEEP_NV(endpoint);   /* MATCH pin: keeps a constant in a register as retail does */
        scaled_delta = (((S_80168C88_2 *)endpoint)->unk_54 - *start_coord) * step;
        axis += 1;
        shape_row = (u8 *)((s32)dest_offset + (s32)shape_row);
        shape_row = (u8 *)((s32)edge_offset + (s32)shape_row);
        dest_coord += (s32)shape_row;
        ASM_KEEP_NV(dest_coord);   /* MATCH pin: keeps a constant in a register as retail does */
        ((S_80168C88_3 *)((void *)dest_coord))->unk_00 = *start_coord + scaled_delta / 7;
        if (axis < 3) {
            goto interpolate_axis;
        }
        edge += 1;
        sample_offset += 6;
        if (edge < 2) {
            goto interpolate_edge;
        }
        step += 1;
        step_offset += 0xC;
    } while (step < 7);

    segment = 0;
    coord_table = D_80175DD8;
    one = 1;
    segment_offset = segment;
    ((S_80168C88_0 *)effect)->unk_1E = ((S_80168C88_0 *)effect)->unk_1E - 1;
    do {
        task = func_8003FC64(0x12);
        if (task != NULL) {
            register void *task_arg ASM_REG("$4");   /* MATCH pin: keeps a constant in a register as retail does */
            void *init_fn;
            void *callback;

            task_arg = task;
            segment_data = (u8 *)task + 0x20;
            ASM_SCHED_BARRIER();   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
            init_fn = D_80167C30;
            ASM_KEEP_DEP_NV(init_fn, segment_data);   /* MATCH pin: retail immediate-load split depends on it */
            callback = D_80166914;
            ((S_80168C88_4 *)segment_data)->unk_18 = one;
            ((S_80168C88_4 *)segment_data)->unk_1A = one;
            ((S_80168C88_5 *)task)->unk_10 = init_fn;
            func_8004491C(task_arg, callback);

            render_flags = ((S_80168C88_5 *)task)->unk_0C;
            ((S_80168C88_6 *)render_flags)->unk_10 = 0x20;
            ((S_80168C88_6 *)render_flags)->unk_14 |= 0xC;

            position = ((S_80168C88_5 *)task)->unk_08;
            ((S_80168C88_7 *)position)->unk_00 = ((S_80168C88_8 *)origin)->unk_00;
            vertex = 0;
            ((S_80168C88_7 *)position)->unk_04 = ((S_80168C88_8 *)origin)->unk_04;
            vertex_color = segment_data;
            ((S_80168C88_7 *)position)->unk_08 = ((S_80168C88_8 *)origin)->unk_08;

            render_data = ((S_80168C88_5 *)task)->unk_0C;
            ((S_80168C88_9 *)render_data)->unk_1E = 0x1000;
            ((S_80168C88_9 *)render_data)->unk_1C = 0x1000;
            ((S_80168C88_9 *)render_data)->unk_0E = 0x80;
            ((S_80168C88_9 *)render_data)->unk_0D = 0x80;
            ((S_80168C88_9 *)render_data)->unk_0C = 0x80;

            do {
                ((S_80168C88_10 *)vertex_color)->unk_00 = ((S_80168C88_1 *)color)->unk_0C;
                ((S_80168C88_10 *)vertex_color)->unk_01 = ((S_80168C88_1 *)color)->unk_0D;
                vertex += 1;
                ((S_80168C88_10 *)vertex_color)->unk_02 = ((S_80168C88_1 *)color)->unk_0E;
                vertex_color += 4;
            } while (vertex < 4);

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

            side = 0;
            sample_offset = segment_offset;
            vertex_base = segment_data;
            texture_data = vertex_base + 0x28;
            ((S_80168C88_9 *)render_data)->unk_08 = texture_data;
            ((S_80168C88_11 *)texture_data)->unk_08 += ((S_80168C88_0 *)effect)->unk_1C * 4;
            texture = ((S_80168C88_9 *)render_data)->unk_08;
            ((S_80168C88_12 *)texture)->unk_09 += (((S_80168C88_0 *)effect)->unk_1E & 3) * 8;

            do {
                coord = 0;
                source_side = one - side;
                ASM_KEEP_NV(source_side);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
                source_index = source_side * 2;
                source_index += source_side;
                ASM_KEEP_NV(source_index);   /* MATCH pin: keeps a constant in a register as retail does */
                source_offset = source_index * 2;
                far_vertex = (u16 *)(vertex_base + 0x80);
                near_vertex = (u16 *)(vertex_base + 0x74);
copy_coord:
                coord_offset = coord * 2;
                coord_lookup = (u8 *)(((S_80168C88_0 *)effect)->unk_1C * 0x60);
                coord_lookup += (s32)coord_table;
                coord_lookup = (u8 *)((s32)sample_offset + (s32)coord_lookup);
                coord_lookup = (u8 *)((s32)source_offset + (s32)coord_lookup);
                coord_lookup = (u8 *)((s32)coord_offset + (s32)coord_lookup);
                *near_vertex = ((S_80168C88_13 *)coord_lookup)->unk_00;
                coord += 1;
                near_vertex += 1;
                coord_lookup = (u8 *)(((S_80168C88_0 *)effect)->unk_1C * 0x60);
                coord_lookup += (s32)coord_table;
                coord_lookup = (u8 *)((s32)sample_offset + (s32)coord_lookup);
                coord_lookup += 0xC;
                coord_lookup = (u8 *)((s32)source_offset + (s32)coord_lookup);
                far_coord = (u8 *)((s32)coord_offset + (s32)coord_lookup);
                ASM_KEEP_NV(far_coord);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
                *far_vertex = ((S_80168C88_14 *)far_coord)->unk_00;
                far_vertex += 1;
                if (coord < 3) {
                    goto copy_coord;
                }
                side += 1;
                vertex_base += 6;
            } while (side < 2);
        }
        segment += 1;
        segment_offset += 0xC;
    } while (segment < 7);

    ticks_left = ((S_80168C88_0 *)effect)->unk_18.u - 1;
    ((S_80168C88_0 *)effect)->unk_18.s = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        (*(u16 *)((u8 *)effect + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
