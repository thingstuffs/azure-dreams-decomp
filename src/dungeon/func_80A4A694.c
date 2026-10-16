#include "modules/dungeon_resource06_slot0.h"

s32 dungeonAppendLinkedShadedPointPackets(u8 *node, void *vertex_arg)
{
    u8 **state_ptr;
    u8 *scratch;
    register u8 *state;
    register u8 *final_state;
    register u8 *packet_end;
    register u8 *packet;
    u8 *mode_packet;
    u8 *vertex;
    void *previous;
    u32 depth_index;
    u16 vertex_x;

    vertex = vertex_arg;
    state_ptr = (u8 **)((u8 *)(&gameWork));
    state = *(u8 **)((u8 *)(&gameWork));
    scratch = (u8 *)0x1F800000;

    *(u8 * *)(scratch + 0x18) = ((GpuContext *)state)->packetCursor;
    ((R06_80173E94_S_80173E94_1 *)scratch)->unk_20.p = state + 0xB0;

    do {
        vertex_x = ((R06_80173E94_S_80173E94_2 *)vertex)->unk_02;
        packet = *(u8 * *)(scratch + 0x18);
        ((R06_80173E94_S_80173E94_1 *)scratch)->unk_00 = vertex_x;
        ((R06_80173E94_S_80173E94_1 *)scratch)->unk_02 = ((R06_80173E94_S_80173E94_2 *)vertex)->unk_06;
        ((R06_80173E94_S_80173E94_1 *)scratch)->unk_04 = ((R06_80173E94_S_80173E94_2 *)vertex)->unk_0A;
        *(u8 * *)(scratch + 0x18) = packet + 0xC;

        depth_index = func_80065420(scratch, packet + 8, scratch + 0x90,
                             scratch + 0x94);
        ((R06_80173E94_S_80173E94_1 *)scratch)->unk_C0 = depth_index;

        if (depth_index < 0x1E0) {
            s32 shade_or_page;
            s32 pixel_mode;
            s32 blend_mode;
            s32 page_x;
            s32 tile_code;

            ((R06_80173E94_S_80173E94_3 *)packet)->unk_04.at00.v = ((R06_80173E94_S_80173E94_4 *)node)->unk_08;
            shade_or_page = ((R06_80173E94_S_80173E94_3 *)packet)->unk_04.at00u.v * ((R06_80173E94_S_80173E94_4 *)node)->unk_32;
            if (shade_or_page < 0) {
                shade_or_page += 0xFF;
            }
            ((R06_80173E94_S_80173E94_3 *)packet)->unk_04.at00u.v = shade_or_page >> 8;

            shade_or_page = ((R06_80173E94_S_80173E94_3 *)packet)->unk_04.at01.v * ((R06_80173E94_S_80173E94_4 *)node)->unk_32;
            if (shade_or_page < 0) {
                shade_or_page += 0xFF;
            }
            ((R06_80173E94_S_80173E94_3 *)packet)->unk_04.at01.v = shade_or_page >> 8;

            shade_or_page = ((R06_80173E94_S_80173E94_3 *)packet)->unk_04.at02.v * ((R06_80173E94_S_80173E94_4 *)node)->unk_32;
            if (shade_or_page < 0) {
                shade_or_page += 0xFF;
                pixel_mode = 0;
            } else {
                pixel_mode = 0;
            }
            blend_mode = 1;
            ((R06_80173E94_S_80173E94_3 *)packet)->unk_04.at02.v = shade_or_page >> 8;
            ((R06_80173E94_S_80173E94_3 *)packet)->unk_00.at03.v = 2;
            tile_code = 0x6A;
            page_x = pixel_mode;
            ((R06_80173E94_S_80173E94_3 *)packet)->unk_04.at03.v = tile_code;

            ((R06_80173E94_OrderingTag *)packet)->addr =
                ((R06_80173E94_OrderingTag *)(((R06_80173E94_S_80173E94_1 *)scratch)->unk_20.p2
                    + ((R06_80173E94_S_80173E94_1 *)scratch)->unk_C0))->addr;
            {
                u32 *ot_entry;
                u32 ot_tag;
                u32 packet_addr;

                ot_entry = (u32 *)(((R06_80173E94_S_80173E94_1 *)scratch)->unk_C0 << 2);
                ot_entry = (u32 *)((u32)ot_entry +
                                   (u32)((R06_80173E94_S_80173E94_1 *)scratch)->unk_20.p2);
                ot_tag = *ot_entry;
                *ot_entry = ((u32)((ot_tag & 0xFF000000) | ((u32)((u32)packet & 0x00FFFFFF))));
            }

            mode_packet = *(u8 * *)(scratch + 0x18);
            ((R06_80173E94_S_80173E94_1 *)scratch)->unk_18 = mode_packet + 0xC;
            shade_or_page = func_80066460(pixel_mode, blend_mode, page_x, pixel_mode);
            func_80067F20(mode_packet, 0, 0, (u16)shade_or_page, 0);

            ((R06_80173E94_OrderingTag *)mode_packet)->addr =
                ((R06_80173E94_OrderingTag *)(((R06_80173E94_S_80173E94_1 *)scratch)->unk_20.p2
                    + ((R06_80173E94_S_80173E94_1 *)scratch)->unk_C0))->addr;
            mode_packet = (u8 *)((u32)mode_packet & 0x00FFFFFF);
            (*(u32 *)((u8 *)(((R06_80173E94_S_80173E94_1 *)scratch)->unk_20.p2) + ((R06_80173E94_S_80173E94_1 *)scratch)->unk_C0 * 4)) =
                ((*(u32 *)((u8 *)(((R06_80173E94_S_80173E94_1 *)scratch)->unk_20.p2)
                    + ((R06_80173E94_S_80173E94_1 *)scratch)->unk_C0 * 4)) & 0xFF000000) |
                (u32)mode_packet;
        }

        previous = ((R06_80173E94_S_80173E94_4_pre *)node)[-1].unk_00;
        node = (u8 *)previous + 0x20;
        if (previous == 0) {
            break;
        }
        vertex = ((R06_80173E94_S_80173E94_5 *)previous)->unk_08;
    } while (1);

    final_state = *state_ptr;
    packet_end = ((R06_80173E94_S_80173E94_1 *)scratch)->unk_18;
    ((GpuContext *)final_state)->packetCursor = packet_end;
    return 0;
}
