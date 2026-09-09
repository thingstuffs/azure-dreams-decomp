#include "common.h"
#include "m2c_compat.h"

extern void *D_80020060[];
M2C_UNK func_80020924();
s32 func_80021594();
s32 func_8002190C();
extern M2C_UNK D_80028530[];
extern M2C_UNK D_80028538[];
extern M2C_UNK D_80028538_read[] __asm__("D_80028538");
extern M2C_UNK D_80028538_write[] __asm__("D_80028538");
extern M2C_UNK D_800287D0[];
extern M2C_UNK D_80084118[];

s32 func_8002168C(void) {
    static void *const jt_keep[] = { &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&kill_lbl };
    s32 temp_a0;
    s32 temp_s0;
    s32 temp_v1;
    s32 keep5;
    s32 *dead_base;

    temp_s0 = func_80021594();
    temp_a0 = func_8002190C();
    if (temp_s0 == 0) {
        goto block_13;
    }
    if (*(s32 *)((s8 *)&D_80028538_read + temp_a0 * 4) != temp_s0) {
        goto block_4;
    }
    *(s32 *)((s8 *)&D_80028530 + temp_a0 * 4) += 1;
    keep5 = temp_a0 * 4;
    goto kill_lbl;
block_4:
    *(s32 *)((s8 *)&D_80028530 + temp_a0 * 4) = 0;
    keep5 = temp_a0 * 4;
kill_lbl:
    *(s32 *)((s8 *)&D_80028538_write + temp_a0 * 4) = temp_s0;
    if ((u32) (temp_s0 - 1) >= 5U) {
        goto block_12;
    }
    (void)jt_keep; goto *D_80020060[(u32)((temp_s0) - 1)];
jt_c1:
jt_c2:
    D_800287D0[temp_a0] = temp_s0;
    goto block_12;
jt_c3:
    dead_base = D_80028530;
    temp_v1 = temp_a0 * 4;
    goto check_count;
jt_c4:
jt_c5:
    D_80084118[temp_a0] = 0;
    temp_v1 = temp_a0 * 4;
    dead_base = D_80028530;
check_count:
    if (*(s32 *)(temp_v1 + (s32)dead_base) < 0xB) {
        func_80020924(temp_a0, (s32 *)(temp_v1 + (s32)dead_base));
        goto block_13;
    }
    *(s32 *)((s8 *)&D_800287D0 + temp_v1) = temp_s0;
    *(s32 *)(temp_v1 + (s32)dead_base) = 0;
    *(s32 *)((s8 *)&D_80028538 + temp_v1) = 0;
    func_80020924(temp_a0, (s32 *)(temp_v1 + (s32)dead_base));
    goto block_13;
block_12:
    func_80020924(temp_a0, (s32 *)keep5);
block_13:
    return temp_s0;
}
