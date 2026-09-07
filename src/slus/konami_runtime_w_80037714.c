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

void func_80037714(DRAW_DESC *desc) {
    VERTEX vertices[4];
    VERTEX projected[4];
    s32 depth;
    s32 flag;
    TEX_RECT *textured;
    RECTANGLE *solid;
    void *owner;
    POLY_FT4 *ft4;
    POLY_G4 *g4;
    DR_MODE *mode;
    u8 *display;
    u8 **global;
    s32 u;
    s32 v;
    s32 page_y;
    s32 v_rem;

    owner = desc->owner;
    textured = &desc->textured;
    solid = &desc->solid;
    global = D_80083160;

    vertices[0].xy.half.x = vertices[2].xy.half.x = textured->x;
    vertices[1].xy.half.x = vertices[3].xy.half.x = textured->x + textured->width;
    vertices[0].xy.half.y = vertices[1].xy.half.y = textured->y;
    vertices[2].xy.half.y = vertices[3].xy.half.y = textured->y + textured->height;
    vertices[0].z = vertices[1].z = vertices[2].z = vertices[3].z = 0;

    RotTransPers4(&vertices[0], &vertices[1], &vertices[2], &vertices[3],
                  &projected[0], &projected[1], &projected[2], &projected[3],
                  &depth, &flag);

    if (ON_SCREEN(projected[0]) | ON_SCREEN(projected[1]) |
        ON_SCREEN(projected[2]) | ON_SCREEN(projected[3])) {
        display = D_80083160[0];
        ft4 = *(POLY_FT4 **)(display + 0x8D0);
        *(u8 **)(display + 0x8D0) = (u8 *)ft4 + sizeof(POLY_FT4);
        SetPolyFT4(ft4);

        ft4->clut = GetClut(textured->clut_x, textured->clut_y);
        ft4->tpage = GetTPage(0, 0, textured->page_x, textured->page_y);
        ft4->r0 = ft4->g0 = ft4->b0 = textured->color;

        u = (textured->page_x % 64) * 4;
        v = textured->tex_x + u;
        ft4->u0 = ft4->u2 = v;
        v += textured->tex_width;
        ft4->u1 = ft4->u3 = v;

        page_y = textured->page_y;
        v_rem = (page_y %= 256) + textured->tex_y;
        ft4->v0 = ft4->v1 = v_rem;
        v_rem += textured->tex_height;
        ft4->v2 = ft4->v3 = v_rem;

        ft4->xy0 = projected[0].xy.word;
        ft4->xy1 = projected[1].xy.word;
        ft4->xy2 = projected[2].xy.word;
        ft4->xy3 = projected[3].xy.word;
        AddPrim(D_80083160[0] + 0x70 + (*(s32 *)((u8 *)owner + 0x60) * 4), ft4);
    }

    vertices[0].xy.half.x = vertices[2].xy.half.x = solid->x;
    vertices[1].xy.half.x = vertices[3].xy.half.x = solid->x + solid->width;
    vertices[0].xy.half.y = vertices[1].xy.half.y = solid->y;
    vertices[2].xy.half.y = vertices[3].xy.half.y = solid->y + solid->height;
    vertices[0].z = vertices[1].z = vertices[2].z = vertices[3].z = 0;

    RotTransPers4(&vertices[0], &vertices[1], &vertices[2], &vertices[3],
                  &projected[0], &projected[1], &projected[2], &projected[3],
                  &depth, &flag);

    if (ON_SCREEN(projected[0]) | ON_SCREEN(projected[1]) |
        ON_SCREEN(projected[2]) | ON_SCREEN(projected[3])) {
        display = global[0];
        g4 = *(POLY_G4 **)(display + 0x8D0);
        *(u8 **)(display + 0x8D0) = (u8 *)g4 + sizeof(POLY_G4);
        SetPolyG4(g4);
        SetSemiTrans(g4, 1);

        g4->r0 = g4->g0 = g4->b0 = g4->r1 = g4->g1 =
        g4->r2 = g4->g2 = g4->b2 = g4->r3 = g4->g3 = 0;
        g4->b1 = g4->b3 = 0x40;

        g4->xy0 = projected[0].xy.word;
        g4->xy1 = projected[1].xy.word;
        g4->xy2 = projected[2].xy.word;
        g4->xy3 = projected[3].xy.word;
        AddPrim(global[0] + 0x70 + (*(s32 *)((u8 *)owner + 0x60) * 4), g4);

        display = global[0];
        mode = *(DR_MODE **)(display + 0x8D0);
        *(u8 **)(display + 0x8D0) = (u8 *)mode + sizeof(DR_MODE);
        SetDrawMode(mode, 0, 0, GetTPage(0, 0, 0x140, 0), 0);
        AddPrim(global[0] + 0x70 + (*(s32 *)((u8 *)owner + 0x60) * 4), mode);
    }
}
