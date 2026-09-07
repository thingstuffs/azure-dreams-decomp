#include "common.h"

typedef struct S_8004A0C0 {
    s32 value;
    s32 mask;
} S_8004A0C0;

extern S_8004A0C0 D_800712FC[13];

/* Scan a 13-entry (value, mask) table for the first entry whose mask bits
   overlap the given flags, returning its value; 0 if none match. */
s32 func_8004A0C0(s32 flags) {
    s32 result = 0;
    s32 i = 0;
    S_8004A0C0 *entry = D_800712FC;

    for (; i < 13; i++, entry++) {
        if (entry->mask & flags) {
            result = entry->value;
            break;
        }
    }
    return result;
}
