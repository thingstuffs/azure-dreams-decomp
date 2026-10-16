#include "modules/dungeon_resource06_slot0.h"

void dungeonProjectAndQueueTexturedQuad(void *quad, void *position, void *draw_state, s16 depth_bias)
{
    u8 *scratch = (u8 *)0x1F800000;
    u8 *packet;
    u8 *texture;
    s32 ot_index;
    u16 draw_flags;
    u8 tex_flags;
    R06_80174334_MATRIX matrix;

    ((R06_80174334_S_80174334_0 *)scratch)->unk_24.p = *(u8 **)((u8 *)(&gameWork)) + 0xB0;
    ((R06_80174334_S_80174334_0 *)scratch)->unk_88 = ((R06_80174334_S_80174334_1 *)position)->unk_02;
    ((R06_80174334_S_80174334_0 *)scratch)->unk_8C = ((R06_80174334_S_80174334_1 *)position)->unk_06;
    ((R06_80174334_S_80174334_0 *)scratch)->unk_90 = ((R06_80174334_S_80174334_1 *)position)->unk_0A;
    ((R06_80174334_S_80174334_2 *)draw_state)->unk_14 |= 0x8000;

    func_800649A0();

    ((R06_80174334_S_80174334_0 *)scratch)->unk_3C = 0x2000;
    ((R06_80174334_S_80174334_0 *)scratch)->unk_38 = 0x2000;
    ((R06_80174334_S_80174334_0 *)scratch)->unk_34 = 0x2000;
    ((R06_80174334_S_80174334_0 *)scratch)->unk_A4 = ((R06_80174334_S_80174334_2 *)draw_state)->unk_16;
    ((R06_80174334_S_80174334_0 *)scratch)->unk_A8 = ((R06_80174334_S_80174334_2 *)draw_state)->unk_1A;
    ((R06_80174334_S_80174334_0 *)scratch)->unk_A6 = ((R06_80174334_S_80174334_2 *)draw_state)->unk_18;
    func_80065820(scratch + 0xA4, scratch + 0x74);
    func_80064AE0(&matrix);
    func_80064840(&matrix, scratch + 0x74, scratch + 0x54);
    func_80064BC0(scratch + 0x54, scratch + 0x34);
    func_80064D80(scratch + 0x54);
    func_80064CF0(scratch + 0x54);

    texture = ((R06_80174334_S_80174334_2 *)draw_state)->unk_08;
    ((R06_80174334_S_80174334_0 *)scratch)->unk_28 = ((R06_80174334_S_80174334_2 *)draw_state)->unk_14;
    ((R06_80174334_S_80174334_0 *)scratch)->unk_0C.s32 = texture[8];
    ((R06_80174334_S_80174334_0 *)scratch)->unk_10.s32 = texture[9];
    (*(s32 *)((u8 *)scratch + 0x14)) = texture[0xA];
    ((R06_80174334_S_80174334_0 *)scratch)->unk_18.s32 = texture[0xB];
    packet = ((GpuContext *)(*(u8 **)((u8 *)(&gameWork))))->packetCursor;
    ((GpuContext *)(*(u8 **)((u8 *)(&gameWork))))->packetCursor = packet + 0x34;

    ((R06_80174334_S_80174334_0 *)scratch)->unk_B0 = ((R06_80174334_S_80174334_4 *)quad)->unk_64;
    ((R06_80174334_S_80174334_0 *)scratch)->unk_B8 = ((R06_80174334_S_80174334_4 *)quad)->unk_6A;
    ((R06_80174334_S_80174334_0 *)scratch)->unk_C0 = ((R06_80174334_S_80174334_4 *)quad)->unk_70;
    ((R06_80174334_S_80174334_0 *)scratch)->unk_C8 = ((R06_80174334_S_80174334_4 *)quad)->unk_76;
    ((R06_80174334_S_80174334_0 *)scratch)->unk_B2 = ((R06_80174334_S_80174334_4 *)quad)->unk_66;
    ((R06_80174334_S_80174334_0 *)scratch)->unk_BA = ((R06_80174334_S_80174334_4 *)quad)->unk_6C;
    ((R06_80174334_S_80174334_0 *)scratch)->unk_C2 = ((R06_80174334_S_80174334_4 *)quad)->unk_72;
    ((R06_80174334_S_80174334_0 *)scratch)->unk_CA = ((R06_80174334_S_80174334_4 *)quad)->unk_78;
    ((R06_80174334_S_80174334_0 *)scratch)->unk_B4 = ((R06_80174334_S_80174334_4 *)quad)->unk_68;
    ((R06_80174334_S_80174334_0 *)scratch)->unk_BC = ((R06_80174334_S_80174334_4 *)quad)->unk_6E;
    ((R06_80174334_S_80174334_0 *)scratch)->unk_C4 = ((R06_80174334_S_80174334_4 *)quad)->unk_74;
    ((R06_80174334_S_80174334_0 *)scratch)->unk_CC = ((R06_80174334_S_80174334_4 *)quad)->unk_7A;

    ot_index = func_80065590(scratch + 0xB0, scratch + 0xB8,
                             scratch + 0xC0, scratch + 0xC8,
                             packet + 8, packet + 0x14,
                             packet + 0x20, packet + 0x2C,
                             scratch + 0xD0, scratch + 0xD4) - depth_bias - 6;
    ((R06_80174334_S_80174334_0 *)scratch)->unk_100 = ot_index;

    if ((u32)ot_index < 0x1E0) {
        if ((((u16)(((R06_80174334_S_80174334_5 *)packet)->unk_08.u + 0x20) < 0x181) &&
             ((u16)(((R06_80174334_S_80174334_5 *)packet)->unk_0A.u + 0x20) < 0x121)) |
            (((u16)(((R06_80174334_S_80174334_5 *)packet)->unk_14 + 0x20) < 0x181) &&
             ((u16)(((R06_80174334_S_80174334_5 *)packet)->unk_16 + 0x20) < 0x121)) |
            (((u16)(((R06_80174334_S_80174334_5 *)packet)->unk_20 + 0x20) < 0x181) &&
             ((u16)(((R06_80174334_S_80174334_5 *)packet)->unk_22 + 0x20) < 0x121)) |
            (((u16)(((R06_80174334_S_80174334_5 *)packet)->unk_2C.u + 0x20) < 0x181) &&
             ((u16)(((R06_80174334_S_80174334_5 *)packet)->unk_2E.u + 0x20) < 0x121))) {
            ((R06_80174334_S_80174334_2 *)draw_state)->unk_14 &= 0x7FFF;

            ((R06_80174334_S_80174334_0 *)scratch)->unk_14.s32 += ((R06_80174334_S_80174334_0 *)scratch)->unk_0C.s32;
            if (((R06_80174334_S_80174334_0 *)scratch)->unk_14.s32 & 0x100) {
                ((R06_80174334_S_80174334_0 *)scratch)->unk_14.s32--;
            }
            ((R06_80174334_S_80174334_0 *)scratch)->unk_18.s32 += ((R06_80174334_S_80174334_0 *)scratch)->unk_10.s32;
            if (((R06_80174334_S_80174334_0 *)scratch)->unk_18.s32 & 0x100) {
                ((R06_80174334_S_80174334_0 *)scratch)->unk_18.s32--;
            }
            ((R06_80174334_S_80174334_0 *)scratch)->unk_10.s32 <<= 8;
            ((R06_80174334_S_80174334_0 *)scratch)->unk_18.s32 <<= 8;

            if (((R06_80174334_S_80174334_2 *)draw_state)->unk_12) {
                if (((R06_80174334_S_80174334_0 *)scratch)->unk_28 & 0x100) {
                    ((R06_80174334_S_80174334_5 *)packet)->unk_0E = ((R06_80174334_S_80174334_2 *)draw_state)->unk_12;
                } else {
                    ((R06_80174334_S_80174334_5 *)packet)->unk_0E = ((R06_80174334_S_80174334_2 *)draw_state)->unk_12 +
                                              ((R06_80174334_S_80174334_6 *)texture)->unk_06;
                }
            } else {
                ((R06_80174334_S_80174334_5 *)packet)->unk_0E = ((R06_80174334_S_80174334_6 *)texture)->unk_06;
            }

            ((R06_80174334_S_80174334_5 *)packet)->unk_0C = ((R06_80174334_S_80174334_0 *)scratch)->unk_10.u16 +
                                      ((R06_80174334_S_80174334_0 *)scratch)->unk_0C.u16;
            ((R06_80174334_S_80174334_5 *)packet)->unk_18.u16 = ((R06_80174334_S_80174334_0 *)scratch)->unk_10.u16 +
                                       ((R06_80174334_S_80174334_0 *)scratch)->unk_14.u16;

            if (((R06_80174334_S_80174334_2 *)draw_state)->unk_10) {
                ((R06_80174334_S_80174334_5 *)packet)->unk_1A = ((R06_80174334_S_80174334_2 *)draw_state)->unk_10 +
                                           (((R06_80174334_S_80174334_6 *)texture)->unk_04 & 0xFF9F);
            } else {
                ((R06_80174334_S_80174334_5 *)packet)->unk_1A = ((R06_80174334_S_80174334_6 *)texture)->unk_04;
            }

            ((R06_80174334_S_80174334_5 *)packet)->unk_24.at00.v = ((R06_80174334_S_80174334_0 *)scratch)->unk_18.u16 +
                                       ((R06_80174334_S_80174334_0 *)scratch)->unk_0C.u16;
            ((R06_80174334_S_80174334_5 *)packet)->unk_30.at00.v = ((R06_80174334_S_80174334_0 *)scratch)->unk_18.u16 +
                                       ((R06_80174334_S_80174334_0 *)scratch)->unk_14.u16;

            if (((R06_80174334_S_80174334_5 *)packet)->unk_08.s > ((R06_80174334_S_80174334_5 *)packet)->unk_2C.s) {
                ((R06_80174334_S_80174334_5 *)packet)->unk_18.u8--;
                ((R06_80174334_S_80174334_5 *)packet)->unk_30.at00u.v--;
            }
            if (((R06_80174334_S_80174334_5 *)packet)->unk_0A.s > ((R06_80174334_S_80174334_5 *)packet)->unk_2E.s) {
                ((R06_80174334_S_80174334_5 *)packet)->unk_24.at01.v--;
                ((R06_80174334_S_80174334_5 *)packet)->unk_30.at01.v--;
            }

            ((R06_80174334_S_80174334_5 *)packet)->unk_04.at00.v = ((R06_80174334_S_80174334_4 *)quad)->unk_04;
            ((R06_80174334_S_80174334_5 *)packet)->unk_10 = ((R06_80174334_S_80174334_4 *)quad)->unk_08;
            ((R06_80174334_S_80174334_5 *)packet)->unk_1C = ((R06_80174334_S_80174334_4 *)quad)->unk_0C;
            ((R06_80174334_S_80174334_5 *)packet)->unk_28 = ((R06_80174334_S_80174334_4 *)quad)->unk_10;

            func_8006671C(packet);

            tex_flags = texture[1];
            ((R06_80174334_S_80174334_2 *)draw_state)->unk_0F = tex_flags;
            draw_flags = ((R06_80174334_S_80174334_0 *)scratch)->unk_28;
            if (draw_flags & 8) {
                ((R06_80174334_S_80174334_2 *)draw_state)->unk_0F = (draw_flags & 4) ?
                    (tex_flags | 2) : (tex_flags & 0xFD);
            }

            ((R06_80174334_S_80174334_5 *)packet)->unk_04.at03.v |= ((R06_80174334_S_80174334_2 *)draw_state)->unk_0F;
            ((R06_80174334_S_80174334_5 *)packet)->unk_00 = (((R06_80174334_S_80174334_5 *)packet)->unk_00 & 0xFF000000) |
                ((*(u32 *)((u8 *)(((R06_80174334_S_80174334_0 *)scratch)->unk_24.p2)
                    + ((R06_80174334_S_80174334_0 *)scratch)->unk_100 * 4)) & 0x00FFFFFF);

            (*(u32 *)((u8 *)(((R06_80174334_S_80174334_0 *)scratch)->unk_24.p2) + ((R06_80174334_S_80174334_0 *)scratch)->unk_100 * 4)) =
                ((*(u32 *)((u8 *)(((R06_80174334_S_80174334_0 *)scratch)->unk_24.p2)
                    + ((R06_80174334_S_80174334_0 *)scratch)->unk_100 * 4)) & 0xFF000000) |
                ((u32)packet & 0x00FFFFFF);
        }
    }

    func_80064A40();
}

