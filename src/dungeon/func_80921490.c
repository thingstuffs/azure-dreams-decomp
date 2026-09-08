#include "common.h"

/* Clears matching table entries and the associated byte in each indexed record. */
void func_800F6490(void) {
    s32 slot_index;
    u32 table_base;
    s32 match_byte1;
    s32 match_byte0;
    volatile u32 *entry;
    volatile u8 *scan_ptr;
    u32 record_index;

    slot_index = 0x3F;
    table_base = 0x80010000;
    match_byte1 = 0x13;
    match_byte0 = 2;
    entry = (volatile u32 *)(table_base | 0xA7C);
    scan_ptr = (volatile u8 *)(table_base | 0xFC);
    do {
        if (scan_ptr[0x981] == match_byte1 && scan_ptr[0x980] == match_byte0) {
            record_index = scan_ptr[0x983] & 0x3F;
            ((u8 *)table_base)[record_index * 0x54 + 0xA93] = 0;
            *entry = 0;
        }
        entry--;
        slot_index--;
        scan_ptr -= 4;
    } while (slot_index >= 0);
}
