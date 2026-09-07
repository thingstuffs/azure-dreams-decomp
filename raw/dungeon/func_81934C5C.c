#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

void func_80024678() __attribute__((noreturn));
void func_8002468C() __attribute__((noreturn));
void func_80024724() __attribute__((noreturn));
void *func_8003FD64();
M2C_UNK func_8004491C();
s32 func_80069EF8();
s16 func_800BCB04();
extern M2C_UNK D_80024928;
extern M2C_UNK D_80045340;
extern s32 D_800814A0[3];
extern M2C_UNK D_80083498;
extern M2C_UNK D_800DEDB0;
extern M2C_UNK D_800DEE38;

void func_81934C5C(void *arg0) {
    s32 temp_a0;
    s32 temp_v0_2;
    s16 temp_v1_2;
    register s32 temp_a2 ASM_REG("$6");
    s32 temp_a3;
    register s32 temp_state2_x ASM_REG("$2");
    register s32 temp_state2_dx ASM_REG("$3");
    s32 temp_call_a1;
    s32 temp_call_a0;
    register s32 temp_state2_step_x ASM_REG("$2");
    s32 temp_state2_step_x3;
    register s32 temp_state2_step_y3 ASM_REG("$2");
    s32 temp_state2_delta_y;
    s32 temp_state2_base_y;
    s32 temp_state2_y;
    u16 temp_v0;
    void *temp_s1;
    void *temp_v0_3;
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0);
    M2C_FIELD(arg0, u16 *, 0x48) = (u16) (M2C_FIELD(arg0, u16 *, 0x48) - 1);
    M2C_FIELD(temp_v1, u16 *, 0xE) = (u16) (M2C_FIELD(temp_v1, u16 *, 0xE) | 0x8000);
    temp_v1_2 = M2C_FIELD(arg0, s16 *, 0x4C);
    if (temp_v1_2 == 2) {
        goto block_state2;
    }
    if (temp_v1_2 < 3) {
        if (temp_v1_2 == 0) {
            goto block_state0;
        }
        if (temp_v1_2 == 1) {
            goto block_state1;
        }
        func_80024724();
        return;
    }
    if (temp_v1_2 == 3) {
        goto block_state3;
    }
    if (temp_v1_2 == 0xFF) {
        goto block_state_ff;
    }
    func_80024724();
    return;

block_state0:
    M2C_FIELD(arg0, u16 *, 0x48) = 3U;
    M2C_FIELD(arg0, s16 *, 0x2A) = -4;
    M2C_FIELD(arg0, s16 *, 0x32) = 0x10;
    M2C_FIELD(arg0, s16 *, 0x4C) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x4C) + 1);

block_state1:
    M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (M2C_FIELD(arg0, s32 *, 0x1C) + M2C_FIELD(arg0, s32 *, 0x28));
    temp_a0 = M2C_FIELD(arg0, s16 *, 0x48);
    M2C_FIELD(arg0, s32 *, 0x24) = (s32) (M2C_FIELD(arg0, s32 *, 0x24) + M2C_FIELD(arg0, s32 *, 0x30));
    if (temp_a0 <= 0) {
        func_8002468C(temp_a0);
        return;
    }
    goto block_return;

