#include "common.h"
#include "engine/object.h"
#include "town/map.h"
#include "shared/object_node.h"

extern struct { s32 v; s32 pad[0x520]; } object_flag_block;

/* Process the referenced record, clear its preceding word, and set local and global flags. */
void release_town_map_record(TownMapBody *body) {
    s32 global_flags;
    clear_word(&body->context->unk_00);
    NODE_HEADER(body)->flags = (u16) (NODE_HEADER(body)->flags | 0x8000);
    global_flags = object_flag_block.v;
    NODE_HEADER(body)->update_callback = 0;
    object_flag_block.v = (s32) (global_flags | 0x8000);
}
