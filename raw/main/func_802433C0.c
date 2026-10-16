#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80022F64(s32, s32);                    /* extern */
extern M2C_UNK D_80026398;

void func_800263C0(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x3C) = 1;
    func_80022F64(arg0 - 0x20, arg0 + 0x40);
    M2C_FIELD(arg0, s32 *, 0x40) = 1;
    M2C_FIELD(arg0, M2C_UNK **, -0x10) = &D_80026398;
}
