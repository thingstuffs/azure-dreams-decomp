#include "common.h"

extern s32 D_80019BB0;

/* Returns whether D_80019BB0 is neither 1 nor 5. */
s32 func_80017D98(void) {
    s32 is_other;

    is_other = 0;
    if (D_80019BB0 != 1) {
        is_other = D_80019BB0 != 5;
    }
    return is_other;
}
