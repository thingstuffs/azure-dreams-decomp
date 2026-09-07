#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8001ACE8();                     /* extern */
extern M2C_UNK D_8001DCD4;

M2C_UNK *func_8001669C(void) {
    func_8001ACE8(0xDAC);
    func_8001ACE8(0xD77);
    return &D_8001DCD4;
}
