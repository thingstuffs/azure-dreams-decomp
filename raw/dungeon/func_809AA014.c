#include "common.h"
#include "m2c_compat.h"

void *func_8003FD64(M2C_UNK, s32);                  /* extern */
M2C_UNK func_800A56E0(M2C_UNK);                     /* extern */
extern M2C_UNK D_8016F6D4;

void func_8016F814(void *arg0) {
    void *temp_v0;

    temp_v0 = func_8003FD64(0x202, arg0 - 0x20);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_8016F6D4;
        M2C_FIELD(temp_v0, void **, 0x20) = arg0;
        M2C_FIELD(temp_v0, s32 *, 8) = (s32) M2C_FIELD(arg0, s32 *, -0x18);
        M2C_FIELD(temp_v0, u16 *, 0x2A) = (u16) M2C_FIELD(arg0, u16 *, 0x2A);
        func_800A56E0(0x703);
    }
}
