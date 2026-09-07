#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8004CB2C();                         /* extern */

void func_80026AE4(s32 arg0) {
    func_8004CB2C(arg0 + 4);
    func_8004CB2C(arg0 + 0x10);
}
