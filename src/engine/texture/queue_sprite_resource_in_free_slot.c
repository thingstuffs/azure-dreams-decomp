#include "common.h"
#include "engine/texture.h"

/* Registers a value in a free slot and returns its index, or -1 if none is free. */
s32 queue_sprite_resource_in_free_slot(s32 value)
{
    s32 slot = find_free_sprite_resource_slot();

    if (slot != -1) {
        queue_sprite_resource_slot_reads(slot, value);
    }
    return slot;
}
