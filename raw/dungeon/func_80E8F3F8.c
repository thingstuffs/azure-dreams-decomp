#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

#ifdef NON_MATCHING
#define LEGACY_ASM_KEEP(value) ((void)0)
#else
#define LEGACY_ASM_KEEP(value) \
    __asm__ __volatile__("" : "=r"(value) : "0"(value))
#endif

extern void func_80047784(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_80174D28(void) __attribute__((noreturn));
extern void func_80174D48(void *, void *, void *);

extern s16 D_80083228[];
extern u8 D_80083460[];
extern u8 D_801710F4[];
extern u8 D_80174F00[];

void func_80174BF8(void *arg0, void *arg1, void *arg2, void *arg3)
{
    register void *call_arg ASM_REG("$4");
    register u8 *counter ASM_REG("$3");
    u16 timer;
    u8 state;

    state = FIELD(arg0, u8, 0x9B);
    if (state != 0) {
        if (state != 1) {
            func_80174D28();
        }
        goto active;
    }

    func_800A56E0(0x50C);
    FIELD(arg0, u16, 0x96) = 10;
    func_80174D48(arg1, arg2, arg3);
    FIELD(arg3, s8, 0x48) = 0;
    FIELD(arg3, s8, 0x49) = 0;
    FIELD(arg0, u8, 0x9B)++;

active:
    if (!(FIELD(arg2, u16, 0x14) & 0x8000)) {
        timer = FIELD(arg0, u16, 0x96);
        FIELD(arg0, u16, 0x96) = timer - 1;
        if ((s16)timer > 0) {
            return;
        }
    }

    call_arg = arg3;
    LEGACY_ASM_KEEP(call_arg);
    counter = D_80083460;
    LEGACY_ASM_KEEP(counter);
    FIELD(counter, u16, 0xA)--;
    FIELD(arg2, u8 *, 0x2C) = D_80174F00;
    func_800AD594(call_arg, 0x200);
    func_80047784(arg2,
        FIELD(arg2, u8 *, 0x2C)[((D_80083228[0] + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    FIELD(arg0, u8 *, 0x8C) = D_801710F4;
    func_800A4ACC(arg3);
    FIELD(arg3, s8, 0x6D) = 0;
    FIELD(arg3, u16, 0x46) &= 0x7FFF;
}
