#include "common.h"

typedef struct {
    s16 x;
    s16 y;
    s16 z;
} SVECTOR;

typedef struct {
    u8 pad0[2];
    u16 x;
    u8 pad4[2];
    u16 y;
    u8 pad8[2];
    u16 z;
} PositionFields;

typedef struct {
    u32 tag;
    u8 r0;
    u8 g0;
    u8 b0;
    u8 code;
    s16 x0;
    s16 y0;
    u8 u0;
    u8 v0;
    u16 clut;
    s16 x1;
    s16 y1;
    u8 u1;
    u8 v1;
    u16 tpage;
    s16 x2;
    s16 y2;
    u8 u2;
    u8 v2;
    u16 pad2;
    s16 x3;
    s16 y3;
    u8 u3;
    u8 v3;
    u16 pad3;
} POLY_FT4;

typedef struct {
    u8 pad0[0xB0];
    u32 ot[0x208];
    u8 pad8D0[0x8D0 - 0x8D0];
    u8 *next_prim;
} RenderContext;

typedef struct {
    RenderContext *ctx;
    u8 pad4[12];
} GlobalState;

typedef struct {
    u8 pad0[0x52];
    s16 frame;
} RenderRecord;

extern GlobalState D_80083160;
extern s32 func_80065420(SVECTOR *, s16 *, s32 *, s32 *);
extern void func_800666F4(POLY_FT4 *);
extern void func_80066640(POLY_FT4 *, s32);
extern u16 func_80066460(s32, s32, s32, s32);
extern u16 func_8006649C(s32, s32);
extern void func_80024934(void) __attribute__((noreturn));

s32 func_818390F8(RenderRecord *arg0, PositionFields *arg1)
{
    SVECTOR input;
    s16 screen[4];
    GlobalState *global = &D_80083160;
    register s16 *screen_base ASM_REG("$23") = screen;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 p;
    register s32 *p_ptr ASM_REG("$20") = &p;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    RenderRecord *record;
    u32 depth;
    s32 i;
    s32 height;
    POLY_FT4 *poly;
    register void *next ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    input.x = arg1->x;
    record = arg0;
    input.y = arg1->y;
    input.z = arg1->z - 14;

    for (i = 0; i < 2; i++) {
        depth = func_80065420(&input, &screen[i * 2], p_ptr, p_ptr) - 8;
        input.z += 28;
    }

    height = screen[1] - screen[3];
    if (++record->frame >= 12) {
        record->frame = 8;
    }

    if (depth < 480) {
        u8 u;
        s32 v;
        s32 ot_offset;

        poly = (POLY_FT4 *)global->ctx->next_prim;
        global->ctx->next_prim = (u8 *)poly + sizeof(POLY_FT4);
        *(u32 *)&poly->r0 = 0x00808080;
        func_800666F4(poly);
        func_80066640(poly, 1);
        poly->tpage = func_80066460(0, 1, 0x2C0, 0x100);
        poly->clut = func_8006649C(0, 0x1F8);

        p = height >> 1;
        poly->x0 = poly->x1 = screen[0] + (u16)p;
        poly->x2 = poly->x3 = screen[0] - (u16)p;
        poly->y0 = poly->y2 = screen[1];
        poly->y1 = poly->y3 = screen[3];

        u = record->frame;
        ot_offset = depth << 2;
        u = (u & 3) << 5;
        poly->u0 = poly->u1 = u;
        poly->u2 = poly->u3 = u + 31;
        v = ((s16)record->frame >> 2) * 32;
        poly->v0 = poly->v2 = v - 128;
        poly->v1 = poly->v3 = v - 97;

        poly->tag = (poly->tag & 0xFF000000) |
                    (*(u32 *)((u8 *)global->ctx + 0xB0 + ot_offset) &
                     0x00FFFFFF);
        *(u32 *)((u8 *)global->ctx + 0xB0 + ot_offset) =
            (*(u32 *)((u8 *)global->ctx + 0xB0 + ot_offset) & 0xFF000000) |
            ((u32)poly & 0x00FFFFFF);
    }

    ASM_KEEP(screen_base);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    next = *(void **)((u8 *)arg0 - 8);
    if (next != 0) {
        arg0 = (RenderRecord *)((u8 *)next + 0x20);
        ASM_KEEP(arg0);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        next = *(void **)((u8 *)next + 8);
        ASM_KEEP(next);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        func_80024934();
    }
    ASM_KEEP(next);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    return 0;
}

/* MECHANISM: Separate stack screen/pointer bases force the retail 0x50 frame and s7/s4 roles.
   A 40-byte FT4 plus uncached OT re-addressing restores the body length and reloads.
   Holding next in a1 and fencing the false return preserves the retail tail-j contract. */
