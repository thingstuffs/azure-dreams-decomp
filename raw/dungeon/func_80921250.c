#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64(M2C_UNK);                       /* extern */
extern M2C_UNK D_800F6020;

void func_800F6250(void) {
    void *temp_v0;

    temp_v0 = func_8003FC64(0);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_800F6020;
    }
}
