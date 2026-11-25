#include "dungeon/system.h"

/* Forwards the item request with no data override. */
void *allocate_item_without_data_override(void *owner, s32 context, s32 mode, void *descriptor) {
    /* The allocator stores the owner address in a signed word. */
    return allocate_item_object((s32)(unsigned long)owner, context, mode, descriptor, 0);
}
