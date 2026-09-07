#include "common.h"

/* Checks pad key state 1 (e.g. select/pause) then key state 4; returns 1 only
 * when key-1 status is 0 and key-4 status is also 0. */
s32 func_8004EBDC(void) {
    s32 ret = 0;

    if (func_80053EF0(1) == 0) {
        if (func_80053EF0(4) == 0) {
            ret = 1;
        }
    }
    return ret;
}
