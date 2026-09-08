#include "common.h"
#include "m2c_compat.h"

#include "common.h"

M2C_UNK func_800483AC();                     /* extern */
s32 func_80048D20();                                /* extern */
extern s32 D_80080A80;

/* Store the result of func_80048D20, then call func_800483AC with 1 and 0. */
void func_8003B034(void) {
    D_80080A80 = func_80048D20();
    func_800483AC(1);
    func_800483AC(0);
}
