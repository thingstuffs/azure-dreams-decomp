#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

extern s16 D_80083228;
extern s32 D_8008346C;
extern u8 D_8017102C[];
extern u8 D_801752DC[];

void func_801729A8(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 state;
    s32 next_state;
    s32 one;
    u16 timer;

    state = FIELD(arg0, u8, 0x9B);
    one = 1;
    if (state == one) {
        goto state_1;
    }
    if (!(state < 2)) {
        goto state_ge_2;
    }
    if (state == 0) {
        goto state_0;
    }
    goto end;

state_ge_2:
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    goto end;

state_0:
    FIELD(arg0, u8, 0x9B) = one;

state_1:
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        FIELD(arg0, u8, 0x9B) = 3;
        FIELD(arg2, u16, 0x14) |= 0x6000;
        func_8009C12C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1);
        goto end;
    }

    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    FIELD(arg2, u8 *, 0x2C) = D_801752DC;
    func_80047784(arg2,
        D_801752DC[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    next_state = FIELD(arg0, u8, 0x9B);
    FIELD(arg0, u16, 0x96) = 0;
    goto bump_state;

state_2:
    timer = FIELD(arg0, u16, 0x96) + 1;
    FIELD(arg0, u16, 0x96) = timer;
    if ((s16)timer == 7 || (FIELD(arg2, u16, 0x14) & 0x8000)) {
        func_8009C12C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1);
    }
    if (FIELD(arg0, s16, 0x96) == 6) {
        func_800A56E0(0x808);
    }
    if (FIELD(arg0, s16, 0x96) == 8) {
        FIELD(arg2, u16, 0x14) |= 0x0800;
    }
    if (FIELD(arg0, s16, 0x96) == 15 ||
        (FIELD(arg2, u16, 0x14) & 0x8000)) {
        FIELD(arg2, u16, 0x14) &= 0xF7FF;
        next_state = FIELD(arg0, u8, 0x9B);
        goto bump_state;
    }
    goto end;

bump_state:
    next_state++;
    FIELD(arg0, u8, 0x9B) = next_state;
    goto end;

state_3:
    if (FIELD(arg2, u16, 0x14) & 0xE000) {
        func_800AD594(arg3, 0x100);
        FIELD(arg0, u8 *, 0x8C) = D_8017102C;
        D_8008346C = 0;
        func_800A4ACC(arg3);
        FIELD(arg3, u16, 0x46) &= 0x7FFF;
    }

end:
    return;
}
