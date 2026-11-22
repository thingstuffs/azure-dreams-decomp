#include "shared/object_node.h"
#include "common.h"
#include "engine/effect.h"
#include "engine/graphics.h"
#include "engine/scene.h"
#include "slus.h"

#include "engine/effect/resource_transition.h"

/* Clears the owner flag and allocates and initializes a callback node with its context. */
void *scene_create_resource_transition(struct ObjectNodeHeader *owner, s32 callback_index)
{
    ObjectNodeHeader *node;
    ResourceTransitionBody *body;

    owner->flags = owner->flags & 0xDFFF;
    node = allocate_flagged_object_node(0);
    if (node != 0) {
        body = NODE_BODY(node);
        body->callback_index = callback_index;
        body->owner = owner;
        SD_Call(0xD1);
        NODE_HEADER(body)->update_callback = schedule_deferred_resource_transition;
        begin_transition_texture_read(&body->image_ready);
    }
    return node;
}
