#include "common.h"

typedef struct S_8004A0C0 {
    s32 value;
    s32 mask;
} S_8004A0C0;

extern S_8004A0C0 D_800712FC[13];

/* Returns the first table value whose mask overlaps the flags, or zero if none match. */
s32 func_8004A0C0(s32 flags) {
    s32 result = 0;
    s32 entry_index = 0;
    S_8004A0C0 *entry = D_800712FC;

    for (; entry_index < 13; entry_index++, entry++) {
        if (entry->mask & flags) {
            result = entry->value;
            break;
        }
    }
    return result;
}
