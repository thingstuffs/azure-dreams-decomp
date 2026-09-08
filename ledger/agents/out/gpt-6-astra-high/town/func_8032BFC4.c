#include "common.h"

s32 func_8001AF7C();                                /* extern */

/* Returns whether func_8001AF7C reports a value of at least two. */
s32 func_800167C4(void) {
    return func_8001AF7C() >= 2;
}
