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

void func_80052774(s16 x, s16 y, s16 w, s16 n)
{
    D80083160_t *base;
    LineF2 *p;
    LineF2 *q;
    LineF2 *r;
    s16 g;
    s16 b;

    base = &D_80083160;
    if (n < 0x11) {
        b = n * 8 + 0x80;
        if (b == 0x100) {
            b = 0xFF;
        }
        g = n * 8 + 0x40;
    } else {
        b = 0x200 - n * 16;
        g = 0x100 - n * 8;
    }

    p = (LineF2 *)base->ctx->prim;
    base->ctx->prim = (u8 *)p + 0x10;
    p->len = 3;
    p->code = 0x40;
    p->r0 = g;
    p->g0 = g;
    p->b0 = b;
    if (x > 0) {
        p->x0 = 0;
        p->y0 = y;
        p->x1 = x + w - 1;
        p->y1 = y;
    } else {
        p->x0 = x;
        p->y0 = y;
        p->x1 = x + w - 1;
        p->y1 = y;
    }
    *(u32 *)p = (*(u32 *)p & 0xFF000000) | (base->ctx->ot & 0xFFFFFF);
    base->ctx->ot = (base->ctx->ot & 0xFF000000) | ((u32)p & 0xFFFFFF);

    b = b / 3;
    b = b * 2;
    g = g / 3;
    g = g * 2;

    q = (LineF2 *)base->ctx->prim;
    base->ctx->prim = (u8 *)q + 0x10;
    q->len = 3;
    q->code = 0x42;
    q->r0 = g;
    q->g0 = g;
    q->b0 = b;
    if (x > 0) {
        q->x0 = 0;
        q->y0 = y - 1;
        q->x1 = x + w - 1;
        q->y1 = y - 1;
    } else {
        q->x0 = x;
        q->y0 = y - 1;
        q->x1 = x + w - 1;
        q->y1 = y - 1;
    }
    *(u32 *)q = (*(u32 *)q & 0xFF000000) | (base->ctx->ot & 0xFFFFFF);
    base->ctx->ot = (base->ctx->ot & 0xFF000000) | ((u32)q & 0xFFFFFF);

    r = (LineF2 *)base->ctx->prim;
    base->ctx->prim = (u8 *)r + 0x10;
    r->len = 3;
    r->code = 0x42;
    r->r0 = g;
    r->g0 = g;
    r->b0 = b;
    if (x > 0) {
        r->x0 = 0;
        r->y0 = y + 1;
        r->x1 = x + w - 1;
        r->y1 = y + 1;
    } else {
        r->x0 = x;
        r->y0 = y + 1;
        r->x1 = x + w - 1;
        r->y1 = y + 1;
    }
    *(u32 *)r = (*(u32 *)r & 0xFF000000) | (base->ctx->ot & 0xFFFFFF);
    base->ctx->ot = (base->ctx->ot & 0xFF000000) | ((u32)r & 0xFFFFFF);
}
