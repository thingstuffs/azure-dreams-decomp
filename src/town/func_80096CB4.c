#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80053DA8();                     /* extern */
M2C_UNK func_80094984(); /* extern */
M2C_UNK func_80094C1C();                  /* extern */
extern M2C_UNK D_800924EC;
extern M2C_UNK D_800D0110;

void func_80094414(M2C_UNK **arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_80053DA8(0x50B);
    func_80094C1C(arg0);
    func_80094984(&D_800D0110, arg0, arg2);
    *arg0 = &D_800924EC;
}
