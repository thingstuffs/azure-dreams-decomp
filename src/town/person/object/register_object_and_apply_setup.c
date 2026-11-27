#include "shared/object_index_slots.h"
#include "shared/slus_callbacks.h"
#include "engine/node.h"
#include "town/person/object.h"

void register_object_and_apply_setup(TownObjectRecord *object, void *update_context, void *setup_context)
{
    register_node_if_unregistered(object, project_sprite_chain);
    object_index_slots[object->slot].motion_id = 0;
    apply_object_setup_and_update(object, update_context, setup_context);
}
