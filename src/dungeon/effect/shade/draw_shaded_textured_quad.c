#include "common.h"
#include "shared/game_work.h"
#include "records/Rec_D_80083160.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/effect/shade.h"
#include "sdk/libgpu.h"
#include "sdk/libgte.h"

#include "sdk/libgpu_types.h"
#include "sdk/libgpu_packets.h"
#include "shared/gpu_packets.h"
#include "dungeon/effect/projected_quad_scratch.h"

   /* (sc) in draw_shaded_textured_quad */

   /* angle_addr in draw_shaded_textured_quad */


   /* arg1 in draw_shaded_textured_quad */


typedef struct S_818C29D4_6 {
    u8 pad_00[0x4];
    s16 unk_04;
    u8 pad_06[0x2];
    u16 unk_08;
    u8 unk_0A;
} S_818C29D4_6;   /* arg0 in draw_shaded_textured_quad */


/* Builds and queues a shaded textured quad with texture-window commands. */
s32 draw_shaded_textured_quad(S_818C29D4_6 *sprite, MovingPosition *position)
{
    ProjectedQuadScratch *scratch = (ProjectedQuadScratch *)0x1F800000;
    s32 angle;
    s32 axis_offset;
    s16 texture_v;
    s32 vertex_coord;
    POLY_GT4 *poly;
    RECT texture_window;
    u32 ot_index;
    s32 tex_depth;
    s32 blend_mode;
    s32 page_x;

    angle = g_game_work.view.camera_rotation.parts.viewAngle;
    scratch->ordering_table = (u32 *)((u8 *)g_game_work.draw_buffer + 0xB0);
    axis_offset = ((rcos(angle) >> 4) * 36) >> 8;
    vertex_coord = position->x - axis_offset;
    scratch->vertices[2].vx = vertex_coord;
    scratch->vertices[0].vx = vertex_coord;
    vertex_coord = position->x + axis_offset;
    scratch->vertices[3].vx = vertex_coord;
    scratch->vertices[1].vx = vertex_coord;
    axis_offset = ((rsin(angle) >> 4) * 36) >> 8;
    vertex_coord = position->y + axis_offset;
    scratch->vertices[2].vy = vertex_coord;
    scratch->vertices[0].vy = vertex_coord;
    vertex_coord = position->y - axis_offset;
    scratch->vertices[3].vy = vertex_coord;
    scratch->vertices[1].vy = vertex_coord;
    vertex_coord = position->z - 0x80;
    scratch->vertices[1].vz = vertex_coord;
    scratch->vertices[0].vz = vertex_coord;
    vertex_coord = position->z;
    scratch->vertices[2].vz = vertex_coord;
    scratch->vertices[3].vz = vertex_coord;
    poly = ((GpuContext *)g_game_work.draw_buffer)->packetCursor;
    ((GpuContext *)g_game_work.draw_buffer)->packetCursor = poly + 1;
    ((GpuLinkTag *)&poly->tag)->len = 12;
    poly->code = 0x3E;
    poly->tpage = GetTPage(0, 1, 0x280, 0x100);
    poly->clut = sprite->unk_08;
    poly->r0 = 0; poly->g0 = 0; poly->b0 = 0;
    poly->r1 = 0; poly->g1 = 0; poly->b1 = 0;
    poly->r2 = sprite->unk_0A;
    poly->g2 = sprite->unk_0A;
    poly->b2 = sprite->unk_0A;
    poly->r3 = sprite->unk_0A;
    poly->g3 = sprite->unk_0A;
    poly->b3 = sprite->unk_0A;
    texture_v = (sprite->unk_04 % 4) << 3;
    poly->u0 = 0; poly->v0 = texture_v;
    poly->u1 = 0x3F; poly->v1 = texture_v;
    poly->u2 = 0x3F; poly->v2 = texture_v + 0x3F;
    poly->u3 = 0; poly->v3 = texture_v + 0x3F;
    ot_index = RotAverage4(
        &scratch->vertices[0], &scratch->vertices[1], &scratch->vertices[2], &scratch->vertices[3],
        (s32 *)&scratch->screen[0], (s32 *)&scratch->screen[1],
        (s32 *)&scratch->screen[2], (s32 *)&scratch->screen[3],
        &scratch->depth_cue, &scratch->gte_flag);
    scratch->ot_index = ot_index;
    poly->x0 = scratch->screen[0].x;
    poly->y0 = scratch->screen[0].y;
    poly->x1 = scratch->screen[1].x;
    poly->y1 = scratch->screen[1].y;
    poly->x2 = scratch->screen[2].x;
    poly->y2 = scratch->screen[2].y;
    poly->x3 = scratch->screen[3].x;
    poly->y3 = scratch->screen[3].y;
    if (scratch->ot_index < 0x1E0U) {
        DR_MODE *draw_mode;
        DR_MODE *draw_mode_2;
        s32 reset_depth;
        s32 reset_blend;
        s32 reset_page_x;
        s32 reset_page_y;
        reset_depth = 0; reset_blend = 1; reset_page_x = 0x280; reset_page_y = 0x100;
        texture_window.y = 0; texture_window.x = 0; texture_window.h = 0xFF; texture_window.w = 0xFF;
        draw_mode = ((GpuContext *)g_game_work.draw_buffer)->packetCursor;
        ((GpuContext *)g_game_work.draw_buffer)->packetCursor = draw_mode + 1;
        SetDrawMode(draw_mode, 0, 0,
                     GetTPage(reset_depth, reset_blend, reset_page_x, reset_page_y) & 0xFFFF,
                     &texture_window);
        tex_depth = 0; blend_mode = 1; page_x = 0x280;
        { u32 *ot;
            ot = (u32 *)((scratch->ot_index << 2) + (u32)scratch->ordering_table);
            ((GpuLinkTag *)draw_mode)->addr = ((GpuLinkTag *)ot)->addr; }
        { u32 *ot;
            ot = (u32 *)((scratch->ot_index << 2) + (u32)scratch->ordering_table);
            ((GpuLinkTag *)ot)->addr = (u32)draw_mode; }
        { u32 *ot;
            ot = (u32 *)((scratch->ot_index << 2) + (u32)scratch->ordering_table);
            ((GpuLinkTag *)poly)->addr = ((GpuLinkTag *)ot)->addr; }
        { u32 *ot;
            ot = (u32 *)((scratch->ot_index << 2) + (u32)scratch->ordering_table);
            ((GpuLinkTag *)ot)->addr = (u32)poly; }
        texture_window.y = 0x80; texture_window.x = 0; texture_window.h = 0x40; texture_window.w = 0x40;
        draw_mode_2 = ((GpuContext *)g_game_work.draw_buffer)->packetCursor;
        ((GpuContext *)g_game_work.draw_buffer)->packetCursor = draw_mode_2 + 1;
        SetDrawMode(draw_mode_2, 0, 0,
                     GetTPage(tex_depth, blend_mode, page_x, 0x100) & 0xFFFF, &texture_window);
        { u32 *ot;
            ot = (u32 *)((scratch->ot_index << 2) + (u32)scratch->ordering_table);
            ((GpuLinkTag *)draw_mode_2)->addr = ((GpuLinkTag *)ot)->addr; }
        { u32 *ot;
            ot = (u32 *)((scratch->ot_index << 2) + (u32)scratch->ordering_table);
            ((GpuLinkTag *)ot)->addr = (u32)draw_mode_2; }
    }
    return 0;
}
