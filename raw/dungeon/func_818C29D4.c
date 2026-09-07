#include "common.h"

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))
#define OT_PTR(sc) \
    (FIELD((sc), u32 *, 0x18) + FIELD((sc), volatile u32, 0xB4))
#define ADD_PRIM(sc, p, hi_mask, lo_mask) do { \
    u32 *_ot; \
    *(u32 *)(p) = (*OT_PTR(sc) & (lo_mask)) | \
                   (*(u32 *)(p) & (hi_mask)); \
    _ot = OT_PTR(sc); \
    *_ot = (*_ot & (hi_mask)) | ((u32)(p) & (lo_mask)); \
} while (0)

typedef struct { s16 x; s16 y; s16 z; s16 pad; } Vec818C29D4;
typedef struct {
    u32 tag;
    u8 r0, g0, b0, code; s16 x0, y0; u8 u0, v0; u16 clut;
    u8 r1, g1, b1, pad1; s16 x1, y1; u8 u1, v1; u16 tpage;
    u8 r2, g2, b2, pad2; s16 x2, y2; u8 u2, v2; u16 pad3;
    u8 r3, g3, b3, pad4; s16 x3, y3; u8 u3, v3; u16 pad5;
} Poly818C29D4;
typedef struct { s16 x; s16 y; s16 w; s16 h; } Rect818C29D4;

extern u8 D_80083160[];
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern u32 func_80065590(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, u16, void *);

