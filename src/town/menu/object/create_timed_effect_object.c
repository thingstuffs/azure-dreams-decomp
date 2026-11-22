#include "common.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "town/event/state.h"
#include "engine/node.h"
#include "town/menu/object.h"

struct IntVector3;        /* extern */

/* Creates an object, copies its source data fields, and initializes its state. */
void create_timed_effect_object(TownObjectRecord *owner, ObjectPosition *position, SpriteFrameState *source) {
    BoundsExpiryObject *objectState;
    ObjectNodeHeader *createdObject;
    SpriteFrameState *objectData;

    createdObject = create_town_effect_object(NODE_HEADER(owner), (struct IntVector3 *)(position), (s32)(&retire_object_on_check_or_timeout), 0);
    objectState = NODE_BODY(createdObject);
    if (createdObject != NULL) {
        objectData = createdObject->sprite;
        objectData->source = source->source;
        objectData->flags = source->flags;
        register_node_if_unregistered(objectState, project_sprite_chain);
        objectState->timer = 5;
    }
}
