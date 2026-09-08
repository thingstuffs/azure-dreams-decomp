#include "common.h"

extern u8 D_800287EC[];

/* Return a table entry, mapping row 0x39 to row 2. */
void *func_80027110(s32 row_id, s32 entry_index)
{
    s32 row;

    row = 2;
    if (row_id != 0x39) {
        row = row_id;
    }
    return D_800287EC + (row * 0x41) + (entry_index * 0xD);
}
