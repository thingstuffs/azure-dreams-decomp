#include "common.h"

extern u8 D_800FC418;

/* Set D_800FC418 to 0xFF and return 1. */
s32 func_8008B7F4(void) {
    D_800FC418 = 0xFF;
    return 1;
}
