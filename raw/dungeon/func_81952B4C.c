#include "common.h"

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))

extern void func_800245F0(void) __attribute__((noreturn));
extern void func_80024638(void) __attribute__((noreturn));
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);

extern s16 D_800249A4;
extern u16 D_800249A6;
extern s32 D_800814A0;

void func_81952B4C(void *arg0, void *arg1, void *arg2)
{
    s16 state;
    s16 angle;
    s16 life;
    s32 x;
    s32 y;
    s32 flags;
    u16 scale;
    u8 color;

    D_800249A6++;

    if (D_800249A4 != 0 && FIELD(arg0, s16, 0x24) < 2) {
        FIELD(arg0, s32, 0) =
            func_80064584(FIELD(arg0, s16, 0x28)) *
            FIELD(arg0, s16, 0x34) * 8;
        FIELD(arg0, s32, 4) =
            func_800644B8(FIELD(arg0, s16, 0x28)) *
            FIELD(arg0, s16, 0x34) * 8;
        FIELD(arg0, s16, 0x24) = 2;
    }

    FIELD(arg1, u16, 0xE) = FIELD(arg1, u16, 2);
    FIELD(arg1, u16, 0x12) = FIELD(arg1, u16, 6);
    FIELD(arg1, u16, 0x16) = FIELD(arg1, u16, 0xA);

    state = FIELD(arg0, s16, 0x24);
    if (state == 1) {
        goto update;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        func_800245F0();
        return;
    }
    if (state == 2) {
        goto state_two;
    }
    func_800245F0();
    return;

state_zero:
    scale = FIELD(arg2, u16, 0x1E);
            scale += (0x1000 - scale) / FIELD(arg0, s16, 0x2C);
            FIELD(arg2, u16, 0x1E) = scale;
            FIELD(arg2, u16, 0x1C) = scale;
            if (scale >= 0x801) {
                FIELD(arg2, u16, 0x1E) = 0x800;
                FIELD(arg2, u16, 0x1C) = 0x800;
            }

            color = FIELD(arg2, u8, 0xE) + 2;
            FIELD(arg2, u8, 0xE) = color;
            FIELD(arg2, u8, 0xD) = color;
            FIELD(arg2, u8, 0xC) = color;
            if (color >= 0x81) {
                FIELD(arg2, s32, 0xC) = 0x00808080;
            }

            FIELD(arg1, s32, 0) =
                (FIELD(arg0, s16, 0x10) << 16) +
                func_80064584(FIELD(arg0, s16, 0x28)) *
                FIELD(arg0, s16, 0x34) * 8;
            FIELD(arg1, s32, 4) =
                (FIELD(arg0, s16, 0x12) << 16) +
                func_800644B8(FIELD(arg0, s16, 0x28)) *
                FIELD(arg0, s16, 0x34) * 8;

            FIELD(arg0, s32, 8) -= 0x5000;
            angle = (u16)FIELD(arg0, s16, 0x34) + 4;
            FIELD(arg0, s16, 0x34) = angle;
            if (angle >= 0x41) {
                FIELD(arg0, s16, 0x34) = 0x40;
            }

            FIELD(arg0, u16, 0x28) += 0x180;
            life = (u16)FIELD(arg0, s16, 0x2C) - 1;
            FIELD(arg0, s16, 0x2C) = life;
            if ((life << 16) <= 0) {
                FIELD(arg0, u16, 0x24)++;
                func_800245F0();
                return;
            }
    goto update;

state_two:
        x = FIELD(arg0, s32, 0);
        y = FIELD(arg0, s32, 4);
        FIELD(arg0, s32, 0) = x + (x >> 1);
        FIELD(arg0, s32, 4) = y + (y >> 1);
        FIELD(arg0, s32, 8) += 0x10000;

        color = FIELD(arg2, u8, 0xE) - 4;
        FIELD(arg2, u8, 0xE) = color;
        FIELD(arg2, u8, 0xD) = color;
        FIELD(arg2, u8, 0xC) = color;
        if ((s8)color > 0) {
            goto update;
        }

        FIELD(arg0, u16, -2) |= 0x8000;
        flags = D_800814A0 | 0x8000;
        FIELD(arg0, u16, 0x24)++;
        D_800814A0 = flags;
        func_80024638();
        return;

update:
    FIELD(arg0, u16, 0x2A)++;
    FIELD(arg1, s32, 0) += FIELD(arg0, s32, 0);
    FIELD(arg1, s32, 4) += FIELD(arg0, s32, 4);
    FIELD(arg1, s32, 8) += FIELD(arg0, s32, 8);
}
