#include "common.h"
#include "m2c_compat.h"

s32 func_800161A4(M2C_UNK);                         /* extern */
M2C_UNK func_800173C4(s16);                         /* extern */

void func_80016A60(s32 arg0, void *arg1, M2C_UNK arg2) {
    func_800173C4(M2C_FIELD(((M2C_FIELD(((func_800161A4(arg2) * 8) + arg0), s16 *, 2) * 8) + M2C_FIELD(arg1, s32 *, 0x14)), s16 *, 4));
}
