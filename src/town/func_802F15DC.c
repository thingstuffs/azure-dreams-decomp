#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80400E34();                            /* extern */
M2C_UNK func_804083FC();                /* extern */
extern s8 D_8008CA34;

void func_802F15DC(s32 arg0) {
    D_8008CA34 = 1;
    func_80400E34();
    func_804083FC(arg0, 0);
}
