#include "common.h"

/* Set the word at 0x80409504 to 4 and return zero. */
s32 func_800199FC(void) {
    *(s32 *)0x80409504 = 4;
    return 0;
}
