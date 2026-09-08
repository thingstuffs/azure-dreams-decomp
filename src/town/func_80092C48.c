#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_80090378;
extern M2C_UNK *D_800D0438;

/* plt_init_sleep_set: sets the message skip-disable pointer. */
void func_800903A8(void) {
    D_800D0438 = &D_80090378;
}
