#include "common.h"

s32 func_8001ADE0();

/* Returns whether every entry in a zero-terminated list passes func_8001ADE0. */
s32 func_80019CD8(s16 *values) {
    s16 *valueCursor;

    for (valueCursor = values; *valueCursor != 0; valueCursor++) {
        if (func_8001ADE0(*valueCursor) == 0) {
            break;
        }
    }
    return *valueCursor == 0;
}
