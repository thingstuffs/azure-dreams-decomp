#include "common.h"

extern s8 D_800FC418;

/* Clears D_800FC418 and returns success. */
s32 func_8008B808(void) {
    D_800FC418 = 0;
    return 1;
}