s32 func_818C29D4(void *arg0, void *arg1)
{
    u8 *scratch = (u8 *)0x1F800000;
    u8 *angle_addr;
    s32 angle;
    s32 delta;
    u8 uv;
    s32 value;
    register Poly818C29D4 *poly ASM_REG("$20");
    register u8 *packet ASM_REG("$16");
    Rect818C29D4 rect;
    u32 index;
    s32 tp_x;
    s32 tp_y;
    s32 tp_w;

    angle_addr = D_80083160;
    angle = FIELD(angle_addr, s16, 0xC8);
    FIELD(scratch, void *, 0x18) = FIELD(D_80083160, u8 *, 0) + 0xB0;
    delta = ((func_80064584(angle) >> 4) * 36) >> 8;
    value = FIELD(arg1, u16, 2) - delta;
    FIELD(scratch, s16, 0x74) = value;
    FIELD(scratch, s16, 0x64) = value;
    value = FIELD(arg1, u16, 2) + delta;
    FIELD(scratch, s16, 0x7C) = value;
    FIELD(scratch, s16, 0x6C) = value;
    delta = ((func_800644B8(angle) >> 4) * 36) >> 8;
    value = FIELD(arg1, u16, 6) + delta;
    FIELD(scratch, s16, 0x76) = value;
    FIELD(scratch, s16, 0x66) = value;
    value = FIELD(arg1, u16, 6) - delta;
    FIELD(scratch, s16, 0x7E) = value;
    FIELD(scratch, s16, 0x6E) = value;
    value = FIELD(arg1, u16, 0xA) - 0x80;
    FIELD(scratch, s16, 0x70) = value;
    FIELD(scratch, s16, 0x68) = value;
    value = FIELD(arg1, u16, 0xA);
    FIELD(scratch, s16, 0x78) = value;
    FIELD(scratch, s16, 0x80) = value;
    poly = FIELD(FIELD(D_80083160, u8 *, 0), Poly818C29D4 *, 0x8D0);
    FIELD(FIELD(D_80083160, u8 *, 0), u8 *, 0x8D0) = (u8 *)poly + sizeof(*poly);
    FIELD(poly, u8, 3) = 12;
    poly->code = 0x3E;
    poly->tpage = func_80066460(0, 1, 0x280, 0x100);
    poly->clut = FIELD(arg0, u16, 8);
    poly->r0 = 0; poly->g0 = 0; poly->b0 = 0;
    poly->r1 = 0; poly->g1 = 0; poly->b1 = 0;
    poly->r2 = FIELD(arg0, u8, 0xA);
    poly->g2 = FIELD(arg0, u8, 0xA);
    poly->b2 = FIELD(arg0, u8, 0xA);
    poly->r3 = FIELD(arg0, u8, 0xA);
    poly->g3 = FIELD(arg0, u8, 0xA);
    poly->b3 = FIELD(arg0, u8, 0xA);
    uv = (FIELD(arg0, s16, 4) % 4) << 3;
    ASM_KEEP(uv);
    poly->u0 = 0; poly->v0 = uv;
    poly->u1 = 0x3F; poly->v1 = uv;
    poly->u2 = 0x3F; poly->v2 = uv + 0x3F;
    poly->u3 = 0; poly->v3 = uv + 0x3F;
    index = func_80065590(
        scratch + 0x64, scratch + 0x6C, scratch + 0x74, scratch + 0x7C,
        scratch + 0xD8, scratch + 0xDC, scratch + 0xE0, scratch + 0xE4,
        scratch + 0x84, scratch + 0x88);
    FIELD(scratch, volatile u32, 0xB4) = index;
    FIELD(poly, volatile u16, 8) = FIELD(scratch, u16, 0xD8);
    FIELD(poly, volatile u16, 0xA) = FIELD(scratch, u16, 0xDA);
    FIELD(poly, volatile u16, 0x14) = FIELD(scratch, u16, 0xDC);
    FIELD(poly, volatile u16, 0x16) = FIELD(scratch, u16, 0xDE);
    FIELD(poly, volatile u16, 0x20) = FIELD(scratch, u16, 0xE0);
    FIELD(poly, volatile u16, 0x22) = FIELD(scratch, u16, 0xE2);
    FIELD(poly, volatile u16, 0x2C) = FIELD(scratch, u16, 0xE4);
    FIELD(poly, volatile u16, 0x2E) = FIELD(scratch, u16, 0xE6);
    if (FIELD(scratch, u32, 0xB4) < 0x1E0U) {
        register u32 lo_mask ASM_REG("$17");
        register u32 hi_mask ASM_REG("$18");
        register s32 first_x ASM_REG("$4");
        register s32 first_y ASM_REG("$5");
        register s32 first_w ASM_REG("$6");
        register s32 first_h ASM_REG("$7");
        first_x = 0; first_y = 1; first_w = 0x280; first_h = 0x100;
        ASM_KEEP4(first_x, first_y, first_w, first_h);
        lo_mask = 0x00FF0000; ASM_KEEP(lo_mask);
        rect.y = 0; rect.x = 0; rect.h = 0xFF; rect.w = 0xFF;
        packet = FIELD(FIELD(D_80083160, u8 *, 0), u8 *, 0x8D0);
        ASM_KEEP(packet);
        lo_mask |= 0xFFFF; ASM_KEEP(lo_mask);
        FIELD(FIELD(D_80083160, u8 *, 0), u8 *, 0x8D0) = packet + 0xC;
        func_80067F20(packet, 0, 0,
                     func_80066460(first_x, first_y, first_w, first_h) & 0xFFFF,
                     &rect);
        tp_x = 0; hi_mask = 0xFF000000; tp_y = 1; tp_w = 0x280;
        ASM_KEEP(tp_x); ASM_KEEP(hi_mask); ASM_KEEP(tp_y); ASM_KEEP(tp_w);
        { register u32 *ot ASM_REG("$2"); u32 prim_tag; u32 ot_tag;
            ot = (u32 *)((FIELD(scratch, volatile u32, 0xB4) << 2) + (u32)FIELD(scratch, u32 *, 0x18));
            ASM_KEEP(ot); prim_tag = *(u32 *)packet; ot_tag = *ot;
            *(u32 *)packet = (prim_tag & hi_mask) | (ot_tag & lo_mask); }
        { register u32 *ot ASM_REG("$3");
            ot = (u32 *)((FIELD(scratch, volatile u32, 0xB4) << 2) + (u32)FIELD(scratch, u32 *, 0x18));
            ASM_KEEP(ot); *ot = (*ot & hi_mask) | ((u32)packet & lo_mask); }
        { register u32 *ot ASM_REG("$2"); u32 prim_tag; u32 ot_tag;
            ot = (u32 *)((FIELD(scratch, volatile u32, 0xB4) << 2) + (u32)FIELD(scratch, u32 *, 0x18));
            ASM_KEEP(ot); prim_tag = *(u32 *)poly; ot_tag = *ot;
            *(u32 *)poly = (prim_tag & hi_mask) | (ot_tag & lo_mask); }
        { register u32 *ot ASM_REG("$7");
            ot = (u32 *)((FIELD(scratch, volatile u32, 0xB4) << 2) + (u32)FIELD(scratch, u32 *, 0x18));
            ASM_KEEP(ot); *ot = (*ot & hi_mask) | ((u32)poly & lo_mask); }
        rect.y = 0x80; rect.x = 0; rect.h = 0x40; rect.w = 0x40;
        packet = FIELD(FIELD(D_80083160, u8 *, 0), u8 *, 0x8D0);
        FIELD(FIELD(D_80083160, u8 *, 0), u8 *, 0x8D0) = packet + 0xC;
        func_80067F20(packet, 0, 0,
                     func_80066460(tp_x, tp_y, tp_w, 0x100) & 0xFFFF, &rect);
        { register u32 *ot ASM_REG("$2"); u32 prim_tag; u32 ot_tag;
            ot = (u32 *)((FIELD(scratch, volatile u32, 0xB4) << 2) + (u32)FIELD(scratch, u32 *, 0x18));
            ASM_KEEP(ot); prim_tag = *(u32 *)packet; ot_tag = *ot;
            *(u32 *)packet = (prim_tag & hi_mask) | (ot_tag & lo_mask); }
        { register u32 *ot ASM_REG("$3");
            ot = (u32 *)((FIELD(scratch, volatile u32, 0xB4) << 2) + (u32)FIELD(scratch, u32 *, 0x18));
            ASM_KEEP(ot); *ot = (*ot & hi_mask) | ((u32)packet & lo_mask); }
    }
    ASM_KEEP(poly);
    return 0;
}
