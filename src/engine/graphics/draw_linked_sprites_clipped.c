#include "common.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/gpu_packets.h"
#include "engine/entity.h"
#include "engine/graphics.h"

/* D_80083160[0] points at a large shared-state struct; only the pointer field
 * at offset 0x8D0 is read here. */

/* Processes unflagged list entries until the list ends or a stop is requested; returns zero. */
s32 draw_linked_sprites_clipped(u8 *first_data, struct ObjectPosition *position, SpriteFrameState *value_record)
{
    u8 *link_data = first_data;
    ObjectNodeHeader *next_link;

    do {
        if (!(value_record->flags & 0x80)) {
            draw_sprite_clipped(link_data, position, value_record, value_record->depth_bias);
            if (is_frame_packet_arena_overflowed(g_game_work.draw_buffer->packetCursor)) {
                return 0;
            }
        }
        next_link = NODE_HEADER(link_data)->chain_next;
        if (next_link == 0) {
            return 0;
        }
        link_data = NODE_BODY(next_link);
        position = next_link->position;
        value_record = next_link->sprite;
    } while (1);
}
