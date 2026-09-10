#include "common.h"

typedef struct {
    s32 words[21];
} TownRecord;

typedef struct {
    s32 words[4];
} CopyChunk;

extern u8 D_80010A80[];

/* itm_mon_koyaw_set: Store slot flags and copy the monster record for type 0x13. */
void itm_mon_koyaw_set(s32 slot, u8 *entry_flags, TownRecord *record, s8 record_byte)
{
    u8 *flags;
    u8 *copy_flags;
    u8 *copy_page;
    u8 *record_base;
    s32 *record_src;
    s32 *record_dst;
    s32 *chunk_end;
    s32 flag_bits;
    s32 flags_offset;
    s32 slot_index;

    do {
    } while (0);
    slot_index = slot;
    flags = (u8 *)0x80010000;
    slot = slot_index * 4;
    flags += slot;
    flags[0x980] = entry_flags[0];
    flags[0x981] = entry_flags[1];
    flags[0x982] = entry_flags[2];
    flags[0x983] = entry_flags[3];

    if (entry_flags[1] == 0x13) {
        record_src = (s32 *)record;
        record_dst = (s32 *)((u8 *)0x80010A80 + (slot_index * 0x54));
        chunk_end = record_src + 20;
        do {
            *(CopyChunk *)record_dst = *(CopyChunk *)record_src;
            record_src += 4;
            record_dst += 4;
        } while (record_src != chunk_end);
        do {
            *record_dst = *record_src;
        } while (0);
        flags_offset = slot_index * 4;
        copy_page = (u8 *)0x80010000;
        copy_flags = copy_page + flags_offset;
        record_base = copy_page + (slot_index * 0x54);
        flag_bits = copy_flags[0x983];
        flag_bits &= 0xC0;
        flag_bits |= slot_index;
        copy_flags[0x983] = flag_bits;
        record_base[0xAC4] = record_byte;
    }
}

/* MECHANISM: The retail leaf is frameless and holds the runtime index in $t2 across both regions.
   Explicit destination/end live ranges wrap a 16-byte chunk assignment, exposing $t0/$t1
   while retaining GCC's load-four/store-four lowering; the post-copy page base is scope-split. */
