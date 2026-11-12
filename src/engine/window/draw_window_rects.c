#include "common.h"
#include "shared/game_work.h"
#include "sdk/libgpu.h"
#include "sdk/libgte.h"
#include "sdk/libgte_matrix.h"
#include "sdk/libgpu_packets.h"
#include "shared/gpu_packets.h"

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

#include "sdk/libgpu_types.h"

#define ON_SCREEN(v) \
(((u16)((v).vx + 0x20) < 0x181U) && \
    ((u16)((v).vy + 0x20) < 0x121U))

/* Project and enqueue visible textured and translucent blue gradient rectangles. */
void draw_window_rects(DRAW_DESC *desc) {
    SVECTOR vertices[4];
    SVECTOR projected[4]; /* RotTransPers4 screen XY outputs, one per vertex slot */
    s32 depth;
    s32 transform_flags;
    TEX_RECT *textured;
    RECTANGLE *solid;
    void *owner;
    POLY_FT4 *tex_quad;
    POLY_G4 *gradient_quad;
    DR_MODE *draw_mode;
    GpuContext *display;
    GpuContext **displays;
    s32 page_u;
    s32 tex_u;
    s32 page_y;
    s32 tex_v;

    owner = desc->owner;
    textured = &desc->textured;
    solid = &desc->solid;
    displays = (GpuContext **)&g_game_work;

    vertices[0].vx = vertices[2].vx = textured->x;
    vertices[1].vx = vertices[3].vx = textured->x + textured->width;
    vertices[0].vy = vertices[1].vy = textured->y;
    vertices[2].vy = vertices[3].vy = textured->y + textured->height;
    vertices[0].vz = vertices[1].vz = vertices[2].vz = vertices[3].vz = 0;

    RotTransPers4(&vertices[0], &vertices[1], &vertices[2], &vertices[3],
                  (s32 *)&projected[0], (s32 *)&projected[1], (s32 *)&projected[2], (s32 *)&projected[3],
                  &depth, &transform_flags);

    if (ON_SCREEN(projected[0]) | ON_SCREEN(projected[1]) |
        ON_SCREEN(projected[2]) | ON_SCREEN(projected[3])) {
        display = g_game_work.draw_buffer;
        tex_quad = display->packetCursor;
        display->packetCursor = tex_quad + 1;
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

        /* BYTES: retail copies the packed screen XY word with one lw/sw; member copies compile to two lh/sh */
        *(u32 *)&tex_quad->x0 = *(u32 *)&projected[0];
        /* BYTES: retail copies the packed screen XY word with one lw/sw; member copies compile to two lh/sh */
        *(u32 *)&tex_quad->x1 = *(u32 *)&projected[1];
        /* BYTES: retail copies the packed screen XY word with one lw/sw; member copies compile to two lh/sh */
        *(u32 *)&tex_quad->x2 = *(u32 *)&projected[2];
        /* BYTES: retail copies the packed screen XY word with one lw/sw; member copies compile to two lh/sh */
        *(u32 *)&tex_quad->x3 = *(u32 *)&projected[3];
        AddPrim(g_game_work.draw_buffer + 0x70 + (*(s32 *)((u8 *)owner + 0x60) * 4), tex_quad);
    }

    vertices[0].vx = vertices[2].vx = solid->x;
    vertices[1].vx = vertices[3].vx = solid->x + solid->width;
    vertices[0].vy = vertices[1].vy = solid->y;
    vertices[2].vy = vertices[3].vy = solid->y + solid->height;
    vertices[0].vz = vertices[1].vz = vertices[2].vz = vertices[3].vz = 0;

    RotTransPers4(&vertices[0], &vertices[1], &vertices[2], &vertices[3],
                  (s32 *)&projected[0], (s32 *)&projected[1], (s32 *)&projected[2], (s32 *)&projected[3],
                  &depth, &transform_flags);

    if (ON_SCREEN(projected[0]) | ON_SCREEN(projected[1]) |
        ON_SCREEN(projected[2]) | ON_SCREEN(projected[3])) {
        display = displays[0];
        gradient_quad = display->packetCursor;
        display->packetCursor = gradient_quad + 1;
        SetPolyG4(gradient_quad);
        SetSemiTrans(gradient_quad, 1);

        gradient_quad->red0 = gradient_quad->green0 = gradient_quad->blue0 = gradient_quad->red1 = gradient_quad->green1 =
            gradient_quad->red2 = gradient_quad->green2 = gradient_quad->blue2 = gradient_quad->red3 = gradient_quad->green3 = 0;
        gradient_quad->blue1 = gradient_quad->blue3 = 0x40;

        /* BYTES: retail copies the packed screen XY word with one lw/sw; member copies compile to two lh/sh */
        *(u32 *)&gradient_quad->x0 = *(u32 *)&projected[0];
        /* BYTES: retail copies the packed screen XY word with one lw/sw; member copies compile to two lh/sh */
        *(u32 *)&gradient_quad->x1 = *(u32 *)&projected[1];
        /* BYTES: retail copies the packed screen XY word with one lw/sw; member copies compile to two lh/sh */
        *(u32 *)&gradient_quad->x2 = *(u32 *)&projected[2];
        /* BYTES: retail copies the packed screen XY word with one lw/sw; member copies compile to two lh/sh */
        *(u32 *)&gradient_quad->x3 = *(u32 *)&projected[3];
        AddPrim((u8 *)displays[0] + 0x70 + (*(s32 *)((u8 *)owner + 0x60) * 4), gradient_quad);

        display = displays[0];
        draw_mode = display->packetCursor;
        display->packetCursor = draw_mode + 1;
        SetDrawMode(draw_mode, 0, 0, GetTPage(0, 0, 0x140, 0), 0);
        AddPrim((u8 *)displays[0] + 0x70 + (*(s32 *)((u8 *)owner + 0x60) * 4), draw_mode);
    }
}
