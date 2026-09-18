#include "common.h"

extern s32 D_800CF85C[];

/* Return whether the zero-terminated table contains the target value. */
s32 func_8008B2E4(s32 target_value) {
    s32 i = 0;

    while (D_800CF85C[i] != 0) {
        if (target_value == D_800CF85C[i]) {
            return 1;
        }
        i++;
    }
    return 0;
}
