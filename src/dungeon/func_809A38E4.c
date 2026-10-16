#include "modules/dungeon_ovl_9c32d4.h"

static __inline__ s16 project_ring_coordinate(s32 radius, s32 trig, u16 center)
{
    return center + ((radius * trig) >> 8);
}

/* Emit colored quads between two concentric elliptical arcs. */
void dungeonEmitConcentricEllipseQuads(u16 radius_a_x, u16 radius_a_y, u16 radius_b_x, u16 radius_b_y,
                   u16 center_x, s16 center_y, s32 *color_b_ptr, s32 *color_a_ptr,
                   s32 draw_bucket, s32 start_segment, s32 end_segment)
{
    ovl_9c32d4_809A38E4_RingRadii radii;
    union { u16 v; } segment_limit = {0};
    u16 segment;
    s32 scale_b_x;
    s32 scale_b_y;
    s32 scale_a_x;
    s32 scale_a_y;
    s32 angle;
    s32 sin_angle;
    s32 cos_angle;
    s32 prev_sin;
    s32 prev_cos;
    u8 *prim;
    u8 *submit_prim;
    u8 *next_vertex;
    u8 *vertex_data;
    ovl_9c32d4_809A38E4_GraphicsState **graphics_ptr;
    ovl_9c32d4_809A38E4_GraphicsState *graphics;
    u16 next_segment;
    s32 outer_prev_x;
    s32 outer_prev_y;
    s32 outer_next_x;
    s32 outer_next_y;
    s32 inner_prev_x;
    s32 inner_prev_y;
    s32 inner_next_x;
    s32 inner_next_y;

    s32 color_b;
    s32 color_a;

    vertex_data = (u8 *)((s16)start_segment);
    angle = (s32)vertex_data << 7;
    radii.inner_x = radius_a_x;
    graphics_ptr = &gameWork.unk_000;
    graphics = *graphics_ptr;
    graphics = (ovl_9c32d4_809A38E4_GraphicsState *)((u8 *)graphics + 0x8D0);
    prim = *(u8 **)graphics;
    radii.inner_y = radius_a_y;
    radii.outer_x = radius_b_x;
    radii.outer_y = radius_b_y;
    sin_angle = func_80064584(angle) >> 4;
    cos_angle = func_800644B8(angle) >> 4;
    segment_limit.v = end_segment;
    segment = start_segment;

    vertex_data = (u8 *)((s32)vertex_data < (s16)end_segment);
    if (vertex_data != 0) {
        scale_b_x = radii.outer_x;
        scale_b_y = radii.outer_y;
        scale_a_x = radii.inner_x;
        do {
            scale_a_y = radii.inner_y;
            vertex_data = prim + 0x1A;
        } while (0);
        do {
            angle += 0x80;
            prev_sin = sin_angle;
            sin_angle = func_80064584(angle) >> 4;
            prev_cos = cos_angle;
            cos_angle = func_800644B8(angle);
            cos_angle = cos_angle >> 4;

            color_b = *color_b_ptr;
            (*(u32 *)((u8 *)vertex_data + -0x0A)) = color_b;
            (*(u32 *)((u8 *)vertex_data + -0x16)) = color_b;
            color_a = *color_a_ptr;
            (*(u32 *)((u8 *)vertex_data + 0x0E)) = color_a;
            (*(u32 *)((u8 *)vertex_data + 0x02)) = color_a;
            func_8006671C(prim);

            ((ovl_9c32d4_809A38E4_S_801750E4_0 *)vertex_data)->unk_0A = 1;
            ((ovl_9c32d4_809A38E4_S_801750E4_0_pre *)vertex_data)[-1].unk_04 = 1;
            ((ovl_9c32d4_809A38E4_S_801750E4_0 *)vertex_data)->unk_16 = 2;
            ((ovl_9c32d4_809A38E4_S_801750E4_0_pre *)vertex_data)[-1].unk_10 = 2;
            ((ovl_9c32d4_809A38E4_S_801750E4_0_pre *)vertex_data)[-1].unk_11 = 0xFB;
            ((ovl_9c32d4_809A38E4_S_801750E4_0_pre *)vertex_data)[-1].unk_05 = 0xFB;
            ((ovl_9c32d4_809A38E4_S_801750E4_0 *)vertex_data)->unk_17 = 0xFB;
            ((ovl_9c32d4_809A38E4_S_801750E4_0 *)vertex_data)->unk_0B = 0xFB;

            outer_prev_x = project_ring_coordinate(scale_b_x, prev_sin, center_x);
            ((ovl_9c32d4_809A38E4_S_801750E4_0_pre *)vertex_data)[-1].unk_00 = outer_prev_x;
            outer_prev_y = project_ring_coordinate(scale_b_y, prev_cos, center_y);
            ((ovl_9c32d4_809A38E4_S_801750E4_0_pre *)vertex_data)[-1].unk_02 = outer_prev_y;
            outer_next_x = project_ring_coordinate(scale_b_x, sin_angle, center_x);
            ((ovl_9c32d4_809A38E4_S_801750E4_0_pre *)vertex_data)[-1].unk_0C = outer_next_x;
            outer_next_y = project_ring_coordinate(scale_b_y, cos_angle, center_y);
            ((ovl_9c32d4_809A38E4_S_801750E4_0_pre *)vertex_data)[-1].unk_0E = outer_next_y;
            inner_prev_x = project_ring_coordinate(scale_a_x, prev_sin, center_x);
            ((ovl_9c32d4_809A38E4_S_801750E4_0 *)vertex_data)->unk_06 = inner_prev_x;
            inner_prev_y = project_ring_coordinate(scale_a_y, prev_cos, center_y);
            ((ovl_9c32d4_809A38E4_S_801750E4_0 *)vertex_data)->unk_08 = inner_prev_y;
            inner_next_x = project_ring_coordinate(scale_a_x, sin_angle, center_x);
            ((ovl_9c32d4_809A38E4_S_801750E4_0 *)vertex_data)->unk_12 = inner_next_x;
            inner_next_y = project_ring_coordinate(scale_a_y, cos_angle, center_y);
            ((ovl_9c32d4_809A38E4_S_801750E4_0 *)vertex_data)->unk_14 = inner_next_y;

            ((ovl_9c32d4_809A38E4_S_801750E4_0 *)vertex_data)->unk_00 = 0x133;

            submit_prim = prim;
            func_8006658C(draw_bucket, submit_prim);
            prim += sizeof(ovl_9c32d4_809A38E4_Block);
            next_vertex = vertex_data + sizeof(ovl_9c32d4_809A38E4_Block);
            next_segment = segment;
            next_segment += 1;
            vertex_data = next_vertex;
            segment = next_segment;
        } while (((s32)(u32)next_segment << 16) < ((s32)(u32)segment_limit.v << 16));
    }
    (*graphics_ptr)->next_prim = prim;
}
