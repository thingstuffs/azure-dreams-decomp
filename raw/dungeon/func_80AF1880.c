#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_80173198() __attribute__((noreturn));
extern void func_80173268(void) __attribute__((noreturn));

extern s16 D_80083228;
extern s32 D_8008346C;
extern u8 D_801717F4[];
extern u8 D_801759C0[];

void func_80173080(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 under_two;
    u16 timer;
    s32 state;

    state = FIELD(arg0, u8, 0x9B);
    if (state != 1) {
        under_two = (s32)state < 2;
        if (under_two) {
            ASM_KEEP(under_two);
            if (state == 0) {
                goto state_0;
            }
            func_80173268();
            return;
        }
        if (state == 2) {
            goto state_2;
        }
        if (state == 3) {
            goto state_3;
        }
        func_80173268();
        return;
    }

    goto state_1;

state_0:
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        FIELD(arg0, u8, 0x9B) = 3;
        FIELD(arg2, u16, 0x14) |= 0x6000;
        func_8009C12C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1);
        func_80173268();
        return;
    }
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0xC) = 0;
    func_80173198(arg3);
    return;

state_1:
    timer = FIELD(arg0, u16, 0x96) + 1;
    FIELD(arg0, u16, 0x96) = timer;
    if (((s16)timer == 4) || (FIELD(arg2, u16, 0x14) & 0x8000)) {
        u8 *table = D_801759C0;

        FIELD(arg2, u8 *, 0x2C) = table;
        func_80047784(arg2,
                     table[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                     0);
        FIELD(arg0, u16, 0x96) = 0;
        FIELD(arg0, u8, 0x9B)++;
        func_80173268();
        return;
    }
    goto done;

state_2:
    timer = FIELD(arg0, u16, 0x96) + 1;
    FIELD(arg0, u16, 0x96) = timer;
    if (((s16)timer == 7) || (FIELD(arg2, u16, 0x14) & 0x8000)) {
        func_8009C12C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1);
        FIELD(arg0, u16, 0x96) = 0;
        FIELD(arg0, u8, 0x9B)++;
    }
    if (FIELD(arg0, s16, 0x96) == 5) {
        func_800A56E0(0x808);
        func_80173268();
        return;
    }
    goto done;

state_3:
    if (FIELD(arg2, u16, 0x14) & 0xE000) {
        func_800AD594(arg3, 0x100);
        FIELD(arg0, u8 *, 0x8C) = D_801717F4;
        D_8008346C = 0;
        func_800A4ACC(arg3);
        FIELD(arg3, u16, 0x46) &= 0x7FFF;
    }

done:
    return;
}
