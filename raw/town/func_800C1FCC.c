#include "common.h"
typedef s32 M2C_UNK;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

void func_800BC574(void *, s32);
extern s32 D_80012D5C;
extern void *D_80089930[];

/* The final state reset is coupled to the non-overflow path.  This is a
 * defined source-level guard whose natural branch leader is the epilogue. */
void func_800BF72C(void *arg0, void *arg1) {
    static void *const sw_keep[] = {
        &&block_0, &&block_1, &&block_2, &&block_3, &&block_4
    };
    s32 stack_record[6];
    s16 temp_v1_2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v1_3;
    s32 stack_low;
    u16 temp_v1;
    u32 swi;
    u32 *clock;
    u32 value;

    temp_v1 = M2C_FIELD(M2C_FIELD(arg0, void **, 0xA0), u16 *, 0x68);
    if ((temp_v1 & 1) && M2C_FIELD(arg0, s16 *, 0x68) == 0)
        M2C_FIELD(arg0, s16 *, 0x68) = (s16)temp_v1;
    temp_v1_2 = M2C_FIELD(arg0, s16 *, 0x68);
    swi = temp_v1_2;
    if (swi >= 5) goto block_0;
    (void)sw_keep;
    goto *D_80089930[swi];

block_1:
    temp_v1_3 = M2C_FIELD(arg1, s32 *, 4) + 0x40000;
    M2C_FIELD(arg1, s32 *, 4) = temp_v1_3;
    if (temp_v1_3 > 0x023FFFFF) {
        M2C_FIELD(arg1, s32 *, 4) = 0x02400000;
        goto block_15;
    }
    goto block_0;

block_2:
    temp_v0 = M2C_FIELD(arg1, s32 *, 0) + 0x40000;
    M2C_FIELD(arg1, s32 *, 0) = temp_v0;
    if (temp_v0 == 0x10000000) {
        clock = (u32 *)0x80010000;
        value = M2C_FIELD(clock, u32 *, 0x2D5C);
        if ((value % 1000U) == 777U) {
            stack_record[0] = 0x0FA00000;
            stack_low = 0xFFF80000;
            stack_record[1] = M2C_FIELD(arg1, s32 *, 4);
            stack_record[2] = stack_low;
            func_800BC574(stack_record, 0x200);
        }
    }
    if (M2C_FIELD(arg1, s32 *, 0) > 0x105FFFFF) {
        M2C_FIELD(arg1, s32 *, 0) = 0x10600000;
        goto block_18;
    }
    goto block_0;

block_3:
    temp_v0_2 = M2C_FIELD(arg1, s32 *, 0) + 0xFFFC0000;
    M2C_FIELD(arg1, s32 *, 0) = temp_v0_2;
    if (temp_v0_2 <= 0x0FA00000) {
        M2C_FIELD(arg1, s32 *, 0) = 0x0FA00000;
        goto block_15;
    }
    goto block_0;

block_15:
    M2C_FIELD(arg0, s16 *, 0x68) =
        (s16)((u16)M2C_FIELD(arg0, s16 *, 0x68) + 1);
    goto block_0;

block_4:
    temp_v0_3 = M2C_FIELD(arg1, s32 *, 4) + 0xFFFC0000;
    M2C_FIELD(arg1, s32 *, 4) = temp_v0_3;
    if (temp_v0_3 > 0x02300000)
        goto block_0;
    M2C_FIELD(arg1, s32 *, 4) = 0x02300000;
    M2C_FIELD(arg0, s16 *, 0x68) = 0;
    goto block_0;
block_18:
    M2C_FIELD(arg0, s16 *, 0x68) = 0;
block_0:
    return;
}
