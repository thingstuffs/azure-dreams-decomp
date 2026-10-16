#include "common.h"
#include "m2c_compat.h"

void *func_80019368(s32);                           /* extern */
extern M2C_UNK D_8001B634;

void *func_800193A4(void *arg1) {
    s32 temp_s1;
    void *temp_v0;

    temp_s1 = M2C_FIELD(arg1, s32 *, 0) & 0x3FFF0000;
    temp_v0 = func_80019368(temp_s1);
    if (M2C_FIELD(temp_v0, s32 **, 4) == NULL) {
        *M2C_FIELD(arg1, s32 **, 8) = (M2C_FIELD(arg1, s32 *, 0xC) - &D_8001B634) + 4;
        M2C_FIELD(temp_v0, s32 **, 4) = (s32 *) M2C_FIELD(arg1, s32 **, 8);
        M2C_FIELD(temp_v0, s32 *, 0) = temp_s1;
        M2C_FIELD(temp_v0, s32 *, 0xC) = 0;
    }
    return temp_v0;
}
