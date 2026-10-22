/* Builds a menu ring from sixteen segments between two radii around a shared center. */
#include "shared/sprite_frame_state.h"
/* inferred-strong G00568: shaded_quad_projection_g00568; joins CL:town/func_800A56D0; no crossing cuts. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800A56D0. */
#include "town/menu/shaded_quad_projection_g00568.h"
#include "shared/game_work.h"

/* Project and enqueue a shaded quad, then enqueue its draw mode packet. */
/* C89 promotes the u16 parameter object to the shared s32 prototype. */
void project_and_enqueue_shaded_quad(vertex_0, vertex_1, vertex_2, vertex_3, shade)
    Coord8 vertex_0, vertex_1;
    Packed8 vertex_2, vertex_3;
    u16 shade;
{
    OutputPair screen_0;
    OutputPair screen_1;
    OutputPair screen_2;
    OutputPair screen_3;
    u32 depth_cue;
    u32 transform_flags;
    s32 depth_or_page;
    u8 *draw_ctx;
    u8 *packet;

    {
        u8 *quad_ctx;

        quad_ctx = *(u8 **)&g_game_work.draw_buffer;
        packet = ((GpuContext *)quad_ctx)->packetCursor;
        ((GpuContext *)quad_ctx)->packetCursor = packet + 0x24;
        ((S_800A2E30_1 *)packet)->unk_16 = shade;
        ((S_800A2E30_1 *)packet)->unk_15 = shade;
        ((S_800A2E30_1 *)packet)->unk_14 = shade;
        ((S_800A2E30_1 *)packet)->unk_06 = shade;
        ((S_800A2E30_1 *)packet)->unk_05 = shade;
        ((S_800A2E30_1 *)packet)->unk_04 = shade;
        ((S_800A2E30_1 *)packet)->unk_1E = 0;
        ((S_800A2E30_1 *)packet)->unk_1D = 0;
        ((S_800A2E30_1 *)packet)->unk_1C = 0;
        ((S_800A2E30_1 *)packet)->unk_0E = 0;
        ((S_800A2E30_1 *)packet)->unk_0D = 0;
        ((S_800A2E30_1 *)packet)->unk_0C = 0;
        func_80066708(packet);
    }
    func_80066640(packet, 1);

    depth_or_page = func_800654B0((InputPair *)&vertex_0, (InputPair *)&vertex_1, (InputPair *)&vertex_2, (InputPair *)&vertex_3,
                          &screen_0, &screen_1, &screen_2, &screen_3, &depth_cue, &transform_flags);

    ((S_800A2E30_1 *)packet)->unk_08 = screen_0.first;
    ((S_800A2E30_1 *)packet)->unk_0A = screen_0.second;
    ((S_800A2E30_1 *)packet)->unk_10 = screen_1.first;
    ((S_800A2E30_1 *)packet)->unk_12 = screen_1.second;
    ((S_800A2E30_1 *)packet)->unk_18 = screen_2.first;
    ((S_800A2E30_1 *)packet)->unk_1A = screen_2.second;
    ((S_800A2E30_1 *)packet)->unk_20 = screen_3.first;
    ((S_800A2E30_1 *)packet)->unk_22 = screen_3.second;

    if (depth_or_page >= 0x1E0) {
        depth_or_page = 0x1DF;
    }
    if (depth_or_page < 0) {
        depth_or_page = 0;
    }

    func_8006658C(*(u8 **)&g_game_work.draw_buffer + 0xD8, packet);

    draw_ctx = *(u8 **)&g_game_work.draw_buffer;
    packet = ((GpuContext *)draw_ctx)->packetCursor;
    ((GpuContext *)draw_ctx)->packetCursor = packet + 0xC;
    depth_or_page = func_80066460(0, 1, 0x140, 0);
    func_80067F20(packet, 0, 0, (u16)depth_or_page, 0);

    func_8006658C(*(u8 **)&g_game_work.draw_buffer + 0xD8, packet);
}

static __inline__ s16 scale_trig(s32 trig, s32 radius)
{
    return (trig * radius) >> 16;
}

static __inline__ s16 offset_coord(s16 base, s32 offset)
{
    return base + offset;
}

/* Builds 16 segments between two radii around a shared center. */
void draw_segmented_menu_ring(s32 center_source, s32 radius_a, s32 radius_b, s16 segment_arg)
{
    Coord8 center;
    Coord8 prev_a;
    Coord8 prev_b;
    Coord8 point_a;
    Coord8 point_b;
    Coord8 *start_a;
    Coord8 *start_b;
    register Coord8 *point_a_ptr;
    Coord8 *point_b_ptr;
    register s32 angle;
    s32 segment_count;

    copy_odd_halfwords_3(&center, center_source);
    start_a = &point_a;
    copy_menu_vector_halfwords(start_a, &center);
    start_b = &point_b;
    copy_menu_vector_halfwords(start_b, &center);
    point_a.h[0] = offset_coord(point_a.h[0], scale_trig(func_800644B8(0), radius_a));
    point_a.h[1] = offset_coord(point_a.h[1], scale_trig(func_80064584(0), radius_a));
    point_b.h[0] = offset_coord(point_b.h[0], scale_trig(func_800644B8(0), radius_b));
    point_b.h[1] = offset_coord(point_b.h[1], scale_trig(func_80064584(0), radius_b));
    angle = 0;
    segment_count = 0;
    point_a_ptr = start_a;
    point_b_ptr = start_b;

    {
        s32 upper_mask = 0xFFFF0000;

        do {
            copy_menu_vector_halfwords(&prev_a, point_a_ptr);
            copy_menu_vector_halfwords(&prev_b, point_b_ptr);
            angle += 0x100;
            copy_menu_vector_halfwords(point_a_ptr, &center);
            copy_menu_vector_halfwords(point_b_ptr, &center);
            point_a.h[0] = offset_coord(point_a.h[0], scale_trig(func_800644B8(angle), radius_a));
            point_a.h[1] = offset_coord(point_a.h[1], scale_trig(func_80064584(angle), radius_a));
            point_b.h[0] = offset_coord(point_b.h[0], scale_trig(func_800644B8(angle), radius_b));
            segment_count++;
            point_b.h[1] = offset_coord(point_b.h[1], scale_trig(func_80064584(angle), radius_b));
            project_and_enqueue_shaded_quad(prev_a, prev_b,
                          *(Packed8 *)&point_a,
                          *(Packed8 *)&point_b,
                          segment_arg);
        } while (segment_count < 0x10);
    }
}
