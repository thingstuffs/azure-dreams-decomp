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

/* Apply rotation, scale, and translation to a vector and copy the result back. */
void func_800AA068(s32 transform, M2C_UNK vector, M2C_UNK transformed) {
    M2C_UNK flags;

    func_80064B90(0x1F800054, &D_800D11C0);
    func_80065820(transform + 8, 0x1F800054);
    func_80064BC0(0x1F800054, transform + 0x10);
    func_80064CF0(0x1F800054);
    func_80064D80(0x1F800054);
    func_80065450(vector, transformed, &flags);
    func_800AA044(vector, transformed);
}
