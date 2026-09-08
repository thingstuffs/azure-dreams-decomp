#include "common.h"

/* Count the 20 table entries whose first halfword matches the packed input bytes. */
s16 func_800A6928(s32 high_byte, s32 low_byte) {
    u8 *entry_cursor;
    u32 table_page;
    s32 match_count;
    s32 entry_index;
    s32 packed_value;

    packed_value = (high_byte << 8) | (low_byte & 0xFF);
    match_count = 0;
    entry_index = 0x13;
    packed_value &= 0xFFFF;
    table_page = 0x80010000;
    entry_cursor = (u8 *)(table_page | 0x4C);
    do {
        if (*(u16 *)*(u32 *)(entry_cursor + 0x29C) == packed_value) {
            match_count++;
        }
        entry_index--;
        entry_cursor -= 4;
    } while (entry_index >= 0);
    return match_count;
}
