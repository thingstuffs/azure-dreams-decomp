#include "common.h"

typedef struct Entry {
    s32 a;
    s32 b;
} Entry;

extern Entry D_800CF720[];

/* Sums the b values of the requested number of entries. */
s32 func_8008ACE8(s32 entry_count) {
    s32 sum;
    s32 entry_index;

    sum = 0;
    for (entry_index = 0; entry_index < entry_count; entry_index++) {
        sum += D_800CF720[entry_index].b;
    }
    return sum;
}
