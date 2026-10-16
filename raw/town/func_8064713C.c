#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80016C64(M2C_UNK *, M2C_UNK *, s32, M2C_UNK); /* extern */
M2C_UNK func_800176A0(M2C_UNK);                     /* extern */
extern M2C_UNK D_8001798C;
extern M2C_UNK D_80017B30;

void func_8001613C(s32 arg0, M2C_UNK arg2) {
    func_800176A0(0x12C7);
    func_80016C64(&D_8001798C, &D_80017B30, arg0, arg2);
}
