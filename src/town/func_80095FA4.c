#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80094984();       /* extern */
extern M2C_UNK D_80093638;
extern M2C_UNK D_800D0078;

void func_80093704(M2C_UNK **arg0) {
    func_80094984(&D_800D0078, arg0);
    *arg0 = &D_80093638;
}
