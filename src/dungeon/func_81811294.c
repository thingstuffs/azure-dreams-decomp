#include "modules/dungeon_ovl_1830850.h"

void inventory_process_resources_and_set_flags(void *object)
{
    u16 object_flags;
    s32 global_flags;

    if (object != 0) {
        inventory_clear_referenced_handle(*(void **)((u8 *)object + 0x74));
        func_8004B248((u16 **)((u8 *)object + 0x78));
        object_flags = *(u16 *)((u8 *)object + 0x1E);
        global_flags = object_flag_block.flags;
        *(u16 *)((u8 *)object + 0x1E) = object_flags | 0x8000;
        object_flag_block.flags = global_flags | 0x8000;
    }
}
