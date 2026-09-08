#include "common.h"
#include "m2c_compat.h"

#include "common.h"

M2C_UNK DrawSync();                          /* extern */
M2C_UNK SetDispMask();                       /* extern */
M2C_UNK VSync();                             /* extern */
M2C_UNK func_8003AF94();            /* extern */
M2C_UNK func_8003B034();                            /* extern */
M2C_UNK func_8003B06C();                            /* extern */
M2C_UNK func_8003C758();                   /* extern */
M2C_UNK func_80041284();                   /* extern */
M2C_UNK func_80053DA8();                     /* extern */
M2C_UNK func_800542BC();                            /* extern */
M2C_UNK func_8008B408();                     /* extern */
M2C_UNK func_8008B550();                     /* extern */
M2C_UNK func_800903A8();                            /* extern */
extern M2C_UNK D_80080E28;
extern M2C_UNK D_80080EA0;
extern M2C_UNK D_80081018;
extern M2C_UNK D_800D1D54;
extern M2C_UNK D_800D1E7C;

/* Synchronize rendering, enable display output, and run runtime setup. */
void func_8003B0B4(void) {
    VSync(0);
    VSync(0);
    DrawSync(0);
    func_80053DA8(0x7F);
    func_800542BC();
    VSync(0);
    func_8003AF94(0x16, 0x5DB);
    SetDispMask(1);
    func_80041284(&D_80080EA0);
    func_80041284(&D_80080E28);
    func_80041284(&D_800D1D54);
    func_80041284(&D_800D1E7C);
    func_8003B034();
    func_8003B06C();
    func_8003C758(&D_80081018);
    func_8008B408(1);
    func_8008B550(1);
    func_800903A8();
}
