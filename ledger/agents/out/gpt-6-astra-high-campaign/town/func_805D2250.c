#include "common.h"
#include "m2c_compat.h"

s32 func_800191E8(M2C_UNK *);                                /* extern */
extern M2C_UNK D_8001AA2E;

/* Return the fallback pointer when the input check is below -47. */
M2C_UNK *func_805D2250(M2C_UNK *input) {
    M2C_UNK *selected_ptr;

    selected_ptr = input;
    if (func_800191E8(input) < -0x2F) {
        selected_ptr = &D_8001AA2E;
    }
    return selected_ptr;
}
