#include "common.h"

extern u8 D_800FC418;

/* start_mogura_func: set the mogura start flag and return success. */
s32 func_8008B7F4(void) {
    D_800FC418 = 0xFF;
    return 1;
}
