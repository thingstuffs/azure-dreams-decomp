#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80400E34();                            /* extern */
M2C_UNK func_804083FC();                /* extern */
extern s8 D_8008CA34;

/* Set the global flag, prepare state, and process the target in mode 1. */
void func_802F155C(s32 target) {
    D_8008CA34 = 1;
    func_80400E34();
    func_804083FC(target, 1);
}
