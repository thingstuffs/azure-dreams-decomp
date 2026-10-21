/* Special table index (G00320). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:dungeon/func_800934E8. */
#include "dungeon/player/special_table_index_g00320.h"

/* Returns the index of a matching table entry address, or -1. */
s32 find_table_entry_address_index(s32 entry_address) {
    s32 entry_index = 0x13;
    s8 *entry = (s8 *)0x80010294;

    do {
        if ((s32)entry != entry_address) {
            entry_index -= 1;
            entry -= 4;
            continue;
        }
        return (s16)entry_index;
    } while (entry_index >= 0);
    return -1;
}

s32 get_special_table_data_index(s32 dataAddress) {
    s32 lookupIndex;

    lookupIndex = (s16)find_table_entry_address_index((s32)dataAddress);
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
