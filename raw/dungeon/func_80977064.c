#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_80172958(void) __attribute__((noreturn));
extern void func_80172A30(void) __attribute__((noreturn));

extern s16 D_80083228[5];
extern s32 D_8008346C[5];
extern void *D_80170838[];
extern u8 D_801714D4[];
extern u8 D_80174108[];

void func_80172864(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const state_keep[] = {
        &&state_0, &&state_1, &&state_2, &&state_3, &&state_4
    };
    register void *s0 = arg0;
    register void *s1 = arg3;
    u8 state;
    u16 timer;

    state = FIELD(s0, u8, 0x9B);
    if ((u32)state >= 5) {
        goto done;
    }
    (void)state_keep;
    goto *D_80170838[state];

state_0:
    timer = FIELD(s0, u16, 0x96);
    FIELD(s0, u16, 0x96) = timer + 1;
    if ((s16)timer < 4 && !(FIELD(arg2, u16, 0x14) & 0x8000)) {
        goto done;
    }
    (void)FIELD(s0, volatile u8, 0x9B);
    FIELD(s0, u16, 0x96) = 0;
    func_80172958();

state_1:
    if (FIELD(s0, s16, 0xA2) != 0 &&
        !(FIELD(arg2, u16, 0x14) & 0x8000)) {
        goto done;
    }
    FIELD(arg2, u8 *, 0x2C) = D_80174108;
    func_80047784(
        arg2,
        D_80174108[((D_80083228[0] + FIELD(s1, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    state = FIELD(s0, u8, 0x9B);
    FIELD(s0, u16, 0x96) = 0;
    FIELD(s0, s16, 0xA2) = 0;
    FIELD(s0, s16, 0x9E) = 0;
    FIELD(s0, u8, 0x9B) = state + 1;
    func_80172A30();

state_2:
    timer = FIELD(s0, u16, 0x96) + 1;
    FIELD(s0, u16, 0x96) = timer;
    if ((s16)timer == 9 || (FIELD(arg2, u16, 0x14) & 0x8000)) {
        func_8009C12C(s1, arg2, FIELD(s1, s16, 0x2A), 1);
        FIELD(s0, u16, 0x96) = 0;
        FIELD(s0, u8, 0x9B)++;
        ASM_SCHED_BARRIER();
    }
    if (FIELD(s0, s16, 0x96) != 6) {
        goto done;
    }
    func_800A56E0(0x808);
    func_80172A30();

state_3:
state_4:
    state = FIELD(s0, u8, 0x9B);
    FIELD(s0, u16, 0x96) = 0;
    FIELD(s0, u8, 0x9B) = state + 1;
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        goto done;
    }
    func_800AD594(s1, 0x100);
    FIELD(s0, void *, 0x8C) = D_801714D4;
    D_8008346C[0] = 0;
    func_800A4ACC(s1);
    FIELD(s1, u16, 0x46) &= 0x7FFF;

done:
    return;
}
