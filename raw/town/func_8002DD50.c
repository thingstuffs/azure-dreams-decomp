#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800C2E84(M2C_UNK, M2C_UNK *);          /* extern */
extern M2C_UNK D_800CB474;
extern M2C_UNK D_800D6938;

void func_800CB4B0(void *arg0, M2C_UNK arg2) {
    u16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, u16 *, 0x6C) - 1;
    M2C_FIELD(arg0, u16 *, 0x6C) = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        func_800C2E84(arg2, &D_800D6938);
        M2C_FIELD(arg0, M2C_UNK **, 0x54) = &D_800CB474;
        M2C_FIELD(arg0, u16 *, 0x6C) = 0xAU;
    }
}
