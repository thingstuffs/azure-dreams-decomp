#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800C4174();                            /* extern */
extern M2C_UNK D_80082660;
extern M2C_UNK D_800D6244;

void func_800C8644(void *arg0) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x80), M2C_UNK **, 4) = &D_800D6244;
    *((M2C_FIELD(arg0, s32 *, 0x60) * 8) + &D_80082660) = 0;
    func_800C4174();
}
