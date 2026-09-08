#include "common.h"

// Returns the sign of a weighted sum of the selected entry's first two components divided by 4096.
s32 func_8008C3B8(s32 *entries, s32 entryIndex, s16 *weights) {
    s32 *selectedEntry;
    s32 weightedSum;

    entryIndex <<= 4;
    entryIndex += (s32)entries;
    selectedEntry = (s32 *)entryIndex;
    weightedSum = (weights[0] * (selectedEntry[0] / 4096)) +
                  (weights[1] * (selectedEntry[1] / 4096));
    if (weightedSum == 0) {
        return 0;
    }
    if (weightedSum < 0) {
        return -1;
    }
    return 1;
}
