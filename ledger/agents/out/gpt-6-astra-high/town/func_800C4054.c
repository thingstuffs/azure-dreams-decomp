#include "common.h"

s32 func_80053EF0();                         /* extern */

/* Returns whether func_80053EF0 reports zero for argument 1. */
s32 func_800C17B4(void) {
    return func_80053EF0(1) == 0;
}
