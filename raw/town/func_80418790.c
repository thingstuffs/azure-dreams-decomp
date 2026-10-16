#include "common.h"
#include "m2c_compat.h"

void func_80016F90(void) {
    void *temp_a0;

    temp_a0 = *(void **)0x80016000;
    M2C_FIELD(M2C_FIELD(temp_a0, void **, 0x1C), s32 *, 4) = 0x4E0;
    M2C_FIELD(M2C_FIELD(temp_a0, void **, 0x1C), s32 *, 8) = 0x4E0;
}
