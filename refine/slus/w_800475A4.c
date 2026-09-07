#include "common.h"

struct S_800475A4_Entry {
    u8 flags;
    u8 pad[0xB];
};

extern void func_80047338(struct S_800475A4_Entry *a0, s32 a1, u16 a2);

/* Processes entries without flags 0x60 using preceding u16 values, through the entry marked 0x80. */
void func_800475A4(struct S_800475A4_Entry *entries, s32 *value_ptr)
{
    struct S_800475A4_Entry *entry = entries;
    s32 *value = value_ptr;
    u16 *cursor = (u16 *)entries;

    do {
        if (!(entry->flags & 0x60)) {
            cursor--;
            func_80047338(entry, *value, *cursor);
        }
    } while (!((entry++)->flags & 0x80));
}
