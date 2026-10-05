#include "common.h"

typedef struct {
    s32 words[21];
} TownRecord;


/* itm_mon_koyaw_set: Store slot flags and copy the monster record for type 0x13. */
void itm_mon_koyaw_set(s32 slot, u8 *entry_flags, TownRecord *record, s8 record_byte)
{
    u8 *flags;
    u8 *copy_flags;
    u8 *copy_page;
    u8 *record_base;
    s32 flag_bits;
    s32 flags_offset;

    flags = (u8 *)0x80010000;
    flags += slot * 4;
    flags[0x980] = entry_flags[0];
    flags[0x981] = entry_flags[1];
    flags[0x982] = entry_flags[2];
    flags[0x983] = entry_flags[3];

    if (entry_flags[1] == 0x13) {
        *(TownRecord *)((u8 *)0x80010A80 + (slot * 0x54)) = *record;
        flags_offset = slot * 4;
        copy_page = (u8 *)0x80010000;
        copy_flags = copy_page + flags_offset;
        record_base = copy_page + (slot * 0x54);
        flag_bits = copy_flags[0x983];
        flag_bits &= 0xC0;
        flag_bits |= slot;
        copy_flags[0x983] = flag_bits;
        record_base[0xAC4] = record_byte;
    }
}

/* MECHANISM: The retail leaf is frameless and holds the runtime index in $t2 across both regions.
   Explicit destination/end live ranges wrap a 16-byte chunk assignment, exposing $t0/$t1
   while retaining GCC's load-four/store-four lowering; the post-copy page base is scope-split. */
