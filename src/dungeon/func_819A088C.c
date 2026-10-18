#include "modules/dungeon_ovl_19c088c.h"

void func_8002408C(void *quad, void *position, void *render_state, s16 depth_bias)
{
    u8 *scratch = (u8 *)0x1F800000;
    u8 *packet;
    u8 *texture;
    s32 ot_index;
    u16 render_flags;
    u8 texture_flags;
    u8 **render_context_ptr = (u8 **)((u8 *)(&g_game_work));
    Row_819A088C_MATRIX base_matrix;

    ((Row_819A088C_S_819A088C_0 *)scratch)->unk_24.p = *(u8 **)((u8 *)(&g_game_work)) + 0xB0;
    ((Row_819A088C_S_819A088C_0 *)scratch)->unk_88 = ((Row_819A088C_S_819A088C_1 *)position)->unk_02;
    ((Row_819A088C_S_819A088C_0 *)scratch)->unk_8C = ((Row_819A088C_S_819A088C_1 *)position)->unk_06;
    ((Row_819A088C_S_819A088C_0 *)scratch)->unk_90 = ((Row_819A088C_S_819A088C_1 *)position)->unk_0A;
    ((Row_819A088C_S_819A088C_2 *)render_state)->unk_14 |= 0x8000;

    func_800649A0();

    ((Row_819A088C_S_819A088C_0 *)scratch)->unk_3C = 0x2000;
    ((Row_819A088C_S_819A088C_0 *)scratch)->unk_38 = 0x2000;
    ((Row_819A088C_S_819A088C_0 *)scratch)->unk_34 = 0x2000;
    ((Row_819A088C_S_819A088C_0 *)scratch)->unk_A4 = ((Row_819A088C_S_819A088C_2 *)render_state)->unk_16;
    ((Row_819A088C_S_819A088C_0 *)scratch)->unk_A8 = ((Row_819A088C_S_819A088C_2 *)render_state)->unk_1A;
    ((Row_819A088C_S_819A088C_0 *)scratch)->unk_A6 = ((Row_819A088C_S_819A088C_2 *)render_state)->unk_18;
    func_80065820(scratch + 0xA4, scratch + 0x74);
    func_80064AE0(&base_matrix);
    func_80064840(&base_matrix, scratch + 0x74, scratch + 0x54);
    func_80064BC0(scratch + 0x54, scratch + 0x34);
    func_80064D80(scratch + 0x54);
    func_80064CF0(scratch + 0x54);

    texture = (*(u8 * *)((u8 *)render_state + 8));
    ((Row_819A088C_S_819A088C_0 *)scratch)->unk_28 = ((Row_819A088C_S_819A088C_2 *)render_state)->unk_14;

    packet = ((Row_819A088C_S_819A088C_3 *)(g_game_work.unk_000))->unk_8D0;
    ((Row_819A088C_S_819A088C_3 *)(g_game_work.unk_000))->unk_8D0 = packet + 0xC;
    func_80067F20(packet, 0, 1, func_80066460(0, 0, 0, 0) & 0xFFFF, 0);
    (*(u32 *)((u8 *)packet + 0)) = (((Row_819A088C_S_819A088C_4 *)packet)->unk_00.at00.v & 0xFF000000) |
        (((Row_819A088C_S_819A088C_3 *)(g_game_work.unk_000))->unk_B0 & 0x00FFFFFF);
    (*(u32 *)((u8 *)(g_game_work.unk_000) + 0xB0)) =
        (((Row_819A088C_S_819A088C_3 *)(g_game_work.unk_000))->unk_B0 & 0xFF000000) |
        ((u32)packet & 0x00FFFFFF);

    {
        u8 *render_context;

        render_context = g_game_work.unk_000;
        packet = ((Row_819A088C_S_819A088C_5 *)render_context)->unk_8D0;
        ((Row_819A088C_S_819A088C_5 *)render_context)->unk_8D0 = packet + 0x24;
    }

    ((Row_819A088C_S_819A088C_0 *)scratch)->unk_B0 = ((Row_819A088C_S_819A088C_6 *)quad)->unk_54;
    ((Row_819A088C_S_819A088C_0 *)scratch)->unk_B8 = ((Row_819A088C_S_819A088C_6 *)quad)->unk_5A;
    ((Row_819A088C_S_819A088C_0 *)scratch)->unk_C0 = ((Row_819A088C_S_819A088C_6 *)quad)->unk_60;
    ((Row_819A088C_S_819A088C_0 *)scratch)->unk_C8 = ((Row_819A088C_S_819A088C_6 *)quad)->unk_66;
    ((Row_819A088C_S_819A088C_0 *)scratch)->unk_B2 = ((Row_819A088C_S_819A088C_6 *)quad)->unk_56;
    ((Row_819A088C_S_819A088C_0 *)scratch)->unk_BA = ((Row_819A088C_S_819A088C_6 *)quad)->unk_5C;
    ((Row_819A088C_S_819A088C_0 *)scratch)->unk_C2 = ((Row_819A088C_S_819A088C_6 *)quad)->unk_62;
    ((Row_819A088C_S_819A088C_0 *)scratch)->unk_CA = ((Row_819A088C_S_819A088C_6 *)quad)->unk_68;
    ((Row_819A088C_S_819A088C_0 *)scratch)->unk_B4 = ((Row_819A088C_S_819A088C_6 *)quad)->unk_58;
    ((Row_819A088C_S_819A088C_0 *)scratch)->unk_BC = ((Row_819A088C_S_819A088C_6 *)quad)->unk_5E;
    ((Row_819A088C_S_819A088C_0 *)scratch)->unk_C4 = ((Row_819A088C_S_819A088C_6 *)quad)->unk_64;
    ((Row_819A088C_S_819A088C_0 *)scratch)->unk_CC = ((Row_819A088C_S_819A088C_6 *)quad)->unk_6A;

    ot_index = func_80065590(scratch + 0xB0, scratch + 0xB8,
                             scratch + 0xC0, scratch + 0xC8,
                             packet + 8, packet + 0x10,
                             packet + 0x18, packet + 0x20,
                             scratch + 0xD0, scratch + 0xD4) - depth_bias - 6;
    ((Row_819A088C_S_819A088C_0 *)scratch)->unk_100 = ot_index;

    if ((u32)ot_index < 0x1E0) {
        if ((((u16)(((Row_819A088C_S_819A088C_4 *)packet)->unk_08 + 0x20) < 0x181) &&
             ((u16)(((Row_819A088C_S_819A088C_4 *)packet)->unk_0A + 0x20) < 0x121)) |
            (((u16)(((Row_819A088C_S_819A088C_4 *)packet)->unk_10 + 0x20) < 0x181) &&
             ((u16)(((Row_819A088C_S_819A088C_4 *)packet)->unk_12 + 0x20) < 0x121)) |
            (((u16)(((Row_819A088C_S_819A088C_4 *)packet)->unk_18 + 0x20) < 0x181) &&
             ((u16)(((Row_819A088C_S_819A088C_4 *)packet)->unk_1A + 0x20) < 0x121)) |
            (((u16)(((Row_819A088C_S_819A088C_4 *)packet)->unk_20 + 0x20) < 0x181) &&
             ((u16)(((Row_819A088C_S_819A088C_4 *)packet)->unk_22 + 0x20) < 0x121))) {
            ((Row_819A088C_S_819A088C_2 *)render_state)->unk_14 &= 0x7FFF;
            texture_flags = texture[1];
            ((Row_819A088C_S_819A088C_2 *)render_state)->unk_0F = texture_flags;
            render_flags = ((Row_819A088C_S_819A088C_0 *)scratch)->unk_28;
            if (render_flags & 8) {
                ((Row_819A088C_S_819A088C_2 *)render_state)->unk_0F = (render_flags & 4) ?
                    (texture_flags | 2) : (texture_flags & 0xFD);
            }

            ((Row_819A088C_S_819A088C_4 *)packet)->unk_04.at00.v = ((Row_819A088C_S_819A088C_6 *)quad)->unk_0C;
            ((Row_819A088C_S_819A088C_4 *)packet)->unk_0C = ((Row_819A088C_S_819A088C_6 *)quad)->unk_10;
            ((Row_819A088C_S_819A088C_4 *)packet)->unk_14 = ((Row_819A088C_S_819A088C_6 *)quad)->unk_14;
            ((Row_819A088C_S_819A088C_4 *)packet)->unk_1C = ((Row_819A088C_S_819A088C_6 *)quad)->unk_18;
            ((Row_819A088C_S_819A088C_4 *)packet)->unk_00.at03.v = 8;
            ((Row_819A088C_S_819A088C_4 *)packet)->unk_04.at03.v = 0x3A;

            ((Row_819A088C_S_819A088C_4 *)packet)->unk_00.at00.v = (((Row_819A088C_S_819A088C_4 *)packet)->unk_00.at00.v & 0xFF000000) |
                ((*(u32 *)((u8 *)(((Row_819A088C_S_819A088C_0 *)scratch)->unk_24.p2)
                    + ((Row_819A088C_S_819A088C_0 *)scratch)->unk_100 * 4)) & 0x00FFFFFF);
            (*(u32 *)((u8 *)(((Row_819A088C_S_819A088C_0 *)scratch)->unk_24.p2) + ((Row_819A088C_S_819A088C_0 *)scratch)->unk_100 * 4)) =
                ((*(u32 *)((u8 *)(((Row_819A088C_S_819A088C_0 *)scratch)->unk_24.p2)
                    + ((Row_819A088C_S_819A088C_0 *)scratch)->unk_100 * 4)) & 0xFF000000) |
                ((u32)packet & 0x00FFFFFF);

            packet = ((Row_819A088C_S_819A088C_7 *)(*render_context_ptr))->unk_8D0;
            ((Row_819A088C_S_819A088C_7 *)(*render_context_ptr))->unk_8D0 = packet + 0xC;
            func_80067F20(packet, 0, 1, func_80066460(0, 1, 0, 0) & 0xFFFF, 0);
            ((Row_819A088C_S_819A088C_4 *)packet)->unk_00.at00.v = (((Row_819A088C_S_819A088C_4 *)packet)->unk_00.at00.v & 0xFF000000) |
                ((*(u32 *)((u8 *)(((Row_819A088C_S_819A088C_0 *)scratch)->unk_24.p2)
                    + ((Row_819A088C_S_819A088C_0 *)scratch)->unk_100 * 4)) & 0x00FFFFFF);
            (*(u32 *)((u8 *)(((Row_819A088C_S_819A088C_0 *)scratch)->unk_24.p2) + ((Row_819A088C_S_819A088C_0 *)scratch)->unk_100 * 4)) =
                ((*(u32 *)((u8 *)(((Row_819A088C_S_819A088C_0 *)scratch)->unk_24.p2)
                    + ((Row_819A088C_S_819A088C_0 *)scratch)->unk_100 * 4)) & 0xFF000000) |
                ((u32)packet & 0x00FFFFFF);
        }
    }

    func_80064A40();
}
