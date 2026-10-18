#include "modules/dungeon_ovl_1831cd8.h"

void retire_menu_object(void *object)
{
    u8 *objectData;
    u16 objectFlags;
    s32 globalFlags;

    if (object != 0) {
        objectData = (u8 *)object + 0x20;
        format_menu_referenced_values(*(void **)(objectData + 0x88));
        func_8004B1A4(*(void **)(objectData + 0x40));
        func_8004B248((u8 *)object + 0xAC);
        objectFlags = *(u16 *)((u8 *)object + 0x1E);
        globalFlags = object_flag_block.flags;
        *(u16 *)((u8 *)object + 0x1E) = objectFlags | 0x8000;
        object_flag_block.flags = globalFlags | 0x8000;
    }
}
