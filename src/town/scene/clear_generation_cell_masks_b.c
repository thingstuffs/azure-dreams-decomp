#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_80016400;

/* Returns the address of D_80016400. */
s32 *clear_generation_cell_masks(void) {
    return &D_80016400;
}
