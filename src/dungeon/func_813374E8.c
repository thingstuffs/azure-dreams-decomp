#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_8016E4E8_0 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[0xF];
    union { s16 s; u16 u; } unk_12;   /* accessed as both */
    u8 pad_14[0x4];
    union { s16 s; u16 u; } unk_18;   /* accessed as both */
    u16 unk_1A;
    s16 unk_1C;
    u16 unk_1E;
} S_8016E4E8_0;   /* arg0 in func_8016E4E8 */

typedef struct S_8016E4E8_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_8016E4E8_1;   /* arg2 in func_8016E4E8 */

typedef struct S_8016E4E8_2 {
    u8 pad_00[0x18];
    s16 unk_18;
    s16 unk_1A;
    u8 pad_1C[0x5C];
    s16 unk_78;
    u8 pad_7A[0x4];
    s16 unk_7E;
    u8 pad_80[0x4];
    s16 unk_84;
    u8 pad_86[0x4];
    s16 unk_8A;
} S_8016E4E8_2;   /* part in func_8016E4E8 */

typedef struct S_8016E4E8_3 {
    u8 pad_00[0x8];
    s32 * unk_08;
    void * unk_0C;
    void * unk_10;
} S_8016E4E8_3;   /* object in func_8016E4E8 */

typedef struct S_8016E4E8_4 {
    u8 pad_00[0x6];
    s16 unk_06;
    union { void * s; u8 * u; } unk_08;   /* accessed as both */
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8016E4E8_4;   /* effect in func_8016E4E8 */

typedef struct S_8016E4E8_5 {
    u16 unk_00;
} S_8016E4E8_5;   /* dst_word in func_8016E4E8 */

typedef struct S_8016E4E8_6 {
    u16 unk_00;
} S_8016E4E8_6;   /* src_word in func_8016E4E8 */



typedef struct {
    u8 bytes[12];
} Data12;

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern void func_800A56E0(s32);
extern void *memcpy(void *, const void *, u32);
extern void *D_801649D0[];

extern s32 D_800814A0;
extern u8 D_8016E450[];
extern u8 D_8016E4A4[];
extern Data12 D_80173B4C;

/* Advances the color fade and creates two rows of animated textured geometry. */
void func_8016E4E8(void *animation, s32 *origin, void *color)
{
    s32 bottom_y;
    register s32 next_state ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register u16 effect_flags ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u16 tick_count;
    register u16 frame_count ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 color_index;
    s32 vertex_index;
    s32 axis;
    s32 row;
    s32 one;
    s32 top_y;
    void *object;
    u8 *part;
    void *effect;
    s32 *position;
    u8 *texture;
    u8 *src_vertices;
    u8 *dst_vertices;
    register u8 *color_dst ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u8 *src_coord;
    u8 *dst_coord;
    s32 state;
    static void *const state_labels[] = {
        &&jt_c0, &&jt_default, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4
    };

    state = ((S_8016E4E8_0 *)animation)->unk_12.s;
    if ((u32)state >= 6) {
        goto common;
    }
    (void)state_labels;
    goto *D_801649D0[(u32)state];

jt_c0:
        ((S_8016E4E8_1 *)color)->unk_0C =
            (((S_8016E4E8_0 *)animation)->unk_00 * (50 - ((S_8016E4E8_0 *)animation)->unk_18.s)) / 10;
        ((S_8016E4E8_1 *)color)->unk_0D =
            (((S_8016E4E8_0 *)animation)->unk_01 * (50 - ((S_8016E4E8_0 *)animation)->unk_18.s)) / 10;
        ((S_8016E4E8_1 *)color)->unk_0E =
            (((S_8016E4E8_0 *)animation)->unk_02 * (50 - ((S_8016E4E8_0 *)animation)->unk_18.s)) / 10;
        ((S_8016E4E8_0 *)animation)->unk_18.u--;
        if (((S_8016E4E8_0 *)animation)->unk_18.s >= 41) {
            goto common;
        }
        goto increment_state_reload;

jt_c1:
        ((S_8016E4E8_0 *)animation)->unk_18.u++;
        if (((S_8016E4E8_0 *)animation)->unk_18.s < 20) {
            goto common;
        }
        next_state = ((S_8016E4E8_0 *)animation)->unk_12.u;
        ((S_8016E4E8_0 *)animation)->unk_18.u = 0;
        goto increment_state_loaded;

jt_c2:
        next_state = ((S_8016E4E8_0 *)animation)->unk_12.u;
        ((S_8016E4E8_0 *)animation)->unk_18.u = 20;
        goto increment_state_loaded;

jt_c3:
        ((S_8016E4E8_0 *)animation)->unk_18.u--;
        ((S_8016E4E8_1 *)color)->unk_0C =
            (((S_8016E4E8_0 *)animation)->unk_00 * ((S_8016E4E8_0 *)animation)->unk_18.s) / 20;
        ((S_8016E4E8_1 *)color)->unk_0D =
            (((S_8016E4E8_0 *)animation)->unk_01 * ((S_8016E4E8_0 *)animation)->unk_18.s) / 20;
        ((S_8016E4E8_1 *)color)->unk_0E =
            (((S_8016E4E8_0 *)animation)->unk_02 * ((S_8016E4E8_0 *)animation)->unk_18.s) / 20;
        if (((S_8016E4E8_0 *)animation)->unk_18.s > 0) {
            goto common;
        }
increment_state_reload:
        next_state = ((S_8016E4E8_0 *)animation)->unk_12.u;
increment_state_loaded:
        next_state++;
        ((S_8016E4E8_0 *)animation)->unk_12.u = next_state;
        goto common;

jt_c4:
        (*(u16 *)((u8 *)animation + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
        return;

jt_default:
    goto common;

common:
    row = 0;
    one = 1;
    top_y = -0x20;
    ((S_8016E4E8_0 *)animation)->unk_1E++;
outer_loop:
        object = func_8003FC64(0x12);
        part = (u8 *)object + 0x20;
        if (object != NULL) {
            ((S_8016E4E8_2 *)part)->unk_18 = one;
            ((S_8016E4E8_2 *)part)->unk_1A = one;
            ((S_8016E4E8_3 *)object)->unk_10 = D_8016E4A4;
            func_8004491C(object, D_8016E450);

            effect = ((S_8016E4E8_3 *)object)->unk_0C;
            effect_flags = ((S_8016E4E8_4 *)effect)->unk_14;
            ((S_8016E4E8_4 *)effect)->unk_10 = 0x20;
            ((S_8016E4E8_4 *)effect)->unk_14 = effect_flags | 0xC;

            position = ((S_8016E4E8_3 *)object)->unk_08;
            position[0] = origin[0];
            position[1] = origin[1];
            color_index = 0;
            position[2] = origin[2];
            color_dst = part;

            effect = ((S_8016E4E8_3 *)object)->unk_0C;
            ((S_8016E4E8_4 *)effect)->unk_1E = 0x1000;
            ((S_8016E4E8_4 *)effect)->unk_1C = 0x1000;
            ((S_8016E4E8_4 *)effect)->unk_0E = 0x80;
            ((S_8016E4E8_4 *)effect)->unk_0D = 0x80;
            ((S_8016E4E8_4 *)effect)->unk_0C = 0x80;

            do {
                color_dst[0] = ((S_8016E4E8_1 *)color)->unk_0C;
                color_dst[1] = ((S_8016E4E8_1 *)color)->unk_0D;
                color_dst[2] = ((S_8016E4E8_1 *)color)->unk_0E;
                color_index++;
                color_dst += 4;
            } while (color_index < 4);

            if (row == one) {
                part[6] = 0;
                part[5] = 0;
                part[4] = 0;
                part[2] = 0;
                part[1] = 0;
                part[0] = 0;
            }

            ((S_8016E4E8_4 *)effect)->unk_06 = 0;
            memcpy(part + 0x28, &D_80173B4C, 12);

            vertex_index = 0;
            src_vertices = (u8 *)animation;
            dst_vertices = part;
            texture = part + 0x28;
            ((S_8016E4E8_4 *)effect)->unk_08.s = texture;
            texture[8] += ((S_8016E4E8_0 *)animation)->unk_1C * 4;
            texture = ((S_8016E4E8_4 *)effect)->unk_08.u;
            frame_count = ((S_8016E4E8_0 *)animation)->unk_1E;
            texture[9] += (frame_count & 3) << 3;

            do {
                axis = 0;
                dst_coord = dst_vertices + 0x74;
                src_coord = src_vertices + 0x74;
                do {
                    ((S_8016E4E8_5 *)dst_coord)->unk_00 = ((S_8016E4E8_6 *)src_coord)->unk_00;
                    src_coord += 2;
                    axis++;
                    dst_coord += 2;
                } while (axis < 3);
                src_vertices += 6;
                vertex_index++;
                dst_vertices += 6;
            } while (vertex_index < 4);

            ((S_8016E4E8_2 *)part)->unk_7E = top_y;
            ((S_8016E4E8_2 *)part)->unk_78 = top_y;
            bottom_y = -(row << 5);
            ((S_8016E4E8_2 *)part)->unk_8A = bottom_y;
            ((S_8016E4E8_2 *)part)->unk_84 = bottom_y;
        }
        row++;
        top_y -= 0x20;
        if (row < 2) {
            goto outer_loop;
        }

    if (((S_8016E4E8_0 *)animation)->unk_12.s < 5) {
        tick_count = ((S_8016E4E8_0 *)animation)->unk_1A;
        ((S_8016E4E8_0 *)animation)->unk_1A = tick_count + 1;
        if ((tick_count & 0xF) == 1) {
            func_800A56E0(0x60E);
        }
    }
}
