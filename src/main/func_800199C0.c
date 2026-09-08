#include "common.h"

/* Sets the flag at 0x80409504 and returns zero. */
s32 func_800199C0(void) {
    *(s32 *)0x80409504 = 1;
    return 0;
}
