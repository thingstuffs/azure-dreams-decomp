#include "common.h"
#include "engine/object.h"
#include "town/map.h"

extern struct { s32 v; s32 pad[0x520]; } object_flag_block;

/* Process the referenced record, clear its preceding word, and set local and global flags. */
void release_town_map_record(void *record_ref) {
    s32 global_flags;
    runtime_clear_value(*(s32 **)record_ref);
    *(u16 *)((u8 *) record_ref - 2) = (u16) (*(u16 *)((u8 *) record_ref - 2) | 0x8000);
    global_flags = object_flag_block.v;
    *(s32 *)((u8 *) record_ref - 0x10) = 0;
    object_flag_block.v = (s32) (global_flags | 0x8000);
}
