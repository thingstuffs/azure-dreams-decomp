#include "common.h"

extern s32 func_807018AC(s16 value);
extern s16 D_80700BAC[];
extern u8 D_80700BB4[];

/* Returns whether the indexed secondary check passes while both primary checks fail. */
s32 func_80874C9C(s32 value_index) {
    s16 *primary_values;
    s32 passes;

    primary_values = D_80700BAC;
    passes = 0;
    if (func_807018AC(primary_values[value_index]) == 0) {
        passes = 0;
        if (func_807018AC(primary_values[0]) == 0) {
            passes = func_807018AC(*(s16 *)(D_80700BB4 + value_index * 2)) != 0;
        }
    }
    return passes;
}
