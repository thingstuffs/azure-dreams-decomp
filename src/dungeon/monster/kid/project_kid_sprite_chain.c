#include "common.h"
#include "engine/graphics/sprite_scratch.h"

#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "engine/graphics.h"

typedef struct {
    u8 pad[0x5218];
    s16 value;
} GlobalPage;

extern s16 D_80175218[];

/* Projects visible entries in the linked sprite chain using the current transition depth adjustment. */
s32 project_kid_sprite_chain(void *initial_payload, ObjectPosition *entry_data, SpriteFrameState *entry, s32 unused)
{
    void *payload = initial_payload;
    SpriteQuadScratch *scratch = SPRITE_SCRATCH;
    ObjectNodeHeader *next_entry;

    for (;;) {
        scratch->vertex_y_offset = D_80175218[0];

        if (!(entry->flags & 0x80)) {
            project_sprite_commands(payload, entry_data, entry, entry->depth_bias);
        }

        next_entry = NODE_HEADER(payload)->chain_next;
        if (next_entry == 0) {
            return 0;
        }
        payload = NODE_BODY(next_entry);
        entry_data = next_entry->position;
        entry = next_entry->sprite;
    }
}

/* The action reads signed halfwords from the actor and stores the scratch values as full words. */
