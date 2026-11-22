#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "engine/graphics.h"
#include "dungeon/actor/effect.h"

typedef struct {
    u8 pad[0x13C];
    s32 flag;
} Scratchpad;

/* Walk linked entries, update the scratch flag, and process entries without bit 0x80 set. */
s32 render_actor_sprite_chain(void *initial_state, ObjectPosition *context, SpriteFrameState *entry)
{
    void *state = initial_state;
    ObjectNodeHeader *next;
    Scratchpad *scratch = (Scratchpad *)0x1F800000;

    for (;;) {
        scratch->flag = *(s16 *)((u8 *)state + 8);
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
