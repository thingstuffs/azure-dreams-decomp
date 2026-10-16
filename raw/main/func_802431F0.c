#include "common.h"
#include "m2c_compat.h"

s32 func_8002168C();                                /* extern */
M2C_UNK func_800231E4(M2C_UNK);                     /* extern */
M2C_UNK func_800261C0();                            /* extern */
extern M2C_UNK D_800265B8;

void func_800261F0(void *arg0) {
    func_800261C0();
    if (func_8002168C() >= 4) {
        func_800231E4(0);
        M2C_FIELD(arg0, M2C_UNK **, -0x10) = &D_800265B8;
    }
}
