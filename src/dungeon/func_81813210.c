#include "modules/dungeon_ovl_1831cd8.h"

void initialize_menu_record_range(void *record, s32 range_start, s32 value) {
    *(s32 *)((u8 *)record + 0x44) = range_start;
    range_start += 0x20;
    *(s32 *)((u8 *)record + 0x04) = 4;
    *(s32 *)((u8 *)record + 0x48) = range_start;
    *(s32 *)((u8 *)record + 0x18) = value;
    *(s32 *)record = 0;
    *(u8 **)((u8 *)record - 0x10) = (void *)advance_menu_value_fade;
}
