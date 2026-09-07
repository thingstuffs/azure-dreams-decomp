#include "common.h"

typedef struct S_8003DF0C {
    /* 0x0 */ u8 flags;
    /* 0x1 */ u8 pad1[5];
    /* 0x6 */ u16 id;
    /* 0x8 */ u8 pad2[4];
} S_8003DF0C; /* size 0xC */

/* Scan an array of 0xC-byte entries starting at ent, looking for one with
 * flags & 0x20 whose id field matches want. Writes the (adjusted) index of
 * the match, or 0, into *idxOut, then returns a pointer to the matching
 * entry (or NULL). The scan stops after processing the entry that has the
 * flags & 0x80 "last" bit set. The stored index is then reduced by half of
 * the total number of entries scanned (rounded down). */
S_8003DF0C *func_8003DF0C(S_8003DF0C *ent, s32 want, u16 *idxOut)
{
    u32 count;
    u32 found;
    u8 flags;

    found = 0;
    *idxOut = 0;
    count = found;

    do {
        if (ent->flags & 0x20) {
            if (ent->id == want) {
                found = (u32)ent;
                *idxOut = count;
            }
        }
        count++;
        flags = ent->flags;
        ent++;
    } while (!(flags & 0x80));

    *idxOut = *idxOut - (count >> 1);
    return (S_8003DF0C *)found;
}
