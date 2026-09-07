#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80051B50();       /* extern */
extern s32 D_80408D6C;

void func_800208D8(s32 arg0) {
    func_80051B50(arg0 + 0x7C, &D_80408D6C, 1);
}
