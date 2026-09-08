#include "common.h"

extern s32 D_80100E2C[];

/* Read and clear the stored value, returning its lower 31 bits. */
s32 func_800A630C(void) {
    s32 stored_value = D_80100E2C[0];
    D_80100E2C[0] = 0;
    return stored_value & 0x7FFFFFFF;
}
