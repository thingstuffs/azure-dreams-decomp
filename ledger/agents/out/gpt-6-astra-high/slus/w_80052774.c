#include "common.h"

typedef struct {
    char pad0[0x230];
    u32 ot;
    char pad_234[0x8D0 - 0x234];
    u8 *prim;
} Ctx;

typedef struct {
    Ctx *ctx;
    char pad4[0x1C0];
} D80083160_t;

extern D80083160_t D_80083160;

typedef struct {
    u8 pad0[3];
    u8 len;
    u8 r0;
    u8 g0;
    u8 b0;
    u8 code;
    s16 x0;
    s16 y0;
    s16 x1;
    s16 y1;
} LineF2;

/* Draw a shaded horizontal line with dimmer translucent lines above and below. */
void func_80052774(s16 x, s16 y, s16 width, s16 shade_step)
{
    D80083160_t *render_state;
    LineF2 *center_line;
    LineF2 *upper_line;
    LineF2 *lower_line;
    s16 red_green;
    s16 blue;

    render_state = &D_80083160;
    if (shade_step < 0x11) {
        blue = shade_step * 8 + 0x80;
        if (blue == 0x100) {
            blue = 0xFF;
        }
        red_green = shade_step * 8 + 0x40;
    } else {
        blue = 0x200 - shade_step * 16;
        red_green = 0x100 - shade_step * 8;
    }

    center_line = (LineF2 *)render_state->ctx->prim;
    render_state->ctx->prim = (u8 *)center_line + 0x10;
    center_line->len = 3;
    center_line->code = 0x40;
    center_line->r0 = red_green;
    center_line->g0 = red_green;
    center_line->b0 = blue;
    if (x > 0) {
        center_line->x0 = 0;
        center_line->y0 = y;
        center_line->x1 = x + width - 1;
        center_line->y1 = y;
    } else {
        center_line->x0 = x;
        center_line->y0 = y;
        center_line->x1 = x + width - 1;
        center_line->y1 = y;
    }
    *(u32 *)center_line = (*(u32 *)center_line & 0xFF000000) | (render_state->ctx->ot & 0xFFFFFF);
    render_state->ctx->ot = (render_state->ctx->ot & 0xFF000000) | ((u32)center_line & 0xFFFFFF);

    blue = blue / 3;
    blue = blue * 2;
    red_green = red_green / 3;
    red_green = red_green * 2;

    upper_line = (LineF2 *)render_state->ctx->prim;
    render_state->ctx->prim = (u8 *)upper_line + 0x10;
    upper_line->len = 3;
    upper_line->code = 0x42;
    upper_line->r0 = red_green;
    upper_line->g0 = red_green;
    upper_line->b0 = blue;
    if (x > 0) {
        upper_line->x0 = 0;
        upper_line->y0 = y - 1;
        upper_line->x1 = x + width - 1;
        upper_line->y1 = y - 1;
    } else {
        upper_line->x0 = x;
        upper_line->y0 = y - 1;
        upper_line->x1 = x + width - 1;
        upper_line->y1 = y - 1;
    }
    *(u32 *)upper_line = (*(u32 *)upper_line & 0xFF000000) | (render_state->ctx->ot & 0xFFFFFF);
    render_state->ctx->ot = (render_state->ctx->ot & 0xFF000000) | ((u32)upper_line & 0xFFFFFF);

    lower_line = (LineF2 *)render_state->ctx->prim;
    render_state->ctx->prim = (u8 *)lower_line + 0x10;
    lower_line->len = 3;
    lower_line->code = 0x42;
    lower_line->r0 = red_green;
    lower_line->g0 = red_green;
    lower_line->b0 = blue;
    if (x > 0) {
        lower_line->x0 = 0;
        lower_line->y0 = y + 1;
        lower_line->x1 = x + width - 1;
        lower_line->y1 = y + 1;
    } else {
        lower_line->x0 = x;
        lower_line->y0 = y + 1;
        lower_line->x1 = x + width - 1;
        lower_line->y1 = y + 1;
    }
    *(u32 *)lower_line = (*(u32 *)lower_line & 0xFF000000) | (render_state->ctx->ot & 0xFFFFFF);
    render_state->ctx->ot = (render_state->ctx->ot & 0xFF000000) | ((u32)lower_line & 0xFFFFFF);
}
