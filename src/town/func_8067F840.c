#include "common.h"

extern u32 D_800188C8;   /* saved entry count (set by func_80016770 / func_8001679C) */

/* Return the saved entry count. */
u32 func_80016840(void) {
    return D_800188C8;
}
