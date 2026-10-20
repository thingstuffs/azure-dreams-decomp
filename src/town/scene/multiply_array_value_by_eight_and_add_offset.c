#include "common.h"

extern s32 D_00000FD0[];
extern s32 D_00001038;

/* Multiply the first array value by eight and add D_00001038. */
void multiply_array_value_by_eight_and_add_offset(void) {
    D_00000FD0[0] = (D_00000FD0[0] * 8) + D_00001038;
}
