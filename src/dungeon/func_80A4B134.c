#include "common.h"

typedef struct S_80174934_0 {
    u8 pad_00[0x16];
    union { s16 s; volatile u16 u; u16 p; } unk_16;   /* accessed as both */
    u8 pad_18[0x2];
    union { s16 s; u16 u; } unk_1A;   /* accessed as both */
    u8 pad_1C[0x2];
    s16 unk_1E;
    u16 unk_20;
    u8 pad_22[0x42];
    s16 unk_64;
    s16 unk_66;
} S_80174934_0;   /* arg0 in func_80174934 */

typedef struct S_80174934_1 {
    u8 pad_00[0x1A];
    s16 unk_1A;
    s16 unk_1C;
    u8 pad_1E[0x4A];
    s16 unk_68;
    u8 pad_6A[0x4];
    s16 unk_6E;
    u8 pad_70[0x4];
    s16 unk_74;
    u8 pad_76[0x4];
    s16 unk_7A;
} S_80174934_1;   /* work in func_80174934 */

typedef struct S_80174934_2 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 * unk_0C;
    void * unk_10;
} S_80174934_2;   /* obj in func_80174934 */

typedef struct S_80174934_3 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 * unk_08;
    u8 pad_0C[0x4];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80174934_3;   /* ctl in func_80174934 */

typedef struct S_80174934_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80174934_4;   /* pos in func_80174934 */



typedef struct Vec3w {
    s32 x;
    s32 y;
    s32 z;
} Vec3w;

typedef struct Rows {
    u8 pad[0x64];
    u16 row[4][3];
} Rows;

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern s32 func_80069EF8(void);
extern void func_80174214(void *, s32, s32, s32, s32, s32, s32);
extern void *memcpy(void *, const void *, u32);

extern s32 D_800814A0;
extern u8 D_8017489C[12];
extern u8 D_801748F0[12];
extern u8 D_80175910[12];

