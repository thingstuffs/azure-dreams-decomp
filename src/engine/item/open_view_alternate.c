#include "common.h"
#include "dungeon/system.h"
#include "engine/cd.h"
#include "engine/item.h"
#include "slus.h"

/* Submits and drains CD task 6, then allocates the item with mode 3 and the supplied data pointers. */
struct ObjectNodeHeader *open_view_alternate(struct ObjectNodeHeader *owner, s32 item_index, struct DungeonItemEntry *item)
{
    submit_global_cd_command_six();
    drain_cd_command_queue();
    return allocate_item_without_data_override(owner, item_index, 3, item);
}
