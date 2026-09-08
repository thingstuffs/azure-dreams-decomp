#include "common.h"

extern s32 D_80083E98[];

/* Returns the first value in the indexed 32-word entry. */
s32 func_80021D38(s32 entry_index) {
    return D_80083E98[entry_index * 32];
}
