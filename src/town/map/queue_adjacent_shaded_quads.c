#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"
#include "sdk/libgpu.h"
#include "sdk/libgpu_packets.h"
#include "sdk/libgpu_types.h"
#include "town/map.h"
#include "town/map/effect.h"

/* Queue two adjoining shaded quads whose vertices fall within the screen margin. */
void queue_adjacent_shaded_quads(TownRingProjection *strip)
{
    POLY_G4 *poly;
    DR_MODE *tpage;
    GameWork *render_state_ptr = &g_game_work;

    if ((((u16)(strip->inner_xy + 0x20U) < 0x181) &&
         ((u16)(((u32)strip->inner_xy >> 16) + 0x20) < 0x121)) |
        (((u16)(strip->middle_xy + 0x20U) < 0x181) &&
         ((u16)(((u32)strip->middle_xy >> 16) + 0x20) < 0x121)) |
        (((u16)(strip->previous_inner_xy + 0x20U) < 0x181) &&
         ((u16)(((u32)strip->previous_inner_xy >> 16) + 0x20) < 0x121)) |
        (((u16)(strip->previous_middle_xy + 0x20U) < 0x181) &&
         ((u16)(((u32)strip->previous_middle_xy >> 16) + 0x20) < 0x121))) {
        GpuContext *poly_state;
        GpuContext *tpage_state;

        poly_state = render_state_ptr->draw_buffer;
        poly = poly_state->packetCursor;
        poly_state->packetCursor = poly + 1;

        /* BYTES: retail stores each vertex colour word (red, green, blue and the next byte) with one sw; member stores compile to sb sequences */
        *(u32 *)&poly->red0 = 0x383838;
        /* BYTES: retail stores each vertex colour word (red, green, blue and the next byte) with one sw; member stores compile to sb sequences */
        *(u32 *)&poly->red1 = strip->color.unsigned_word;
        /* BYTES: retail stores each vertex colour word (red, green, blue and the next byte) with one sw; member stores compile to sb sequences */
        *(u32 *)&poly->red2 = 0x383838;
        /* BYTES: retail stores each vertex colour word (red, green, blue and the next byte) with one sw; member stores compile to sb sequences */
        *(u32 *)&poly->red3 = strip->previous_color.unsigned_word;
        SetPolyG4(poly);
        SetSemiTrans(poly, 1);

        poly->tag = (poly->tag & 0xFF000000) |
                    (strip->ordering_table[strip->depth_index] & 0x00FFFFFF);
        strip->ordering_table[strip->depth_index] =
            (strip->ordering_table[strip->depth_index] & 0xFF000000) |
            ((u32)poly & 0x00FFFFFF);

        poly->x0 = strip->inner_xy;
        poly->y0 = (u32)strip->inner_xy >> 16;
        poly->x1 = strip->middle_xy;
        poly->y1 = (u32)strip->middle_xy >> 16;
        poly->x2 = strip->previous_inner_xy;
        poly->y2 = (u32)strip->previous_inner_xy >> 16;
        poly->x3 = strip->previous_middle_xy;
        poly->y3 = (u32)strip->previous_middle_xy >> 16;

        tpage_state = render_state_ptr->draw_buffer;
        tpage = tpage_state->packetCursor;
        tpage_state->packetCursor = tpage + 1;
        SetDrawMode(tpage, 1, 0, GetTPage(0, 1, 0x140, 0), 0);
        AddPrim(strip->ordering_table + strip->depth_index, tpage);
    }

    if ((((u16)(strip->middle_xy + 0x20U) < 0x181) &&
         ((u16)(((u32)strip->middle_xy >> 16) + 0x20) < 0x121)) |
        (((u16)(strip->outer_xy + 0x20U) < 0x181) &&
         ((u16)(((u32)strip->outer_xy >> 16) + 0x20) < 0x121)) |
        (((u16)(strip->previous_middle_xy + 0x20U) < 0x181) &&
         ((u16)(((u32)strip->previous_middle_xy >> 16) + 0x20) < 0x121)) |
        (((u16)(strip->previous_outer_xy + 0x20U) < 0x181) &&
         ((u16)(((u32)strip->previous_outer_xy >> 16) + 0x20) < 0x121))) {
        GpuContext *poly_state;
        GpuContext *tpage_state;

        poly_state = render_state_ptr->draw_buffer;
        poly = poly_state->packetCursor;
        poly_state->packetCursor = poly + 1;

        /* BYTES: retail stores each vertex colour word (red, green, blue and the next byte) with one sw; member stores compile to sb sequences */
        *(u32 *)&poly->red0 = strip->color.unsigned_word;
        /* BYTES: retail stores each vertex colour word (red, green, blue and the next byte) with one sw; member stores compile to sb sequences */
        *(u32 *)&poly->red1 = 0;
        /* BYTES: retail stores each vertex colour word (red, green, blue and the next byte) with one sw; member stores compile to sb sequences */
        *(u32 *)&poly->red2 = strip->previous_color.unsigned_word;
        /* BYTES: retail stores each vertex colour word (red, green, blue and the next byte) with one sw; member stores compile to sb sequences */
        *(u32 *)&poly->red3 = 0;
        SetPolyG4(poly);
        SetSemiTrans(poly, 1);

        poly->tag = (poly->tag & 0xFF000000) |
                    (strip->ordering_table[strip->depth_index] & 0x00FFFFFF);
        strip->ordering_table[strip->depth_index] =
            (strip->ordering_table[strip->depth_index] & 0xFF000000) |
            ((u32)poly & 0x00FFFFFF);

        poly->x0 = strip->middle_xy;
        poly->y0 = (u32)strip->middle_xy >> 16;
        poly->x1 = strip->outer_xy;
        poly->y1 = (u32)strip->outer_xy >> 16;
        poly->x2 = strip->previous_middle_xy;
        poly->y2 = (u32)strip->previous_middle_xy >> 16;
        poly->x3 = strip->previous_outer_xy;
        poly->y3 = (u32)strip->previous_outer_xy >> 16;

        tpage_state = render_state_ptr->draw_buffer;
        tpage = tpage_state->packetCursor;
        tpage_state->packetCursor = tpage + 1;
        SetDrawMode(tpage, 1, 0, GetTPage(0, 1, 0x140, 0), 0);
        AddPrim(strip->ordering_table + strip->depth_index, tpage);
    }
}
