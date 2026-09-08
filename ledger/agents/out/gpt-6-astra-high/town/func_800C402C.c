#include "common.h"

extern s16 D_800D4258[2];
__asm__(".set D_800D4258, 0x800D4258");

/* Stores a pair of values in D_800D4258. */
void func_800C178C(s16 first_value, s16 second_value) {
    D_800D4258[0] = first_value;
    D_800D4258[1] = second_value;
}
