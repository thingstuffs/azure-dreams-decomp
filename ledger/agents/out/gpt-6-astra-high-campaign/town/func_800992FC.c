#include "common.h"

/* Return the second word of an indexed entry in the record's nested table. */
s32 func_80096A5C(void *record, s32 row_index, s32 entry_index) {
    u8 *table_handle = *(u8 **)((u8 *)record + 0x28);
    u8 *table_ref = *(u8 **)table_handle;
    u8 *rows = *(u8 **)table_ref;
    u8 *entries = *(u8 **)(((s32)(row_index << 0x10) >> 0xE) + (s32)rows);
    return *(s32 *)(entries + ((s32)(entry_index << 0x10) >> 0xD) + 4);
}
