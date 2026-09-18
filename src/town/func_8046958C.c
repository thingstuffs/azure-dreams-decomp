#include "common.h"

extern u8 D_80017BC8[];

/* Check whether the zero-terminated byte list contains the target value. */
s32 func_8001A58C(s32 target_value) {
    s32 i = 0;

    while (D_80017BC8[i] != 0) {
        if (target_value == D_80017BC8[i]) {
            return 1;
        }
        i++;
    }
    return 0;
}
