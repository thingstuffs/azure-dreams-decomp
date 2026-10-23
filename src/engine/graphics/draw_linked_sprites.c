#include "common.h"
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
    u16 *scratch;

    payload = first_payload;
    coords = first_coords;
    record = first_record;
    scratch = (u16 *)0x1F800000;

    while (1) {
        if (!(record->flags & 0x80)) {
            scratch[0] = *(u16 *)&coords->x.w.i;
            scratch[1] = *(u16 *)&coords->y.w.i;
            draw_sprite_parts(payload, record, (s16)(*(u16 *)&coords->z.w.i + *(u16 *)&record->depth_bias));
        }

        next_node = ((ObjectNodeHeader *)payload)[-1].chain_next;
        payload = (s8 *)next_node + 0x20;
        if (next_node == 0) {
            break;
        }
        coords = next_node->position;
        record = next_node->sprite;
    }

    return 0;
}
