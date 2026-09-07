#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80064B90();          /* extern */
M2C_UNK func_80064BC0();                /* extern */
M2C_UNK func_80064CF0();                     /* extern */
M2C_UNK func_80064D80();                     /* extern */
M2C_UNK func_80065450(); /* extern */
M2C_UNK func_80065820();                /* extern */
M2C_UNK func_800AA044();            /* extern */
extern M2C_UNK D_800D11C0;

void func_800AA068(s32 arg0, M2C_UNK arg1, M2C_UNK arg2) {
    M2C_UNK sp10;

    func_80064B90(0x1F800054, &D_800D11C0);
    func_80065820(arg0 + 8, 0x1F800054);
    func_80064BC0(0x1F800054, arg0 + 0x10);
    func_80064CF0(0x1F800054);
    func_80064D80(0x1F800054);
    func_80065450(arg1, arg2, &sp10);
    func_800AA044(arg1, arg2);
}
