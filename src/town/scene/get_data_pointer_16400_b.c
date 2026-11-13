#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_80016400;

/* Returns the address of D_80016400. */
s32 *get_data_pointer_16400(void) {
    return &D_80016400;
}
