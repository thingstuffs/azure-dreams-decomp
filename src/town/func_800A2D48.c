#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_80100AA0;

/* Returns the address of D_80100AA0. */
M2C_UNK *townGetAddressGlobal80100AA0(void) {
    return &D_80100AA0;
}
