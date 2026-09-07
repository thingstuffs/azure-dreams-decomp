#include "common.h"

typedef struct S_8003DF0C {
    /* 0x0 */ u8 flags;
    /* 0x1 */ u8 pad1[5];
    /* 0x6 */ u16 id;
    /* 0x8 */ u8 pad2[4];
} S_8003DF0C; /* size 0xC */

/* Return the last ID match with flag 0x20 (or NULL) and subtract half the entry count from its index (or zero). */
S_8003DF0C *func_8003DF0C(S_8003DF0C *entry, s32 targetId, u16 *indexOut)
{
    u32 entryCount;
    u32 matchAddress;
    u8 entryFlags;

    matchAddress = 0;
    *indexOut = 0;
    entryCount = matchAddress;

    do {
        if (entry->flags & 0x20) {
            if (entry->id == targetId) {
                matchAddress = (u32)entry;
                *indexOut = entryCount;
            }
        }
        entryCount++;
        entryFlags = entry->flags;
        entry++;
    } while (!(entryFlags & 0x80));

    *indexOut = *indexOut - (entryCount >> 1);
    return (S_8003DF0C *)matchAddress;
}
