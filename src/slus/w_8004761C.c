#include "common.h"

/* S_8004761C_Entry: array element (same family as S_800482C8_Entry); stride 0xC,
 * only the flags byte at offset 0 is read here. */
struct S_8004761C_Entry {
    u8 flags;
    u8 pad[0xB];
};

extern void func_80047468(struct S_8004761C_Entry *a0, s32 a1, s32 a2);

/* Dispatches entries with flags 0x60 clear using preceding u16 values until flag 0x80 marks the end. */
void func_8004761C(struct S_8004761C_Entry *entries, s32 *shared_value)
{
    struct S_8004761C_Entry *entry = entries;
    s32 *value_ptr = shared_value;
    u16 *cursor = (u16 *)entries;

    do {
        if (!(entry->flags & 0x60)) {
            cursor--;
            func_80047468(entry, *value_ptr, *cursor);
        }
    } while (!((entry++)->flags & 0x80));
}
