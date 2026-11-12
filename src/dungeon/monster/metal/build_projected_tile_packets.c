#include "dungeon/monster/metal/build_projected_tile_packets.h"


/* Builds and links tile and draw-mode packets for a chain of projected positions. */
s32 build_projected_tile_packets(u8 *node_data, u16 *position)
{
    PointTileScratch *scratch = (PointTileScratch *)0x1F800000;
    void **globals = ((void * *)(&g_game_work));
    GpuContext *render_state = globals[0];
    TILE_1 *first_packet = render_state->packetCursor;
    TILE_1 *packet;
    s32 depth_index;
    u32 address_mask = 0x00FFFFFF;
    u32 length_mask = 0xFF000000;

    scratch->ordering_table = (u32 *)&render_state->orderTag;
    scratch->packet_cursor = first_packet;
    for (;;) {
        scratch->position.vx = position[1];
        packet = scratch->packet_cursor;
        scratch->position.vy = position[3];
        scratch->position.vz = position[5];

        scratch->packet_cursor = packet + 1;
        depth_index = RotTransPers(&scratch->position, (s32 *)&packet->x0,
                              &scratch->depth_cue, &scratch->gte_flag);
        scratch->ot_index = depth_index;

        if ((u32)depth_index < 480U) {
            u16 tpage;
            DR_MODE *mode_packet;
            u8 r;
            u8 g;
            u8 b;

            /* BYTES: retail copies the tile colour word (r0, g0, b0 and code) with one lw/sw; member copies compile to four lbu/sb */
            *(u32 *)&packet->r0 = *(u32 *)(node_data + 8);
            ((GpuLinkTag *)&packet->tag)->len = 2;
            r = packet->r0;
            g = packet->g0;
            b = packet->b0;
            packet->r0 = r;
            packet->g0 = g;
            packet->b0 = b;
            packet->code = 106;

            packet->tag = (packet->tag & length_mask) |
                          (scratch->ordering_table[scratch->ot_index] & address_mask);
            scratch->ordering_table[scratch->ot_index] =
                                    (scratch->ordering_table[scratch->ot_index] & length_mask) |
                                    ((u32)packet & address_mask);

            mode_packet = scratch->packet_cursor;
            scratch->packet_cursor = mode_packet + 1;
            tpage = (u16)GetTPage(0, 1, 0, 0);
            SetDrawMode(mode_packet, 0, 0, tpage, 0);

            mode_packet->tag = (mode_packet->tag & length_mask) |
                          (scratch->ordering_table[scratch->ot_index] & address_mask);
            mode_packet = (DR_MODE *)((u32)mode_packet & address_mask);
            scratch->ordering_table[scratch->ot_index] =
                                    (scratch->ordering_table[scratch->ot_index] & length_mask) |
                                    (u32)mode_packet;
        }

        {
            u8 *next_node = *(u8 **)(node_data - 8);

            if (next_node == 0)
                break;
            node_data = next_node + 0x20;
            position = (u16 *)*(u8 **)(next_node + 8);
        }
    }

    ((GpuContext *)globals[0])->packetCursor = scratch->packet_cursor;
    return 0;
}
