#include "common.h"

extern s32 D_80019BB4;

/* Returns whether D_80019BB4 is set to 1. */
s32 get_set_1(void) {
    return D_80019BB4 == 1;
}
