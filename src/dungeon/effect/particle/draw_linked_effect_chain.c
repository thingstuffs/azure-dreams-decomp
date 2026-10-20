#include "dungeon/effect/particle/draw_linked_effect_chain.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/effect/particle/draw_linked_effect_chain.h"

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
#include "dungeon/effect/particle/draw_linked_effect_chain.h"

s32 draw_linked_effect_chain(void *state, void *position, void *appearance) {
    Row_819A0D64_GapNode *node;
    for (;;) {
        func_8002408C(state, position, appearance, 0);
        node = *(Row_819A0D64_GapNode **)((u8 *)state - 8);
        state = (u8 *)node + 0x20;
        if (node == 0) break;
        position = node->position;
        appearance = node->appearance;
    }
    return 0;
}
#include "dungeon/effect/particle/draw_linked_effect_chain.h"

void update_effect_countdown_fields(void *object_data)
{
    s32 phase_index;
    s32 pair_offset;
    Row_819A0DB8_S_func_819A0DB8_0 *object = object_data;

    phase_index = (s16)(object->unk_3A - 3);
    (*(s16 *)D_800261B0) = 1;
    switch (phase_index) {
    case 3:
    case 7:
        object->unk_92 -= 0x60;
        object->unk_9E -= 0x60;
        object->unk_93 += 0x20;
        object->unk_9F += 0x20;
        break;
    case 4:
    case 6:
    case 8:
    case 9:
        object->unk_92 += 0x20;
        object->unk_9E += 0x20;
        object->unk_8C -= 1;
        object->unk_98 += 1;
        break;
    case 2:
        object->unk_95 = 24;
        do {
            object->unk_A1 = 24;
        } while (0);
        pair_offset = -12;
        object->unk_8D = pair_offset;
        object->unk_99 = pair_offset;
        object->unk_92 += 0x20;
        object->unk_9E += 0x20;
        break;
    case 0:
        object->unk_95 = 16;
        do {
            object->unk_A1 = 16;
        } while (0);
        pair_offset = -8;
        object->unk_8D = pair_offset;
        object->unk_99 = pair_offset;
    case 1:
    case 5:
    case 10:
        object->unk_92 += 0x20;
        object->unk_9E += 0x20;
        break;
    }
    {
        u16 remaining_steps = object->unk_3A - 1;
        object->unk_3A = remaining_steps;
        if ((s16)remaining_steps <= 0) {
            *(u16 *)((u8 *)object - 2) |= 0x8000;
            object_flag_block.flags |= 0x8000;
        }
    }
}
#include "../../modules/ovl_19c088c_data.c"
#include "dungeon/effect/particle/draw_linked_effect_chain.h"

void fade_moving_effect(void *effect, Row_819A0EF0_S_800246F0_2 *motion, SpriteFrameState *primitive)
{
    s32 brightness;
    s32 x;
    s32 y;
    s32 dx;
    s32 dy;
    s32 ticks_left;

    ticks_left = ((Row_819A0EF0_S_800246F0_0 *)effect)->unk_3A.s;
    ((s16 *)D_800261B0)[0] = 1;
    ((Row_819A0EF0_S_800246F0_0 *)effect)->unk_3A.s = ticks_left - 1;
    func_800478B8(primitive);
    brightness = ((s16)((Row_819A0EF0_S_800246F0_0 *)effect)->unk_3A.s << 7) /
            ((Row_819A0EF0_S_800246F0_0 *)effect)->unk_3C;
    primitive->color.c.b = brightness;
    primitive->color.c.g = brightness;
    primitive->color.c.r = brightness;
    x = motion->unk_00;
    dx = motion->unk_0C;
    y = motion->unk_04;
    dy = motion->unk_10;
    motion->unk_00 = x + dx;
    motion->unk_04 = y + dy;
    if (((Row_819A0EF0_S_800246F0_0 *)effect)->unk_3A.u <= 0) {
        ((Row_819A0EF0_S_800246F0_0_pre *)effect)[-1].unk_00 |= 0x8000;
        ((Row_819A0EF0_S_800246F0_3 *)((u8 *)(&object_flag_block)))->unk_00 |= 0x8000;
    }
}
#include "dungeon/effect/particle/draw_linked_effect_chain.h"

void shrink_effect_and_spawn_particles(Row_819A0FC0_S_func_819A0FC0_0 *fadeState, void *unused, Row_819A0FC0_S_func_819A0FC0_1 *primitive)
{
    s32 brightness;
    u16 remainingTicks;

    remainingTicks = fadeState->unk_3A - 1;
    brightness = (s32)((s32)(remainingTicks << 0x10) >> 9) /
                 (s16)fadeState->unk_3C;
    (*(s16 *)D_800261B0) = 1;
    fadeState->unk_3A = remainingTicks;
    primitive->unk_0E = (s8)brightness;
    primitive->unk_0D = (s8)brightness;
    primitive->unk_0C = (s8)brightness;
    if ((s16)fadeState->unk_3A <= 0) {
        *(u16 *)((u8 *)fadeState - 2) =
            (u16)(((Row_819A0FC0_S_func_819A0FC0_2 *)((u8 *)fadeState - 2))->unk_00 | 0x8000);
        object_flag_block.flags |= 0x8000;
    }
}
#include "dungeon/effect/particle/draw_linked_effect_chain.h"

