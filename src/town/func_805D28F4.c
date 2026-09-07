#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80016228();                            /* extern */
M2C_UNK func_800193E0();                     /* extern */
extern s32 D_8001967C;

void func_800168F4(void) {
    D_8001967C = 1;
    func_800193E0(0x632);
    func_80016228();
}
