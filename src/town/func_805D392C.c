#include "common.h"

extern u8 D_800198A4[];
extern s32 D_80019B8C;

/* Returns the word at offset 12 in the selected 24-byte table entry. */
s32 func_8001792C(void) {
    s32 entry_offset;
    u8 *table_base;

    table_base = D_800198A4;
    entry_offset = D_80019B8C * 0x18;
    return *(s32 *)(table_base + entry_offset + 12);
}
