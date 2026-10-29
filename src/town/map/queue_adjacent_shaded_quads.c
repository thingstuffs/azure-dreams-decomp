#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"
#include "sdk/libgpu.h"
#include "town/map.h"

typedef struct Func800AB788Arg {
    u8 pad00[0x24];
    u32 *ot;
    u8 pad28[0x9C];
    s32 otIndex;
    u8 padC8[0x20];
    u16 x0;
    u16 y0;
    u16 x1;
    u16 y1;
    u16 x2;
    u16 y2;
    u16 x3;
    u16 y3;
    u8 padF8[0x1C];
    u32 color1;
    u32 color3;
    u8 pad11C[8];
    u16 x4;
    u16 y4;
    u16 x5;
    u16 y5;
} Func800AB788Arg;



typedef struct Func800AB788Poly {
    u32 tag;
    u32 color0;
    u16 x0;
    u16 y0;
    u32 color1;
    u16 x1;
    u16 y1;
    u32 color2;
    u16 x2;
    u16 y2;
    u32 color3;
    u16 x3;
    u16 y3;
} Func800AB788Poly;

/* Queue two adjoining shaded quads whose vertices fall within the screen margin. */
void queue_adjacent_shaded_quads(Func800AB788Arg *strip)
{
    Func800AB788Poly *poly;
    u8 *tpage;
    GameWork *render_state_ptr = &g_game_work;

    if ((((u16)(strip->x0 + 0x20) < 0x181) &&
         ((u16)(strip->y0 + 0x20) < 0x121)) |
        (((u16)(strip->x1 + 0x20) < 0x181) &&
         ((u16)(strip->y1 + 0x20) < 0x121)) |
        (((u16)(strip->x2 + 0x20) < 0x181) &&
         ((u16)(strip->y2 + 0x20) < 0x121)) |
        (((u16)(strip->x3 + 0x20) < 0x181) &&
         ((u16)(strip->y3 + 0x20) < 0x121))) {
        GpuContext *poly_state;
        GpuContext *tpage_state;

        poly_state = (GpuContext *)render_state_ptr->draw_buffer;
        poly = (Func800AB788Poly *)poly_state->packetCursor;
        poly_state->packetCursor = (u8 *)poly + sizeof(*poly);

        poly->color0 = 0x383838;
        poly->color1 = strip->color1;
        poly->color2 = 0x383838;
        poly->color3 = strip->color3;
        SetPolyG4(poly);
        SetSemiTrans(poly, 1);

        poly->tag = (poly->tag & 0xFF000000) |
                    (strip->ot[strip->otIndex] & 0x00FFFFFF);
        strip->ot[strip->otIndex] =
            (strip->ot[strip->otIndex] & 0xFF000000) |
            ((u32)poly & 0x00FFFFFF);

        poly->x0 = strip->x0;
        poly->y0 = strip->y0;
        poly->x1 = strip->x1;
        poly->y1 = strip->y1;
        poly->x2 = strip->x2;
        poly->y2 = strip->y2;
        poly->x3 = strip->x3;
        poly->y3 = strip->y3;

        tpage_state = (GpuContext *)render_state_ptr->draw_buffer;
        tpage = tpage_state->packetCursor;
        tpage_state->packetCursor = tpage + 0xC;
        SetDrawMode(tpage, 1, 0, GetTPage(0, 1, 0x140, 0), 0);
        AddPrim(strip->ot + strip->otIndex, tpage);
    }

    if ((((u16)(strip->x1 + 0x20) < 0x181) &&
         ((u16)(strip->y1 + 0x20) < 0x121)) |
        (((u16)(strip->x4 + 0x20) < 0x181) &&
         ((u16)(strip->y4 + 0x20) < 0x121)) |
        (((u16)(strip->x3 + 0x20) < 0x181) &&
         ((u16)(strip->y3 + 0x20) < 0x121)) |
        (((u16)(strip->x5 + 0x20) < 0x181) &&
         ((u16)(strip->y5 + 0x20) < 0x121))) {
        GpuContext *poly_state;
        GpuContext *tpage_state;

        poly_state = (GpuContext *)render_state_ptr->draw_buffer;
        poly = (Func800AB788Poly *)poly_state->packetCursor;
        poly_state->packetCursor = (u8 *)poly + sizeof(*poly);

        poly->color0 = strip->color1;
        poly->color1 = 0;
        poly->color2 = strip->color3;
        poly->color3 = 0;
        SetPolyG4(poly);
        SetSemiTrans(poly, 1);

        poly->tag = (poly->tag & 0xFF000000) |
                    (strip->ot[strip->otIndex] & 0x00FFFFFF);
        strip->ot[strip->otIndex] =
            (strip->ot[strip->otIndex] & 0xFF000000) |
            ((u32)poly & 0x00FFFFFF);

        poly->x0 = strip->x1;
        poly->y0 = strip->y1;
        poly->x1 = strip->x4;
        poly->y1 = strip->y4;
        poly->x2 = strip->x3;
        poly->y2 = strip->y3;
        poly->x3 = strip->x5;
        poly->y3 = strip->y5;

        tpage_state = (GpuContext *)render_state_ptr->draw_buffer;
        tpage = tpage_state->packetCursor;
        tpage_state->packetCursor = tpage + 0xC;
        SetDrawMode(tpage, 1, 0, GetTPage(0, 1, 0x140, 0), 0);
        AddPrim(strip->ot + strip->otIndex, tpage);
    }
}
