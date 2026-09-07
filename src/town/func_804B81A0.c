#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80017D9C();                /* extern */
M2C_UNK func_80018854();                     /* extern */
s32 func_8001894C();                             /* extern */
extern s16 D_80018AEA;

void func_800169A0(s32 arg0, M2C_UNK arg1) {
    if (func_8001894C(D_80018AEA) == 0) {
        func_80018854(0x511);
    }
    func_80017D9C(arg0, arg1);
}
