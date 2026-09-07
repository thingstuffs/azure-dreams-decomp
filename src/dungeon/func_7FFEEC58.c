#include "common.h"

s32 func_8008C3B8(s32 *base, s32 index, s16 *coeff) {
    s32 *entry;
    s32 sum;

    index <<= 4;
    index += (s32)base;
    entry = (s32 *)index;
    sum = (coeff[0] * (entry[0] / 4096)) +
          (coeff[1] * (entry[1] / 4096));
    if (sum == 0) {
        return 0;
    }
    if (sum < 0) {
        return -1;
    }
    return 1;
}
