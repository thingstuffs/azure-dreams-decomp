#include "common.h"

extern u8 D_800E045D[];

void *func_80099978(void *arg0) {
    register u8 *dst ASM_REG("$4") = (u8 *)arg0;   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

    *dst = D_800E045D[0];
    dst++;
    *dst = D_800E045D[1];
    dst++;
    *dst = 7;
    dst++;
    *dst = 7;
    dst++;

    return dst;
}
