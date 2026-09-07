#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_8017373C() __attribute__((noreturn));
extern void func_80173798(void) __attribute__((noreturn));

extern s16 D_80083228;
extern s32 D_8008346C;
extern u8 D_80170870[20];
extern s32 D_80171CE8;
extern u8 D_80174EE0[];

void func_80173514(void *arg0, void *arg1, void *arg2, void *arg3)
{
    u8 state;
    static void *const keepalive[] = { &&L0, &&L1, &&L2, &&L3, &&L4 };

    state = FIELD(arg0, u8, 0x9B);
    if ((u32)state >= 5) {
        return;
    }
    goto *(((void **)D_80170870)[state]);

L0:
    {
    register void *call_a0 ASM_REG("$4") = arg3;
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        FIELD(arg0, u8, 0x9B) = 4;
        FIELD(arg2, u16, 0x14) |= 0x6000;
        func_8017373C(call_a0, arg2);
        return;
    }
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    FIELD(arg2, u8 *, 0x2C) = D_80174EE0;
    func_80047784(arg2,
        D_80174EE0[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    FIELD(arg0, u16, 0x96) = 0;
    FIELD(arg0, u8, 0x9B)++;
    func_80173798();
    return;
    }

L1:
    if ((s16)++FIELD(arg0, u16, 0x96) == 5) {
        FIELD(arg0, u16, 0x96) = 0;
        FIELD(arg0, u8, 0x9B)++;
        FIELD(arg2, u16, 0x14) |= 0x0800;
        func_80173798();
    }
    return;

L2:
    if ((s16)++FIELD(arg0, u16, 0x96) == 6 ||
        (FIELD(arg2, u16, 0x14) & 0xE000)) {
        FIELD(arg0, u16, 0x96) = 0;
        FIELD(arg0, u8, 0x9B)++;
        FIELD(arg2, u16, 0x14) &= 0xF7FF;
        func_800A56E0(0x804);
        func_80173798();
    }
    return;

L3:
    if ((s16)++FIELD(arg0, u16, 0x96) == 5 ||
        (FIELD(arg2, u16, 0x14) & 0xE000)) {
        FIELD(arg2, u16, 0x14) |= 0x0800;
    }
    if (FIELD(arg0, s16, 0x96) == 12 ||
        (FIELD(arg2, u16, 0x14) & 0xE000)) {
        FIELD(arg0, u16, 0x96) = 0;
        FIELD(arg0, u8, 0x9B)++;
        FIELD(arg2, u16, 0x14) &= 0xF7FF;
    }
    if (FIELD(arg0, s16, 0x96) == 1 ||
        (FIELD(arg2, u16, 0x14) & 0xE000)) {
        func_8009C12C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1);
        func_80173798();
    }
    return;

L4:
    if (FIELD(arg2, u16, 0x14) & 0xE000) {
        func_800AD594(arg3, 0x100);
        FIELD(arg0, s32 *, 0x8C) = &D_80171CE8;
        D_8008346C = 0;
        func_800A4ACC(arg3);
        FIELD(arg3, u16, 0x46) &= 0x7FFF;
    }
}
