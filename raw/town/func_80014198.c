#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80048E00(M2C_UNK *);                   /* extern */
extern M2C_UNK D_800D161C;

void func_800B18F8(void *arg0) {
    func_80048E00(&D_800D161C);
    M2C_FIELD(arg0, u8 *, 0x3C) = (u8) (M2C_FIELD(arg0, u8 *, 0x3C) | 0x80);
}
