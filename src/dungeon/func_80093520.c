#include "common.h"

extern u8 D_80081484[];
extern u8 D_80081470[];
s16 dungeonFindTableEntryAddressIndex();

// Returns a one-based lookup index, a special code for known data addresses, or zero.
s32 dungeonGetSpecialTableDataIndex(s32 dataAddress) {
    s32 lookupIndex;

    lookupIndex = (s16)dungeonFindTableEntryAddressIndex();
    if (lookupIndex >= 0) {
        lookupIndex++;
        return (s16)lookupIndex;
    }
    if (dataAddress == D_80081484) {
        return 0x15;
    }
    if (dataAddress == D_80081470) {
        return 0x16;
    }
    return 0;
}
