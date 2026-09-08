#include "common.h"

extern int D_800E3648[64];

/* Clear the first 32 entries of D_800E3648. */
void func_8001F32C(void) {
    s32 entry_index;

    for (entry_index = 0x1F; entry_index >= 0; entry_index--) {
        D_800E3648[entry_index] = 0;
    }
}
