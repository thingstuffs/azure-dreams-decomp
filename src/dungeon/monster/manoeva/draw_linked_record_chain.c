#include "common.h"
#include "engine/graphics/sprite_scratch.h"
#include "dungeon/monster/manoeva.h"

#include "engine/graphics.h"

/* Clears the scratchpad counter and processes each record in the linked chain. */
s32 draw_linked_record_chain(u8 *record_data, ObjectPosition *position, SpriteFrameState *sprite) {
    SPRITE_SCRATCH->vertex_y_offset = 0;
    for (;;) {
        ObjectNodeHeader *next;

        project_sprite_commands(record_data, position, sprite, -0x10);
        next = NODE_HEADER(record_data)->chain_next;
        if (next == 0) {
            return 0;
        }
        record_data = NODE_BODY(next);
        position = next->position;
        sprite = next->sprite;
    }
}

/* The backedge returns to the
 * local loop. The loop tests the
 * current position before advancing it. */
