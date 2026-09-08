#include "common.h"

/* S_8004761C_Entry: array element (same family as S_800482C8_Entry); stride 0xC,
 * only the flags byte at offset 0 is read here. */
struct S_8004761C_Entry {
    u8 flags;
    u8 pad[0xB];
};

extern void func_80047468(struct S_8004761C_Entry *a0, s32 a1, s32 a2);

/* Packs and uploads entries with flags 0x60 clear using data offsets stored before the array. */
void func_8004761C(struct S_8004761C_Entry *entries, s32 *source_record_ptr)
{
    struct S_8004761C_Entry *entry = entries;
    s32 *source_record = source_record_ptr;
    u16 *data_offsets = (u16 *)entries;

    do {
        if (!(entry->flags & 0x60)) {
            data_offsets--;
            func_80047468(entry, *source_record, *data_offsets);
        }
    } while (!((entry++)->flags & 0x80));
}
