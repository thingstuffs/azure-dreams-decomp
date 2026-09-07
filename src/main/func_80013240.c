#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80026920();                         /* extern */
M2C_UNK func_80027BF4();                            /* extern */
M2C_UNK func_80040AA0();                     /* extern */

void func_80026240(s32 arg0) {
    func_80026920(arg0 - 0x20);
    func_80027BF4();
    func_80040AA0(3);
}
