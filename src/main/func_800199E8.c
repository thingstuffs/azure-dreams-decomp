#include "common.h"

/* Set the value at 0x80409504 to 3 and return zero. */
s32 func_800199E8(void) {
    *(s32 *)0x80409504 = 3;
    return 0;
}
