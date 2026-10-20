#include "modules/dungeon_ovl_cb3000.h"

void project_visible_effect_quad(void *quad, void *position, void *render_info, s16 depth_bias)
{
    u8 *scratch = (u8 *)0x1F800000;
    u8 *packet;
    u8 *texture;
    s32 ot_index;
    u16 render_flags;
    u8 texture_flags;
    GameWork *render_state_ptr = &g_game_work;
    CB_80173E40_MATRIX current_matrix;

    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_24.p = *(u8 **)((u8 *)(&g_game_work)) + 0xB0;
    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_88 = ((CB_80173E40_S_80173E40_1 *)position)->unk_02;
    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_8C = ((CB_80173E40_S_80173E40_1 *)position)->unk_06;
    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_90 = ((CB_80173E40_S_80173E40_1 *)position)->unk_0A;
    ((CB_80173E40_S_80173E40_2 *)render_info)->unk_14 |= 0x8000;

    func_800649A0();

    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_3C = 0x2000;
    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_38 = 0x2000;
    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_34 = 0x2000;
    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_A4 = ((CB_80173E40_S_80173E40_2 *)render_info)->unk_16;
    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_A8 = ((CB_80173E40_S_80173E40_2 *)render_info)->unk_1A;
    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_A6 = ((CB_80173E40_S_80173E40_2 *)render_info)->unk_18;
    func_80065820(scratch + 0xA4, scratch + 0x74);
    func_80064AE0(&current_matrix);
    func_80064840(&current_matrix, scratch + 0x74, scratch + 0x54);
    func_80064BC0(scratch + 0x54, scratch + 0x34);
    func_80064D80(scratch + 0x54);
    func_80064CF0(scratch + 0x54);

    texture = (*(u8 * *)((u8 *)render_info + 8));
    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_28 = ((CB_80173E40_S_80173E40_2 *)render_info)->unk_14;
    packet = ((CB_80173E40_S_80173E40_3 *)(g_game_work.draw_buffer))->unk_8D0;
    ((CB_80173E40_S_80173E40_3 *)(g_game_work.draw_buffer))->unk_8D0 = packet + 0xC;
    func_80067F20(packet, 0, 0, func_80066460(0, 0, 0, 0), 0);

    (*(u32 *)((u8 *)packet + 0)) = (((CB_80173E40_S_80173E40_4 *)packet)->unk_00 & 0xFF000000) |
        (((CB_80173E40_S_80173E40_3 *)(g_game_work.draw_buffer))->unk_B0 & 0x00FFFFFF);
    (*(u32 *)((u8 *)(g_game_work.draw_buffer) + 0xB0)) =
        (((CB_80173E40_S_80173E40_3 *)(g_game_work.draw_buffer))->unk_B0 & 0xFF000000) |
        ((u32)packet & 0x00FFFFFF);

    {
        u8 *render_state = g_game_work.draw_buffer;
        packet = ((CB_80173E40_S_80173E40_5 *)render_state)->unk_8D0;
        ((CB_80173E40_S_80173E40_5 *)render_state)->unk_8D0 = packet + 0x24;
    }

    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_B0 = ((CB_80173E40_S_80173E40_6 *)quad)->unk_44;
    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_B8 = ((CB_80173E40_S_80173E40_6 *)quad)->unk_4A;
    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_C0 = ((CB_80173E40_S_80173E40_6 *)quad)->unk_50;
    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_C8 = ((CB_80173E40_S_80173E40_6 *)quad)->unk_56;
    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_B2 = ((CB_80173E40_S_80173E40_6 *)quad)->unk_46;
    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_BA = ((CB_80173E40_S_80173E40_6 *)quad)->unk_4C;
    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_C2 = ((CB_80173E40_S_80173E40_6 *)quad)->unk_52;
    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_CA = ((CB_80173E40_S_80173E40_6 *)quad)->unk_58;
    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_B4 = ((CB_80173E40_S_80173E40_6 *)quad)->unk_48;
    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_BC = ((CB_80173E40_S_80173E40_6 *)quad)->unk_4E;
    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_C4 = ((CB_80173E40_S_80173E40_6 *)quad)->unk_54;
    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_CC = ((CB_80173E40_S_80173E40_6 *)quad)->unk_5A;

    ot_index = func_80065590(scratch + 0xB0, scratch + 0xB8,
                             scratch + 0xC0, scratch + 0xC8,
                             packet + 8, packet + 0x10,
                             packet + 0x18, packet + 0x20,
                             scratch + 0xD0, scratch + 0xD4) - depth_bias - 6;
    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_100 = ot_index;

    if ((u32)ot_index < 0x1E0) {
        if ((((u16)(((CB_80173E40_S_80173E40_4 *)packet)->unk_08 + 0x20) < 0x181) &&
             ((u16)(((CB_80173E40_S_80173E40_4 *)packet)->unk_0A + 0x20) < 0x121)) |
            (((u16)(((CB_80173E40_S_80173E40_4 *)packet)->unk_10 + 0x20) < 0x181) &&
             ((u16)(((CB_80173E40_S_80173E40_4 *)packet)->unk_12 + 0x20) < 0x121)) |
            (((u16)(((CB_80173E40_S_80173E40_4 *)packet)->unk_18 + 0x20) < 0x181) &&
             ((u16)(((CB_80173E40_S_80173E40_4 *)packet)->unk_1A + 0x20) < 0x121)) |
            (((u16)(((CB_80173E40_S_80173E40_4 *)packet)->unk_20 + 0x20) < 0x181) &&
             ((u16)(((CB_80173E40_S_80173E40_4 *)packet)->unk_22 + 0x20) < 0x121))) {
            ((CB_80173E40_S_80173E40_2 *)render_info)->unk_14 &= 0x7FFF;
            texture_flags = texture[1];
            ((CB_80173E40_S_80173E40_2 *)render_info)->unk_0F = texture_flags;
            render_flags = ((CB_80173E40_S_80173E40_0 *)scratch)->unk_28;
            if (render_flags & 8) {
                ((CB_80173E40_S_80173E40_2 *)render_info)->unk_0F = (render_flags & 4) ?
                    (texture_flags | 2) : (texture_flags & 0xFD);
            }

            ((CB_80173E40_S_80173E40_4 *)packet)->unk_04.at00.v = ((CB_80173E40_S_80173E40_6 *)quad)->unk_04;
            ((CB_80173E40_S_80173E40_4 *)packet)->unk_0C = ((CB_80173E40_S_80173E40_6 *)quad)->unk_08;
            ((CB_80173E40_S_80173E40_4 *)packet)->unk_14 = ((CB_80173E40_S_80173E40_6 *)quad)->unk_0C;
            ((CB_80173E40_S_80173E40_4 *)packet)->unk_1C = ((CB_80173E40_S_80173E40_6 *)quad)->unk_10;
            func_80066708(packet);
            ((CB_80173E40_S_80173E40_4 *)packet)->unk_04.at03.v |= 2;

            ((CB_80173E40_S_80173E40_4 *)packet)->unk_00 = (((CB_80173E40_S_80173E40_4 *)packet)->unk_00 & 0xFF000000) |
                ((*(u32 *)((u8 *)(((CB_80173E40_S_80173E40_0 *)scratch)->unk_24.p2)
                    + ((CB_80173E40_S_80173E40_0 *)scratch)->unk_100 * 4)) & 0x00FFFFFF);
            (*(u32 *)((u8 *)(((CB_80173E40_S_80173E40_0 *)scratch)->unk_24.p2) + ((CB_80173E40_S_80173E40_0 *)scratch)->unk_100 * 4)) =
                ((*(u32 *)((u8 *)(((CB_80173E40_S_80173E40_0 *)scratch)->unk_24.p2)
                    + ((CB_80173E40_S_80173E40_0 *)scratch)->unk_100 * 4)) & 0xFF000000) |
                ((u32)packet & 0x00FFFFFF);

            packet = ((CB_80173E40_S_80173E40_7 *)(render_state_ptr->draw_buffer))->unk_8D0;
            ((CB_80173E40_S_80173E40_7 *)(render_state_ptr->draw_buffer))->unk_8D0 = packet + 0xC;
            func_80067F20(packet, 0, 0, func_80066460(0, 1, 0, 0), 0);
            ((CB_80173E40_S_80173E40_4 *)packet)->unk_00 = (((CB_80173E40_S_80173E40_4 *)packet)->unk_00 & 0xFF000000) |
                ((*(u32 *)((u8 *)(((CB_80173E40_S_80173E40_0 *)scratch)->unk_24.p2)
                    + ((CB_80173E40_S_80173E40_0 *)scratch)->unk_100 * 4)) & 0x00FFFFFF);
            (*(u32 *)((u8 *)(((CB_80173E40_S_80173E40_0 *)scratch)->unk_24.p2) + ((CB_80173E40_S_80173E40_0 *)scratch)->unk_100 * 4)) =
                ((*(u32 *)((u8 *)(((CB_80173E40_S_80173E40_0 *)scratch)->unk_24.p2)
                    + ((CB_80173E40_S_80173E40_0 *)scratch)->unk_100 * 4)) & 0xFF000000) |
                ((u32)packet & 0x00FFFFFF);
        }
    }

    func_80064A40();
}
