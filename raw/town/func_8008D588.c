#include "common.h"

extern s32 D_800CF720[];

s32 func_8008ACE8(s32 arg0) {
    s32 *ptr;
    register s32 sum ASM_REG("$5");
    register s32 i ASM_REG("$6");
    s32 value;

    i = 0;
    sum = i;
    if (arg0 > 0) {
        ptr = D_800CF720;
        do {
            value = ptr[1];
            ASM_KEEP(value);
            i += 1;
            sum += value;
            ptr += 2;
        } while (i < arg0);
    }
    return sum;
}
