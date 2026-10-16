#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80016BF0(M2C_UNK, M2C_UNK, s16, s16);  /* extern */
extern M2C_UNK D_80083160;

void func_80016E6C(void) {
    void *temp_v0;

    temp_v0 = &D_80083160 + 0x1DC;
    func_80016BF0(0, 0, (s16) (1 << M2C_FIELD(temp_v0, s16 *, 0x14)), (s16) (1 << M2C_FIELD(temp_v0, s16 *, 0x16)));
}
