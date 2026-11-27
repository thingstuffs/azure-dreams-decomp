#include "common.h"
#include "shared/town_object.h"
#include "shared/object_index_slots.h"
#include "engine/node.h"
#include "town/person.h"
#include "town/person/object.h"

/* Take the object's node off its registration, clear its index slot, then set it up and update it. */
void unregister_and_update_object(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *sprite) {
    unlink_node_if_registered(object);
    object_index_slots[object->slot].motion_id = 0;
    apply_object_setup_and_update(object, position, sprite);
}
