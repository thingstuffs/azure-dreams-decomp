
struct SpriteFrameState;

struct ObjectPosition;
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "dungeon/effect/mesh.h"

/* The registered three-word callback traverses the registry's +0x18 link.
 * register_node writes that link; dispatch_registered_draw_callbacks supplies payload and +8/+C. */

/* Transforms and draws sprite parts as quads for every linked node using each sprite's depth offset. */
s32 draw_linked_sprite_parts_as_quads(void *payload, ObjectPosition *position, SpriteFrameState *render_state)
{
    ObjectNodeHeader *next;
    do {
        transform_sprite_parts_to_quads((s32)payload, position, render_state, render_state->depth_bias);
        next = NODE_HEADER(payload)->chain_next;
        if (next == 0) break;
        payload = NODE_BODY(next);
        position = next->position;
        render_state = next->sprite;
    } while (1);
    return 0;
}
