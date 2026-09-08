#include "common.h"

extern s32 D_800CF720[];

s32 func_8008ACE8(s32 arg0) {
    s32 *ptr;
    s32 sum;
    register s32 i ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 value;

    i = 0;
    sum = i;
    if (arg0 > 0) {
        ptr = D_800CF720;
        do {
            value = ptr[1];
            ASM_KEEP(value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            i += 1;
            sum += value;
            ptr += 2;
        } while (i < arg0);
    }
    return sum;
}
