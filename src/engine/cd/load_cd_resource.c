#include "engine/scene/address_slot.h"

#include "common.h"

/* Inferred present ownership; canonical row body is included unchanged. */
void *loaded_cd_resource_handle = 0;

#include "engine/scene/address_slot.h"
#include "engine/cd.h"

/*
 * Queues and drains the two CD resource descriptors, creates a handle with mode 5 and flags
 * 0x7F80/0xF, and returns the address of loaded_cd_resource_handle.
 */
void *load_cd_resource(int resource_id)
{
    queue_entity_resource_descriptor_pair(&cd_resource_primary_buffer, &cd_resource_secondary_buffer, (unsigned short)resource_id);
    drain_cd_command_queue();
    loaded_cd_resource_handle = func_80047AB0(&cd_resource_primary_buffer, 5, 0x7F80, 0xF, &cd_resource_secondary_buffer);
    return &loaded_cd_resource_handle;
}
