#include "modules/dungeon_resource12_slot0.h"

void transform_and_queue_line_packets(R12_80174618_S_80174618_4 *endpoints, R12_80174618_S_80174618_1 *position, void *render_params, s16 depth_bias)
{
    u8 *line_packet;
    u8 *scratch = (u8 *)0x1F800000;
    u8 *draw_packet;
    GameWork *work_base;
    u8 *context;
    u8 *screen_start;
    u8 *screen_end;
    u8 *start_vertex;
    u8 *depth_cue;
    u8 *transform_flags;
    u16 flags;
    u16 field_value;
    s32 color_word;
    u16 end_z;
    s32 depth_index;
    R12_80174618_MATRIX matrix;
    R12_80174618_EMPTY_ARG no_arg;

    context = (u8 *)&g_game_work;
    ((R12_80174618_S_80174618_0 *)scratch)->unk_24.s = *(u8 **)context + 0xB0;
    ((R12_80174618_S_80174618_0 *)scratch)->unk_88 = position->unk_02;
    ((R12_80174618_S_80174618_0 *)scratch)->unk_8C = position->unk_06;
    ((R12_80174618_S_80174618_0 *)scratch)->unk_90 = position->unk_0A;
    ((R12_80174618_S_80174618_2 *)render_params)->unk_14 |= 0x8000;

    func_800649A0();

    ((R12_80174618_S_80174618_0 *)scratch)->unk_3C = 0x2000;
    ((R12_80174618_S_80174618_0 *)scratch)->unk_38 = 0x2000;
    ((R12_80174618_S_80174618_0 *)scratch)->unk_34 = 0x2000;
    ((R12_80174618_S_80174618_0 *)scratch)->unk_A4 = ((R12_80174618_S_80174618_2 *)render_params)->unk_16;
    ((R12_80174618_S_80174618_0 *)scratch)->unk_A8 = ((R12_80174618_S_80174618_2 *)render_params)->unk_1A;
    ((R12_80174618_S_80174618_0 *)scratch)->unk_A6 = ((R12_80174618_S_80174618_2 *)render_params)->unk_18;
    func_80065820(scratch + 0xA4, scratch + 0x74);
    func_80064AE0(&matrix);
    func_80064840(&matrix, scratch + 0x74, scratch + 0x54);
    func_80064BC0(scratch + 0x54, scratch + 0x34);
    func_80064D80(scratch + 0x54);
    func_80064CF0(scratch + 0x54);

    depth_cue = scratch + 0xD0;
    transform_flags = scratch + 0xD4;
    start_vertex = scratch + 0xB0;

    field_value = ((R12_80174618_S_80174618_2 *)render_params)->unk_14;
    context = *(u8 **)context;
    ((R12_80174618_S_80174618_0 *)scratch)->unk_28 = field_value;
    line_packet = ((GpuContext *)context)->packetCursor;
    ((GpuContext *)context)->packetCursor = line_packet + 0x10;

    field_value = endpoints->unk_64;
    ((R12_80174618_S_80174618_0 *)scratch)->unk_C0 = field_value;
    ((R12_80174618_S_80174618_0 *)scratch)->unk_B0 = field_value;
    field_value = endpoints->unk_6A;
    ((R12_80174618_S_80174618_0 *)scratch)->unk_C8 = field_value;
    ((R12_80174618_S_80174618_0 *)scratch)->unk_B8 = field_value;
    field_value = endpoints->unk_66;
    ((R12_80174618_S_80174618_0 *)scratch)->unk_C2 = field_value;
    ((R12_80174618_S_80174618_0 *)scratch)->unk_B2 = field_value;
    field_value = endpoints->unk_6C;
    ((R12_80174618_S_80174618_0 *)scratch)->unk_CA = field_value;
    ((R12_80174618_S_80174618_0 *)scratch)->unk_BA = field_value;
    field_value = endpoints->unk_68;
    ((R12_80174618_S_80174618_0 *)scratch)->unk_C4 = field_value;
    ((R12_80174618_S_80174618_0 *)scratch)->unk_B4 = field_value;
    end_z = endpoints->unk_6E;
    screen_start = line_packet + 8;
    screen_end = line_packet + 0xC;
    work_base = &g_game_work;
    depth_index = func_80065590(start_vertex, scratch + 0xB8,
                          scratch + 0xC0, scratch + 0xC8,
                          screen_start, screen_end,
                          screen_start, screen_end,
                          depth_cue, transform_flags,
                          (((R12_80174618_S_80174618_0 *)scratch)->unk_CC = end_z,
                           ((R12_80174618_S_80174618_0 *)scratch)->unk_BC = end_z,
                           no_arg));
    depth_index = depth_index - depth_bias - 6;
    ((R12_80174618_S_80174618_0 *)scratch)->unk_100 = depth_index;
    flags = ((R12_80174618_S_80174618_0 *)scratch)->unk_28;

    if (flags & 8) {
        u8 color_code;
        if (flags & 4) {
            color_code = ((R12_80174618_S_80174618_2 *)render_params)->unk_0C.at03.v | 2;
        } else {
            color_code = ((R12_80174618_S_80174618_2 *)render_params)->unk_0C.at03.v & 0xFD;
        }
        ((R12_80174618_S_80174618_2 *)render_params)->unk_0C.at03.v = color_code;
    }

    color_word = ((R12_80174618_S_80174618_2 *)render_params)->unk_0C.at00.v;
    ((R12_80174618_S_80174618_5 *)line_packet)->unk_00.at03.v = 3;
    ((R12_80174618_S_80174618_5 *)line_packet)->unk_04.at00.v = color_word;
    ((R12_80174618_S_80174618_5 *)line_packet)->unk_04.at03.v = 0x40;
    flags = ((R12_80174618_S_80174618_0 *)scratch)->unk_28;
    if (flags & 8) {
        s32 line_code = flags & 4;
        if (line_code) {
            line_code = 0x42;
        } else {
            line_code = 0x40;
        }
        ((R12_80174618_S_80174618_5 *)line_packet)->unk_04.at03.v = line_code;
    }

    {
        u8 *draw_context;
        ((R12_80174618_P_TAG *)line_packet)->addr = ((R12_80174618_P_TAG *)&((R12_80174618_S_80174618_0 *)scratch)->unk_24.u[((R12_80174618_S_80174618_0 *)scratch)->unk_100])->addr;
        ((R12_80174618_P_TAG *)&((R12_80174618_S_80174618_0 *)scratch)->unk_24.u[((R12_80174618_S_80174618_0 *)scratch)->unk_100])->addr = (u32)line_packet;

        draw_context = work_base->unk_000;
        draw_packet = ((GpuContext *)draw_context)->packetCursor;
        ((GpuContext *)draw_context)->packetCursor = draw_packet + 0xC;
        func_80067F20(draw_packet, 0, 0, (u16)func_80066460(0, 1, 0, 0), 0);

        ((R12_80174618_P_TAG *)draw_packet)->addr = ((R12_80174618_P_TAG *)&((R12_80174618_S_80174618_0 *)scratch)->unk_24.u[((R12_80174618_S_80174618_0 *)scratch)->unk_100])->addr;
        ((R12_80174618_P_TAG *)&((R12_80174618_S_80174618_0 *)scratch)->unk_24.u[((R12_80174618_S_80174618_0 *)scratch)->unk_100])->addr = (u32)draw_packet;

        func_80064A40();
    }
}
