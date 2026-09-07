#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80017BA0();                            /* extern */
extern M2C_UNK D_8001CC5C;

M2C_UNK *func_80016DD0(void) {
    func_80017BA0();
    return &D_8001CC5C;
}
