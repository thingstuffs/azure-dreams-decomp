/* Resource descriptor queuing and creation of callback pairs with default arguments. */
#include "common.h"
#include "engine/resource.h"
#include "engine/texture.h"

#include "engine/scene/removal_counter.h"

/* Forward the values with two leading zeros and return the allocated node. */
void *allocate_node_body(int value)
{
    int saved_value = value;
    return create_node_with_record_pair(0, 0, saved_value);
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
