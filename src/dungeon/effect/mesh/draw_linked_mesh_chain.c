#include "dungeon/effect/mesh_callbacks_api.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/effect.h"

/*
 * Transforms and queues each linked mesh using its payload kind, follows the chain headers, and
 * returns zero at the end.
 */
s32 draw_linked_mesh_chain(void *body, ObjectPosition *value, SpriteFrameState *payload) {
    ObjectNodeHeader *next;
    do {
        transform_mesh_and_append_draw_packets(body, value, payload, payload->depth_bias);
        next = NODE_HEADER(body)->chain_next;
        body = NODE_BODY(next);
        if (next != 0) {
            value = next->position;
            payload = next->sprite;
        }
    } while (next != 0);
    return 0;
}
