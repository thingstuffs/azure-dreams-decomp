#include "common.h"


extern void func_80047784(void *, u8, s32);
extern s32 rand(void);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_800D5DCC(void *, s16, s32, s32);
extern void func_801708B8(void *, void *, void *);
extern void func_80173938(void) __attribute__((noreturn));
extern void func_80173A3C(void) __attribute__((noreturn));

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_8008346C;
extern u8 D_800E23E0[];
extern u8 D_800E2400[];
extern void *D_80170850[];
extern u8 D_80171A80[];


typedef struct S_80173510_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x2];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    union { u8 n; volatile u8 v; } unk_9B;   /* accessed as both */
    u8 pad_9C[0x14];
    u8 unk_B0;
} S_80173510_0;   /* arg0 in func_80173510 */

typedef struct S_80173510_1 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 unk_05;
    u8 pad_06[0xE];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80173510_1;   /* arg2 in func_80173510 */

typedef struct S_80173510_2 {
    u8 pad_00[0x2A];
    union { s16 s; u16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_80173510_2;   /* arg3 in func_80173510 */

typedef struct S_80173510_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80173510_3;   /* arg1 in func_80173510 */

void func_80173510(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const jt_keep[] = { &&L0, &&L1, &&L2, &&L3, &&L4, &&L5 };
    u8 state;

    state = ((S_80173510_0 *)arg0)->unk_9B.n;
    if ((u32)state >= 6) {
        return;
    }
    (void)jt_keep;
    goto *D_80170850[state];

L0:
    if (((S_80173510_1 *)arg2)->unk_14 & 0x8000) {
        u8 *model;

        ((S_80173510_0 *)arg0)->unk_9B.n = 5;
        ((S_80173510_0 *)arg0)->unk_96.u = 0;
        ((S_80173510_1 *)arg2)->unk_14 |= 0x6000;
        func_8009C12C(arg3, arg2, ((S_80173510_2 *)arg3)->unk_2A.s, 1);

        model = D_800E23E0;
        (*(u8 * *)((u8 *)arg2 + (0x2C))) = model;
        func_80047784(arg2,
            model[((D_80083228 + ((S_80173510_2 *)arg3)->unk_2A.s + 0x100) >> 9) & 7],
            0);
        if (((S_80173510_0 *)arg0)->unk_B0 != 0) {
            return;
        }
        func_801708B8(arg0, arg1, arg2);
        func_80173A3C();
    }

    ((S_80173510_3 *)arg1)->unk_14 = 0;
    ((S_80173510_3 *)arg1)->unk_10 = 0;
    ((S_80173510_3 *)arg1)->unk_0C = 0;
    ((S_80173510_0 *)arg0)->unk_96.u = 2;
    ((S_80173510_0 *)arg0)->unk_98 &= 0xFFF7;
    ((S_80173510_0 *)arg0)->unk_9B.n++;
    func_80173A3C();

L1:
    {
        s16 *base_x;
        s16 *base_y;
        u16 timer;

        timer = ((S_80173510_0 *)arg0)->unk_96.u;
        ((S_80173510_0 *)arg0)->unk_96.u = timer - 1;
        if ((s16)timer > 0 && !(((S_80173510_1 *)arg2)->unk_14 & 0x8000)) {
            return;
        }

        ((S_80173510_0 *)arg0)->unk_96.u = 0x12;
        base_x = (s16 *)&D_8006CCD8;
        ((S_80173510_0 *)arg0)->unk_9B.n++;
        base_y = (s16 *)&D_8006CCE8;
        ((S_80173510_3 *)arg1)->unk_0C =
            -*(s16 *)((u8 *)base_x +
              ((((S_80173510_2 *)arg3)->unk_2A.u >> 8) & 0xE)) << 18;
        ((S_80173510_3 *)arg1)->unk_10 =
            -*(s16 *)((u8 *)base_y +
              ((((S_80173510_2 *)arg3)->unk_2A.u >> 8) & 0xE)) << 18;
        func_80173A3C();
    }

L2:
    {
        s16 *base_x;
        s16 *base_y;
        s32 eight;
        s8 kind;
        u16 timer;

        if (((S_80173510_0 *)arg0)->unk_96.s == 0xB) {
            ((S_80173510_3 *)arg1)->unk_0C = 0;
            ((S_80173510_3 *)arg1)->unk_10 = 0;
        }

        eight = 8;
        if (((S_80173510_0 *)arg0)->unk_96.s == eight) {
            u8 *model;

            model = D_800E2400;
            (*(u8 * *)((u8 *)arg2 + (0x2C))) = model;
            func_80047784(arg2,
                model[((D_80083228 + ((S_80173510_2 *)arg3)->unk_2A.s + 0x100) >> 9) & 7],
                1);

            base_x = (s16 *)&D_8006CCD8;
            base_y = (s16 *)&D_8006CCE8;
            ((S_80173510_3 *)arg1)->unk_0C =
                *(s16 *)((u8 *)base_x +
                  ((((S_80173510_2 *)arg3)->unk_2A.u >> 8) & 0xE)) << 19;
            ((S_80173510_3 *)arg1)->unk_10 =
                *(s16 *)((u8 *)base_y +
                  ((((S_80173510_2 *)arg3)->unk_2A.u >> 8) & 0xE)) << 19;
        }

        kind = ((S_80173510_1 *)arg2)->unk_04;
        if (kind == 4 || kind == eight) {
            s32 i;

            func_800A56E0(0x706);
            i = 0x14;
            do {
                s32 random;

                i--;
                random = rand();
                func_800D5DCC((u8 *)arg0 - 0x20,
                    ((S_80173510_2 *)arg3)->unk_2A.s, 0x8080FF,
                    (random & 0xFF) | 0x80);
            } while (i >= 0);
        }

        timer = ((S_80173510_0 *)arg0)->unk_96.u;
        ((S_80173510_0 *)arg0)->unk_96.u = timer - 1;
        if ((s16)timer <= 0 || (((S_80173510_1 *)arg2)->unk_14 & 0x8000)) {
            ((S_80173510_0 *)arg0)->unk_96.u = 4;
            ((S_80173510_0 *)arg0)->unk_9B.n++;
        }

        if (((S_80173510_1 *)arg2)->unk_2C != D_800E2400) {
            return;
        }
        ((S_80173510_1 *)arg2)->unk_05 = 0;
        func_80173A3C();
    }

L3:
    {
        register u32 state_step ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
        s16 timer;

        timer = ((S_80173510_0 *)arg0)->unk_96.u - 1;
        ((S_80173510_0 *)arg0)->unk_96.u = timer;
        if (timer == 3 || (((S_80173510_1 *)arg2)->unk_14 & 0x8000)) {
            u8 *model;

            ((S_80173510_3 *)arg1)->unk_14 = 0;
            ((S_80173510_3 *)arg1)->unk_10 = 0;
            ((S_80173510_3 *)arg1)->unk_0C = 0;
            func_8009C12C(arg3, arg2, ((S_80173510_2 *)arg3)->unk_2A.s, 1);

            model = D_800E23E0;
            (*(u8 * *)((u8 *)arg2 + (0x2C))) = model;
            func_80047784(arg2,
                model[((D_80083228 + ((S_80173510_2 *)arg3)->unk_2A.s + 0x100) >> 9) & 7],
                0);
            ((S_80173510_0 *)arg0)->unk_92 = -0x20;
            if (((S_80173510_0 *)arg0)->unk_B0 == 0) {
                func_801708B8(arg0, arg1, arg2);
            }
        }

        if (((S_80173510_0 *)arg0)->unk_96.s > 0 &&
            !(((S_80173510_1 *)arg2)->unk_14 & 0x8000)) {
            return;
        }
        (void)((S_80173510_0 *)arg0)->unk_9B.v;
        state_step = 2;
        ASM_TAILSLOT_PIN(state_step);   /* MATCH pin: retail delay-slot contents depend on it */
        func_80173938();
    }

L4:
    {
        u16 timer;

        timer = ((S_80173510_0 *)arg0)->unk_96.u;
        ((S_80173510_0 *)arg0)->unk_96.u = timer - 1;
        if ((s16)timer > 0 && !(((S_80173510_1 *)arg2)->unk_14 & 0x8000)) {
            return;
        }
        ((S_80173510_0 *)arg0)->unk_96.u = 6;
        ((S_80173510_0 *)arg0)->unk_9B.n++;
        func_80173A3C();
    }

L5:
    {
        s32 delta;
        s32 position;
        s16 timer;

        timer = ((S_80173510_0 *)arg0)->unk_96.s;
        if (timer != 0) {
            delta = ((S_80173510_1 *)arg2)->unk_24 << 6;
            position = ((S_80173510_3 *)arg1)->unk_02;
            position -= 0x20;
            delta -= position;
            ((S_80173510_3 *)arg1)->unk_0C = (delta << 16) / timer;

            position = ((S_80173510_3 *)arg1)->unk_06;
            delta = ((S_80173510_1 *)arg2)->unk_25 << 6;
            position -= 0x20;
            delta -= position;
            ((S_80173510_3 *)arg1)->unk_10 =
                (delta << 16) / ((S_80173510_0 *)arg0)->unk_96.s;
        }

        ((S_80173510_0 *)arg0)->unk_96.u--;
        if (((S_80173510_0 *)arg0)->unk_96.s > 0 &&
            !(((S_80173510_1 *)arg2)->unk_14 & 0x8000)) {
            return;
        }

        func_800AD594(arg3, 0x100);
        ((S_80173510_0 *)arg0)->unk_8C = D_80171A80;
        D_8008346C = 0;
        func_800A4ACC(arg3);
        ((S_80173510_3 *)arg1)->unk_0C = 0;
        ((S_80173510_3 *)arg1)->unk_10 = 0;
        ((S_80173510_3 *)arg1)->unk_02 = ((S_80173510_1 *)arg2)->unk_24 * 0x40 + 0x20;
        ((S_80173510_3 *)arg1)->unk_06 = ((S_80173510_1 *)arg2)->unk_25 * 0x40 + 0x20;
        ((S_80173510_2 *)arg3)->unk_46 &= 0x7FFF;
    }
}
