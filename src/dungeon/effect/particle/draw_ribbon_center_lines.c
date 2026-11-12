#include "shared/vector.h"
#include "dungeon/effect/particle.h"
#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"
#include "sdk/libgpu.h"
#include "sdk/libgte.h"
#include "sdk/libgte_matrix.h"

typedef struct S_80166968_0 {
    u8 pad_00[0x24];
    u8 *unk_24;
    u16 unk_28;
    u8 pad_2A[0xA];
    VECTOR scale; /* ScaleMatrix scale of the composed matrix */
    u8 pad_44[0x10];
    MATRIX composed_matrix; /* CompMatrix of the view matrix and object_matrix, scaled by +0x34 and installed */
    MATRIX object_matrix; /* RotMatrix of the angles at +0xA4; its translation is the integer position */
    u8 pad_94[0x10];
    SVECTOR angles; /* RotMatrix angles of object_matrix */
    u8 pad_AC[0x4];
    SVECTOR points[4]; /* RotAverage4 inputs: the two edge midpoints, each given twice */
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
    SVECTOR *point_a;
    SVECTOR *point_b;
    SVECTOR *point_a_copy;
    SVECTOR *point_b_copy;
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

    scratch->scale.vz = 0x2000;
    scratch->scale.vy = 0x2000;
    scratch->scale.vx = 0x2000;
    scratch->angles.vx = render_data->angle_x;
    scratch->angles.vz = render_data->angle_z;
    scratch->angles.vy = render_data->angle_y;
    RotMatrix(&scratch->angles, &scratch->object_matrix);
    ReadRotMatrix(&matrix);
    CompMatrix(&matrix, &scratch->object_matrix, &scratch->composed_matrix);
    ScaleMatrix(&scratch->composed_matrix, &scratch->scale);
    SetTransMatrix(&scratch->composed_matrix);
    SetRotMatrix(&scratch->composed_matrix);

    texture_entry = render_data->source;
    length_mask = 0xFF000000;
    scratch->unk_28 = render_data->flags;

    for (;;) {
        packet = ((GpuContext *)(*render_state_ref))->packetCursor;
        ((GpuContext *)(*render_state_ref))->packetCursor = (u8 *)packet + 0x10;

        point_a = &scratch->points[0];
        mid_a_x = (geometry->unk_74 + geometry->unk_7A) / 2;
        scratch->points[2].vx = mid_a_x;
        scratch->points[0].vx = mid_a_x;
        point_b = &scratch->points[1];
        mid_b_x = (geometry->unk_80 + geometry->unk_86) / 2;
        scratch->points[3].vx = mid_b_x;
        scratch->points[1].vx = mid_b_x;
        point_a_copy = &scratch->points[2];
        mid_a_y = (geometry->unk_76 + geometry->unk_7C) / 2;
        scratch->points[2].vy = mid_a_y;
        scratch->points[0].vy = mid_a_y;
        point_b_copy = &scratch->points[3];
        mid_b_y = (geometry->unk_82 + geometry->unk_88) / 2;
        scratch->points[3].vy = mid_b_y;
        scratch->points[1].vy = mid_b_y;
        mid_a_z = (geometry->unk_78 + geometry->unk_7E) / 2;
        scratch->points[2].vz = mid_a_z;
        scratch->points[0].vz = mid_a_z;
        mid_b_z = (geometry->unk_84 + geometry->unk_8A) / 2;
        scratch->points[3].vz = mid_b_z;
        scratch->points[1].vz = mid_b_z;

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
