#include "common.h"

#include "common.h"
#include "sdk/libgpu.h"

typedef struct {
    char pad0[0x70];
    u32 field_70;
    char pad_74[0x8D0 - 0x74];
    u8 *field_8D0;
} Ctx;

typedef struct {
    Ctx *ctx;
    char pad4[0x1C0];
} D80083160_t;

extern D80083160_t g_game_work;

typedef struct {
    char pad0[2];
    s16 field_2;
    s16 field_4;
    s16 field_6;
} Param;

typedef struct {
    u32 tag;
    u32 code;
    u32 tpage;
} TPagePkt;

typedef struct {
    u32 tag;
    u32 rgbc;
    s16 x0;
    s16 y0;
    s16 x1;
    s16 y1;
    s16 x2;
    s16 y2;
    s16 x3;
    s16 y3;
} PolyF4;

/* Draw a fading fullscreen overlay and advance its frame counter. */
s32 render_screen_fade_decreasing_intensity(Param *fade)
{
    D80083160_t *render_state;
    TPagePkt *tpage_pkt;
    PolyF4 *poly;
    u32 addr_mask;
    u32 length_mask;
    Ctx *draw_ctx;
    u32 poly_addr;
    s32 blend_mode;
    u16 tpage;
    s32 color;

    render_state = &g_game_work;
    if (fade->field_2 >= fade->field_4) {
        return 1;
    }
    tpage_pkt = (TPagePkt *)g_game_work.ctx->field_8D0;
    g_game_work.ctx->field_8D0 = (u8 *)tpage_pkt + 0xC;
    poly = (PolyF4 *)g_game_work.ctx->field_8D0;
    g_game_work.ctx->field_8D0 = (u8 *)poly + 0x18;
    blend_mode = (fade->field_6 == 0) ? 2 : 1;
    tpage = GetTPage(0, blend_mode, 0, 0);
    SetDrawMode(tpage_pkt, 0, 0, tpage, 0);
    if (fade->field_2 == 0) {
        color = 0xFFFFFF;
    } else {
        color = 0x100 - ((fade->field_2 << 8) / fade->field_4);
        color = color + ((color << 8) + (color << 16));
    }
    poly->rgbc = color;
    SetPolyF4(poly);
    SetSemiTrans(poly, 1);
    do {
        addr_mask = 0xFFFFFF;
    } while (0);
    poly->x3 = 0x140;
    poly->x2 = 0x140;
    length_mask = 0xFF000000;
    poly->x1 = 0;
    poly->x0 = 0;
    poly->y2 = 0;
    poly->y0 = 0;
    poly->y3 = 0xE0;
    poly->y1 = 0xE0;
    poly->tag = (poly->tag & length_mask) | (render_state->ctx->field_70 & addr_mask);
    draw_ctx = render_state->ctx;
    poly_addr = (u32)poly & addr_mask;
    draw_ctx->field_70 = (draw_ctx->field_70 & length_mask) | poly_addr;
    tpage_pkt->tag =
        (tpage_pkt->tag & length_mask) | (render_state->ctx->field_70 & addr_mask);
    render_state->ctx->field_70 =
        (render_state->ctx->field_70 & length_mask) | ((u32)tpage_pkt & addr_mask);
    fade->field_2++;
    return 0;
}
