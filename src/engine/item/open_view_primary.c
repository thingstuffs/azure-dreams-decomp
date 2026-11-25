#include "common.h"
#include "dungeon/system.h"

#include "engine/cd.h"
#include "engine/item.h"
#include "slus.h"

/* Prepares shared state and initializes an item in mode 1. */
struct ObjectNodeHeader *open_view_primary(struct ObjectNodeHeader *owner, s32 item_index, struct DungeonItemEntry *item) {
    submit_global_cd_command_six();
    drain_cd_command_queue();
    return allocate_item_without_data_override(owner, item_index, 1, item);
}
