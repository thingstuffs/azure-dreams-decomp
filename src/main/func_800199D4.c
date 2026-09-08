#include "common.h"

/* Sets the value at 0x80409504 to 2 and returns zero. */
s32 func_800199D4(void) {
    *(s32 *)0x80409504 = 2;
    return 0;
}
