#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void func_80047784(void *, u8, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern s16 D_80083228;
extern s32 D_8008346C;
extern u8 D_80171014[];
extern u8 D_8017423C[];

void func_801723F0(void *arg0, void *arg1, void *arg2, void *arg3) {
    s32 state;
    u16 counter;

    state = FIELD(arg0, u8, 0x9B);
    if (state == 1) {
        goto state1;
    }
    if (state >= 2) {
        goto state_ge2;
    }
    if (state == 0) {
        goto set_state1;
    }
    goto done;

state_ge2:
    if (state == 2) {
        goto state2;
    }
    if (state == 3) {
        goto state3;
    }
    goto done;

set_state1:
    FIELD(arg0, u8, 0x9B) = 1;

state1:
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        FIELD(arg0, u8, 0x9B) = 3;
        FIELD(arg2, u16, 0x14) |= 0x6000;
        func_8009C12C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1);
        goto done;
    }
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    FIELD(arg2, u8 *, 0x2C) = D_8017423C;
    func_80047784(arg2,
        D_8017423C[((s32)(D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    FIELD(arg0, u16, 0x96) = 0;
    FIELD(arg0, u8, 0x9B)++;
    func_800A56E0(0x804);
    goto done;

state2:
    counter = FIELD(arg0, u16, 0x96) + 1;
    FIELD(arg0, u16, 0x96) = counter;
    if (((s16)counter == 8) || (FIELD(arg2, u16, 0x14) & 0x8000)) {
        func_8009C12C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1);
    }

state3:
    if (FIELD(arg2, u16, 0x14) & 0xE000) {
        func_800AD594(arg3, 0x100);
        FIELD(arg0, u8 *, 0x8C) = D_80171014;
        D_8008346C = 0;
        FIELD(arg3, u16, 0x46) &= 0x7FFF;
        func_800A4ACC(arg3);
    }

done:
    return;
}
