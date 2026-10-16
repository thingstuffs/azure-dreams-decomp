#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80017320(M2C_UNK);                     /* extern */
M2C_UNK func_80017398(M2C_UNK);                     /* extern */
extern u16 D_800175B4;

void func_80016188(void) {
    u16 temp_v0;

    temp_v0 = D_800175B4 + 1;
    D_800175B4 = temp_v0;
    if ((s16) temp_v0 >= 0x15) {
        D_800175B4 = 9;
    }
    if (((s16) D_800175B4 == 8) || ((s16) D_800175B4 == 0x14)) {
        func_80017320(0x5DB);
        return;
    }
    func_80017398(0x5DB);
}
