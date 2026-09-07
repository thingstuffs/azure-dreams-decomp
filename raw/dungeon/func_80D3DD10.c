#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

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

void func_80173510(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const jt_keep[] = { &&L0, &&L1, &&L2, &&L3, &&L4, &&L5 };
    u8 state;

    state = FIELD(arg0, u8, 0x9B);
    if ((u32)state >= 6) {
        return;
    }
    (void)jt_keep;
    goto *D_80170850[state];

L0:
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        u8 *model;

        FIELD(arg0, u8, 0x9B) = 5;
        FIELD(arg0, u16, 0x96) = 0;
        FIELD(arg2, u16, 0x14) |= 0x6000;
        func_8009C12C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1);

        model = D_800E23E0;
        FIELD(arg2, u8 *, 0x2C) = model;
        func_80047784(arg2,
            model[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        if (FIELD(arg0, u8, 0xB0) != 0) {
            return;
        }
        func_801708B8(arg0, arg1, arg2);
        func_80173A3C();
    }

    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    FIELD(arg0, u16, 0x96) = 2;
    FIELD(arg0, u16, 0x98) &= 0xFFF7;
    FIELD(arg0, u8, 0x9B)++;
    func_80173A3C();

L1:
    {
        s16 *base_x;
        s16 *base_y;
        u16 timer;

        timer = FIELD(arg0, u16, 0x96);
        FIELD(arg0, u16, 0x96) = timer - 1;
        if ((s16)timer > 0 && !(FIELD(arg2, u16, 0x14) & 0x8000)) {
            return;
        }

        FIELD(arg0, u16, 0x96) = 0x12;
        base_x = (s16 *)&D_8006CCD8;
        FIELD(arg0, u8, 0x9B)++;
        base_y = (s16 *)&D_8006CCE8;
        FIELD(arg1, s32, 0x0C) =
            -*(s16 *)((u8 *)base_x +
              ((FIELD(arg3, u16, 0x2A) >> 8) & 0xE)) << 18;
        FIELD(arg1, s32, 0x10) =
            -*(s16 *)((u8 *)base_y +
              ((FIELD(arg3, u16, 0x2A) >> 8) & 0xE)) << 18;
        func_80173A3C();
    }

L2:
    {
        s16 *base_x;
        s16 *base_y;
        s32 eight;
        s8 kind;
        u16 timer;

        if (FIELD(arg0, s16, 0x96) == 0xB) {
            FIELD(arg1, s32, 0x0C) = 0;
            FIELD(arg1, s32, 0x10) = 0;
        }

        eight = 8;
        if (FIELD(arg0, s16, 0x96) == eight) {
            u8 *model;

            model = D_800E2400;
            FIELD(arg2, u8 *, 0x2C) = model;
            func_80047784(arg2,
                model[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                1);

            base_x = (s16 *)&D_8006CCD8;
            base_y = (s16 *)&D_8006CCE8;
            FIELD(arg1, s32, 0x0C) =
                *(s16 *)((u8 *)base_x +
                  ((FIELD(arg3, u16, 0x2A) >> 8) & 0xE)) << 19;
            FIELD(arg1, s32, 0x10) =
                *(s16 *)((u8 *)base_y +
                  ((FIELD(arg3, u16, 0x2A) >> 8) & 0xE)) << 19;
        }

        kind = FIELD(arg2, s8, 4);
        if (kind == 4 || kind == eight) {
            s32 i;

            func_800A56E0(0x706);
            i = 0x14;
            do {
                s32 random;

                i--;
                random = rand();
                func_800D5DCC((u8 *)arg0 - 0x20,
                    FIELD(arg3, s16, 0x2A), 0x8080FF,
                    (random & 0xFF) | 0x80);
            } while (i >= 0);
        }

        timer = FIELD(arg0, u16, 0x96);
        FIELD(arg0, u16, 0x96) = timer - 1;
        if ((s16)timer <= 0 || (FIELD(arg2, u16, 0x14) & 0x8000)) {
            FIELD(arg0, u16, 0x96) = 4;
            FIELD(arg0, u8, 0x9B)++;
        }

        if (FIELD(arg2, u8 *, 0x2C) != D_800E2400) {
            return;
        }
        FIELD(arg2, u8, 5) = 0;
        func_80173A3C();
    }

L3:
    {
        register u32 state_step ASM_REG("$3");
        s16 timer;

        timer = FIELD(arg0, u16, 0x96) - 1;
        FIELD(arg0, u16, 0x96) = timer;
        if (timer == 3 || (FIELD(arg2, u16, 0x14) & 0x8000)) {
            u8 *model;

            FIELD(arg1, s32, 0x14) = 0;
            FIELD(arg1, s32, 0x10) = 0;
            FIELD(arg1, s32, 0x0C) = 0;
            func_8009C12C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1);

            model = D_800E23E0;
            FIELD(arg2, u8 *, 0x2C) = model;
            func_80047784(arg2,
                model[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                0);
            FIELD(arg0, s16, 0x92) = -0x20;
            if (FIELD(arg0, u8, 0xB0) == 0) {
                func_801708B8(arg0, arg1, arg2);
            }
        }

        if (FIELD(arg0, s16, 0x96) > 0 &&
            !(FIELD(arg2, u16, 0x14) & 0x8000)) {
            return;
        }
        (void)FIELD(arg0, volatile u8, 0x9B);
        state_step = 2;
        ASM_TAILSLOT_PIN(state_step);
        func_80173938();
    }

L4:
    {
        u16 timer;

        timer = FIELD(arg0, u16, 0x96);
        FIELD(arg0, u16, 0x96) = timer - 1;
        if ((s16)timer > 0 && !(FIELD(arg2, u16, 0x14) & 0x8000)) {
            return;
        }
        FIELD(arg0, u16, 0x96) = 6;
        FIELD(arg0, u8, 0x9B)++;
        func_80173A3C();
    }

L5:
    {
        s32 delta;
        s32 position;
        s16 timer;

        timer = FIELD(arg0, s16, 0x96);
        if (timer != 0) {
            delta = FIELD(arg2, u8, 0x24) << 6;
            position = FIELD(arg1, s16, 2);
            position -= 0x20;
            delta -= position;
            FIELD(arg1, s32, 0x0C) = (delta << 16) / timer;

            position = FIELD(arg1, s16, 6);
            delta = FIELD(arg2, u8, 0x25) << 6;
            position -= 0x20;
            delta -= position;
            FIELD(arg1, s32, 0x10) =
                (delta << 16) / FIELD(arg0, s16, 0x96);
        }

        FIELD(arg0, u16, 0x96)--;
        if (FIELD(arg0, s16, 0x96) > 0 &&
            !(FIELD(arg2, u16, 0x14) & 0x8000)) {
            return;
        }

        func_800AD594(arg3, 0x100);
        FIELD(arg0, u8 *, 0x8C) = D_80171A80;
        D_8008346C = 0;
        func_800A4ACC(arg3);
        FIELD(arg1, s32, 0x0C) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s16, 2) = FIELD(arg2, u8, 0x24) * 0x40 + 0x20;
        FIELD(arg1, s16, 6) = FIELD(arg2, u8, 0x25) * 0x40 + 0x20;
        FIELD(arg3, u16, 0x46) &= 0x7FFF;
    }
}
