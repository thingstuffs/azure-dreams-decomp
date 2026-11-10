#include "common.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"

#include "engine/entity.h"
#include "engine/graphics.h"
#include "sdk/libgte.h"
#include "shared/scratchpad.h"

/* Projects coordinates and processes linked entries whose 0x80 flag is clear. */
s32 project_and_draw_sprite_node_chain(u8 *first_data, ObjectPosition *first_coords, SpriteFrameState *first_entry)
{
    u8 *node_data = first_data;
    void *coords = first_coords;
    SpriteFrameState *entry = first_entry;
    ScratchPad *scratch = (ScratchPad *)0x1F800000;
    ObjectNodeHeader *next_node;

    for (;;) {
        if (!(entry->flags & 0x80)) {
            scratch->h[0x70 / 2] = *(u16 *)((u8 *)coords + 2);
            scratch->h[0x72 / 2] = *(u16 *)((u8 *)coords + 6);
            scratch->h[0x74 / 2] = *(u16 *)((u8 *)coords + 0xA);
            RotTransPers(&scratch->h[0x70 / 2], &scratch->sw[0], &scratch->sw[0x90 / 4], &scratch->sw[0x94 / 4]);
            draw_sprite_parts(node_data, entry, entry->depth_bias);
            if (is_frame_packet_arena_overflowed(*(u32 *)((u8 *)g_game_work.draw_buffer + 0x8D0))) {
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
