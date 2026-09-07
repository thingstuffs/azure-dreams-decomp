#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_80174690(void *);

extern s16 D_80083228;
extern s32 D_8008346C;
extern u8 D_80170EE4[];
extern u8 D_80176600[];
extern u8 D_80176668[];

void func_801726A4(void *arg0, void *arg1, void *arg2, void *arg3)
{
    u16 flags;
    u16 timer;
    s32 state;

    state = FIELD(arg0, u8, 0x9B);
    if (state != 1) {
        if ((s32)state < 2) {
            if (state == 0) {
                goto state_zero;
            }
            return;
        }

        if (state == 2) {
            goto state_two;
        }
        if (state == 3) {
            goto state_three;
        }
        return;
    }
    goto state_one;

state_zero:
    FIELD(arg0, u16, 0x98) |= 1;
    FIELD(arg0, u8, 0x9B)++;

state_one:
    flags = FIELD(arg2, u16, 0x14);
    if (flags & 0x8000) {
        FIELD(arg0, u8, 0x9B) = 3;
        FIELD(arg2, u16, 0x14) |= 0x6000;
        func_8009C12C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1);
        return;
    }

    if (flags & 0x6000) {
        FIELD(arg1, s32, 0xC) =
            FIELD(arg1, s32, 0x10) =
            FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg2, u8 *, 0x2C) = D_80176600;
        func_80047784(arg2,
            D_80176600[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        func_80174690((u8 *)arg0 - 0x20);
        FIELD(arg0, u16, 0x96) = 0;
        FIELD(arg0, u8, 0x9B)++;
        func_800A56E0(0x804);
        return;
    }
    return;

state_two:
    timer = FIELD(arg0, u16, 0x96) + 1;
    FIELD(arg0, u16, 0x96) = timer;

    if ((s16)timer == state ||
        (FIELD(arg2, u16, 0x14) & 0x8000)) {
        func_8009C12C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1);
    }

    if (FIELD(arg2, u16, 0x14) & 0xE000) {
        FIELD(arg2, u8 *, 0x2C) = D_80176668;
        func_80047784(arg2,
            D_80176668[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        FIELD(arg0, u8, 0x9B)++;
        FIELD(arg0, u16, 0x98) &= 0xFFFE;
        return;
    }
    return;

state_three:
    if (FIELD(arg2, u16, 0x14) & 0xE000) {
        func_800AD594(arg3, 0x100);
        FIELD(arg0, u8 *, 0x8C) = D_80170EE4;
        D_8008346C = 0;
        FIELD(arg3, u16, 0x46) &= 0x7FFF;
        func_800A4ACC(arg3);
    }
}
