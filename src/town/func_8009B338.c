#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80098ABC(void *, void *, s32);                            /* extern */
extern s8 D_80082668;

void func_80098A98(void *arg0, void *arg1, s32 arg2) {
    D_80082668 = 0;
    func_80098ABC(arg0, arg1, arg2);
}
