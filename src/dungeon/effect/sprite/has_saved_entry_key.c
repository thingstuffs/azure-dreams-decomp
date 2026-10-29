#include "common.h"
#include "dungeon/effect/sprite.h"

/* Return whether any of 20 referenced entries matches the combined byte key. */
s32 has_saved_entry_key(s32 key, s32 key_low) {
    s32 entry_index;
    s8 *table_cursor;
    s32 result;

    key = (key << 8) | (key_low & 0xFF);
    entry_index = 0x13;
    key &= 0xFFFF;
    table_cursor = (s8 *)0x8001004C;
    for (;;) {
        result = **(u16 **)(table_cursor + 0x29C);
        if (result == key) {
            result = 1;
        } else {
            entry_index--;
            table_cursor -= 4;
            if (entry_index < 0) {
                result = 0;
            } else {
                continue;
            }
        }
        break;
    }
    return result;
}
