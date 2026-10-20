#include "modules/dungeon_ovl_cc5000.h"

void func_80161E40(void *quad, void *position, void *render_info, s16 depth_bias)
{
    u8 *scratch = (u8 *)0x1F800000;
    u8 *packet;
    u8 *texture;
    s32 ot_index;
    u16 render_flags;
    u8 texture_flags;
    GameWork *render_state_ptr = &g_game_work;
    CL_CC5000_80173E40_MATRIX current_matrix;

    ((CL_CC5000_80173E40_S_80173E40_0 *)scratch)->unk_24.p = *(u8 **)((u8 *)(&g_game_work)) + 0xB0;
    ((CL_CC5000_80173E40_S_80173E40_0 *)scratch)->unk_88 = ((CL_CC5000_80173E40_S_80173E40_1 *)position)->unk_02;
    ((CL_CC5000_80173E40_S_80173E40_0 *)scratch)->unk_8C = ((CL_CC5000_80173E40_S_80173E40_1 *)position)->unk_06;
    ((CL_CC5000_80173E40_S_80173E40_0 *)scratch)->unk_90 = ((CL_CC5000_80173E40_S_80173E40_1 *)position)->unk_0A;
    ((CL_CC5000_80173E40_S_80173E40_2 *)render_info)->unk_14 |= 0x8000;

    func_800649A0();

    ((CL_CC5000_80173E40_S_80173E40_0 *)scratch)->unk_3C = 0x2000;
    ((CL_CC5000_80173E40_S_80173E40_0 *)scratch)->unk_38 = 0x2000;
    ((CL_CC5000_80173E40_S_80173E40_0 *)scratch)->unk_34 = 0x2000;
    ((CL_CC5000_80173E40_S_80173E40_0 *)scratch)->unk_A4 = ((CL_CC5000_80173E40_S_80173E40_2 *)render_info)->unk_16;
    ((CL_CC5000_80173E40_S_80173E40_0 *)scratch)->unk_A8 = ((CL_CC5000_80173E40_S_80173E40_2 *)render_info)->unk_1A;
    ((CL_CC5000_80173E40_S_80173E40_0 *)scratch)->unk_A6 = ((CL_CC5000_80173E40_S_80173E40_2 *)render_info)->unk_18;
    func_80065820(scratch + 0xA4, scratch + 0x74);
    func_80064AE0(&current_matrix);
    func_80064840(&current_matrix, scratch + 0x74, scratch + 0x54);
    func_80064BC0(scratch + 0x54, scratch + 0x34);
    func_80064D80(scratch + 0x54);
    func_80064CF0(scratch + 0x54);

    texture = (*(u8 * *)((u8 *)render_info + 8));
    ((CL_CC5000_80173E40_S_80173E40_0 *)scratch)->unk_28 = ((CL_CC5000_80173E40_S_80173E40_2 *)render_info)->unk_14;
    packet = ((CL_CC5000_80173E40_S_80173E40_3 *)(g_game_work.draw_buffer))->unk_8D0;
    ((CL_CC5000_80173E40_S_80173E40_3 *)(g_game_work.draw_buffer))->unk_8D0 = packet + 0xC;
    func_80067F20(packet, 0, 0, func_80066460(0, 0, 0, 0), 0);

    (*(u32 *)((u8 *)packet + 0)) = (((CL_CC5000_80173E40_S_80173E40_4 *)packet)->unk_00 & 0xFF000000) |
        (((CL_CC5000_80173E40_S_80173E40_3 *)(g_game_work.draw_buffer))->unk_B0 & 0x00FFFFFF);
    (*(u32 *)((u8 *)(g_game_work.draw_buffer) + 0xB0)) =
        (((CL_CC5000_80173E40_S_80173E40_3 *)(g_game_work.draw_buffer))->unk_B0 & 0xFF000000) |
        ((u32)packet & 0x00FFFFFF);

    {
        u8 *render_state = g_game_work.draw_buffer;
        packet = ((CL_CC5000_80173E40_S_80173E40_5 *)render_state)->unk_8D0;
        ((CL_CC5000_80173E40_S_80173E40_5 *)render_state)->unk_8D0 = packet + 0x24;
    }

    ((CL_CC5000_80173E40_S_80173E40_0 *)scratch)->unk_B0 = ((CL_CC5000_80173E40_S_80173E40_6 *)quad)->unk_44;
    ((CL_CC5000_80173E40_S_80173E40_0 *)scratch)->unk_B8 = ((CL_CC5000_80173E40_S_80173E40_6 *)quad)->unk_4A;
    ((CL_CC5000_80173E40_S_80173E40_0 *)scratch)->unk_C0 = ((CL_CC5000_80173E40_S_80173E40_6 *)quad)->unk_50;
    ((CL_CC5000_80173E40_S_80173E40_0 *)scratch)->unk_C8 = ((CL_CC5000_80173E40_S_80173E40_6 *)quad)->unk_56;
    ((CL_CC5000_80173E40_S_80173E40_0 *)scratch)->unk_B2 = ((CL_CC5000_80173E40_S_80173E40_6 *)quad)->unk_46;
    ((CL_CC5000_80173E40_S_80173E40_0 *)scratch)->unk_BA = ((CL_CC5000_80173E40_S_80173E40_6 *)quad)->unk_4C;
    ((CL_CC5000_80173E40_S_80173E40_0 *)scratch)->unk_C2 = ((CL_CC5000_80173E40_S_80173E40_6 *)quad)->unk_52;
    ((CL_CC5000_80173E40_S_80173E40_0 *)scratch)->unk_CA = ((CL_CC5000_80173E40_S_80173E40_6 *)quad)->unk_58;
    ((CL_CC5000_80173E40_S_80173E40_0 *)scratch)->unk_B4 = ((CL_CC5000_80173E40_S_80173E40_6 *)quad)->unk_48;
    ((CL_CC5000_80173E40_S_80173E40_0 *)scratch)->unk_BC = ((CL_CC5000_80173E40_S_80173E40_6 *)quad)->unk_4E;
    ((CL_CC5000_80173E40_S_80173E40_0 *)scratch)->unk_C4 = ((CL_CC5000_80173E40_S_80173E40_6 *)quad)->unk_54;
    ((CL_CC5000_80173E40_S_80173E40_0 *)scratch)->unk_CC = ((CL_CC5000_80173E40_S_80173E40_6 *)quad)->unk_5A;

    ot_index = func_80065590(scratch + 0xB0, scratch + 0xB8,
                             scratch + 0xC0, scratch + 0xC8,
                             packet + 8, packet + 0x10,
                             packet + 0x18, packet + 0x20,
                             scratch + 0xD0, scratch + 0xD4) - depth_bias - 6;
    ((CL_CC5000_80173E40_S_80173E40_0 *)scratch)->unk_100 = ot_index;

    if ((u32)ot_index < 0x1E0) {
        if ((((u16)(((CL_CC5000_80173E40_S_80173E40_4 *)packet)->unk_08 + 0x20) < 0x181) &&
             ((u16)(((CL_CC5000_80173E40_S_80173E40_4 *)packet)->unk_0A + 0x20) < 0x121)) |
            (((u16)(((CL_CC5000_80173E40_S_80173E40_4 *)packet)->unk_10 + 0x20) < 0x181) &&
             ((u16)(((CL_CC5000_80173E40_S_80173E40_4 *)packet)->unk_12 + 0x20) < 0x121)) |
            (((u16)(((CL_CC5000_80173E40_S_80173E40_4 *)packet)->unk_18 + 0x20) < 0x181) &&
             ((u16)(((CL_CC5000_80173E40_S_80173E40_4 *)packet)->unk_1A + 0x20) < 0x121)) |
            (((u16)(((CL_CC5000_80173E40_S_80173E40_4 *)packet)->unk_20 + 0x20) < 0x181) &&
             ((u16)(((CL_CC5000_80173E40_S_80173E40_4 *)packet)->unk_22 + 0x20) < 0x121))) {
            ((CL_CC5000_80173E40_S_80173E40_2 *)render_info)->unk_14 &= 0x7FFF;
            texture_flags = texture[1];
            ((CL_CC5000_80173E40_S_80173E40_2 *)render_info)->unk_0F = texture_flags;
            render_flags = ((CL_CC5000_80173E40_S_80173E40_0 *)scratch)->unk_28;
            if (render_flags & 8) {
                ((CL_CC5000_80173E40_S_80173E40_2 *)render_info)->unk_0F = (render_flags & 4) ?
                    (texture_flags | 2) : (texture_flags & 0xFD);
            }

            ((CL_CC5000_80173E40_S_80173E40_4 *)packet)->unk_04.at00.v = ((CL_CC5000_80173E40_S_80173E40_6 *)quad)->unk_04;
            ((CL_CC5000_80173E40_S_80173E40_4 *)packet)->unk_0C = ((CL_CC5000_80173E40_S_80173E40_6 *)quad)->unk_08;
            ((CL_CC5000_80173E40_S_80173E40_4 *)packet)->unk_14 = ((CL_CC5000_80173E40_S_80173E40_6 *)quad)->unk_0C;
            ((CL_CC5000_80173E40_S_80173E40_4 *)packet)->unk_1C = ((CL_CC5000_80173E40_S_80173E40_6 *)quad)->unk_10;
            func_80066708(packet);
            ((CL_CC5000_80173E40_S_80173E40_4 *)packet)->unk_04.at03.v |= 2;

            ((CL_CC5000_80173E40_S_80173E40_4 *)packet)->unk_00 = (((CL_CC5000_80173E40_S_80173E40_4 *)packet)->unk_00 & 0xFF000000) |
                ((*(u32 *)((u8 *)(((CL_CC5000_80173E40_S_80173E40_0 *)scratch)->unk_24.p2)
                    + ((CL_CC5000_80173E40_S_80173E40_0 *)scratch)->unk_100 * 4)) & 0x00FFFFFF);
            (*(u32 *)((u8 *)(((CL_CC5000_80173E40_S_80173E40_0 *)scratch)->unk_24.p2) + ((CL_CC5000_80173E40_S_80173E40_0 *)scratch)->unk_100 * 4)) =
                ((*(u32 *)((u8 *)(((CL_CC5000_80173E40_S_80173E40_0 *)scratch)->unk_24.p2)
                    + ((CL_CC5000_80173E40_S_80173E40_0 *)scratch)->unk_100 * 4)) & 0xFF000000) |
                ((u32)packet & 0x00FFFFFF);

            packet = ((CL_CC5000_80173E40_S_80173E40_7 *)(render_state_ptr->draw_buffer))->unk_8D0;
            ((CL_CC5000_80173E40_S_80173E40_7 *)(render_state_ptr->draw_buffer))->unk_8D0 = packet + 0xC;
            func_80067F20(packet, 0, 0, func_80066460(0, 1, 0, 0), 0);
            ((CL_CC5000_80173E40_S_80173E40_4 *)packet)->unk_00 = (((CL_CC5000_80173E40_S_80173E40_4 *)packet)->unk_00 & 0xFF000000) |
                ((*(u32 *)((u8 *)(((CL_CC5000_80173E40_S_80173E40_0 *)scratch)->unk_24.p2)
                    + ((CL_CC5000_80173E40_S_80173E40_0 *)scratch)->unk_100 * 4)) & 0x00FFFFFF);
            (*(u32 *)((u8 *)(((CL_CC5000_80173E40_S_80173E40_0 *)scratch)->unk_24.p2) + ((CL_CC5000_80173E40_S_80173E40_0 *)scratch)->unk_100 * 4)) =
                ((*(u32 *)((u8 *)(((CL_CC5000_80173E40_S_80173E40_0 *)scratch)->unk_24.p2)
                    + ((CL_CC5000_80173E40_S_80173E40_0 *)scratch)->unk_100 * 4)) & 0xFF000000) |
                ((u32)packet & 0x00FFFFFF);
        }
    }

    func_80064A40();
}
