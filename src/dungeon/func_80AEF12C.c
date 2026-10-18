#include "modules/dungeon_resource10_slot0.h"

s32 func_8017092C(u8 *node_data, u16 *position)
{
    R10_8017092C_Scratch *scratch = (R10_8017092C_Scratch *)0x1F800000;
    void **global_state = ((void * *)(&g_game_work));
    GpuContext *render_state = (GpuContext *)global_state[0];
    R10_8017092C_Packet *first_packet = (R10_8017092C_Packet *)render_state->packetCursor;
    R10_8017092C_Packet *packet;
    R10_8017092C_Packet *mode_packet;
    s32 depth_index;
    u32 addr_mask = 0x00FFFFFF;
    u32 length_mask = 0xFF000000;

    scratch->table = (u8 *)render_state + 0xB0;
    scratch->current = (u8 *)first_packet;
    for (;;) {
        scratch->in0 = position[1];
        packet = (R10_8017092C_Packet *)scratch->current;
        scratch->in1 = position[3];
        scratch->in2 = position[5];

        scratch->current = (u8 *)packet + 0xC;
        depth_index = func_80065420(&scratch->in0, (u8 *)packet + 8,
                              &scratch->out0, &scratch->out1);
        scratch->index = depth_index;

        if ((u32)depth_index < 480U) {
            u16 tpage;
            u8 r;
            u8 g;
            u8 b;

            packet->data.link = *(u32 *)(node_data + 8);
            packet->code = 2;
            r = packet->data.color.r;
            g = packet->data.color.g;
            b = packet->data.color.b;
            packet->data.color.r = r;
            packet->data.color.g = g;
            packet->data.color.b = b;
            packet->data.color.command = 106;

            *(u32 *)packet = (*(u32 *)packet & length_mask) |
                          (((u32 *)scratch->table)[scratch->index] & addr_mask);
            ((u32 *)scratch->table)[scratch->index] =
                                    (((u32 *)scratch->table)[scratch->index] & length_mask) |
                                    ((u32)packet & addr_mask);

            mode_packet = (R10_8017092C_Packet *)scratch->current;
            scratch->current = (u8 *)mode_packet + 0xC;
            tpage = (u16)func_80066460(0, 1, 0, 0);
            func_80067F20(mode_packet, 0, 0,(u16)(tpage), 0);

            *(u32 *)mode_packet = (*(u32 *)mode_packet & length_mask) |
                          (((u32 *)scratch->table)[scratch->index] & addr_mask);
            mode_packet = (R10_8017092C_Packet *)((u32)mode_packet & addr_mask);
            ((u32 *)scratch->table)[scratch->index] =
                                    (((u32 *)scratch->table)[scratch->index] & length_mask) |
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

    ((GpuContext *)global_state[0])->packetCursor = scratch->current;
    return 0;
}

