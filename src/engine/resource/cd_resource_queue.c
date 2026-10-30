/* Resource descriptor queuing and creation of callback pairs with default arguments. */
#include "common.h"
#include "engine/resource.h"
#include "engine/texture.h"

/* The owning scene header has a different legacy queue descriptor contract. */
extern void *create_callback_pair_payload(void *second_value, void *first_value, unsigned long unused_value);

/* Forward the values with two leading zeros and return the allocated node. */
void *create_callback_pair_default(int value)
{
    int saved_value = value;
    void *empty = 0;
    return create_callback_pair_payload(empty, empty, saved_value);
}


/* Fixed input buffers and the shared texture-result pointer. */
extern u8 resource_queue_input_buffer[0x10];
extern u8 D_80023000[0x10];

extern void queue_entity_resource_descriptor_pair(void *a0, void *a1, u16 a2); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */

/* Registers callbacks for the fixed buffers and returns the result-pointer slot. */
void *queue_cd_resource(s32 id)
{
    queue_entity_resource_descriptor_pair(&resource_queue_input_buffer, &D_80023000, (u16)id);
    return &runtime_texture_resource_handle;
}
