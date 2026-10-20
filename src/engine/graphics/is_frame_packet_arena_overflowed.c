#include "common.h"
#include "shared/game_work.h"

#include "common.h"

typedef struct {
    u8 pad00[6];
    s16 unk06;
    u8 pad08[0x14 - 0x8];
    u16 unk14;
} Entry80044C54;

extern void RotTransPers(void *a0, void *a1, void *a2, void *a3);
extern void draw_sprite_parts(void *unused, u8 *sprite, s32 ot_depth);
extern s32 is_frame_packet_arena_overflowed(u32 a0);

/* Projects coordinates and processes linked entries whose 0x80 flag is clear. */
s32 func_80044C54(u8 *first_data, void *first_coords, Entry80044C54 *first_entry)
{
    u8 *node_data = first_data;
    void *coords = first_coords;
    Entry80044C54 *entry = first_entry;
    u8 *scratch = (u8 *)0x1F800000;
    void *next_node;

    for (;;) {
        if (!(entry->unk14 & 0x80)) {
            *(u16 *)(scratch + 0x70) = *(u16 *)((u8 *)coords + 2);
            *(u16 *)(scratch + 0x72) = *(u16 *)((u8 *)coords + 6);
            *(u16 *)(scratch + 0x74) = *(u16 *)((u8 *)coords + 0xA);
            RotTransPers(scratch + 0x70, scratch, scratch + 0x90, scratch + 0x94);
            draw_sprite_parts(node_data, entry, entry->unk06);
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
        entry = *(Entry80044C54 **)((u8 *)next_node + 0xC);
    }
}
