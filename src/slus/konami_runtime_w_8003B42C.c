#include "common.h"
#include "m2c_compat.h"

#include "common.h"

M2C_UNK func_80033AA8();                     /* extern */
M2C_UNK func_80033AE8();                     /* extern */

void func_8003B42C(s32 arg0) {
    if (arg0 != 0) {
        func_80033AA8(0x3E8);
        func_80033AE8(0xA);
        return;
    }
    func_80033AE8(0x3E8);
    func_80033AA8(0xA);
}
