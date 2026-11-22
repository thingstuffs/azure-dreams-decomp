#include "common.h"
#include "town/map.h"
#include "shared/object_node.h"

#ifndef NULL
#define NULL 0
#endif

/* Process the initial value and each linked record value until the chain ends. */
s32 draw_linked_shaded_quad_rings(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *sprite) {
    ObjectNodeHeader *next;

    for (;;) {
        draw_shaded_quad_ring(sprite, position);
        next = NODE_HEADER(object)->chain_next;
        if (next == NULL) {
            break;
        }
        object = NODE_BODY(next);
        position = next->position;
        sprite = next->sprite;
    }
    return 0;
}
