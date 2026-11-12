#include "shared/vector.h"
#include "dungeon/effect/particle.h"
#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"
#include "sdk/libgpu.h"
#include "sdk/libgte.h"

typedef struct S_80166968_0 {
    u8 pad_00[0x24];
    u8 *unk_24;
    u16 unk_28;
    u8 pad_2A[0xA];
    s32 unk_34;
    s32 unk_38;
    s32 unk_3C;
    u8 pad_40[0x14];
    MATRIX composed_matrix; /* CompMatrix of the view matrix and object_matrix, scaled by +0x34 and installed */
    MATRIX object_matrix; /* RotMatrix of the angles at +0xA4; its translation is the integer position */
    u8 pad_94[0x10];
    u16 unk_A4;
    u16 unk_A6;
    u16 unk_A8;
    u8 pad_AA[0x6];
    s16 unk_B0;
    s16 unk_B2;
    s16 unk_B4;
    u8 pad_B6[0x2];
    s16 unk_B8;
    s16 unk_BA;
    s16 unk_BC;
    u8 pad_BE[0x2];
    s16 unk_C0;
    s16 unk_C2;
    s16 unk_C4;
    u8 pad_C6[0x2];
    s16 unk_C8;
    s16 unk_CA;
    s16 unk_CC;
    u8 pad_CE[0x2];
    s32 depth_cue; /* RotAverage4 depth-cue output */
    s32 gte_flag; /* RotAverage4 GTE flag output */
    u8 pad_D8[0x28];
    s32 unk_100;
} S_80166968_0;   /* scratch in draw_ribbon_center_lines */

typedef struct RibbonLineGeometry {
    u32 unk_00;
    u8 pad_04[0x70];
    s16 unk_74;
    s16 unk_76;
    s16 unk_78;
    s16 unk_7A;
    s16 unk_7C;
    s16 unk_7E;
    s16 unk_80;
    s16 unk_82;
    s16 unk_84;
    s16 unk_86;
    s16 unk_88;
    s16 unk_8A;
} RibbonLineGeometry;   /* arg0 in draw_ribbon_center_lines */

typedef struct S_80166968_5 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_00;   /* overlapping accesses */
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_04;   /* overlapping accesses */
} S_80166968_5;   /* packet in draw_ribbon_center_lines */

#include "sdk/libgte_matrix.h"

