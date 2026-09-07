#include "common.h"

typedef struct {
    s16 value;
    s16 first;
    s16 second;
    s16 unused;
} Entry;

extern Entry D_800E3CD8[4];

// Returns the value for a matching pair, stopping at the first value below two.
s16 func_800A4474(s16 firstKey, s16 secondKey) {
    s32 entryIndex;
    s16 entryValue;

    for (entryIndex = 0; entryIndex < 4; entryIndex++) {
        entryValue = D_800E3CD8[entryIndex].value;
        if (entryValue < 2) {
            return 0;
        }
        if ((firstKey == D_800E3CD8[entryIndex].first) &&
            (secondKey == D_800E3CD8[entryIndex].second)) {
            return entryValue;
        }
    }
    return 0;
}
