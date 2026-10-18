#include "modules/dungeon_ovl_1831cd8.h"

void *get_mapped_menu_table_entry(s32 row_id, s32 entry_index)
{
    s32 row;

    row = 2;
    if (row_id != 0x39) {
        row = row_id;
    }
    return D_800287EC + (row * 0x41) + (entry_index * 0xD);
}
