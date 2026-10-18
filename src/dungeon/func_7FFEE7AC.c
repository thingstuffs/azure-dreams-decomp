#include "modules/dungeon_town_map.h"

void release_town_map_record(void *record) {
    int global_flags;
    runtime_clear_value(*(void **)record);
    ((u16 *)record)[-1] |= 0x8000;
    global_flags = object_flag_block.flags;
    ((s32 *)record)[-4] = 0;
    object_flag_block.flags = global_flags | 0x8000;
}
