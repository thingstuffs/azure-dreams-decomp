#include "common.h"
#include "m2c_compat.h"

s32 func_800A9CAC();                       /* extern */
M2C_UNK func_800C170C();                            /* extern */
s32 func_800C2124();                       /* extern */
extern M2C_UNK D_800C2074;
extern M2C_UNK D_800D4710;

void func_800C172C(void) {
    if ((func_800A9CAC(&D_800C2074) == 0) || (func_800C2124(&D_800D4710) == 0)) {
        func_800C170C();
    }
}
