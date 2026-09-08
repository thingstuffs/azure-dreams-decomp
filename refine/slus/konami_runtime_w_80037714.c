#include "common.h"

typedef union {
    struct {
        u16 x;
        u16 y;
    } half;
    u32 word;
} XY;

typedef struct {
    XY xy;
    s16 z;
    s16 pad;
} VERTEX;

typedef struct {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    s16 page_x;
    s16 page_y;
    u8 tex_width;
    u8 pad0D;
    u8 tex_height;
    u8 pad0F;
    u8 color;
    u8 pad11[3];
    s16 clut_x;
    s16 clut_y;
    u8 tex_x;
    u8 pad19;
    u8 tex_y;
    u8 pad1B;
} TEX_RECT;

typedef struct {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
} RECTANGLE;

typedef struct {
    void *owner;
    u8 pad04[8];
    TEX_RECT textured;
    RECTANGLE solid;
} DRAW_DESC;

typedef struct {
    u32 tag;
    u8 r0;
    u8 g0;
    u8 b0;
    u8 code;
    u32 xy0;
    u8 u0;
    u8 v0;
    u16 clut;
    u32 xy1;
    u8 u1;
    u8 v1;
    u16 tpage;
    u32 xy2;
    u8 u2;
    u8 v2;
    u16 pad1E;
    u32 xy3;
    u8 u3;
    u8 v3;
    u16 pad26;
} POLY_FT4;

typedef struct {
    u32 tag;
    u8 r0;
    u8 g0;
    u8 b0;
    u8 code;
    u32 xy0;
    u8 r1;
    u8 g1;
    u8 b1;
    u8 pad0F;
    u32 xy1;
    u8 r2;
    u8 g2;
    u8 b2;
    u8 pad17;
    u32 xy2;
    u8 r3;
    u8 g3;
    u8 b3;
    u8 pad1F;
    u32 xy3;
} POLY_G4;

typedef struct {
    u32 tag;
    u32 code[2];
} DR_MODE;

extern u8 *D_80083160[];

extern void RotTransPers4(VERTEX *, VERTEX *, VERTEX *, VERTEX *,
                          VERTEX *, VERTEX *, VERTEX *, VERTEX *, s32 *, s32 *);
extern void SetPolyFT4(POLY_FT4 *);
extern void SetPolyG4(POLY_G4 *);
extern void SetSemiTrans(void *, s32);
extern u16 GetClut(s16, s16);
extern u16 GetTPage(s32, s32, s16, s16);
extern void SetDrawMode(DR_MODE *, s32, s32, s32, void *);
extern void AddPrim(void *, void *);

#define ON_SCREEN(v) \
    (((u16)((v).xy.half.x + 0x20) < 0x181U) && \
     ((u16)((v).xy.half.y + 0x20) < 0x121U))

