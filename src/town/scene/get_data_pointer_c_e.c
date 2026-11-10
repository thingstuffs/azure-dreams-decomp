#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_80016A0C;

/* Returns the address of D_80016A0C. */
s32 *get_data_pointer_16_a_0_c(void) {
    return &D_80016A0C;
}
