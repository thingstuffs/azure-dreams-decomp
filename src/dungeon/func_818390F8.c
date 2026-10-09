#include "modules/dungeon_ovl_1858800.h"
#include "common.h"
#include "shared/game_work.h"



/* Advance the animation and enqueue a textured quad at the projected position. */
s32 func_800248F8(RenderRecord *render_record, PositionFields *position)
{
    SVECTOR world_point;
    s16 screen[4];
    GameWork *render_state = &gameWork;
    s16 *screen_base = screen;
    s32 half_width;
    s32 *projection_out = &half_width;
    RenderRecord *frame_record;
    u32 depth;
    s32 endpoint;
    s32 height;
    POLY_FT4 *poly;

next_record:
    world_point.x = position->x;
    frame_record = render_record;
    world_point.y = position->y;
    world_point.z = position->z - 14;

    for (endpoint = 0; endpoint < 2; endpoint++) {
        depth = func_80065420(&world_point, &screen_base[endpoint * 2], projection_out, projection_out) - 8;
        world_point.z += 28;
    }

    height = screen[1] - screen[3];
    if (++frame_record->frame >= 12) {
        frame_record->frame = 8;
    }

    if (depth < 480) {
        u8 tex_u;
        s32 tex_v;
        s32 ot_offset;

        poly = (POLY_FT4 *)((RenderContext *)render_state->unk_000)->next_prim;
        ((RenderContext *)render_state->unk_000)->next_prim = (u8 *)poly + sizeof(POLY_FT4);
        *(u32 *)&poly->r0 = 0x00808080;
        func_800666F4(poly);
        func_80066640(poly, 1);
        poly->tpage = func_80066460(0, 1, 0x2C0, 0x100);
        poly->clut = func_8006649C(0, 0x1F8);

        half_width = height >> 1;
        poly->x0 = poly->x1 = screen[0] + (u16)half_width;
        poly->x2 = poly->x3 = screen[0] - (u16)half_width;
        poly->y0 = poly->y2 = screen[1];
        poly->y1 = poly->y3 = screen[3];

        tex_u = frame_record->frame;
        ot_offset = depth << 2;
        tex_u = (tex_u & 3) << 5;
        poly->u0 = poly->u1 = tex_u;
        poly->u2 = poly->u3 = tex_u + 31;
        tex_v = ((s16)frame_record->frame >> 2) * 32;
        poly->v0 = poly->v2 = tex_v - 128;
        poly->v1 = poly->v3 = tex_v - 97;

        poly->tag = (poly->tag & 0xFF000000) |
                    (*(u32 *)((u8 *)((RenderContext *)render_state->unk_000) + 0xB0 + ot_offset) &
                     0x00FFFFFF);
        *(u32 *)((u8 *)((RenderContext *)render_state->unk_000) + 0xB0 + ot_offset) =
            (*(u32 *)((u8 *)((RenderContext *)render_state->unk_000) + 0xB0 + ot_offset) & 0xFF000000) |
            ((u32)poly & 0x00FFFFFF);
    }

    position = *(void **)((u8 *)render_record - 8);
    if (position != 0) {
        render_record = (RenderRecord *)((u8 *)position + 0x20);
        position = *(void **)((u8 *)position + 8);
        goto next_record;
    }
    return 0;
}

/* MECHANISM: Separate stack screen/pointer bases force the retail 0x50 frame and s7/s4 roles.
   A 40-byte FT4 plus uncached OT re-addressing restores the body length and reloads.
   The record walk is a loop whose top is the first statement after the prologue (retail
   word 15, the `j 0x80024934` back edge at word 137); the projection loop must index through
   `screen_base`, not through `screen` directly, or gcc materialises the array address again
   (`addiu $s0,$sp,0x18`) where retail copies the base register (`move $s0,$s7`). */
