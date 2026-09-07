#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

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

    phase = FIELD(arg0, s16, 0x16);
    phase_u = FIELD(arg0, volatile u16, 0x16);
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
            (0x32 - FIELD(arg0, s16, 0x1A))) / 10);
        arg2[0xD] = (u8)((arg0[5] *
            (0x32 - FIELD(arg0, s16, 0x1A))) / 10);
        shade = 0x32 - FIELD(arg0, s16, 0x1A);
        arg2[0xE] = (u8)((arg0[6] * shade) / 10);
        if (FIELD(arg0, s16, 0x1A) < 0x29) {
            FIELD(arg0, u16, 0x16) =
                FIELD(arg0, volatile u16, 0x16) + 1;
            func_80174BC8();
        }

        goto build_objects;
    }

    if (FIELD(arg0, s16, 0x1A) < 0xC) {
        FIELD(arg0, s16, 0x16) = phase_u + 1;
    }

    if (func_80069EF8() & 1) {
        work = (u8 *)(func_80069EF8() & 7);
        obj = (u8 *)(func_80069EF8() & 0xFF);
        obj = (u8 *)((s32)obj | 0x80);
        random_low = func_80069EF8();
        func_80174214(arg0 - 0x20, (s32)work, 0xF0, (s32)obj,
            FIELD(arg0, s16, 0x64), FIELD(arg0, s16, 0x66),
            (s16)(-0x70 - (random_low & 0x1F)));
    } else {
        work = (u8 *)(func_80069EF8() & 7);
        obj = (u8 *)(func_80069EF8() & 0xFF);
        obj = (u8 *)((s32)obj | 0x80);
        random_low = func_80069EF8();
        func_80174214(arg0 - 0x20, (s32)work, 0xF0, (s32)obj,
            FIELD(arg0, s16, 0x64), FIELD(arg0, s16, 0x66),
            (s16)(-0x40 - (random_low & 0x1F)));
    }
    func_80174BC8();

phase_two:
    arg2[0xC] = (u8)((arg0[4] * FIELD(arg0, s16, 0x1A)) / 10);
    arg2[0xD] = (u8)((arg0[5] * FIELD(arg0, s16, 0x1A)) / 10);
    arg2[0xE] = (u8)((arg0[6] * FIELD(arg0, s16, 0x1A)) / 10);

build_objects:
        FIELD(arg0, u16, 0x20) = FIELD(arg0, u16, 0x20) + 1;
        i = 0;
        do {
            obj = func_8003FC64(0x12);
            if (obj != 0) {
                ASM_SCHED_BARRIER();
                call_obj = obj;
                ASM_KEEP(call_obj);
                callback = D_8017489C;
                ASM_KEEP(callback);
                work = obj + 0x20;
                FIELD(work, s16, 0x1A) = 1;
                FIELD(work, s16, 0x1C) = 1;
                FIELD(obj, void *, 0x10) = D_801748F0;
                func_8004491C(call_obj, callback);

                ctl = FIELD(obj, u8 *, 0xC);
                FIELD(ctl, s16, 0x10) = 0x20;
                FIELD(ctl, u16, 0x14) |= 0xC;

                pos = FIELD(obj, u8 *, 8);
                FIELD(pos, s32, 0) = arg1->x;
                FIELD(pos, s32, 4) = arg1->y;
                FIELD(pos, s32, 8) = arg1->z;

                ctl = FIELD(obj, u8 *, 0xC);
                FIELD(ctl, s16, 0x1E) = 0x1000;
                FIELD(ctl, s16, 0x1C) = 0x1000;
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

                FIELD(ctl, s16, 6) = 0;
                memcpy(work + 0x28, D_80175910, 12);
                vec = work + 0x28;
                FIELD(ctl, u8 *, 8) = vec;
                vec[8] = (u8)(vec[8] + FIELD(arg0, s16, 0x1E) * 4);
                vec = FIELD(ctl, u8 *, 8);
                vec[9] = (u8)(vec[9] + ((FIELD(arg0, u16, 0x20) & 3) * 8));

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
                FIELD(work, s16, 0x6E) = top;
                FIELD(work, s16, 0x68) = top;
                FIELD(work, s16, 0x7A) = bottom;
                FIELD(work, s16, 0x74) = bottom;
            }
            i++;
        } while (i < 4);

        counter = FIELD(arg0, u16, 0x1A) - 1;
        FIELD(arg0, s16, 0x1A) = counter;
        if (counter <= 0) {
            FIELD(arg0, u16, -2) |= 0x8000;
            D_800814A0 |= 0x8000;
        }
        return;
}
