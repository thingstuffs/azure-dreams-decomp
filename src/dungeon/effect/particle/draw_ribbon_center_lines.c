#include "dungeon/effect/particle.h"
#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"

typedef struct S_80166968_0 {
    u8 pad_00[0x24];
    union { u8 * p; u32 * p2; } unk_24;   /* accessed as both */
    u16 unk_28;
    u8 pad_2A[0xA];
    s32 unk_34;
    s32 unk_38;
    s32 unk_3C;
    u8 pad_40[0x48];
    s32 unk_88;
    s32 unk_8C;
    s32 unk_90;
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
    u8 pad_CE[0x32];
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

typedef struct {
    s16 m[3][3];
    s16 pad;
    s32 t[3];
} MATRIX;

extern void CompMatrix(void *, void *, void *);
extern void PushMatrix(void);
extern void PopMatrix(void);
extern void ReadRotMatrix(void *);
extern void ScaleMatrix(void *, void *);
extern void SetRotMatrix(void *);
extern void SetTransMatrix(void *);
extern s32 RotAverage4(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern void RotMatrix(void *, void *);
extern u16 GetTPage(s32, s32, s32, s32);
extern void SetDrawMode(void *, s32, s32, u16, s32);

/* Project edge midpoints and queue line and draw-mode packets in the ordering table. */
void draw_ribbon_center_lines(RibbonLineGeometry *geometry, ObjectPosition *position, SpriteFrameState *render_data, s32 depth_bias)
{
    u8 *scratch = (u8 *)0x1F800000;
    u8 *render_state = g_game_work.draw_buffer;
    u32 draw_flags;
    void **render_state_ref;
    u8 *packet;
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

    ((S_80166968_0 *)scratch)->unk_24.p = render_state + 0xB0;
    address_mask = 0x00FFFFFF;
    ((S_80166968_0 *)scratch)->unk_88 = position->x.w.i;
    ((S_80166968_0 *)scratch)->unk_8C = position->y.w.i;
    saved_depth_bias = depth_bias;
    ((S_80166968_0 *)scratch)->unk_90 = position->z.w.i;
    render_data->flags |= 0x8000;
    render_state_ref = &g_game_work.draw_buffer;
    PushMatrix();

    ((S_80166968_0 *)scratch)->unk_3C = 0x2000;
    ((S_80166968_0 *)scratch)->unk_38 = 0x2000;
    ((S_80166968_0 *)scratch)->unk_34 = 0x2000;
    ((S_80166968_0 *)scratch)->unk_A4 = render_data->angle_x;
    ((S_80166968_0 *)scratch)->unk_A8 = render_data->angle_z;
    ((S_80166968_0 *)scratch)->unk_A6 = render_data->angle_y;
    RotMatrix(scratch + 0xA4, scratch + 0x74);
    ReadRotMatrix(&matrix);
    CompMatrix(&matrix, scratch + 0x74, scratch + 0x54);
    ScaleMatrix(scratch + 0x54, scratch + 0x34);
    SetTransMatrix(scratch + 0x54);
    SetRotMatrix(scratch + 0x54);

    texture_entry = render_data->source;
    length_mask = 0xFF000000;
    ((S_80166968_0 *)scratch)->unk_28 = render_data->flags;

    for (;;) {
        packet = ((GpuContext *)(*render_state_ref))->packetCursor;
        ((GpuContext *)(*render_state_ref))->packetCursor = packet + 0x10;

        point_a = scratch + 0xB0;
        mid_a_x = (geometry->unk_74 + geometry->unk_7A) / 2;
        ((S_80166968_0 *)scratch)->unk_C0 = mid_a_x;
        ((S_80166968_0 *)scratch)->unk_B0 = mid_a_x;
        point_b = scratch + 0xB8;
        mid_b_x = (geometry->unk_80 + geometry->unk_86) / 2;
        ((S_80166968_0 *)scratch)->unk_C8 = mid_b_x;
        ((S_80166968_0 *)scratch)->unk_B8 = mid_b_x;
        point_a_copy = scratch + 0xC0;
        mid_a_y = (geometry->unk_76 + geometry->unk_7C) / 2;
        ((S_80166968_0 *)scratch)->unk_C2 = mid_a_y;
        ((S_80166968_0 *)scratch)->unk_B2 = mid_a_y;
        point_b_copy = scratch + 0xC8;
        mid_b_y = (geometry->unk_82 + geometry->unk_88) / 2;
        ((S_80166968_0 *)scratch)->unk_CA = mid_b_y;
        ((S_80166968_0 *)scratch)->unk_BA = mid_b_y;
        mid_a_z = (geometry->unk_78 + geometry->unk_7E) / 2;
        ((S_80166968_0 *)scratch)->unk_C4 = mid_a_z;
        ((S_80166968_0 *)scratch)->unk_B4 = mid_a_z;
        mid_b_z = (geometry->unk_84 + geometry->unk_8A) / 2;
        ((S_80166968_0 *)scratch)->unk_CC = mid_b_z;
        ((S_80166968_0 *)scratch)->unk_BC = mid_b_z;

        ot_index = RotAverage4(point_a, point_b, point_a_copy, point_b_copy,
                                 packet + 8, packet + 0xC,
                                 packet + 8, packet + 0xC,
                                 scratch + 0xD0, scratch + 0xD4) - (s16)saved_depth_bias - 6;
        ((S_80166968_0 *)scratch)->unk_100 = ot_index;

        render_flags = ((S_80166968_0 *)scratch)->unk_28;
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
        ((S_80166968_5 *)packet)->unk_00.at03.v = 3;
        ((S_80166968_5 *)packet)->unk_04.at00.v = color;
        ((S_80166968_5 *)packet)->unk_04.at03.v = 0x42;

        ((S_80166968_5 *)packet)->unk_00.at00.v = (((S_80166968_5 *)packet)->unk_00.at00.v & length_mask) |
            ((*(u32 *)((u8 *)(((S_80166968_0 *)scratch)->unk_24.p2)
                + ((S_80166968_0 *)scratch)->unk_100 * 4)) & address_mask);
        (*(u32 *)((u8 *)(((S_80166968_0 *)scratch)->unk_24.p2) + ((S_80166968_0 *)scratch)->unk_100 * 4)) =
            ((*(u32 *)((u8 *)(((S_80166968_0 *)scratch)->unk_24.p2)
                + ((S_80166968_0 *)scratch)->unk_100 * 4)) & length_mask) |
            ((u32)packet & address_mask);

        packet = ((GpuContext *)(*render_state_ref))->packetCursor;
        ((GpuContext *)(*render_state_ref))->packetCursor = packet + 0xC;
        SetDrawMode(packet, zero, zero, GetTPage(zero, 1, zero, zero) & 0xFFFF, zero);

        ((S_80166968_5 *)packet)->unk_00.at00.v = (((S_80166968_5 *)packet)->unk_00.at00.v & length_mask) |
            ((*(u32 *)((u8 *)(((S_80166968_0 *)scratch)->unk_24.p2)
                + ((S_80166968_0 *)scratch)->unk_100 * 4)) & address_mask);
        packet = (u8 *)((u32)packet & address_mask);
        (*(u32 *)((u8 *)(((S_80166968_0 *)scratch)->unk_24.p2) + ((S_80166968_0 *)scratch)->unk_100 * 4)) =
            ((*(u32 *)((u8 *)(((S_80166968_0 *)scratch)->unk_24.p2)
                + ((S_80166968_0 *)scratch)->unk_100 * 4)) & length_mask) |
            (u32)packet;

        if (*texture_entry < 0) {
            break;
        }
        texture_entry += 0xC;
    }

    PopMatrix();
}
