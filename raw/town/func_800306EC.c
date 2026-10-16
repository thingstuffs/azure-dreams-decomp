#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800C2E84(M2C_UNK, M2C_UNK *);          /* extern */
extern M2C_UNK D_800CD87C;
extern M2C_UNK D_800D72AC;

void func_800CDE4C(void *arg0, M2C_UNK arg2) {
    func_800C2E84(arg2, &D_800D72AC);
    M2C_FIELD(arg0, M2C_UNK **, 0x50) = &D_800CD87C;
    M2C_FIELD(arg0, s16 *, 0x84) = 0x50;
    M2C_FIELD(arg0, s16 *, 0x6C) = 0xD2;
}
