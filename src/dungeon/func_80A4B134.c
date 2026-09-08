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
extern void func_80174BC8() __attribute__((noreturn));
extern void *memcpy(void *, const void *, u32);

extern s32 D_800814A0;
extern u8 D_8017489C[12];
extern u8 D_801748F0[12];
extern u8 D_80175910[12];

void func_80174934(u8 *arg0, Vec3w *arg1, u8 *arg2)
{
    s16 phase;
    u16 phase_u;
    s16 i;
    s16 color_i;
    s16 color_next;
    s16 row_i;
    s16 row_next;
    s16 col_i;
    s16 col_next;
    s16 counter;
    s16 top;
    s16 bottom;
    s32 shade;
    s32 random_low;
    u8 *obj;
    u8 *call_obj;
    u8 *work;
    u8 *ctl;
    u8 *pos;
    u8 *vec;
    void *callback;
    u32 *color;

    phase = ((S_80174934_0 *)arg0)->unk_16.s;
    phase_u = ((S_80174934_0 *)arg0)->unk_16.u;
    if (phase != 1) {
        if (phase < 2) {
            if (phase == 0)
                goto phase_zero;
            func_80174BC8();
        } else {
            if (phase != 2) {
                func_80174BC8();
            }

            goto phase_two;
        }

phase_zero:
        arg2[0xC] = (u8)((arg0[4] *
            (0x32 - ((S_80174934_0 *)arg0)->unk_1A.s)) / 10);
        arg2[0xD] = (u8)((arg0[5] *
            (0x32 - ((S_80174934_0 *)arg0)->unk_1A.s)) / 10);
        shade = 0x32 - ((S_80174934_0 *)arg0)->unk_1A.s;
        arg2[0xE] = (u8)((arg0[6] * shade) / 10);
        if (((S_80174934_0 *)arg0)->unk_1A.s < 0x29) {
            ((S_80174934_0 *)arg0)->unk_16.p =
                ((S_80174934_0 *)arg0)->unk_16.u + 1;
            func_80174BC8();
        }

        goto build_objects;
    }

    if (((S_80174934_0 *)arg0)->unk_1A.s < 0xC) {
        ((S_80174934_0 *)arg0)->unk_16.s = phase_u + 1;
    }

    if (func_80069EF8() & 1) {
        work = (u8 *)(func_80069EF8() & 7);
        obj = (u8 *)(func_80069EF8() & 0xFF);
        obj = (u8 *)((s32)obj | 0x80);
        random_low = func_80069EF8();
        func_80174214(arg0 - 0x20, (s32)work, 0xF0, (s32)obj,
            ((S_80174934_0 *)arg0)->unk_64, ((S_80174934_0 *)arg0)->unk_66,
            (s16)(-0x70 - (random_low & 0x1F)));
    } else {
        work = (u8 *)(func_80069EF8() & 7);
        obj = (u8 *)(func_80069EF8() & 0xFF);
        obj = (u8 *)((s32)obj | 0x80);
        random_low = func_80069EF8();
        func_80174214(arg0 - 0x20, (s32)work, 0xF0, (s32)obj,
            ((S_80174934_0 *)arg0)->unk_64, ((S_80174934_0 *)arg0)->unk_66,
            (s16)(-0x40 - (random_low & 0x1F)));
    }
    func_80174BC8();

phase_two:
    arg2[0xC] = (u8)((arg0[4] * ((S_80174934_0 *)arg0)->unk_1A.s) / 10);
    arg2[0xD] = (u8)((arg0[5] * ((S_80174934_0 *)arg0)->unk_1A.s) / 10);
    arg2[0xE] = (u8)((arg0[6] * ((S_80174934_0 *)arg0)->unk_1A.s) / 10);

build_objects:
        ((S_80174934_0 *)arg0)->unk_20 = ((S_80174934_0 *)arg0)->unk_20 + 1;
        i = 0;
        do {
            obj = func_8003FC64(0x12);
            if (obj != 0) {
                call_obj = obj;
                ASM_KEEP(call_obj);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                callback = D_8017489C;
                ASM_KEEP(callback);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                work = obj + 0x20;
                ((S_80174934_1 *)work)->unk_1A = 1;
                ((S_80174934_1 *)work)->unk_1C = 1;
                ((S_80174934_2 *)obj)->unk_10 = D_801748F0;
                func_8004491C(call_obj, callback);

                ctl = ((S_80174934_2 *)obj)->unk_0C;
                ((S_80174934_3 *)ctl)->unk_10 = 0x20;
                ((S_80174934_3 *)ctl)->unk_14 |= 0xC;

                pos = ((S_80174934_2 *)obj)->unk_08;
                ((S_80174934_4 *)pos)->unk_00 = arg1->x;
                ((S_80174934_4 *)pos)->unk_04 = arg1->y;
                ((S_80174934_4 *)pos)->unk_08 = arg1->z;

                ctl = ((S_80174934_2 *)obj)->unk_0C;
                ((S_80174934_3 *)ctl)->unk_1E = 0x1000;
                ((S_80174934_3 *)ctl)->unk_1C = 0x1000;
                ctl[0xE] = 0x80;
                ctl[0xD] = 0x80;
                ctl[0xC] = 0x80;

                color_i = 0;
                do {
                    color = (u32 *)work + color_i;
                    ((u8 *)color)[4] = arg2[0xC];
                    ((u8 *)color)[5] = arg2[0xD];
                    color_next = color_i + 1;
                    color_i = color_next;
                    ((u8 *)color)[6] = arg2[0xE];
                } while (color_next < 4);

                if (i == 3) {
                    work[0xA] = 0;
                    work[9] = 0;
                    work[8] = 0;
                    work[6] = 0;
                    work[5] = 0;
                    work[4] = 0;
                }

                ((S_80174934_3 *)ctl)->unk_06 = 0;
                memcpy(work + 0x28, D_80175910, 12);
                vec = work + 0x28;
                ((S_80174934_3 *)ctl)->unk_08 = vec;
                vec[8] = (u8)(vec[8] + ((S_80174934_0 *)arg0)->unk_1E * 4);
                vec = ((S_80174934_3 *)ctl)->unk_08;
                vec[9] = (u8)(vec[9] + ((((S_80174934_0 *)arg0)->unk_20 & 3) * 8));

                row_i = 0;
                do {
                    col_i = 0;
                    do {
                        ((Rows *)work)->row[row_i][col_i] =
                            ((Rows *)arg0)->row[row_i][col_i];
                        col_next = col_i + 1;
                        col_i = col_next;
                    } while (col_next < 3);
                    row_next = row_i + 1;
                    row_i = row_next;
                } while (row_next < 4);

                top = 0 - ((i + 1) * 0x10);
                bottom = 0 - (i * 0x10);
                ((S_80174934_1 *)work)->unk_6E = top;
                ((S_80174934_1 *)work)->unk_68 = top;
                ((S_80174934_1 *)work)->unk_7A = bottom;
                ((S_80174934_1 *)work)->unk_74 = bottom;
            }
            i++;
        } while (i < 4);

        counter = ((S_80174934_0 *)arg0)->unk_1A.u - 1;
        ((S_80174934_0 *)arg0)->unk_1A.s = counter;
        if (counter <= 0) {
            (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
            D_800814A0 |= 0x8000;
        }
        return;
}
