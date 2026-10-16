#include "common.h"
#include "m2c_compat.h"

s32 func_8002168C();                                /* extern */
M2C_UNK func_800231E4(M2C_UNK);                     /* extern */
M2C_UNK func_800274A8();                            /* extern */
extern M2C_UNK D_8002789C;

void func_800274D8(void *arg0) {
    func_800274A8();
    if (func_8002168C() >= 4) {
        func_800231E4(0);
        M2C_FIELD(arg0, M2C_UNK **, -0x10) = &D_8002789C;
    }
}
