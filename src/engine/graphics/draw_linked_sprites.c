#include "common.h"
#include "engine/graphics/sprite_scratch.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#include "engine/graphics.h"


/* Process linked entries with flag 0x80 clear using their coordinates and combined offset. */
s32 draw_linked_sprites(void *first_payload, ObjectPosition *first_coords, SpriteFrameState *first_record) {
    void *payload;
    ObjectPosition *coords;
    SpriteFrameState *record;
    ObjectNodeHeader *next_node;
    SpriteQuadScratch *scratch;

    payload = first_payload;
    coords = first_coords;
    record = first_record;
    scratch = SPRITE_SCRATCH;

    while (1) {
        if (!(record->flags & 0x80)) {
            scratch->position.vx = (coords->x).unsigned_parts.integer;
            scratch->position.vy = *(u16 *)&coords->y.w.i;
            draw_sprite_parts(payload, record, (s16)((coords->z).unsigned_parts.integer + ((u16)(record->depth_bias))));
        }

        next_node = NODE_HEADER(payload)->chain_next;
        payload = NODE_BODY(next_node);
        if (next_node == 0) {
            break;
        }
        coords = next_node->position;
        record = next_node->sprite;
    }

    return 0;
}
