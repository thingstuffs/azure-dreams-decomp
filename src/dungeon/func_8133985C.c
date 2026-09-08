#include "common.h"

typedef struct S_8017085C_0 {
    u8 pad_00[0x12];
    union { s16 s; u16 u; } unk_12;   /* accessed as both */
    u8 pad_14[0x4];
    u16 unk_18;
    u8 pad_1A[0x3E];
    s8 unk_58;
    s8 unk_59;
    u8 pad_5A[0x2];
    s32 unk_5C;
} S_8017085C_0;   /* arg0 in func_8017085C */

typedef struct S_8017085C_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x8];
    s32 unk_14;
} S_8017085C_1;   /* arg1 in func_8017085C */

typedef struct S_8017085C_2 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8017085C_2;   /* arg2 in func_8017085C */



extern s32 func_800644B8();
extern void func_800A7A7C();
extern s32 D_800814A0;

void func_8017085C(void *arg0, void *arg1, void *arg2) {
    s8 sp18[4];
    s16 temp_v0_4;
    s16 temp_v1;
    s16 temp_v1_2;
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 var_a1;
    s32 var_v0;
    register u16 temp_v0 ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    u16 temp_v0_5;
    u16 temp_v0_7;

    temp_v1 = ((S_8017085C_0 *)arg0)->unk_12.s;
    if (temp_v1 == 1) {
        goto state1;
    }
    if (temp_v1 < 2) {
        if (temp_v1 == 0) {
            goto state0;
        }
        return;
    }
    ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    if (temp_v1 == 2) {
        goto state2;
    }
    return;

state0:
    temp_v0 = ((S_8017085C_0 *)arg0)->unk_18;
    ((S_8017085C_0 *)arg0)->unk_18 = temp_v0 + 1;
    temp_a0 = (s32)((u32)temp_v0 << 0x10);
    temp_a0 >>= 4;
    ((S_8017085C_0 *)arg0)->unk_5C = (0 - func_800644B8(temp_a0 / 80)) << 7;
    temp_v0_2 = ((S_8017085C_0 *)arg0)->unk_5C - 0x200000;
    ((S_8017085C_1 *)arg1)->unk_08.at00.v = ((S_8017085C_1 *)arg1)->unk_14 + temp_v0_2;

    return;

state1:
    temp_v0 = ((S_8017085C_0 *)arg0)->unk_18;
    ((S_8017085C_0 *)arg0)->unk_18 = temp_v0 + 1;
    temp_a0 = (s32)((u32)temp_v0 << 0x10);
    temp_a0 >>= 4;
    ((S_8017085C_0 *)arg0)->unk_5C = (0 - func_800644B8(temp_a0 / 80)) << 7;
    temp_v0_2 = ((S_8017085C_0 *)arg0)->unk_5C - 0x200000;
    ((S_8017085C_1 *)arg1)->unk_08.at00.v = ((S_8017085C_1 *)arg1)->unk_14 + temp_v0_2;

    temp_v0_5 = ((S_8017085C_0 *)arg0)->unk_18;
    ((S_8017085C_0 *)arg0)->unk_18 = temp_v0_5 + 1;
    if ((s16)temp_v0_5 < 0x14) {
        return;
    }

    temp_v0_7 = ((S_8017085C_0 *)arg0)->unk_12.u;
    ((S_8017085C_0 *)arg0)->unk_18 = 0;
    ((S_8017085C_0 *)arg0)->unk_12.u = temp_v0_7 + 1;
    return;

state2:
    ((S_8017085C_1 *)arg1)->unk_08.at00.v += 0x20000;
    if (((S_8017085C_1 *)arg1)->unk_08.at00.v < ((S_8017085C_1 *)arg1)->unk_14) {
        return;
    }

    ((S_8017085C_1 *)arg1)->unk_08.at00.v = ((S_8017085C_1 *)arg1)->unk_14;
    sp18[1] = 0x12;
    sp18[0] = 1;
    sp18[2] = 0x32;
    sp18[3] = 0;

    temp_v1_2 = ((S_8017085C_1 *)arg1)->unk_02;
    if (temp_v1_2 - 0x20 >= 0) {
        ((S_8017085C_0 *)arg0)->unk_58 = (temp_v1_2 - 0x20) >> 6;
    } else {
        ((S_8017085C_0 *)arg0)->unk_58 = (temp_v1_2 + 0x1F) >> 6;
    }

    temp_v0_4 = ((S_8017085C_1 *)arg1)->unk_06;
    var_a1 = temp_v0_4 - 0x20;
    if (var_a1 < 0) {
        do {
            var_a1 = temp_v0_4 + 0x1F;
        } while (0);
    }
    temp_a1 = var_a1 >> 6;
    ((S_8017085C_0 *)arg0)->unk_59 = temp_a1;
    func_800A7A7C(((S_8017085C_0 *)arg0)->unk_58, (s8)temp_a1,
        ((S_8017085C_1 *)arg1)->unk_08.at02.v, ((S_8017085C_2 *)arg2)->unk_08, sp18);

    (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
    D_800814A0 |= 0x8000;
}
