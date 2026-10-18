#include "modules/dungeon_ovl_1831cd8.h"

s32 find_menu_entry_from_index(s32 target_value, s32 start_index)
{
    s32 index;

    for (index = start_index; index < 0x40; index++) {
        if (((ovl_1831cd8_81811F04_S_func_80026F04_0 *)((u8 *)0x80010000 + index * 19))->unk_57D2 == target_value) {
            return index;
        }
    }
    return -1;
}
