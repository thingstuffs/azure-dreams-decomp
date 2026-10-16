#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800C2E84(M2C_UNK, M2C_UNK *);          /* extern */
extern M2C_UNK D_800CE08C;
extern M2C_UNK D_800D72AC;

void func_800CE94C(void *arg0, M2C_UNK arg2) {
    func_800C2E84(arg2, &D_800D72AC);
    *(s8 *)0x80082688 = 0;
    M2C_FIELD(arg0, M2C_UNK **, 0x54) = &D_800CE08C;
    M2C_FIELD(arg0, s16 *, 0x6C) = 0x15;
}
