#include "common.h"

extern s32 D_80019BB0;

/* Returns whether D_80019BB0 is nonzero. */
s32 is_global_flag_19_bb_0_set(void) {
    return D_80019BB0 != 0;
}
