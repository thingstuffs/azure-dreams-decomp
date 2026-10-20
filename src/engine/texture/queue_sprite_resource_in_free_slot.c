#include "common.h"

extern s32 find_free_sprite_resource_slot(void);
extern void queue_sprite_resource_slot_reads(s32 a0, s32 a1);

/* Registers a value in a free slot and returns its index, or -1 if none is free. */
s32 queue_sprite_resource_in_free_slot(s32 value)
{
    s32 slot = find_free_sprite_resource_slot();

    if (slot != -1) {
        queue_sprite_resource_slot_reads(slot, value);
    }
    return slot;
}
