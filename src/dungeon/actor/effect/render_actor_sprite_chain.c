#include "shared/entity.h"
#include "engine/graphics/sprite_scratch.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "engine/graphics.h"
#include "dungeon/actor/effect.h"

/* Walk linked entries, set the vertex y offset, and project entries with bit 0x80 clear. */
s32 render_actor_sprite_chain(void *initial_state, ObjectPosition *context, SpriteFrameState *entry)
{
    void *state = initial_state;
    ObjectNodeHeader *next;
    SpriteQuadScratch *scratch = SPRITE_SCRATCH;

    for (;;) {
        scratch->vertex_y_offset = *(s16 *)((u8 *)state + 8);
        if (!(entry->flags & 0x80)) {
            project_sprite_commands(state, context, entry, entry->depth_bias);
        }

        next = NODE_HEADER(state)->chain_next;
        if (next != 0) {
            state = NODE_BODY(next);
            context = next->position;
            entry = next->sprite;
            continue;
        }
        return 0;
    }
}
