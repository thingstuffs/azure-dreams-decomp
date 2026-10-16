#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80018AC4(void *);                      /* extern */

void func_80018BE4(s32 arg0) {
    void **temp_s0;
    void *temp_a0;

    temp_s0 = M2C_FIELD(*(void **)0x80016000, s32 *, 0x38) + 0x29C + (arg0 * 4);
    temp_a0 = *temp_s0;
    if (M2C_FIELD(temp_a0, u8 *, 1) == 0x13) {
        func_80018AC4(temp_a0);
    }
    M2C_FIELD(*temp_s0, s32 *, 0) = 0;
    *temp_s0 = (void *)-1;
}
