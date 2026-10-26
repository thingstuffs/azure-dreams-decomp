#include "common.h"
#include "sdk/libgte.h"
#include "shared/gpu_packets.h"
#include "town/menu/line_effects.h"
#include "shared/game_work.h"
#include "sdk/libc.h"
#include "sdk/libgpu.h"



struct MovingPosition; struct S_800A130C_0; void copy_odd_halfwords_3(struct S_800A130C_0 *, struct MovingPosition *);


/* Queues a randomly colored line between two projected points with draw mode commands. */
void draw_random_colored_line(s32 end_point, s32 start_point)
{
    s32 end_pos = end_point;
    s32 start_pos = start_point;
    MenuLineScratch *scratch = (MenuLineScratch *)0x1F800000;
    GpuContext *draw_ctx;
    MenuLineG2 *line;
    u32 *draw_mode;
    s32 color_factor;
    s32 color_factor_2;
    s32 depth_or_tpage;
    s32 depth_or_tpage_2;
    u32 low_mask = 0x00FFFFFF;
    u32 length_mask;
    s32 texture_depth;
    s32 texture_y;

    draw_ctx = g_game_work.draw_buffer;
    scratch->order_table.words = &draw_ctx->orderTag;
    line = draw_ctx->packetCursor;
    draw_ctx->packetCursor = (u8 *)line + 0x14;

    color_factor = rand();
    line->vertices[0].color.word = (color_factor * rand()) & low_mask;
    color_factor_2 = rand();
    line->vertices[1].color.word = (color_factor_2 * rand()) & low_mask;

    SetLineG2(line);
    SetSemiTrans(line, 1);

    copy_odd_halfwords_3((struct S_800A130C_0 *)(scratch->vertices[0]), (struct MovingPosition *)(start_pos));
    copy_odd_halfwords_3((struct S_800A130C_0 *)(scratch->vertices[1]), (struct MovingPosition *)(end_pos));
    scratch->depth = RotTransPers(
        scratch->vertices[0], &scratch->screen.words[0], &scratch->interp, &scratch->flag);
    RotTransPers(
        scratch->vertices[1], &scratch->screen.words[1], &scratch->interp, &scratch->flag);

    {
        u16 start_x;
        depth_or_tpage_2 = scratch->depth;
        start_x = scratch->screen.halves[0][0];
        depth_or_tpage_2 -= 0x30;
        scratch->depth = depth_or_tpage_2;
        line->vertices[0].x = start_x;
    }
    line->vertices[0].y = scratch->screen.halves[0][1];
    line->vertices[1].x = scratch->screen.halves[1][0];
    line->vertices[1].y = scratch->screen.halves[1][1];

    if (scratch->depth >= 0x1E0) {
        scratch->depth = 0x1DF;
    }
    if (scratch->depth < 0) {
        scratch->depth = 0;
    }

    draw_ctx = g_game_work.draw_buffer;
    draw_mode = draw_ctx->packetCursor;
    draw_ctx->packetCursor = (u8 *)draw_mode + 0xC;
    depth_or_tpage = GetTPage(0, 0, 0x140, 0);
    SetDrawMode(draw_mode, 1, 0, (u16)depth_or_tpage, 0);

    texture_depth = 0;
    length_mask = 0xFF000000;
    texture_y = 0;
    {
        u32 *ot_entry;
        ot_entry = (u32 *)(((u32)scratch->depth << 2) +
            (u32)scratch->order_table.words);
        draw_mode[0] = (draw_mode[0] & length_mask) | (*ot_entry & low_mask);
    }
    {
        s32 ot_index = scratch->depth;
        u32 ot_tag = scratch->order_table.words[ot_index];
        *(u32 *)((u8 *)scratch->order_table.words + ot_index * 4) =
            (ot_tag & length_mask) | ((u32)draw_mode & low_mask);
    }

    {
        u32 ot_tag;
        ot_tag = scratch->order_table.words[scratch->depth];
        line->tag = (line->tag & length_mask) | (ot_tag & low_mask);
    }
    {
        s32 ot_index = scratch->depth;
        u32 ot_tag = scratch->order_table.words[ot_index];
        scratch->order_table.words[ot_index] =
            (ot_tag & length_mask) | ((u32)line & low_mask);
    }

    draw_ctx = g_game_work.draw_buffer;
    draw_mode = draw_ctx->packetCursor;
    draw_ctx->packetCursor = (u8 *)draw_mode + 0xC;
    depth_or_tpage = GetTPage(texture_depth, 1, 0x140, texture_y);
    SetDrawMode(draw_mode, 1, 0, (u16)depth_or_tpage, 0);

    {
        u32 *ot_entry =
            (u32 *)(((u32)scratch->depth << 2) +
                    (u32)scratch->order_table.words);
        draw_mode[0] = (draw_mode[0] & length_mask) | (*ot_entry & low_mask);
    }
    {
        u32 ot_tag = scratch->order_table.words[scratch->depth];
        scratch->order_table.words[scratch->depth] =
            (ot_tag & length_mask) | ((u32)draw_mode & low_mask);
    }
}
