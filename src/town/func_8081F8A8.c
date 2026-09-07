#include "common.h"
#include "m2c_compat.h"

typedef struct S_800220A8_0 {
    s16 unk_00;
    u16 unk_02;
    void * unk_04;
} S_800220A8_0;   /* arg0 in func_800220A8 */

typedef struct S_800220A8_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800220A8_1;   /* arg1 in func_800220A8 */

typedef struct S_800220A8_2 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_800220A8_2;   /* ((S_800220A8_0 *)arg0)->unk_04 in func_800220A8 */


M2C_UNK func_800644B8();
extern M2C_UNK D_800814A0;

void func_800220A8(void *arg0, void *arg1) {
    s16 temp_v1;
    s32 temp_v0;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_v0;
    s32 temp_a1;
    u16 temp_a0_2;

    temp_a1 = 2;
    if (((S_800220A8_2 *)(((S_800220A8_0 *)arg0)->unk_04))->unk_18 == temp_a1) {
        ((S_800220A8_0 *)arg0)->unk_00 = 3;
    }
    temp_v1 = ((S_800220A8_0 *)arg0)->unk_00;
    if (temp_v1 != temp_a1) {
        if (temp_v1 < 3) {
            if (temp_v1 != 0) {
                if (temp_v1 == 1) {
                    goto state1;
                }
                return;
            }
            goto state0;
        }
        if (temp_v1 != 3) {
            if (temp_v1 != 0xF0) {
                return;
            }
            goto state_f0;
        }
        goto state3;
    }
    goto state2;

state0:
    if ((((S_800220A8_1 *)arg1)->unk_08 += 0x100000) < (s32)0xFF900000) {
        return;
    }
    ((S_800220A8_0 *)arg0)->unk_02 = 0;
    ((S_800220A8_1 *)arg1)->unk_14 = -0x40000;
    goto set_state1;

state1:
{
    s32 state1_a0;
    register s32 state1_v1 ASM_REG("$3");   /* MATCH pin: retail schedule: same instructions, different order without it */
    s32 state1_v0;

    state1_a0 = ((S_800220A8_1 *)arg1)->unk_14;
    state1_v1 = state1_a0;
    ASM_KEEP_NV(state1_v1);   /* MATCH pin: keeps a statement from moving across a call/branch */
    state1_v0 = ((S_800220A8_1 *)arg1)->unk_08;
    state1_v0 += state1_a0;
    state1_v1 += 0x4000;
    ((S_800220A8_1 *)arg1)->unk_08 = state1_v0;
    ((S_800220A8_1 *)arg1)->unk_14 = state1_v1;
    if (state1_v1 != 0x40000) {
        return;
    }
    ((S_800220A8_0 *)arg0)->unk_00 = temp_a1;
    return;
}

state2:
{
    register s32 state2_v0 ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
    s32 state2_v1;

    state2_v0 = ((S_800220A8_1 *)arg1)->unk_08;
    state2_v1 = ((S_800220A8_1 *)arg1)->unk_14;
    state2_v0 += state2_v1;
    ((S_800220A8_1 *)arg1)->unk_08 = state2_v0;
    state2_v0 = state2_v1;
    state2_v1 = -0x8000;
    state2_v0 += state2_v1;
    ((S_800220A8_1 *)arg1)->unk_14 = state2_v0;
    if (state2_v0 != -0x40000) {
        return;
    }
}

set_state1:
    ((S_800220A8_0 *)arg0)->unk_00 = 1;
    return;

state_f0:
{
    u16 statef0_a0;
    s32 statef0_v0;
    s32 statef0_v1;

    statef0_a0 = (((S_800220A8_0 *)arg0)->unk_02 + 1) & 0x7F;
    ((S_800220A8_0 *)arg0)->unk_02 = statef0_a0;
    statef0_v0 = func_800644B8(statef0_a0 << 6, temp_a1, arg0);
    statef0_v0 <<= 7;
    statef0_v1 = (s32)0xFF900000;
    statef0_v0 += statef0_v1;
    ((S_800220A8_1 *)arg1)->unk_08 = statef0_v0;
    return;
}

state3:
{
    register s32 state3_v0 ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
    register s32 state3_v1 ASM_REG("$3");   /* MATCH pin: retail schedule: same instructions, different order without it */

    state3_v0 = ((S_800220A8_1 *)arg1)->unk_08;
    state3_v1 = (s32)0xFFF00000;
    state3_v0 += state3_v1;
    state3_v1 = (s32)0xFE000000;
    state3_v1 = state3_v1 < state3_v0;
    ((S_800220A8_1 *)arg1)->unk_08 = state3_v0;
    if (state3_v1 != 0) {
        return;
    }
    (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
    state3_v0 = D_800814A0;
    state3_v0 |= 0x8000;
    D_800814A0 = state3_v0;
    return;
}
}
