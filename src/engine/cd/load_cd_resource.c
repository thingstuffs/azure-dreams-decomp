#include "engine/scene/address_slot.h"

#include "common.h"

/* Inferred present ownership; canonical row body is included unchanged. */
void *D_80081528 = 0;

#include "engine/scene/address_slot.h"

void *load_cd_resource(int resource_id)
{
    queue_entity_resource_descriptor_pair(&D_80119000, &D_80126000, (unsigned short)resource_id);
    drain_cd_command_queue();
    D_80081528 = func_80047AB0(&D_80119000, 5, 0x7F80, 0xF, &D_80126000);
    return &D_80081528;
}
