#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80096B50(s32);                            /* extern */
M2C_UNK func_80096C3C();                            /* extern */
extern s16 D_8006ADD4;

void func_80096DC8(s32 arg0) {
    if (D_8006ADD4 == 0xC) {
        func_80096B50(arg0);
        return;
    }
    func_80096C3C();
}
