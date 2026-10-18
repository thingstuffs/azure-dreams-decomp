#include "common.h"

/* Already-matched callee (defined elsewhere): returns &D_800FC000[a0]. */
extern void *get_sprite_resource_slot_buffer(int a0);

extern void queue_entity_resource_descriptor_pair(void *a0, void *a1, unsigned short a2);

extern void *D_80080A90;

/* Passes the indexed slot, global pointer, and low 16 bits of value to queue_entity_resource_descriptor_pair. */
void queue_sprite_resource_slot_reads(int slot_index, int value)
{
    queue_entity_resource_descriptor_pair(get_sprite_resource_slot_buffer(slot_index), D_80080A90, (unsigned short)value);
}
