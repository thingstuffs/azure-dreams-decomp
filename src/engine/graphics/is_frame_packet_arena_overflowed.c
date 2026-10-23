#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"

#include "common.h"
#include "engine/entity.h"
#include "engine/graphics.h"
#include "sdk/libgte.h"

/* Projects coordinates and processes linked entries whose 0x80 flag is clear. */
s32 project_and_draw_sprite_node_chain(u8 *first_data, void *first_coords, SpriteFrameState *first_entry)
{
    u8 *node_data = first_data;
    void *coords = first_coords;
    SpriteFrameState *entry = first_entry;
    u8 *scratch = (u8 *)0x1F800000;
    void *next_node;

    for (;;) {
        if (!(entry->flags & 0x80)) {
            *(u16 *)(scratch + 0x70) = *(u16 *)((u8 *)coords + 2);
            *(u16 *)(scratch + 0x72) = *(u16 *)((u8 *)coords + 6);
            *(u16 *)(scratch + 0x74) = *(u16 *)((u8 *)coords + 0xA);
            RotTransPers(scratch + 0x70, scratch, scratch + 0x90, scratch + 0x94);
            draw_sprite_parts(node_data, entry, entry->depth_bias);
            if (is_frame_packet_arena_overflowed(*(u32 *)((u8 *)g_game_work.draw_buffer + 0x8D0))) {
                return 0;
            }
        }

        next_node = *(void **)(node_data - 8);
        if (next_node == 0) {
            return 0;
        }
        node_data = (u8 *)next_node + 0x20;
        coords = *(void **)((u8 *)next_node + 8);
        entry = *(SpriteFrameState **)((u8 *)next_node + 0xC);
    }
}
