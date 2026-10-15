/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "m2c_compat.h"

s16 func_8008C610();               

s16 func_8008CB58(s32 context, s32 data, s32 count) {
    s16 value;
    s16 minimum;
    s32 index;

    minimum = 0x7FFF;
    index = 0;
    if (count > 0) {
        do {
            value = func_8008C610(context, data, index);
            if ((value << 0x10) < (minimum << 0x10)) {
                minimum = value;
            }
            index += 1;
        } while (index < count);
    }
    return minimum;
}
