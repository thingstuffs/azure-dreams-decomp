#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8001611C();                /* extern */
M2C_UNK func_80017EB0();                /* extern */
M2C_UNK func_800188CC();                     /* extern */
s32 func_8001894C();                             /* extern */
extern s16 D_80018AEA;

void func_804B7BD0(s32 arg0, M2C_UNK arg1) {
    if (func_8001894C(0x50C) != 0) {
        if (func_8001894C(D_80018AEA) == 0) {
            func_800188CC(0x50C);
        }
    }
    func_8001611C(arg0, arg1);
    func_80017EB0(arg0, arg1);
}
