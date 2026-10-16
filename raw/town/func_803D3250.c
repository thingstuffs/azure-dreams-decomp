#include "common.h"
#include "m2c_compat.h"

s32 func_8001A250(void *arg0, void *arg1) {
    s32 temp_a2;
    s32 temp_a2_2;
    s32 temp_a2_3;

    temp_a2 = M2C_FIELD(arg1, s16 *, 0) - M2C_FIELD(arg0, s16 *, 0);
    temp_a2_2 = M2C_FIELD(arg1, s16 *, 2) - M2C_FIELD(arg0, s16 *, 2);
    temp_a2_3 = M2C_FIELD(arg1, s16 *, 4) - M2C_FIELD(arg0, s16 *, 4);
    return (temp_a2 * temp_a2) + (temp_a2_2 * temp_a2_2) + (temp_a2_3 * temp_a2_3);
}