/* Project and enqueue visible textured and translucent blue gradient rectangles. */
void func_80037714(DRAW_DESC *desc) {
    VERTEX vertices[4];
    VERTEX projected[4];
    s32 depth;
    s32 transform_flags;
    TEX_RECT *textured;
    RECTANGLE *solid;
    void *owner;
    POLY_FT4 *tex_quad;
    POLY_G4 *gradient_quad;
    DR_MODE *draw_mode;
    u8 *display;
    u8 **displays;
    s32 page_u;
    s32 tex_u;
    s32 page_y;
    s32 tex_v;

    owner = desc->owner;
    textured = &desc->textured;
    solid = &desc->solid;
    displays = D_80083160;

    vertices[0].xy.half.x = vertices[2].xy.half.x = textured->x;
    vertices[1].xy.half.x = vertices[3].xy.half.x = textured->x + textured->width;
    vertices[0].xy.half.y = vertices[1].xy.half.y = textured->y;
    vertices[2].xy.half.y = vertices[3].xy.half.y = textured->y + textured->height;
    vertices[0].z = vertices[1].z = vertices[2].z = vertices[3].z = 0;

    RotTransPers4(&vertices[0], &vertices[1], &vertices[2], &vertices[3],
                  &projected[0], &projected[1], &projected[2], &projected[3],
                  &depth, &transform_flags);

    if (ON_SCREEN(projected[0]) | ON_SCREEN(projected[1]) |
        ON_SCREEN(projected[2]) | ON_SCREEN(projected[3])) {
        display = D_80083160[0];
        tex_quad = *(POLY_FT4 **)(display + 0x8D0);
        *(u8 **)(display + 0x8D0) = (u8 *)tex_quad + sizeof(POLY_FT4);
        SetPolyFT4(tex_quad);

        tex_quad->clut = GetClut(textured->clut_x, textured->clut_y);
        tex_quad->tpage = GetTPage(0, 0, textured->page_x, textured->page_y);
        tex_quad->r0 = tex_quad->g0 = tex_quad->b0 = textured->color;

        page_u = (textured->page_x % 64) * 4;
        tex_u = textured->tex_x + page_u;
        tex_quad->u0 = tex_quad->u2 = tex_u;
        tex_u += textured->tex_width;
        tex_quad->u1 = tex_quad->u3 = tex_u;

        page_y = textured->page_y;
        tex_v = (page_y %= 256) + textured->tex_y;
        tex_quad->v0 = tex_quad->v1 = tex_v;
        tex_v += textured->tex_height;
        tex_quad->v2 = tex_quad->v3 = tex_v;

        tex_quad->xy0 = projected[0].xy.word;
        tex_quad->xy1 = projected[1].xy.word;
        tex_quad->xy2 = projected[2].xy.word;
        tex_quad->xy3 = projected[3].xy.word;
        AddPrim(D_80083160[0] + 0x70 + (*(s32 *)((u8 *)owner + 0x60) * 4), tex_quad);
    }

    vertices[0].xy.half.x = vertices[2].xy.half.x = solid->x;
    vertices[1].xy.half.x = vertices[3].xy.half.x = solid->x + solid->width;
    vertices[0].xy.half.y = vertices[1].xy.half.y = solid->y;
    vertices[2].xy.half.y = vertices[3].xy.half.y = solid->y + solid->height;
    vertices[0].z = vertices[1].z = vertices[2].z = vertices[3].z = 0;

    RotTransPers4(&vertices[0], &vertices[1], &vertices[2], &vertices[3],
                  &projected[0], &projected[1], &projected[2], &projected[3],
                  &depth, &transform_flags);

    if (ON_SCREEN(projected[0]) | ON_SCREEN(projected[1]) |
        ON_SCREEN(projected[2]) | ON_SCREEN(projected[3])) {
        display = displays[0];
        gradient_quad = *(POLY_G4 **)(display + 0x8D0);
        *(u8 **)(display + 0x8D0) = (u8 *)gradient_quad + sizeof(POLY_G4);
        SetPolyG4(gradient_quad);
        SetSemiTrans(gradient_quad, 1);

        gradient_quad->r0 = gradient_quad->g0 = gradient_quad->b0 = gradient_quad->r1 = gradient_quad->g1 =
        gradient_quad->r2 = gradient_quad->g2 = gradient_quad->b2 = gradient_quad->r3 = gradient_quad->g3 = 0;
        gradient_quad->b1 = gradient_quad->b3 = 0x40;

        gradient_quad->xy0 = projected[0].xy.word;
        gradient_quad->xy1 = projected[1].xy.word;
        gradient_quad->xy2 = projected[2].xy.word;
        gradient_quad->xy3 = projected[3].xy.word;
        AddPrim(displays[0] + 0x70 + (*(s32 *)((u8 *)owner + 0x60) * 4), gradient_quad);

        display = displays[0];
        draw_mode = *(DR_MODE **)(display + 0x8D0);
        *(u8 **)(display + 0x8D0) = (u8 *)draw_mode + sizeof(DR_MODE);
        SetDrawMode(draw_mode, 0, 0, GetTPage(0, 0, 0x140, 0), 0);
        AddPrim(displays[0] + 0x70 + (*(s32 *)((u8 *)owner + 0x60) * 4), draw_mode);
    }
}
