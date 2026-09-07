#include "common.h"

/* S_800482C8: array element for the entity/monster list iterated here;
 * stride 0xC, only the flags byte at offset 0 is read. */
struct S_800482C8_Entry {
    u8 flags;
    u8 pad[0xB];
};

/* S_80082E60: global state struct; field at offset 0xA (u8) selects which
 * of two callback functions is invoked. This is the same struct as
 * src/w_80040BB4.c's S_80082E60, which currently names this byte pad_A
 * (unused there) -- it should be renamed field_A and reconciled. */
struct S_80082E60 {
    char pad0[0xA];
    u8 field_A;
};

extern struct S_80082E60 D_80082E60;

extern void func_80047338(struct S_800482C8_Entry *a0, s32 a1, s32 a2);
extern void func_80047468(struct S_800482C8_Entry *a0, s32 a1, s32 a2);

/* Dispatches eligible entries to the selected callback with a shared value and successive words preceding the array. */
void func_800482C8(struct S_800482C8_Entry *entries, s32 *shared_value)
{
    struct S_800482C8_Entry *entry = entries;
    s32 *value_ptr = shared_value;
    s32 *value_cursor = (s32 *)entries;

    do {
        if (!(entry->flags & 0x60)) {
            value_cursor--;
            if (D_80082E60.field_A == 1) {
                func_80047468(entry, *value_ptr, *value_cursor);
            } else {
                func_80047338(entry, *value_ptr, *value_cursor);
            }
        }
    } while (!((entry++)->flags & 0x80));
}
