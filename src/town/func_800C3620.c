#include "common.h"

extern void func_80033AE8(s32 arg0);
extern s16 D_800D253C[66];
extern s16 D_800D25C0[66];

/* Processes paired array entries until the first array's zero terminator. */
void func_800C0D80(void) {
    if (D_800D253C[0] != 0) {
        s32 entryIndex = 0;

        do {
            func_80033AE8(D_800D253C[entryIndex]);
            func_80033AE8(D_800D25C0[entryIndex]);
            entryIndex++;
        } while (D_800D253C[entryIndex] != 0);
    }
}
