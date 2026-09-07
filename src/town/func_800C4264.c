#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003AF58();        /* extern */
M2C_UNK func_80053DA8();                     /* extern */
M2C_UNK func_800542BC();                            /* extern */
extern M2C_UNK D_800717E8;
extern s8 D_80080A88;
extern M2C_UNK D_800D42B4;

void func_800C19C4(void) {
    func_8003AF58(&D_800717E8, &D_800D42B4);
    D_80080A88 = 1;
    func_80053DA8(0xBF);
    func_800542BC();
}
