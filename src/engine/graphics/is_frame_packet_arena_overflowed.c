#include "common.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/gpu_packets.h"

#include "engine/entity.h"
#include "engine/graphics.h"
#include "sdk/libgte.h"
#include "shared/scratchpad.h"
#include "engine/graphics/sprite_scratch.h"

/* Projects coordinates and processes linked entries whose 0x80 flag is clear. */
s32 project_and_draw_sprite_node_chain(u8 *first_data, ObjectPosition *first_coords, SpriteFrameState *first_entry)
{
    u8 *node_data = first_data;
    ObjectPosition *coords = first_coords;
    SpriteFrameState *entry = first_entry;
    SpriteQuadScratch *scratch = SPRITE_SCRATCH;
    ObjectNodeHeader *next_node;

    for (;;) {
        if (!(entry->flags & 0x80)) {
            scratch->vertices[0].vx = coords->x.w.i;
            scratch->vertices[0].vy = coords->y.w.i;
            scratch->vertices[0].vz = coords->z.w.i;
            RotTransPers(&scratch->vertices[0], &((ScratchPad *)scratch)->sw[0], &scratch->depth_cue, &scratch->gte_flag);
            draw_sprite_parts(node_data, entry, entry->depth_bias);
            if (is_frame_packet_arena_overflowed(g_game_work.draw_buffer->packetCursor)) {
                return 0;
            }
        }

        next_node = NODE_HEADER(node_data)->chain_next;
        if (next_node == 0) {
            return 0;
        }
        node_data = NODE_BODY(next_node);
        coords = next_node->position;
        entry = next_node->sprite;
    }
}
