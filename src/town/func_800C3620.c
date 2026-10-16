#include "common.h"

extern void clearResidentBitmapBit(s32 flag_id);
extern s16 D_800D253C[66];
extern s16 D_800D25C0[66];

/* Processes paired array entries until the first array's zero terminator. */
void townProcessPairedArraysUntilTerminator(void) {
    if (D_800D253C[0] != 0) {
        s32 entryIndex = 0;

        do {
            clearResidentBitmapBit(D_800D253C[entryIndex]);
            clearResidentBitmapBit(D_800D25C0[entryIndex]);
            entryIndex++;
        } while (D_800D253C[entryIndex] != 0);
    }
}
