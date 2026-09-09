#include "common.h"
extern s32 D_8001029C[];
s32 func_8009904C(s32 target_value) {
    s32 entry_index;
    for (entry_index = 0; entry_index < 20; entry_index++) {
        if (D_8001029C[entry_index] == 0) break;
        if (D_8001029C[entry_index] == target_value) return (s16)entry_index;
    }
    return -1;
}
