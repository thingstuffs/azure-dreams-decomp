#include "common.h"
#include "m2c_compat.h"

extern s32 D_80082E88;
extern s32 D_80100E2C;

/* Stores the supplied value and returns D_80082E88 minus 12 with its sign bit cleared. */
s32 func_800A62E8(M2C_UNK unused_0, M2C_UNK unused_1, M2C_UNK unused_2, s32 stored_value) {
    D_80100E2C = stored_value;
    return (D_80082E88 - 0xC) & 0x7FFFFFFF;
}
