#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_80090378;
extern M2C_UNK *D_800D0438;

/* plt_init_sleep_set: set the sleep initialization pointer. */
void plt_init_sleep_set(void) {
    D_800D0438 = &D_80090378;
}