void func_80024834(void *fade_data)
{
    void *fade;
    s32 color_index;
    u16 ticks_left;

    fade = fade_data;
    ticks_left = ((Row_819A1034_S_819A1034_0 *)fade)->unk_3A.s;
    (*(s16 *)D_800261B0) = 1;
    ticks_left--;
    ((Row_819A1034_S_819A1034_0 *)fade)->unk_3A.s = ticks_left;
    for (color_index = 0; color_index < 4; color_index++) {
        ((Row_819A1034_S_819A1034_2 *)((u8 *)fade + color_index * 4))->unk_0C =
            ((Row_819A1034_S_819A1034_2 *)((u8 *)fade + color_index * 4))->unk_1C * ((Row_819A1034_S_819A1034_0 *)fade)->unk_3A.u /
            ((Row_819A1034_S_819A1034_0 *)fade)->unk_3C;
        ((Row_819A1034_S_819A1034_2 *)((u8 *)fade + color_index * 4))->unk_0D =
            ((Row_819A1034_S_819A1034_2 *)((u8 *)fade + color_index * 4))->unk_1D * ((Row_819A1034_S_819A1034_0 *)fade)->unk_3A.u /
            ((Row_819A1034_S_819A1034_0 *)fade)->unk_3C;
        ((Row_819A1034_S_819A1034_2 *)((u8 *)fade + color_index * 4))->unk_0E =
            ((Row_819A1034_S_819A1034_2 *)((u8 *)fade + color_index * 4))->unk_1E * ((Row_819A1034_S_819A1034_0 *)fade)->unk_3A.u /
            ((Row_819A1034_S_819A1034_0 *)fade)->unk_3C;
    }
    if (((Row_819A1034_S_819A1034_0 *)fade)->unk_3A.u <= 0) {
        (*(u16 *)((u8 *)fade + -2)) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}
#include "dungeon/effect/particle/draw_linked_effect_chain.h"

void advance_object_motion_and_animation(void *effect) {
    s32 blend_ticks;
    s32 elapsed_ticks;
    s32 color_index;
    u16 ticks_left;
    void *color_ptr;

    ticks_left = ((Row_819A1118_S_819A1118_0 *)effect)->unk_3A - 1;
    ((s16 *)D_800261B0)[0] = 1;
    blend_ticks = ((Row_819A1118_S_819A1118_0 *)effect)->unk_3E;
    ((Row_819A1118_S_819A1118_0 *)effect)->unk_3A = ticks_left;
    elapsed_ticks = ((Row_819A1118_S_819A1118_0 *)effect)->unk_3C - (s16) ticks_left;
    if (blend_ticks >= elapsed_ticks) {
        ((Row_819A1118_S_819A1118_0 *)effect)->unk_54 = (s16) (((Row_819A1118_S_819A1118_0 *)effect)->unk_60
            + ((s32) (((Row_819A1118_S_819A1118_0 *)effect)->unk_6C * elapsed_ticks) / blend_ticks));
        ((Row_819A1118_S_819A1118_0 *)effect)->unk_56 = (s16) (((Row_819A1118_S_819A1118_0 *)effect)->unk_62
            + ((s32) (((Row_819A1118_S_819A1118_0 *)effect)->unk_6E * (((Row_819A1118_S_819A1118_0 *)effect)->unk_3C
            - (s16) ((Row_819A1118_S_819A1118_0 *)effect)->unk_3A)) / (s16) ((Row_819A1118_S_819A1118_0 *)effect)->unk_3E));
        ((Row_819A1118_S_819A1118_0 *)effect)->unk_58 = (s16) (((Row_819A1118_S_819A1118_0 *)effect)->unk_64
            + ((s32) (((Row_819A1118_S_819A1118_0 *)effect)->unk_70 * (((Row_819A1118_S_819A1118_0 *)effect)->unk_3C
            - (s16) ((Row_819A1118_S_819A1118_0 *)effect)->unk_3A)) / (s16) ((Row_819A1118_S_819A1118_0 *)effect)->unk_3E));
        ((Row_819A1118_S_819A1118_0 *)effect)->unk_5A = (s16) (((Row_819A1118_S_819A1118_0 *)effect)->unk_66
            + ((s32) (((Row_819A1118_S_819A1118_0 *)effect)->unk_72 * (((Row_819A1118_S_819A1118_0 *)effect)->unk_3C
            - (s16) ((Row_819A1118_S_819A1118_0 *)effect)->unk_3A)) / (s16) ((Row_819A1118_S_819A1118_0 *)effect)->unk_3E));
        ((Row_819A1118_S_819A1118_0 *)effect)->unk_5C = (s16) (((Row_819A1118_S_819A1118_0 *)effect)->unk_68
            + ((s32) (((Row_819A1118_S_819A1118_0 *)effect)->unk_74 * (((Row_819A1118_S_819A1118_0 *)effect)->unk_3C
            - (s16) ((Row_819A1118_S_819A1118_0 *)effect)->unk_3A)) / (s16) ((Row_819A1118_S_819A1118_0 *)effect)->unk_3E));
        ((Row_819A1118_S_819A1118_0 *)effect)->unk_5E = (s16) (((Row_819A1118_S_819A1118_0 *)effect)->unk_6A
            + ((s32) (((Row_819A1118_S_819A1118_0 *)effect)->unk_76 * (((Row_819A1118_S_819A1118_0 *)effect)->unk_3C
            - (s16) ((Row_819A1118_S_819A1118_0 *)effect)->unk_3A)) / (s16) ((Row_819A1118_S_819A1118_0 *)effect)->unk_3E));
    }
    for (color_index = 0; color_index < 4; color_index++) {
        color_ptr = (u8 *)effect + color_index * 4;
        ((Row_819A1118_S_819A1118_1 *)color_ptr)->unk_0C =
            (s8) ((s32) (((Row_819A1118_S_819A1118_1 *)color_ptr)->unk_1C * (s16) ((Row_819A1118_S_819A1118_0 *)effect)->unk_3A) / (s16) ((Row_819A1118_S_819A1118_0 *)effect)->unk_3C);
        ((Row_819A1118_S_819A1118_1 *)color_ptr)->unk_0D =
            (s8) ((s32) (((Row_819A1118_S_819A1118_1 *)color_ptr)->unk_1D * (s16) ((Row_819A1118_S_819A1118_0 *)effect)->unk_3A) / (s16) ((Row_819A1118_S_819A1118_0 *)effect)->unk_3C);
        ((Row_819A1118_S_819A1118_1 *)color_ptr)->unk_0E =
            (s8) ((s32) (((Row_819A1118_S_819A1118_1 *)color_ptr)->unk_1E * (s16) ((Row_819A1118_S_819A1118_0 *)effect)->unk_3A) / (s16) ((Row_819A1118_S_819A1118_0 *)effect)->unk_3C);
    }
    if ((s16) ((Row_819A1118_S_819A1118_0 *)effect)->unk_3A <= 0) {
        (*(u16 *)((u8 *)effect + -2)) = (u16) (((Row_819A1118_S_819A1118_0_pre *)effect)[-1].unk_00 | 0x8000);
        object_flag_block.flags |= 0x8000;
    }
}
#include "dungeon/effect/particle/draw_linked_effect_chain.h"

void choose_random_sign(void *effect, s32 unused, void *primitive)
{
    s32 intensity;
    u16 ticks_left;

    ticks_left = *(u16 *)((u8 *)effect + 0x3A) - 1;
    intensity = ((s32)(ticks_left << 16) >> 9) /
            *(s16 *)((u8 *)effect + 0x3C);
    (*(s16 *)D_800261B0) = 1;
    *(u16 *)((u8 *)effect + 0x3A) = ticks_left;
    *(s8 *)((u8 *)primitive + 0x0E) = intensity;
    *(s8 *)((u8 *)primitive + 0x0D) = intensity;
    *(s8 *)((u8 *)primitive + 0x0C) = intensity;
    *(u8 *)((u8 *)effect + 0x8C) -= 1;
    *(u16 *)((u8 *)primitive + 0x1A) += *(u16 *)((u8 *)effect + 0x40);
    if (*(s16 *)((u8 *)effect + 0x3A) <= 0) {
        *(u16 *)((u8 *)effect - 2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}
#include "dungeon/effect/particle/draw_linked_effect_chain.h"

void func_80024BD0(Row_819A13D0_Work *work, s32 unused, Row_819A13D0_Obj *obj) {
    s32 scaled_count;
    u16 count;
    u16 angle;

    count = work->count - 1;
    scaled_count = (s32)((s32)(count << 16) >> 9) / work->divisor;
    work->count = count;
    angle = obj->angle;
    ((s16 *)D_800261B0)[0] = 1;
    obj->angle = angle + 0x190;
    obj->c2 = scaled_count;
    obj->c1 = scaled_count;
    obj->c0 = scaled_count;
    if ((s16)work->count > 0) {
        return;
    }
    *(u16 *)((u8 *)work - 2) |= 0x8000;
    object_flag_block.flags |= 0x8000;
}
#include "dungeon/effect/particle/draw_linked_effect_chain.h"

void func_80024C50(Row_819A1450_S_819A1450_4 *source, s32 unused_1, s32 unused_2, s16 offset_x, s16 offset_y,
                   s16 offset_z)
{
    Row_819A1450_LocalTable direction_table;
    void *node;
    SpriteFrameState *part;
    Row_819A1450_S_819A1450_3 *coords;
    u8 *setup;
    s16 direction;

    direction_table = D_80024034;
    node = func_8003FC64(0x212);
    if (node != 0) {
        setup = (u8 *)node + 0x20;
        ((Row_819A1450_S_819A1450_0 *)setup)->unk_3A = 5;
        ((Row_819A1450_S_819A1450_0 *)setup)->unk_3C = 5;
        ((Row_819A1450_S_819A1450_1 *)node)->unk_10 = D_800246F0;
        register_node(node, project_sprite_chain);

        part = ((Row_819A1450_S_819A1450_1 *)node)->unk_0C;
        part->tpage_abr = 0x20;
        part->flags |= 0xC;
        part->angle_z = (rand() & 7) << 9;
        part->unk_06 = 0;

        coords = ((Row_819A1450_S_819A1450_1 *)node)->unk_08;
        coords->unk_02 = offset_x;
        coords->unk_06 = offset_y;
        coords->unk_0A = offset_z;
        coords->unk_02 += source->unk_84;
        coords->unk_06 += source->unk_86;
        coords->unk_0A += source->unk_88;

        direction = source->unk_36;
        coords->unk_0C =
            (s32)direction_table.entries[direction].first << 20;
        direction = source->unk_36;
        coords->unk_10 =
            (s32)direction_table.entries[direction].second << 20;

        part = ((Row_819A1450_S_819A1450_1 *)node)->unk_0C;
        part->scale_y = 0x800;
        part->scale_x = 0x800;
        part->color.c.b = 0x80;
        part->color.c.g = 0x80;
        part->color.c.r = 0x80;
        func_8003DB94(part, D_800DEC00, 0);
    }
}
#include "dungeon/effect/particle/draw_linked_effect_chain.h"

void advance_entity_effect_sequence(Row_819A1654_Entity *entity, void *saved_context, void *saved_data) {
    Row_819A1654_PointTable points;
    Row_819A1654_Task *task;
    Row_819A1654_Effect *effect;
    Row_819A1654_Sprite *sprite;
    Row_819A1654_Coord *coord;
    Row_819A1654_Coord *start_origin;
    Row_819A1654_Coord *origin_loop;
    EntityRec *origin_second;
    Row_819A1654_Coord *origin_path;
    u8 *copy_page;
    EntityRec *world;
    void *focus;
    Row_819A1654_Coord *focus_coord;
    s32 spawn_index;
    s32 path_pair;
    s32 first_path_timer;
    s32 sound_id;
    s32 saved_timer;
    s16 rechecked_timer;
    EntityRec *start_world;
    Row_819A1654_World *hit_world;
    void (*particle_callback)(void);

    *(Row_819A1654_PointTable *)&points = *(Row_819A1654_PointTable *)&D_80024054;

    entity->age++;

    {
        s32 dispatch_state;
        s32 interp_work;
        dispatch_state = entity->state;
        switch (dispatch_state) {
        case 0:
        start_world = D_800814A8;
        start_world->unk_F4 = 0;
        start_world->unk_96 = 20;
        D_80082E86[0] = 6;
        entity->state++;
        start_origin = &D_80083780[0];
        {
            Row_819A1654_Blob24 *flag_base = D_80026198;
            entity->base[0] = start_origin->x;
            entity->base[1] = start_origin->y;
            entity->base[2] = start_origin->z;
            *(s16 *)(flag_base->bytes + 24) = 1;
        }
    case 1:
        if ((*entity->header & 0x80) != 0) {
            u8 *hit_world_page = (u8 *)0x80080000;
            s16 next_state;
            u16 angle;
            hit_world = *(Row_819A1654_World **)(hit_world_page + 0x14A8);
            entity->timer = 33;
            hit_world->fieldA6--;
            hit_world->fieldA8 = entity->type;
            next_state = entity->state;
            angle = (*(Row_819A1654_World **)(hit_world_page + 0x14A8))->angle;
            entity->state = next_state + 1;
            entity->age = 0;
            entity->point_index = (angle >> 9) & 7;
            break;
        }
        break;

        case 2:
            entity->timer--;
            if (entity->timer <= 0) {
                entity->timer = 16;
                entity->state++;
                break;
            }

            if (entity->timer == 18) {
                spawn_index = func_80053EF0(4);
                sound_id = 0x4300;
                if (spawn_index != 2) {
                    sound_id = 0x300;
                }
                play_sound_if_enabled(sound_id);
            }

            if (entity->timer == 24) {
                if (get_sprite_attachment_vector((&D_80082E80[0])->found, &D_80082E80[0], &entity->x, 0) != 0) {
                    spawn_index = 0;
                    particle_callback = choose_random_sign;
                    origin_loop = D_80083780;
                    do {
                        task = (Row_819A1654_Task *)func_8003FC64(0x212);
                        effect = &task->effect;
                        if (task != 0) {
                            effect->timer3A = 20;
                            effect->timer3C = 20;
                            effect->random40 = (s16)((func_80069EF8() & 0xFF) + 200);
                            task->callback = particle_callback;
                            register_node(task, project_sprite_chain);
                            sprite = task->sprite;
                            sprite->field10 = 32;
                            sprite->flags |= 0xC;
                            coord = task->coord;
                            coord->x = entity->x + origin_loop->x;
                            coord->y = entity->y + origin_loop->y;
                            coord->z = entity->z + origin_loop->z;
                            sprite = task->sprite;
                            interp_work = 0x1000;
                            sprite->field1E = interp_work;
                            sprite->field1C = interp_work;
                            interp_work = 0x80;
                            sprite->b = interp_work;
                            sprite->g = interp_work;
                            sprite->r = interp_work;
                            sprite->field16 = (func_80069EF8() & 0xF) << 8;
                            sprite->field18 = (func_80069EF8() & 0xF) << 8;
                            sprite->field1A = (func_80069EF8() & 0xF) << 8;
                            *(Row_819A1654_Blob12 *)(task->data) = D_80026180[0];
                            sprite->data = task->data;
                        }
                        spawn_index++;
                    } while (spawn_index < 10);
                }
            }

            if (entity->timer == 24) {
                if (get_sprite_attachment_vector((&D_80082E80[0])->found, &D_80082E80[0], &entity->x, 0) != 0) {
                    task = (Row_819A1654_Task *)func_8003FC64(0x212);
                    effect = &task->effect;
                    if (task != 0) {
                        s32 burst_size;
                        u16 burst_flags;
                        effect->timer3A = 20;
                        effect->timer3C = 20;
                        task->callback = func_80024BD0;
                        register_node(task, project_sprite_chain);
                        burst_size = 96;
                        sprite = task->sprite;
                        burst_flags = sprite->flags;
                        origin_second = &D_80083780;
                        sprite->field10 = burst_size;
                        sprite->flags = burst_flags | 0xC;
                        coord = task->coord;
                        coord->x = entity->x + origin_second->x.w.i;
                        coord->y = entity->y + origin_second->y.w.i;
                        coord->z = entity->z + origin_second->z.w.i;
                        sprite = task->sprite;
                        sprite->field1E = 0x1000;
                        sprite->field1C = 0x1000;
                        sprite->b = 0x80;
                        sprite->g = 0x80;
                        sprite->r = 0x80;
                        *(Row_819A1654_Blob12 *)(task->data) = D_8002618C[0];
                        (*(void **)((u8 *)sprite + 8)) = task->data;
                    }
                }
            }

            if (entity->timer < 10) {
                if (entity->timer < 6) {
                    if (entity->timer != 3) {
                        s32 second_path_timer;
                        path_pair = entity->timer == 4;
                        second_path_timer = 2;
                        first_path_timer = 4;
                        if (entity->timer == second_path_timer) {
                            path_pair = second_path_timer;
                        }
                        if (entity->timer == 1) {
                            path_pair = 3;
                        }

                        if (get_sprite_attachment_vector((&D_80082E80[0])->found, &D_80082E80[0], &entity->x, 0) != 0) {
                            s32 path_point;
                            Row_819A1654_Entity *path_entity;
                            Row_819A1654_Entity *next_entity;
                            s32 path_half;
                            u32 dim_color;
                            path_point = path_pair * 2;
                            path_entity = (Row_819A1654_Entity *)((u8 *)entity + (path_point + path_pair) * 4);
                            path_point++;
                            path_half = entity->x / 2;
                            origin_path = D_80083780;
                            path_entity->path[0] = path_half + (origin_path->x - entity->base[0]) / 2;
                            path_entity->path[1] = entity->y / 2 + (origin_path->y - entity->base[1]) / 2;
                            path_entity->path[2] = entity->z / 2 + (origin_path->z - entity->base[2]) / 2;
                            next_entity = (Row_819A1654_Entity *)((u8 *)entity + path_point * 3 * 2);
                            next_entity->path[0] = entity->x / 4 + (origin_path->x - entity->base[0]) / 2;
                            next_entity->path[1] = entity->y / 4 + (origin_path->y - entity->base[1]) / 2;
                            next_entity->path[2] = entity->z / 4 + (origin_path->z - entity->base[2]) / 2;

                            if (entity->timer == first_path_timer) {
                                task = (Row_819A1654_Task *)func_8003FC64(0x212);
                                effect = &task->effect;
                                if (task != 0) {
                                    effect->timer3A = 20;
                                    effect->timer3C = 20;
                                    task->callback = func_80024834;
                                    register_node(task, draw_linked_effect_chain);
                                    sprite = task->sprite;
                                    sprite->field10 = 32;
                                    sprite->flags |= 0xC;
                                    effect->path[0] = entity->path[6];
                                    effect->path[1] = entity->path[7];
                                    effect->path[2] = entity->path[8];
                                    effect->path[3] = entity->path[0];
                                    effect->path[4] = entity->path[1];
                                    effect->path[5] = entity->path[2];
                                    effect->path[6] = entity->path[9];
                                    effect->path[7] = entity->path[10];
                                    effect->path[8] = entity->path[11];
                                    effect->path[9] = entity->path[3];
                                    effect->path[10] = entity->path[4];
                                    effect->path[11] = entity->path[5];
                                    coord = task->coord;
                                    coord->x = entity->base[0];
                                    coord->y = entity->base[1];
                                    coord->z = entity->base[2];
                                    sprite = task->sprite;
                                    sprite->field1E = 0x1000;
                                    sprite->field1C = 0x1000;
                                    sprite->b = 0x80;
                                    sprite->g = 0x80;
                                    sprite->r = 0x80;
                                    *(Row_819A1654_Blob12 *)(task->data) = D_8002618C[0];
                                    (*(void **)((u8 *)sprite + 8)) = task->data;
                                }
                            }

                            if (entity->timer == 2) {
                                task = (Row_819A1654_Task *)func_8003FC64(0x212);
                                effect = &task->effect;
                                if (task != 0) {
                                    s32 bright_color;
                                    bright_color = 0x804020;
                                    dim_color = 0x201008;
                                    effect->value1C = bright_color;
                                    effect->value24 = dim_color;
                                    effect->value28 = dim_color;
                                    effect->value20 = bright_color;
                                    effect->value0C = effect->value1C;
                                    effect->value10 = effect->value20;
                                    effect->value14 = effect->value24;
                                    effect->value18 = effect->value28;
                                    effect->timer3A = 20;
                                    effect->timer3C = 20;
                                    task->callback = func_80024834;
                                    register_node(task, draw_linked_effect_chain);
                                    sprite = task->sprite;
                                    sprite->field10 = 32;
                                    sprite->flags |= 0xC;
                                    effect->path[0] = entity->path[12];
                                    effect->path[1] = entity->path[13];
                                    effect->path[2] = entity->path[14];
                                    effect->path[3] = entity->path[6];
                                    effect->path[4] = entity->path[7];
                                    effect->path[5] = entity->path[8];
                                    effect->path[6] = entity->path[15];
                                    effect->path[7] = entity->path[16];
                                    effect->path[8] = entity->path[17];
                                    effect->path[9] = entity->path[9];
                                    effect->path[10] = entity->path[10];
                                    effect->path[11] = entity->path[11];
                                    coord = task->coord;
                                    coord->x = entity->base[0];
                                    coord->y = entity->base[1];
                                    coord->z = entity->base[2];
                                    sprite = task->sprite;
                                    sprite->field1E = 0x1000;
                                    sprite->field1C = 0x1000;
                                    sprite->b = 0x80;
                                    sprite->g = 0x80;
                                    sprite->r = 0x80;
                                    *(Row_819A1654_Blob12 *)(task->data) = D_8002618C[0];
                                    (*(void **)((u8 *)sprite + 8)) = task->data;
                                }
                            }

                            saved_timer = entity->timer;
                            if (saved_timer == 1) {
                                task = (Row_819A1654_Task *)func_8003FC64(0x212);
                                effect = &task->effect;
                                if (task != 0) {
                                    s32 bright_color;
                                    bright_color = 0x804020;
                                    dim_color = 0x201008;
                                    effect->value1C = bright_color;
                                    effect->value24 = dim_color;
                                    effect->value28 = dim_color;
                                    effect->value20 = bright_color;
                                    effect->value0C = effect->value1C;
                                    effect->value10 = effect->value20;
                                    effect->value14 = effect->value24;
                                    effect->value18 = effect->value28;
                                    effect->timer3A = 20;
                                    effect->timer3C = 20;
                                    task->callback = func_80024834;
                                    register_node(task, draw_linked_effect_chain);
                                    sprite = task->sprite;
                                    sprite->field10 = 32;
                                    sprite->flags |= 0xC;
                                    effect->path[0] = entity->path[18];
                                    effect->path[1] = entity->path[19];
                                    effect->path[2] = entity->path[20];
                                    effect->path[3] = entity->path[12];
                                    effect->path[4] = entity->path[13];
                                    effect->path[5] = entity->path[14];
                                    effect->path[6] = entity->path[21];
                                    effect->path[7] = entity->path[22];
                                    effect->path[8] = entity->path[23];
                                    effect->path[9] = entity->path[15];
                                    effect->path[10] = entity->path[16];
                                    effect->path[11] = entity->path[17];
                                    coord = task->coord;
                                    coord->x = entity->base[0];
                                    coord->y = entity->base[1];
                                    coord->z = entity->base[2];
                                    sprite = task->sprite;
                                    sprite->field1E = 0x1000;
                                    sprite->field1C = 0x1000;
                                    sprite->b = 0x80;
                                    sprite->g = 0x80;
                                    sprite->r = 0x80;
                                    *(Row_819A1654_Blob12 *)(task->data) = D_8002618C[0];
                                    (*(void **)((u8 *)sprite + 8)) = task->data;
                                }

                                rechecked_timer = entity->timer;
                                if (rechecked_timer == saved_timer) {
                                    task = (Row_819A1654_Task *)func_8003FC64(0x212);
                                    effect = &task->effect;
                                    if (task != 0) {
                                        effect->timer3A = 20;
                                        effect->timer3C = 20;
                                        effect->value1C = 0x10000;
                                        effect->value24 = 0x804020;
                                        effect->value28 = 0x804020;
                                        effect->value20 = 0x10000;
                                        effect->mode3E = 2;
                                        effect->value0C = effect->value1C;
                                        effect->value10 = effect->value20;
                                        effect->value14 = effect->value24;
                                        effect->value18 = effect->value28;
                                        task->callback = advance_object_motion_and_animation;
                                        register_node(task, draw_linked_effect_chain);
                                        sprite = task->sprite;
                                        sprite->field10 = 32;
                                        sprite->flags |= 0xC;
                                        effect->path[0] = entity->path[12];
                                        effect->path[1] = entity->path[13];
                                        effect->path[2] = entity->path[14];
                                        effect->path[3] = entity->path[6];
                                        effect->path[4] = entity->path[7];
                                        effect->path[5] = entity->path[8];
                                        effect->path[6] = entity->path[12];
                                        effect->path[7] = entity->path[13];
                                        effect->path[8] = entity->path[14];
                                        effect->path[9] = entity->path[6];
                                        effect->path[10] = entity->path[7];
                                        effect->path[11] = entity->path[8];
                                        effect->path[12] = points.point[entity->point_index].x * 8;
                                        effect->path[13] = points.point[entity->point_index].y * 8;
                                        effect->path[14] = 0;
                                        effect->path[15] = points.point[entity->point_index].x * 8;
                                        effect->path[16] = points.point[entity->point_index].y * 8;
                                        effect->path[17] = 0;
                                        coord = task->coord;
                                        coord->x = entity->base[0];
                                        coord->y = entity->base[1];
                                        coord->z = entity->base[2];
                                        sprite = task->sprite;
                                        sprite->field1E = 0x1000;
                                        sprite->field1C = 0x1000;
                                        sprite->b = 0x80;
                                        sprite->g = 0x80;
                                        sprite->r = 0x80;
                                        *(Row_819A1654_Blob12 *)(task->data) = D_8002618C[0];
                                        (*(void **)((u8 *)sprite + 8)) = task->data;
                                    }

                                    saved_timer = entity->timer;
                                    if (saved_timer == rechecked_timer) {
                                        task = (Row_819A1654_Task *)func_8003FC64(0x212);
                                        effect = &task->effect;
                                        if (task != 0) {
                                            effect->timer3A = 20;
                                            effect->timer3C = 20;
                                            effect->value1C = 0x10000;
                                            effect->value24 = 0x804020;
                                            effect->value28 = 0x804020;
                                            effect->value20 = 0x10000;
                                            effect->mode3E = 2;
                                            effect->value0C = effect->value1C;
                                            effect->value10 = effect->value20;
                                            effect->value14 = effect->value24;
                                            effect->value18 = effect->value28;
                                            task->callback = advance_object_motion_and_animation;
                                            register_node(task, draw_linked_effect_chain);
                                            sprite = task->sprite;
                                            sprite->field10 = 32;
                                            sprite->flags |= 0xC;
                                            effect->path[0] = entity->path[18];
                                            effect->path[1] = entity->path[19];
                                            effect->path[2] = entity->path[20];
                                            effect->path[3] = entity->path[12];
                                            effect->path[4] = entity->path[13];
                                            effect->path[5] = entity->path[14];
                                            effect->path[6] = entity->path[18];
                                            effect->path[7] = entity->path[19];
                                            effect->path[8] = entity->path[20];
                                            effect->path[9] = entity->path[12];
                                            effect->path[10] = entity->path[13];
                                            effect->path[11] = entity->path[14];
                                            effect->path[12] = points.point[entity->point_index].x * 8;
                                            effect->path[13] = points.point[entity->point_index].y * 8;
                                            effect->path[14] = 0;
                                            effect->path[15] = points.point[entity->point_index].x * 8;
                                            effect->path[16] = points.point[entity->point_index].y * 8;
                                            effect->path[17] = 0;
                                            coord = task->coord;
                                            coord->x = entity->base[0];
                                            coord->y = entity->base[1];
                                            coord->z = entity->base[2];
                                            sprite = task->sprite;
                                            sprite->field1E = 0x1000;
                                            sprite->field1C = 0x1000;
                                            sprite->b = 0x80;
                                            sprite->g = 0x80;
                                            sprite->r = 0x80;
                                            *(Row_819A1654_Blob12 *)(task->data) = D_8002618C[0];
                                            (*(void **)((u8 *)sprite + 8)) = task->data;
                                        }

                                        if (entity->timer == saved_timer) {
                                            s32 trail_fraction;
                                            s32 interp_x;
                                            s32 interp_z;
                                            s32 interp_base;
                                            s32 out_x;
                                            saved_timer = 0;
loop_1:
                                            {
                                                interp_base = entity->path[18];
                                                interp_work = entity->path[6] - interp_base;
                                                trail_fraction = saved_timer << 1;
                                                interp_x = interp_work * trail_fraction;
                                                if (interp_x < 0) {
                                                    interp_x += 15;
                                                }
                                                out_x = interp_base * 2;
                                                interp_base = entity->path[19];
                                                interp_work = entity->path[7] - interp_base;
                                                next_entity = (Row_819A1654_Entity *)(interp_work * trail_fraction);
                                                interp_work = interp_x >> 4;
                                                out_x += interp_work;
                                                interp_x = interp_base * 2;
                                                if ((s32)next_entity < 0) {
                                                    next_entity = (Row_819A1654_Entity *)((s32)next_entity + 15);
                                                }
                                                interp_base = entity->path[20];
                                                interp_work = entity->path[8] - interp_base;
                                                interp_z = interp_work * trail_fraction;
                                                interp_work = (s32)next_entity >> 4;
                                                {
                                                    s32 interp_y = interp_x + interp_work;
                                                    interp_work = interp_y;
                                                }
                                                interp_base = interp_base * 2;
                                                if (interp_z < 0) {
                                                    interp_z += 15;
                                                }
                                                D_80024C50(entity, saved_context, saved_data,
                                                    (s16)out_x, (s16)interp_work,
                                                    (s16)(interp_base + (interp_z >> 4)));
                                                saved_timer++;
                                            }
                                            if (saved_timer < 16)
                                                goto loop_1;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            world = D_800814A8;
            focus = world->target;
            if (focus != 0 && entity->timer == 1) {
                task = (Row_819A1654_Task *)func_8003FC64(0x212);
                effect = &task->effect;
                if (task != 0) {
                    effect->timer3A = 13;
                    effect->timer3C = 13;
                    task->callback = update_effect_countdown_fields;
                    register_node(task, project_sprite_chain);
                    sprite = task->sprite;
                    sprite->field6 = 6;
                    sprite->flags &= 0xFFF3;
                    focus_coord = *(Row_819A1654_Coord **)((u8 *)focus - 24);
                    coord = task->coord;
                    coord->x = focus_coord->x;
                    coord->y = focus_coord->y;
                    coord->z = focus_coord->z - (D_800DDC40[*((u8 *)focus + 19)] >> 1);
                    sprite = task->sprite;
                    sprite->field1E = 0x1000;
                    sprite->field1C = 0x1000;
                    sprite->b = 0x80;
                    sprite->g = 0x80;
                    sprite->r = 0x80;
                    *(Row_819A1654_Blob12 *)task->data = *(Row_819A1654_Blob12 *)D_80026198;
                    copy_page = (u8 *)D_80026198;
                    *(Row_819A1654_Blob12 *)(task->data + 12) = *(Row_819A1654_Blob12 *)(copy_page + 12);
                    sprite->data = task->data;
                    break;
                }
            }
            break;

        case 3:
            if ((D_80082E94[0] & 0x8000) != 0 || --entity->timer < 0) {
                entity->state = 4;
            }
            /* fallthrough */

        case 4:
            if (((s16 *)D_800261B0)[0] == 0) {
                ((Row_819A1654_ControlGlobal *)&g_dungeon_status)[0].active = 0;
                D_80082E86[0] = 0;
                ((Row_819A1654_ControlGlobal *)&g_dungeon_status)[0].count--;
                *((u16 *)entity - 1) |= 0x8000;
                D_800814A0[0].flags |= 0x8000;
                break;
            }
            ((s16 *)D_800261B0)[0] = 0;
            break;

        default:
            break;
        }
    }
}
