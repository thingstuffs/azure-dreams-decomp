#include "common.h"

typedef struct TownEntry {
    s8 field0;
    s8 field1;
    s16 field2;
    s32 field4;
} TownEntry;

extern TownEntry D_800CF720[];

// Finds a town entry by its three key fields, returning the end index with its high bit set if absent.
s32 func_8008AD1C(s32 targetField0, s32 targetField1, s32 targetField2) {
    s32 entryIndex;

    for (entryIndex = 0; D_800CF720[entryIndex].field1 != -1; entryIndex++) {
        if (targetField0 == D_800CF720[entryIndex].field0 &&
            targetField1 == D_800CF720[entryIndex].field1 &&
            targetField2 == D_800CF720[entryIndex].field2) {
            return entryIndex;
        }
    }
    return entryIndex - 0x80000000;
}
