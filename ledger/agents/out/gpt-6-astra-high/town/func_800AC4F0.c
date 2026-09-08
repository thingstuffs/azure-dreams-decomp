#include "common.h"

extern s32 D_8006ADD4;

/* Returns whether D_8006ADD4 equals 0xD000C. */
s32 func_800A9C50(void) {
    return D_8006ADD4 == 0xD000C;
}
