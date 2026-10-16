#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80016DBC(s32, s16);                    /* extern */
s32 func_80017844(s16);                             /* extern */
extern s32 D_80017AAC;

s32 func_80016EA8(void *arg0) {
    s32 temp_s0;
    s32 var_s1;

    func_80016DBC(M2C_FIELD(arg0, s32 *, 0x14), M2C_FIELD(arg0, s16 *, 0x1A));
    do {
        D_80017AAC = 0;
        var_s1 = 0;
loop_2:
        temp_s0 = var_s1 * 0x10;
        if (func_80017844(M2C_FIELD((temp_s0 + M2C_FIELD(arg0, s32 *, 0x10)), s16 *, 0xC)) != 0) {
block_4:
            var_s1 += 1;
            goto loop_2;
        }
        if (*(temp_s0 + M2C_FIELD(arg0, s32 *, 0x10))(arg0, var_s1) != 0) {
            goto block_4;
        }
    } while (D_80017AAC != 0);
    return var_s1;
}
