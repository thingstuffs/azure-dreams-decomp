#include "common.h"
#include "m2c_compat.h"

extern void * D_800189D0;
extern s32 D_800189D4;
s32 func_8001674C(void) {
    void *temp_a0;

    temp_a0 = D_800189D0;
    D_800189D4 = M2C_FIELD(temp_a0, s32 *, 0x24);
    return M2C_FIELD(temp_a0, s32 *, 0x20);
}
