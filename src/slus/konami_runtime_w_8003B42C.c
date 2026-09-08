#include "common.h"
#include "m2c_compat.h"

#include "common.h"

M2C_UNK func_80033AA8();                     /* extern */
M2C_UNK func_80033AE8();                     /* extern */

/* Selects which runtime call receives 1000 and which receives 10. */
void func_8003B42C(s32 mode) {
    if (mode != 0) {
        func_80033AA8(0x3E8);
        func_80033AE8(0xA);
        return;
    }
    func_80033AE8(0x3E8);
    func_80033AA8(0xA);
}