block_state2:
    temp_state2_x = M2C_FIELD(arg0, s32 *, 0x1C);
    temp_state2_dx = M2C_FIELD(arg0, s32 *, 0x28);
    temp_call_a1 = M2C_FIELD(arg0, u16 *, 0x22);
    ASM_SCHED_BARRIER();
    temp_a2 = M2C_FIELD(arg0, s16 *, 0x32);
    temp_a3 = M2C_FIELD(arg0, s32 *, 0x30);
    ASM_SCHED_BARRIER();
    ASM_KEEP(temp_state2_x);
    ASM_KEEP(temp_state2_dx);
    M2C_FIELD(arg0, s32 *, 0x1C) = temp_state2_x + temp_state2_dx;
    ASM_CLOBBER("$2");
    ASM_CLOBBER("$3");
    temp_state2_step_x = M2C_FIELD(arg0, s16 *, 0x2A);
    temp_call_a0 = M2C_FIELD(arg0, u16 *, 0x1E);
    temp_state2_step_x3 = temp_state2_step_x * 3;
    ASM_KEEP(temp_state2_step_x);
    M2C_FIELD(arg0, u16 *, 0xC) = (u16) (M2C_FIELD(arg0, u16 *, 0xC) + (temp_state2_step_x3 >> 2));
    ASM_SCHED_BARRIER();
    temp_state2_step_y3 = temp_a2 * 3;
    ASM_KEEP(temp_a2);
    ASM_KEEP(temp_state2_step_y3);
    temp_state2_delta_y = temp_state2_step_y3 >> 2;
    ASM_SCHED_BARRIER();
    temp_state2_base_y = M2C_FIELD(arg0, u16 *, 0x10);
    do {
        temp_a2 = M2C_FIELD(arg0, s32 *, 0x24);
    } while (0);
    temp_state2_y = temp_state2_base_y + temp_state2_delta_y;
    temp_a2 += temp_a3;
    M2C_FIELD(arg0, s32 *, 0x24) = temp_a2;
    M2C_FIELD(arg0, u16 *, 0x10) = temp_state2_y;
    temp_v0_2 = func_800BCB04(temp_call_a0, temp_call_a1, -0x400, temp_a3);
    if (temp_v0_2 >= 0x201) {
        if (M2C_FIELD(arg0, s16 *, 0x26) > 0) {
            goto block_tail_ff;
        }
    }
    if (temp_v0_2 >= M2C_FIELD(arg0, s16 *, 0x26)) {
        goto block_return;
    }
    M2C_FIELD(arg0, s16 *, 0x26) = temp_v0_2;
    temp_v0_3 = func_8003FD64(0x312, &D_80083498);
    if (temp_v0_3 != NULL) {
        M2C_FIELD(temp_v0_3, M2C_UNK **, 0x10) = &D_80024928;
        M2C_FIELD(temp_v0_3, void **, 0x20) = (void *) M2C_FIELD(arg0, void **, 0);
        func_8004491C(temp_v0_3, &D_80045340);
        temp_s1 = M2C_FIELD(temp_v0_3, void **, 0xC);
        M2C_FIELD(M2C_FIELD(temp_v0_3, void **, 8), s32 *, 0) = (s32) M2C_FIELD(arg0, s32 *, 0x1C);
        M2C_FIELD(M2C_FIELD(temp_v0_3, void **, 8), s32 *, 4) = (s32) M2C_FIELD(arg0, s32 *, 0x20);
        M2C_FIELD(M2C_FIELD(temp_v0_3, void **, 8), s32 *, 8) = (s32) M2C_FIELD(arg0, s32 *, 0x24);
        M2C_FIELD(temp_s1, s16 *, 0x1E) = 0x500;
        M2C_FIELD(temp_s1, s16 *, 0x1C) = 0x500;
        M2C_FIELD(temp_s1, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s1, u16 *, 0x14) | 0xC);
        if (func_80069EF8() & 1) {
            register M2C_UNK *temp_tail_base ASM_REG("$2") = &D_800DEDB0;

            ASM_TAILSLOT_PIN(temp_tail_base);
            func_80024678();
            return;
        }
        {
            register M2C_UNK *temp_spawn_base ASM_REG("$2");

            ASM_CLOBBER("$2");
            temp_spawn_base = &D_800DEE38;
            M2C_FIELD(temp_s1, M2C_UNK **, 0) = temp_spawn_base;
            M2C_FIELD(temp_s1, s32 *, 8) = (s32) M2C_FIELD(temp_spawn_base, s32 *, 4);
            M2C_FIELD(temp_s1, s8 *, 4) = 0;
            M2C_FIELD(temp_s1, s8 *, 5) = 0;
        }
    }
    M2C_FIELD(arg0, s16 *, 0x4C) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x4C) + 1);
    func_80024724();
    return;

block_state3:
    M2C_FIELD(arg0, u16 *, 0xC) = (u16) (M2C_FIELD(arg0, u16 *, 0xC) + ((s32) (M2C_FIELD(arg0, s16 *, 0x2A) * 3) >> 2));
    temp_v0 = M2C_FIELD(arg0, u16 *, 0x10) + ((s32) (M2C_FIELD(arg0, s16 *, 0x32) * 3) >> 2);
    M2C_FIELD(arg0, u16 *, 0x10) = temp_v0;
    if (M2C_FIELD(arg0, s16 *, 0x26) < (s16) temp_v0) {
        M2C_FIELD(arg0, u16 *, 0x10) = (u16) M2C_FIELD(arg0, s16 *, 0x26);
        goto block_tail_ff;
    }
    goto block_return;

block_tail_ff:
    M2C_FIELD(arg0, s16 *, 0x4C) = 0xFF;
    func_80024724();
    return;

block_state_ff:
    M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
    D_800814A0[0] |= 0x8000;

block_return:
    return;
}
