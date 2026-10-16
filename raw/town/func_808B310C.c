#include "common.h"
#include "m2c_compat.h"

s32 func_80700DC0(s16);                             /* extern */
extern M2C_UNK D_A0700110;
extern M2C_UNK D_A0700118;

void func_8070090C(void) {
    s16 sp10;
    M2C_UNK sp14;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 temp_v0;
    s32 var_s0;
    s32 var_s3;
    s32 var_v0;

    temp_v0 = M2C_UNALIGNED32(M2C_FIELD(&D_A0700110, M2C_UNK *, 0));
    sp10 = temp_v0;
    sp14 = M2C_UNALIGNED32(M2C_FIELD(&D_A0700110, M2C_UNK *, 4));
    sp18 = M2C_FIELD(&D_A0700118, s32 *, 0);
    sp1C = M2C_FIELD(&D_A0700118, s32 *, 4);
    sp20 = M2C_FIELD(&D_A0700118, s32 *, 8);
    sp24 = M2C_FIELD(&D_A0700118, s32 *, 0xC);
    var_s3 = 0;
    if (temp_v0 != 0) {
        var_s0 = 0;
loop_2:
        var_v0 = var_s3 * 4;
        if (func_80700DC0(*(var_s0 + &sp10)) != 0) {
            var_s0 += 2;
            var_s3 += 1;
            if (*(var_s0 + &sp10) == 0) {
                goto block_4;
            }
            goto loop_2;
        }
    } else {
block_4:
        var_v0 = var_s3 * 4;
    }
    M2C_FIELD((sp + var_v0), M2C_UNK (**)(s32), 0x18)(var_s3);
}
