#include "common.h"

extern int D_800E3548[64];

/* Clears all 64 entries in D_800E3548. */
void func_8001E96C(void) {
    s32 entry_index;

    for (entry_index = 0x3F; entry_index >= 0; entry_index--) {
        D_800E3548[entry_index] = 0;
    }
}
