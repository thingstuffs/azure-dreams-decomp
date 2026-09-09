#include "common.h"
#include "m2c_compat.h"

s32 func_800352FC(s32, M2C_UNK, M2C_UNK, s32);        /* extern */
extern M2C_UNK (*D_800FE5D8)(s32, M2C_UNK, M2C_UNK);

void func_800933FC(s32 arg0, M2C_UNK arg1, M2C_UNK arg2, s32 arg3) {
    if (func_800352FC(arg0, arg1, arg2, arg3) == 0) {
        M2C_UNK (*callback)(s32, M2C_UNK, M2C_UNK) = D_800FE5D8;
        /* MATCH: Keep the callback load before argument register setup. */
        ASM_SCHED_BARRIER();
        callback(arg0, arg1, arg2);
    }
}
