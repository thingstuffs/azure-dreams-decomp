#include "common.h"

typedef struct S_8003DF0C {
    /* 0x0 */ u8 flags;
    /* 0x1 */ u8 pad1[5];
    /* 0x6 */ u16 id;
    /* 0x8 */ u8 pad2[4];
} S_8003DF0C; /* size 0xC */

/* Return the last ID match with flag 0x20 (or NULL) and subtract half the entry count from its index (or zero). */
S_8003DF0C *func_8003DF0C(S_8003DF0C *entry, s32 want, u16 *idx_out)
{
    u32 entry_count;
    u32 match_address;
    u8 entry_flags;

    match_address = 0;
    *idx_out = 0;
    entry_count = match_address;

    do {
        if (entry->flags & 0x20) {
            if (entry->id == want) {
                match_address = (u32)entry;
                *idx_out = entry_count;
            }
        }
        entry_count++;
        entry_flags = entry->flags;
        entry++;
    } while (!(entry_flags & 0x80));

    *idx_out = *idx_out - (entry_count >> 1);
    return (S_8003DF0C *)match_address;
}