/* Project edge midpoints and queue line and draw-mode packets in the ordering table. */
void draw_ribbon_center_lines(RibbonLineGeometry *geometry, ObjectPosition *position, SpriteFrameState *render_data, s32 depth_bias)
{
    S_80166968_0 *scratch = (S_80166968_0 *)0x1F800000;
    u8 *render_state = g_game_work.draw_buffer;
    u32 draw_flags;
    void **render_state_ref;
    S_80166968_5 *packet;
    s8 *texture_entry;
    u32 color;
    s32 zero;
    s32 ot_index;
    s32 mid_a_x;
    s32 mid_b_x;
    s32 mid_a_y;
    s32 mid_b_y;
    s32 mid_a_z;
    s32 mid_b_z;
    u8 *point_a;
    u8 *point_b;
    u8 *point_a_copy;
    u8 *point_b_copy;
    u32 address_mask;
    u32 length_mask;
    u16 render_flags;
    s32 saved_depth_bias;
    MATRIX matrix;

    scratch->unk_24 = render_state + 0xB0;
    address_mask = 0x00FFFFFF;
    scratch->object_matrix.t[0] = position->x.w.i;
    scratch->object_matrix.t[1] = position->y.w.i;
    saved_depth_bias = depth_bias;
    scratch->object_matrix.t[2] = position->z.w.i;
    render_data->flags |= 0x8000;
    render_state_ref = &g_game_work.draw_buffer;
    PushMatrix();

    scratch->unk_3C = 0x2000;
    scratch->unk_38 = 0x2000;
    scratch->unk_34 = 0x2000;
    scratch->unk_A4 = render_data->angle_x;
    scratch->unk_A8 = render_data->angle_z;
    scratch->unk_A6 = render_data->angle_y;
    RotMatrix(&scratch->unk_A4, &scratch->object_matrix);
    ReadRotMatrix(&matrix);
    CompMatrix(&matrix, &scratch->object_matrix, &scratch->composed_matrix);
    ScaleMatrix(&scratch->composed_matrix, &scratch->unk_34);
    SetTransMatrix(&scratch->composed_matrix);
    SetRotMatrix(&scratch->composed_matrix);

    texture_entry = render_data->source;
    length_mask = 0xFF000000;
    scratch->unk_28 = render_data->flags;

    for (;;) {
        packet = ((GpuContext *)(*render_state_ref))->packetCursor;
        ((GpuContext *)(*render_state_ref))->packetCursor = (u8 *)packet + 0x10;

        point_a = (u8 *)scratch + 0xB0;
        mid_a_x = (geometry->unk_74 + geometry->unk_7A) / 2;
        scratch->unk_C0 = mid_a_x;
        scratch->unk_B0 = mid_a_x;
        point_b = (u8 *)scratch + 0xB8;
        mid_b_x = (geometry->unk_80 + geometry->unk_86) / 2;
        scratch->unk_C8 = mid_b_x;
        scratch->unk_B8 = mid_b_x;
        point_a_copy = (u8 *)scratch + 0xC0;
        mid_a_y = (geometry->unk_76 + geometry->unk_7C) / 2;
        scratch->unk_C2 = mid_a_y;
        scratch->unk_B2 = mid_a_y;
        point_b_copy = (u8 *)scratch + 0xC8;
        mid_b_y = (geometry->unk_82 + geometry->unk_88) / 2;
        scratch->unk_CA = mid_b_y;
        scratch->unk_BA = mid_b_y;
        mid_a_z = (geometry->unk_78 + geometry->unk_7E) / 2;
        scratch->unk_C4 = mid_a_z;
        scratch->unk_B4 = mid_a_z;
        mid_b_z = (geometry->unk_84 + geometry->unk_8A) / 2;
        scratch->unk_CC = mid_b_z;
        scratch->unk_BC = mid_b_z;

        ot_index = RotAverage4(point_a, point_b, point_a_copy, point_b_copy,
                                 (u8 *)packet + 8, (u8 *)packet + 0xC,
                                 (u8 *)packet + 8, (u8 *)packet + 0xC,
                                 &scratch->depth_cue, &scratch->gte_flag) - (s16)saved_depth_bias - 6;
        scratch->unk_100 = ot_index;

        render_flags = scratch->unk_28;
        if (render_flags & 8) {
            if (render_flags & 4) {
                draw_flags = render_data->color.c.code | 2;
            } else {
                draw_flags = render_data->color.c.code & 0xFD;
            }
            render_data->color.c.code = draw_flags;
        }

        zero = 0;
        color = geometry->unk_00;
        packet->unk_00.at03.v = 3;
        packet->unk_04.at00.v = color;
        packet->unk_04.at03.v = 0x42;

        packet->unk_00.at00.v = (packet->unk_00.at00.v & length_mask) |
            ((*(u32 *)((u8 *)(scratch->unk_24)
                + scratch->unk_100 * 4)) & address_mask);
        (*(u32 *)((u8 *)(scratch->unk_24) + scratch->unk_100 * 4)) =
            ((*(u32 *)((u8 *)(scratch->unk_24)
                + scratch->unk_100 * 4)) & length_mask) |
            ((u32)packet & address_mask);

        packet = ((GpuContext *)(*render_state_ref))->packetCursor;
        ((GpuContext *)(*render_state_ref))->packetCursor = (u8 *)packet + 0xC;
        SetDrawMode(packet, zero, zero, GetTPage(zero, 1, zero, zero) & 0xFFFF, zero);

        packet->unk_00.at00.v = (packet->unk_00.at00.v & length_mask) |
            ((*(u32 *)((u8 *)(scratch->unk_24)
                + scratch->unk_100 * 4)) & address_mask);
        packet = (S_80166968_5 *)((u32)packet & address_mask);
        (*(u32 *)((u8 *)(scratch->unk_24) + scratch->unk_100 * 4)) =
            ((*(u32 *)((u8 *)(scratch->unk_24)
                + scratch->unk_100 * 4)) & length_mask) |
            (u32)packet;

        if (*texture_entry < 0) {
            break;
        }
        texture_entry += 0xC;
    }

    PopMatrix();
}
