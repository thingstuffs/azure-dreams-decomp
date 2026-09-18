#include "common.h"

extern s32 D_800CF85C[];

/* Checks whether a value appears in the zero-terminated table. */
s32 func_8008B2E4(s32 value) {
    s32 i = 0;

    while (D_800CF85C[i] != 0) {
        if (value == D_800CF85C[i]) {
            return 1;
        }
        i++;
    }
    return 0;
}
