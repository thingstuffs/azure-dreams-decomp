#include "common.h"

#define FIELD(p, t, off) (*(t)((s8 *)(p) + (off)))

extern s32 D_800814A0;
extern u8 D_800DDC40[];
extern void func_800247B0(void *, void *, s16);
extern void func_800249C4(void *, void *, s16, s32);
extern void func_80024D2C(void *, void *, s16, s16);
extern void func_80025328(void) __attribute__((noreturn));
extern s32 func_80069EF8(void);

void func_818BD74C(void *arg0, void *arg1, void *arg2) {
    s16 temp_a0;
    s32 temp_a2;
    s16 temp_v1_2;
    s16 var_a1;
    s32 var_v0;
    s32 temp_a0_2;
    u32 temp_a0_shift;
    s32 temp_v0;
    s32 temp_state0_0;
    s32 temp_state0_c;
    s32 temp_state0_10;
    s32 temp_state0_14;
    s32 temp_state0_4;
    s32 temp_state0_8;
    u16 temp_state2_e;
    u16 temp_head_10;
    u16 temp_head_12;
    u16 temp_head_16;
    s32 var_v1;
    void *temp_s1;
    void *temp_s2;
    void *temp_v1;
    u8 *temp_s0;

    temp_s1 = arg0;
    temp_v1 = FIELD(temp_s1, void **, 0);
    FIELD(temp_v1, u16 *, 0x14) = (s16)(FIELD(temp_v1, u16 *, 0x14) + 1);
    temp_s2 = arg1;
    temp_head_10 = FIELD(temp_s1, u16 *, 0x10);
    temp_head_12 = FIELD(temp_s1, u16 *, 0x12);
    ASM_SCHED_BARRIER();
    FIELD(temp_s1, u16 *, 0x10) = (u16)(temp_head_10 + 1);
    FIELD(temp_s1, u16 *, 0x12) = (u16)(temp_head_12 + 1);
    temp_head_16 = FIELD(temp_s1, u16 *, 0x16);
    FIELD(temp_s1, u16 *, 0x16) = (u16)(temp_head_16 + 0x140);
    if (FIELD(temp_s1, s16 *, 0xE) != 0) {
        temp_a0 = (s16)FIELD(temp_s1, u16 *, 0x12);
        temp_a0 = (s16)(temp_a0 % 7);
        temp_a0 += 1;
        temp_a0_shift = (u32)(temp_a0 << 0x10);
        var_a1 = (s16)(temp_a0_shift >> 0x10);
        var_v0 = var_a1;
        if (var_a1 < 0) {
            var_v0 += 3;
        }
        temp_a0_2 = (s32)(var_a1 + (temp_a0_shift >> 0x1F)) >> 1;
        FIELD(arg2, s8 *, 0xC) = (s8)(((var_v0 >> 2) << 7) + 0x40);
        FIELD(arg2, s8 *, 0xD) = (s8)(((s32)(((s16)temp_a0_2 - (((s32)((s16)temp_a0_2 + ((u32)(temp_a0_2 << 0x10) >> 0x1F)) >> 1) * 2)) << 0x10) >> 9) + 0x40);
        FIELD(arg2, s8 *, 0xE) = (s8)(((s32)((var_a1 - (temp_a0_2 * 2)) << 0x10) >> 9) + 0x40);
    }
    FIELD(arg2, u16 *, 0x1A) = (u16)(FIELD(arg2, u16 *, 0x1A) + 0x300);
    temp_v1_2 = FIELD(temp_s1, s16 *, 0xE);
    if (temp_v1_2 == 1) {
        goto state1;
    }
    if (temp_v1_2 >= 2) {
        goto state_ge2;
    }
    if (temp_v1_2 == 0) {
        goto state0;
    }
    func_80025328();
    return;

state_ge2:
    ASM_SCHED_BARRIER();
    temp_v0 = 2;
    
    if (temp_v1_2 != temp_v0) {
        func_80025328();
        return;
    }
    goto state2;

state0:
    temp_state0_0 = FIELD(temp_s2, s32 *, 0);
    temp_state0_c = FIELD(temp_s2, s32 *, 0xC);
    temp_state0_10 = FIELD(temp_s2, s32 *, 0x10);
    temp_state0_14 = FIELD(temp_s2, s32 *, 0x14);
    FIELD(temp_s2, s32 *, 0) = temp_state0_0 + temp_state0_c;
    temp_state0_4 = FIELD(temp_s2, s32 *, 4);
    temp_state0_8 = FIELD(temp_s2, s32 *, 8);
    FIELD(temp_s2, s32 *, 4) = temp_state0_4 + temp_state0_10;
    FIELD(temp_s2, s32 *, 8) = temp_state0_8 + temp_state0_14;
    if (FIELD(temp_s1, s16 *, 0x10) < FIELD(temp_s1, s16 *, 0x14)) {
        func_80025328();
        return;
    }
    goto advance;

state1:
    FIELD(arg2, s16 *, 0x12) = 0;
    FIELD(arg2, u16 *, 0x14) = (u16)(FIELD(arg2, u16 *, 0x14) & 0xFEFF);
    temp_v0 = (0x19 - FIELD(temp_s1, s16 *, 0x10)) << 8;
    FIELD(arg2, s16 *, 0x1E) = temp_v0;
    FIELD(arg2, s16 *, 0x1C) = temp_v0;
    if (FIELD(temp_s1, s16 *, 0x10) < 0x10) {
        return;
    }
    temp_a2 = (s16)func_80069EF8();
    temp_s0 = D_800DDC40;
    var_v1 = temp_s0[FIELD(FIELD(temp_s1, void **, 0x18), u8 *, 0x13)] * 3;
    if (var_v1 < 0) {
        var_v1 += 3;
    }
    func_800249C4(temp_s1, temp_s2, (s16)temp_a2, 0 - (var_v1 >> 2));
    func_800247B0(temp_s1, temp_s2, temp_s0[FIELD(FIELD(temp_s1, void **, 0x18), u8 *, 0x13)]);
    goto advance;

advance:
    FIELD(temp_s1, s16 *, 0x10) = 0;
    FIELD(temp_s1, u16 *, 0xE) = (u16)(FIELD(temp_s1, u16 *, 0xE) + 1);
    func_80025328();

state2:
    func_80024D2C(temp_s1, temp_s2, (s16)(func_80069EF8() % 7), FIELD(temp_s1, s16 *, 0x16));
    func_80024D2C(temp_s1, temp_s2, (s16)(func_80069EF8() % 7), (s16)((u16)FIELD(temp_s1, s16 *, 0x16) + 0x400));
    func_80024D2C(temp_s1, temp_s2, (s16)(func_80069EF8() % 7), (s16)((u16)FIELD(temp_s1, s16 *, 0x16) + 0x800));
    func_80024D2C(temp_s1, temp_s2, (s16)(func_80069EF8() % 7), (s16)((u16)FIELD(temp_s1, s16 *, 0x16) + 0xC00));
    if (FIELD(temp_s1, s16 *, 0x10) < 0x30) {
        return;
    }
    FIELD(temp_s1, s16 *, 0x10) = 0;
    FIELD(temp_s1, u16 *, -2) = (u16)(FIELD(temp_s1, u16 *, -2) | 0x8000);
    temp_state2_e = *(volatile u16 *)((s8 *)temp_s1 + 0xE);
    {
        s32 temp_global = D_800814A0;
        *(volatile u16 *)((s8 *)temp_s1 + 0xE) = (u16)(temp_state2_e + 1);
        D_800814A0 = temp_global | 0x8000;
    }
}
