#include "common.h"
#include "m2c_compat.h"

s32 func_800A639C();                             /* extern */
M2C_UNK func_800A63C8();                /* extern */
extern s32 D_80100E2C[1];

void func_800A643C(s32 arg0, M2C_UNK arg1) {
    s32 *p;
    func_800A63C8(func_800A639C(arg0 & 0xFF), arg1);
    p = D_80100E2C;
    *p = 0;
}
