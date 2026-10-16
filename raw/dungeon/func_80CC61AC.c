#include "common.h"
#include "m2c_compat.h"

s32 func_800AB464();                                /* extern */
extern M2C_UNK D_8016AF20;
extern M2C_UNK D_8016DB98;

void func_8016D9AC(void *arg0) {
    M2C_UNK *var_v0;

    if (func_800AB464() > 0) {
        if (M2C_FIELD(arg0, u8 *, 0xA7) != 0) {
            var_v0 = &D_8016DB98;
        } else {
            var_v0 = &D_8016AF20;
        }
        M2C_FIELD(arg0, M2C_UNK **, 0x8C) = var_v0;
    }
}
