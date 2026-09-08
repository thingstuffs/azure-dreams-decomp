#include "common.h"

/* Returns whether the value at 0x804094EC is nonzero. */
s32 func_8001A9A4(void) {
    return *(s32 *)0x804094EC != 0;
}
