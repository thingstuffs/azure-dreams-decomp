#include "common.h"
#include "shared/game_work.h"


extern s32 RotTransPers();
extern s32 GetTPage();
extern void SetSemiTrans();
extern void SetLineG2();
extern void SetDrawMode();
extern s32 rand();
struct MovingPosition; struct S_800A130C_0; void copy_odd_halfwords_3(struct S_800A130C_0 *, struct MovingPosition *);

typedef struct
{
    u8 pad0[0x24];
    u32 *ot;
    u8 pad28[0x4C];
    s16 start[4];
    s16 end[4];
    u8 pad84[0x10];
    s32 interp;
    s32 flag;
    u8 pad9C[0x28];
    s32 depth;
    u8 padC8[0x20];
    u16 start_x;
    u16 start_y;
    u16 end_x;
    u16 end_y;
} LineWork;

/* Queues a randomly colored line between two projected points with draw mode commands. */
void draw_random_colored_line(s32 end_point, s32 start_point)
{
    s32 end_pos = end_point;
    s32 start_pos = start_point;
    LineWork *scratch = (LineWork *)0x1F800000;
    u8 *draw_ctx;
    u32 *line;
    u32 *draw_mode;
    s32 color_factor;
    s32 color_factor_2;
    s32 depth_or_tpage;
    s32 depth_or_tpage_2;
    u32 low_mask = 0x00FFFFFF;
    u32 length_mask;
    s32 texture_depth;
    s32 texture_y;

    draw_ctx = (u8 *)g_game_work.draw_buffer;
    scratch->ot = (u32 *)(draw_ctx + 0xB0);
    line = *(u32 **)(draw_ctx + 0x8D0);
    *(u8 **)(draw_ctx + 0x8D0) = (u8 *)line + 0x14;

    color_factor = rand();
    line[1] = (color_factor * rand()) & low_mask;
    color_factor_2 = rand();
    line[3] = (color_factor_2 * rand()) & low_mask;

    SetLineG2(line);
    SetSemiTrans(line, 1);

    copy_odd_halfwords_3((struct S_800A130C_0 *)(scratch->start), (struct MovingPosition *)(start_pos));
    copy_odd_halfwords_3((struct S_800A130C_0 *)(scratch->end), (struct MovingPosition *)(end_pos));
    scratch->depth = RotTransPers(
        scratch->start, &scratch->start_x, &scratch->interp, &scratch->flag);
    RotTransPers(
        scratch->end, &scratch->end_x, &scratch->interp, &scratch->flag);

    {
        u16 start_x;
        depth_or_tpage_2 = scratch->depth;
        start_x = scratch->start_x;
        depth_or_tpage_2 -= 0x30;
        scratch->depth = depth_or_tpage_2;
        *(u16 *)((u8 *)line + 8) = start_x;
    }
    *(u16 *)((u8 *)line + 0xA) = scratch->start_y;
    *(u16 *)((u8 *)line + 0x10) = scratch->end_x;
    *(u16 *)((u8 *)line + 0x12) = scratch->end_y;

    if (scratch->depth >= 0x1E0) {
        scratch->depth = 0x1DF;
    }
    if (scratch->depth < 0) {
        scratch->depth = 0;
    }

    draw_ctx = (u8 *)g_game_work.draw_buffer;
    draw_mode = *(u32 **)(draw_ctx + 0x8D0);
    *(u8 **)(draw_ctx + 0x8D0) = (u8 *)draw_mode + 0xC;
    depth_or_tpage = GetTPage(0, 0, 0x140, 0);
    SetDrawMode(draw_mode, 1, 0, (u16)depth_or_tpage, 0);

    texture_depth = 0;
    length_mask = 0xFF000000;
    texture_y = 0;
    {
        u32 *ot_entry;
        ot_entry = (u32 *)(((u32)scratch->depth << 2) +
            (u32)scratch->ot);
        draw_mode[0] = (draw_mode[0] & length_mask) | (*ot_entry & low_mask);
    }
    {
        s32 ot_index = scratch->depth;
        u32 ot_tag = scratch->ot[ot_index];
        *(u32 *)((u8 *)scratch->ot + ot_index * 4) =
            (ot_tag & length_mask) | ((u32)draw_mode & low_mask);
    }

    {
        u32 ot_tag;
        ot_tag = scratch->ot[scratch->depth];
        line[0] = (line[0] & length_mask) | (ot_tag & low_mask);
    }
    {
        s32 ot_index = scratch->depth;
        u32 ot_tag = scratch->ot[ot_index];
        scratch->ot[ot_index] =
            (ot_tag & length_mask) | ((u32)line & low_mask);
    }

    draw_ctx = (u8 *)g_game_work.draw_buffer;
    draw_mode = *(u32 **)(draw_ctx + 0x8D0);
    *(u8 **)(draw_ctx + 0x8D0) = (u8 *)draw_mode + 0xC;
    depth_or_tpage = GetTPage(texture_depth, 1, 0x140, texture_y);
    SetDrawMode(draw_mode, 1, 0, (u16)depth_or_tpage, 0);

    {
        u32 *ot_entry =
            (u32 *)(((u32)scratch->depth << 2) +
                    (u32)scratch->ot);
        draw_mode[0] = (draw_mode[0] & length_mask) | (*ot_entry & low_mask);
    }
    {
        u32 ot_tag = scratch->ot[scratch->depth];
        scratch->ot[scratch->depth] =
            (ot_tag & length_mask) | ((u32)draw_mode & low_mask);
    }
}
