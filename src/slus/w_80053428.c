#include "common.h"

#include "common.h"

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

extern D80083160_t D_80083160;

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

extern u16 GetTPage(s32 tp, s32 abr, s32 x, s32 y);
extern void SetPolyF4(PolyF4 *p);
extern void SetSemiTrans(void *p, s32 abe);
extern void SetDrawMode(void *a0, s32 a1, s32 a2, s32 a3, s32 a4);

s32 func_80053428(Param *a0)
{
    D80083160_t *base;
    TPagePkt *tpage_pkt;
    PolyF4 *poly;
    register u32 mask_lo ASM_REG("$4");   /* MATCH pin: slus-diff */
    u32 mask_hi;
    Ctx *ctx2;
    u32 poly_addr;
    s32 abr;
    u16 tp;
    s32 color;

    base = &D_80083160;
    if (a0->field_2 >= a0->field_4) {
        return 1;
    }
    tpage_pkt = (TPagePkt *)D_80083160.ctx->field_8D0;
    D_80083160.ctx->field_8D0 = (u8 *)tpage_pkt + 0xC;
    poly = (PolyF4 *)D_80083160.ctx->field_8D0;
    D_80083160.ctx->field_8D0 = (u8 *)poly + 0x18;
    abr = (a0->field_6 == 0) ? 2 : 1;
    tp = GetTPage(0, abr, 0, 0);
    SetDrawMode(tpage_pkt, 0, 0, tp, 0);
    if (a0->field_2 == 0) {
        color = 0xFFFFFF;
    } else {
        color = 0x100 - ((a0->field_2 << 8) / a0->field_4);
        color = color + ((color << 8) + (color << 16));
    }
    poly->rgbc = color;
    SetPolyF4(poly);
    SetSemiTrans(poly, 1);
    mask_lo = 0xFFFFFF;
    poly->x3 = 0x140;
    poly->x2 = 0x140;
    mask_hi = 0xFF000000;
    poly->x1 = 0;
    poly->x0 = 0;
    poly->y2 = 0;
    poly->y0 = 0;
    poly->y3 = 0xE0;
    poly->y1 = 0xE0;
    poly->tag = (poly->tag & mask_hi) | (base->ctx->field_70 & mask_lo);
    ctx2 = base->ctx;
    poly_addr = (u32)poly & mask_lo;
    ctx2->field_70 = (ctx2->field_70 & mask_hi) | poly_addr;
    tpage_pkt->tag =
        (tpage_pkt->tag & mask_hi) | (base->ctx->field_70 & mask_lo);
    base->ctx->field_70 =
        (base->ctx->field_70 & mask_hi) | ((u32)tpage_pkt & mask_lo);
    a0->field_2++;
    return 0;
}
