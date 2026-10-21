#include "common.h"
#include "engine/texture.h"
#include "slus.h"

/* Allocate an unregistered entity's slot, retrying after cleanup if needed; return NULL if already registered. */
void *prepare_uncached_sprite_resource(s16 entity_index)
{
    s32 slot_index;
    s32 no_slot = -1;

    slot_index = find_sprite_resource_slot_by_id(entity_index);
    if (slot_index == no_slot) {
        slot_index = queue_sprite_resource_in_free_slot(entity_index);
        if (slot_index == no_slot) {
            clear_marked_slot_entries();
            slot_index = queue_sprite_resource_in_free_slot(entity_index);
        }
        return get_sprite_resource_slot_buffer(slot_index);
    }
    return 0;
}
