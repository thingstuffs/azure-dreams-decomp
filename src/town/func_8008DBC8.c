#include "common.h"

extern s32 func_8008B2E4(s32 arg0);

extern u8 D_800CF828[15];
extern s32 D_800CF838[16];

/* Returns whether any of the 15 selected entries passes func_8008B2E4. */
s32 func_8008B328(void) {
    s32 entry_index;

    for (entry_index = 0; entry_index < 15; entry_index++) {
        if (func_8008B2E4(D_800CF838[D_800CF828[entry_index]]) != 0) {
            return 1;
        }
    }

    return 0;
}