/* Updates a fading effect, builds four strips, and marks completion when its timer expires. */
void func_80174934(u8 *effect, Vec3w *origin, u8 *render_data)
{
    s16 phase;
    u16 phase_bits;
    s16 strip_index;
    s16 vertex_index;
    s16 next_vertex;
    s16 row_index;
    s16 next_row;
    s16 axis_index;
    s16 next_axis;
    s16 frames_left;
    s16 top;
    s16 bottom;
    s32 fade_level;
    s32 random_offset;
    s32 particle_variant;
    s32 particle_strength;
    u8 *strip_obj;
    u8 *init_obj;
    u8 *strip_data;
    u8 *render_ctl;
    u8 *position;
    u8 *frame_data;
    void *callback;
    u32 *vertex_color;

    phase = ((S_80174934_0 *)effect)->unk_16.s;
    phase_bits = ((S_80174934_0 *)effect)->unk_16.u;
    if (phase != 1) {
        if (phase < 2) {
            if (phase == 0)
                goto phase_zero;
            goto build_objects;
        } else {
            if (phase == 2) {
                goto phase_two;
            }

            goto build_objects;
        }

phase_zero:
        render_data[0xC] = (u8)((effect[4] *
            (0x32 - ((S_80174934_0 *)effect)->unk_1A.s)) / 10);
        render_data[0xD] = (u8)((effect[5] *
            (0x32 - ((S_80174934_0 *)effect)->unk_1A.s)) / 10);
        fade_level = 0x32 - ((S_80174934_0 *)effect)->unk_1A.s;
        render_data[0xE] = (u8)((effect[6] * fade_level) / 10);
        if (((S_80174934_0 *)effect)->unk_1A.s < 0x29) {
            ((S_80174934_0 *)effect)->unk_16.p =
                ((S_80174934_0 *)effect)->unk_16.u + 1;
            goto build_objects;
        }

        goto build_objects;
    }

    if (((S_80174934_0 *)effect)->unk_1A.s < 0xC) {
        ((S_80174934_0 *)effect)->unk_16.s = phase_bits + 1;
    }

    if (func_80069EF8() & 1) {
        particle_variant = func_80069EF8() & 7;
        particle_strength = func_80069EF8() & 0xFF;
        particle_strength = particle_strength | 0x80;
        random_offset = func_80069EF8();
        func_80174214(effect - 0x20, particle_variant, 0xF0, particle_strength,
            ((S_80174934_0 *)effect)->unk_64, ((S_80174934_0 *)effect)->unk_66,
            (s16)(-0x70 - (random_offset & 0x1F)));
    } else {
        particle_variant = func_80069EF8() & 7;
        particle_strength = func_80069EF8() & 0xFF;
        particle_strength = particle_strength | 0x80;
        random_offset = func_80069EF8();
        func_80174214(effect - 0x20, particle_variant, 0xF0, particle_strength,
            ((S_80174934_0 *)effect)->unk_64, ((S_80174934_0 *)effect)->unk_66,
            (s16)(-0x40 - (random_offset & 0x1F)));
    }
    goto build_objects;

phase_two:
    render_data[0xC] = (u8)((effect[4] * ((S_80174934_0 *)effect)->unk_1A.s) / 10);
    render_data[0xD] = (u8)((effect[5] * ((S_80174934_0 *)effect)->unk_1A.s) / 10);
    render_data[0xE] = (u8)((effect[6] * ((S_80174934_0 *)effect)->unk_1A.s) / 10);

build_objects:
    ((S_80174934_0 *)effect)->unk_20 = ((S_80174934_0 *)effect)->unk_20 + 1;
    for (strip_index = 0; strip_index < 4; strip_index++) {
        strip_obj = func_8003FC64(0x12);
        if (strip_obj != 0) {
            init_obj = strip_obj;
            callback = D_8017489C;
            strip_data = strip_obj + 0x20;
            ((S_80174934_1 *)strip_data)->unk_1A = 1;
            ((S_80174934_1 *)strip_data)->unk_1C = 1;
            ((S_80174934_2 *)strip_obj)->unk_10 = D_801748F0;
            func_8004491C(init_obj, callback);

            render_ctl = ((S_80174934_2 *)strip_obj)->unk_0C;
            ((S_80174934_3 *)render_ctl)->unk_10 = 0x20;
            ((S_80174934_3 *)render_ctl)->unk_14 |= 0xC;

            position = ((S_80174934_2 *)strip_obj)->unk_08;
            ((S_80174934_4 *)position)->unk_00 = origin->x;
            ((S_80174934_4 *)position)->unk_04 = origin->y;
            ((S_80174934_4 *)position)->unk_08 = origin->z;

            render_ctl = ((S_80174934_2 *)strip_obj)->unk_0C;
            ((S_80174934_3 *)render_ctl)->unk_1E = 0x1000;
            ((S_80174934_3 *)render_ctl)->unk_1C = 0x1000;
            render_ctl[0xE] = 0x80;
            render_ctl[0xD] = 0x80;
            render_ctl[0xC] = 0x80;

            vertex_index = 0;
            do {
                vertex_color = (u32 *)strip_data + vertex_index;
                ((u8 *)vertex_color)[4] = render_data[0xC];
                ((u8 *)vertex_color)[5] = render_data[0xD];
                next_vertex = vertex_index + 1;
                vertex_index = next_vertex;
                ((u8 *)vertex_color)[6] = render_data[0xE];
            } while (next_vertex < 4);

            if (strip_index == 3) {
                strip_data[0xA] = 0;
                strip_data[9] = 0;
                strip_data[8] = 0;
                strip_data[6] = 0;
                strip_data[5] = 0;
                strip_data[4] = 0;
            }

            ((S_80174934_3 *)render_ctl)->unk_06 = 0;
            memcpy(strip_data + 0x28, D_80175910, 12);
            frame_data = strip_data + 0x28;
            ((S_80174934_3 *)render_ctl)->unk_08 = frame_data;
            frame_data[8] = (u8)(frame_data[8] + ((S_80174934_0 *)effect)->unk_1E * 4);
            frame_data = ((S_80174934_3 *)render_ctl)->unk_08;
            frame_data[9] = (u8)(frame_data[9] + ((((S_80174934_0 *)effect)->unk_20 & 3) * 8));

            row_index = 0;
            do {
                axis_index = 0;
                do {
                    ((Rows *)strip_data)->row[row_index][axis_index] =
                        ((Rows *)effect)->row[row_index][axis_index];
                    next_axis = axis_index + 1;
                    axis_index = next_axis;
                } while (next_axis < 3);
                next_row = row_index + 1;
                row_index = next_row;
            } while (next_row < 4);

            top = 0 - ((strip_index + 1) * 0x10);
            bottom = 0 - (strip_index * 0x10);
            ((S_80174934_1 *)strip_data)->unk_6E = top;
            ((S_80174934_1 *)strip_data)->unk_68 = top;
            ((S_80174934_1 *)strip_data)->unk_7A = bottom;
            ((S_80174934_1 *)strip_data)->unk_74 = bottom;
        }
    }

    frames_left = ((S_80174934_0 *)effect)->unk_1A.u - 1;
    ((S_80174934_0 *)effect)->unk_1A.s = frames_left;
    if (frames_left <= 0) {
        (*(u16 *)((u8 *)effect + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
    return;
}
