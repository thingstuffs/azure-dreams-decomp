#include "common.h"

#define FIELD(base, type, offset) (*(type *)((s8 *)(base) + (offset)))

extern s32 func_800644B8();
extern void func_800A7A7C();
extern void func_80170A44() __attribute__((noreturn));
extern s32 D_800814A0;

void func_8017085C(void *arg0, void *arg1, void *arg2) {
    s8 sp18[4];
    s16 temp_v0_4;
    s16 temp_v1;
    s16 temp_v1_2;
    register s32 temp_a0 ASM_REG("$4");
    s32 temp_a1;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 var_a1;
    s32 var_v0;
    register u16 temp_v0 ASM_REG("$2");
    u16 temp_v0_5;
    u16 temp_v0_7;

    temp_v1 = FIELD(arg0, s16, 0x12);
    if (temp_v1 == 1) {
        goto state1;
    }
    if (temp_v1 < 2) {
        if (temp_v1 == 0) {
            goto state0;
        }
        return func_80170A44();
    }
    ASM_SCHED_BARRIER();
    if (temp_v1 == 2) {
        goto state2;
    }
    return func_80170A44();

state0:
    temp_v0 = FIELD(arg0, u16, 0x18);
    FIELD(arg0, u16, 0x18) = temp_v0 + 1;
    temp_a0 = (s32)((u32)temp_v0 << 0x10);
    temp_a0 >>= 4;
    ASM_KEEP_NV(temp_a0);
    ASM_KEEP_NV(temp_v0);
    FIELD(arg0, s32, 0x5C) = (0 - func_800644B8(temp_a0 / 80)) << 7;
    temp_v0_2 = FIELD(arg0, s32, 0x5C) - 0x200000;
    FIELD(arg1, s32, 8) = FIELD(arg1, s32, 0x14) + temp_v0_2;

    return func_80170A44();

state1:
    temp_v0 = FIELD(arg0, u16, 0x18);
    FIELD(arg0, u16, 0x18) = temp_v0 + 1;
    temp_a0 = (s32)((u32)temp_v0 << 0x10);
    temp_a0 >>= 4;
    ASM_KEEP_NV(temp_a0);
    ASM_KEEP_NV(temp_v0);
    FIELD(arg0, s32, 0x5C) = (0 - func_800644B8(temp_a0 / 80)) << 7;
    temp_v0_2 = FIELD(arg0, s32, 0x5C) - 0x200000;
    FIELD(arg1, s32, 8) = FIELD(arg1, s32, 0x14) + temp_v0_2;

    temp_v0_5 = FIELD(arg0, u16, 0x18);
    FIELD(arg0, u16, 0x18) = temp_v0_5 + 1;
    if ((s16)temp_v0_5 < 0x14) {
        return;
    }

    temp_v0_7 = FIELD(arg0, u16, 0x12);
    FIELD(arg0, u16, 0x18) = 0;
    FIELD(arg0, u16, 0x12) = temp_v0_7 + 1;
    return func_80170A44();

state2:
    FIELD(arg1, s32, 8) += 0x20000;
    if (FIELD(arg1, s32, 8) < FIELD(arg1, s32, 0x14)) {
        return;
    }

    FIELD(arg1, s32, 8) = FIELD(arg1, s32, 0x14);
    sp18[1] = 0x12;
    sp18[0] = 1;
    sp18[2] = 0x32;
    sp18[3] = 0;

    temp_v1_2 = FIELD(arg1, s16, 2);
    if (temp_v1_2 - 0x20 >= 0) {
        FIELD(arg0, s8, 0x58) = (temp_v1_2 - 0x20) >> 6;
    } else {
        FIELD(arg0, s8, 0x58) = (temp_v1_2 + 0x1F) >> 6;
    }

    temp_v0_4 = FIELD(arg1, s16, 6);
    var_a1 = temp_v0_4 - 0x20;
    if (var_a1 < 0) {
        do {
            var_a1 = temp_v0_4 + 0x1F;
        } while (0);
    }
    temp_a1 = var_a1 >> 6;
    FIELD(arg0, s8, 0x59) = temp_a1;
    func_800A7A7C(FIELD(arg0, s8, 0x58), (s8)temp_a1,
        FIELD(arg1, s16, 0xA), FIELD(arg2, s32, 8), sp18);

    FIELD(arg0, u16, -2) |= 0x8000;
    D_800814A0 |= 0x8000;
}
