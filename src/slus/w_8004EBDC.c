#include "common.h"

/* Returns 1 when pad key states 1 and 4 are both zero. */
s32 func_8004EBDC(void) {
    s32 keys_clear = 0;

    if (func_80053EF0(1) == 0) {
        if (func_80053EF0(4) == 0) {
            keys_clear = 1;
        }
    }
    return keys_clear;
}
