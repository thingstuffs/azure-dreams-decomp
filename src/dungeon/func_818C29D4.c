#include "common.h"
#include "records/Rec_D_80083160.h"

#define OT_PTR(sc) \
    (((S_818C29D4_0 *)((sc)))->unk_18 + ((S_818C29D4_0 *)((sc)))->unk_B4)
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


typedef struct S_818C29D4_0 {
    u8 pad_00[0x18];
    u32 * unk_18;
    u8 pad_1C[0x98];
    volatile u32 unk_B4;
} S_818C29D4_0;   /* (sc) in func_818C29D4 */

typedef struct S_818C29D4_1 {
    u8 pad_00[0xC8];
    s16 unk_C8;
} S_818C29D4_1;   /* angle_addr in func_818C29D4 */

typedef struct S_818C29D4_2 {
    u8 pad_00[0x18];
    union { void * p; u32 * p2; } unk_18;   /* accessed as both */
    u8 pad_1C[0x48];
    s16 unk_64;
    s16 unk_66;
    s16 unk_68;
    u8 pad_6A[0x2];
    s16 unk_6C;
    s16 unk_6E;
    s16 unk_70;
    u8 pad_72[0x2];
    s16 unk_74;
    s16 unk_76;
    s16 unk_78;
    u8 pad_7A[0x2];
    s16 unk_7C;
    s16 unk_7E;
    s16 unk_80;
    u8 pad_82[0x32];
    union { volatile u32 v; u32 n; } unk_B4;   /* accessed as both */
    u8 pad_B8[0x20];
    u16 unk_D8;
    u16 unk_DA;
    u16 unk_DC;
    u16 unk_DE;
    u16 unk_E0;
    u16 unk_E2;
    u16 unk_E4;
    u16 unk_E6;
} S_818C29D4_2;   /* scratch in func_818C29D4 */


typedef struct S_818C29D4_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_818C29D4_4;   /* arg1 in func_818C29D4 */

typedef struct S_818C29D4_5 {
    u8 pad_00[0x3];
    u8 unk_03;
    u8 pad_04[0x4];
    volatile u16 unk_08;
    volatile u16 unk_0A;
    u8 pad_0C[0x8];
    volatile u16 unk_14;
    volatile u16 unk_16;
    u8 pad_18[0x8];
    volatile u16 unk_20;
    volatile u16 unk_22;
    u8 pad_24[0x8];
    volatile u16 unk_2C;
    volatile u16 unk_2E;
} S_818C29D4_5;   /* poly in func_818C29D4 */

typedef struct S_818C29D4_6 {
    u8 pad_00[0x4];
    s16 unk_04;
    u8 pad_06[0x2];
    u16 unk_08;
    u8 unk_0A;
} S_818C29D4_6;   /* arg0 in func_818C29D4 */

typedef struct S_818C29D4_7 {
    u8 pad_00[0x8D0];
    union { Poly818C29D4 * p; u8 * p2; } unk_8D0;   /* accessed as both */
} S_818C29D4_7;   /* ((Rec_D_80083160 *)D_80083160)->unk_00.as_pu8 in func_818C29D4 */

