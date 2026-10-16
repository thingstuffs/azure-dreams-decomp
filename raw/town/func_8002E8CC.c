#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800C2E84(M2C_UNK, M2C_UNK *);          /* extern */
extern M2C_UNK D_800D6A70;

void func_800CC02C(void *arg0, M2C_UNK arg2) {
    func_800C2E84(arg2, &D_800D6A70);
    M2C_FIELD(arg0, u16 *, 0x68) = (u16) (M2C_FIELD(arg0, u16 *, 0x68) + 1);
}
