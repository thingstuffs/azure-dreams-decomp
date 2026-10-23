#include "dungeon/monster/metal/queue_projected_point_primitives.h"


/* Adds projected point primitives and draw-mode packets to the ordering table. */
s32 queue_projected_point_primitives_2(u8 *object_data, u16 *point_data)
{
    Scratch *scratch = (Scratch *)0x1F800000;
    void **global_state = ((void * *)(&g_game_work));
    GpuContext *render_state = (GpuContext *)global_state[0];
    Packet *first_packet = (Packet *)render_state->packetCursor;
    Packet *packet;
    s32 depth_index;
    u32 address_mask = 0x00FFFFFF;
    u32 length_mask = 0xFF000000;

    scratch->table = (u8 *)render_state + 0xB0;
    scratch->current = (u8 *)first_packet;
    for (;;) {
        scratch->in0 = point_data[1];
        packet = (Packet *)scratch->current;
        scratch->in1 = point_data[3];
        scratch->in2 = point_data[5];

        scratch->current = (u8 *)packet + 0xC;
        depth_index = RotTransPers(&scratch->in0, (u8 *)packet + 8,
                              &scratch->out0, &scratch->out1);
        scratch->index = depth_index;

        if ((u32)depth_index < 480U) {
            u16 tpage;
            Packet *mode_packet;
            u8 r;
            u8 g;
            u8 b;

            packet->data.link = *(u32 *)(object_data + 8);
            packet->code = 2;
            r = packet->data.color.r;
            g = packet->data.color.g;
            b = packet->data.color.b;
            packet->data.color.r = r;
            packet->data.color.g = g;
            packet->data.color.b = b;
            packet->data.color.command = 106;

            *(u32 *)packet = (*(u32 *)packet & length_mask) |
                          (((u32 *)scratch->table)[scratch->index] & address_mask);
            ((u32 *)scratch->table)[scratch->index] =
                                    (((u32 *)scratch->table)[scratch->index] & length_mask) |
                                    ((u32)packet & address_mask);

            mode_packet = (Packet *)scratch->current;
            scratch->current = (u8 *)mode_packet + 0xC;
            tpage = (u16)GetTPage(0, 1, 0, 0);
            SetDrawMode(mode_packet, 0, 0, tpage, 0);

            *(u32 *)mode_packet = (*(u32 *)mode_packet & length_mask) |
                          (((u32 *)scratch->table)[scratch->index] & address_mask);
            mode_packet = (Packet *)((u32)mode_packet & address_mask);
            ((u32 *)scratch->table)[scratch->index] =
                                    (((u32 *)scratch->table)[scratch->index] & length_mask) |
                                    (u32)mode_packet;
        }

        {
            u8 *next_object = *(u8 **)(object_data - 8);

            if (next_object == 0)
                break;
            object_data = next_object + 0x20;
            point_data = (u16 *)*(u8 **)(next_object + 8);
        }
    }

    ((GpuContext *)global_state[0])->packetCursor = scratch->current;
    return 0;
}