/* Builds and queues a shaded textured quad with texture-window commands. */
s32 func_818C29D4(S_818C29D4_6 *sprite, S_818C29D4_4 *position)
{
    u8 *scratch = (u8 *)0x1F800000;
    u8 *angle_addr;
    s32 angle;
    s32 axis_offset;
    s16 texture_v;
    s32 vertex_coord;
    Poly818C29D4 *poly;
    register u8 *draw_mode ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    Rect818C29D4 texture_window;
    u32 ot_index;
    s32 tex_depth;
    s32 blend_mode;
    s32 page_x;

    angle_addr = D_80083160;
    angle = ((S_818C29D4_1 *)angle_addr)->unk_C8;
    ((S_818C29D4_2 *)scratch)->unk_18.p = ((Rec_D_80083160 *)D_80083160)->unk_00.as_pu8 + 0xB0;
    axis_offset = ((func_80064584(angle) >> 4) * 36) >> 8;
    vertex_coord = position->unk_02 - axis_offset;
    ((S_818C29D4_2 *)scratch)->unk_74 = vertex_coord;
    ((S_818C29D4_2 *)scratch)->unk_64 = vertex_coord;
    vertex_coord = position->unk_02 + axis_offset;
    ((S_818C29D4_2 *)scratch)->unk_7C = vertex_coord;
    ((S_818C29D4_2 *)scratch)->unk_6C = vertex_coord;
    axis_offset = ((func_800644B8(angle) >> 4) * 36) >> 8;
    vertex_coord = position->unk_06 + axis_offset;
    ((S_818C29D4_2 *)scratch)->unk_76 = vertex_coord;
    ((S_818C29D4_2 *)scratch)->unk_66 = vertex_coord;
    vertex_coord = position->unk_06 - axis_offset;
    ((S_818C29D4_2 *)scratch)->unk_7E = vertex_coord;
    ((S_818C29D4_2 *)scratch)->unk_6E = vertex_coord;
    vertex_coord = position->unk_0A - 0x80;
    ((S_818C29D4_2 *)scratch)->unk_70 = vertex_coord;
    ((S_818C29D4_2 *)scratch)->unk_68 = vertex_coord;
    vertex_coord = position->unk_0A;
    ((S_818C29D4_2 *)scratch)->unk_78 = vertex_coord;
    ((S_818C29D4_2 *)scratch)->unk_80 = vertex_coord;
    poly = ((S_818C29D4_7 *)(((Rec_D_80083160 *)D_80083160)->unk_00.as_pu8))->unk_8D0.p;
    ((S_818C29D4_7 *)(((Rec_D_80083160 *)D_80083160)->unk_00.as_pu8))->unk_8D0.p2 = (u8 *)poly + sizeof(*poly);
    ((S_818C29D4_5 *)poly)->unk_03 = 12;
    poly->code = 0x3E;
    poly->tpage = func_80066460(0, 1, 0x280, 0x100);
    poly->clut = sprite->unk_08;
    poly->r0 = 0; poly->g0 = 0; poly->b0 = 0;
    poly->r1 = 0; poly->g1 = 0; poly->b1 = 0;
    poly->r2 = sprite->unk_0A;
    poly->g2 = sprite->unk_0A;
    poly->b2 = sprite->unk_0A;
    poly->r3 = sprite->unk_0A;
    poly->g3 = sprite->unk_0A;
    poly->b3 = sprite->unk_0A;
    texture_v = (sprite->unk_04 % 4) << 3;
    poly->u0 = 0; poly->v0 = texture_v;
    poly->u1 = 0x3F; poly->v1 = texture_v;
    poly->u2 = 0x3F; poly->v2 = texture_v + 0x3F;
    poly->u3 = 0; poly->v3 = texture_v + 0x3F;
    ot_index = func_80065590(
        scratch + 0x64, scratch + 0x6C, scratch + 0x74, scratch + 0x7C,
        scratch + 0xD8, scratch + 0xDC, scratch + 0xE0, scratch + 0xE4,
        scratch + 0x84, scratch + 0x88);
    ((S_818C29D4_2 *)scratch)->unk_B4.v = ot_index;
    ((S_818C29D4_5 *)poly)->unk_08 = ((S_818C29D4_2 *)scratch)->unk_D8;
    ((S_818C29D4_5 *)poly)->unk_0A = ((S_818C29D4_2 *)scratch)->unk_DA;
    ((S_818C29D4_5 *)poly)->unk_14 = ((S_818C29D4_2 *)scratch)->unk_DC;
    ((S_818C29D4_5 *)poly)->unk_16 = ((S_818C29D4_2 *)scratch)->unk_DE;
    ((S_818C29D4_5 *)poly)->unk_20 = ((S_818C29D4_2 *)scratch)->unk_E0;
    ((S_818C29D4_5 *)poly)->unk_22 = ((S_818C29D4_2 *)scratch)->unk_E2;
    ((S_818C29D4_5 *)poly)->unk_2C = ((S_818C29D4_2 *)scratch)->unk_E4;
    ((S_818C29D4_5 *)poly)->unk_2E = ((S_818C29D4_2 *)scratch)->unk_E6;
    if (((S_818C29D4_2 *)scratch)->unk_B4.n < 0x1E0U) {
        u32 addr_mask;
        u32 length_mask;
        s32 reset_depth;
        s32 reset_blend;
        s32 reset_page_x;
        s32 reset_page_y;
        reset_depth = 0; reset_blend = 1; reset_page_x = 0x280; reset_page_y = 0x100;
        ASM_KEEP4(reset_depth, reset_blend, reset_page_x, reset_page_y);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        addr_mask = 0x00FF0000; ASM_KEEP(addr_mask);
        texture_window.y = 0; texture_window.x = 0; texture_window.h = 0xFF; texture_window.w = 0xFF;
        draw_mode = ((S_818C29D4_7 *)(((Rec_D_80083160 *)D_80083160)->unk_00.as_pu8))->unk_8D0.p2;
           /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        addr_mask |= 0xFFFF; 
        ((S_818C29D4_7 *)(((Rec_D_80083160 *)D_80083160)->unk_00.as_pu8))->unk_8D0.p2 = draw_mode + 0xC;
        func_80067F20(draw_mode, 0, 0,
                     func_80066460(reset_depth, reset_blend, reset_page_x, reset_page_y) & 0xFFFF,
                     &texture_window);
        tex_depth = 0; length_mask = 0xFF000000; blend_mode = 1; page_x = 0x280;
           /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        { u32 *ot; u32 prim_tag; u32 ot_tag;
            ot = (u32 *)((((S_818C29D4_2 *)scratch)->unk_B4.v << 2) + (u32)((S_818C29D4_2 *)scratch)->unk_18.p2);
             prim_tag = *(u32 *)draw_mode; ot_tag = *ot;
            *(u32 *)draw_mode = (prim_tag & length_mask) | (ot_tag & addr_mask); }
        { u32 *ot;
            ot = (u32 *)((((S_818C29D4_2 *)scratch)->unk_B4.v << 2) + (u32)((S_818C29D4_2 *)scratch)->unk_18.p2);
             *ot = (*ot & length_mask) | ((u32)draw_mode & addr_mask); }
        { u32 *ot; u32 prim_tag; u32 ot_tag;
            ot = (u32 *)((((S_818C29D4_2 *)scratch)->unk_B4.v << 2) + (u32)((S_818C29D4_2 *)scratch)->unk_18.p2);
             prim_tag = *(u32 *)poly; ot_tag = *ot;
            *(u32 *)poly = (prim_tag & length_mask) | (ot_tag & addr_mask); }
        { u32 *ot;
            ot = (u32 *)((((S_818C29D4_2 *)scratch)->unk_B4.v << 2) + (u32)((S_818C29D4_2 *)scratch)->unk_18.p2);
             *ot = (*ot & length_mask) | ((u32)poly & addr_mask); }
        texture_window.y = 0x80; texture_window.x = 0; texture_window.h = 0x40; texture_window.w = 0x40;
        draw_mode = ((S_818C29D4_7 *)(((Rec_D_80083160 *)D_80083160)->unk_00.as_pu8))->unk_8D0.p2;
        ((S_818C29D4_7 *)(((Rec_D_80083160 *)D_80083160)->unk_00.as_pu8))->unk_8D0.p2 = draw_mode + 0xC;
        func_80067F20(draw_mode, 0, 0,
                     func_80066460(tex_depth, blend_mode, page_x, 0x100) & 0xFFFF, &texture_window);
        { u32 *ot; u32 prim_tag; u32 ot_tag;
            ot = (u32 *)((((S_818C29D4_2 *)scratch)->unk_B4.v << 2) + (u32)((S_818C29D4_2 *)scratch)->unk_18.p2);
             prim_tag = *(u32 *)draw_mode; ot_tag = *ot;
            *(u32 *)draw_mode = (prim_tag & length_mask) | (ot_tag & addr_mask); }
        { u32 *ot;
            ot = (u32 *)((((S_818C29D4_2 *)scratch)->unk_B4.v << 2) + (u32)((S_818C29D4_2 *)scratch)->unk_18.p2);
             *ot = (*ot & length_mask) | ((u32)draw_mode & addr_mask); }
    }
    return 0;
}
