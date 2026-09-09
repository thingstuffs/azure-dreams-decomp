#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80017BA0(s32, s32);                            /* extern */
extern M2C_UNK D_8001CC5C;

M2C_UNK *func_80016DD0(s32 arg0, s32 arg1) {
    func_80017BA0(arg0, arg1);
    return &D_8001CC5C;
}
