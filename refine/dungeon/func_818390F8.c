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

/* Advance the animation and enqueue a textured quad at the projected position. */
s32 func_818390F8(RenderRecord *render_record, PositionFields *position)
{
    SVECTOR world_point;
    s16 screen[4];
    GlobalState *render_state = &D_80083160;
    register s16 *screen_base ASM_REG("$23") = screen;   /* MATCH pin: load-bearing for the whole function shape */
    s32 half_width;
    register s32 *projection_out ASM_REG("$20") = &half_width;   /* MATCH pin: load-bearing for the whole function shape */
    RenderRecord *frame_record;
    u32 depth;
    s32 endpoint;
    s32 height;
    POLY_FT4 *poly;
    register void *next_node ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */

    world_point.x = position->x;
    frame_record = render_record;
    world_point.y = position->y;
    world_point.z = position->z - 14;

    for (endpoint = 0; endpoint < 2; endpoint++) {
        depth = func_80065420(&world_point, &screen[endpoint * 2], projection_out, projection_out) - 8;
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

        poly = (POLY_FT4 *)render_state->ctx->next_prim;
        render_state->ctx->next_prim = (u8 *)poly + sizeof(POLY_FT4);
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
                    (*(u32 *)((u8 *)render_state->ctx + 0xB0 + ot_offset) &
                     0x00FFFFFF);
        *(u32 *)((u8 *)render_state->ctx + 0xB0 + ot_offset) =
            (*(u32 *)((u8 *)render_state->ctx + 0xB0 + ot_offset) & 0xFF000000) |
            ((u32)poly & 0x00FFFFFF);
    }

    ASM_KEEP(screen_base);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    next_node = *(void **)((u8 *)render_record - 8);
    if (next_node != 0) {
        render_record = (RenderRecord *)((u8 *)next_node + 0x20);
        ASM_KEEP(render_record);   /* MATCH pin: load-bearing for the whole function shape */
        next_node = *(void **)((u8 *)next_node + 8);
        ASM_KEEP(next_node);   /* MATCH pin: retail basic-block layout depends on it */
        func_80024934();
    }
    ASM_KEEP(next_node);   /* MATCH pin: retail basic-block layout depends on it */
    return 0;
}

/* MECHANISM: Separate stack screen/pointer bases force the retail 0x50 frame and s7/s4 roles.
   A 40-byte FT4 plus uncached OT re-addressing restores the body length and reloads.
   Holding next in a1 and fencing the false return preserves the retail tail-j contract. */
