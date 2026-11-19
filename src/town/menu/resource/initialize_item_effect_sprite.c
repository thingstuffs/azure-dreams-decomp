#include "common.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "shared/slus_callbacks.h"
#include "shared/town_object.h"
#include "engine/node.h"
#include "town/menu/indexed_effect_vectors_g00583.h"


#include "town/menu/position_callbacks_api.h"

/* Initialize the object state from its byte value and set the context resource and callback. */
void initialize_item_effect_sprite(TownObjectRecord *object_arg, ObjectPosition *unused, struct SpriteFrameState *context) {
    TownObjectRecord *object = object_arg;

    NODE_HEADER(object)->update_callback = &follow_linked_position_or_retire;
    object->slot = (s32) object->variant;
    context->source = &item_effect_descriptor;
    register_node_if_unregistered(object, project_sprite_chain);
}
